/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name        : SYS_IOdefine_H.H
**Author      : maji
**date        : 2016-04-26
**description : define for  系统IO口相关定义
**note        : memer type  DL03CA，对应原理图版本为"DL03C-V9811A-20160418-V1.0"
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26  v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#ifndef 	_SYS_IOdefine_H
#define	_SYS_IOdefine_H

//******************************************************************
//  E2P 24CXXX  i2c  PORT DEFINE    //
//******************************************************************
#define PIN_E2SDA		BIT1      //DIO   p9_1
#define PIN_E2SCL		BIT2      //CLK   p9_2
#define I2C_PORT_OUT	P9DO
#define I2C_PORT_IN		P9DI	
#define I2C_DIR_IN			P9IE
#define I2C_DIR_OUT			P9OE

#define PIN_Reverse  BIT1   //P1.1
#define PIN_Reverse_HIGH()  {P1OE &= (~PIN_Reverse);P1OD |= PIN_Reverse;P11FS = 0;}
#define PIN_Reverse_LOW()  {P1OE &= (~PIN_Reverse);P1OD &= (~PIN_Reverse);P11FS = 0;}

#define I2C_DIO_IN			{I2C_DIR_OUT |= PIN_E2SDA; I2C_DIR_IN |= PIN_E2SDA;  } 
#define I2C_DIO_OUT			{I2C_DIR_IN &= (~PIN_E2SDA);I2C_DIR_OUT &= (~PIN_E2SDA); } 
#define I2C_CLK_IN			{I2C_DIR_IN |= PIN_E2SCL;I2C_DIR_OUT |= PIN_E2SCL; } 
#define I2C_CLK_OUT			{I2C_DIR_OUT &= (~PIN_E2SCL); I2C_DIR_IN &= (~PIN_E2SCL);} 

#define I2C_DIO_HIGH    I2C_DIO_IN    //{I2C_PORT_OUT |=PIN_E2SDA; }	采用输入态的上拉电阻输出高，避免总线冲突 //	
#define I2C_DIO_LOW     {I2C_PORT_OUT &=(~PIN_E2SDA); I2C_DIO_OUT;}  	//采用输出0方式 //	
#define I2C_CLK_HIGH    {I2C_PORT_OUT |=PIN_E2SCL; }
#define I2C_CLK_LOW     {I2C_PORT_OUT &=(~PIN_E2SCL); }
#define I2C_DIO_JUDGE  	(I2C_PORT_IN&PIN_E2SDA)
#define I2C_CLK_JUDGE  	(I2C_PORT_IN&PIN_E2SCL)

#define I2C_PORT_INITLIZE()  {I2C_DIO_IN;I2C_CLK_HIGH;I2C_CLK_OUT;}   

//******************************************************************
// RS485_UART PORT DEFINE    //  UART4
//******************************************************************
#define PIN_UART4_RX    BIT0
#define PIN_UART4_TX    BIT1
#define UART4_FUNC_EN()   {P2OE &= ~PIN_UART4_TX;P2IE |=PIN_UART4_RX; P20FS = 0X02;P21FS = 0X02;}
#define UART4_FUNC_DIS()   {P2OE |= PIN_UART4_TX;P2IE &=~PIN_UART4_RX; P20FS = 0;P21FS = 0;}
#define UART4_TX_DIR_OUT()   {P2OE &= ~PIN_UART4_TX;}
#define UART4_RX_DIR_IN()   {P2IE |= PIN_UART4_RX;}
#define UART4_TX_HIGH()   {P2OD |= PIN_UART4_TX;}
#define UART4_TX_LOW()   {P2OD &= ~PIN_UART4_TX;}

#define UART4_INITLIZE_OFF()  {UART4_FUNC_DIS();UART4_TX_HIGH();UART4_TX_DIR_OUT() ;UART4_RX_DIR_IN();}
#define UART4_INITLIZE_ON()  {UART4_TX_HIGH();UART4_TX_DIR_OUT() ;UART4_RX_DIR_IN();UART4_FUNC_EN();}

//******************************************************************
// FAR IR_UART PORT DEFINE    //
//******************************************************************
#define PIN_UART2_RX    BIT4  
#define PIN_UART2_TX    BIT5
#define UART2_FUNC_EN()   {P2OE &= ~PIN_UART2_TX;P2IE |=PIN_UART2_RX; P24FS = 0X02;P25FS = 0X02;}
#define UART2_FUNC_DIS()   {P2OE |= PIN_UART2_TX;P2IE &=~PIN_UART2_RX; P24FS = 0;P25FS = 0;}


