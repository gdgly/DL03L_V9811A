/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Lib_myTimer.c
**Author: maji
**date: 
**description: c code for general library function 
**note: memer type  DJ04A
**--------------------Version History -------------------------------------
** NO.	Date        		Ver    		By     			Description 
**==============================================================
** 1		2014-07-08  		0.1  			sosomj   			1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>


/****************************************************************
Function:		void Lib_Delay_Nop(uchar cnt)
Description:	��ʱCNT��NOP() 
Input:
Parameters:     
Returns:                                
Others:         
****************************************************************/
void Lib_Delay_Nop(INT8U cnt)
{
	while(cnt--)
	{
		NOP();
	}
}

/****************************************************************
Function:   	void Lib_Delay2us(uint cnt)    
Description: 	CNT��2us��ʱ
Input:		cnt
Parameters:     
Returns:                                
Others:	��������: 8MHz   
****************************************************************/
void Lib_Delay_2us(INT8U cnt)  
{
	 uint8 i;
	 
	while(cnt--)
	{
	      NOP();
            NOP();
	}	
}


/****************************************************************
Function:   	void Lib_Delay_ms(uint cnt)   
Description: 	CNT��1ms��ʱ
Input:		cnt :��ʱ��Ӧ��ms
Parameters:     
Returns:                                
Others:	��������: 4.096Mhz  
****************************************************************/
void Lib_Delay_ms(INT16U cnt)
{
   INT16U i;
   INT8U j;
	 
   for(i=cnt;i>0;i--)
   {
        for (j=0;j<230;j++)
        {
            NOP();
        }
   }  
}

/****************************************************************
Function:   	void Lib_Delay_sec(uint cnt)  
Description: 	CNT��s��ʱ
Input:		cnt :��ʱ��Ӧ��s
Parameters:     
Returns:                                
Others:	��������: 8MHz   
****************************************************************/
void Lib_Delay_sec(INT8U cnt)
{
	INT8U i;
	for(i=0;i<cnt;i++)
	{
		CLRWDT();
		Lib_Delay_ms(1000);
	}
}



/****************************************************************
Function:   	void SystemDelay(uint cnt)  
Description: 	����΢��˾�ṩ��ϵͳ��ʱ����,ÿ��ѭ����ʱԼ1ms
Input:		
Parameters:     
Returns:                                
Others:	
****************************************************************/
void Lib_SystemDelay(INT16U t)
{
	INT16U i;
	while(t--)
	{
		for (i = 0;i < 400;i++)
		  ;
		CLRWDT();
	}
}

/***************************************************************
*    END
****************************************************************/


