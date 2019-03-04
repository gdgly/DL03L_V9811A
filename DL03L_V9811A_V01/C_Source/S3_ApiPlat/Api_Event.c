/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Event.C
**Author		: maji
**date			: 2016-04-20 
**description	: 事件记录处理应用层相关函数程序C文件
**note			: MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-20   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#include <MyIncludes_H.h>

const  EVEN_CLASSII_VAR  code   gs_even_var =
{
0,    //  even_cnt[0];
3,3,3,
0,     //  doing_flg[0];
0,0,0,
0,   // even_data[0]
0,0,0,	
0, // even_csck
};
EVEN_FUN_VAR   gs_even_fun_var;


/*******************************************************************************
* 全局变量定义区
*******************************************************************************/


/*******************************************************************************
* 常量表区
*******************************************************************************/
//  常量字符表定义 x//
const CLASS_I_TAB  code even_class_I_tab[] = {
    ID_CLASS_I_PROG,         ADR_BLOCK150_EVENI_PROG_E2P,
    ID_CLASS_I_resetMD,     ADR_BLOCK151_EVENI_resetMD_E2P,
    ID_CLASS_I_setRtc,       ADR_BLOCK152_EVENI_setRtc_E2P,
    
	// 2类数据//
	  
	  ID_CLASS_II_PWN,            ADR_BLOCK161_EVENII_PWN_E2P, 
	  ID_CLASS_II_lowbattery,    ADR_BLOCK162_EVENII_lowbattery_E2P,
	  ID_CLASS_II_COVER,         ADR_BLOCK163_EVENII_COVER_E2P,
    ID_CLASS_II_L1reverse,     ADR_BLOCK164_EVENII_L1reverse_E2P,  //L1反向事件 //	
};


