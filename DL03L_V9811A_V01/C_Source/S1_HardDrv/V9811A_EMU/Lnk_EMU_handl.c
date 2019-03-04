/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Lnk_EMU_handl.c
**Author		: maji
**date			: 2016-04-20 
**description	: V9811A的EMU计量模块链路层处理C代码
**note			: V9811A ，MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>




EMU_RUN_VAR   gs_emu_run_var;

/*********************************************************************************************************
** 函数名称: Init_EMU
** 功能描述: 初始化EMU
** 入口参数: 无
** 出口参数: 无
********************************************************************************************************/
void Init_EMU_RAM(void)
{
    Get_EMU_AdjParam();
}


/*********************************************************************************************************
** 函数名称: EMU_Verify
** 功能描述: EMU寄存器校验
** 入口参数: 无
** 出口参数: 无
********************************************************************************************************/
void check_EMU_per_second(void)
{
   ST_U32_U08 regval;

    // ADC 配置检查  //
    if(gs_sys_globaL_var.work_mode==NORMAL_MODE)
    {
        if((CtrlADC6&(ADCAPDN+ADCBPDN+ADCUPDN)) != (ADCAPDN+ADCBPDN+ADCUPDN))
        {
            ADCOPEN(ADCAPDN+ADCBPDN+ADCUPDN);//OPEN ADC U A B
            SetMeterCfgACK(0X889374BC,PARABPF);    // 手册要求 //
        }
    }
    if((gs_sys_globaL_var.work_mode ==DLX_MODE)||(gs_sys_globaL_var.work_mode ==CONST_MODE))
    {
        if((CtrlADC6&(ADCAPDN+ADCBPDN+ADCUPDN)) != (ADCAPDN+ADCBPDN))
        {
            ADCOPEN(ADCAPDN+ADCBPDN);//OPEN ADC  A B
            SetMeterCfgACK(0X911D3C9C,PARABPF);    // 手册要求 // 
        }
    }

    if((CtrlADC0&(ADCA16X+ADCB4X+ADCU2X)) != (ADCA16X+ADCB4X+ADCU2X))
    {
        CtrlADC0=(ADCA16X+ADCB4X+ADCU2X); //ADC A 16X GAIN  ADC B 4x GAIN ADC U 4X GAIN	
    }

   // PMCtrl x 检查   //
    regval.u32 = 0;
    regval.u32 = ReadMeterParaACK(PMCtrl1);
    if((regval.u32&0x000000ff) != 0x57)
    {
        SetMeterCfgACK(0x57,PMCtrl1);
    }

    regval.u32 = 0;
    regval.u32 = ReadMeterParaACK(PMCtrl2);
    if((regval.u32&0x000000ff) != 0x00)
    {
        SetMeterCfgACK(0x00,PMCtrl2);
    }

    regval.u32 = 0;
    regval.u32 = ReadMeterParaACK(PMCtrl3);
    if((regval.u32&0x000000ff) != 0x70)
    {
        SetMeterCfgACK(0x70,PMCtrl3);
    }

    regval.u32 = 0;
    regval.u32 = ReadMeterParaACK(PMCtrl4);
    if((regval.u32&0x000000ff) != 0xDA)
    {
        SetMeterCfgACK(0xDA,PMCtrl4);
    }

    //EMU计量类参数检查处理  //
    Check_EMU_AdjParam();
}


