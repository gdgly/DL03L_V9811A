/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Lnk_EMU_Adj.c
**Author		: maji
**date			: 2016-04-20 
**description	: G80F92XD的EMU计量模块链路层校表处理C代码
**note			: MCU- G80F92XD ，MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-20   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>



ST_EMU_ADJ_PARAM  gs_adj_emu_param;
ST_EMU_ADJ_VAR      gs_emu_adj_var;


/*********************************************************************************************************
**  校表相关参数初始化默认数据
********************************************************************************************************/
const  ST_EMU_ADJ_PARAM  code   default_adj_emu_param_tab = 
{
    86243328,  //uint32 w1gain;   //通道1功率增益寄存器(有功无功使用同一组)  //
    7,  //uint32 p1cal;           //通道1电压电流相位补偿寄存器  //
    0,  //uint32 watt1os;      //通道1有功功率偏置  //
    0,  //uint32 irms1os;      //通道1电流有效值偏置  //
    3653512704,  //uint32 w2gain;         //通道2功率增益寄存器(有功无功使用同一组)  //
    7,  //uint32 p2cal;           //通道2电压电流相位补偿寄存器  //
    0,  //uint32 watt2os;      //通道2有功功率偏置  //
    0,  //uint32 irms2os;      //通道2电流有效值偏置  //
    0.1099405,  //uint32 vconst_val_ch1;   //通道1掉零线电压固定值 //    
    0.07784639,  //uint32 vconst_val_ch2;   //通道2掉零线电压固定值 //
    9.657958e-006,  //float vrms_xs;          //人为计算的电压有效值系数  //
    0.0001168467,  //float i1rms_xs;         //人为计算的通道1电流有效值系数  //
    8.279879e-005,  //float i2rms_xs;         //人为计算的通道2电流有效值系数  //
    0,  //uint16     csck;  //校验和 //
};

const  ST_Adjust_CONST  code   cst_adj_const = 
{
    C_Un*10,        //uint32 U_ref;       //参比电压值，量纲0.1V  // 
    2*C_Ib*1000,     //uint32 I_ref;       //参比电流值，量纲0.001A  //     
    INITGATEP,     //uint32 GATEP;    // 计量门限值 //
    INITGATECP,   //uint32 C_GATECP;   // 潜动门限值 //
    REF_RMSPn,    // uint32 C_PCONST;   // 额定功率的校准后标准值//
    K_RMSP,         //float   Kim_Prms;          //有功功率有效值系数//   
};


const  EMU_CK_TAB  code   cst_emu_selfchck_tab[] = 
{
    &gs_adj_emu_param.w1gain,            SCP,    //通道1功率增益寄存器(有功无功使用同一组)  //
    &gs_adj_emu_param.w2gain,            SCQ,    //通道2功率增益寄存器(有功无功使用同一组)  //
    &gs_adj_emu_param.p1cal,            PHCCtrl1,    //通道1电压电流相位补偿寄存器  //
    &gs_adj_emu_param.p2cal,            PHCCtrl2,    //通道2电压电流相位补偿寄存器  //
    &gs_adj_emu_param.watt1os,            PARAPC,    //通道1有功功率偏置  // 
    &gs_adj_emu_param.watt2os,            PARAQC,    //通道2有功功率偏置  //
};

const  EMU_CONST_CK_TAB  code   cst_emu_constchck_tab[] = 
{
    INITGATEP,            GATEP,    //uint32 GATEP;    // 计量门限值 //
    INITGATECP,          GATECP,    //uint32 C_GATECP;   // 潜动门限值 //
    0,                         SCU,     // U32  电压有效值比差校正值 //
    0,                         SCI1,     // U32  I1 电流有效值比差校正值//
    0,                         SCI2,     // U32  I2 电流有效值比差校正值//
};

/*********************************************************************************************************
** 函数名称: Save_EMU_AdjParam
** 功能描述: EMU相关参数修改后的保存更新处理
** 入口参数: 无
** 出口参数: 无
********************************************************************************************************/
void Save_EMU_AdjParam(void)
{
    gs_adj_emu_param.csck =Lib_get_csck_int16u_num((uint8 *)&gs_adj_emu_param,(LEN_BLOCK70_EMU_PARAM_E2P-2),CHECKWORD);
    mem_db_write(ADR_BLOCK70_EMU_PARAM_E2P, (uint8 *)&gs_adj_emu_param,(LEN_BLOCK70_EMU_PARAM_E2P-2),MEM_E2P1); 
}



