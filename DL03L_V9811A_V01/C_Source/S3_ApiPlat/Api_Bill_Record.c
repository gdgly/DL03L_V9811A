/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Api_Measure.c
**Author: maji
**date: 
**description: c code for 测量程序应用层
**note:  Driver code for GENERAL
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2015-10-21   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>


#if (BILL_MAX_NUM>0)


//*****************************************************************
//	Calculate the address of history data
//*****************************************************************
code BILL_INFO bill_info[] = 
{
    ADR_BLOCK101_BILL1_DATA_E2P, ADR_BLOCK26_BILL_VAR_PTR_E2P,  LEN_BLOCK10X_BILLX_DATA_E2P,  BILL_MAX_NUM,   MEM_E2P1,		    // 0 电量结算账单周期数   //
};   


/*****************************************************************************
** Function name    :api_get_bill_record_addr
**
** Description         : 获取指定账单类记录的绝对地址(输入相对地址位置)    
**
** Parameters         :INT16U addr: 输入相对地址位置       
**
** Returned value   :INT16U addr: 输出绝对地址位置  
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
INT16U api_get_bill_record_addr( INT16U addr )
{
 INT8U i,ptr,temp ,num;
 INT16U hist_addr,len;

	for( i=0; i<(sizeof(bill_info)/sizeof(BILL_INFO)); i++ )
	{
		hist_addr = bill_info[i].head_adr;
		len = bill_info[i].data_size* (INT16U)bill_info[i].ptr_num;
		if( addr>=hist_addr && addr<(hist_addr+len) ) break;
	}

	mem_read(&ptr, bill_info[i].ptr_adr, 1, bill_info[i].mem_type);
	if( ptr>= bill_info[i].ptr_num)
	{
	    ptr = 0;
	}
	
	hist_addr = addr - bill_info[i].head_adr;
	temp = hist_addr / bill_info[i].data_size;
	num = hist_addr - temp*bill_info[i].data_size;
	if ( ptr < temp ) 
	{
	    ptr = ptr + ( bill_info[i].ptr_num -temp);    
	}
	else
	{
	    ptr = ptr - temp; 
	}
	addr = bill_info[i].head_adr+ ptr*(INT16U)bill_info[i].data_size +num;

	return	addr;
}



/*****************************************************************************
** Function name    :api_write_bill_data
**
** Description         : 写入账单类记录的数据
**
** Parameters         :INT8U id: 账单时间类    
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_write_bill_data(INT8U id)
{
INT16U adr_tmp;
INT8U  ptr_tmp;
INT8U buff_int8u[BILL_BUFF_MAX_LEN];


    Lib_Clr_String(&buff_int8u[0],BILL_BUFF_MAX_LEN);

    // 1.调整记录数据的指针数据并获得数据存储的首地址  //
    mem_read(&ptr_tmp, bill_info[id].ptr_adr, 1, MEM_E2P1);
    ptr_tmp++;
    if(ptr_tmp>(bill_info[id].ptr_num-1))   ptr_tmp = 0;  
    adr_tmp = bill_info[id].head_adr+ptr_tmp* bill_info[id].data_size;
    mem_db_write(bill_info[id].ptr_adr,&ptr_tmp, 1,  MEM_E2P1);

    // 2.获取数据至事件记录的缓冲区  //
    switch(id)
    {
        case BILL_ID0_MOTTH_SETTL:
            buff_int8u[0]= gs_CurDateTime.Year;
            buff_int8u[1]= gs_CurDateTime.Month;
            buff_int8u[2]= gs_CurDateTime.Day;
            buff_int8u[3]= gs_CurDateTime.Hour;
            buff_int8u[4]= gs_CurDateTime.Minute;
            buff_int8u[5]= gs_CurDateTime.Second;
            mem_db_write(ADR_BLOCK26_BILL_VAR_DATETTIME_E2P,&buff_int8u[0], 6,  MEM_E2P1); //当前最近1次结算点时间日期记录      //

            Lib_Copy_Str_TwoArry(&buff_int8u[6], &gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT);
            mem_read(((&buff_int8u[6])+LEN_EC_CURRENT), ADR_BLOCK01_MMD_L0_E2P, LEN_MMD_CURRENT, MEM_E2P1);  
            mem_db_write(adr_tmp,&buff_int8u[0], bill_info[id].data_size-2,  MEM_E2P1);

            //当前需量清零  //
            api_clr_current_MD_data();
        break;

        default:
            sys_err();	
        break;
    }
    

}


/*****************************************************************************
** Function name    :api_handl_settle_per_minute
**
** Description         :每分钟调用的月结算函数，当前时钟的日时时间和结算参数相等时进行月结算处理
**
** Parameters         :NONE    
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-05-3
******************************************************************************/
void api_handl_settle_per_minute(void)
{
  uint8 param_settel[2];   //最近1次结算时间点 年月日时分秒 //
  ST_U16_U08 u16_hour_A,u16_hour_B;

    if(gs_CurDateTime.Minute != 0)   return;   //分钟和秒都为0的时候处理 //

    mem_read(&param_settel[0], ADR_METER_PARAM1_SETL_DDHH, 2, MEM_E2P1);  //读取电量结算日( 日，时)//
    u16_hour_A.u16= Lib_bcd_byte(param_settel[0]) *24+ Lib_bcd_byte(param_settel[1]);    //换算获取结算参数小时单位数据 //
    u16_hour_B.u16 = Lib_bcd_byte(gs_CurDateTime.Day)*24 + Lib_bcd_byte(gs_CurDateTime.Hour);     //换算获取当前时钟的日时部分的小时单位数据 //	

    if((u16_hour_B.u16 - u16_hour_A.u16)==0)    //相等则结算 //
    {
        api_write_bill_data(BILL_ID0_MOTTH_SETTL);	//电量结算//	
    }
}



