/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Proc_System_Check.c
**Author		: maji
**date			: 2016-04-20
**description	: ϵͳ��ѭ���Լ촦�����C����
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#include <MyIncludes_H.h>

SYS_CKECK_VAR gs_sys_check_var;

/****************************************************************
Function:   		void SysInitialize(void)  
Description: 		ϵͳ�ϵ�/��λ��ʼ������ 
Input:			no
Parameters:     	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_Check_System_Pre_Cycle(void)
{


	    
}


//void Proc_Check_COVER_Pre_sec(void)
//{
//    if(Judge_ERR_COVER_key()==TRUE)
//    {
//        if(gs_sys_check_var.tmr_closeCover<3)
//        {
//            gs_sys_check_var.tmr_closeCover++;
//            if(gs_sys_check_var.tmr_closeCover>=3)
//            {
////               if((gs_sys_globaL_var.meter_factory_status !=METER_FACTORY_MARK))
//                {
//                   if(gs_sys_check_var.flg_openCover !=TRUE)
//                   { 
//						api_deal_even_class1_recode(ID_CLASS_II_COVER,START);
//						gs_sys_check_var.flg_openCover =TRUE ;   
//									
//                   }
//                }       
//            }
//        } 
//    } 
//	else
//    {
//        if(gs_sys_check_var.tmr_closeCover>0)  gs_sys_check_var.tmr_proKey--;
//        if(gs_sys_check_var.tmr_closeCover == 0) 
//		{ 
//			if(gs_sys_check_var.flg_openCover ==TRUE)
//			{ 
//				api_deal_even_class1_recode(ID_CLASS_II_COVER,END );
//				gs_sys_check_var.flg_openCover =FALSE ;   
//			}	
//					
//        }      
//    }
//}

/****************************************************************
Function:   		void SysInitialize(void)  
Description: 		ϵͳ�ϵ�/��λ��ʼ������ 
Input:			no
Parameters:     	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_Check_PROKEY_Pre_sec(void)
{
 //   if((Judge_PRO_key()==TRUE) &&(Judge_ERR_ADJ_key()==TRUE))
    if((Judge_ERR_ADJ_key()==TRUE))      // ����Ҫ���޸�Ϊ1���̽ӵ�У��mj 2016-06-14 //
    {
        if(gs_sys_check_var.tmr_proKey<3)
        {
            gs_sys_check_var.tmr_proKey++;
            if(gs_sys_check_var.tmr_proKey>=3)
            {
                if((gs_sys_globaL_var.meter_factory_status ==METER_FACTORY_MARK))
                {
                    if(gs_sys_check_var.flg_proKey !=TRUE)
                    {
                        Hardware_AdjustDiv_Sub();
                        gs_sys_check_var.flg_proKey =TRUE ;       
                    }
                }
            }       
        }
    } 
    else
    {
        if(gs_sys_check_var.tmr_proKey>0)  gs_sys_check_var.tmr_proKey--;
        if(gs_sys_check_var.tmr_proKey == 0)  gs_sys_check_var.flg_proKey =FALSE;
    }      
}

/*****************************************************************************
** Function name    :Proc_init_tou_var
**
** Description         :��ȡ��ǰRTC ʱ��ȫ�ֱ�������  
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void Proc_init_Check_var(void)
{
    Lib_Set_String((uint8*)&gs_sys_check_var,0,sizeof(SYS_CKECK_VAR));      
}


/*******************************************************************************************
** ��������: CheckPOWERUP
** ��������: ���VDCIN��ȷ����ǰ�Ƿ����ⲿ��Դ����
** �������: 
** �������: FALSE-���磻TRUE -���е�;
** ˵��    : 
*******************************************************************************************/
uint8 CheckPOWERUP(void)
{
uint8 i;

    for(i = 0; i < 30; i++)	   
    {
         #if(MCU_TYPE == MCU_G80F92X)   // ��ӱоƬ //
   	   if((LPDCON & Bin(01000000)) == Bin(01000000) )     //bit6 :1>1.2V 
         #endif
    
         #if(MCU_TYPE == MCU_V98XX)   // ��оƬ //
   	    if((Systate&0x03)==0x01)
         #endif

	      break;
    }	
	if(i < 25)
	   return TRUE;		 //�е� 
	else
	  return FALSE;		 //û��

} 





/***************************************************************
*    END
****************************************************************/

