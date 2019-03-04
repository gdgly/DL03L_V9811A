/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Prco_Data_H.H
**Author		: maji
**date			: 2016-04-26
**description	: 系统相关数据处理C文件
**note			: V9811A ，MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/



#ifndef _PROC_DATA_H
#define _PROC_DATA_H

/***************************************************************
*    1     立即数预定义   
****************************************************************/


/***************************************************************
*    2     数据结构声明     
****************************************************************/
typedef struct 
{	
	INT8U	back_fg;                     // 中断形成标识 //
	INT8U	font_fg;                     // 程序处理过程中产生标识 //
} SYS_RUN_STATUS;


typedef struct 
{	
    INT8U	 reset_status;                     // 系统复位标识字 //
    INT8U  work_mode;             // 系统电源标识 //
    INT8U  delay_emu;                    // EMU 稳定时间，初始化值=2， //
    INT8U  gs_check_err_status;   //校验状态字  //
    INT8U  gs_hard_err_status;   //硬件状态字//
    INT8U  gs_net_status;             //电网状态字//
    INT8U  meter_factory_status;     //电表工厂状态字=0x5A代表处在工厂状态//
} SYS_GLOBAL_VAR;

typedef struct  
{
     INT8U      meter_cons[3];           //电表常数//
     INT8U      video[12];               //软件版本号12个字节ASCII码//
}SYS_PARM;





typedef struct 
{
    MD_PARAM                                md_param;
    BILL_MONTH_SETTLED_PARAM     bill_ms_param; 
    INT8U   EMU_fast_flg;  //EMU 加倍标识=0x3c 为加倍，其他为正常 //
    INT8U   meter_id[16];
    INT8U   password[2][4];   //  2 级密码 //
    INT8U   fac_cfg[4];          //  工厂信息配置字//
    INT8U   bat_level[2];          //  电池电压阀值//
    INT8U   baoliu[32];
    
	  INT16U   load_Ptr_var;
    INT16U   load_Num_var;
    INT16U   load_lptime_inv_var;     //各通道记录时间间隔（Min）  	2       BCD  XXXX     
    INT8U    load_egcode_var[10];  // 各寄存器代码(1+9)   			10      BCD  XXXX         第一个位个数 
      
    INT16U  param1_csck;    //16位累加和校验值//
} E2P_METER_PARAM1_MAP;

typedef struct 
{
    RTC_TYPE  save_rtc;  //下电保存的时钟 //
    INT16U  var_csck;    //16位累加和校验值//
} E2P_METER_VAR_MAP;


/***************************************************************
*    3    变量声明       
****************************************************************/
extern SYS_RUN_STATUS  gs_sys_run;
extern SYS_GLOBAL_VAR gs_sys_globaL_var;

//常量表 //
extern const  E2P_METER_PARAM1_MAP  code   default_meter_parm1_tab;
extern const SYS_PARM code sys_parm;
/***************************************************************
*    4     函数声明        
****************************************************************/
extern void Proc_sys_data_init(void);
extern void Proc_clr_meter(void);

/***************************************************************
*    5     其他内容，例如伪指令等       
****************************************************************/
//  gs_sys_globaL_var.work_mode define 
#define      NORMAL_MODE                0    //市电供应状态 //
#define      DLX_MODE                       1    // 掉零线工作状态//
#define      CONST_MODE                   2   // 常数计量工作状态//   
#define      SLEEP_MODE                    3   // 低功耗休眠工作状态//   

//  gs_sys_globaL_var.meter_factory_status define 
#define  METER_FACTORY_MARK      0x5A     // =0X5A 代表处在工厂状态//

//  gs_sys_run.back_fg define 
#define  BIT0_FONT_FG_10MS   BIT0   // 10ms 中断产生标识 //
#define  BIT1_BACK_FG_RTC   BIT1   // RTC产生的1S中断标识 //
#define  BIT2_BACK_DIS_KEY   BIT2   // 显示按键产生的中断标识 //


/***************************************************************
*    END
****************************************************************/

#endif
