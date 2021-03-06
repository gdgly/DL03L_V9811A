/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Proc_System_Interrupt.c
**Author		: maji
**date			: 2016-04-20
**description	: 系统中断向量处理相关C代码
**note			: V9811A ，MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>




//=======================================================
//函数名：Interrupt_Int0
//函数作用：端口中断0，中断向量				（03H）
//======================================================= 
void Interrupt_Int0 (void) interrupt 0 using 2
{
    TCON &= ~BIT1;
//  user coding begin
//    Int0();		
}
//=======================================================
//函数名：Interrupt_Timer0
//函数作用：内核timer0中断，中断向量		（0BH）
//应用说明: 10ms定时
//======================================================= 
void Interrupt_Timer0 (void) interrupt 1 using 2
{

    TL0  = LOBYTE(T0_10MS_CNT);         //10ms
    TH0  = HIBYTE(T0_10MS_CNT);

    // user coding begin
    gs_sys_run.back_fg |= BIT0_FONT_FG_10MS;   //配置10ms标识有效 //
    gs_uart_iec_app_var[UART_CH0_IR].delay_10ms++;
    gs_uart_iec_app_var[UART_CH1_RS].delay_10ms++;
    if(gs_uart_iec_app_var[UART_CH0_IR].tx_delay_flg ==TRUE )
    {
        if(gs_uart_iec_app_var[UART_CH0_IR].tx_ready_10ms>0)  gs_uart_iec_app_var[UART_CH0_IR].tx_ready_10ms --;
    }
   
    if(gs_uart_iec_app_var[UART_CH1_RS].tx_delay_flg ==TRUE )
    {
        if(gs_uart_iec_app_var[UART_CH1_RS].tx_ready_10ms>0)  gs_uart_iec_app_var[UART_CH1_RS].tx_ready_10ms --;
    }
	
}

//=======================================================
//函数名：Interrupt_Int1
//函数作用：端口中断1，中断向量				（13H）
//======================================================= 
void Interrupt_Int1 (void) interrupt 2 using 2
{
    TCON &= ~BIT3;
  
    if(Judge_DIS_key()==TRUE)		//!!!	p1.4
    {
        gs_sys_run.back_fg |= BIT2_BACK_DIS_KEY;   //配置显示按键标识有效 //
    }

}
//=======================================================
//函数名：Interrupt_Timer1
//函数作用：内核timer1中断，中断向量		（1BH）
//======================================================= 
void Interrupt_Timer1 (void) interrupt 3 using 2
{
    TCON &= ~BIT7;

// user coding begin

}

//=======================================================
//函数名：Interrupt_Timer2
//函数作用：内核timer2中断，中断向量		（2BH）
//======================================================= 
void Interrupt_Timer2 (void) interrupt 5 using 2
{
	T2CON &= ~BIT7;
   //user coding begin
       
}

//=======================================================
//函数名：Interrupt_Uart1
//函数作用：内核uart1中断，中断向量			（3BH）
//=======================================================
void Interrupt_Uart1 (void) interrupt 7 using 2
{
    if (SCON1 & BIT0)
    {// 接受中断标记
        SCON1 &= ~BIT0;
        // user coding begin
    }
    else if (SCON1 & BIT1)
    {// 发送中断标记
        SCON1 &= ~BIT1;
        // user coding begin
    }
}


