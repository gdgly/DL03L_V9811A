/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_E2P_FM24c16.c
**Author		: maji
**date			: 2016-04-20
**description	: c code for read&Write FM24C16(����)
**note			:  Driver code for GENERAL
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-20   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>


/*******************************************************************************************
** ��������: Read_EEPROM_Page_Sub
** ��������: ��EEPROM��ȡ�����ֽ� ����1��PAGE�ķ�Χ�ڲ�����
** �������: *Buf:Ŀ���RAM�����׵�ַָ��
**           Addr:Դ����EEPROM�洢��ַ
**           Len: ��ȡ���ֽ���
** �������: TRUE-��ȡ��ȷ   FALSE-��ȡʧ��
** ˵��    : ��1��PAGE�ķ�Χ�ڲ���ʹ�ã���˫���ȶ��ߴ����
*******************************************************************************************/
uint8 Read_EEPROM_Page_Sub(uint8 *Buf,uint16 Addr,uint8 Len)
{
	uint8 NewWrCmd,NewRdCmd;
	#if (EE_Chip>=EE24XX08 )
	uint8 Page;
	#endif
	uint8 err_cnt=0;
	   

	#if (EE_Chip>=EE24XX08 )

	Page=HIBYTE(Addr);
	Page=Page&Bin(00000111);
	Page=Page<<1;
	NewWrCmd=WRITE_EEPROM_CMD|Page;
	NewRdCmd=READ_EEPROM_CMD|Page;
	#else
	NewWrCmd=WRITE_EEPROM_CMD;
	NewRdCmd=READ_EEPROM_CMD;
	#endif

	do
	{
		E2p_Stop_i2c();
		err_cnt++;
		if(err_cnt>10)	return FALSE;   // ����10�β��ܳɹ��򷵻�ʧ�ܱ�ʶ//
		E2p_Start_i2c();
	}while (E2p_TxByte_i2c(NewWrCmd)!=TRUE);

	#if (EE_Chip>=EE24XX08 )
	if(E2p_TxByte_i2c(LOBYTE(Addr))!=TRUE) return FALSE;
	#else
	if(E2p_TxByte_i2c(HIBYTE(Addr))!=TRUE) return FALSE;
	if(E2p_TxByte_i2c(LOBYTE(Addr))!=TRUE) return FALSE;
	#endif

	E2p_Start_i2c();                                           //�ط���ʼ����  //

	if(E2p_TxByte_i2c(NewRdCmd)!=TRUE) return FALSE;

	while(Len--)
	{
		*Buf = E2p_RxByte_i2c((Len==0)? FALSE: TRUE);		//������������  //
		Buf++;
	}
	E2p_Stop_i2c();
	return TRUE;
}

/*******************************************************************************************
** ��������: Write_EEPROM_Page_Sub
** ��������: ��EEPROMд�������ֽ� ����1��PAGE�ķ�Χ�ڲ�����
** �������: addr:Ŀ������EEPROM�洢��ַ
**           *buf:Դ����RAM�����׵�ַָ��
**           len: д����ֽ���
** �������: TRUE-д����ȷ   FALSE-д��ʧ��
** ˵��    : ��1��PAGE�ķ�Χ�ڲ���ʹ�ã���д������ȶ��ߴ����
*******************************************************************************************/
uint8 Write_EEPROM_Page_Sub(uint16 Addr,uint8 *Buf,uint8 Len)
{
	uint8 NewWrCmd,NewRdCmd;

	#if (EE_Chip>=EE24XX08 )
	uint8 Page;
	#endif
	uint8 err_cnt=0;

	#if (EE_Chip>=EE24XX08 )
	Page=HIBYTE(Addr);
	Page=Page&Bin(00000111);
	Page=Page<<1;
	NewWrCmd=WRITE_EEPROM_CMD|Page;
	NewRdCmd=READ_EEPROM_CMD|Page;
	#else
	NewWrCmd=WRITE_EEPROM_CMD;
	NewRdCmd=READ_EEPROM_CMD;
	#endif

	Disable_WP();
	do
	{
		E2p_Stop_i2c();
		err_cnt++;
		if(err_cnt>10)	return FALSE;   // ����10�β��ܳɹ��򷵻�ʧ�ܱ�ʶ//
		E2p_Start_i2c();
	}while (E2p_TxByte_i2c(NewWrCmd)!=TRUE);

	#if (EE_Chip>=EE24XX08 )
	if(E2p_TxByte_i2c(LOBYTE(Addr))!=TRUE) return FALSE;
	#else
	if(E2p_TxByte_i2c(HIBYTE(Addr))!=TRUE) return FALSE;
	if(E2p_TxByte_i2c(LOBYTE(Addr))!=TRUE) return FALSE;
	#endif

	do
	{
		if (E2p_TxByte_i2c(*Buf)!=TRUE )
		{
			Enable_WP();
			return FALSE;
		}
		Buf++;
		Addr++;
		Len--;
	}while (Len != 0) ;

	E2p_Stop_i2c();
	#ifdef _E2P_TYPE_AT24
	Lib_Delay_ms(5);   //  ��ͨE2Pд�����Ҫ��ʱ5ms//			
	#endif
	Enable_WP();

	return TRUE;
}



