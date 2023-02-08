// MIT License
// Copyright (c) 2022 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// SOFTWARE.

//////////////////////////////////////////////////////////////////////////////////
// Module Name: lab4 FIR
// Purpose:
//    This is source file for the Lab4 Application Project.
// Reference:
//////////////////////////////////////////////////////////////////////////////////

#include "pynq_z2_audio.h"
#include <stdio.h>
#include <xil_io.h>
#include <sleep.h>
#include "xiicps.h"
#include <xil_printf.h>
#include <xparameters.h>
#include "xfir.h"
#include "xuartps.h"
#include "xscutimer.h"
#include "xscugic.h"


unsigned char IicConfig(unsigned int DeviceIdPS);
void AudioPllConfig();
void AudioWriteToReg(unsigned char u8RegAddr, unsigned char u8Data);
void AudioConfigureJacks();
void LineinLineoutConfig();

XIicPs Iic;

typedef short		Xint16;
typedef long		Xint32;

// HLS FIR HW instance
XFir HlsFir_left, HlsFir_right;
//Interrupt Controller Instance
XScuGic ScuGic;
//Global variables used by ISR
int ResultAvailHlsFir_left, ResultAvailHlsFir_right;

int hls_fir_init(XFir *hls_firPtr_left, XFir *hls_firPtr_right)
{
   XFir_Config *cfgPtr_left, *cfgPtr_right;
   int status;

   cfgPtr_left = XFir_LookupConfig(XPAR_FIR_LEFT_DEVICE_ID);
   if (!cfgPtr_left) {
      print("ERROR: Lookup of Left FIR configuration failed.\n\r");
      return XST_FAILURE;
   }
   status = XFir_CfgInitialize(hls_firPtr_left, cfgPtr_left);
   if (status != XST_SUCCESS) {
      print("ERROR: Could not initialize left FIR.\n\r");
      return XST_FAILURE;
   }

   cfgPtr_right = XFir_LookupConfig(XPAR_FIR_RIGHT_DEVICE_ID);
   if (!cfgPtr_right) {
      print("ERROR: Lookup of Right FIR configuration failed.\n\r");
      return XST_FAILURE;
   }
   status = XFir_CfgInitialize(hls_firPtr_right, cfgPtr_right);
   if (status != XST_SUCCESS) {
      print("ERROR: Could not initialize right FIR.\n\r");
      return XST_FAILURE;
   }

   return status;
}

void hls_fir_left_isr(void *InstancePtr)
{k
	   XFir *pAccelerator = (XFir *)InstancePtr;

	   // clear the local interrupt
	   XFir_InterruptClear(pAccelerator,1);

	   ResultAvailHlsFir_left = 1;
}

void hls_fir_right_isr(void *InstancePtr)
{
	   XFir *pAccelerator = (XFir *)InstancePtr;

	   // clear the local interrupt
	   XFir_InterruptClear(pAccelerator,1);

	   ResultAvailHlsFir_right = 1;
}

int setup_interrupt()
{
	   //This functions sets up the interrupt on the ARM
	   int result;
	   XScuGic_Config *pCfg = XScuGic_LookupConfig(XPAR_SCUGIC_0_DEVICE_ID);
	   if (pCfg == NULL){
	      print("Interrupt Configuration Lookup Failed\n\r");
	      return XST_FAILURE;
	   }
	   result = XScuGic_CfgInitialize(&ScuGic,pCfg,pCfg->CpuBaseAddress);
	   if(result != XST_SUCCESS){
	      return result;
	   }
	   // self test
	   result = XScuGic_SelfTest(&ScuGic);
	   if(result != XST_SUCCESS){
	      return result;
	   }
	   // Initialize the exception handler
	   Xil_ExceptionInit();
	   // Register the exception handler
	   Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,&ScuGic);
	   //Enable the exception handler
	   Xil_ExceptionEnable();
	   // Connect the Left FIR ISR to the exception table
	   result = XScuGic_Connect(&ScuGic,XPAR_FABRIC_FIR_LEFT_INTERRUPT_INTR,(Xil_InterruptHandler)hls_fir_left_isr,&HlsFir_left);
	   if(result != XST_SUCCESS){
	      return result;
	   }
	   // Connect the Right FIR ISR to the exception table
	   result = XScuGic_Connect(&ScuGic,XPAR_FABRIC_FIR_RIGHT_INTERRUPT_INTR,(Xil_InterruptHandler)hls_fir_right_isr,&HlsFir_right);
	   if(result != XST_SUCCESS){
	      return result;
	   }
	   // Enable the Left FIR ISR
	   XScuGic_Enable(&ScuGic,XPAR_FABRIC_FIR_LEFT_INTERRUPT_INTR);
	   // Enable the Right FIR ISR
	   XScuGic_Enable(&ScuGic,XPAR_FABRIC_FIR_RIGHT_INTERRUPT_INTR);
	   return XST_SUCCESS;
}

