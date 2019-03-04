/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_User_Comm_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: ͨѶ����Ӧ�ò���غ�������H�ļ�
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/



#ifndef _Api_User_Comm_H
#define _Api_User_Comm_H

/***************************************************************
*    1     ������Ԥ����   
****************************************************************/
/////////////////////////////////
//security
////////////////////////////////
#define  mmok    0x00           //   Ȩ���ж���ȷ
#define  mmover  0x01           // ���볬Ȩ��
#define  mmerr   0x02           //  �������
#define  keyoff  0x03            //   ��̿�����Ч
#define  uferr   0x04             //


//ͨѶ��·���˳����ʱ�䶨��//
#define  COMM_DELAY_3500MS     350
#define  COMM_DELAY_100MS      5
#define  COMM_DELAY_500MS      40

//#define   _COMM_FUNCTION
//IEC_COMM_LINK.mode define 
#define   IEC_COMM_END                                   0x00
#define   IEC_COMM_REQUEST                            '/'
#define   IEC_COMM_ACKNOWLEDGEMENT           0x06   // ACK //
#define   IEC_COMM_COMMAND                          0X01   // SOH  //

#define UART_BUFF_MAX_LENTH 170  //���ݻ������ֽڳ������100  //
#define UART_BUFF_MIN_SIZE 12       //��С���ݳ���Ϊ12�ֽ�  //


//  ��ʼ�������ݵĹ̶��ֳ�����  //
#define IEC_START_LENTH05   5      // no meter id
#define IEC_START_LENTH13	13    // with  meter id 12λ

#define IEC_START_LENTH17	17    // with meter id	8λ


#define Meter_INFO_LENTH  16     //�����Ϣ���鳤��   //
#define MIMA_INFO_LENTH   10    // ��������ʶ���鳤�� //

/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
//ͨѶ��
typedef struct 
{
	INT32U 	ComID;
	INT8U 	*Addr;
  	INT16U 	ComInfo;
	INT8U 	Len;
	INT8U     Len_Asc;
}IEC_COMDISTAB;


 typedef struct 
{
    ST_U16_U08	    Info;
    ST_U32_U08	    di1_di0;
   INT8U                             *addr;//INT16U                             addr;
    INT8U                               len;
    INT8U                               len_asc;
    INT8U                               id_mode;
} COMM_DATA;


//ͨѶ�����е�Ӧ�ò�������� //
typedef struct 
{
    INT8U                        len;                                      //���շ���֡���ݳ���//
    INT8U                        baud_rate;                             //ͨѶ�������ݴ�//
    INT8U                        err_flg;                                //��·�����״̬�ݴ�//
    INT8U                        iec_status;                            //ͨѶģʽ//
    INT16U                      delay_10ms;                         //  ���ֳɹ����3S���еȴ���λ��ʱ�Ĵ���    //
    INT16U                      tx_ready_10ms;                   //�������ݳɹ���������ǰ����ʱ   //
    INT8U                        tx_delay_flg;
    INT8U                        start_index;
} UART_COMM_APP_VAR;

/***************************************************************
*    3    ��������       
****************************************************************/
extern uint8 *P_IEC_BUFF;    //ͨѶ������ָ�� //
extern uint8 g_ch_comm;   //��ǰͨѶͨ���� //
extern UART_COMM_APP_VAR  gs_uart_iec_app_var[UART_CH_NUM];


/***************************************************************
*    4     ��������        
****************************************************************/
extern INT8U get_meter_id_asclen(INT8U *Addr,INT8U numbyte);
extern INT8U  get_IEC_comm_var( INT32U id );
extern INT8U SecurityCK(void);
extern INT8U IEC_Cmd_Password_Deal(INT8U* sptr);
extern INT8U IEC_Cmd_Read_Deal(INT8U* sptr);
extern INT8U IEC_Cmd_Write_Deal(INT8U* sptr,INT8U len);
extern INT8U IEC_Cmd_Break_Deal(INT8U* sptr);

extern void lnk_tx_comm_ready( uint8 ch,uint8 start_index);
extern void api_handl_COMM_FRAME_ERROR( uint8 ch);
extern void process_iec62056_21 (INT8U ch);
extern void api_handl_COMM_pre_10ms(uint8 ch);


/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/
// ComInfo  define 
// 11000000 00000000    read or program ability  
#define EN_R   0X8000            //enable read
#define EN_W   0x4000            //enable program
#define EN_RW  0xc000
#define EN_E   0x0000		// Execute

//00111000 00000000    operate data type        
#define P_RAM    	0x0800*1
#define P_E2P1   	(0x0800*2)		//P_DMFLASH//
#define P_DMFLASH   (0x0800*MEM_DMFLASH)//
#define P_RTC    	0x0800*8

// 00000111 00000000  operate security level
#define W_MM  0x0100*0           // ����Ȩ��
#define W_HKEY  0x0100*1         // ��̰���
#define W_SKEY  0x0100*2         // also by sofy-key control
#define W_FCT  0x0100*3          // ��������
#define W_CLR  0x0100*4         //��������  
#define W_SETM	0x0100*5     //��������c=0F


// 00000000 11110000  special command operate
#define CM_ALL      0X0010*15         //����ȡֵʹ��
#define CM_NOMAL 0x0010*0         //������Ŀ
#define CM_BILL     0x0010*1         //���˵�����
#define CM_SET_TIME     0x0010*2         //����ʱ������
#define CM_SET_LIMIT     0x0010*3         //������Ŀ
#define CM_BILL_48HOUR     0x0010*4         //��48Сʱ�����˵�����//
#define CM_EBIL			0x0010*5			//���¼���¼ ��δ���˵����ݺϲ�//


// uart_vomm_app_avr.iec_status   bit define
#define COMM_INFO_OK_IEC            0X01     // bit0 
#define COMM_REQUIST_OK_IEC       0x02     //  ����������Ч //
#define COMM_MIMA_OK_IEC           0X04     //  ������֤��Ч //
#define COMM_CMD_OK_IEC            0X08     //  ������֤��Ч //
#define COMM_BREAK_OK_IEC         0X10     //  ��ָֹ����Ч //

//uart_vomm_app_avr.err_flg define
#define  FRAME_ERROR     0X01     //֡������Ҫ��λ  //


/***************************************************************
*    END
****************************************************************/

#endif