/*********************************************************************************************************
** 函数名称: Save_EMU_AdjParam
** 功能描述: EMU相关参数修改后的保存更新处理
** 入口参数: 无
** 出口参数: 无
********************************************************************************************************/
void Get_EMU_AdjParam(void)
{
   uint16  csck_u16;
   
    Lib_Set_String((uint8 *)&gs_adj_emu_param,0,sizeof(gs_adj_emu_param));
    //RAM 数据检查  //
    csck_u16 =Lib_get_csck_int16u_num((uint8 *)&gs_adj_emu_param,(LEN_BLOCK70_EMU_PARAM_E2P-2),CHECKWORD);
    if(csck_u16 != gs_adj_emu_param.csck)
    {
        mem_read((uint8 *)&gs_adj_emu_param, ADR_BLOCK70_EMU_PARAM_E2P, LEN_BLOCK70_EMU_PARAM_E2P, MEM_E2P1);
    }
}


/*********************************************************************************************************
** 函数名称: Check_EMU_AdjParam
** 功能描述: EMU寄存器校验
** 入口参数: 无
** 出口参数: 无
********************************************************************************************************/
void Check_EMU_AdjParam(void)
{
   ST_U32_U08 regval;
   uint8 i;
   EMU_CK_TAB tmp_tab;
   EMU_CONST_CK_TAB  tmp_const_tab;

    // 检查RAM内的校表参数数据，如果校验不正确则从EEPROM内获取 //
    Get_EMU_AdjParam();   

    // 固定值配置的校表相关数据检查 //    
    for(i=0;i<(dim(cst_emu_constchck_tab));i++)
    {
        tmp_const_tab.emuAdr = cst_emu_constchck_tab[i].emuAdr;
        tmp_const_tab.val = cst_emu_constchck_tab[i].val;
        regval.u32 = 0;
        regval.u32 = ReadMeterParaACK(tmp_const_tab.emuAdr);     //计量门限值检查  //
        if(regval.u32 != tmp_const_tab.val)
        {
            regval.u32 = tmp_const_tab.val;
            SetMeterCfgACK(regval.u32,tmp_const_tab.emuAdr);
        }  
    }

    // 读取存储芯片内的校表数据进行检查 //
    for(i=0;i<(dim(cst_emu_selfchck_tab));i++)
    {
        tmp_tab.emuAdr = cst_emu_selfchck_tab[i].emuAdr;
        tmp_tab.ramAdr = cst_emu_selfchck_tab[i].ramAdr;
        regval.u32 = 0;
        regval.u32= ReadMeterParaACK(tmp_tab.emuAdr);
        if((tmp_tab.emuAdr==PHCCtrl1) ||(tmp_tab.emuAdr==PHCCtrl2))
        {
            if(regval.B08[3] != (uint8)(*tmp_tab.ramAdr))
            {
                regval.u32 = (uint8)(*tmp_tab.ramAdr);
                SetMeterCfgACK(regval.u32,tmp_tab.emuAdr);
            }      
        }
        else
        {
            if(regval.u32 != *tmp_tab.ramAdr)
            {
                regval.u32 = *tmp_tab.ramAdr;
                SetMeterCfgACK(regval.u32,tmp_tab.emuAdr);
            }
        }    
    }


    
}

/*********************************************************************************************************
** 函数名称: Get_Original_Power
** 功能描述: 获取原始功率值
** 入口参数: avr_times-平均次数 
** 出口参数: 无		
********************************************************************************************************/
uint32 Get_Original_Power(uint8 avr_times,uint8 ch)
{
    uint32 val;
    uint8  i;
    uint32 aery_old;
    uint32 aery_val;
    uint32 avr_aery;

    CLRWDT();

    avr_aery=0;
    gs_emu_adj_var.sec_flg=FALSE; 
    for (i=0;i<avr_times;i++)
    {
        CLRWDT();
        while(gs_emu_adj_var.sec_flg==FALSE);
        gs_emu_adj_var.sec_flg=FALSE; 
        CLRWDT(); 
        if(ch==EMU_CH_L)
        {
            val=ReadMeterParaACK(DATAIP);	 
        }
        else
        {
            val=ReadMeterParaACK(DATAIQ);	   
        }

       if(val>=0x80000000)
       {
          val=~val+1;  
       }

       aery_old=val;
       avr_aery=avr_aery+aery_old;
    }   

    aery_val=avr_aery/avr_times;
    CLRWDT();
    NOP();
    return(aery_val);
}	 	