/*********************************************************************************************************
** 函数名称: Init_EMU
** 功能描述: 初始化EMU
** 入口参数: 无
** 出口参数: 无
********************************************************************************************************/
void Init_EMU(uint8 u8_mode)
{
    if(u8_mode==SLEEP_MODE)
    {
        CtrlADC5=0X80;     //关闭M通道 //
        CtrlADC6=0;         //关闭所有AD采样 //  
        PMG=1;              //关闭计量时钟  //
        return;
    }

    PMG=0;              //打开计量时钟  //
    //step1  //
    SetMeterCfgACK(0x00,PMCtrl4);   //关闭能量累加、CF 输出以及起动/潜动判断电路 //
    SetMeterCfgACK(0x00,PMCtrl1);   // 关闭计量通道，并停止功率/有效值计算  //
    // step2  //
    CtrlADC5=0X80;   
    CtrlADC6=0;   
    if(u8_mode==NORMAL_MODE)
    {
        Set_EmuClock(EMUCLK_3M2);          // 3.2M 计量主频 //
        ADCOPEN(ADCAPDN+ADCBPDN+ADCUPDN);//OPEN ADC U A B
        SetMeterCfgACK(0X889374BC,PARABPF);    // 手册要求 //
    }
    else if((u8_mode ==DLX_MODE)||(u8_mode ==CONST_MODE))
    {
        Set_EmuClock(EMUCLK_800k);       // 800K计量主频 //
        ADCOPEN(ADCAPDN+ADCBPDN);//OPEN ADC  A B
        SetMeterCfgACK(0X911D3C9C,PARABPF);    // 手册要求 // 
    }
    else
    {
        sys_err();          // 输入参数异常，死循环退出 //
    }
    CtrlADC0=(ADCA16X+ADCB4X+ADCU2X); //ADC A 4X GAIN  ADC B 4x GAIN ADC U 1X GAIN	

    // step3  //   
    SetMeterCfgACK(INITGATEP,GATEP);//设置计量初始值
    SetMeterCfgACK(INITGATEQ,GATEQ);

    // step4 // 
    SetMeterCfgACK(0,0x10f0);    //0x10f0  PPCNT  正向 E1 能量累加寄存器  //
    SetMeterCfgACK(0,0x10f1);    //0x10f1  NPCNT  反向 E1 能量累加寄存器 //
    SetMeterCfgACK(0,0x10f2);    //0x10f2  PPCFCNT  正向 E1 能量脉冲计数器   //
    SetMeterCfgACK(0,0x10f3);   //0x10f3  NPCFCNT  反向 E1 能量脉冲计数器   //
    SetMeterCfgACK(0,0x10f6);   //0x10f6  PQCNT  正向 E2 能量累加寄存器//
    SetMeterCfgACK(0,0x10f7);   //0x10f7  NQCNT  反向 E2 能量累加寄存器   //
    SetMeterCfgACK(0,0x10f8);   //0x10f8  PQCFCNT   正向 E2 能量脉冲计数器  //
    SetMeterCfgACK(0,0x10f9);   //0x10f9 NQCFCNT   反向 E2 能量脉冲计数器  //
    // step5// 
    SetMeterCfgACK(0xC8,PMCtrl4);		//  ?????  //
    SetMeterCfgACK(0x08,PMCtrl4);
    SetMeterCfgACK(0x00,PMCtrl4);
    // step6 // 
    SetMeterCfgACK(0,0x10f0);    //0x10f0  PPCNT  正向 E1 能量累加寄存器  //
    SetMeterCfgACK(0,0x10f1);    //0x10f1  NPCNT  反向 E1 能量累加寄存器 //
    SetMeterCfgACK(0,0x10f2);    //0x10f2  PPCFCNT  正向 E1 能量脉冲计数器   //
    SetMeterCfgACK(0,0x10f3);   //0x10f3  NPCFCNT  反向 E1 能量脉冲计数器   //
    SetMeterCfgACK(0,0x10f6);   //0x10f6  PQCNT  正向 E2 能量累加寄存器//
    SetMeterCfgACK(0,0x10f7);   //0x10f7  NQCNT  反向 E2 能量累加寄存器   //
    SetMeterCfgACK(0,0x10f8);   //0x10f8  PQCFCNT   正向 E2 能量脉冲计数器  //
    SetMeterCfgACK(0,0x10f9);   //0x10f9 NQCFCNT   反向 E2 能量脉冲计数器  //
    // step7// 
    SetMeterCfgACK(0x01,GATECP);//潜动1   ,=1会禁止脉冲发出    //
    SetMeterCfgACK(0x01,GATECQ);//潜动2   ,=1会禁止脉冲发出  //
    SetMeterCfgACK(0x00,DATACP);//清常数功率寄存器 //

    // step8// 
    SetMeterCfgACK(0x57,PMCtrl1);//BIT7= 0  测试位确保为0  ; BIT6=1 使能角差校正  //
                                                  //BIT5= 0  IA--I1,IB--I2 ; BIT4=1 使能PM数字信号处理  //
                                                  //BIT3= 0  屏蔽M通道数字信号输入; BIT2=1 使能I2数字信号输入使能  //
                                                  //BIT1= 1   使能I1数字信号输入使能; BIT0=1 使能U数字信号输入使能  //
    SetMeterCfgACK(0x00,PMCtrl2);// 数字增益类的参数寄存器，要求为0  //

    SetMeterCfgACK(0x70,PMCtrl3);//开启两路有功,带通和低通滤波器有效 //
    SetMeterCfgACK(0xD2,PMCtrl4);//BIT7= 1  E2 计量通道起动/潜动判断使能  ; BIT6=1  E2 计量通道起动/潜动判断使能  //
                                                  //BIT5= 0 E2 能量 CF 脉冲输出关闭; BIT4=1 使能E1 能量 CF 脉冲输出 //
                                                  //BIT3= 0 禁止能量累加和能量脉冲计数; BIT2=0  E1 能量 CF 脉冲从引脚 CF1 输出，E2 能量 CF 脉冲从引脚 CF2 输出  //
                                                  //BIT1:0= 10 常数功率 //
    SetMeterCfgACK(0,0x10f0);    //0x10f0  PPCNT  正向 E1 能量累加寄存器  //
    SetMeterCfgACK(0,0x10f1);    //0x10f1  NPCNT  反向 E1 能量累加寄存器 //
    SetMeterCfgACK(0,0x10f2);    //0x10f2  PPCFCNT  正向 E1 能量脉冲计数器   //
    SetMeterCfgACK(0,0x10f3);   //0x10f3  NPCFCNT  反向 E1 能量脉冲计数器   //
    SetMeterCfgACK(0,0x10f6);   //0x10f6  PQCNT  正向 E2 能量累加寄存器//
    SetMeterCfgACK(0,0x10f7);   //0x10f7  NQCNT  反向 E2 能量累加寄存器   //
    SetMeterCfgACK(0,0x10f8);   //0x10f8  PQCFCNT   正向 E2 能量脉冲计数器  //
    SetMeterCfgACK(0,0x10f9);   //0x10f9 NQCFCNT   反向 E2 能量脉冲计数器  //
    // step9 // 
    SetMeterCfgACK(0xDA,PMCtrl4);//BIT7= 1  E2 计量通道起动/潜动判断使能  ; BIT6=1  E2 计量通道起动/潜动判断使能  //
                                                  //BIT5= 0 E2 能量 CF 脉冲输出关闭; BIT4=1 使能E1 能量 CF 脉冲输出 //
                                                  //BIT3= 1 使能能量累加和能量脉冲计数; BIT2=0  E1 能量 CF 脉冲从引脚 CF1 输出，E2 能量 CF 脉冲从引脚 CF2 输出  //
                                                  //BIT1:0= 10 常数功率 //
     // step10 // 
    SetMeterCfgACK(0,PHCCtrl1);//清0
    SetMeterCfgACK(0,PHCCtrl2);//清0

    SetMeterCfgACK(0x01,CFCtrl);           //以E1正相能量为依据产生CF	//

     // step11// 
    SetMeterCfgACK(0x00,DATACP);//清常数功率寄存器 //

    // STEP 12 打开CF脉冲  //
    CFLED_INITLIZE();
    EIE|=0x01;
    ExInt2IE|=BIT7;     // 开启CF中断 //

    gs_emu_run_var.delay_emu = 2;   // 初始化后的稳定时间为2秒 //
}