/*******************************************************************************************
** ��������: Read_EEPROM_Page
** ��������: ��EEPROM��ȡ�����ֽ� ����1��PAGE�ķ�Χ�ڲ�������˫���ȶԣ�
** �������: * u8p_dst:Ŀ������ָ��
**           u16_src:  Դ����EEPROM�洢��ַ
**           u8_len: ��ȡ���ֽ���
** �������: TRUE-��ȡ��ȷ   FALSE-��ȡʧ��
** ˵��    : ��1��PAGE�ķ�Χ�ڲ���ʹ�ã��߱�˫���ȶ��ߴ����
**           ʧ�����������������3��
*******************************************************************************************/
uint8 Read_EEPROM_Page(uint8* u8p_dst, uint16 u16_src, uint8 u8_len)
{
 uint8 data00[EE_PageMask];
 uint8 i;
  
	if((u8_len<= 0)||(u8_len>EE_PageMask))     //if len is illegal,program run with dead circle
	{
		return(FALSE); 
	}
	for(i=0;i<3;i++)                                                 //read and compare, if error,repeat 6 times.
	{
		Read_EEPROM_Page_Sub(&data00[0],u16_src , u8_len); 
		Read_EEPROM_Page_Sub(u8p_dst, u16_src, u8_len);
		if(Lib_Cmp_TwoArry(u8p_dst,&data00[0],u8_len)==0)  return (TRUE);  
	}
	return(FALSE);
}


/*******************************************************************************************
** ��������: Write_EEPROM_Page
** ��������: ��EEPROM��ȡ�����ֽ� ����1��PAGE�ķ�Χ�ڲ�������д������ȶԣ�
** �������: u16_dst:   Ŀ������EEPROM�洢��ַ
**           *u8p_src:  Դ����RAM�����׵�ַָ��
**           u8_len: д����ֽ���
** �������: TRUE-д����ȷ   FALSE-д��ʧ��
** ˵��    : ��1��PAGE�ķ�Χ�ڲ���ʹ�ã��߱�д������ȶ��ߴ����
**           ʧ�����������������3��
*******************************************************************************************/
uint8 Write_EEPROM_Page(uint16 u16_dst, uint8 *u8p_src, uint8 u8_len)
{
 uint8 data00[EE_PageMask];
 uint8 i;
  
   if((u8_len<= 0)||(u8_len>EE_PageMask))                                    //if len is illegal,program run with dead circle
   {
       sys_err();
   }
   for(i=0;i<3;i++)                                                           //write and read compare, if error,repeat 3 times.
   {
       Write_EEPROM_Page_Sub(u16_dst, u8p_src, u8_len);
       Read_EEPROM_Page_Sub(&data00[0], u16_dst , u8_len); 
       if(Lib_Cmp_TwoArry(u8p_src,&data00[0],u8_len)== 0 )  return (TRUE);  
   }
   return(FALSE);
}


/*******************************************************************************************
** ��������: Read_EEPROM
** ��������: ��EEPROM��ȡ�����ֽ� ��ʵ������λ����ʼ��16λ�ֽڳ������ݶ�ȡ��
** �������: * u8p_dst:Ŀ������ָ��
**           u16_src:  Դ����EEPROM�洢��ַ
**           u16_len: ��ȡ���ֽ���
** �������: TRUE-��ȡ��ȷ   FALSE-��ȡʧ��
** ˵��    : ����ʼλ�õ����ƣ�
**           ��ȡ����Ϊ16λ�ֽ�
**           �Զ�ʵ�ֿ�ҳ�����������������ζ����ȶԹ���
*******************************************************************************************/
uint8 Read_EEPROM(uint8* u8p_dst, uint16 u16_src, uint16 u16_len)
{
 uint8 tmp;
 uint8 u8_lenth;

	while( u16_len > 0 )
	{
		tmp = (INT8U)(u16_src & (EE_PageMask -1));	// Դ���� ��ҳ���еĵ�ַ�� //
		if( tmp != 0 ) 
		{
			u8_lenth = EE_PageMask - tmp;			   	// Դ�����׵�ַ ��ҳβ��  ���� //
		}
		else 
		{
			u8_lenth = EE_PageMask;
		}
		if( u16_len < u8_lenth ) u8_lenth = u16_len;       				 // 

		if(Read_EEPROM_Page(u8p_dst, u16_src, u8_lenth) == FALSE)  return(FALSE);
		u8p_dst += u8_lenth;
		u16_src += u8_lenth;
		u16_len -= u8_lenth;
	} 
	return (TRUE);  
}

/*******************************************************************************************
** ��������: Write_EEPROM_Page
** ��������: ��EEPROM��ȡ�����ֽ� ��ʵ������λ����ʼ��16λ�ֽڳ�������д�룩
** �������: u16_dst:   Ŀ������EEPROM�洢��ַ
**           *u8p_src:  Դ����RAM�����׵�ַָ��
**           u16_len: д����ֽ���
** �������: TRUE-д����ȷ   FALSE-д��ʧ��
** ˵��    : ����ʼλ�õ����ƣ�
**           ��ȡ����Ϊ16λ�ֽ�
**           �Զ�ʵ�ֿ�ҳд�봦��������д������ȶԹ���
*******************************************************************************************/
uint8  Write_EEPROM(uint16 u16_dst, uint8 *u8p_src, uint16 u16_len)
{
 uint8 tmp;
 uint8 u8_lenth;
  
   while( u16_len > 0 )
   {
		tmp = (INT8U)(u16_dst & (EE_PageMask -1));	// Դ���� ��ҳ���еĵ�ַ�� //
		if( tmp != 0 ) 
		{
			u8_lenth = EE_PageMask - tmp;			   	// Դ�����׵�ַ ��ҳβ��  ���� //
		}
		else 
		{
			u8_lenth = EE_PageMask;
		}
		if( u16_len < u8_lenth ) u8_lenth = u16_len;       				 // 


       if(Write_EEPROM_Page(u16_dst, u8p_src, u8_lenth)==FALSE)  return(FALSE);
       u16_dst += u8_lenth;
       u8p_src += u8_lenth;
       u16_len -= u8_lenth;
   } 
   return (TRUE); 
}

/*******************************************************************************************
**    END
*******************************************************************************************/