/*********************************************************************************************************
** 函数名称: Get_Original_Irms
** 功能描述: 获取原始电流有效值数据
** 入口参数: avr_times-平均次数 
** 出口参数: 无		
********************************************************************************************************/
uint32 Get_Original_Irms(uint8 avr_times,uint8 ch)
{
    uint32 val;
    uint8  i;
    uint32 aery_old;
    uint32 aery_val;
    uint32 avr_aery;

    CLRWDT();

    avr_aery=0;
    gs_emu_adj_var.sec_flg=FALSE; 
    for (i=0;i<avr_times;i++)
    {
        CLRWDT();
        while(gs_emu_adj_var.sec_flg==FALSE);
        gs_emu_adj_var.sec_flg=FALSE; 
        CLRWDT(); 
        if(ch==EMU_CH_L)
        {
            val=ReadMeterParaACK(RMSII1);	 
        }
        else
        {
            val=ReadMeterParaACK(RMSII2);	   
        }

       if(val>=0x80000000)
       {
          val=~val+1;  
       }

       aery_old=val;
       avr_aery=avr_aery+aery_old;
    }   

    aery_val=avr_aery/avr_times;
    CLRWDT();
    NOP();
    return(aery_val);
}	 


/*=========================================================================================\n
* @function_name: CalculateSC
* @function_file: EnergyBottom.c
* @描述: 比差计算公式
* 
* 
* @参数: 
* @param:CurValue  :电表有功功率值
* @param:TarValue  :标准表有功功率值
* 
* @返回: 
* @return: uint32 
* @作者:   lwb (2012-03-08)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
INT32U CalculateSC(INT32U CurValue,INT32U TarValue)
{
    //  2016-5-20  mj //                
    INT32S s32_tmp0;
    double f_CurValue,f_TarValue,f_Error;
    double f_s32_tmp0,f_s32_tmp1,f_s32_tmp2,f_s32_tmp3;

    // 获取当前误差  ((CurValue-TarValue)/TarValue )*100% //    
    f_CurValue = (double)CurValue;
    f_TarValue = (double)TarValue;
    f_Error = (f_CurValue-TarValue)*1.0/f_TarValue;

	f_s32_tmp0 = 1.0/(1+f_Error);

	f_s32_tmp1 = f_s32_tmp0 - 1.0;
	
	f_s32_tmp2 = f_s32_tmp1* 0x80000000;
	
	f_s32_tmp3 = floor(f_s32_tmp2);     // 向下取整 //
	s32_tmp0 = (INT32S)f_s32_tmp3;	
	return (s32_tmp0);
}

/*=========================================================================================\n
* @function_name: CalculateAC
* @function_file: EnergyBottom.c
* @描述: 角差计算公式
* 
* 
* @参数: 
* @param:CurValue   ：电表功率 
* @param:TarValue   ：标准表功率
* 
* @返回: 
* @return: uint8    
* @作者:   lwb (2012-06-18)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
INT8U CalculateAC(INT32U CurValue,INT32U TarValue)
{
    //计算公式更换,雷文斌，2011年7月14日//
    INT16U Error;                    
    INT8U Result;
	INT8U JCFH;
	
	JCFH = 0;
	if(TarValue < 50)   return 0;
	
	if(TarValue>CurValue)  
	{
		// 负误差 //
		Error=(TarValue-CurValue)*1000/TarValue;            //计算误差值。。扩大1000
		JCFH = 1;
	}
	else
	{
		// 正误差 //
		Error=(CurValue-TarValue)*1000/TarValue;            //计算误差值。。扩大1000
	}
    Result = (INT32U)3011*Error/2000;
	if(JCFH==1)
	{
		Result|=BIT7;
	}
    return Result; 
}

/*********************************************************************************************************
** 函数名称: SoftAdjust_IB_Process
** 功能描述: 校准大功率
** 入口参数: jzval：理论功率值：脉冲常数/3600*表台输出功率/1000*ICONT*8388608 如：1200/3600/220*10/1000*96*8388608=576716
**           channel: 电流通道 0-通道1 1-通道2       
** 出口参数: 无	
********************************************************************************************************/
void SoftAdjust_IB_Process(uint32 jzval,uint8 channel)
{
   uint32 val;
   uint32 adjust_wcval;

    CLRWDT();
    if(channel==EMU_CH_L)
    {
        val=0;
        SetMeterCfgACK(val,SCP);  //校正功率增益
        SetMeterCfgACK(val,PARAPC);   
    }
    else
    {
        val=0;
        SetMeterCfgACK(val,SCQ);  //校正功率增益
        SetMeterCfgACK(val,PARAQC);   
    }
   adjust_wcval=Get_Original_Power(2,channel); 
   val = CalculateSC(adjust_wcval,jzval);
   
    CLRWDT(); 
    if(channel==EMU_CH_L)
    {
        gs_adj_emu_param.w1gain=val;      
    }
    else
    {
        gs_adj_emu_param.w2gain=val;      
    }
    Save_EMU_AdjParam();
    Check_EMU_AdjParam();
    CLRWDT();
}	