/*****************************************************************************
** Function name    :api_measure_deal_pre_second
**
** Description         :每秒调用的事件记录扫描//
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/

INT8U api_even_Detect_lowbattery(void)
{
 if(gs_measure_status_judge_var.u8_status & VBAT_LOW)
   return TRUE;

  else   return FALSE ;
}


/*****************************************************************************
** Function name    :api_measure_deal_pre_second
**
** Description         :每秒调用的事件记录扫描//
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/

INT8U  api_even_Detect_L1reverse(void)
{

	if(gs_measure_status_judge_var.u8_status&REV_ACPOWER_L)
		return TRUE;
  	else   
		return FALSE ;
}


/*****************************************************************************
** Function name    :api_measure_deal_pre_second
**
** Description         :每秒调用的事件记录扫描//
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_even_Detect_sec(void)
{
     if(CheckPOWERUP()!=TRUE) return;    

//    api_even_ee_err(); // E2错误扫描..
//	
	if(api_even_Detect_lowbattery()==TRUE)api_deal_even_class_recode(ID_CLASS_II_lowbattery,START);
	else  api_deal_even_class_recode(ID_CLASS_II_lowbattery,END);

//	if(api_even_Detect_NOL1()==TRUE)api_deal_even_class_recode(ID_CLASS_II_NOL1,START);
//	else  api_deal_even_class_recode(ID_CLASS_II_NOL1,END);

//	if(api_even_Detect_NOL2()==TRUE)api_deal_even_class_recode(ID_CLASS_II_NOL2,START);
//	else  api_deal_even_class_recode(ID_CLASS_II_NOL2,END);


	//反向只做合相功率反向事件 ID 使用L1断相
	if(api_even_Detect_L1reverse()==TRUE)api_deal_even_class_recode(ID_CLASS_II_L1reverse,START);
	else  api_deal_even_class_recode(ID_CLASS_II_L1reverse,END);

//	if(api_even_Detect_L2reverse()==TRUE)api_deal_even_class_recode(ID_CLASS_II_L2reverse,START);
//	else  api_deal_even_class_recode(ID_CLASS_II_L2reverse,END);
  if(Judge_ERR_COVER_key()==TRUE)api_deal_even_class_recode(ID_CLASS_II_COVER,START);
  else api_deal_even_class_recode(ID_CLASS_II_COVER,END);
//   Proc_Check_COVER_Pre_sec();
}


/*****************************************************************************
** Function name    :api_measure_deal_pre_second
**
** Description         :每秒调用的测量函数
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_deal_even_class_recode(uint8 even_id, uint8 type )
{
    uint8 i,ID;
    CLASS_I_TAB  tab_class;

    if(even_id < ID_CLASS_I_max ) 
    {
    for(i=0;i< ID_CLASS_I_max ; i++)
    {
        if(even_id==even_class_I_tab[i].id_even)  break;
    }

    if(i>=ID_CLASS_I_max)   return;

    tab_class.addr_even = even_class_I_tab[i].addr_even;
    ID = even_id ;        // 一类事件ID  0-6
    }
  else if( (even_id >= ID_CLASS_II_min)&&(even_id < ID_CLASS_II_max))	
        {

          for(i=0;i< len_CLASSII_cnt ; i++)
          {
              if(even_id==even_class_I_tab[ID_CLASS_I_max+i].id_even)  break;
          }
      
          if(i>= len_CLASSII_cnt)   return;
      
          tab_class.addr_even = even_class_I_tab[ID_CLASS_I_max+i].addr_even;
	   ID = i;              //  二类事件ID    0 - 6
        } 
  else   return;

  
    lnk_save_even_class1_recode(ID,tab_class.addr_even,type);
    
}

void api_pwl_cover_even_class_recode(uint8 even_id, uint8 type )
{	
	CLASS_II_UNIT  data_class2;
	INT8U buftmp[22];
	ST_U32_U08 Time;
	uint8 i ;	
	if(type == START)  
	{   
		if((0x5a != gs_even_fun_var.even_fun_doingflg[even_id])&& (gs_even_fun_var.into_cnt[even_id]>2)) // 未开始
		{
			gs_even_fun_var.even_fun_doingflg[even_id] = 0x5a;
			mem_db_write(ADR_CLASS2FLG_START_E2P+ even_id* LEN_CLASSII_flg,&gs_even_fun_var.even_fun_doingflg[even_id],LEN_CLASSII_flg,MEM_E2P1 );
	 	}
		else 
		{
			gs_even_fun_var.esc_cnt[even_id] =0;		
			if((gs_even_fun_var.into_cnt[even_id]<3)) gs_even_fun_var.into_cnt[even_id] += 1; //	if((0x5a ==gs_even_fun_var.even_fun_doingflg[even_id])&& 
			return;
		}
		mem_read(&data_class2.u16_num.B08[0], ADR_BLOCK163_EVENII_COVER_E2P, LEN_CLASS_II_UNIT, MEM_E2P1);  
		//移动数据 //
		//次数超出不再更新//
		if(data_class2.u16_num.u16<65535)  data_class2.u16_num.u16++;
		for(i=9;i>0;i--)//  开始时间
		{
			Lib_Copy_Str_TwoArry(&data_class2.StartTm[i][0], &data_class2.StartTm[i-1][0], 6);//开始时间滚存
		}
		data_class2.StartTm[0][0] = gs_CurDateTime.Year;
		data_class2.StartTm[0][1] = gs_CurDateTime.Month;
		data_class2.StartTm[0][2] = gs_CurDateTime.Day;
		data_class2.StartTm[0][3] = gs_CurDateTime.Hour;
		data_class2.StartTm[0][4] = gs_CurDateTime.Minute;
		data_class2.StartTm[0][5] = gs_CurDateTime.Second;
	    //结束时间滚存
	    for(i=9;i>0;i--)
		{
			Lib_Copy_Str_TwoArry(&data_class2.EndTm[i][0], &data_class2.EndTm[i-1][0], 6);//开始时间滚存
		}
		CLRWDT();     
	    //结束时间清零//
	   	Lib_Set_String(&data_class2.EndTm[0][0],0x00, 6 );// 结束时间清零	
	    //获取校验和 //
		data_class2.u16_csck = Lib_get_csck_int16u_num(&data_class2.u16_num.B08[0],LEN_CLASS_II_UNIT-2,CHECKWORD);
		//数据保存 //
		mem_write(ADR_BLOCK163_EVENII_COVER_E2P, &data_class2.u16_num.B08[0], LEN_CLASS_II_UNIT, MEM_E2P1);
  }
	else 
	{  
		if( 0x5a !=gs_even_fun_var.even_fun_doingflg[even_id])  // 未开始
		{
		  return;  //已经结束
		} 
    	if(gs_even_fun_var.esc_cnt[even_id] < 3) 
		{
			gs_even_fun_var.into_cnt[even_id] =0;			
			gs_even_fun_var.esc_cnt[even_id]++;		// 写结束标识//

		}	
		else 
		{
			gs_even_fun_var.even_fun_doingflg[even_id] = 0;
			mem_db_write(ADR_CLASS2FLG_START_E2P+ even_id* LEN_CLASSII_flg,&gs_even_fun_var.even_fun_doingflg[even_id],LEN_CLASSII_flg,MEM_E2P1 );
			CLRWDT();     
			mem_read(&data_class2.u16_num.B08[0], ADR_BLOCK163_EVENII_COVER_E2P, LEN_CLASS_II_UNIT, MEM_E2P1);  
			//移动数据 //
			data_class2.EndTm[0][0] = gs_CurDateTime.Year;
			data_class2.EndTm[0][1] = gs_CurDateTime.Month;
			data_class2.EndTm[0][2] = gs_CurDateTime.Day;
			data_class2.EndTm[0][3] = gs_CurDateTime.Hour;
			data_class2.EndTm[0][4] = gs_CurDateTime.Minute;
			data_class2.EndTm[0][5] = gs_CurDateTime.Second;
			//开始时间转移
			buftmp[10] = data_class2.StartTm[0][5];  // 秒
			buftmp[11] = data_class2.StartTm[0][4];
			buftmp[12] = data_class2.StartTm[0][3];
			buftmp[13] = data_class2.StartTm[0][2];
			buftmp[14] = data_class2.StartTm[0][1];
			buftmp[15] = data_class2.StartTm[0][0]; //年
			//结束时间转移
			buftmp[16] = data_class2.EndTm[0][5];// 秒
			buftmp[17] = data_class2.EndTm[0][4];
			buftmp[18] = data_class2.EndTm[0][3];
			buftmp[19] = data_class2.EndTm[0][2];
			buftmp[20] = data_class2.EndTm[0][1];
			buftmp[21] = data_class2.EndTm[0][0];// 年
			//计算秒数//
			GetTotalTime(&buftmp[0]);
			//秒数累加//
			Lib_Copy_Str_TwoArry(&Time.B08[0], &buftmp[4], 4);//开始时间滚存
			//持续时间累加，超出不清零//
			if(0xFFFFFFFF-data_class2.accumTime.u32>Time.u32)  data_class2.accumTime.u32 += Time.u32;
			//获取校验和 //
			data_class2.u16_csck = Lib_get_csck_int16u_num(&data_class2.u16_num.B08[0],LEN_CLASS_II_UNIT-2,CHECKWORD);
			CLRWDT();     
			//数据保存 //
			mem_write(ADR_BLOCK163_EVENII_COVER_E2P, &data_class2.u16_num.B08[0], LEN_CLASS_II_UNIT, MEM_E2P1);
			gs_even_fun_var.esc_cnt[even_id] =0; 
			gs_even_fun_var.into_cnt[even_id] =0;
		}		
	}	
}


/*****************************************************************************
** Function name    :api_measure_deal_pre_second
**
** Description         :每秒调用的测量函数
**
** Parameters         :NONE   adr 卷页地址 
**
** Returned value   :NONE   type 发生类型   1 开始  0x55  进行时候  0xFF 结束   
**                                      ID   只有二类时间有效，前期处理 0 - 6
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void lnk_save_even_class1_recode(uint8 ID, uint16 adr , uint8 type)
{
    CLASS_I_UNIT   data_class1;
    CLASS_II_UNIT  data_class2;
    INT8U buftmp[22];
    ST_U32_U08 Time;
    uint8 i ;

	
    if(adr < ADR_BLOCK_min_EVENI_E2P)  return;
	
    if(adr <=ADR_BLOCK_max_EVENI_E2P)
    {
	// 一类事件处理 // 
    mem_read(&data_class1.u16_num.B08[0], adr, LEN_CLASS_I_UNIT, MEM_E2P1);  
    //移动数据 //
    if(data_class1.u16_num.u16<65535) data_class1.u16_num.u16++;
    for(i=9;i>0;i--)
    {
        Lib_Copy_Str_TwoArry(&data_class1.dataTime[i][0], &data_class1.dataTime[i-1][0], 6);
    }
	
    data_class1.dataTime[0][0]=gs_CurDateTime.Year;
    data_class1.dataTime[0][1]=gs_CurDateTime.Month;
    data_class1.dataTime[0][2]=gs_CurDateTime.Day;
    data_class1.dataTime[0][3]=gs_CurDateTime.Hour;
    data_class1.dataTime[0][4]=gs_CurDateTime.Minute;
    data_class1.dataTime[0][5]=gs_CurDateTime.Second;
    //获取校验和 //
    data_class1.u16_csck = Lib_get_csck_int16u_num(&data_class1.u16_num.B08[0],LEN_CLASS_I_UNIT-2,CHECKWORD);

    //数据保存 //
    mem_write(adr, &data_class1.u16_num.B08[0], LEN_CLASS_I_UNIT, MEM_E2P1);
    return ;
    }

	//  二类事件发生处理// 
    if((adr >=ADR_BLOCK_min_EVENII_E2P) && (adr <=ADR_BLOCK_max_EVENII_E2P))
    {
      if(type == START)  
      {
        gs_even_fun_var.esc_cnt[ID]=0;  // 事件保持时间
        //  读取延时时间参数更新里读取//
//		    if(gs_sys_globaL_var.work_mode != SLEEP_MODE)
			  mem_read(&gs_even_var.even_cnt[ID],ADR_CLASS2CNT_START_E2P+ ID* LEN_CLASSII_cnt,LEN_CLASSII_cnt,MEM_E2P1);
		    if((gs_even_fun_var.into_cnt[ID]< gs_even_var.even_cnt[ID]))//&&(gs_sys_globaL_var.work_mode != SLEEP_MODE)
		    {
                  gs_even_fun_var.into_cnt[ID]++;  // 事件保持时间
		    }
		    else 
	      {
         gs_even_fun_var.into_cnt[ID]+=gs_even_var.even_cnt[ID];  // 事件保持时间
			   mem_read(&gs_even_fun_var.even_fun_doingflg[ID],ADR_CLASS2FLG_START_E2P+ ID* LEN_CLASSII_flg,LEN_CLASSII_flg,MEM_E2P1);
			   CLRWDT();     
       if( ID ==1 ) 
				 CLRWDT(); 
			 if(0x5a!=gs_even_fun_var.even_fun_doingflg[ID])  // 未开始
	 	      {
 	 			gs_even_fun_var.even_fun_doingflg[ID] = 0x5a;
 			    mem_db_write(ADR_CLASS2FLG_START_E2P+ ID* LEN_CLASSII_flg,&gs_even_fun_var.even_fun_doingflg[ID],LEN_CLASSII_flg,MEM_E2P1 );
	 		  }
 	           else 
 	         return;  // 处于发生状态

			mem_read(&data_class2.u16_num.B08[0], adr, LEN_CLASS_II_UNIT, MEM_E2P1);  
			//移动数据 //
			//次数超出不再更新//
			if(data_class2.u16_num.u16<65535)  data_class2.u16_num.u16++;
			for(i=9;i>0;i--)//  开始时间
			{
			Lib_Copy_Str_TwoArry(&data_class2.StartTm[i][0], &data_class2.StartTm[i-1][0], 6);//开始时间滚存
			}
			data_class2.StartTm[0][0] = gs_CurDateTime.Year;
			data_class2.StartTm[0][1] = gs_CurDateTime.Month;
			data_class2.StartTm[0][2] = gs_CurDateTime.Day;
			data_class2.StartTm[0][3] = gs_CurDateTime.Hour;
			data_class2.StartTm[0][4] = gs_CurDateTime.Minute;
			data_class2.StartTm[0][5] = gs_CurDateTime.Second;
                     //结束时间滚存
            for(i=9;i>0;i--)
			{
			Lib_Copy_Str_TwoArry(&data_class2.EndTm[i][0], &data_class2.EndTm[i-1][0], 6);//开始时间滚存
			}
		    CLRWDT();     

            //结束时间清零//
   			Lib_Set_String(&data_class2.EndTm[0][0],0x00, 6 );// 结束时间清零	


			//获取校验和 //
			data_class2.u16_csck = Lib_get_csck_int16u_num(&data_class2.u16_num.B08[0],LEN_CLASS_II_UNIT-2,CHECKWORD);

			//数据保存 //
			mem_write(adr, &data_class2.u16_num.B08[0], LEN_CLASS_II_UNIT, MEM_E2P1);
		  }
           	}
	   else
	    {
		  if(gs_even_fun_var.into_cnt[ID] > gs_even_var.even_cnt[ID])
		  {
		   if(gs_even_fun_var.esc_cnt[ID] < gs_even_var.even_cnt[ID])   gs_even_fun_var.esc_cnt[ID]++;
		   else 
		   {
		       gs_even_fun_var.esc_cnt[ID] =0;
			gs_even_fun_var.into_cnt[ID] =0;
		      //  读取2类数据状态//
		      // gs_even_fun_var.into_cnt[ID]+=gs_even_var.even_cnt[ID];  // 事件保持时间
			mem_read(&gs_even_fun_var.even_fun_doingflg[ID],ADR_CLASS2FLG_START_E2P+ ID* LEN_CLASSII_flg,LEN_CLASSII_flg,MEM_E2P1);
		     if( 0 ==gs_even_fun_var.even_fun_doingflg[ID])  // 未开始
		      {
		          return;  //已经结束
		      }

                    // 写结束标识//
			gs_even_fun_var.even_fun_doingflg[ID] = 0;
			mem_db_write(ADR_CLASS2FLG_START_E2P+ ID* LEN_CLASSII_flg,&gs_even_fun_var.even_fun_doingflg[ID],LEN_CLASSII_flg,MEM_E2P1 );
			CLRWDT();     
			 mem_read(&data_class2.u16_num.B08[0], adr, LEN_CLASS_II_UNIT, MEM_E2P1);  
			//移动数据 //
			data_class2.EndTm[0][0] = gs_CurDateTime.Year;
			data_class2.EndTm[0][1] = gs_CurDateTime.Month;
			data_class2.EndTm[0][2] = gs_CurDateTime.Day;
			data_class2.EndTm[0][3] = gs_CurDateTime.Hour;
			data_class2.EndTm[0][4] = gs_CurDateTime.Minute;
			data_class2.EndTm[0][5] = gs_CurDateTime.Second;
	        //开始时间转移
			buftmp[10] = data_class2.StartTm[0][5];  // 秒
			buftmp[11] = data_class2.StartTm[0][4];
			buftmp[12] = data_class2.StartTm[0][3];
			buftmp[13] = data_class2.StartTm[0][2];
			buftmp[14] = data_class2.StartTm[0][1];
			buftmp[15] = data_class2.StartTm[0][0]; //年

			//结束时间转移
			buftmp[16] = data_class2.EndTm[0][5];// 秒
			buftmp[17] = data_class2.EndTm[0][4];
			buftmp[18] = data_class2.EndTm[0][3];
			buftmp[19] = data_class2.EndTm[0][2];
			buftmp[20] = data_class2.EndTm[0][1];
			buftmp[21] = data_class2.EndTm[0][0];// 年
			//计算秒数//
			GetTotalTime(&buftmp[0]);
			//秒数累加//
			Lib_Copy_Str_TwoArry(&Time.B08[0], &buftmp[4], 4);//开始时间滚存
 	  	    //持续时间累加，超出不清零//
			if(0xFFFFFFFF-data_class2.accumTime.u32>Time.u32)  data_class2.accumTime.u32 += Time.u32;
			//获取校验和 //
			data_class2.u16_csck = Lib_get_csck_int16u_num(&data_class2.u16_num.B08[0],LEN_CLASS_II_UNIT-2,CHECKWORD);

		    CLRWDT();     

			//数据保存 //
			mem_write(adr, &data_class2.u16_num.B08[0], LEN_CLASS_II_UNIT, MEM_E2P1);

		  }
		  }
		else 
		{
			gs_even_fun_var.esc_cnt[ID] =0;
			gs_even_fun_var.into_cnt[ID] =0;
		}
	}

}
	else  return;   // 不存在事件

}


/*****************************************************************************
** Function name    :api_measure_deal_pre_second
**
** Description         :每秒调用的测量函数
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_deal_even_class1_recode(uint8 even_id, uint8 type)
{
    uint8 i,ID;

    CLASS_I_TAB  tab_class;

//    for(i=0;i<(dim(even_class_I_tab)); i++)
//    {
//        if(even_id==even_class_I_tab[i].id_even)  break;
//    }
//    
//    if(i>=(dim(even_class_I_tab)))   return;
	if(even_id < ID_CLASS_I_max ) //判为1类事件
    {
		for(i=0;i< ID_CLASS_I_max ; i++)
		{
			if(even_id==even_class_I_tab[i].id_even)  break;
		}
		
		if(i>=ID_CLASS_I_max)   return;
		
		tab_class.addr_even = even_class_I_tab[i].addr_even;
		ID = even_id ;        // 一类事件ID  
	}
	else if( (even_id >= ID_CLASS_II_min)&&(even_id < ID_CLASS_II_max))	//判别为2类事件
	{
		for(i=0;i< len_CLASSII_cnt ; i++)
		{
			if(even_id==even_class_I_tab[ID_CLASS_I_max+i].id_even)  break;
		}
		if(i>= len_CLASSII_cnt)   return;
		tab_class.addr_even = even_class_I_tab[ID_CLASS_I_max+i].addr_even;
		ID = i;              //  二类事件ID    0 - 6
	} 
	else   return;

//    tab_class1.addr_even = even_class_I_tab[i].addr_even;

    lnk_save_even_class1_recode(ID,tab_class.addr_even,type);
    
}



/*****************************************************************************
** Function name    :api_measure_deal_pre_second
**
** Description         :每秒调用的测量函数
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_clr_even_by_comm(void)
{
   uint8 i;
    CLASS_I_UNIT   data_class1;
    CLASS_II_UNIT  data_class2;

    Lib_Set_String(&data_class1.u16_num.B08[0], 0, LEN_CLASS_I_UNIT);
    Lib_Set_String(&data_class2.u16_num.B08[0], 0, LEN_CLASS_II_UNIT);
//    gs_sys_globaL_var.sys_e2_err_flg=0;
     Lib_Set_String(&gs_even_fun_var.esc_cnt,0,sizeof(EVEN_FUN_VAR));

     mem_db_write(ADR_CLASS2FLG_START_E2P ,&gs_even_fun_var.even_fun_doingflg[0],len_CLASSII_cnt,MEM_E2P1 );   

    data_class1.u16_csck = Lib_get_csck_int16u_num(&data_class1.u16_num.B08[0],LEN_CLASS_I_UNIT-2,CHECKWORD);
    data_class2.u16_csck = Lib_get_csck_int16u_num(&data_class2.u16_num.B08[0],LEN_CLASS_II_UNIT-2,CHECKWORD);
	
    for(i=0;i<(dim(even_class_I_tab)); i++)
    {
       CLRWDT();
	if(i<ID_CLASS_I_max) mem_write(even_class_I_tab[i].addr_even, &data_class1.u16_num.B08[0], LEN_CLASS_I_UNIT, MEM_E2P1);
	else mem_write(even_class_I_tab[i].addr_even, &data_class2.u16_num.B08[0], LEN_CLASS_II_UNIT, MEM_E2P1);
       CLRWDT();
    }
    
}

void GetTotalTime(INT8U *buftmp) 
{
    union Union_DWordDef temp1,temp2;
    //开始和结束的月日都不可能为0
    if( (buftmp[13] == 0) || (buftmp[14] == 0) || (buftmp[19] == 0) || (buftmp[20] == 0) )
    {
        temp2.UDWORD= 0;
        temp1.UDWORD = 0;
    }  
    else   
    {
        temp2.UDWORD = Lib_GetGmSec( &buftmp[10] );//开始时间的秒数
        temp1.UDWORD = Lib_GetGmSec( &buftmp[16] );//结束时间的秒数
        /////夏时制判断////////////////////////////////////////////////////////////
		//
        /////////////////////////////////////////////////////////////////////////////
    }
	//得到此次的累计时间，放到temp1			
    if( temp1.UDWORD > temp2.UDWORD )
    {
        temp1.UDWORD -= temp2.UDWORD;
    }
    else
    {
        temp1.UDWORD = 0;
    }
	
	Lib_Copy_Str_TwoArry(&buftmp[4], &temp1.BYTE[0], 4 );
}

/***************************************************************
*    END
****************************************************************/