/*****************************************************************************
** Function name    :api_handl_settle_when_powerUp
**
** Description         :上电补月结算应用函数
**
** Parameters         :NONE   
**
** Returned value   :NONE
**
** NOTE                :注意在调用本函数前需要确保系统读取过RTC数据和当前电量数据
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-05-03
******************************************************************************/
void api_handl_settle_when_powerUp(void)
{
  uint8 last_rec_dateTime[6];   //最近1次结算时间点 年月日时分秒 //
  uint8 param_settel[2];   //最近1次结算时间点 年月日时分秒 //
  ST_U16_U08 u16_month_A,u16_month_B;
  ST_U16_U08 u16_hour_A,u16_hour_B;
  uint16  months_no_settled;
  INT8U i,j; 

   
    mem_read(&last_rec_dateTime[0], ADR_BLOCK26_BILL_VAR_DATETTIME_E2P, 6, MEM_E2P1); //读取上次结算时间(年月日时分秒 )
    u16_month_A.u16 = Lib_bcd_byte(last_rec_dateTime[0])*12 + Lib_bcd_byte(last_rec_dateTime[1]);	    //最近1次结算的月单位数据 //
    u16_month_B.u16 = Lib_bcd_byte(gs_CurDateTime.Year)*12 + Lib_bcd_byte(gs_CurDateTime.Month);	
    mem_read(&param_settel[0], ADR_METER_PARAM1_SETL_DDHH, 2, MEM_E2P1);  //读取电量结算日( 日，时)//
    u16_hour_A.u16 = Lib_bcd_byte(param_settel[0]) *24+ Lib_bcd_byte(param_settel[1]);
    u16_hour_B.u16 = Lib_bcd_byte(gs_CurDateTime.Day)*24 + Lib_bcd_byte(gs_CurDateTime.Hour);	

	if(u16_month_A.u16>u16_month_B.u16)
	{
		months_no_settled = 1;   // 最近1次结算时间大于当前时间时，默认补1次结算 //
	}
	else
	{
		months_no_settled = u16_month_B.u16- u16_month_A.u16;
	}

    j=0;//补结算的记录条数清零  //
    for(i=0;i<(MAX_Fill_SETTLED_MONTHS+1);i++)
    {
        if(j>= MAX_Fill_SETTLED_MONTHS)  break;
        if(months_no_settled==0)   break;
        if(months_no_settled==1)   
        {
            if(u16_hour_B.u16>= u16_hour_A.u16)
            {
                api_write_bill_data(BILL_ID0_MOTTH_SETTL);	//月结算//		
                CLRWDT();
                j++;
                months_no_settled--;
            }
            else
            {
                break;
            }
        } 
        else
        {
            api_write_bill_data(BILL_ID0_MOTTH_SETTL);	//月结算//		
            CLRWDT();
            j++;
            months_no_settled--;  
        } 
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
void api_clr_bill_data(void)
{
    E2P_BILL_VAR_MAP  tmp_bill_var;

     CLRWDT();
    Lib_Clr_String(&tmp_bill_var.bill_var.ptrNo,LEN_BILL_EXRAM_VAR);
    mem_db_write(ADR_BLOCK26_BILL_VAR_E2P,&tmp_bill_var.bill_var.ptrNo, LEN_BILL_EXRAM_VAR,  MEM_E2P1); //清除指针记录 // 
    CLRWDT();
    
    mem_fill(ADR_BLOCK101_BILL1_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK102_BILL2_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK103_BILL3_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK104_BILL4_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK105_BILL5_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK106_BILL6_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK107_BILL7_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK108_BILL8_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK109_BILL9_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK110_BILL10_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK111_BILL11_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK112_BILL12_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    
}




#endif

/***************************************************************
*    END
****************************************************************/


