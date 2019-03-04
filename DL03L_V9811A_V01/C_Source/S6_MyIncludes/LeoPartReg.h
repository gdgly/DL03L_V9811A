/******************** (C) COPYRIGHT 2011 Vangotech ********************
* File Name          : ADC.C
* Author             : LIM
* Version            : V0.1
* Date               : 2/15/2011
* Description        : register define
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, VANGOTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifndef _LEOPARTREG_H_
#define _LEOPARTREG_H_
#include "dw8051.h"

#define XBYTE 		((unsigned char volatile xdata *) 0)

/*******************************************
			sys ctrl registers
*******************************************/
sfr  Systate  = 0xa1;
sfr  version	= 0xa2;
sfr  wdt0      = 0xce;	// 0xa5
sfr  wdt1      = 0xcf;	// 0x5a
sfr  SysCtrl   = 0x80;

sbit MCUFRQ  = SysCtrl^0;
sbit SLEEP0  = SysCtrl^1;
sbit SLEEP1  = SysCtrl^2;
sbit LCDG      = SysCtrl^3;
sbit PMG      = SysCtrl^4;
sbit FSC       = SysCtrl^5;
sbit FWC      = SysCtrl^6;
sbit MEAFRQ= SysCtrl^7;
sfr PLLLCK =0xa3;
sfr CBANK =0xa0;
sfr SPCFNC =0X8F;
/**************************************
FAST IO register
****************************************/

sfr P9OE = 0xa4;
sfr P9IE =0xa5;
sfr P9DO=0xa6;
sfr P9DI=0xa7;
sfr P9FC=0xad;

sfr P10OE = 0xa9;
sfr P10IE =0xaa;
sfr P10DO=0xab;
sfr P10DI=0xac;
sfr P10FC=0xae;

/******************************************
RTC register
*******************************************/
sfr  RTCPEN 	 = 0x90;    // 0x96
sfr  RTCPWD = 0x97;	// 0x57, 0xd7
sfr  INTRTC   = 0x96;
sfr  RTCCH =0x94;
sfr  RTCCL =0x95;
sfr  RTCLATCH  =0xDA;
sfr  DIVTHH = 0xDB;
sfr  DIVTHM = 0xDC;
sfr  DIVTHL  =0xDD;
sfr  RTCCNT= 0xDE;
sfr  SECINT= 0xDF;   //2016-2-18  mj  //
sfr  RTCSC = 0x9a;
sfr  RTCMiC = 0x9b;
sfr  RTCHC = 0x9c;
sfr  RTCDC =0x9d;
sfr  RTCWC =0x9E;
sfr  RTCMoC = 0x9f;
sfr RTCYC  =0x93; 

sbit A0REG =ACC^0;
sbit A1REG =ACC^1;
sbit A2REG =ACC^2;
sbit A3REG =ACC^3;
sbit A4REG =ACC^4;
sbit A5REG =ACC^5;
sbit A6REG =ACC^6;
sbit A7REG =ACC^7;

sbit B0REG =B^0;
sbit B1REG =B^1;
sbit B2REG =B^2;
sbit B3REG =B^3;
sbit B4REG =B^4;
sbit B5REG =B^5;
sbit B6REG =B^6;
sbit B7REG =B^7;

    
/**************************************************
			Analog Interface regist
**************************************************/
#define CtrlCry0       XBYTE[0X285F]    //����΢��
#define CryCtrl1       XBYTE[0x2860]   //������ݵ���
#define CryCtrl2       XBYTE[0x2861]   //�������
#define CtrlCLK        XBYTE[0x2867]   //PLL DSP ADC ����Ƶ������
#define CtrlPLL        XBYTE[0x2868]    //PLL ����

