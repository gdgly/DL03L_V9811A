/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_UART_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: UARTģ���Ӳ������C����������ļ�
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#ifndef _Drv_UART_H
#define _Drv_UART_H

/***************************************************************
*    1     ������Ԥ����   
****************************************************************/
//uart  bps define   //
#define BPS300    300UL
#define BPS600    600UL
#define BPS1200    1200UL
#define BPS2400    2400UL
#define BPS4800    4800UL
#define BPS9600    9600UL

#define		UART_BAUDRATE_300			(32768-FSYSCLK/16UL/BPS300)	
#define		UART_BAUDRATE_600			(32768-FSYSCLK/16UL/BPS600)	
#define		UART_BAUDRATE_1200			(32768-FSYSCLK/16UL/BPS1200)	
#define		UART_BAUDRATE_2400			(32768-FSYSCLK/16UL/BPS2400)	
#define		UART_BAUDRATE_4800			(32768-FSYSCLK/16UL/BPS4800)	
#define		UART_BAUDRATE_9600			(32768-FSYSCLK/16UL/BPS9600)	


//uart  data bits lenth  define 
#define UART_8BITS    8
#define UART_7BITS    7

// UART ͨ�� //
#define UART_CH_NUM 2
#define UART_CH_INDEX_MAX  (UART_CH_NUM-1)
#define UART_CH0_IR 0    // UART2 //
#define UART_CH1_RS 1   // UART4 //

// ͨ��BUFF ��󳤶�  //
#define UART_BUFF_SIZE    100    //��������󳤶�Ϊ200��  //

/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
typedef struct 
{	
    uint8  tx_len;					// ���ڷ������ݳ���//
    uint8	buff_index;				// ��ǰ��������BUFF ָ���±� //
    uint8  buff_index_back;			// ��һ�δ��ڽ�������BUFF ָ���±� //
    uint8  rx_over_ticks;           // ���ڽ������ݳ�ʱ������ʱ����10mS��׼  //
    uint8  buff[UART_BUFF_SIZE];	//  ���ڻ����� //
    uint8  status;					// ���ڹ�����ʶ//
    uint16 badu;					// ���ڲ����� //
    uint8  bits_len;				// ����λ�� 8��7 //
} UART_DRV_VAR;




/***************************************************************
*    3    ��������       
****************************************************************/
extern UART_DRV_VAR gs_uart_drv_var[UART_CH_NUM];


/***************************************************************
*    4     ��������        
****************************************************************/
extern void Set_Uart2_badu(uint16 rate);
extern void Set_Uart4_badu(uint16 rate);
extern void En_UART2_rx(void);
extern void En_UART4_rx(void);
extern void Dis_UART2_rx(void);
extern void Dis_UART4_rx(void);
extern void En_UART2_Tx(void);
extern void En_UART4_Tx(void);
extern void Init_UART2_hard(uint16 badu);
extern void Init_UART4_hard(uint16 badu);
extern void Init_UART_soft(uint8 ch);
extern void Hdl_UART_10ms_run(uint8 ch);
extern void Tx_UART_frist (uint8 *p_buf, uint8 len,uint16 badu,uint8 ch);
extern uint8 Get_UART_rx_buff (uint8 **p_buf,uint8 ch);


/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/

//UART_DRV_VAR. status define  //
#define UART_STATUS_IDLE                    0                                                                    // ����״̬ //
#define UART_STATUS_BUSY_RX       UART_STATUS_IDLE+1                   // ����״̬ //
#define UART_STATUS_BUSY_RX_OVER       UART_STATUS_BUSY_RX+1    // ����״̬ //
#define UART_STATUS_BUSY_TX       UART_STATUS_BUSY_RX_OVER+1    // ����״̬ //
#define UART_STATUS_BUSY_TX_OVER       UART_STATUS_BUSY_TX+1    // ����״̬ //

/***************************************************************
*    END
****************************************************************/
#endif