#define UART2_TX_DIR_OUT()   {P2OE &= ~PIN_UART2_TX;}
#define UART2_RX_DIR_IN()   {P2IE |= PIN_UART2_RX;}
#define UART2_TX_HIGH()   {P2OD |= PIN_UART2_TX;}
#define UART2_TX_LOW()   {P2OD &= ~PIN_UART2_TX;}
//#define UART2_PWM38K_EN()   {P25FS = 0X02;Txd2FS &=~ BIT0;CARRHH= 0;CARRHL=61;CARRLH= 0;CARRLL=111;	}  // 带有载波信号38K//
//#define UART2_PWM38K_DIS()   {P25FS = 0X00;Txd2FS |=BIT0;UART2_TX_LOW();UART2_TX_DIR_OUT();}  //关闭串口发送功能 //
#define UART2_INITLIZE_OFF()  {UART2_FUNC_DIS();UART2_TX_HIGH();UART2_TX_DIR_OUT() ;UART2_RX_DIR_IN();}
#define UART2_INITLIZE_ON()  {UART2_TX_HIGH();UART2_TX_DIR_OUT() ;UART2_RX_DIR_IN();UART2_FUNC_EN();}
//#define UART2_INITLIZE_OFF()  {UART2_FUNC_DIS();UART2_PWM38K_DIS();UART2_TX_HIGH();UART2_TX_DIR_OUT() ;UART2_RX_DIR_IN();}
//#define UART2_INITLIZE_ON()  {UART2_FUNC_EN();UART2_RX_DIR_IN();UART2_PWM38K_DIS();}

//******************************************************************
//LED port define  //
//******************************************************************
#define PIN_LED_BG  BIT2     //P1.2 控制背光LED灯  //
#define LED_BG_ON()     {P1OE &= ~PIN_LED_BG; P1OD |= PIN_LED_BG;}
#define LED_BG_OFF()    {P1OE &= ~PIN_LED_BG; P1OD &= ~PIN_LED_BG;}

#define PIN_LED_REV  BIT1     //P1.2 控制背光LED灯  //
#define LED_REV_ON()     {P1OE &= ~PIN_LED_REV; P1OD |= PIN_LED_REV;}
#define LED_REV_OFF()    {P1OE &= ~PIN_LED_REV; P1OD &= ~PIN_LED_REV;}

#define PIN_CFLED	             BIT3		// enarge pluse led port,  DIR = O  //
#define CFLED_INITLIZE()  {P13FS= 0X04; P1OE &= ~PIN_CFLED;P1OD &= ~PIN_CFLED;}
#define CFLED_CLOSE()     {P13FS= 0X00; P1OE &= ~PIN_CFLED;P1OD &= ~PIN_CFLED;}

#define PIN_KEY_ERR_COVER   BIT6    //P9.6  
#define KEY_ERR_COVER_INITLIZE() {P9IE |= PIN_KEY_ERR_COVER;P9OE |= PIN_KEY_ERR_COVER;P9DO |= BIT6;P9FC &= ~PIN_KEY_ERR_COVER; }
#define KEY_READ_ERR_COVER  (P9DI&PIN_KEY_ERR_COVER)

//******************************************************************
// key  port define  //
//******************************************************************
#define PIN_KEY_ERR_ADJ   BIT5    // P9.5    ADJA
#define PIN_KEY_PROG   BIT3    // P9.3   PROG
#define PIN_KEY_DIS   BIT4    // P1.4   PROG

#define KEY_ERR_ADJ_INITLIZE()  {P9IE |= PIN_KEY_ERR_ADJ;P9OE |= PIN_KEY_ERR_ADJ;}
#define KEY_READ_ERR_ADJ  (P9DI&PIN_KEY_ERR_ADJ)

#define KEY_PROG_INITLIZE()  {P9IE |= PIN_KEY_PROG;P9OE |= PIN_KEY_PROG;}
#define KEY_READ_PROG  (P9DI&PIN_KEY_PROG)

#define KEY_DIS_INITLIZE()  {P1OE |= PIN_KEY_DIS;P1IE |= PIN_KEY_DIS;P14FS = (BIT0+BIT1);TCON |= BIT2; IE |= BIT2;}   //外部中断1//
#define KEY_READ_DIS()         (P1ID&PIN_KEY_DIS)



//******************************************************************
// other  ports define  //
//******************************************************************
#define PIN_RTC_OUT   BIT3    // P1.3    ADJA  //
#define RTC_OUT_LOW()   {P1OD &= ~PIN_RTC_OUT;}




/***************************************************************
*    END
****************************************************************/

#endif