//=======================================================
//函数名：Interrupt_ExInt2
//函数作用：外部中断2，中断向量				（43H）
//注意：先清扩展中断标志位，后清内核中断标志位
//=======================================================
void Interrupt_ExInt2 (void) interrupt 8 using 2
{
 uint8 buf;
 uint8 temp_ifg;

    temp_ifg = ExInt2IE & ExInt2IFG;        // 防止对未使能中断的位操作 //

////////////////////////////////////////////////////////////////////////
//  UART2  TX 	START
////////////////////////////////////////////////////////////////////////
    if (temp_ifg & BIT0)
    {// uart2 translate interrupt flag
        ExInt2IFG &= ~BIT0;        //BIT0, ExInt2IFG发送中断标识 //
        SCON2 &= ~BIT1;           //BIT1 , UART2的SCON2中的发送中断标识 //
        // user coding begin
        if (gs_uart_drv_var[UART_CH0_IR].tx_len>0)
        {
            buf=(gs_uart_drv_var[UART_CH0_IR].buff[gs_uart_drv_var[UART_CH0_IR].buff_index]);
            if(gs_uart_drv_var[UART_CH0_IR].bits_len==7)
           {
                 // 7位数据处理方式 //
                 ACC=(buf &0x7F);
                if(P)
                {
                    buf |= BIT7;
                }
                else
                {
                    buf&= ~BIT7;
                }
            }
            SBUF2 = buf;
            gs_uart_iec_app_var[UART_CH0_IR].delay_10ms = 0;   // 有数据处理时清除延时计数器 //
            gs_uart_drv_var[UART_CH0_IR].buff[gs_uart_drv_var[UART_CH0_IR].buff_index] =0;
            gs_uart_drv_var[UART_CH0_IR].buff_index++;
            gs_uart_drv_var[UART_CH0_IR].tx_len -- ;
        }
        else
        {
            //发送完成  //
            gs_uart_drv_var[UART_CH0_IR].buff_index = 0;
            gs_uart_drv_var[UART_CH0_IR].status = UART_STATUS_BUSY_TX_OVER; 
            En_UART2_rx();
					  Init_UART_soft(UART_CH0_IR);   					
//            UART2_PWM38K_DIS();    //! 发送完成及时关闭PWM //        
        }
    }

////////////////////////////////////////////////////////////////////////
//  UART2  TX 	END
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//  UART2  RX 	START
////////////////////////////////////////////////////////////////////////
    if (temp_ifg & BIT1)
    {// uart2 receive interrupt flag
        ExInt2IFG &= ~BIT1;
        SCON2 &= ~BIT0;
        // user coding begin
        buf = SBUF2;
	 gs_uart_iec_app_var[UART_CH0_IR].delay_10ms = 0;   // 有数据处理时清除延时计数器 //
        gs_uart_drv_var[UART_CH0_IR].buff[gs_uart_drv_var[UART_CH0_IR].buff_index] = buf&0x7f;//  7位数据位//
        gs_uart_drv_var[UART_CH0_IR].buff_index++;
        if(gs_uart_drv_var[UART_CH0_IR].buff_index>4)
        {
            NOP();
            NOP();
        }
        gs_uart_drv_var[UART_CH0_IR].buff_index %= UART_BUFF_SIZE;

    }
////////////////////////////////////////////////////////////////////////
//  UART2  RX 	END
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//  UART4  TX 	START
////////////////////////////////////////////////////////////////////////
    if (temp_ifg & BIT2)
    {// uart4 translate interrupt flag
        ExInt2IFG &= ~BIT2;
        SCON4 &= ~BIT1;
        // user coding begin
        if (gs_uart_drv_var[UART_CH1_RS].tx_len>0)
        {
            buf=(gs_uart_drv_var[UART_CH1_RS].buff[gs_uart_drv_var[UART_CH1_RS].buff_index]);
            if(gs_uart_drv_var[UART_CH1_RS].bits_len==7)
           {
                 // 7位数据处理方式 //
                 ACC=(buf &0x7F);
                if(P)
                {
                    buf |= BIT7;
                }
                else
                {
                    buf&= ~BIT7;
                }
            }
            SBUF4= buf;
            gs_uart_iec_app_var[UART_CH1_RS].delay_10ms = 0;   // 有数据处理时清除延时计数器 //
            gs_uart_drv_var[UART_CH1_RS].buff[gs_uart_drv_var[UART_CH1_RS].buff_index] =0;
            gs_uart_drv_var[UART_CH1_RS].buff_index++;
            gs_uart_drv_var[UART_CH1_RS].tx_len -- ;
        }
        else
        {
            //发送完成  //
            gs_uart_drv_var[UART_CH1_RS].buff_index = 0;
            gs_uart_drv_var[UART_CH1_RS].status = UART_STATUS_BUSY_TX_OVER;
            En_UART4_rx();
					  Init_UART_soft(UART_CH1_RS);           
        }
    }

////////////////////////////////////////////////////////////////////////
//  UART4  TX 	END
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//  UART4  RX 	START
////////////////////////////////////////////////////////////////////////
    if (temp_ifg & BIT3)
    {// uart4 receive interrupt flag
        ExInt2IFG &= ~BIT3;
        SCON4 &= ~BIT0;
        // user coding begin
        buf = SBUF4;
	 gs_uart_iec_app_var[UART_CH1_RS].delay_10ms = 0;   // 有数据处理时清除延时计数器 //
        gs_uart_drv_var[UART_CH1_RS].buff[gs_uart_drv_var[UART_CH1_RS].buff_index] = buf&0x7f;//  7位数据位//
        gs_uart_drv_var[UART_CH1_RS].buff_index++;
        if(gs_uart_drv_var[UART_CH1_RS].buff_index>4)
        {
            NOP();
            NOP();
        }
        gs_uart_drv_var[UART_CH1_RS].buff_index %= UART_BUFF_SIZE;

    }
////////////////////////////////////////////////////////////////////////
//  UART4  RX 	END
////////////////////////////////////////////////////////////////////////


    if (temp_ifg & BIT4)
    {// uart2timer0 interrupt
        ExInt2IFG &= ~BIT4;
        // user coding begin  
    }
    if (temp_ifg & BIT5)
    {// uart4timer0 interrupt
        ExInt2IFG &= ~BIT5;
        // user coding begin    
    }
    if (temp_ifg & BIT6)
    {// flash erase interrupt
        ExInt2IFG &= ~BIT6;
        // user coding begin  
    }

////////////////////////////////////////////////////////////////////////
//   ACTIVE ENERGY PLUSE accumulate 	START
////////////////////////////////////////////////////////////////////////
    if (temp_ifg & BIT7)
    {// CF impluse interrupt
        ExInt2IFG &= ~BIT7;
        // user coding begin
        gs_energy_var.pluse[EC_CH_AC_PT_TT]++;    //有功总电能累计 //
    }
////////////////////////////////////////////////////////////////////////
//   ACTIVE ENERGY PLUSE accumulate 	END
////////////////////////////////////////////////////////////////////////


    EXIF &= ~BIT4;
}