/*********************************************************************************************************
** 函数名称: SoftAdjust_IB5_Process
** 功能描述: 校准小功率
** 入口参数: jzval：理论功率值 脉冲常数/3600*表台输出功率/1000*ICONT*8388608 如：1200/3600/220*0.5/1000*96*8388608=28835
**           channle:电流通道号 0-通道1  1-通道2
** 出口参数: 无	
********************************************************************************************************/
void SoftAdjust_IB5_Process(uint32 jzval,uint8 channel)
{
   bit Flag_fu=0;   //负号标志	

   uint32 val;		 
   uint32 adjust_wcval;
              

    CLRWDT();
    val=0;
    if(channel==EMU_CH_L)
    {
        SetMeterCfgACK(val,PARAPC);   
    }
    else
    {
        SetMeterCfgACK(val,PARAQC);   
    }
   adjust_wcval=Get_Original_Power(3,channel); 
   val = CalculateAC(adjust_wcval,jzval);

    CLRWDT(); 
    if(channel==EMU_CH_L)
    {
        gs_adj_emu_param.watt1os=val;      
    }
    else
    {
        gs_adj_emu_param.watt2os=val;      
    }
    Save_EMU_AdjParam();
    Check_EMU_AdjParam();
    CLRWDT();

}
			
/*********************************************************************************************************
** 函数名称: SoftAdjust_Phase_Process
** 功能描述: 功率校准相位
** 入口参数: jzval：理论功率值 脉冲常数/3600*表台输出功率/1000*ICONT*8388608 如：1200/3600/220*5/1000*96*8388608=288358
**           channel：通道号
** 出口参数: 无	
********************************************************************************************************/
void SoftAdjust_Phase_Process(uint32 jzval,uint8 channel)
{   
   uint32 val;		 
   uint32 adjust_wcval;
              

    CLRWDT();
    val=0;
    if(channel==EMU_CH_L)
    {
        SetMeterCfgACK(val,PHCCtrl1);   
    }
    else
    {
        SetMeterCfgACK(val,PHCCtrl2);   
    }
    CLRWDT();

    gs_emu_adj_var.sec_flg=FALSE;
    while(gs_emu_adj_var.sec_flg==FALSE);              //延时1秒 等待功率稳定
    gs_emu_adj_var.sec_flg=FALSE; 

   adjust_wcval=Get_Original_Power(2,channel); 
   val = CalculateAC(adjust_wcval,jzval);
   
    CLRWDT(); 
    if(channel==EMU_CH_L)
    {
        gs_adj_emu_param.p1cal=val;      
    }
    else
    {
        gs_adj_emu_param.p2cal=val;      
    }
    Save_EMU_AdjParam();
    Check_EMU_AdjParam();
    CLRWDT();

}
      
