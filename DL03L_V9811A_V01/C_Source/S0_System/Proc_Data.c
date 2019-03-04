/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Proc_Data.c
**Author		: maji
**date			: 2016-04-20
**description	: 系统相关数据处理C文件
**note			: V9811A ，MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#include <MyIncludes_H.h>



SYS_RUN_STATUS  gs_sys_run;
SYS_GLOBAL_VAR gs_sys_globaL_var;




// 0 版本号 常数 定义 //
/*********************************************************************************************************
**  版本号 常数 定义
********************************************************************************************************/
const SYS_PARM code sys_parm={
      0x00,(uint8)METER_CONST_10WH_BCD,0x00,        //电表有功常数//
      'D','L','0','3','L','-','V','0','1','.','0','0',   //软件版本号DL03C-V01.02  //
};

/*********************************************************************************************************
**  电能表参数1 初始化默认数据
********************************************************************************************************/
const  E2P_METER_PARAM1_MAP  code   default_meter_parm1_tab = 
{
    15,1,       //  MD_PARAM                                md_param;
    1,0,        //BILL_MONTH_SETTLED_PARAM     bill_ms_param; 
    0,           //INT8U   EMU_fast_flg;    = 0X//EMU 加倍标识 //
    0X11,0X11,0X11,0X11,0X11,0XFF,0XFF,0XFF,//INT8U   meter_id[16];
    0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
    0,0,0,0,//INT8U   password[2][4];   //  2 级密码 //
    0,0,0,0,
    METER_FACTORY_MARK,0,0,0,//INT8U   fac_cfg[4];          //  工厂信息配置字//
    0,29,   //INT8U   bat_level[2];          //  电池电压阀值//  29=2.90v
    0,0,0,0,0,0,0,0,//INT8U   baoliu[32];       // //    
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
	  0,	   //各通道负荷记录指针(1个通道)  	2       BIN  XXXX    
    0,	    //各通道负荷记录条数		   	2       BIN  XXXX    
    15,		   //各通道记录时间间隔（min）  	2       BCD  XXXX 
    1,1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,   // 各寄存器代码(1+9)   			10      BCD  XXXX         第一个位个数   
    
    0,           //INT16U  param1_csck;    //16位累加和校验值//
};


/*****************************************************************************
** Function name    :Proc_sys_data_init
**
** Description         :系统数据模块的变量初始化
**
** Parameters         :NONE
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.00  MJ  2016-06-01
******************************************************************************/
void Proc_sys_data_init(void)
{
    gs_sys_run.back_fg = 0;
    gs_sys_run.font_fg = 0;
    gs_sys_globaL_var.delay_emu =3;   // EMU 温度时间映射 //
    mem_read(&gs_sys_globaL_var.meter_factory_status, ADR_METER_PARAM1_FC_CFG, 1, MEM_E2P1);   //数据0=0X5A 代表工厂状态 // 

}


/*****************************************************************************
** Function name    :Proc_clr_meter
**
** Description         :电表清零(除校表参数外的其他数据)   
**
** Parameters         :NONE
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.00  MJ  2016-06-01
******************************************************************************/
void Proc_clr_meter(void)
{
    //电表清零 //        
	CLRWDT();
	api_clr_current_energy_data();
	CLRWDT();
	api_clr_current_MD_data();
	CLRWDT();
	api_clr_bill_data();
	CLRWDT();
}


/***************************************************************
*    END
****************************************************************/