//=======================================================
//函数名：Interrupt_ExInt3
//函数作用：外部中断3，中断向量				（4BH）	
//注意：先清扩展中断标志位，后清内核中断标志位		
//=======================================================
void Interrupt_ExInt3 (void) interrupt 9 using 2
{
 unsigned char temp_ifg;
	
    temp_ifg = ExInt3IE & ExInt3IFG;
    if (temp_ifg & BIT4)
    {// uart3timer0 interrupt
       ExInt3IFG &= ~BIT4;
        // user coding begin   
    }
	if (temp_ifg & BIT5)//UART5 中普通定时器溢出中断
    {// uart3timer0 interrupt
       ExInt3IFG &= ~BIT5;
        // user coding begin   
    }			
    if (temp_ifg & BIT6)
    {// rtc interrupt
        ExInt3IFG &= ~BIT6;
        // user coding begin  
        gs_sys_run.back_fg |= BIT1_BACK_FG_RTC;   //配置显示按键标识有效 //  //  RTC 每秒产生的中断  //
        gs_emu_adj_var.sec_flg=TRUE;           // 硬件短接校表秒定时标识 //
    }


    if (temp_ifg & BIT7)	//  无功
    {// CF2 interrupt
        ExInt3IFG &= ~BIT7;
        // user coding begin 
                

    }
    EXIF &= ~BIT5;
}
//=======================================================
//函数名：Interrupt_ExInt4
//函数作用：外部中断4，中断向量				（53H）
//注意：先清扩展中断标志位，后清内核中断标志位
//======================================================= 
void Interrupt_ExInt4 (void) interrupt 10 using 2
{

 unsigned char temp_ifg;
 
    temp_ifg = ExInt4IE & ExInt4IFG;
//    if (temp_ifg & BIT0)
//    {
//        ExInt4IFG &= ~BIT0;
//        // user coding begin   
//    }
//    if (temp_ifg & BIT1)
//    {
//        ExInt4IFG &= ~BIT1;
//        // user coding begin    
//    }
//    if (temp_ifg & BIT2)
//    {
//        ExInt4IFG &= ~BIT2;
//        // user coding begin    
//    }
    if (temp_ifg & BIT3)
    {
        
//		for(cnt=10;cnt>0;cnt--)
//		 {
//		    NOP();
//	     }
//		 if((P1ID & BIT2 ) ==0)		//!!!	p1.2
//	     {
//			io_trg_var.cover_key2_status = TRUE;
//		 }
		 ExInt4IFG &= ~BIT3;
        // user coding begin   
    }
//    if (temp_ifg & BIT4)
//    {
//        ExInt4IFG &= ~BIT4;
//        // user coding begin   
//    }
//    if (temp_ifg & BIT5)
//    {
//        ExInt4IFG &= ~BIT5;
//        // user coding begin 
//    }
   
    EXIF &= ~BIT6;
}

//=======================================================
//函数名：Interrupt_PF
//函数作用：系统掉电预警中断，中断向量		（63H）
//======================================================= 
/*void Interrupt_PF (void) interrupt 12 using 2
{// powerdown interrupt
    EICON &= ~BIT3;
    // user coding begin
    Int27();    
}*/
	


/***************************************************************
*    END
****************************************************************/