#define CtrlADC0    	XBYTE[0x2858]	//ADC �������	 
#define CtrlADC1    	XBYTE[0x2859]	//ADC ����ƫ�ÿ���
#define CtrlADC2    	XBYTE[0x285a]	//ADC���������ƼĴ���
#define CtrlADC3    	XBYTE[0x285b]	//ADC ���ԼĴ���
#define CtrlADC4    	XBYTE[0x285d]	//
#define CtrlADC5      XBYTE[0x2863]	//Mͨ����������
#define CtrlADC6    	XBYTE[0x2864]	// ADC ͨ�����ؼĴ���
#define CtrlM			XBYTE[0X2865]
#define CtrlLDO         XBYTE[0X2866]
#define CtrlBGP         XBYTE[0X2862]  //BGP REF���������Ĵ���
#define XRAMPWD  XBYTE[0x28a0]
/**************************************************
			PM ctrl
**************************************************/

#define PMCtrl1      0x2878  // PM���ƼĴ���1  0x2878;
#define PMCtrl2    	 0x2879	// PM���ƼĴ���2  0x2879;
#define PMCtrl3    	 0x287a	// PM���ƼĴ���3  0x287a;
#define PHCCtrl1     0x287b// �ǲ�У�����ƼĴ���1  0x287b;
#define PHCCtrl2     0x287c// �ǲ�У�����ƼĴ���2  0x287c;
#define PMCtrl4    	 0x287d // PM���ƼĴ���4  0x287d;
#define CFCtrl    	 0x287e	// ����������ƼĴ���  0x287e;



/********************************************
		interrupt control regist
********************************************/

/* External interrupt 2 */
#define ExInt2IFG    	XBYTE[0x2840]//�ж�����8�жϱ�־�����󣩼Ĵ��� 0x2840
#define ExInt2IN    	XBYTE[0x2841]//�ж�����8��չ�ж��������ͼĴ��� 0x2841
#define ExInt2OUT    XBYTE[0x2842]//�ж�����8��չ�ж�������ͼĴ��� 0x2842
#define ExInt2IE    	XBYTE[0x2843]//�ж�����8��չ�ж�ʹ�ܼĴ��� 0x2843
#define ExInt2OV    	XBYTE[0x2844]//�ж�����8��չ�ж϶��мĴ��� 0x2844
/* External interrupt 3 */
#define ExInt3IFG    	XBYTE[0x2848]//�ж�����9�жϱ�־�����󣩼Ĵ��� 0x2848
#define ExInt3IN    	XBYTE[0x2849]//�ж�����9��չ�ж��������ͼĴ��� 0x2849
#define ExInt3OUT    	XBYTE[0x284a]//�ж�����9��չ�ж�ʹ�ܼĴ��� 0x284a
#define ExInt3IE    	XBYTE[0x284b]//�ж�����9��չ�ж�ʹ�ܼĴ��� 0x284b
#define ExInt3OV    	XBYTE[0x284c]//�ж�����9��չ�ж϶��мĴ��� 0x284c
/* External interrupt 4 */
#define ExInt4IFG    	XBYTE[0x2850]//�ж�����10�жϱ�־�����󣩼Ĵ��� 0x2850
#define ExInt4IN    	XBYTE[0x2851]//�ж�����10��չ�ж��������ͼĴ��� 0x2851
#define ExInt4OUT    	XBYTE[0x2852]//�ж�����10��չ�ж�ʹ�ܼĴ��� 0x2852
#define ExInt4IE    	XBYTE[0x2853]//�ж�����10��չ�ж�ʹ�ܼĴ��� 0x2853
#define ExInt4OV    	XBYTE[0x2854]//�ж�����10��չ�ж϶��мĴ��� 0x2854

