/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: IEC62056_21.c
**Author		: maji
**date			: 2016-04-21 
**description	: IEC62056-21ͨѶЭ����غ�������C�ļ�
**note			: ͨ�ó���
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-21   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#include <MyIncludes_H.h>




//-------------------------------------------------------------------------------//
//  Function:             void dl645_data_encrypt(INT8U* sptr,INT8U len )
//  Description:          DL645����������ܺ���
//  Parameters:          unsigned char* sptr: ��Ҫ�������ݵ��׵�ַ
//                            INT8U len:   ��Ҫ�������ݵĳ���
//  Returns:               ��
//  Others:                1������DL/T645-1997/2007
//                            2 
//  author:                 sosomj         2009.02.16      V01.00
//-------------------------------------------------------------------------------//
INT8U IEC_Comm_Request_Cmd_Judge(INT8U* sptr,INT8U len,INT8U* id_ptr,INT8U meter_id_lenth)
{
 INT8U i;

     if(len == IEC_START_LENTH05 )
     {
         if( (*(sptr+0)) !=  '/' )    return FALSE;
	  if( (*(sptr+1)) !=  '?' )     return FALSE;
	  if( (*(sptr+2)) !=  '!' )     return FALSE;
	  if( (*(sptr+3)) !=  CR )     return FALSE;
        if( (*(sptr+4)) !=  LF )     return FALSE;
	  return TRUE;
     }
	 else
	 {
		if( (*(sptr+0)) !=  '/' )    return FALSE;
		if( (*(sptr+1)) !=  '?' )     return FALSE;
		for(i=0;i<meter_id_lenth;i++)		//��ŶԱ�
		{
			if( (*(sptr+2+i)) !=  (*(id_ptr+i) ))	 
			{
				return FALSE;
			}
		}
		if( (*(sptr+2+meter_id_lenth)) !=  '!' ) 		return FALSE;
		if( (*(sptr+3+meter_id_lenth)) !=  CR )		return FALSE;
		if( (*(sptr+4+meter_id_lenth)) !=	LF )	 	return FALSE;

		return TRUE;
	 }

     return FALSE;	 
	 
}



//-------------------------------------------------------------------------------//
//  Function:             void dl645_data_encrypt(INT8U* sptr,INT8U len )
//  Description:          DL645����������ܺ���
//  Parameters:          unsigned char* sptr: ��Ҫ�������ݵ��׵�ַ
//                            INT8U len:   ��Ҫ�������ݵĳ���
//  Returns:               ��
//  Others:                1������DL/T645-1997/2007
//                            2 
//  author:                 sosomj         2009.02.16      V01.00
//-------------------------------------------------------------------------------//
INT8U IEC_Comm_Acknowledgement_Cmd_Judge(INT8U* sptr,INT8U len)
{
     if(len != 6 )  return FALSE;

     if( (*(sptr+0)) != ACKCOM )    return FALSE;
     if( (*(sptr+1)) !=  '0' )     return FALSE;
     if( ((*(sptr+2))  > 0x36) ||((*(sptr+2))  < 0x30))     return FALSE;   // '0' ~'6' ,300bps ~19200bps //
     if( (*(sptr+3) !=  '1' )&&(*(sptr+3) !=  '0' ))     return FALSE;
     if( (*(sptr+4)) !=  CR )     return FALSE;
     if( (*(sptr+5)) !=  LF )     return FALSE;

     return TRUE;
	 
}