void filter_or_bypass_input(void)
{
	unsigned long u32DataL, u32DataR;
	unsigned long u32Temp;
	int sw_check;

	while (1)
	{
		do //wait for RX data to become available
		{
			u32Temp = Xil_In32(I2S_STATUS_REG);
		} while ( u32Temp == 0);

		Xil_Out32(I2S_STATUS_REG, 0x00000001); //Clear data rdy bit

		u32DataL = Xil_In32(I2S_DATA_RX_L_REG);
		u32DataR = Xil_In32(I2S_DATA_RX_R_REG);
		sw_check = Xil_In32(XPAR_AXI_GPIO_0_BASEADDR+8);
		if(sw_check & 01) // SW0=1 then pass the sample through the filter
		{
			// send samples after shifting least significant 8 bits as the filter
			// requires 16 bit input sample
			XFir_Set_x(&HlsFir_left, u32DataL >> 8);
			XFir_Set_x(&HlsFir_right, u32DataR >> 8);
			// Clear done flags
			ResultAvailHlsFir_left = 0;
			ResultAvailHlsFir_right = 0;
			// issue start
			XFir_Start(&HlsFir_left);
			XFir_Start(&HlsFir_right);
			// wait for done interrupt on each channel and then read the corresponding output sample
		    while(!ResultAvailHlsFir_left);
		    u32DataL = XFir_Get_y(&HlsFir_left);
		    while(!ResultAvailHlsFir_right);
			u32DataR = XFir_Get_y(&HlsFir_right);
			// shift left by 8 bits as output sample is 16 bit whereas CODEC requires 24 bits
			u32DataL = u32DataL << 8;
			u32DataR = u32DataR << 8;
		}
		Xil_Out32(I2S_DATA_TX_L_REG, u32DataL);
		Xil_Out32(I2S_DATA_TX_R_REG, u32DataR);
	}
}


int main(void)
{
	int status;

	//Configure the IIC data structure
	IicConfig(XPAR_XIICPS_0_DEVICE_ID);

	//Configure the Audio Codec's PLL
	AudioPllConfig();

	//Configure the Line in and Line out ports.
	//Call LineInLineOutConfig() for a configuration that
	//enables the HP jack too.
//	AudioConfigureJacks();
	LineinLineoutConfig();

	xil_printf("ADAU1761 configured\n\r");

	// Setup the FIR instances
	status=hls_fir_init(&HlsFir_left, &HlsFir_right);
    if(status != XST_SUCCESS){
	   print("HLS peripheral setup failed\n\r");
	   return(-1);
    }

    //Setup the interrupt
    status = setup_interrupt();
    if(status != XST_SUCCESS){
       print("Interrupt setup failed\n\r");
       return(-1);
    }

    // Enable Global and instance interrupts
    XFir_InterruptEnable(&HlsFir_left,1);
    XFir_InterruptGlobalEnable(&HlsFir_left);
    XFir_InterruptEnable(&HlsFir_right,1);
    XFir_InterruptGlobalEnable(&HlsFir_right);

	ResultAvailHlsFir_left = 0;
	ResultAvailHlsFir_right = 0;

	filter_or_bypass_input(); // check SW0 in the function.  If 1 then filter otherwise bypasss
	return 0;
}

unsigned char IicConfig(unsigned int DeviceIdPS)
{

	XIicPs_Config *Config;
	int Status;

	//Initialize the IIC driver so that it's ready to use
	//Look up the configuration in the config table, then initialize it.
	Config = XIicPs_LookupConfig(DeviceIdPS);
	if(NULL == Config) {
		return XST_FAILURE;
	}

	Status = XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	//Set the IIC serial clock rate.
	XIicPs_SetSClk(&Iic, IIC_SCLK_RATE);

	return XST_SUCCESS;
}


