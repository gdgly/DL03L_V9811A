/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Api_Measure_H.H
**Author: maji
**date: 
**description:  ��������Ӧ�ò���غ�������
**note: memer type  SD03A
**--------------------Version History -------------------------------------
** NO.	Date        		Ver    		By     			Description 
**==============================================================
** 1    2015-10-12  		0.1  		sosomj   		1. frist version                             
**
**==============================================================
*/


#ifndef _Api_Bill_Record_H
#define _Api_Bill_Record_H

#if (BILL_MAX_NUM>0)
/***************************************************************
*    1     ������Ԥ����   
****************************************************************/
//bill info index define 
#define  BILL_ID0_MOTTH_SETTL         0            //�½���������ID //

#define  MAX_Fill_SETTLED_MONTHS      12     //����ϵ粹��������� //

/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/

typedef struct 
{
    INT16U     head_adr;
    INT16U     ptr_adr;
    INT16U     data_size;
    INT8U       ptr_num;
    INT8U       mem_type;
} BILL_INFO;
 

typedef struct 
{
    INT8U                                   u8_RTC_record[6];           //������ʱ����  //
    US_EC_DATA_UNIT                 ec_val[EC_CH_NUM][1+TARIFF_MAX_NUM];
    MMD_DATA_UNIT                   mmd_val[EC_CH_NUM][1+TARIFF_MAX_NUM];
} BILL_DATA_UNIT;

typedef struct 
{
    INT8U   ptrNo;                      //��ǰ��������ָ��  //
    INT8U   dateTime[6];   //������ʱ����  //
} BILL_EXRAM_VAR;

typedef struct 
{
    INT8U   u8_ddhh[2];             // [0]=day,[1]=hour //
} BILL_MONTH_SETTLED_PARAM;


//���з����������E2P�洢���ݽṹ  //
typedef struct 
{
    BILL_DATA_UNIT  bill_data;
    INT16U  bill_data_csck;    //16λ�ۼӺ�У��ֵ//
} E2P_BILL_DATA_MAP_ONE;


typedef struct 
{
    BILL_EXRAM_VAR  bill_var;
    INT16U  bill_var_csck;    //16λ�ۼӺ�У��ֵ//
} E2P_BILL_VAR_MAP;

/***************************************************************
*    3    ��������       
****************************************************************/



/***************************************************************
*    4     ��������        
****************************************************************/
extern INT16U api_get_bill_record_addr( INT16U addr );
extern void api_handl_settle_per_minute(void);
extern void api_handl_settle_when_powerUp(void);
extern void api_clr_bill_data(void);


/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/
// �ⲿ�洢�洢���ݳ��ȶ��� //
#define LEN_BILL_DATA_UNIT	    (sizeof(BILL_DATA_UNIT) )
#define LEN_BILL_EXRAM_VAR	    (sizeof(BILL_EXRAM_VAR) )

#define BILL_BUFF_MAX_LEN       LEN_BILL_DATA_UNIT   // ����˵����ݳ��� //

// �ⲿ�洢�洢����ƫ�����ͳ��ȶ��� //
     // E2P_BILL_VAR_MAP  //
#define OFFSET_bill_var                 ST_MB_OFFSET(E2P_BILL_VAR_MAP,bill_var)
#define OFFSET_bill_var_csck         ST_MB_OFFSET(E2P_BILL_VAR_MAP,bill_var_csck)
#define LEN_bill_var	                   (OFFSET_bill_var_csck+2)

#define OFFSET_bill_var_ptrNo           OFFSET_bill_var+ ST_MB_OFFSET(BILL_EXRAM_VAR,ptrNo)   
#define LEN_bill_var_ptrNo                  ST_MB_LEN(BILL_EXRAM_VAR,ptrNo)     
#define OFFSET_bill_var_dateTime       OFFSET_bill_var+ ST_MB_OFFSET(BILL_EXRAM_VAR,dateTime)   
#define LEN_bill_var_dateTime             6  //���1�ν���ʱ������� YYMMDD hhmmss  //  

    // E2P_BILL_DATA_MAP  //
#define OFFSET_bill1_data              ST_MB_OFFSET(E2P_BILL_DATA_MAP_ONE,bill_data)
#define OFFSET_bill1_data_csck         ST_MB_OFFSET(E2P_BILL_DATA_MAP_ONE,bill_data_csck)
#define LEN_bill1_data	                (OFFSET_bill1_data_csck+2)

#define OFFSET_bill_data_dateTime       ST_MB_OFFSET(BILL_DATA_UNIT,u8_RTC_record)       
#define OFFSET_bill_data_ec                 ST_MB_OFFSET(BILL_DATA_UNIT,ec_val) 
#define OFFSET_bill_data_mmd             ST_MB_OFFSET(BILL_DATA_UNIT,mmd_val)         



#endif

/***************************************************************
*    END
****************************************************************/

#endif