/*******************************************
				LCD Reg
*******************************************/
#define LCDM0    	XBYTE[0x2C00]//��ʾ����Ĵ��� 0x2800 
#define LCDM1    	XBYTE[0x2C01]//��ʾ����Ĵ��� 0x2801
#define LCDM2    	XBYTE[0x2C02]//��ʾ����Ĵ��� 0x2802
#define LCDM3    	XBYTE[0x2C03]//��ʾ����Ĵ��� 0x2803
#define LCDM4    	XBYTE[0x2C04]//��ʾ����Ĵ��� 0x2804
#define LCDM5    	XBYTE[0x2C05]//��ʾ����Ĵ��� 0x2805
#define LCDM6    	XBYTE[0x2C06]//��ʾ����Ĵ��� 0x2806
#define LCDM7    	XBYTE[0x2C07]//��ʾ����Ĵ��� 0x2807
#define LCDM8    	XBYTE[0x2C08]//��ʾ����Ĵ��� 0x2808
#define LCDM9    	XBYTE[0x2C09]//��ʾ����Ĵ��� 0x2809
#define LCDM10    	XBYTE[0x2C0a]//��ʾ����Ĵ��� 0x280a
#define LCDM11    	XBYTE[0x2C0b]//��ʾ����Ĵ��� 0x280b
#define LCDM12    	XBYTE[0x2C0c]//��ʾ����Ĵ��� 0x280c
#define LCDM13    	XBYTE[0x2C0d]//��ʾ����Ĵ��� 0x280d
#define LCDM14    	XBYTE[0x2C0e]//��ʾ����Ĵ��� 0x280e
#define LCDM15    	XBYTE[0x2C0f]//��ʾ����Ĵ��� 0x280f
#define LCDM16    	XBYTE[0x2C10]//��ʾ����Ĵ��� 0x2810
#define LCDM17    	XBYTE[0x2C11]//��ʾ����Ĵ��� 0x2811
#define LCDM18    	XBYTE[0x2C12]//��ʾ����Ĵ��� 0x2812
#define LCDM19    	XBYTE[0x2C13]//��ʾ����Ĵ��� 0x2813
#define LCDM20        XBYTE[0X2C14]
#define LCDM21        XBYTE[0X2C15]
#define LCDM22        XBYTE[0X2C16]
#define LCDM23        XBYTE[0X2C17]
#define LCDM24        XBYTE[0X2C18]
#define LCDM26        XBYTE[0X2C19]
#define LCDM27        XBYTE[0X2C1a]
#define LCDM28        XBYTE[0X2C1b]
#define LCDM29        XBYTE[0X2C1c]
#define LCDM30        XBYTE[0x2C28]
#define LCDM31        XBYTE[0x2C29]
#define LCDM32        XBYTE[0x2C2A]
#define LCDM33        XBYTE[0x2C2B]
#define LCDM34        XBYTE[0x2C2C]
#define LCDM35        XBYTE[0x2C2D]
#define LCDM38        XBYTE[0x2C30]
#define LCDM39        XBYTE[0x2C31]




#define CtrlLCDV    XBYTE[0x285e]//LCD��ѹ������

#define LCDCtrl    	XBYTE[0x2c1E]// ��ʾ���ƼĴ��� 0x2814
#define SegCtrl0    XBYTE[0x2c1F]// ��ʾ���ƼĴ���2 0x2815
#define SegCtrl1    XBYTE[0x2c20]// ��ʾ���ƼĴ���3 0x2816
#define SegCtrl2    XBYTE[0x2c21]// ��ʾ���ƼĴ���4 0x2817
#define SegCtrl3    XBYTE[0x2c22]// ��ʾ���ƼĴ���5 0x2818
#define SegCtrl4    XBYTE[0x2c23]// ��ʾ���ƼĴ���6 0x2819
#define LCDVCtrl     XBYTE[0x2c5e] //LCD������ѹ���ƼĴ���

/*********************************************
			timer & uart regist
*********************************************/

