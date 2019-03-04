/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Measure.H
**Author		: maji
**date			: 2016-04-21 
**description	: c code for ��������Ӧ�ò�
**note			: MCU- G80F92XD ��MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-21   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#include <MyIncludes_H.h>

MEASURE_VAR_DATA gs_measure_var_data;
MEASURE_STATU_JUDGE_VAR gs_measure_status_judge_var;

/*****************************************************************************
** Function name    :api_Measure_ram_INIT
**
** Description         :��������������ʼ��
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_Measure_ram_INIT(void)
{
 INT16U temp_16u;
    temp_16u = gs_measure_var_data.w_temp.u16;   //��ȡ����¶�  //
    Lib_Set_String((uint8 *)&gs_measure_var_data,0,sizeof(MEASURE_VAR_DATA));
    Lib_Set_String((uint8 *)&gs_measure_status_judge_var,0,sizeof(MEASURE_STATU_JUDGE_VAR));

     gs_measure_var_data.w_temp.u16 = temp_16u;   //��ȡ����¶�  //
}

/*****************************************************************************
** Function name    :api_measure_deal_pre_second
**
** Description         :ÿ����õĲ�������
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_measure_deal_pre_second(void)
{
 uint32 u32_UI, u32_P, u32_PF;
 
    if(CheckPOWERUP() !=TRUE)   return;        

    if(gs_emu_run_var.delay_emu>0)
    {
        gs_emu_run_var.delay_emu--;
        api_Measure_ram_INIT();
        return;
    }

    //��ȡ����ͨ�����������ݸ�ֵ����ȡ����״̬����  //
    gs_measure_status_judge_var.emu_ch = lnk_CAL_EMU_constSum_per_second(&gs_measure_status_judge_var.u8_status,gs_sys_globaL_var.work_mode);

    //��ѹ��ȡ  //
    gs_measure_var_data.gs_really[0].dw_u_val.u32= Lnk_get_EMU_voltage(PHASE_TT);
    
    //������ȡ  //
    gs_measure_var_data.gs_really[0].dw_i_val.u32 = Lnk_get_EMU_current(WIRE_L);
   // gs_measure_var_data.dw_i_n_val.u32  = Lnk_get_EMU_current(WIRE_N);

    //�й����ʻ�ȡ  //
    gs_measure_var_data.gs_really[0].dw_p_val.u32 = Lnk_get_EMU_activePower(WIRE_L);
   // gs_measure_var_data.dw_p_n_val.u32  = Lnk_get_EMU_activePower(WIRE_N);   

    //����Ƶ�ʲ���//
    gs_measure_var_data.gs_really[0].w_freq_val.u16 = (uint16)Lnk_get_EMU_freq(PHASE_TT);
    // �����ص�ѹ�������� //
    
    if(gs_measure_var_data.gs_really[0].dw_p_val.u32<20)
    {
        gs_measure_var_data.gs_really[0].dw_i_val.u32 = 0;
        gs_measure_var_data.gs_really[0].dw_p_val.u32 = 0;
        gs_measure_var_data.gs_really[0].dw_pf_val.u16= 1000;
    }
    else
    {
        //���㹦������������0.001 ��ʽX.XXX //
        u32_P = 1000*gs_measure_var_data.gs_really[0].dw_p_val.u32;
        u32_UI = ((gs_measure_var_data.gs_really[0].dw_u_val.u32 * gs_measure_var_data.gs_really[0].dw_i_val.u32 )/1000);
        u32_PF = u32_P/u32_UI;
        if(u32_PF>995)  u32_PF = 1000;
        gs_measure_var_data.gs_really[0].dw_pf_val.u16 = (uint16)(u32_PF);
    }
    
}

/*****************************************************************************
** Function name    :api_measure_VBAT_pre_min
**
** Description         :ÿ���Ӳ���һ�ε�ص�ѹ
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_measure_VBAT_pre_min(void)
{
    gs_measure_var_data.w_bat_v.u16= (Samlpe_BatAdc());
  
//      if( gs_measure_var_data.w_bat_v.u16<= 280 )
		if( gs_measure_var_data.w_bat_v.u16<= 250 ) 
     	{
          gs_measure_var_data.w_bat_v.u16= (Samlpe_BatAdc());
         // if( gs_measure_var_data.w_bat_v.u16<= 280 )
		   if( gs_measure_var_data.w_bat_v.u16<= 250 ) 
		  	gs_measure_status_judge_var.u8_status |=VBAT_LOW;
     	}
      else
      	{
         gs_measure_status_judge_var.u8_status &= (~VBAT_LOW);
       }	
}

/*****************************************************************************
** Function name    :api_measure_VBAT_pre_min
**
** Description         :ÿ���Ӳ���һ�ε�ص�ѹ
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_measure_temperature_pre_min(void)
{
#ifdef _RTC_CAL
     gs_measure_var_data.w_temp.u16 =  (INT16U)(10*Handl_RTC_Adj_per_minu());         // ���²����ܵı���µ�ͬʱ����²� //
#endif

#ifndef _RTC_CAL
    gs_measure_var_data.w_temp.u16 = Samlpe_temperatureAdc();
#endif
}


/***************************************************************
*    END
****************************************************************/

