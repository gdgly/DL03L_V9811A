/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Lnk_EMU_handl_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: V9811A��EMU����ģ����·�㴦��C����������ļ�
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#ifndef _Lnk_EMU_handl_H
#define _Lnk_EMU_handl_H

/***************************************************************
*    1     ������Ԥ����   
****************************************************************/
//  //
#define VAL_CURRENT_ZERO   (C_Ib*2)             //����Ϊ 3λС����С��0.002Ib������ //
#define VAL_ACPOWER_ZERO   ((C_Ib*C_Un*10)/1000L)             //�й�����Ϊ0.1w���٣�С��0.001Ib*Un������ //





/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
typedef struct 
{
    uint8   work_mode;  //EMU ����ģʽ//
    uint8   delay_emu;   // EMU �ȶ�ʱ�䣬�����ȶ�ʱ���ſɽ��в����ͼ��� //
    uint8   net_flg;
} EMU_RUN_VAR;


/***************************************************************
*    3    ��������       
****************************************************************/
extern EMU_RUN_VAR   gs_emu_run_var;


/***************************************************************
*    4     ��������        
****************************************************************/
extern void Init_EMU_RAM(void);
extern void check_EMU_per_second(void);
extern void Init_EMU(uint8 u8_mode);
extern uint32 Lnk_get_EMU_voltage(uint8 ch);
extern uint32 Lnk_get_EMU_current(uint8 ch);
extern uint32 Lnk_get_EMU_activePower(uint8 ch);
extern uint32 Lnk_get_EMU_freq(uint8 ch);
extern uint8 lnk_CAL_EMU_constSum_per_second(uint8 *bypass_flg,uint8 work_mode);

/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/

/**************************ADC CHANNEL********************/
#define ADCAPDN   BIT0
#define ADCBPDN   BIT1
#define ADCUPDN   BIT2
#define ADCMPDN   BIT3
//open adc
#define ADCOPEN(Channel)  {CtrlADC6|=Channel;}
//close adc
#define ADCCLOSE(Channel) {CtrlADC6&=(~Channel);}
/***********************************************/
/***********************ADC PARA****************/
#define ADCA1X    	0
#define ADCA4X    	BIT0
#define ADCA8X    	BIT1
#define ADCA16X  	BIT0+BIT1
#define ADCA32X  	BIT0+BIT1+BIT2
#define ADCB1X    	0
#define ADCB4X    	BIT3
#define ADCB8X    	BIT4
#define ADCB16X  	BIT3+BIT4
#define ADCB32X  	BIT3+BIT4+BIT5
#define ADCU1X  	0
#define ADCU2X    	BIT6
#define ADCM1X    	0
#define ADCM2X    	BIT7


// gs_emu_run_var.ch define //
#define      EMU_CH_L   0
#define      EMU_CH_N   1
// gs_emu_run_var.net_flg define //

#define  REV_L_ACPOWER   BIT0    //������?A?��1|?������?��  //
#define  REV_N_ACPOWER   BIT1    //������?A?��1|?������?��  //
#define  REV_L_RACPOWER  BIT2    //?T1|1|?��A����?�� //
#define  REV_N_RACPOWER  BIT3    //?T1|1|?��B����?��  //
#define  REV_TT_ACPOWER  BIT4    //��D1|o??������?��//
#define  REV_TT_RACPOWER  BIT5    //?T1|o??������?��//


/***************************************************************
*    END
****************************************************************/
#endif
