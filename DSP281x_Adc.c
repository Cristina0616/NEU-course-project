// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:11:45 $
//###########################################################################
//
// FILE:	DSP281x_Adc.c
//
// TITLE:	DSP281x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

#define ADC_usDELAY  8000L
#define ADC_usDELAY2 20L

//---------------------------------------------------------------------------
// InitAdc: 
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
	extern void DSP28x_usDelay(Uint32 Count);
	Uint16 i;
	
    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap and reference circuitry.
    // After a 5ms delay the rest of the ADC can be powered up. After ADC
    // powerup, another 20us delay is required before performing the first
    // ADC conversion. Please note that for the delay function below to
    // operate correctly the CPU_CLOCK_SPEED define statement in the
    // DSP28_Examples.h file must contain the correct CPU clock period in
    // nanoseconds. For example:

	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;	// ADCCLK = HSPCLK/2,ͬ������ģʽ
	DELAY_US(ADC_usDELAY);                  // ��ʱ800us�ȴ��趨�ɹ�
	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;		// ģ���·�ϵ�
	DELAY_US(ADC_usDELAY2);                 // ��ʱ20us�ȴ�ģ���·�ϵ�

	AdcRegs.ADCTRL1.bit.RESET = 1;          //��λADC
	for( i = 0;i < 10000;i++ )              //��ʱ�ȴ���λ
	{
		;
	}
	AdcRegs.ADCTRL1.all = 0x1240; //�������ģʽ�����ڴ�С=3*ADCCLK,��������ʱ�ӷ�Ƶ������ת��ģʽ��˫����ģʽ
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;   //����ת��ģʽ
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;   //˫����ģʽ
	AdcRegs.ADCTRL2.all = 0x4100;       //��λ��������ʹ��EVA����ADCת��
	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 3; //��϶�Ͳο���·�ϵ�
	for( i = 0;i < 10000;i++ )  //��ʱ�ȴ���·�ϵ�
	{
		;
	}
	AdcRegs.ADCTRL3.bit.ADCPWDN = 1; //ģ���·�ϵ�
	for( i = 0;i < 5000;i++ )   //��ʱ�ȴ���·�ϵ�
	{
		;
	}
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 2; // HSPCLK/[4*(ADCTRL1[7] + 1)] = ADCCLK
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 1;  //���ת��ͨ���� = 2
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0xc; //1100 ADCINB4 Ia �������AdcResult[0]
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0xd; //1101 ADCINB5 Ib �������AdcResult[1]
}	
//�˴�ʹ��˫���� ͬ������ģʽ�����ڽ�����2��ͨ����Ҫ���������ǿ���ʵ�ֲ�����
//===========================================================================
// No more.
//===========================================================================
