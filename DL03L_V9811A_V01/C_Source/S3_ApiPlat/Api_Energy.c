/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Energy.C
**Author		: maji
**date			: 2016-04-20 
**description	: 电能计量应用层相关函数C文件
**note			: MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-20   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#include <MyIncludes_H.h>




ENERGY_USER_DATA    gs_energy_user_data;            //当前电量RAM主数据  //
ENERGY_USER_DATA    gs_energy_user_data_back;   //当前电量RAM备份数据 //
ENERGY_VAR		      gs_energy_var;                 // 电能增量脉冲变量数据，上电初始化为0  //


/*****************************************************************************
** Function name    :api_init_current_energy_data_ram
**
** Description         :初始化当前电量RAM区数据，程序复位初始化调用        
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_init_current_energy_data_ram(void)
{
 uint8 i;

    api_check_current_energy_data(); 
    for(i=0;i<EC_CH_NUM;i++)
    {
        gs_energy_var.pluse[i] = 0;
    }
}

/*****************************************************************************
** Function name    :api_check_current_energy_data
**
** Description         :当前电能数据的检查处理，电能累计函数调用
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_check_current_energy_data(void)
{   
    INT16U csck_tmp;
 
    //电能数据获取  //   
    csck_tmp = Lib_get_csck_int16u_num(&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);
    if(csck_tmp != gs_energy_user_data.u16_csck) 
    {
        csck_tmp = Lib_get_csck_int16u_num(&gs_energy_user_data_back.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);        
        if(csck_tmp != gs_energy_user_data_back.u16_csck) 
        {
            mem_read(&gs_energy_user_data_back.us_val[0][0].buf[0], ADR_BLOCK00_EC_L0_E2P, LEN_EC_CURRENT, MEM_E2P1);
            gs_energy_user_data_back.u16_csck = Lib_get_csck_int16u_num(&gs_energy_user_data_back.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);
        }
        Lib_Copy_Str_TwoArry(&gs_energy_user_data.us_val[0][0].buf[0],&gs_energy_user_data_back.us_val[0][0].buf[0],LEN_EC_CURRENT);
        gs_energy_user_data.u16_csck = gs_energy_user_data_back.u16_csck;       
    }
}

/*****************************************************************************
** Function name    :lnk_inc_energy_pluse
**
** Description         :当前电能脉冲增量处理，安装定义的通道进行累计    
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
uint8 lnk_add_energy_pluse(void)
{
uint8 i;
uint8 chg_fg=FALSE;
uint8 u8_tmp;

	for(i=0;i<EC_CH_NUM;i++)
	{
		switch (i)
		{
			default:
				if(gs_energy_var.pluse[i]>0)
				{
					DisableINT();    				// disable interrupt function  //
					u8_tmp = gs_energy_var.pluse[i];
					gs_energy_var.pluse[i] =0;  //清零处理 //
					EnableINT();

					chg_fg = TRUE;
                                 //u16_tmp = MAKEWORD(gs_energy_user_data.us_val[i][0].buf[4],gs_energy_user_data.us_val[i][0].buf[5]);
					gs_energy_user_data.us_val[i][0].val.decim_hex16 += u8_tmp;
					#if (TARIFF_MAX_NUM>1)
					gs_energy_user_data.us_val[i][EN_TRIFF_no].val.decim_hex16 += u8_tmp;
					#endif
				}
			break;
		
		}
	}

	return (chg_fg);
}


/*****************************************************************************
** Function name    :api_accum_current_energy_data_pre_second
**
** Description         :当前电能数据累计处理，每秒调用
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_accum_current_energy_data_pre_second(void)
{
uint8 save_fg=FALSE;
uint8 i;

        if(CheckPOWERUP() !=TRUE)   return;  
	// 电能数据合法性检查 //
	api_check_current_energy_data();

	//电能脉冲增量处理 //
	if(lnk_add_energy_pluse()==FALSE)  return;  
	
	for(i=0;i<EC_CH_NUM;i++)
	{
		if(gs_energy_user_data.us_val[i][0].val.decim_hex16>=METER_CONST_1KWH)
		{
			if(i==0)   save_fg = TRUE;   //电能通道1的电量发生整数进位时配置存储标识 //
			gs_energy_user_data.us_val[i][0].val.decim_hex16 -= METER_CONST_1KWH;
			gs_energy_user_data.us_val[i][0].val.integ_hex32++;
			if(gs_energy_user_data.us_val[i][0].val.integ_hex32 > MAX_ENERGY_INtEGER)
			{
				gs_energy_user_data.us_val[i][0].val.integ_hex32 = 0;  // 超出最大范围后清理 //
			}
		}
		#if (TARIFF_MAX_NUM>0)
		if(gs_energy_user_data.us_val[i][EN_TRIFF_no].val.decim_hex16>=METER_CONST_1KWH)
		{
			gs_energy_user_data.us_val[i][EN_TRIFF_no].val.decim_hex16 -= METER_CONST_1KWH;
			gs_energy_user_data.us_val[i][EN_TRIFF_no].val.integ_hex32++;
			if(gs_energy_user_data.us_val[i][EN_TRIFF_no].val.integ_hex32 > MAX_ENERGY_INtEGER)
			{
				gs_energy_user_data.us_val[i][EN_TRIFF_no].val.integ_hex32 = 0;  // 超出最大范围后清理 //
			}
		}		
		#endif
		
	}

	// 更新RAM区电能校验和和备份区数据//
	gs_energy_user_data.u16_csck = Lib_get_csck_int16u_num(&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);  
	Lib_Copy_Str_TwoArry(&gs_energy_user_data_back.us_val[0][0].buf[0],&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_E2P);

	// 电能数据保存 //
	if(save_fg==TRUE)
	{
		mem_db_write(ADR_BLOCK00_EC_L0_E2P,&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT,MEM_E2P1);
	}        
}



/*****************************************************************************
** Function name    :api_clr_current_energy_data
**
** Description         :当前电能数据的清零处理
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_clr_current_energy_data(void)
{
    // 清除当前电量数据的RAM主区数据 //
    Lib_Set_String(&gs_energy_user_data.us_val[0][0].buf[0],0,LEN_EC_CURRENT);
    gs_energy_user_data.u16_csck = Lib_get_csck_int16u_num(&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);  
    // 清除当前电量数据的RAM备份区数据 //
    Lib_Copy_Str_TwoArry(&gs_energy_user_data_back.us_val[0][0].buf[0],&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_E2P);
    // 清除当前电量数据的E2P区数据 //
    mem_db_write(ADR_BLOCK00_EC_L0_E2P,&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_E2P-2,MEM_E2P1);
}


	
/***************************************************************
*    END
****************************************************************/

