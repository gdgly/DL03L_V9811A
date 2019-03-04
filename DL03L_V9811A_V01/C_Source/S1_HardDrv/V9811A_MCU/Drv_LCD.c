/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_LCD.c
**Author		: maji
**date			: 2016-04-20 
**description	: LCDģ���Ӳ������C����
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>



/*******************************************************************************************
** ��������: LCD_ON
** ��������: LCD����ʾ
** �������: ��
** �������: �� 
** ˵��    : 
*******************************************************************************************/
void LCD_ON(void)
{
    LCDG=0;		//��LCDʱ��
    CtrlLCDV=0;	// 3.3V
    LCDCtrl= 0XD2;       //6C0TYPE=1, 6COM,300K,256HZ
}


/*******************************************************************************************
** ��������: Full_SEG
** ��������: ��SEG����ָ����ֵ
** �������: val:Ҫ�����ֵ
** �������: �� 
** ˵��    : 
*******************************************************************************************/
void Full_SEG(uint8 val)
{
	LCDM8 =  val&0X3F;    
	LCDM9 =  val&0X3F;  
	LCDM10 =  val&0X3F; 
	LCDM11 =  val&0X3F; 
	LCDM12 =  val&0X3F; 
	LCDM13 =  val&0X3F; 
	LCDM14 =  val&0X3F; 
	LCDM15 =  val&0X3F; 

	LCDM18 =  val&0X3F; 
	LCDM19 = val&0X3F; 
	LCDM20 =  val&0X3F; 
	LCDM21 =  val&0X3F; 
	LCDM22 =  val&0X3F; 
	LCDM23 =  val&0X3F; 

	LCDM30 =  val&0X3F; 
	LCDM31 =  val&0X3F; 
	LCDM32 =  val&0X3F; 
	LCDM33 =  val&0X3F; 
	LCDM34 =  val&0X3F; 
	LCDM35 =  val&0X3F; 

	LCDM38 =  val&0X3F; 
}


/*******************************************************************************************
** ��������: LCD_OFF
** ��������: LCD�ر���ʾ
** �������: ��
** �������: �� 
** ˵��    : 
*******************************************************************************************/
void LCD_OFF(void)
{
    Full_SEG(0);
/*  ��Ϊ�رպ�Һ������Ϊ������������ mj,2016-6-12
    SegCtrl0 = 0;
    SegCtrl1 = 0;
    SegCtrl2 = 0;
    SegCtrl3 = 0;
    SegCtrl4 = 0;
    LCDCtrl = 0;
    LCDG = 1;   // �ر� //
*/
}

/*******************************************************************************************
** ��������: LCD_Init
** ��������: LCD��ʼ��
** �������: ��
** �������: �� 
** ˵��    : 
*******************************************************************************************/
void Init_LCD(void)
{
 //
     LCD_ON();
     Full_SEG(0);
    //SegCtrl0: seg0~7,  seg0~1 ��Ч  //
    SegCtrl0=Bin(00000000);      // seg0~seg1  OFF //
    //SegCtrl1: seg8~15,  seg5~15 ��Ч  //
    SegCtrl1=Bin(11111111);	     // seg8~seg15  ON//
    //SegCtrl2: seg16~23,  seg18~23 ��Ч  //
    SegCtrl2=Bin(11111100);     // seg18~seg23  ON//
    //SegCtrl3: seg24~31,  seg30~31 ��Ч  //
    SegCtrl3=Bin(11000000);     // seg30~seg31  ON//
    //SegCtrl4: seg32~39,  seg32~35,  seg38~39��Ч  //
    SegCtrl4=Bin(01001111);     // seg32~seg35    seg38  ON//	
}


//*****************************************************************
//  Function:       void InitLCD(void)           
//  Description:                                           
//  Others:        len Ϊ   
//***************************************************************
void Write_LCD(INT8U* bf_i2cData)
{
	LCDM8 =  (*(bf_i2cData+0))&0X3F;    
	LCDM9 =  (*(bf_i2cData+1))&0X3F;  
	LCDM10 =  (*(bf_i2cData+2))&0X3F; 
	LCDM11 =  (*(bf_i2cData+3))&0X3F; 
	LCDM12 =  (*(bf_i2cData+4))&0X3F; 
	LCDM13 =  (*(bf_i2cData+5))&0X3F; 
	LCDM14 =  (*(bf_i2cData+6))&0X3F; 
	LCDM15 =  (*(bf_i2cData+7))&0X3F; 

	LCDM18 =  (*(bf_i2cData+8))&0X3F; 
	LCDM19 =  (*(bf_i2cData+9))&0X3F; 
	LCDM20 =  (*(bf_i2cData+10))&0X3F; 
	LCDM21 =  (*(bf_i2cData+11))&0X3F; 
	LCDM22 =  (*(bf_i2cData+12))&0X3F; 
	LCDM23 =  (*(bf_i2cData+13))&0X3F; 

	LCDM30 =  (*(bf_i2cData+14))&0X3F; 
	LCDM31 =  (*(bf_i2cData+15))&0X3F; 
	LCDM32 =  (*(bf_i2cData+16))&0X3F; 
	LCDM33 =  (*(bf_i2cData+17))&0X3F; 
	LCDM34 =  (*(bf_i2cData+18))&0X3F; 
	LCDM35 =  (*(bf_i2cData+19))&0X3F; 

	LCDM38 =  (*(bf_i2cData+20))&0X3F; 
}



/*******************************************************************************************
**    END
*******************************************************************************************/
