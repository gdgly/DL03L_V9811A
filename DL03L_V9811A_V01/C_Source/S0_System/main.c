/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name          : main.c
**Author		: maji
**date           : 2016-04-20
**description	: main ������C�ļ�
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>

uint8  debug_tmp1;

/****************************************************************
Function:  		void main(void)   
Description: 		ϵͳ������
Input:
Parameters:     
Returns:                                
Others:         
****************************************************************/
void main(void)
{
    NOP();
    CLRWDT();     
    DisableINT();    				// disable interrupt function  //
    Proc_Initialize_systerm_reset();  
    EnableINT();
    NOP();

    while(1)
    {
        CLRWDT();   // �忴�Ź�//
                               
       //ϵͳ�ؼ�����ѭ�������� //
        Proc_Check_System_Pre_Cycle();

        if(gs_sys_run.back_fg&BIT0_FONT_FG_10MS)
        {
            gs_sys_run.back_fg &= ~BIT0_FONT_FG_10MS;
            Proc_handl_tou_10ms();
        }

        if(gs_sys_run.back_fg&BIT1_BACK_FG_RTC)
        {
            gs_sys_run.back_fg &= ~BIT1_BACK_FG_RTC;
            Proc_handl_tou_1s();
        }

 /*       if(gs_sys_run.back_fg&BIT2_BACK_DIS_KEY)
        {
            gs_sys_run.back_fg &= ~BIT2_BACK_DIS_KEY;
            api_handl_dis_key();
            api_updated_LCDDisplayPixel_per_second();
        }
*/        
	 // �ϵ�״̬�µĵ�Դ������  //   
       Proc_judge_Power_down_process();      

    }

}




/***************************************************************
*    END
****************************************************************/