/*********************************************************************************************************
** 函数名称: SoftAdjust_dlxProcess	
** 功能描述: 校准调零线校准
** 入口参数: jzval：理论功率值 脉冲常数/3600*表台输出功率/1000*ICONT*8388608 如：1200/3600/220*5/1000*96*8388608=288358
**           channel：通道号
** 出口参数: 无	
********************************************************************************************************/
void SoftAdjust_dlxProcess(uint32 jzval,uint8 channel)
{
    uint32 xdata adjust_wcval;

    CLRWDT();
    Init_EMU(DLX_MODE);
    gs_emu_adj_var.sec_flg=FALSE;
    while(gs_emu_adj_var.sec_flg==FALSE);              //延时1秒 等待功率稳定
    gs_emu_adj_var.sec_flg=FALSE; 
    CLRWDT();

    gs_emu_adj_var.sec_flg=FALSE;
    while(gs_emu_adj_var.sec_flg==FALSE);              //延时1秒 等待功率稳定
    gs_emu_adj_var.sec_flg=FALSE;    
    CLRWDT();

    if(channel==EMU_CH_L)
    {
        //Dis_Adjust(7);		
        adjust_wcval=Get_Original_Irms(3,EMU_CH_L);		//读取A通道实际 电流有效值数据 //
       gs_adj_emu_param.vconst_val_ch1 =((float) jzval)/((float) adjust_wcval);   //获取A通道的常数计量系数 //
    }
    else
    {
        //Dis_Adjust(8);
        adjust_wcval=Get_Original_Irms(3,EMU_CH_N);   //读取B通道实际 电流有效值数据 //
        gs_adj_emu_param.vconst_val_ch2 =((float) jzval)/((float) adjust_wcval);   //获取B通道的常数计量系数 //
    }

    CLRWDT();
    Init_EMU(NORMAL_MODE);
    Save_EMU_AdjParam();
    Check_EMU_AdjParam();
    NOP();
    NOP();
}