/* extern uart2 & extern timer2-0 */
#define TCON2    	XBYTE[0x2820]//timer2����/״̬�Ĵ��� 0x2820
#define TMOD2    	XBYTE[0x2821]//timer2 TMOD 0x2821
#define TH20    	XBYTE[0x2822]//UART2 TH0 0x2822
#define TH21    	XBYTE[0x2823]//UART2 TH1 0x2823
#define TL20    	XBYTE[0x2824]//UART2 TL0 0x2824
#define TL21    	XBYTE[0x2825]//UART2 TL1 0x2825
#define SCON2    	XBYTE[0x2826]//UART2 ���пڿ��ƼĴ���SCON 0x2826
#define SBUF2    	XBYTE[0x2827]//UART2 ���пڻ���Ĵ���SBUF 0x2827
#define CARRHH   XBYTE[0X2898] //�ز������Ĵ���1��λ�ֽ�
#define CARRHL   XBYTE[0X2899] //�ز������Ĵ���1��λ�ֽ�
#define CARRLH   XBYTE[0x289a] //
#define CARRLL   XBYTE[0X289B]
/* extern uart3 & extern timer3-0 */
#define TCON3    	XBYTE[0x2828]//timer3����/״̬�Ĵ��� 0x2828
#define TMOD3    	XBYTE[0x2829]//timer3 TMOD 0x2829
#define TH30    	XBYTE[0x282a]//UART3 TH0 0x282a
#define TH31    	XBYTE[0x282b]//UART3 TH1 0x282b
#define TL30    	XBYTE[0x282c]//UART3 TL0 0x282c
#define TL31    	XBYTE[0x282d]//UART3 TL1 0x282d
#define SCON3    	XBYTE[0x282e]//UART3 ���пڿ��ƼĴ���SCON 0x282e
#define SBUF3    	XBYTE[0x282f]//UART3 ���пڻ���Ĵ���SBUF 0x282f
/* extern uart4 & extern timer4-0 */
#define TCON4    	XBYTE[0x2830]//timer4����/״̬�Ĵ��� 0x2830
#define TMOD4    	XBYTE[0x2831]//timer4 TMOD 0x2831
#define TH40    	XBYTE[0x2832]//UART4 TH0 0x2832
#define TH41    	XBYTE[0x2833]//UART4 TH1 0x2833
#define TL40    	XBYTE[0x2834]//UART4 TL0 0x2834
#define TL41    	XBYTE[0x2835]//UART4 TL1 0x2835
#define SCON4    	XBYTE[0x2836]//UART4 ���пڿ��ƼĴ���SCON 0x2836
#define SBUF4    	XBYTE[0x2837]//UART4 ���пڻ���Ĵ���SBUF 0x2837
/* extern uart5 & extern timer5-0 */
#define TCON5    	XBYTE[0x2838]//timer5����/״̬�Ĵ��� 0x2838
#define TMOD5    	XBYTE[0x2839]//timer5 TMOD 0x2839
#define TH50    	XBYTE[0x283a]//UART5 TH0 0x283a
#define TH51    	XBYTE[0x283b]//UART5 TH1 0x283b
#define TL50    	XBYTE[0x283c]//UART5 TL0 0x283c
#define TL51    	XBYTE[0x283d]//UART5 TL1 0x283d
#define SCON5    	XBYTE[0x283e]//UART5 ���пڿ��ƼĴ���SCON 0x283e
#define SBUF5    	XBYTE[0x283f]//UART5 ���пڻ���Ĵ���SBUF 0x283f



/****************************************** 
			gpio regist 
******************************************/

