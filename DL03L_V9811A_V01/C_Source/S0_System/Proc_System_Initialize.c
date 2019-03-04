/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Proc_System_Initialize.c
**Author		: maji
**date			: 2016-04-20
**description	: 系统复位初始化处理相关C代码
**note			: V9811A ，MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>


/****************************************************************
Function:           Proc_Initialize_systerm_normal_mode 
Description:            系统上电/复位初始化函数 
Input:			no
Parameters:         	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_handle_when_systerm_reset(void)
{
   #if(MCU_TYPE == MCU_G80F92X)   // 中颖芯片 //
       IEN0=0x00;
   IEN1=0x00;
    gs_sys_globaL_var.reset_status = RSTSTAT;
   Switch_Clk_4P096M();
   #endif

   #if(MCU_TYPE == MCU_V98XX)   //万工芯片 //
   gs_sys_globaL_var.reset_status = Systate;
         #ifndef _RTC_CAL    //不需要温补操作时执行下面内容 //
          Clr_RTC_AdjParam();
          #endif

    SPCFNC=1;  		//调整FLASH功耗
    XBYTE[0x0402]=0x86;
    SPCFNC=0;
    CBANK=0X01;
   Set_McuClock(FSYSCLK_800k);   //SetMCUPLL();  6Mhz
   #endif

    Init_GPIO_sleep();
    E2p_IIC_Initail();
    E2p_Stop_i2c();

}

/****************************************************************
Function:   		Proc_Initialize_INRam
Description: 		上电初始化RAM相关
Input:			no
Parameters:     	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_Initialize_INRam(void)
{
    //////////dubge   将E2P初始化////////////
//    mem_db_clr(0XA5);
//    CLRWDT();
    ////////////////////////////
    mem_db_check();  //数据校验检查 //
    CLRWDT();
////////////////////////////////////////////////
//  S0_System 区相关RAM初始化
////////////////////////////////////////////////
    Proc_sys_data_init();
    Proc_init_tou_var();
    Proc_init_Check_var();

////////////////////////////////////////////////
//  S1_HardDrv 区相关RAM初始化
////////////////////////////////////////////////
    Init_EMU_RAM();    

////////////////////////////////////////////////
//  S3_ApiPlat 区相关RAM初始化
////////////////////////////////////////////////
    api_init_md_data_ram();
    api_init_current_energy_data_ram();

    api_Measure_ram_INIT();
    api_measure_VBAT_pre_min();
    api_measure_temperature_pre_min();

#if (TARIFF_MAX_NUM>1)
    api_update_triffNo_pre_minute();   
#endif

#if (BILL_MAX_NUM>1)
    api_handl_settle_when_powerUp();   
#endif

////////////////////////////////////////////////
//  S4_ApiUser 区相关RAM初始化
////////////////////////////////////////////////
    api_init_display();


}


/****************************************************************
Function:   		void SysInitialize(void)  
Description: 		系统上电/复位初始化函数 
Input:			no
Parameters:     	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_sleep_when_reset(void)
{
    switch (gs_sys_globaL_var.reset_status&0x3c)
    {
        // IO唤醒，可能来源为按键IO //
        
			 case BIT3: 
           // if(KEY_READ_DIS() == FALSE) 	// 按键 //
            {
                Set_McuClock(FSYSCLK);   //SetMCUPLL();  6Mhz  //
                // 1 打开液晶显示//
                Init_LCD();
                api_check_current_energy_data();		//  初始化电量//
                api_handl_dis_sleep_key();        //处理显示项目 //
//                SetExtRTC(0x01,0x00);// 秒唤醒//
//                Set_McuSleep();       // 处理结束后休眠 //
            }
        break;   

        // RTC唤醒，可能来源唤醒显示内容切换//
        //default:
        case BIT2:
             Set_McuClock(FSYSCLK);   //SetMCUPLL();  6Mhz  //					
            if(INTRTC ==0)   
            {   
                if(gs_dis_ctl_var.keep_sec[1]>0)   gs_dis_ctl_var.keep_sec[1]--;
                if(gs_dis_ctl_var.keep_sec[1] ==0)  
                {
                    api_handl_dis_sleep();            //下电液晶显示处理 //    
//                    SetExtRTC(0x01,0x02);// 小时唤醒
//                    CLRWDT();
//                    if(CheckPOWERUP()==TRUE)     sys_err();   
//                    Set_McuSleep();       // 处理结束后休眠 //    
                }
//                else
//                {
////                    SetExtRTC(0x01,0x00);// 秒唤醒//
////                    CLRWDT();
////                    if(CheckPOWERUP()==TRUE)     sys_err();   
////                    Set_McuSleep();       // 处理结束后休眠 //    
//                }
            }
//            else
//            {
////                api_measure_temperature_pre_min();     // 注意这个函数可选进行RTC温度补偿//
////                SetExtRTC(0x01,0x02);// 小时唤醒
//                CLRWDT();
//                if(CheckPOWERUP()==TRUE)     sys_err();   
////                Set_McuSleep();       // 处理结束后休眠 //    
//            } 
            break;
						
        
    }
		CLRWDT();
//		mem_read(&gs_even_fun_var.even_fun_doingflg[ID_CLASS_II_COVER-ID_CLASS_II_min],ADR_CLASS2FLG_START_E2P+ (ID_CLASS_II_COVER-ID_CLASS_II_min)* LEN_CLASSII_flg,LEN_CLASSII_flg,MEM_E2P1);	
//					
//    if(Judge_ERR_COVER_key()==TRUE)
//	      api_pwl_cover_even_class_recode(ID_CLASS_II_COVER-ID_CLASS_II_min,START);
//    else 
//				api_pwl_cover_even_class_recode(ID_CLASS_II_COVER-ID_CLASS_II_min,END);	

    if(Judge_ERR_COVER_key()==TRUE)api_deal_even_class_recode(ID_CLASS_II_COVER,START);
    else api_deal_even_class_recode(ID_CLASS_II_COVER,END);
		
    if(CheckPOWERUP()==TRUE)     sys_err();   

//  api_measure_temperature_pre_min();     // 注意这个函数可选进行RTC温度补偿//
//		Init_GPIO_sleep();
    SetExtRTC(0x01,0x00);// 小时唤醒
    CLRWDT();
//    if(CheckPOWERUP()==TRUE)     sys_err();   
    Set_McuSleep();       // 处理结束后休眠 //     
    Set_McuSleep();       // 处理结束后休眠 //      		
}
	



/****************************************************************
Function:           Proc_Initialize_systerm_normal_mode 
Description:            系统上电/复位初始化函数 
Input:			no
Parameters:         	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_Initialize_systerm_normal_mode(void)
{
    Init_RTC();
    Init_LCD();
    
    Set_McuClock(FSYSCLK);   //SetMCUPLL();  6Mhz
    Init_GPIO_run();
    Lib_Delay_ms(200);
    CLRWDT();

    Proc_Initialize_INRam();  //初始化RAM区 //
	
    Init_Timer();	
    Init_RTC();
    //Open_SecOut();
    Init_UART2_hard(BPS300);  //IR  //
    Init_UART4_hard(BPS300);  //RS485  //
    Init_LCD();
    Full_SEG(0xFF);
    api_handl_COMM_FRAME_ERROR(UART_CH0_IR);
    api_handl_COMM_FRAME_ERROR(UART_CH1_RS);  
    Init_EMU(NORMAL_MODE);
	
	  gs_even_fun_var.into_cnt[ID_CLASS_II_PWN-ID_CLASS_II_min]=4;  // 事件保持时间 二类事件序号
	  gs_even_fun_var.esc_cnt[ID_CLASS_II_PWN-ID_CLASS_II_min]=4;  // 事件保持时间
	  api_deal_even_class_recode(ID_CLASS_II_PWN,END);
	  
		KEY_ERR_COVER_INITLIZE() ;
}



/****************************************************************
Function:          Proc_Initialize_systerm_reset
Description:        系统上电/复位初始化函数 
Input:			no
Parameters:         	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_Initialize_systerm_reset(void)
{

    Proc_handle_when_systerm_reset();   // 系统复位的处理函数，注意MCU不同时需要进行修改函数内容 //
    Set_Mcu_core();
   //Lib_Delay_ms(110);         //滤波处理  //
   CLRWDT();   


    if(CheckPOWERUP()== FALSE)		//无市电
    {
        #if((_METER_TYPE_CFG ==_METER_TYPE_1P2W_0) ||(_METER_TYPE_CFG ==_METER_TYPE_1P2W_1) )
        gs_sys_globaL_var.work_mode = SLEEP_MODE;  
        #endif

        #if((_METER_TYPE_CFG ==_METER_TYPE_1P3W_10) ||(_METER_TYPE_CFG ==_METER_TYPE_1P3W_11) )
        gs_sys_globaL_var.work_mode = SLEEP_MODE;  
        #endif
		
        //Proc_sleep_when_reset();
    }
    else
   {
        gs_sys_globaL_var.work_mode = NORMAL_MODE;
   }


    ////////////////////////////////////////////////////
    
    if(gs_sys_globaL_var.work_mode == SLEEP_MODE)
    {
        Proc_sleep_when_reset();                                   // 休眠初始化//
    }
    else
    {
        #if(_METER_TYPE_CFG == _METER_TYPE_1P2W_2)
         if(gs_sys_globaL_var.work_mode == DLX_MODE)   //  掉零线初始化//
        {
            Proc_Initialize_systerm_dlx_mode(); 
        }
        else
        {
            Proc_Initialize_systerm_normal_mode();    //  市电供应情况下的初始化//
        }
	 #endif

       ////////////////////////////////////////////////////
       //  市电供应情况下的初始化//
        #if((_METER_TYPE_CFG ==_METER_TYPE_1P2W_0) ||(_METER_TYPE_CFG ==_METER_TYPE_1P2W_1) )
        Proc_Initialize_systerm_normal_mode();    //  市电供应情况下的初始化//
        #endif
	 
    }
	
}



/****************************************************************
Function:           Proc_judge_Power_down_process
Description:       运行过程中的掉电检查函数
Input:			no
Parameters:         	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_judge_Power_down_process(void)
{
    if(CheckPOWERUP()==TRUE)   return;

    Lib_Delay_ms(100);	
    CLRWDT();
    
    if(CheckPOWERUP()==TRUE)   return;  
    Lib_Delay_ms(100);	
    CLRWDT();
    E2p_IIC_Initail();
    E2p_Stop_i2c();		
	
	//save data-------------------------------
    mem_db_write(ADR_BLOCK00_EC_L0_E2P,&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT,MEM_E2P1);
    mem_db_write(ADR_METER_VAR_RTC, &gs_CurDateTime.Week, 7, MEM_E2P1);
    CLRWDT();
   gs_even_fun_var.into_cnt[ID_CLASS_II_PWN-ID_CLASS_II_min]=4;  // 事件保持时间传人ID - 0-6
	 api_deal_even_class_recode(ID_CLASS_II_PWN,START);	
	
	 gs_even_fun_var.into_cnt[ID_CLASS_II_L1reverse-ID_CLASS_II_min]=4;  // 事件保持时间 二类事件序号
	 gs_even_fun_var.esc_cnt[ID_CLASS_II_L1reverse-ID_CLASS_II_min]=4;  // 事件保持时间
	 api_deal_even_class_recode(ID_CLASS_II_L1reverse,END);

   	
		
    api_Measure_ram_INIT();
    //api_handl_dis_sleep();

//    mem_read(&gs_even_fun_var.even_fun_doingflg[ID_CLASS_II_COVER-ID_CLASS_II_min],ADR_CLASS2FLG_START_E2P+ (ID_CLASS_II_COVER-ID_CLASS_II_min)* LEN_CLASSII_flg,LEN_CLASSII_flg,MEM_E2P1);	
//		
    Init_GPIO_sleep();
    
    KEY_DIS_INITLIZE();

	  KEY_ERR_COVER_INITLIZE() ;
    E2p_IIC_Initail();
    E2p_Stop_i2c();		
	
    api_handl_dis_sleep();            //下电液晶显示处理 //
    if(CheckPOWERUP()==TRUE)     sys_err();   
    
    SetExtRTC(0x01,0x00);// 小时唤醒
    Set_McuSleep();       // 处理结束后休眠 //
    Set_McuSleep();       // 处理结束后休眠 //
    
}


/****************************************************************
Function:   		void sys_err(void)
Description: 		系统错误后的看门狗复位处理
Input:			no
Parameters:     	no
Returns:			no                        
Others:         
****************************************************************/
void sys_err(void)
{  
    CLRWDT();

    while(1)
    {
		NOP();
		NOP();
		NOP();
    }  
}



/***************************************************************
*    END
****************************************************************/

