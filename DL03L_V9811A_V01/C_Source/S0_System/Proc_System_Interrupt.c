/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Proc_System_Interrupt.c
**Author		: maji
**date			: 2016-04-20
**description	: ϵͳ�ж������������C����
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>




//=======================================================
//��������Interrupt_Int0
//�������ã��˿��ж�0���ж�����				��03H��
//======================================================= 
void Interrupt_Int0 (void) interrupt 0 using 2
{
    TCON &= ~BIT1;
//  user coding begin
//    Int0();		
}
//=======================================================
//��������Interrupt_Timer0
//�������ã��ں�timer0�жϣ��ж�����		��0BH��
//Ӧ��˵��: 10ms��ʱ
//======================================================= 
void Interrupt_Timer0 (void) interrupt 1 using 2
{

    TL0  = LOBYTE(T0_10MS_CNT);         //10ms
    TH0  = HIBYTE(T0_10MS_CNT);

    // user coding begin
    gs_sys_run.back_fg |= BIT0_FONT_FG_10MS;   //����10ms��ʶ��Ч //
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
//��������Interrupt_Int1
//�������ã��˿��ж�1���ж�����				��13H��
//======================================================= 
void Interrupt_Int1 (void) interrupt 2 using 2
{
    TCON &= ~BIT3;
  
    if(Judge_DIS_key()==TRUE)		//!!!	p1.4
    {
        gs_sys_run.back_fg |= BIT2_BACK_DIS_KEY;   //������ʾ������ʶ��Ч //
    }

}
//=======================================================
//��������Interrupt_Timer1
//�������ã��ں�timer1�жϣ��ж�����		��1BH��
//======================================================= 
void Interrupt_Timer1 (void) interrupt 3 using 2
{
    TCON &= ~BIT7;

// user coding begin

}

//=======================================================
//��������Interrupt_Timer2
//�������ã��ں�timer2�жϣ��ж�����		��2BH��
//======================================================= 
void Interrupt_Timer2 (void) interrupt 5 using 2
{
	T2CON &= ~BIT7;
   //user coding begin
       
}

//=======================================================
//��������Interrupt_Uart1
//�������ã��ں�uart1�жϣ��ж�����			��3BH��
//=======================================================
void Interrupt_Uart1 (void) interrupt 7 using 2
{
    if (SCON1 & BIT0)
    {// �����жϱ��
        SCON1 &= ~BIT0;
        // user coding begin
    }
    else if (SCON1 & BIT1)
    {// �����жϱ��
        SCON1 &= ~BIT1;
        // user coding begin
    }
}


//=======================================================
//��������Interrupt_ExInt2
//�������ã��ⲿ�ж�2���ж�����				��43H��
//ע�⣺������չ�жϱ�־λ�������ں��жϱ�־λ
//=======================================================
void Interrupt_ExInt2 (void) interrupt 8 using 2
{
 uint8 buf;
 uint8 temp_ifg;

    temp_ifg = ExInt2IE & ExInt2IFG;        // ��ֹ��δʹ���жϵ�λ���� //

////////////////////////////////////////////////////////////////////////
//  UART2  TX 	START
////////////////////////////////////////////////////////////////////////
    if (temp_ifg & BIT0)
    {// uart2 translate interrupt flag
        ExInt2IFG &= ~BIT0;        //BIT0, ExInt2IFG�����жϱ�ʶ //
        SCON2 &= ~BIT1;           //BIT1 , UART2��SCON2�еķ����жϱ�ʶ //
        // user coding begin
        if (gs_uart_drv_var[UART_CH0_IR].tx_len>0)
        {
            buf=(gs_uart_drv_var[UART_CH0_IR].buff[gs_uart_drv_var[UART_CH0_IR].buff_index]);
            if(gs_uart_drv_var[UART_CH0_IR].bits_len==7)
           {
                 // 7λ���ݴ���ʽ //
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
            gs_uart_iec_app_var[UART_CH0_IR].delay_10ms = 0;   // �����ݴ���ʱ�����ʱ������ //
            gs_uart_drv_var[UART_CH0_IR].buff[gs_uart_drv_var[UART_CH0_IR].buff_index] =0;
            gs_uart_drv_var[UART_CH0_IR].buff_index++;
            gs_uart_drv_var[UART_CH0_IR].tx_len -- ;
        }
        else
        {
            //�������  //
            gs_uart_drv_var[UART_CH0_IR].buff_index = 0;
            gs_uart_drv_var[UART_CH0_IR].status = UART_STATUS_BUSY_TX_OVER; 
            En_UART2_rx();
					  Init_UART_soft(UART_CH0_IR);   					
//            UART2_PWM38K_DIS();    //! ������ɼ�ʱ�ر�PWM //        
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
	 gs_uart_iec_app_var[UART_CH0_IR].delay_10ms = 0;   // �����ݴ���ʱ�����ʱ������ //
        gs_uart_drv_var[UART_CH0_IR].buff[gs_uart_drv_var[UART_CH0_IR].buff_index] = buf&0x7f;//  7λ����λ//
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
                 // 7λ���ݴ���ʽ //
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
            gs_uart_iec_app_var[UART_CH1_RS].delay_10ms = 0;   // �����ݴ���ʱ�����ʱ������ //
            gs_uart_drv_var[UART_CH1_RS].buff[gs_uart_drv_var[UART_CH1_RS].buff_index] =0;
            gs_uart_drv_var[UART_CH1_RS].buff_index++;
            gs_uart_drv_var[UART_CH1_RS].tx_len -- ;
        }
        else
        {
            //�������  //
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
	 gs_uart_iec_app_var[UART_CH1_RS].delay_10ms = 0;   // �����ݴ���ʱ�����ʱ������ //
        gs_uart_drv_var[UART_CH1_RS].buff[gs_uart_drv_var[UART_CH1_RS].buff_index] = buf&0x7f;//  7λ����λ//
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
        gs_energy_var.pluse[EC_CH_AC_PT_TT]++;    //�й��ܵ����ۼ� //
    }
////////////////////////////////////////////////////////////////////////
//   ACTIVE ENERGY PLUSE accumulate 	END
////////////////////////////////////////////////////////////////////////


    EXIF &= ~BIT4;
}

//=======================================================
//��������Interrupt_ExInt3
//�������ã��ⲿ�ж�3���ж�����				��4BH��	
//ע�⣺������չ�жϱ�־λ�������ں��жϱ�־λ		
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
	if (temp_ifg & BIT5)//UART5 ����ͨ��ʱ������ж�
    {// uart3timer0 interrupt
       ExInt3IFG &= ~BIT5;
        // user coding begin   
    }			
    if (temp_ifg & BIT6)
    {// rtc interrupt
        ExInt3IFG &= ~BIT6;
        // user coding begin  
        gs_sys_run.back_fg |= BIT1_BACK_FG_RTC;   //������ʾ������ʶ��Ч //  //  RTC ÿ��������ж�  //
        gs_emu_adj_var.sec_flg=TRUE;           // Ӳ���̽�У���붨ʱ��ʶ //
    }


    if (temp_ifg & BIT7)	//  �޹�
    {// CF2 interrupt
        ExInt3IFG &= ~BIT7;
        // user coding begin 
                

    }
    EXIF &= ~BIT5;
}
//=======================================================
//��������Interrupt_ExInt4
//�������ã��ⲿ�ж�4���ж�����				��53H��
//ע�⣺������չ�жϱ�־λ�������ں��жϱ�־λ
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
//��������Interrupt_PF
//�������ã�ϵͳ����Ԥ���жϣ��ж�����		��63H��
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