/* port0_4_bits */
#define P0OE    	XBYTE[0x28a8]//P0���ʹ�ܼĴ��� 0x28a8
#define P0IE    	XBYTE[0x28a9]//P0����ʹ�ܼĴ��� 0x28a9
#define P0OD    	XBYTE[0x28aa]//P0������ݼĴ��� 0x28aa
#define P0ID    	XBYTE[0x28ab]//P0�������ݼĴ��� 0x28ab
/* port1_5_bits */
#define P1OE    	XBYTE[0x28ac]//P1���ʹ�ܼĴ��� 0x28ac
#define P1IE    	XBYTE[0x28ad]//P1����ʹ�ܼĴ��� 0x28ad
#define P1OD    	XBYTE[0x28ae]//P1������ݼĴ��� 0x28ae
#define P1ID    	XBYTE[0x28af]//P1�������ݼĴ��� 0x28af
/* port2_6_bits */
#define P2OE    	XBYTE[0x28b0]//P2���ʹ�ܼĴ��� 0x28b0
#define P2IE    	XBYTE[0x28b1]//P2����ʹ�ܼĴ��� 0x28b1
#define P2OD    	XBYTE[0x28b2]//P2������ݼĴ��� 0x28b2
#define P2ID    	XBYTE[0x28b3]//P2�������ݼĴ��� 0x28b3
/* port3_4_bits */
#define P3OE    	XBYTE[0x28b4]//P3���ʹ�ܼĴ��� 0x28b4
#define P3IE    	XBYTE[0x28b5]//P3����ʹ�ܼĴ��� 0x28b5
#define P3OD    	XBYTE[0x28b6]//P3������ݼĴ��� 0x28b6
#define P3ID    	XBYTE[0x28b7]//P3�������ݼĴ��� 0x28b7
/* port4_8_bits */
#define P4OE    	XBYTE[0x28b8]//P4���ʹ�ܼĴ��� 0x28b8
#define P4IE    	XBYTE[0x28b9]//P4����ʹ�ܼĴ��� 0x28b9
#define P4OD    	XBYTE[0x28ba]//P4������ݼĴ��� 0x28ba
#define P4ID    	XBYTE[0x28bb]//P4�������ݼĴ��� 0x28bb
/* port5_8_bits */
#define P5OE    	XBYTE[0x28bc]//P5���ʹ�ܼĴ��� 0x28bc
#define P5IE    	XBYTE[0x28bd]//P5����ʹ�ܼĴ��� 0x28bd
#define P5OD    	XBYTE[0x28be]//P5������ݼĴ��� 0x28be
#define P5ID    	XBYTE[0x28bf]//P5�������ݼĴ��� 0x28bf
/* port6_8_bits */
#define P6OE    	XBYTE[0x28c0]//P6���ʹ�ܼĴ��� 0x28c0
#define P6IE    	XBYTE[0x28c1]//P6����ʹ�ܼĴ��� 0x28c1
#define P6OD    	XBYTE[0x28c2]//P6������ݼĴ��� 0x28c2
#define P6ID    	XBYTE[0x28c3]//P6�������ݼĴ��� 0x28c3
/* special function select regist */
#define P10FS    	XBYTE[0x28c4]//P1.0����ѡ��Ĵ��� 0x28c4
#define P11FS    	XBYTE[0x28c5]//P1.1����ѡ��Ĵ��� 0x28c5
#define P12FS    	XBYTE[0x28c6]//P1.2����ѡ��Ĵ��� 0x28c6
#define P13FS    	XBYTE[0x28c7]//P1.3����ѡ��Ĵ��� 0x28c7
#define P14FS    	XBYTE[0x28c8]//P1.4����ѡ��Ĵ��� 0x28c8
#define P20FS    	XBYTE[0x28c9]//P2.0����ѡ��Ĵ��� 0x28c9
#define P21FS    	XBYTE[0x28ca]//P2.1����ѡ��Ĵ��� 0x28ca
#define P22FS    	XBYTE[0x28cb]//P2.2����ѡ��Ĵ��� 0x28cb
#define P23FS    	XBYTE[0x28cc]//P2.3����ѡ��Ĵ��� 0x28cc
#define P24FS    	XBYTE[0x28cd]//P2.4����ѡ��Ĵ��� 0x28cd
#define P25FS    	XBYTE[0x28ce]//P2.5����ѡ��Ĵ��� 0x28ce
#define Txd2FS    	XBYTE[0x28cf]//TXD2����ѡ��Ĵ��� 0x28cf

#define P7OE    	XBYTE[0x28d5]//P7���ʹ�ܼĴ��� 0x28d5
#define P7IE    	XBYTE[0x28d6]//P7����ʹ�ܼĴ��� 0x28d6
#define P7OD    	XBYTE[0x28d7]//P7������ݼĴ��� 0x28d7
#define P7ID    	XBYTE[0x28d8]//P7�������ݼĴ��� 0x28d8

#define P8OE    	XBYTE[0x28d9]//P8���ʹ�ܼĴ��� 0x28d9
#define P8IE    	XBYTE[0x28da]//P8����ʹ�ܼĴ��� 0x28da
#define P8OD    	XBYTE[0x28db]//P8������ݼĴ��� 0x28db 
#define P8ID    	XBYTE[0x28dc]//P8�������ݼĴ��� 0x28dc

