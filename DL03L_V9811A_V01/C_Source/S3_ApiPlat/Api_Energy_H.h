/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Energy_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: ���ܼ���Ӧ�ò���غ������������ļ�
**note			: MCU- G80F92XD ��MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-20   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/



#ifndef _Api_Energy_H
#define _Api_Energy_H

//******************************************************************
//              1     ������Ԥ����                                                                 
//******************************************************************


//******************************************************************
//               2     ���ݽṹ����                               
//******************************************************************
//�ۼƵ������ݵ�Ԫ�ṹ  //
typedef union
{
	uint8 buf[6];
	struct
	{
	  uint32 integ_hex32;   // ���������������֣�32λ16�������ݣ�����1kWh //
	  uint16 decim_hex16;   // ��������С�����֣�16λ16�������ݣ�����(1/�����)kWh //
	}val;
}US_EC_DATA_UNIT;

//��ǰ�������ݵ�Ԫ�ṹ  //
typedef struct 
{
	US_EC_DATA_UNIT   us_val[EC_CH_NUM][1+TARIFF_MAX_NUM];
    INT16U  u16_csck;    //16λ�ۼӺ�У��ֵ//
} ENERGY_USER_DATA;

//��ǰ���������������ݽṹ //
typedef struct 
{
    uint8   pluse[EC_CH_NUM];
} ENERGY_VAR;



//��ǰ��������E2P�洢���ݽṹ  //
typedef struct 
{
    US_EC_DATA_UNIT   us_val[EC_CH_NUM][1+TARIFF_MAX_NUM];
    INT16U  u16_csck;    //16λ�ۼӺ�У��ֵ//
} E2P_CURRENT_ENERGY_DATA_MAP;

//******************************************************************
//              3    ��������                                      
//******************************************************************
extern ENERGY_USER_DATA    gs_energy_user_data;
extern ENERGY_USER_DATA    gs_energy_user_data_back;
extern ENERGY_VAR               gs_energy_var;

//******************************************************************
//             4     ��������                                      
//******************************************************************
extern void api_init_current_energy_data_ram(void);
extern void api_check_current_energy_data(void);
extern uint8 lnk_add_energy_pluse(void);
extern void api_accum_current_energy_data_pre_second(void);
extern void api_clr_current_energy_data(void);


//******************************************************************
//             5     �������ݣ�����αָ���             
//******************************************************************
//�������ݵ�Ԫ���� //
#define LEN_EC_UNIT			sizeof(US_EC_DATA_UNIT)    
#define LEN_EC_CURRENT		( EC_CH_NUM*(1+TARIFF_MAX_NUM)*LEN_EC_UNIT)
#define LEN_EC_E2P         sizeof(ENERGY_USER_DATA)




/***************************************************************
*    END
****************************************************************/
#endif