/*******************************************************************************************
** 函数名称: Lnk_get_EMU_voltage
** 函数描述: 获取指定通道电压 
** 输入参数: ch: 通道序号0代表合相
** 输出参数: uint32 指定通道电压值，HEX码,量纲为0.01V
** 说明    : 校表系数为0.01V，/10转为0.1V
*******************************************************************************************/
uint32 Lnk_get_EMU_voltage(uint8 ch)
{
    uint32 val,tmpval;
    fp32   f32_tmp;

    if(ch==PHASE_TT) 
    {    
        val= ReadMeterParaACK(RMSU);   
        if(val>=0x80000000)
        {
            val=~val+1;  
        }       
        f32_tmp = (gs_adj_emu_param.vrms_xs*(fp32)val);
        tmpval = (uint32)f32_tmp;
    }
    else
    {
        tmpval = 0;
    }

    return(tmpval);
}

/*******************************************************************************************
** 函数名称: Lnk_get_EMU_current
** 函数描述: 获取指定通道电流
** 输入参数: ch: 通道序号0代表合相
** 输出参数: uint32 指定通道电流值，HEX码,量纲为0.001A
** 说明    : 
*******************************************************************************************/
uint32 Lnk_get_EMU_current(uint8 ch)
{
   uint32 val,tmpval;
   fp32   f32_tmp;

    if(ch==WIRE_L) 
    {
        val = ReadMeterParaACK(RMSII1);  
        if(val>=0x80000000)
        {
            val=~val+1;  
        } 
        f32_tmp = gs_adj_emu_param.i1rms_xs*val;
        tmpval = (uint32)f32_tmp;
    }
    else  if(ch==WIRE_N) 
    {
        val = ReadMeterParaACK(RMSII2);   
        if(val>=0x80000000)
        {
            val=~val+1;  
        }
        f32_tmp = gs_adj_emu_param.i2rms_xs*val;
        tmpval = (uint32)f32_tmp;
    }
    else
    {
        tmpval = 0;
    }

    if( tmpval <VAL_CURRENT_ZERO)   tmpval =0;

    return (tmpval);

}