/******************************************************************************
 * Configures audio codes's internal PLL. With MCLK = 8 MHz it configures the
 * PLL for a VCO frequency = 49.152 MHz, and an audio sample rate of 48 KHz.
 *
 * @param	none.
 *
 * @return	none.
 *****************************************************************************/
void AudioPllConfig() {

	unsigned char u8TxData[8], u8RxData[6];

	AudioWriteToReg(R0_CLOCK_CONTROL, 0x0E);

	// Write 6 bytes to R1
	u8TxData[0] = 0x40;
	u8TxData[1] = 0x02;
	u8TxData[2] = 0x02; // byte 1
	u8TxData[3] = 0x71; // byte 2
	u8TxData[4] = 0x02; // byte 3
	u8TxData[5] = 0x3C; // byte 4
	u8TxData[6] = 0x21; // byte 5
	u8TxData[7] = 0x01; // byte 6


	XIicPs_MasterSendPolled(&Iic, u8TxData, 8, (IIC_SLAVE_ADDR >> 1));
	while(XIicPs_BusIsBusy(&Iic));

	// Poll PLL Lock bit
	u8TxData[0] = 0x40;
	u8TxData[1] = 0x02;

	do {
		XIicPs_MasterSendPolled(&Iic, u8TxData, 2, (IIC_SLAVE_ADDR >> 1));
		while(XIicPs_BusIsBusy(&Iic));
		XIicPs_MasterRecvPolled(&Iic, u8RxData, 6, (IIC_SLAVE_ADDR >> 1));
		while(XIicPs_BusIsBusy(&Iic));
	}
	while((u8RxData[5] & 0x02) == 0);

	AudioWriteToReg(R0_CLOCK_CONTROL, 0x0F);//COREN
}

/******************************************************************************
 * Function to write one byte (8-bits) to one of the registers from the audio
 * controller.
 *
 * @param	u8RegAddr is the LSB part of the register address (0x40xx).
 * @param	u8Data is the data byte to write.
 *
 * @return	none.
 *****************************************************************************/
void AudioWriteToReg(unsigned char u8RegAddr, unsigned char u8Data) {

	unsigned char u8TxData[3];

	u8TxData[0] = 0x40;
	u8TxData[1] = u8RegAddr;
	u8TxData[2] = u8Data;

	XIicPs_MasterSendPolled(&Iic, u8TxData, 3, (IIC_SLAVE_ADDR >> 1));
	while(XIicPs_BusIsBusy(&Iic));
}

/******************************************************************************
 * Configures audio codes's various mixers, ADC's, DAC's, and amplifiers to
 * accept stereo input from line in and push stereo output to line out
 *
 * @param	none.
 *
 * @return	none.
 *****************************************************************************/
void AudioConfigureJacks()
{
	AudioWriteToReg(R4_RECORD_MIXER_LEFT_CONTROL_0, 0x01); //enable mixer 1
	AudioWriteToReg(R5_RECORD_MIXER_LEFT_CONTROL_1, 0x07); //unmute Left channel of line in into mxr 1 and set gain to 6 db
	AudioWriteToReg(R6_RECORD_MIXER_RIGHT_CONTROL_0, 0x01); //enable mixer 2
	AudioWriteToReg(R7_RECORD_MIXER_RIGHT_CONTROL_1, 0x07); //unmute Right channel of line in into mxr 2 and set gain to 6 db
	AudioWriteToReg(R19_ADC_CONTROL, 0x13); //enable ADCs

	AudioWriteToReg(R22_PLAYBACK_MIXER_LEFT_CONTROL_0, 0x21); //unmute Left DAC into Mxr 3; enable mxr 3
	AudioWriteToReg(R24_PLAYBACK_MIXER_RIGHT_CONTROL_0, 0x41); //unmute Right DAC into Mxr4; enable mxr 4
	AudioWriteToReg(R26_PLAYBACK_LR_MIXER_LEFT_LINE_OUTPUT_CONTROL, 0x05); //unmute Mxr3 into Mxr5 and set gain to 6db; enable mxr 5
	AudioWriteToReg(R27_PLAYBACK_LR_MIXER_RIGHT_LINE_OUTPUT_CONTROL, 0x11); //unmute Mxr4 into Mxr6 and set gain to 6db; enable mxr 6
	AudioWriteToReg(R29_PLAYBACK_HEADPHONE_LEFT_VOLUME_CONTROL, 0x00);//Mute Left channel of HP port (LHP)
	AudioWriteToReg(R30_PLAYBACK_HEADPHONE_RIGHT_VOLUME_CONTROL, 0x00); //Mute Right channel of HP port (LHP)
	AudioWriteToReg(R31_PLAYBACK_LINE_OUTPUT_LEFT_VOLUME_CONTROL, 0xE6); //set LOUT volume (0db); unmute left channel of Line out port; set Line out port to line out mode
	AudioWriteToReg(R32_PLAYBACK_LINE_OUTPUT_RIGHT_VOLUME_CONTROL, 0xE6); // set ROUT volume (0db); unmute right channel of Line out port; set Line out port to line out mode

	AudioWriteToReg(R35_PLAYBACK_POWER_MANAGEMENT, 0x03); //enable left and right channel playback (not sure exactly what this does...)
	AudioWriteToReg(R36_DAC_CONTROL_0, 0x03); //enable both DACs

	AudioWriteToReg(R58_SERIAL_INPUT_ROUTE_CONTROL, 0x01); //Connect I2S serial port output (SDATA_O) to DACs
	AudioWriteToReg(R59_SERIAL_OUTPUT_ROUTE_CONTROL, 0x01); //connect I2S serial port input (SDATA_I) to ADCs

	AudioWriteToReg(R65_CLOCK_ENABLE_0, 0x7F); //Enable clocks
	AudioWriteToReg(R66_CLOCK_ENABLE_1, 0x03); //Enable rest of clocks
}