/*********************************************************************************************************
** 函数名称: Hardware_AdjustDiv_Sub
** 功能描述: 硬件短接 校准步骤判断
** 入口参数: 无
** 出口参数: 无
********************************************************************************************************/
void Hardware_AdjustDiv_Sub(void)
{
   uint8 i;
    uint32 val;
   uint32 tmpval;
   uint32 tmpval1=0;	 
   uint32 jzwcval;
	uint8 ajust_type;
   uint32 cmp_val[4];
   uint32 adjust_wcval;

    if(EA==0)  return;

    //  准备阶段  ，获取功率值，判断进行哪一步的校表//
    gs_emu_adj_var.adj_flg =0x55;   // =0X55 标识目前进入校表状态 //
    //Dis_Adjust(99);   //准备阶段 

    jzwcval=cst_adj_const.C_PCONST;     // 额定功率点的功率校准定点数据//
    cmp_val[0]=jzwcval*25/10;         //250% IB 基本校表点参数采用默认值初始化 //
    cmp_val[1]=jzwcval*70/100;       // 基本点校准 //
    cmp_val[2]=jzwcval*35/100;       // 角差校准 //
    cmp_val[3]=jzwcval*3/100;         // 小信号校准 //

    CLRWDT(); 	 	 
    adjust_wcval=Get_Original_Power(4,EMU_CH_L);	 //读取实际功率
#if((_METER_TYPE_CFG ==_METER_TYPE_1P2W_1) || (_METER_TYPE_CFG ==_METER_TYPE_1P2W_2)||(_METER_TYPE_CFG ==_METER_TYPE_1P3W_11)  ) 
    if(adjust_wcval>cmp_val[0])
    {
        ajust_type=HARD_EADJ_STEP0_L_INITLIZE;//IB 1.0 ch0;
    }
    else if(adjust_wcval>cmp_val[1])
    {
        ajust_type=HARD_EADJ_STEP1_L_100IB_100L;//IB 1.0 ch0;
    }
    else if(adjust_wcval>cmp_val[2])
    {
        ajust_type=HARD_EADJ_STEP2_L_100IB_50L;//IB 0.5 ch0;   
    }   
    else if(adjust_wcval>cmp_val[3])
    {
        ajust_type=HARD_EADJ_STEP3_L_5IB_100L;//5%IB 1.0 ch0;   
    }
    else
    {
        adjust_wcval=Get_Original_Power(4,EMU_CH_N);	 //读取实际功率
        if(adjust_wcval>cmp_val[0])
        {
            ajust_type=HARD_EADJ_STEP4_N_INITLIZE;//IB 1.0 ch0;
        }
        else if(adjust_wcval>cmp_val[1])
        {
            ajust_type=HARD_EADJ_STEP5_N_100IB_100L;//IB 1.0 ch1;
        }
        else if(adjust_wcval>cmp_val[2])
        {
            ajust_type=HARD_EADJ_STEP6_N_100IB_50L;//IB 0.5 ch1;     
        }   
        else if(adjust_wcval>cmp_val[3])
        {
            ajust_type=HARD_EADJ_STEP7_N_5IB_100L;//5%IB 1.0 ch1;   
        }
        else
        {
            ajust_type=HARD_EADJ_STEP8_METER_CLR;// 电表清零  //   
        }
    }
#endif

#if((_METER_TYPE_CFG ==_METER_TYPE_1P2W_0)  ) 
    if(adjust_wcval>cmp_val[0])
    {
        ajust_type=HARD_EADJ_STEP0_L_INITLIZE;//IB 1.0 ch0;
    }
    else if(adjust_wcval>cmp_val[1])
    {
        ajust_type=HARD_EADJ_STEP1_L_100IB_100L;//IB 1.0 ch0;
    }
    else if(adjust_wcval>cmp_val[2])
    {
        ajust_type=HARD_EADJ_STEP2_L_100IB_50L;//IB 0.5 ch0;   
    }   
    else if(adjust_wcval>cmp_val[3])
    {
        ajust_type=HARD_EADJ_STEP3_L_5IB_100L;//5%IB 1.0 ch0;   
    }
    else
    {
    	 ajust_type=HARD_EADJ_STEP8_METER_CLR;// 电表清零  //   
    }
#endif

    //   分步骤校准处理   //
    //  HARD_EADJ_STEP0_L_INITLIZE   L回路比差寄存器初始化//
    if(ajust_type==HARD_EADJ_STEP0_L_INITLIZE)
    {                      
        gs_adj_emu_param.w1gain = 0;   //初始化L1通道比差寄存器  //
        Save_EMU_AdjParam();
        Check_EMU_AdjParam();
        CLRWDT();
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_0);   // 液晶显示 //
    }

    //  HARD_EADJ_STEP1_L_100IB_100L   L回路100%Ib, 1.0L 校准//
    if(ajust_type==HARD_EADJ_STEP1_L_100IB_100L)
    {                      
        //Dis_Adjust(1);  
        // L回路有功增益校准 // 
        SoftAdjust_IB_Process(jzwcval,EMU_CH_L); 

        // L回路电流有效值增益校准 //  	
        tmpval=0;
        for(i=0;i<8;i++)
        {
            Lib_Delay_ms(30);
            val = ReadMeterParaACK(RMSII1);
            if(val>=0x80000000)
            {
                val=~val+1;  
            } 		  		
            tmpval=tmpval+val;
            CLRWDT();          
        }
        tmpval=tmpval/8;
        //电流有效值的位数在此处决定，取决于cst_adj_const.I_ref和基本电流整数的倍数//
        gs_adj_emu_param.i1rms_xs=(float)cst_adj_const.I_ref/(float)tmpval;  
        //电压有效值增益校准 //             		
        tmpval=0;
        for(i=0;i<8;i++)
        {
            Lib_Delay_ms(30);
            val = ReadMeterParaACK(RMSIU);
            if(val>=0x80000000)
            {
                val=~val+1;  
            } 		  		
            tmpval=tmpval+val;
            CLRWDT();        
        }
        tmpval=tmpval/8;      
        //电压有效值的位数在此处决定，取决于cst_adj_const.U_ref和基本电压整数的倍数//
        gs_adj_emu_param.vrms_xs=(float)cst_adj_const.U_ref/(float)tmpval;  

#if( (_METER_TYPE_CFG ==_METER_TYPE_1P2W_2) ) 
        // L回路掉零线电压常量校准//  
        CLRWDT();            
        //Dis_Adjust(99);   //准备阶段    
        SoftAdjust_dlxProcess(jzwcval,EMU_CH_L);
#endif

        Save_EMU_AdjParam();
        Check_EMU_AdjParam();
        CLRWDT();
		
	  api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_1);   // 液晶显示 //
    }

    //  HARD_EADJ_STEP2_L_100IB_50L   L回路100%Ib, 0.5L 校准//
    if(ajust_type==HARD_EADJ_STEP2_L_100IB_50L)
    {                            
        //Dis_Adjust(2);
        jzwcval=jzwcval/2;
        SoftAdjust_Phase_Process(jzwcval,EMU_CH_L);  
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_2);   // 液晶显示 //
    }
    //  HARD_EADJ_STEP3_L_5IB_100L   L回路5%Ib, 1.0L 校准//
    if(ajust_type==HARD_EADJ_STEP3_L_5IB_100L)
    {                            
        //Dis_Adjust(3);
        jzwcval=jzwcval/20;
        SoftAdjust_IB5_Process(jzwcval,EMU_CH_L);   
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_3);   // 液晶显示 //   
    }

