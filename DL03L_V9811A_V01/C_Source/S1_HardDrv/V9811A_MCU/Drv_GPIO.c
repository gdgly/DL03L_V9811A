/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_GPIO.c
**Author		: maji
**date			: 2016-04-20 
**description	: GPIOģ���Ӳ������C����
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
** ��������: Init_GPIO_run
** ��������: ����GPIO���ܣ���������ģʽ�£�
** �������: ��
** �������: �� 
** ˵��    : 
*******************************************************************************************/
void Init_GPIO_run(void)                  
{
    // P0 port  [0:3]  use for debug////JTAG
    P0OE&=(~(BIT0+BIT1+BIT2+BIT3)); //JTAG ��� 0
    P0OD&=(~(BIT0+BIT1+BIT2+BIT3));

    //P9FC = PIN_CFLED;    //CF1 FUNCTION ENABLE ,OTHER IS GPIO FUNCTION //
    CFLED_CLOSE();

    UART4_INITLIZE_OFF();
    UART2_INITLIZE_OFF();
    LED_BG_OFF();
    KEY_ERR_ADJ_INITLIZE();
    KEY_PROG_INITLIZE();
    KEY_DIS_INITLIZE();
    I2C_PORT_INITLIZE();


}

/*******************************************************************************************
** ��������: Init_GPIO_sleep
** ��������: ����GPIO���ܣ��͹�������ģʽ�£�
** �������: ��
** �������: �� 
** ˵��    : 
*******************************************************************************************/
void Init_GPIO_sleep(void)                  
{
    P0OE=0XFF;
    P0IE=0;
    P1OE=0XFF;	
    P1IE=0 ;
    P2OE=0XFF;
    P2IE=0;	
    P3OE=0XFF;
    P3IE=0;
    P4OE=0XFF;	
    P4IE=0;
    P5OE=0XFF;
    P5IE=0;
    P6OE=0XFF;	   
    P6IE=0;
    P7OE=0XFF;
    P7IE=0;
    P8OE=0XFF;	   
    P8IE=0;
 
    CFLED_CLOSE();  
    P9OE=0XFF;	   
    P9IE=0;

    KEY_DIS_INITLIZE();
                
}



/*******************************************************************************************
**    END
*******************************************************************************************/