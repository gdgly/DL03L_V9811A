/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Lnk_EMU_handl_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: V9811A的EMU计量模块链路层处理C代码的声明文件
**note			: V9811A ，MERTER FOR DL03C
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
*    1     立即数预定义   
****************************************************************/
//  //
#define VAL_CURRENT_ZERO   (C_Ib*2)             //电流为 3位小数，小于0.002Ib则清零 //
#define VAL_ACPOWER_ZERO   ((C_Ib*C_Un*10)/1000L)             //有功功率为0.1w量纲，小于0.001Ib*Un则清零 //





/***************************************************************
*    2     数据结构声明     
****************************************************************/
typedef struct 
{
    uint8   work_mode;  //EMU 工作模式//
    uint8   delay_emu;   // EMU 稳定时间，超过稳定时间后才可进行侧脸和计量 //
    uint8   net_flg;
} EMU_RUN_VAR;


/***************************************************************
*    3    变量声明       
****************************************************************/
extern EMU_RUN_VAR   gs_emu_run_var;


/***************************************************************
*    4     函数声明        
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
*    5     其他内容，例如伪指令等       
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

#define  REV_L_ACPOWER   BIT0    //±êê?A?à1|?ê·′?ò  //
#define  REV_N_ACPOWER   BIT1    //±êê?A?à1|?ê·′?ò  //
#define  REV_L_RACPOWER  BIT2    //?T1|1|?êA·′?ò //
#define  REV_N_RACPOWER  BIT3    //?T1|1|?êB·′?ò  //
#define  REV_TT_ACPOWER  BIT4    //óD1|o??à·′?ò//
#define  REV_TT_RACPOWER  BIT5    //?T1|o??à·′?ò//


/***************************************************************
*    END
****************************************************************/
#endif