//-------------------------------------------------------------------------------//
//  Function:             INT8U IEC_Comm_Command_Cmd_Judge(INT8U* sptr,INT8U len)
//  Description:          IEC�Ĳ��������������
//  Parameters:          unsigned char* sptr: ͨѶ�������׵�ַ
//                            INT8U len:   ��Ч���ݳ���
//  Returns:               �ɹ� or ʧ��
//  Others:                1
//                            2 
//  author:                 sosomj         
//-------------------------------------------------------------------------------//
INT8U IEC_Comm_Command_Cmd_Judge(INT8U* sptr,INT8U len)
{
 INT8U  u8_a[9];

     if( (*(sptr+0)) != SOH)         return FALSE;
     if( (*(sptr+len-2)) != ETX)    return FALSE;

     if( (*(sptr+len-1)) != Get_Bcc_Chk(sptr, 1, len-2))    return FALSE;


        u8_a[0] =*(sptr+1);
	 u8_a[1] =*(sptr+2);
	 u8_a[2] =*(sptr+3);
	 u8_a[3] =*(sptr+4);
	 u8_a[4] =*(sptr+5);
	 u8_a[5] =*(sptr+6);
	 u8_a[6] =*(sptr+7);
	 u8_a[7] =*(sptr+8);
	 u8_a[8] =*(sptr+9);
	 
     switch(*(sptr+1))
     {
         case 'P' :                      //  ����ָ�� //
	         return(IEC_Cmd_Password_Deal(sptr));
		 break;

         case 'R' :                    // ��ָ�� //
              return(IEC_Cmd_Read_Deal(sptr));
		 break;		

         case 'W' :                   //  дָ�� //
              return(IEC_Cmd_Write_Deal(sptr,len));
		 break;	
		 
         
         case 'B' :                   //  ��ָֹ�� //
              //return(IEC_Cmd_Break_Deal(sptr));
              gs_uart_iec_app_var[g_ch_comm].err_flg |= FRAME_ERROR;   //��ֹ����֡��Ӧ��ֱ�Ӹ�λ���в�  //	
              return FALSE;
		 break;	

         //case 'E' :                   //  ִ��ָ�� //
	//		return(IEC_Execute_Deal(sptr));
	//	 break;	

         default:
		 gs_uart_iec_app_var[g_ch_comm].err_flg |= FRAME_ERROR;   //֡������Ҫ��λ  //	
              return FALSE;
		 break;	
		 
     }
	 
     return TRUE;
	 
}

	
//-------------------------------------------------------------------------------//
//  Function:            void Get_Start_Cmd_Answer(INT8U* sptr,INT8U len,INT8U* info_ptr)
//  Description:           ��ʼ���������ɹ�Ӧ�����ݴ���
//  Parameters:          INT8U* sptr : �ظ�֡�׵�ַ
//                            INT8U len  :���INFO���ݳ���
//                            INT8U* info_ptr: ���INFO�����׵�ַ
//  Returns:               ��
//  Others:                1
//                            2 
//  author:                 sosomj         2009.02.16      V01.00
//-------------------------------------------------------------------------------//
void Get_IEC_Comm_Request_Cmd_Answer(INT8U* sptr,INT8U len,INT8U* info_ptr)
{
  INT8U i;
  
      (*(sptr+0)) =  '/' ;
	  	
      for(i=0;i<len;i++)
      {
           (*(sptr+i+1)) =   (*(info_ptr+i));  
      }
	  
      *(sptr+1+len)=  CR ;   
      *(sptr+1+len+1) =  LF;
	 
}

//-------------------------------------------------------------------------------//
//  Function:            void Get_IEC_Comm_Operand_Answer(INT8U* sptr,INT8U len,INT8U* info_ptr)
//  Description:           ��ʼ���������ɹ�Ӧ�����ݴ���
//  Parameters:          INT8U* sptr : �ظ�֡�׵�ַ
//                            INT8U len  :���INFO���ݳ���
//                            INT8U* info_ptr: ���INFO�����׵�ַ
//  Returns:               ��
//  Others:                1
//                            2 
//  author:                 sosomj         2009.02.16      V01.00
//-------------------------------------------------------------------------------//
void Get_IEC_Comm_Operand_Answer(INT8U* sptr,INT8U len,INT8U* info_ptr)
{
  INT8U i;
  
      (*(sptr+0)) =  SOH;
	(*(sptr+1)) =  'P' ;      
	(*(sptr+2)) =  '0' ;
	(*(sptr+3)) =  STX;  
	  	
      for(i=0;i<len;i++)
      {
           (*(sptr+i+4)) =   (*(info_ptr+i));  
      }
	  
      *(sptr+len+4)=  ETX;   
      *(sptr+len+5) =  Get_Bcc_Chk(sptr,1, (len+4));    // BCC check get //
	 
}


//-------------------------------------------------------------------------------//
//  Function:             void Get_Error_Answer(INT8U* sptr)
//  Description:          
//  Parameters:          unsigned char* sptr: ��Ҫ�������ݵ��׵�ַ
//                            
//  Returns:               ��
//  Others:                1
//                            2 
//  author:                 sosomj         
//-------------------------------------------------------------------------------//
void Get_Error_Answer(INT8U* sptr)
{
      (*(sptr+0)) =  NAK;
}



//-------------------------------------------------------------------------------//
//  Function:             void Get_ACK_Answer(INT8U* sptr)
//  Description:          
//  Parameters:          unsigned char* sptr: ��Ҫ�������ݵ��׵�ַ
//                            
//  Returns:               ��
//  Others:                1
//                            2 
//  author:                 sosomj         
//-------------------------------------------------------------------------------//
void Get_ACK_Answer(INT8U* sptr)
{
      (*(sptr+0)) = ACKCOM;
}


//-------------------------------------------------------------------------------//
//  Function:             INT8U Get_Bcc_Chk(INT8U* yourBuf, INT8U StartID, INT8U EndID)
//  Description:          IEC ��Լ��BCCУ��
//  Parameters:          INT8U* yourBuf  ͨѶ���������׵�ַ
//                            
//  Returns:               ��
//  Others:                1������DL/T645-1997/2007
//                            2 
//  author:                 sosomj         2009.02.16      V01.00
//-------------------------------------------------------------------------------//
INT8U Get_Bcc_Chk(INT8U* yourBuf, INT8U StartID, INT8U EndID)
{
    INT8U i;
    INT8U tmp;

    tmp=0x00;
    for(i=StartID;i<=EndID;i++)
    {
        tmp ^= *(yourBuf+i);
    }
    return tmp;
}






/***************************************************************
*    END
****************************************************************/