/******************************************************************************
 * Configures Line-In input, ADC's, DAC's, Line-Out and HP-Out.
 *
 * @param   none.
 *
 * @return	none.
 *****************************************************************************/
void LineinLineoutConfig() {

	AudioWriteToReg(R17_CONVERTER_CONTROL_0, 0x06);//96 kHz
	AudioWriteToReg(R64_SERIAL_PORT_SAMPLING_RATE, 0x06);//96 kHz
	AudioWriteToReg(R19_ADC_CONTROL, 0x13);
	AudioWriteToReg(R36_DAC_CONTROL_0, 0x03);
	AudioWriteToReg(R35_PLAYBACK_POWER_MANAGEMENT, 0x03);
	AudioWriteToReg(R58_SERIAL_INPUT_ROUTE_CONTROL, 0x01);
	AudioWriteToReg(R59_SERIAL_OUTPUT_ROUTE_CONTROL, 0x01);
	AudioWriteToReg(R65_CLOCK_ENABLE_0, 0x7F);
	AudioWriteToReg(R66_CLOCK_ENABLE_1, 0x03);

	AudioWriteToReg(R4_RECORD_MIXER_LEFT_CONTROL_0, 0x01);
	AudioWriteToReg(R5_RECORD_MIXER_LEFT_CONTROL_1, 0x05);//0 dB gain
	AudioWriteToReg(R6_RECORD_MIXER_RIGHT_CONTROL_0, 0x01);
	AudioWriteToReg(R7_RECORD_MIXER_RIGHT_CONTROL_1, 0x05);//0 dB gain

	AudioWriteToReg(R22_PLAYBACK_MIXER_LEFT_CONTROL_0, 0x21);
	AudioWriteToReg(R24_PLAYBACK_MIXER_RIGHT_CONTROL_0, 0x41);
	AudioWriteToReg(R26_PLAYBACK_LR_MIXER_LEFT_LINE_OUTPUT_CONTROL, 0x03);//0 dB
	AudioWriteToReg(R27_PLAYBACK_LR_MIXER_RIGHT_LINE_OUTPUT_CONTROL, 0x09);//0 dB
	AudioWriteToReg(R29_PLAYBACK_HEADPHONE_LEFT_VOLUME_CONTROL, 0xE7);//0 dB
	AudioWriteToReg(R30_PLAYBACK_HEADPHONE_RIGHT_VOLUME_CONTROL, 0xE7);//0 dB
	AudioWriteToReg(R31_PLAYBACK_LINE_OUTPUT_LEFT_VOLUME_CONTROL, 0x00);//0 dB
	AudioWriteToReg(R32_PLAYBACK_LINE_OUTPUT_RIGHT_VOLUME_CONTROL, 0x00);//0 dB
}