/*******************************************************************************************
** 函数名称: Lnk_get_EMU_activePower
** 函数描述: 获取指定通道电流
** 输入参数: ch: 通道序号
** 输出参数: uint32 指定通道功率值，HEX码,量纲为0.1W
** 说明    : 
*******************************************************************************************/
uint32 Lnk_get_EMU_activePower(uint8 ch)
{
   uint32 val,tmpval;
   fp32   f32_tmp;

    if(ch==WIRE_L) 
    {
       gs_emu_run_var.net_flg &= ~REV_L_ACPOWER;
       val=ReadMeterParaACK(DATAIP);	 
       if(val>=0x80000000)
       {
          val=~val+1;  
          gs_emu_run_var.net_flg |= REV_L_ACPOWER;
       }
				
    }
   else  if(ch==WIRE_N) 
    {
        gs_emu_run_var.net_flg &= ~REV_N_ACPOWER;
       val=ReadMeterParaACK(DATAIQ);	 
       if(val>=0x80000000)
       {
          val=~val+1; 
           gs_emu_run_var.net_flg |= REV_N_ACPOWER;  
       }	
    }
    else
    {
        val = 0;
    }

    if(val<REF_START_Pn)
    {
        tmpval =0;    
        if(ch==WIRE_L) gs_emu_run_var.net_flg &= ~REV_L_ACPOWER;
        if(ch==WIRE_N) gs_emu_run_var.net_flg &= ~REV_N_ACPOWER;
    }
    else
    {
        f32_tmp = cst_adj_const.Kim_Prms*val;
        tmpval = (uint32)f32_tmp;  	        
    }

    return (tmpval);
}

/*******************************************************************************************
** 函数名称: Lnk_get_EMU_freq
** 函数描述: 获取指定通道电网频率
** 输入参数: ch: 通道序号0代表合相
** 输出参数: uint32 指定通道频率值，HEX码,量纲为0.01Hz
** 说明    : 
*******************************************************************************************/
uint32 Lnk_get_EMU_freq(uint8 ch)
{
    uint32 val,tmpval;

    if(ch==PHASE_TT) 
    {    
        val= ReadMeterParaACK(DATAFREQ);          
        tmpval= (819200 *100)/val;			// 819200为ADC 频率  //
    }
    else
    {
        tmpval = 0;
    }

    return(tmpval);
}