#if((_METER_TYPE_CFG ==_METER_TYPE_1P2W_1) || (_METER_TYPE_CFG ==_METER_TYPE_1P2W_2)||(_METER_TYPE_CFG ==_METER_TYPE_1P3W_11)  ) 
    //  HARD_EADJ_STEP4_N_INITLIZE   N回路比差寄存器初始化//
    if(ajust_type==HARD_EADJ_STEP4_N_INITLIZE)
    {                      
        gs_adj_emu_param.w2gain = 0;   //初始化L1通道比差寄存器  //
        Save_EMU_AdjParam();
        Check_EMU_AdjParam();
        CLRWDT();
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_0);   // 液晶显示 //
    }

    //  HARD_EADJ_STEP4_N_100IB_100L   N回路100%Ib, 1.0L 校准//
    if(ajust_type==HARD_EADJ_STEP5_N_100IB_100L)
    {              
        //Dis_Adjust(1);  
        // L回路有功增益校准 // 
        SoftAdjust_IB_Process(jzwcval,EMU_CH_N); 

        // L回路电流有效值增益校准 //  	
        tmpval=0;
        for(i=0;i<8;i++)
        {
            Lib_Delay_ms(30);
            val = ReadMeterParaACK(RMSII2);
            if(val>=0x80000000)
            {
                val=~val+1;  
            } 		  		
            tmpval=tmpval+val;
            CLRWDT();          
        }
        tmpval=tmpval/8;
        //电流有效值的位数在此处决定，取决于cst_adj_const.I_ref和基本电流整数的倍数//
        gs_adj_emu_param.i2rms_xs=(float)cst_adj_const.I_ref/(float)tmpval;  

#if( (_METER_TYPE_CFG ==_METER_TYPE_1P2W_2) ) 
        // N回路掉零线电压常量校准//  
        CLRWDT();            
        //Dis_Adjust(99);   //准备阶段    
        SoftAdjust_dlxProcess(jzwcval,EMU_CH_N);
#endif

        Save_EMU_AdjParam();
        Check_EMU_AdjParam();
        CLRWDT();
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_1);   // 液晶显示 //		
    }

    //  HARD_EADJ_STEP6_N_100IB_50L   N回路100%Ib, 0.5L 校准//
    if(ajust_type==HARD_EADJ_STEP6_N_100IB_50L)
    {                      
        //Dis_Adjust(5);
        jzwcval=jzwcval/2;
        SoftAdjust_Phase_Process(jzwcval,EMU_CH_N);  
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_2);   // 液晶显示 //
    }    
    //  HARD_EADJ_STEP7_N_5IB_100L   N回路5%Ib, 1.0L 校准//
    if(ajust_type==HARD_EADJ_STEP7_N_5IB_100L)
    {                         
        //Dis_Adjust(6);
        jzwcval=jzwcval/20;
        SoftAdjust_IB5_Process(jzwcval,EMU_CH_N);   
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_3);   // 液晶显示 //   
    }
#endif

    if(ajust_type==HARD_EADJ_STEP8_METER_CLR)
    {        
        Proc_clr_meter();
        api_chg_LCDDisplay_adj_item(DIS_DATA_CLR);   // 液晶显示 //
    }

    gs_emu_adj_var.adj_flg =0;   // =0X0 标识目前退出校表状态 //	

}


/*******************************************************************************************
**    END
*******************************************************************************************/