/**�ɷ�Ƶʱ����� P9.7*/
#define PWMCLK1H   XBYTE[0x289c] //�ߵ�ƽ����ʱ����ֽ�
#define PWMCLK1L   XBYTE[0x289d]//�ߵ�ƽ����ʱ����ֽ�
#define PWMCLK2H   XBYTE[0X289E]//�͵�ƽ����ʱ����ֽ�
#define PWMCLK2L   XBYTE[0X289F]//�͵�ƽ����ʱ����ֽ�

/**ESAM */
#define DIVLA      XBYTE[0X2A01] //ESAM1 ��Ƶ��λ
#define DIVHA      XBYTE[0X2A02] //ESAM1 ��Ƶ��λ
#define DATAA    XBYTE[0X2A03] //esam1 ����
#define INFOA     XBYTE[0x2a04]  //ESAM1 ��Ϣ�Ĵ���
#define CFGA       XBYTE[0X2a05] //ESAM1 ���üĴ���
#define DIVLB      XBYTE[0X2b01] //ESAM2 ��Ƶ��λ
#define DIVHB      XBYTE[0X2b02] //ESAM2 ��Ƶ��λ
#define DATAB    XBYTE[0X2b03] //esam2 ����
#define INFOB     XBYTE[0x2b04]  //ESAM2 ��Ϣ�Ĵ���
#define CFGB       XBYTE[0X2b05] //ESAM2 ���üĴ���

/***********************************************
 PM ������صļĴ���
***********************************************/
//��д����Ĵ���
#define ACK     0X2885  
#define INVD   0x2884
#define BUFF3  0x2883
#define BUFF2  0x2882
#define BUFF1  0x2881
#define BUFF0  0x2880


//ԭʼ���μĴ���
#define DATAOIU  0x1005  //˲ʱ��ѹԭʼֵ
#define DATAOII1   0x100a //ͨ��I1˲ʱ����ԭʼֵ
#define DATAOII2   0X100F //ͨ��I2˲ʱ����ԭʼֵ
#define DATAIAU    0X1051  //˲ʱ��ѹ����ֵ
#define DATAIAI1   0x1052  //ͨ��I1˲ʱ����ֵ
#define DATAIAI2   0x1053  //ͨ��I2˲ʱ��������ֵ
#define DATAIDU   0x103a   //˲ʱ��ѹֱ��ֵ
#define DATAIDI1   0x1041  //ͨ��I1˲ʱ����ֱ��ֵ
#define DATAIDI2    0x1048 //ͨ��I2˲ʱ����ֱ��ֵ


//����/�������ݼĴ���
#define DATAIP    0x10d1
#define DATAIQ    0X10D2
#define RMSIU     0x10d3
#define RMSII1    0X10D4
#define RMSII2    0x10d5
#define DATAP     0X10D6
#define DATAQ     0x10d7
#define RMSU       0x10D8
#define  RMSI1    0x10d9
#define  RMSI2      0x10da
#define DATAAP1    0x10db
#define DATAAP2    0x10dc


//����/��Чֵ�Ȳ�Ĵ���

#define SCP  0x10e8
#define SCQ   0x10e9
#define SCU    0x10ea
#define SCI1    0x10eb
#define SCI2    0x10ec
#define PARAPC   0x10ed
#define PARAQC    0x10ee
#define PARABPF    0x10ef

#define PPCFCNT  0x10f2
#define GATEP   0x10f4
#define GATECP  0x10f5
#define GATEQ    0x10fa
#define GATECQ  0x10fb
#define DATACP   0x10fc


#define DATAFREQ  0x10fd


#define DATAOM 0x10ce
#define DATADM   0x10cf
#define DATAADM  0x10d0
//����Ͱ
#define PPCNT  0X10F0
#define NPCNT  0X10F1
#define PQCNT  0X10F6
#define NQCNT  0X10F7

#endif