/*******************************************************************************************
** 函数名称: uint8 lnk_CAL_EMU_constSum_per_second(uint8 *bypass_flg,uint8 work_mode)
** 函数描述: 计量数据每秒更新
** 输入参数: work_mode : NORMAL_MODE/DLX_MODE/CONST_MODE三种选择，其他模式退出
**                       *bypass_flg :旁路转态字，用于输出旁路状态
** 输出参数: uint8 ，输出当前计量通道
** 说明    :  表计的计量采用常数计量方式，并在此函数处理旁路和掉零线的
**                   计量通道选择和常量寄存器的赋值，
**                   本函数是计量的十分重要的函数，在TOU的文件内的秒处理内调用
*******************************************************************************************/
uint8 lnk_CAL_EMU_constSum_per_second(uint8 *net_status,uint8 work_mode)
{
   uint32 val1,val2,sumval;
   fp32   f32_tmp;

    sumval = 0;
    (*net_status) &=(~BYPASS_L);       
    (*net_status) &=(~BYPASS_N);   

    (*net_status) &= (~REV_ACPOWER_L);
    (*net_status) &= (~REV_ACPOWER_N);

    //非处理模式则清除常量能量寄存器并退出  // 
    if(work_mode>CONST_MODE)
    {
        sumval = 0;
        SetMeterCfgACK(sumval,DATACP); 
        return (EMU_CH_L);   //计量通道为L //        
    }

#if((_METER_TYPE_CFG == _METER_TYPE_1P2W_0))
    //A路功率获取 //
    val1=ReadMeterParaACK(DATAIP);	 
    if(val1>=0x80000000)
    {
        val1=~val1+1;  
         (*net_status) |=   REV_ACPOWER_L;  
    }
    sumval = val1;

	if(val1<REF_START_Pn)
    {
    	sumval = 0;
    	SetMeterCfgACK(sumval,DATACP);
     	(*net_status) &=  (~REV_ACPOWER_L);  
    }
    SetMeterCfgACK(sumval,DATACP); 
    return (EMU_CH_L);   //计量通道为L //   
#endif

#if((_METER_TYPE_CFG == _METER_TYPE_1P2W_1)||(_METER_TYPE_CFG == _METER_TYPE_1P2W_2))
    if(work_mode==NORMAL_MODE)
    {
        //A路功率获取 //
        val1=ReadMeterParaACK(DATAIP);	 
        if(val1>=0x80000000)
        {
            val1=~val1+1;  
             (*net_status) |=   REV_ACPOWER_L;  
        }

        //B路功率获取 //
        val2=ReadMeterParaACK(DATAIQ);	 
        if(val2>=0x80000000)
        {
            val2=~val2+1;  
             (*net_status) |=   REV_ACPOWER_N;  
        }

        if((val1<REF_START_Pn)&&(val2<REF_START_Pn)) 
        {
            sumval = 0;
            SetMeterCfgACK(sumval,DATACP);
             (*net_status) &=   (~REV_ACPOWER_L);
             (*net_status) &=   (~REV_ACPOWER_N);
            return (EMU_CH_L);   //计量通道默认为L //   
        }

        if((val1>REF_START_Pn)&&(val2<REF_START_Pn))
        {
            sumval = val1;
            SetMeterCfgACK(sumval,DATACP);
             (*net_status)|=   BYPASS_N;   
              (*net_status) &=   (~REV_ACPOWER_N);           
            return (EMU_CH_L);   //计量通道默认为L //      
        }

        if((val1<REF_START_Pn)&&(val2>REF_START_Pn))
        {
            sumval = val2;
            SetMeterCfgACK(sumval,DATACP);
             (*net_status) |=   BYPASS_L;  
             (*net_status) &=   (~REV_ACPOWER_L);
            return (EMU_CH_N);   //计量通道默认为N //          
        }

        if((val1>REF_START_Pn)&&(val2>REF_START_Pn))
        {
            if((val2*95) >(val1*100))
            {
                sumval = val2;
                SetMeterCfgACK(sumval,DATACP);
                (*net_status) |=   BYPASS_L;  
                return (EMU_CH_N);   //计量通道默认为N //         
            }
            else  if((val1*95) >(val2*100))
            {
                sumval = val1;
                SetMeterCfgACK(sumval,DATACP);
                 (*net_status) |=   BYPASS_N;   
                return (EMU_CH_L);   //计量通道默认为L //                 
            }
            else
            {
                sumval = val1;
                SetMeterCfgACK(sumval,DATACP);
                return (EMU_CH_L);   //计量通道默认为L //    
            }
        }
    }

    if((work_mode==DLX_MODE)||(work_mode ==CONST_MODE))
    {
        //A路电流瞬时有效值获取 //
        val1=ReadMeterParaACK(RMSII1);	 
        if(val1>=0x80000000)
        {
            val1=~val1+1;  
        }

        //B路电流瞬时有效值获取 //
        val2=ReadMeterParaACK(RMSII2);	 
        if(val2>=0x80000000)
        {
            val2=~val2+1;  
        }  
        
        // 掉零线回路计量判断 //
        if((val1<REF_DLX_START_IA) &&(val2>REF_DLX_START_IB))
        {
                f32_tmp = val2*gs_adj_emu_param.vconst_val_ch2;   //  //
                sumval = (uint32)f32_tmp;
                SetMeterCfgACK(sumval,DATACP); 
                return (EMU_CH_N);   //计量通道为N //                         
        }
        
        if((val1>REF_DLX_START_IA) &&(val2<REF_DLX_START_IB))
        {
                f32_tmp = val1*gs_adj_emu_param.vconst_val_ch1;   //  //
                sumval = (uint32)f32_tmp;
                SetMeterCfgACK(sumval,DATACP); 
                return (EMU_CH_L);   //计量通道为L //                         
        }
        else
        {
                sumval = 0;
                SetMeterCfgACK(sumval,DATACP); 
                return (EMU_CH_L);   //计量通道为L //                      
        }
        /////////////////////
              
    }
#endif

    return (EMU_CH_L);   //计量通道为L //     
}



/*******************************************************************************************
**    END
*******************************************************************************************/


