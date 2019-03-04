/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_User_Comm.c
**Author		: maji
**date			: 2016-04-21 
**description	: ͨѶ����Ӧ�ò���غ�������C�ļ�
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/



#include <MyIncludes_H.h>


/*******************************************************************************
* ȫ�ֱ���������
*******************************************************************************/
uint8 *P_IEC_BUFF;    //ͨѶ������ָ�� //
uint8 g_ch_comm;   //��ǰͨѶͨ���� //
UART_COMM_APP_VAR  gs_uart_iec_app_var[UART_CH_NUM];
COMM_DATA  comm_data;


/*******************************************************************************
* ��������
*******************************************************************************/
code INT8U Super_mima_iec[8] ={'4','5','6','1','2','3','0','0'};
code INT8U meter_info[Meter_INFO_LENTH] = {'X','L','E','3','D','D','S','3','1','1','-','7','V','4','.','1',};	// ��ΪԶ���⣬��չΪ2400bps//
code INT8U meter_info_IR[Meter_INFO_LENTH] = {'X','L','E','2','D','D','S','3','1','1','-','7','V','4','.','1',};	// ��ΪԶ���⣬��չΪ2400bps//
code INT8U mima_info[MIMA_INFO_LENTH] = {'(','1','1','1','1','1','1','1','1',')',};

/*********************************************************************************************************
**  ͨѶID���
********************************************************************************************************/
 code IEC_COMDISTAB    IEC_ComDisTab[] =
{
    // �й����������//
    0x00010000, &gs_energy_user_data.us_val[EC_CH_AC_PT_TT][TARIFF_T].buf[0],	EN_R+P_RAM,	4,8,	//��ǰ�ܵ���
    0x00010001, ADR_BLOCK101_BILL1_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL ,4,8,	//��1�µ���
    0x00010002, ADR_BLOCK102_BILL2_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��2�µ���
    0x00010003, ADR_BLOCK103_BILL3_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��3�µ���
    0x00010004, ADR_BLOCK104_BILL4_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��4�µ���
    0x00010005, ADR_BLOCK105_BILL5_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��5�µ���
    0x00010006, ADR_BLOCK106_BILL6_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��6�µ���
    0x00010007, ADR_BLOCK107_BILL7_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��7�µ���
    0x00010008, ADR_BLOCK108_BILL8_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��8�µ���
    0x00010009, ADR_BLOCK109_BILL9_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��9�µ���
    0x0001000A, ADR_BLOCK110_BILL10_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��10�µ���
    0x0001000B, ADR_BLOCK111_BILL11_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��11�µ���
    0x0001000C, ADR_BLOCK112_BILL12_DATA_E2P+(OFFSET_bill_data_ec+TARIFF_T*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��12�µ���
    // �й�����1 F1  //
    0x00010100, &gs_energy_user_data.us_val[EC_CH_AC_PT_TT][TARIFF1].buf[0],	EN_R+P_RAM,	4,8,	//��ǰ�ܵ���
    0x00010101,	ADR_BLOCK101_BILL1_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL ,4,8,	//��1�µ���
    0x00010102,	ADR_BLOCK102_BILL2_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��2�µ���
    0x00010103,	ADR_BLOCK103_BILL3_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��3�µ���
    0x00010104,	ADR_BLOCK104_BILL4_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��4�µ���
    0x00010105,	ADR_BLOCK105_BILL5_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��5�µ���
    0x00010106,	ADR_BLOCK106_BILL6_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��6�µ���
    0x00010107,	ADR_BLOCK107_BILL7_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��7�µ���
    0x00010108,	ADR_BLOCK108_BILL8_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��8�µ���
    0x00010109,	ADR_BLOCK109_BILL9_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��9�µ���
    0x0001010A,	ADR_BLOCK110_BILL10_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��10�µ���
    0x0001010B,	ADR_BLOCK111_BILL11_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��11�µ���
    0x0001010C,	ADR_BLOCK112_BILL12_DATA_E2P+(OFFSET_bill_data_ec+TARIFF1*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��12�µ���
    // �й�����2 F2
    0x00010200, &gs_energy_user_data.us_val[EC_CH_AC_PT_TT][TARIFF2].buf[0],	EN_R+P_RAM,	4,8,	//��ǰ�ܵ���
    0x00010201,	ADR_BLOCK101_BILL1_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL ,4,8,	//��1�µ���
    0x00010202,	ADR_BLOCK102_BILL2_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��2�µ���
    0x00010203,	ADR_BLOCK103_BILL3_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��3�µ���
    0x00010204,	ADR_BLOCK104_BILL4_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��4�µ���
    0x00010205,	ADR_BLOCK105_BILL5_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��5�µ���
    0x00010206,	ADR_BLOCK106_BILL6_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��6�µ���
    0x00010207,	ADR_BLOCK107_BILL7_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��7�µ���
    0x00010208,	ADR_BLOCK108_BILL8_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��8�µ���
    0x00010209,	ADR_BLOCK109_BILL9_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��9�µ���
    0x0001020A,	ADR_BLOCK110_BILL10_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��10�µ���
    0x0001020B,	ADR_BLOCK111_BILL11_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��11�µ���
    0x0001020C,	ADR_BLOCK112_BILL12_DATA_E2P+(OFFSET_bill_data_ec+TARIFF2*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��12�µ���
    // �й�����3 F3
    0x00010300,  &gs_energy_user_data.us_val[EC_CH_AC_PT_TT][TARIFF3].buf[0],	EN_R+P_RAM,	4,8,	//��ǰ�ܵ���
    0x00010301,	ADR_BLOCK101_BILL1_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL ,4,8,	//��1�µ���
    0x00010302,	ADR_BLOCK102_BILL2_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��2�µ���
    0x00010303,	ADR_BLOCK103_BILL3_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��3�µ���
    0x00010304,	ADR_BLOCK104_BILL4_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��4�µ���
    0x00010305,	ADR_BLOCK105_BILL5_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��5�µ���
    0x00010306,	ADR_BLOCK106_BILL6_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��6�µ���
    0x00010307,	ADR_BLOCK107_BILL7_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��7�µ���
    0x00010308,	ADR_BLOCK108_BILL8_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��8�µ���
    0x00010309,	ADR_BLOCK109_BILL9_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��9�µ���
    0x0001030A,	ADR_BLOCK110_BILL10_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��10�µ���
    0x0001030B,	ADR_BLOCK111_BILL11_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��11�µ���
    0x0001030C,	ADR_BLOCK112_BILL12_DATA_E2P+(OFFSET_bill_data_ec+TARIFF3*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��12�µ���
    // �й�����4 F4
    0x00010400, &gs_energy_user_data.us_val[EC_CH_AC_PT_TT][TARIFF4].buf[0],	EN_R+P_RAM,	4,8,	//��ǰ�ܵ���
    0x00010401,	ADR_BLOCK101_BILL1_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL ,4,8,	//��1�µ���
    0x00010402,	ADR_BLOCK102_BILL2_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��2�µ���
    0x00010403,	ADR_BLOCK103_BILL3_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��3�µ���
    0x00010404,	ADR_BLOCK104_BILL4_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��4�µ���
    0x00010405,	ADR_BLOCK105_BILL5_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��5�µ���
    0x00010406,	ADR_BLOCK106_BILL6_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��6�µ���
    0x00010407,	ADR_BLOCK107_BILL7_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��7�µ���
    0x00010408,	ADR_BLOCK108_BILL8_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��8�µ���
    0x00010409,	ADR_BLOCK109_BILL9_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��9�µ���
    0x0001040A,	ADR_BLOCK110_BILL10_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��10�µ���
    0x0001040B,	ADR_BLOCK111_BILL11_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��11�µ���
    0x0001040C,	ADR_BLOCK112_BILL12_DATA_E2P+(OFFSET_bill_data_ec+TARIFF4*LEN_EC_UNIT),	EN_R+P_E2P1+CM_BILL,4,8,	//��12�µ���

    //���� ��
    0x01010000,	ADR_BLOCK01_MMD_L0_E2P+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1,8,16,//��ǰ���������� 3+5 ����+ʱ��
    0x01010001,	ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010002,	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010003,	ADR_BLOCK103_BILL3_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010004,	ADR_BLOCK104_BILL4_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010005,	ADR_BLOCK105_BILL5_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010006,	ADR_BLOCK106_BILL6_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010007,	ADR_BLOCK107_BILL7_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010008,	ADR_BLOCK108_BILL8_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010009,	ADR_BLOCK109_BILL9_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101000A,	ADR_BLOCK110_BILL10_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101000B,	ADR_BLOCK111_BILL11_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT), EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101000C,	ADR_BLOCK112_BILL12_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF_T*LEN_MMD_UNIT),EN_R+P_E2P1+CM_BILL,8,16,//��1��������
	//���� F1
	0x01010100,	ADR_BLOCK01_MMD_L0_E2P+(TARIFF1*LEN_MMD_UNIT), EN_R+P_E2P1,8,16,//��ǰ���������� 3+5 ����+ʱ��
    0x01010101,	ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010102,	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010103,	ADR_BLOCK103_BILL3_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010104,	ADR_BLOCK104_BILL4_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010105,	ADR_BLOCK105_BILL5_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010106,	ADR_BLOCK106_BILL6_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010107,	ADR_BLOCK107_BILL7_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010108,	ADR_BLOCK108_BILL8_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010109,	ADR_BLOCK109_BILL9_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101010A,	ADR_BLOCK110_BILL10_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101010B,	ADR_BLOCK111_BILL11_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101010C,	ADR_BLOCK112_BILL12_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF1*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
	//���� F2
	0x01010200,	ADR_BLOCK01_MMD_L0_E2P+(TARIFF2*LEN_MMD_UNIT), EN_R+P_E2P1,8,16,//��ǰ���������� 3+5 ����+ʱ��
    0x01010201,	ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010202,	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010203,	ADR_BLOCK103_BILL3_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010204,	ADR_BLOCK104_BILL4_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010205,	ADR_BLOCK105_BILL5_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010206,	ADR_BLOCK106_BILL6_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010207,	ADR_BLOCK107_BILL7_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010208,	ADR_BLOCK108_BILL8_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010209,	ADR_BLOCK109_BILL9_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101020A,	ADR_BLOCK110_BILL10_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101020B,	ADR_BLOCK111_BILL11_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101020C,	ADR_BLOCK112_BILL12_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF2*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
	//���� F3
	0x01010300,	ADR_BLOCK01_MMD_L0_E2P+(TARIFF3*LEN_MMD_UNIT), EN_R+P_E2P1,8,16,//��ǰ���������� 3+5 ����+ʱ��
    0x01010301,	ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010302,	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010303,	ADR_BLOCK103_BILL3_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010304,	ADR_BLOCK104_BILL4_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010305,	ADR_BLOCK105_BILL5_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010306,	ADR_BLOCK106_BILL6_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010307,	ADR_BLOCK107_BILL7_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010308,	ADR_BLOCK108_BILL8_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010309,	ADR_BLOCK109_BILL9_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101030A,	ADR_BLOCK110_BILL10_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101030B,	ADR_BLOCK111_BILL11_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101030C,	ADR_BLOCK112_BILL12_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF3*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
	//���� F4  //
	0x01010400,	ADR_BLOCK01_MMD_L0_E2P+(TARIFF4*LEN_MMD_UNIT), EN_R+P_E2P1,8,16,//��ǰ���������� 3+5 ����+ʱ��
    0x01010401,	ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010402,	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010403,	ADR_BLOCK103_BILL3_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010404,	ADR_BLOCK104_BILL4_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010405,	ADR_BLOCK105_BILL5_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010406,	ADR_BLOCK106_BILL6_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010407,	ADR_BLOCK107_BILL7_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010408,	ADR_BLOCK108_BILL8_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x01010409,	ADR_BLOCK109_BILL9_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT), 	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101040A,	ADR_BLOCK110_BILL10_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101040B,	ADR_BLOCK111_BILL11_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
    0x0101040C,	ADR_BLOCK112_BILL12_DATA_E2P+OFFSET_bill_data_mmd+(TARIFF4*LEN_MMD_UNIT),	EN_R+P_E2P1+CM_BILL,8,16,//��1��������
///////////////////�½���ʱ�������////////////////////////////////////////////////////////////////////////////////
    0x03700101, ADR_BLOCK101_BILL1_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��1�½���ʱ����¼//
    0x03700102, ADR_BLOCK102_BILL2_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��2�½���ʱ����¼//
    0x03700103, ADR_BLOCK103_BILL3_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��3�½���ʱ����¼//
    0x03700104, ADR_BLOCK104_BILL4_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��4�½���ʱ����¼//
    0x03700105, ADR_BLOCK105_BILL5_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��5�½���ʱ����¼//
    0x03700106, ADR_BLOCK106_BILL6_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��6�½���ʱ����¼//
    0x03700107, ADR_BLOCK107_BILL7_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��7�½���ʱ����¼//
    0x03700108, ADR_BLOCK108_BILL8_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��8�½���ʱ����¼//
    0x03700109, ADR_BLOCK109_BILL9_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��9�½���ʱ����¼//
    0x0370010A, ADR_BLOCK110_BILL10_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��10�½���ʱ����¼//
    0x0370010B, ADR_BLOCK111_BILL11_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��11�½���ʱ����¼//
    0x0370010C, ADR_BLOCK112_BILL12_DATA_E2P+(OFFSET_bill_data_dateTime),	EN_R+P_E2P1+CM_BILL ,6,12,	//��12�½���ʱ����¼//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //��������  //
    0x02010000,&gs_measure_var_data.gs_really[0].dw_u_val.B08[0],	EN_R+P_RAM,	2,4,	//�����ѹ xxx.x		 YYY
    0x02010100,&gs_measure_var_data.gs_really[0].dw_u_val.B08[0],	EN_R+P_RAM,	2,4,	//A���ѹ xxx.x		 YYY
    0x02020000,&gs_measure_var_data.gs_really[0].dw_i_val.B08[0],	EN_R+P_RAM,	3,6,	//�������   XXX.XXX
    0x02020100,&gs_measure_var_data.gs_really[0].dw_i_val.B08[0],	EN_R+P_RAM,	3,6,	//A�����   XXX.XXX
    0x02030000,&gs_measure_var_data.gs_really[0].dw_p_val.B08[0],     EN_R+P_RAM,	3,6,	// TOTAL ACTIVE POWER   XX.XXXX 
    0x02030100,&gs_measure_var_data.gs_really[0].dw_p_val.B08[0],     EN_R+P_RAM,	3,6,	// A�� ACTIVE POWER   XX.XXXX 
    0x02060000,&gs_measure_var_data.gs_really[0].dw_pf_val.B08[0],	 EN_R+P_RAM,2,4,	//���๦������  X.XXX
    0x02060100,&gs_measure_var_data.gs_really[0].dw_pf_val.B08[0],	 EN_R+P_RAM,2,4,	// A�๦������  X.XXX
    0x02800002,&gs_measure_var_data.gs_really[0].w_freq_val.B08[0],    EN_R+P_RAM,2,4,	//Ƶ��  XX.XX
    0x02800003,&gs_md_var.min_var[0].val_min,    EN_R+P_RAM,3,6,	//��ǰ������������ XX.XXXX 
    0x02800006,&gs_measure_var_data.w_temp.B08[0],    EN_R+P_RAM,2,4,	//�¶� XX.XX
    0x02800007,&gs_measure_var_data.w_bat_v.B08[0],    EN_R+P_RAM,2,4,	//��ص�ѹXX.XX
    0x02900001,&gs_current_triff_var.triff_No,    EN_R+P_RAM,1,2,	//��ǰ���� 1~4//
    0x02900002,&gs_current_triff_var.dayTab_No,    EN_R+P_RAM,1,2,	//��ǰ���� 1~4//
    0x02900003,&gs_current_triff_var.weekTab_No,    EN_R+P_RAM,1,2,	//��ǰ���� 1~4//
    0x02900004,&gs_current_triff_var.seasonTab_No,    EN_R+P_RAM,1,2,	//��ǰ���� 1~4//


    // һ���¼�  //
    //������λ   //
    0x03500000, ADR_BLOCK151_EVENI_resetMD_E2P,			EN_R+P_E2P1, 	2,4,	//�ܴ���//
    0x03500101, ADR_BLOCK151_EVENI_resetMD_E2P+2,		       EN_R+P_E2P1+CM_EBIL, 4,8, //���1�ε�����¼����ʱ��//
    0x03500102, (ADR_BLOCK151_EVENI_resetMD_E2P+2+ 1*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���2�ε�����¼����ʱ��//
    0x03500103, (ADR_BLOCK151_EVENI_resetMD_E2P+2+ 2*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���3�ε�����¼����ʱ��//
    0x03500104, (ADR_BLOCK151_EVENI_resetMD_E2P+2+ 3*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���4�ε�����¼����ʱ��//
    0x03500105, (ADR_BLOCK151_EVENI_resetMD_E2P+2+ 4*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���5�ε�����¼����ʱ��//
    0x03500106, (ADR_BLOCK151_EVENI_resetMD_E2P+2+ 5*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���6�ε�����¼����ʱ��//
    0x03500107, (ADR_BLOCK151_EVENI_resetMD_E2P+2+ 6*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���7�ε�����¼����ʱ��//
    0x03500108, (ADR_BLOCK151_EVENI_resetMD_E2P+2+ 7*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���8�ε�����¼����ʱ��//
    0x03500109, (ADR_BLOCK151_EVENI_resetMD_E2P+2+ 8*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���9�ε�����¼����ʱ��//
    0x0350010A, (ADR_BLOCK151_EVENI_resetMD_E2P+2+ 9*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���10�ε�����¼����ʱ��//

    //ͨѶ���//
    0x03520000,  ADR_BLOCK150_EVENI_PROG_E2P,			EN_R+P_E2P1, 	2,4,	//�ܴ���//
    0x03520101,  ADR_BLOCK150_EVENI_PROG_E2P+2,		EN_R+P_E2P1+CM_EBIL, 4,8, //���1�ε�����¼����ʱ��//
    0x03520102,  (ADR_BLOCK150_EVENI_PROG_E2P+2+ 1*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���2�ε�����¼����ʱ��//
    0x03520103,  (ADR_BLOCK150_EVENI_PROG_E2P+2+ 2*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���3�ε�����¼����ʱ��//
    0x03520104,  (ADR_BLOCK150_EVENI_PROG_E2P+2+ 3*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���4�ε�����¼����ʱ��//
    0x03520105,  (ADR_BLOCK150_EVENI_PROG_E2P+2+ 4*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���5�ε�����¼����ʱ��//
    0x03520106,  (ADR_BLOCK150_EVENI_PROG_E2P+2+ 5*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���6�ε�����¼����ʱ��//
    0x03520107,  (ADR_BLOCK150_EVENI_PROG_E2P+2+ 6*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���7�ε�����¼����ʱ��//
    0x03520108,  (ADR_BLOCK150_EVENI_PROG_E2P+2+ 7*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���8�ε�����¼����ʱ��//
    0x03520109,  (ADR_BLOCK150_EVENI_PROG_E2P+2+ 8*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���9�ε�����¼����ʱ��//
    0x0352010A,  (ADR_BLOCK150_EVENI_PROG_E2P+2+ 9*4),	EN_R+P_E2P1+CM_EBIL, 4,8,//���10�ε�����¼����ʱ��//

    //ʱ��У׼
    0x03570000,  ADR_BLOCK152_EVENI_setRtc_E2P,			EN_R+P_E2P1, 	2,4,	//�ܴ���//
    0x03570101,  ADR_BLOCK152_EVENI_setRtc_E2P+2,		    	EN_R+P_E2P1+CM_EBIL, 4,8,  //���1�ε�����¼����ʱ��//
    0x03570102,  (ADR_BLOCK152_EVENI_setRtc_E2P+2+ 1*4),	EN_R+P_E2P1+CM_EBIL, 4,8, //���2�ε�����¼����ʱ��//
    0x03570103,  (ADR_BLOCK152_EVENI_setRtc_E2P+2+ 2*4),	EN_R+P_E2P1+CM_EBIL, 4,8, //���3�ε�����¼����ʱ��//
    0x03570104,  (ADR_BLOCK152_EVENI_setRtc_E2P+2+ 3*4),	EN_R+P_E2P1+CM_EBIL, 4,8, //���4�ε�����¼����ʱ��//
    0x03570105,  (ADR_BLOCK152_EVENI_setRtc_E2P+2+ 4*4),	EN_R+P_E2P1+CM_EBIL, 4,8, //���5�ε�����¼����ʱ��//
    0x03570106,  (ADR_BLOCK152_EVENI_setRtc_E2P+2+ 5*4),	EN_R+P_E2P1+CM_EBIL, 4,8, //���6�ε�����¼����ʱ��//
    0x03570107,  (ADR_BLOCK152_EVENI_setRtc_E2P+2+ 6*4),	EN_R+P_E2P1+CM_EBIL, 4,8, //���7�ε�����¼����ʱ��//
    0x03570108,  (ADR_BLOCK152_EVENI_setRtc_E2P+2+ 7*4),	EN_R+P_E2P1+CM_EBIL, 4,8, //���8�ε�����¼����ʱ��//
    0x03570109,  (ADR_BLOCK152_EVENI_setRtc_E2P+2+ 8*4),	EN_R+P_E2P1+CM_EBIL, 4,8, //���9�ε�����¼����ʱ��//
    0x0357010A,  (ADR_BLOCK152_EVENI_setRtc_E2P+2+ 9*4),	EN_R+P_E2P1+CM_EBIL, 4,8, //���10�ε�����¼����ʱ��//

   //���Ƿѹ ���⴦��  ֻ��������ʱ��//	
	0x03590000,   ADR_BLOCK162_EVENII_lowbattery_E2P,            EN_R+P_E2P1, 2,4,	//�ܴ���
	0x03590001,   ADR_BLOCK162_EVENII_lowbattery_E2P+2,          EN_R+P_E2P1, 4,8,	//�ۼ�ʱ��
	0x03590101,   ADR_BLOCK162_EVENII_lowbattery_E2P+6,		     EN_R+P_E2P1+CM_EBIL, 12,24,	 //���һ�ε�����¼  �¼����� ��ʼʱ�� ����ʱ��
	0x03590102,  (ADR_BLOCK162_EVENII_lowbattery_E2P+6+ 1*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03590103,  (ADR_BLOCK162_EVENII_lowbattery_E2P+6+ 2*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03590104,  (ADR_BLOCK162_EVENII_lowbattery_E2P+6+ 3*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03590105,  (ADR_BLOCK162_EVENII_lowbattery_E2P+6+ 4*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03590106,  (ADR_BLOCK162_EVENII_lowbattery_E2P+6+ 5*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03590107,  (ADR_BLOCK162_EVENII_lowbattery_E2P+6+ 6*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,//������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03590108,  (ADR_BLOCK162_EVENII_lowbattery_E2P+6+ 7*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03590109,  (ADR_BLOCK162_EVENII_lowbattery_E2P+6+ 8*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x0359010A,  (ADR_BLOCK162_EVENII_lowbattery_E2P+6+ 9*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,//������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��

//	0x0359FFFF,  ADR_BLOCK162_EVENII_lowbattery_E2P+6,	         EN_R+P_E2P1, 60,120,//��ʼ��¼  6*10��
	
	// ��Դ����  //	
	0x03380000,  ADR_BLOCK161_EVENII_PWN_E2P,                      EN_R+P_E2P1, 	2,4,	//�ܴ���
	0x03380001,  ADR_BLOCK161_EVENII_PWN_E2P+2,                  EN_R+P_E2P1, 	4,8,	//�ۼ�ʱ��
	0x03380101,  ADR_BLOCK161_EVENII_PWN_E2P+6,		        EN_R+P_E2P1+CM_EBIL, 12,24, 		 //���һ�ε�����¼  �¼����� ��ʼʱ�� ����ʱ��
	0x03380102,  (ADR_BLOCK161_EVENII_PWN_E2P+6+ 1*6),	 EN_R+P_E2P1+CM_EBIL, 12,24, ///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03380103,  (ADR_BLOCK161_EVENII_PWN_E2P+6+ 2*6),	 EN_R+P_E2P1+CM_EBIL, 12,24, ///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03380104,  (ADR_BLOCK161_EVENII_PWN_E2P+6+ 3*6),	 EN_R+P_E2P1+CM_EBIL, 12,24, ///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03380105,  (ADR_BLOCK161_EVENII_PWN_E2P+6+ 4*6),	  EN_R+P_E2P1+CM_EBIL, 12,24, ///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03380106,  (ADR_BLOCK161_EVENII_PWN_E2P+6+ 5*6),	  EN_R+P_E2P1+CM_EBIL, 12,24, ///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03380107,  (ADR_BLOCK161_EVENII_PWN_E2P+6+ 6*6),	 EN_R+P_E2P1+CM_EBIL, 12,24, //������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03380108,  (ADR_BLOCK161_EVENII_PWN_E2P+6+ 7*6),	  EN_R+P_E2P1+CM_EBIL, 12,24, ///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03380109,  (ADR_BLOCK161_EVENII_PWN_E2P+6+ 8*6),	  EN_R+P_E2P1+CM_EBIL, 12,24, ///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x0338010A,  (ADR_BLOCK161_EVENII_PWN_E2P+6+ 9*6),	  EN_R+P_E2P1+CM_EBIL, 12,24, ///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��

	//COVER_//
	0x03450000,  ADR_BLOCK163_EVENII_COVER_E2P,           EN_R+P_E2P1, 	2,4,	//�ܴ���
	0x03450001,  ADR_BLOCK163_EVENII_COVER_E2P+2,         EN_R+P_E2P1, 	4,8,	//�ܴ���
	0x03450101,  ADR_BLOCK163_EVENII_COVER_E2P+6,		      EN_R+P_E2P1+CM_EBIL, 12,24,		 //���һ�ε�����¼  �¼����� ��ʼʱ�� ����ʱ��
	0x03450102,  (ADR_BLOCK163_EVENII_COVER_E2P+6+ 1*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03450103,  (ADR_BLOCK163_EVENII_COVER_E2P+6+ 2*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03450104,  (ADR_BLOCK163_EVENII_COVER_E2P+6+ 3*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03450105,  (ADR_BLOCK163_EVENII_COVER_E2P+6+ 4*6),  EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03450106,  (ADR_BLOCK163_EVENII_COVER_E2P+6+ 5*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03450107,  (ADR_BLOCK163_EVENII_COVER_E2P+6+ 6*6),  EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03450108,  (ADR_BLOCK163_EVENII_COVER_E2P+6+ 7*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x03450109,  (ADR_BLOCK163_EVENII_COVER_E2P+6+ 8*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��
	0x0345010A,  (ADR_BLOCK163_EVENII_COVER_E2P+6+ 9*6),	 EN_R+P_E2P1+CM_EBIL, 12,24,///������ε�����¼  �¼�����  ��ʼʱ�� ����ʱ��

// ���ʷ����¼�  //	
	0x03360000,  ADR_BLOCK164_EVENII_L1reverse_E2P,                       EN_R+P_E2P1, 	2,4,	//�ܴ���
	0x03360001, ( ADR_BLOCK164_EVENII_L1reverse_E2P+2),                EN_R+P_E2P1, 	4,8,	//���ۼ�ʱ��//
	0x03360101,  (ADR_BLOCK164_EVENII_L1reverse_E2P+6),                EN_R+P_E2P1+CM_EBIL, 	12,24,	//��ʼʱ��+����ʱ��//
	0x03360102, ( ADR_BLOCK164_EVENII_L1reverse_E2P+6+1*6),         EN_R+P_E2P1+CM_EBIL, 	12,24,	//��ʼʱ��+����ʱ��//
	0x03360103,  (ADR_BLOCK164_EVENII_L1reverse_E2P+6+2*6),         EN_R+P_E2P1+CM_EBIL, 	12,24,	//��ʼʱ��+����ʱ��//
	0x03360104, ( ADR_BLOCK164_EVENII_L1reverse_E2P+6+3*6),         EN_R+P_E2P1+CM_EBIL, 	12,24,	//��ʼʱ��+����ʱ��//
	0x03360105, ( ADR_BLOCK164_EVENII_L1reverse_E2P+6+4*6),         EN_R+P_E2P1+CM_EBIL, 	12,24,	//��ʼʱ��+����ʱ��//
	0x03360106, ( ADR_BLOCK164_EVENII_L1reverse_E2P+6+5*6),         EN_R+P_E2P1+CM_EBIL, 	12,24,	//��ʼʱ��+����ʱ��//
	0x03360107,  (ADR_BLOCK164_EVENII_L1reverse_E2P+6+6*6),         EN_R+P_E2P1+CM_EBIL, 	12,24,	//��ʼʱ��+����ʱ��//
	0x03360108, ( ADR_BLOCK164_EVENII_L1reverse_E2P+6+7*6),         EN_R+P_E2P1+CM_EBIL, 	12,24,	//��ʼʱ��+����ʱ��//
	0x03360109, ( ADR_BLOCK164_EVENII_L1reverse_E2P+6+8*6),         EN_R+P_E2P1+CM_EBIL, 	12,24,	//��ʼʱ��+����ʱ��//
	0x0336010A,  (ADR_BLOCK164_EVENII_L1reverse_E2P+6+9*6),         EN_R+P_E2P1+CM_EBIL, 	12,24,	//��ʼʱ��+����ʱ��//


//
    0x04000100,&gs_CurDateTime.Week,				EN_RW+P_RAM,7,14,	//ע�����ڣ�ͨѶ��д˳�� YYMMDDWWhhmmss
    0x04000103,ADR_METER_PARAM1_MD,			       EN_RW+P_E2P1,	2,	4,	//�����������,����ʱ��//

    0x04000801,ADR_BLOCK83_WEEK_TAB_E2P	,			EN_RW+P_E2P1,LEN_WEEK_TABLE_ONE,(2*LEN_WEEK_TABLE_ONE),	//�ܱ���ʼ��ַ(4���ܱ�)	
    0x04000802,ADR_BLOCK83_WEEK_TAB_E2P+(1*LEN_WEEK_TABLE_ONE),		EN_RW+P_E2P1,LEN_WEEK_TABLE_ONE,(2*LEN_WEEK_TABLE_ONE),	//�ܱ���ʼ��ַ(4���ܱ�)
    0x04000803,ADR_BLOCK83_WEEK_TAB_E2P+(2*LEN_WEEK_TABLE_ONE),		EN_RW+P_E2P1,LEN_WEEK_TABLE_ONE,(2*LEN_WEEK_TABLE_ONE),	//�ܱ���ʼ��ַ(4���ܱ�)
    0x04000804,ADR_BLOCK83_WEEK_TAB_E2P+(3*LEN_WEEK_TABLE_ONE),		EN_RW+P_E2P1,LEN_WEEK_TABLE_ONE,(2*LEN_WEEK_TABLE_ONE),	//�ܱ���ʼ��ַ(4���ܱ�) 
 
	0x04010000,ADR_BLOCK82_SEASON_TAB_E2P,	             EN_RW+P_E2P1,LEN_SEASON_TABLE, (2*LEN_SEASON_TABLE),    // ���ڱ� 8*3  ����+�ܱ��
	0x04010001,ADR_BLOCK84_DAY_TAB_E2P,				EN_RW+P_E2P1,LEN_DAY_TABLE_ONE, (2*LEN_DAY_TABLE_ONE),//ʱ�α�1  ʱ�α���ʼ��ַ(8��ʱ�α�10��ʱ����)  288      BCD  hhnnNN          
	0x04010002,ADR_BLOCK84_DAY_TAB_E2P+(1*LEN_DAY_TABLE_ONE),		EN_RW+P_E2P1,LEN_DAY_TABLE_ONE, (2*LEN_DAY_TABLE_ONE),//ʱ�α�2  ʱ�α���ʼ��ַ(8��ʱ�α�10��ʱ����)  288      BCD  hhnnNN          
	0x04010003,ADR_BLOCK84_DAY_TAB_E2P+(2*LEN_DAY_TABLE_ONE),		EN_RW+P_E2P1,LEN_DAY_TABLE_ONE, (2*LEN_DAY_TABLE_ONE),//ʱ�α�3  ʱ�α���ʼ��ַ(8��ʱ�α�10��ʱ����)  288      BCD  hhnnNN          
	0x04010004,ADR_BLOCK84_DAY_TAB_E2P+(3*LEN_DAY_TABLE_ONE),		EN_RW+P_E2P1,LEN_DAY_TABLE_ONE, (2*LEN_DAY_TABLE_ONE),//ʱ�α�4  ʱ�α���ʼ��ַ(8��ʱ�α�10��ʱ����)  288      BCD  hhnnNN          

	0x04000401,ADR_METER_PARAM1_METER_ID,			EN_RW+P_E2P1,16,32,	//ͨѶ��ַ ���

	0x04000409,&sys_parm.meter_cons[0],				EN_R+P_RAM,3,6,		//����	 //		

	0x04000B01,ADR_METER_PARAM1_SETL_DDHH,          EN_RW+P_E2P1,2,4,	//������
	0x04000C01,ADR_METER_PARAM1_PW0,                    EN_W+P_E2P1,4,8,		//0������

    0x04000A01,	 ADR_METER_PARAM1_load_lptime_inv_var,  	EN_RW+P_E2P1,2,4,//��¼���
    0x04000AA1,	 ADR_METER_PARAM1_load_egcode_var,            EN_RW+P_E2P1,10,20, //���ɱ����
    0x06010000,	 &LPRunPa.Num[0],				    EN_R+P_RAM,2,4, //�Ѽ�¼����
	
	//��ʾ�����//
    0x04000302,ADR_DIS_PARAM_AUTO_SEC,	        EN_RW+P_E2P1,1,2,    //�Զ�ѭ��ʱ�� 
    0x04000303,ADR_DIS_PARAM_EC_FORM,		 EN_RW+P_E2P1,1,2,    // ������ʾλ��//
    0x04000310,ADR_DIS_PARAM_BG_SEC,			 EN_RW+P_E2P1,1,2,	//�������ʱ��,BCD sec
    0x040003A0,ADR_DIS_PARAM_KEY_SEC,			 EN_RW+P_E2P1,1,2,    //����ʱ��
    0x04040100,ADR_DIS_PARAM_AUTO_TAB,		 EN_RW+P_E2P1,11,22,	//�Զ�ѭ�Ա�  //
    0x04040200,ADR_DIS_PARAM_KEY_TAB,		       EN_RW+P_E2P1,11,22,	//������ʾ�б� //
    0x04040300,ADR_DIS_PARAM_PWN_TAB,		 EN_RW+P_E2P1,10,20,	//�µ���ʾ�б�//

    0x04800001,&sys_parm.video[0],						EN_R+P_RAM,12,12,  //����汾��(ASCII)

/*	//У�����
    0x80800101,&Adjust_Param.SCP_adj_val.B08[0],	 EN_RW+P_RAM+W_FCT,4,8,// E1 ���ʱȲ�Ĵ���  // 
    0x80800102,&Adjust_Param.SCQ_adj_val.B08[0],     EN_RW+P_RAM+W_FCT,4,8,// E2 ���ʱȲ�Ĵ���  //
    0x80800103,&Adjust_Param.SCU_adj_val.B08[0],	EN_RW+P_RAM+W_FCT,4,8,// ��ѹ��Чֵ �Ȳ�Ĵ���//
    0x80800104,&Adjust_Param.SCI1_adj_val.B08[0],	EN_RW+P_RAM+W_FCT,4,8,// IA ������Чֵ3.2M �Ȳ�Ĵ���//
    0x80800105,&Adjust_Param.SCI2_adj_val.B08[0],	EN_RW+P_RAM+W_FCT,4,8,// IB ������Чֵ3.2M �Ȳ�Ĵ���   //
    0x80800106,&Adjust_Param.PARAPC_adj_val.B08[0],		EN_RW+P_RAM+W_FCT,4,8,// E1 ���ʱȲ�Ĵ���С�źŲ���ֵ//
    0x80800107,&Adjust_Param.PARAQC_adj_val.B08[0],		EN_RW+P_RAM+W_FCT,4,8,// E2 ���ʱȲ�Ĵ���С�źŲ���ֵ//
    0x80800108,&Adjust_Param.PHCCTRL1_adj_val.B08[0],	EN_RW+P_RAM+W_FCT,4,8,// I1 �ǲ���ڼĴ��� ʵ��Ϊ8λ  //
    0x80800109,&Adjust_Param.PHCCTRL2_adj_val.B08[0], 	EN_RW+P_RAM+W_FCT,4,8,// I2 �ǲ���ڼĴ��� ʵ��Ϊ8λ  //


	//ͨѶ����У��//  
    0x0000FEB0,	0x0000,							EN_W+P_E2P1+W_FCT,12,24,   //����· 1.0L IB ������ЧֵУ׼// 
    0x0000FEB1,	0x0000,							EN_W+P_E2P1+W_FCT,12,24,   //����· 0.5L IB ���У׼// 
    0x0000FEB2,	0x0000,							EN_W+P_E2P1+W_FCT,12,24,	  //�λ�·1.0L IB ���У׼// 
    0x0000FEB3,	0x0000,							EN_W+P_E2P1+W_FCT,12,24,   //�λ�·0.5L IB ���У׼// 
    0x0000FEB4,	0x0000,							EN_W+P_E2P1+W_FCT,12,24,  //�λ�·0.5L IB ���У׼// 
    0x0000FEB5,	0x0000,							EN_W+P_E2P1+W_FCT,12,24,  //�λ�·1.0L 5%IB ���У׼// 
*/

    0x80800803,     0x0000,	                                        EN_W+P_E2P1+W_FCT,2,4,// EMU����������ʼ��  // 
    
        // ����//
    0x08020100,0x0000,							EN_W+P_RAM,1,2, 	//��������/�ֶ���λ
    0x08020200,0x0000,							EN_W+P_RAM,1,2, 	//�¼���¼����
   	0x08020300,0x0000,						    EN_W+P_RAM,1,2, 		   //=00 ���ɼ�¼����  //
    0x08020400,0x0000,							EN_W+P_RAM,4,8, 	//xxxxxxxx = 00000000ʱ�����ǰ����ʷ����
    0x08020500,ADR_METER_PARAM1_FC_CFG,		EN_RW+P_E2P1,4,8,	//��������״̬�֣�1�ֽ�  // 5A:����   
    0x08020600,0x0000,							EN_W+P_RAM,1,2, 	//����������л��������=0X5A λ���������  //
    0x04000107,ADR_METER_PARAM1_BAT_LEVEL,	EN_RW+P_E2P1,	1,	2,	// ��ص�ѹ��ֵ  1 �ֽڣ�BCD  X.X 

    0x0000FEFF,0x0000,							EN_W+P_RAM,2,4, 	// ��ʼ��
};

//---------------------------------------------------------------------//
//����:   ��������ʼ��ַ��ʼ��F��ֹ�ĳ���//
//     0000F     return 4
//	*Addr ������ʼ��ַ��num���ݳ���
//---------------------------------------------------------------------//
INT8U get_meter_id_asclen(INT8U *Addr,INT8U numbyte)
{
	INT8U i;
	INT8U asclen=0;
	for(i=0;i<numbyte;i++)
	{
		if((((*(Addr+i))>>4)&0x0F)==0x0F)
		{
			return asclen;
		}
		asclen++;
		if(((*(Addr+i))&0x0F)==0x0F)
		{
			return asclen;
		}
		asclen++;
	}
	return asclen;
}


/*****************************************************************
 name:          INT8U  get_comm_var( INT16U id )
 function:      get command information precess  
 input:         no            
 return:        GetComVar()
                =0    succeed  precess 
                =1    fail precess 
*****************************************************************/
INT8U  get_IEC_comm_var( INT32U id )
{
    INT16U i;  
	
  if((id>=0x06010001)&&(id<=0x060105A0))//������������¼900��   //SXL 2019-01-6
  {
		comm_data.addr =0;
		comm_data.Info.u16 = EN_R;		//���ܻ���
		comm_data.len = 0;
		comm_data.len_asc = 0;
		return TRUE;
  }
  if((id>=0x060A0001)&&(id<=0x060A0120))//�������ݿ�����¼90��   //SXL 2019-01-6
  {
		comm_data.addr =0;
		comm_data.Info.u16 = EN_R;		//���ܻ���
		comm_data.len = 0;
		comm_data.len_asc = 0;
		return TRUE;
  }

		for( i = 0 ; i <dim(IEC_ComDisTab) ; i++ )
    {
        if( id == IEC_ComDisTab[i].ComID )
        {
            comm_data.addr = IEC_ComDisTab[i].Addr;
            comm_data.Info.u16 = IEC_ComDisTab[i].ComInfo;
            comm_data.len = IEC_ComDisTab[i].Len;
            comm_data.len_asc = IEC_ComDisTab[i].Len_Asc;
            return TRUE;
        }
    }
    return FALSE;
}

/*****************************************************************
 name:          uchar  GetComVar( uchar* Addr, uint* Info )
 function:      get command information precess  
 input:         no            
 return:        GetComVar()
                =0    succeed  precess 
                =1    fail precess 
*****************************************************************/
INT8U SecurityCK(void)
{
	INT8U secType;
	secType = comm_data.Info.B08[0]&0x07; //Ȩ�޼��//
	/*
	if(secType ==(W_FCT>>8))
	{
		if(ADJA_KEY)	// 0 �̽� 1 δ�̽�
		{
			return (mmover);
		}
	}
    */
	return (mmok);
}

//-------------------------------------------------------------------------------//
//  Function:      INT8U IEC_Cmd_Password_Deal(INT8U* sptr,INT8U len) 
//  Description:   iec ͨѶ����ָ������
//  Parameters:    
//  Returns:        ��                          
//  Others:         
//-------------------------------------------------------------------------------//
INT8U IEC_Cmd_Password_Deal(INT8U* sptr)
{
  INT8U tmp_8u_01[4];
  INT8U tmp_8u_02[8];

    if((gs_uart_iec_app_var[g_ch_comm].iec_status & (COMM_REQUIST_OK_IEC+COMM_INFO_OK_IEC)) != 0x03)   return(FALSE);

     mem_read(&tmp_8u_01[0], ADR_METER_PARAM1_PW0, 4, MEM_E2P1);
     Lib_BCD_AscA(&tmp_8u_02[0], &tmp_8u_01[0], 4);
	 

    if(Lib_Cmp_TwoArry((sptr+5), &tmp_8u_02[0], 8) == 0x00)  
    {
         gs_uart_iec_app_var[g_ch_comm].iec_status |= COMM_MIMA_OK_IEC;  // ������������ɹ���ʶ //
         Get_ACK_Answer(sptr);
         gs_uart_iec_app_var[g_ch_comm].len = 1;
         return TRUE;
    }
    else
    {
        if(Lib_Cmp_TwoArry((sptr+5), &Super_mima_iec[0], 8) == 0x00) 
        {
            gs_uart_iec_app_var[g_ch_comm].iec_status |= COMM_MIMA_OK_IEC;  // ������������ɹ���ʶ //
            Get_ACK_Answer(sptr);
            gs_uart_iec_app_var[g_ch_comm].len = 1;
            return TRUE;
        }
    }

    return FALSE;
}


//-------------------------------------------------------------------------------//
//  Function:      INT8U IEC_Cmd_Read_Deal(INT8U* sptr,INT8U len)
//  Description:   iec ͨѶ��ָ������
//  Parameters:    
//  Returns:        ��                          
//  Others:         
//-------------------------------------------------------------------------------//
INT8U IEC_Cmd_Read_Deal(INT8U* sptr)
{
 INT8U  mem_type;
 INT8U  data_buff[70];
 INT8U  *ptr_adr;
 INT16U ctmp1;
	union  Union_DWordDef tmp_32u;
ST_U32_U08  long_tmp;

  ST_U16_U08	 LPRecStart,LPRecEnd;
  if((gs_uart_iec_app_var[g_ch_comm].iec_status &(COMM_REQUIST_OK_IEC+COMM_INFO_OK_IEC+COMM_MIMA_OK_IEC)) != 0x07)   return(FALSE);	
    //get comm DI1 DI0
    Lib_Asc_BCDA(&comm_data.di1_di0.B08[0], sptr+4,8);

    //get other comm fram data 	
    if(get_IEC_comm_var( comm_data.di1_di0.u32) == 0 )   return(FALSE);
    if( ( comm_data.Info.u16& EN_R) == 0 )  return(FALSE);
    //  ��ȡ���ݵĴ洢���� //
    mem_type = (comm_data.Info.B08[0]>>3)&0x07;   	
    //���������㲢���÷��ͳ���
    Lib_Set_String((sptr+2), '0', comm_data.len_asc);  

    ptr_adr = comm_data.addr;
//���ڱ����ID���� ��������ID 
	if((comm_data.di1_di0.u32>=0x06010001)&&(comm_data.di1_di0.u32<=0x060105A0))
	{
		ctmp1 = (INT16U)(comm_data.di1_di0.u32 - 0x06010001);
		if(ctmp1 < LPRunPa.Num[0])	// ��ȡID С�����Ѽ�¼��
		{
			comm_data.len = LPRec_Read_1(sptr+2, ctmp1);
			comm_data.len_asc = 2*comm_data.len;	
		}
		else
		{
//			comm_data.len = LPRec_Read_1(sptr+2, ctmp1);
//			comm_data.len_asc = 2*comm_data.len;	
//			Lib_Set_String((sptr+2), 'F', comm_data.len_asc); 
			comm_data.len_asc = 0;	
		}


		// �ɹ���������֡ //
		//api_deal_even_class_recode(ID_CLASS_I_COMM,START);
		gs_uart_iec_app_var[g_ch_comm].len= (comm_data.len_asc+5);
		*(sptr+0) = STX;
		*(sptr+1) = '(';
		CLRWDT(); *(sptr+2+comm_data.len_asc) = ')';
		*(sptr+gs_uart_iec_app_var[g_ch_comm].len-2) =ETX;
	CLRWDT(); 	*(sptr+gs_uart_iec_app_var[g_ch_comm].len-1) = Get_Bcc_Chk(sptr, 1, gs_uart_iec_app_var[g_ch_comm].len-2);

		return(TRUE); 
	}
	
	
	if((comm_data.di1_di0.u32>=0x060A0001)&&(comm_data.di1_di0.u32<=0x060A0120))//   //SXL 2019-01-6
  {
		LPRecStart.u16 =(INT16U)((comm_data.di1_di0.u32 - 0x060A0001)*BLOCK_MAX_LEN);
		LPRecEnd.u16 =LPRecStart.u16+BLOCK_MAX_LEN;
		
		if(LPReadPara.ReadLoraFlag == FALSE )
		{			
			LPReadPara.Original_FrameNum = LPRunPa.Num[0] ;
			LPReadPara.Original_Ptr = LPRunPa.Ptr[0] ;
		} 		
		
		comm_data.len_asc  = LPRec_Read_Block(sptr+2,LPRecStart.u16, LPRecEnd.u16);
	  	 
		
		if(LPReadPara.ReadLoraFlag == FALSE )	LPReadPara.ReadLoraFlag = TRUE; 
			
		gs_uart_iec_app_var[g_ch_comm].len= (comm_data.len_asc+5);
		CLRWDT(); 
		*(sptr+0) = STX;
		*(sptr+1) = '(';CLRWDT(); 
		*(sptr+2+comm_data.len_asc) = ')';
		CLRWDT(); *(sptr+gs_uart_iec_app_var[g_ch_comm].len-2) =ETX;
		*(sptr+gs_uart_iec_app_var[g_ch_comm].len-1) = Get_Bcc_Chk(sptr, 1, gs_uart_iec_app_var[g_ch_comm].len-2);
CLRWDT(); 
		return(TRUE); 
		
		}

    // ���ݶ�ȡ���ݵ�ID��Ŀ����֧���� //
    switch(comm_data.di1_di0.u32)
    {	
        case 0x02010000:    //��ѹ Դ����ΪHEX32��0.1V���٣���Ҫת��ΪBCD���ʽ,XXX.XV //
        case 0x02010100:    //��ѹ Դ����ΪHEX32��0.1V���٣���Ҫת��ΪBCD���ʽ,XXX.XV //
            Lib_long_bcd4(&long_tmp.B08[0],gs_measure_var_data.gs_really[0].dw_u_val.u32);
            Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[2], 2);
            Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len); 
            break;
        case 0x02020000:    //���� Դ����ΪHEX32��0.0001A���٣���Ҫת��ΪBCD���ʽ,XXX.XXXA //
        case 0x02020100:    //���� Դ����ΪHEX32��0.0001A���٣���Ҫת��ΪBCD���ʽ,XXX.XXXA //
            Lib_long_bcd4(&long_tmp.B08[0],(gs_measure_var_data.gs_really[0].dw_i_val.u32));
            Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[1], 3);
            Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len); 
            break;

        case 0x02030000:    //����Դ����ΪHEX32��0.0001KW���٣���Ҫת��ΪBCD���ʽ,XX.XXXXkW //
        case 0x02030100:    //����Դ����ΪHEX32��0.0001KW���٣���Ҫת��ΪBCD���ʽ,XX.XXXXkW //
            Lib_long_bcd4(&long_tmp.B08[0],(gs_measure_var_data.gs_really[0].dw_p_val.u32));
            Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[1], 3);
            Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len); 
            break;

        case 0x02060000:    //������������ΪHEX16��0.001����Ҫת��ΪBCD���ʽ0.001 //
        case 0x02060100:    //������������ΪHEX16��0.001����Ҫת��ΪBCD���ʽ0.001 //
            Lib_word_bcd2(&long_tmp.B08[0],(gs_measure_var_data.gs_really[0].dw_pf_val.u16));
            Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[0], 2);
            Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len); 
            break;

        case 0x02800002:    //����Ƶ������ΪHEX16��0.01Hz����Ҫת��ΪBCD���ʽxx.xx //
            Lib_word_bcd2(&long_tmp.B08[0],(gs_measure_var_data.gs_really[0].w_freq_val.u16));
            Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[0], 2);
            Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len); 
            break;

        case 0x02800003:  //ÿ�����й�ƽ������Դ����ΪHEX32��0.0001KW���٣���Ҫת��ΪBCD���ʽ,XX.XXXXkW //
            Lib_long_bcd4(&long_tmp.B08[0],(gs_md_var.min_var[0].val_min ));
            Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[1], 3);
            Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len); 
            break;

        case 0x02800006:    //����¶�����ΪHEX16��0.1��ʩ�ȣ�//
            //Lib_word_bcd2(&long_tmp.B08[0],(gs_measure_var_data.w_temp.u16));
            Lib_Copy_Str_TwoArry(&data_buff[0], &gs_measure_var_data.w_temp.B08[0], 2);
            Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len); 
            break;
            
        case 0x02800007:    //��ص�ѹ����ΪHEX16��0.1V����Ҫת��ΪBCD���ʽxx.xx V//
            Lib_word_bcd2(&long_tmp.B08[0],(gs_measure_var_data.w_bat_v.u16));
            Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[0], 2);
            Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len); 
            break;



        case 0x04000100://���ڼ�����(����0����������)YYMMDDWWhhmmss
            Lib_Copy_Str_TwoArry(&data_buff[0], ptr_adr, comm_data.len);
            data_buff[7] = data_buff[0];	//ww
            data_buff[0] = data_buff[1];	//YY
            data_buff[1] = data_buff[2];	//MM
            data_buff[2] = data_buff[3];	//DD
            data_buff[3] = data_buff[7];	//WW
            data_buff[4] = data_buff[4];	//hh
            data_buff[5] = data_buff[5];	//mm
            data_buff[6] = data_buff[6];	//ss
            Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len); 
            break;



        case 0x04000401://���ַ ��� NNNNNNNNNNNN
            mem_read(&data_buff[0], comm_data.addr,  comm_data.len,  mem_type );
            comm_data.len_asc = get_meter_id_asclen(&data_buff[0], 16);
            comm_data.len = comm_data.len_asc/2;
            Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len);

            break;

        case 0x04800001: //����汾�� ����ASC��
            Lib_Copy_Str_TwoArry(sptr+2, ptr_adr, comm_data.len);
            break;		
			
        default:
////////////////���������⴦��/////////////////////////////
            if(comm_data.di1_di0.B08[0]==0x00)
            {
                comm_data.len = LEN_EC_UNIT;   // �޸Ļ�ȡ����//
            }
///////////////////////////////////////////////////////////////////

            if((comm_data.Info.u16&CM_ALL) == CM_BILL)
            {
                mem_read(&data_buff[0],  api_get_bill_record_addr(comm_data.addr), comm_data.len,  mem_type );
            }
						else if((comm_data.Info.u16&CM_ALL) == CM_EBIL)//�¼���¼������
	  	      {
               mem_read(&data_buff[0], comm_data.addr,     (comm_data.len>>1),  mem_type );
               mem_read(&data_buff[6], comm_data.addr+60,  (comm_data.len>>1),  mem_type );
	          }
            else 
            {
                if(mem_type==MEM_RAM)
                {
                    Lib_Copy_Str_TwoArry(&data_buff[0], ptr_adr, comm_data.len);
                }
                else
                {
                    mem_read(&data_buff[0], comm_data.addr,  comm_data.len,  mem_type );
                }
            }

////////////////���������⴦��/////////////////////////////
            if(comm_data.di1_di0.B08[0]==0x00)
            {
                Lib_Copy_Str_TwoArry(&data_buff[10], &data_buff[0], LEN_EC_UNIT);
                api_get_energy_LCD(&data_buff[10], gs_dis_param.ec_form, &data_buff[0]) ;   
            }
///////////////////////////////////////////////////////////////////

////////////////����������⴦��/////////////////////////////
            if(comm_data.di1_di0.B08[0]==0x01)
            {  
                Lib_Copy_Str_TwoArry(&long_tmp.B08[0], &data_buff[0], 4);
                Lib_long_bcd4(&data_buff[0],long_tmp.u32);
            }
///////////////////////////////////////////////////////////////////            
            if(comm_data.len_asc == 5)
            {
                *(sptr+2) = Lib_BtoA(data_buff[0]&0x0f);
                Lib_BCD_AscA(sptr+3, &data_buff[1], 2);   
            }
            else
            {
                Lib_BCD_AscA(sptr+2, &data_buff[0], comm_data.len); 
            }
            break;	
    }

    // �ɹ���������֡ //
    gs_uart_iec_app_var[g_ch_comm].len= (comm_data.len_asc+5);
    *(sptr+0) = STX;
    *(sptr+1) = '(';
    *(sptr+2+comm_data.len_asc) = ')';
    *(sptr+gs_uart_iec_app_var[g_ch_comm].len-2) =ETX;
    *(sptr+gs_uart_iec_app_var[g_ch_comm].len-1) = Get_Bcc_Chk(sptr, 1, gs_uart_iec_app_var[g_ch_comm].len-2);
	
    return(TRUE); 
}


//-------------------------------------------------------------------------------//
//  Function:      INT8U IEC_Cmd_Write_Deal(INT8U* sptr,INT8U len)
//  Description:   iec ͨѶдָ������
//  Parameters:   lenΪ�������ݵ�ʵ�ʳ���
//  Returns:        ��                          
//  Others:         
//-------------------------------------------------------------------------------//
INT8U IEC_Cmd_Write_Deal(INT8U* sptr,INT8U len)
{
// INT8U tmp_8u_01[16];
 INT8U  mem_type;
 INT8U  data_buff[70];
 INT8U	sectemp;
 INT8U i,MeterID_LenTmp; //���  ��Ч���� asc
 INT8U  *ptr_adr;
 
    if((gs_uart_iec_app_var[g_ch_comm].iec_status &(COMM_REQUIST_OK_IEC+COMM_INFO_OK_IEC+COMM_MIMA_OK_IEC)) != 0x07)   return(FALSE);
    //get comm DI1 DI0
    Lib_Asc_BCDA(&comm_data.di1_di0.B08[0], sptr+4,8);
    //get other comm fram data 
    if(get_IEC_comm_var( comm_data.di1_di0.u32) == 0 )   return(FALSE);

    if( ( comm_data.Info.u16& EN_W) == 0 )  return(FALSE);
    //  ��ȡ���ݵĴ洢���� //
    mem_type = (comm_data.Info.B08[0]>>3)&0x07;   	
    sectemp = SecurityCK();					//Ȩ���ж�
    if(sectemp == mmover)   return(FALSE);

    //���������㲢�����յ����ݳ��ȺϷ��� //
    Lib_Set_String(&data_buff[0], 0x00, comm_data.len); 
    if(comm_data.di1_di0.u32== 0x04000401) //�����ñ����.����Ҫ�Ա����ݳ���
    {
        if((len > comm_data.len_asc+16)||(len < 16))
        return(FALSE);
    }
    else
    {
        if(len != (comm_data.len_asc+16))	   
        return(FALSE);
    }

    ptr_adr = comm_data.addr;

    // �����������ݵ�ID��Ŀ����֧���� //
    switch(comm_data.di1_di0.u32)
    {

        case 0x04000100://���ڼ�����(����0����������)YYMMDDWWhhmmss  
            Lib_Asc_BCDA(&data_buff[0], (sptr+13), comm_data.len_asc);   //AtoB(INT8U Asc)
            gs_CurDateTime.Year= data_buff[0];
            gs_CurDateTime.Month= data_buff[1];
            gs_CurDateTime.Day= data_buff[2];
            gs_CurDateTime.Week= data_buff[3];
            gs_CurDateTime.Hour= data_buff[4];
            gs_CurDateTime.Minute= data_buff[5];
            gs_CurDateTime.Second= data_buff[6];
            EA=0;
            Set_RTCTime(&gs_CurDateTime);
            EA=1;
            mem_db_write(ADR_METER_VAR_RTC, &gs_CurDateTime.Week, 7, MEM_E2P1);
            //api_handl_settle_month();
            api_deal_even_class_recode(ID_CLASS_I_setRtc,START);
            api_update_triffNo_pre_minute();
            break;
			

            //������⴦��
            case 0x04000401://���ַ ��� 16���ֽ� ����Ӧ,������������ǰ��0
                MeterID_LenTmp = (len-16);	//��Ч���  ����
                if(((len-16)%2)!=0)	//������ǰ�油һ��0
                {
                for(i=(len-16);i>0;i--)
                {
                *(sptr+13+i) = *(sptr+13+i-1) ;	//���Ų1λ
                }
                *(sptr+13)= '0';					//��λ��0
                MeterID_LenTmp = (len-16) +1;
                }
                comm_data.len_asc = MeterID_LenTmp;
                 Lib_Set_String(&data_buff[0], 0xFF, 16);
                 Lib_Asc_BCDA(&data_buff[0], (sptr+13), comm_data.len_asc);   //AtoB(INT8U Asc)			
                mem_db_write(comm_data.addr, &data_buff[0], comm_data.len, mem_type);		//д��Ӧ����16�ֽڣ����������õĳ���
                break;

			
		case 0x04000B01://������DDHH 4
                Lib_Asc_BCDA(&data_buff[0], (sptr+13), comm_data.len_asc);   //AtoB(INT8U Asc)
                if((data_buff[0]<0x01)||(data_buff[0]>0x28)||(data_buff[1]>0x23))		//�����ж�
                {
                    return(FALSE);
                }
                mem_db_write(comm_data.addr, &data_buff[0], comm_data.len, mem_type);
                break;

		case 0x04000103://�������� PERIOD : SLID   4  //�޸ĺ��������¼��� //
                Lib_Asc_BCDA(&data_buff[0], (sptr+13), comm_data.len_asc);   //AtoB(INT8U Asc)
                if(((data_buff[0]%data_buff[1]) !=0)||(data_buff[0]>30)||(data_buff[0]==0)||(data_buff[1]==0))		//�����ж�//
                {
                    return(FALSE);
                }
                mem_db_write(comm_data.addr, &data_buff[0], comm_data.len, mem_type);
                api_init_md_data_ram();
                break;

/*
///////////���У��//////////////////
		case 0x0000FEB0: 
		case 0x0000FEB1:
		case 0x0000FEB2:
		case 0x0000FEB3:
		case 0x0000FEB4:
		case 0x0000FEB5:
			Measure_Electric_Err_Gain(sptr, comm_data.di1_di0.u32);	  	//������У׼����ʱ1������У׼�������׼//	
			break;

		//---- ����У��//
		case 0x80800101:
		case 0x80800102:
		case 0x80800103:
		case 0x80800104:
		case 0x80800105:
		case 0x80800106:
		case 0x80800107:
		case 0x80800108:		
		case 0x80800109:
		case 0x8080010A:
		case 0x8080010B:
			Lib_Asc_BCDA(&data_buff[0], (sptr+13), comm_data.len_asc);
			Lib_Copy_Str_TwoArry(&data_buff[0], ptr_adr,4);   //���ݸ��� //
                    CLRWDT();
                    Save_EMU_AdjParam();
			break;
*/
			
		//У���ʼ��(��������)   //
		case 0x80800803:		
                if((*(sptr+13)=='3')&&(*(sptr+14)=='3')&&(*(sptr+15)=='3'))  
                {
                    if((*(sptr+16)=='3'))					// clear all
                    {
                        //У���������//
                        gs_adj_emu_param.w1gain =0;
                        gs_adj_emu_param.w2gain =0;
                        CLRWDT();
                        Save_EMU_AdjParam();
                    }
                }
                else
                {
                    return FALSE;
                }
                break;

		case 0x08020100://ֻ�嵱ǰ��������//
                    Lib_Asc_BCDA(&data_buff[0], (sptr+13), comm_data.len_asc);   //AtoB(INT8U Asc)
                    if((data_buff[0]!=0))  return(FALSE);
                    api_clr_current_MD_data();
                    CLRWDT();
                    api_deal_even_class_recode(ID_CLASS_I_resetMD,START);
			break;

		case 0x08020200://NN=FF���������ͨ����//
			if((*(sptr+13)=='F')&&(*(sptr+14)=='F'))	//YYY
			{
				api_clr_even_by_comm();	
				CLRWDT();
			}
			else
			{
				return(FALSE);
			}
			break;
		case 0x08020300:
			// Asc_BCDA( &data_buff[0],(sptr+13), 1*2);
            // һ��ͨ�����ɼ�¼ָ�롢��¼���� 
            if((*(sptr+13)=='0')&&(*(sptr+14)=='0'))	//YYY
			{
				LoadProRst();
				CLRWDT();
			}
			else
			{
				return(FALSE);
			}
			break;
            
		case 0x08020400://��������(�������(����+����)) //
                    Lib_Asc_BCDA(&data_buff[0], (sptr+13), comm_data.len_asc);   //AtoB(INT8U Asc)
                    if((data_buff[0]!=0)||(data_buff[1]!=0)||(data_buff[2]!=0)||(data_buff[3]!=0))  return(FALSE);
                    Proc_clr_meter();
			break;

		case 0x08020600://����ڿ������� =0X5A �޸�Ϊ�����壬����ֵΪ��������//
                    Lib_Asc_BCDA(&data_buff[0], (sptr+13), comm_data.len_asc);   //AtoB(INT8U Asc)
                    if(data_buff[0]==METER_FACTORY_MARK)      //  =0X5A �޸�Ϊ������ //
                    {
                        Open_SecOut();   
                    }
                    else
                    {
                       Close_SecOut();
                       CFLED_INITLIZE();    
                    }
			break;
            
		case 0x0000FEFF:
			 if((*(sptr+13)=='5')&&(*(sptr+14)=='5')&&(*(sptr+15)=='5')&&(*(sptr+16)=='5'))    //��У������⣬����������ʼ��ΪĬ�ϲ���  //
			{
				mem_db_clr(0);   //������У���ȫ������ //
                           while(1)
                           {
                                NOP();          // ��λ���ȴ����ݼ��ظ����ݣ�10������ //
                           }	
				CLRWDT();
			}
			 if((*(sptr+13)=='3')&&(*(sptr+14)=='3')&&(*(sptr+15)=='3')&&(*(sptr+16)=='3'))   //����У����������в�����ʼ��ΪĬ�ϲ���  //
			{
				mem_db_clr(0XA5);   //������У���ȫ������ //
                           while(1)
                           {
                                NOP();          // ��λ���ȴ����ݼ��ظ����ݣ�10������ //
                           }	
				CLRWDT();
			}
			 
			else
			{
				return(FALSE);
			}
			break;

          default:
                 Lib_Asc_BCDA(&data_buff[0], (sptr+13), comm_data.len_asc);   //AtoB(INT8U Asc)
		    
                 if(mem_type == MEM_RAM)
                 {
                       mem_write(comm_data.addr,&data_buff[0], comm_data.len, mem_type);
                 }
                 else
                 {
                       mem_db_write(comm_data.addr, &data_buff[0], comm_data.len, mem_type);
                 }
				 
	          	break;	
		   
     	}
	 	
// ͨѶ���� ϵͳ����
	if(((comm_data.di1_di0.u32 >= 0x04000801)&&(comm_data.di1_di0.u32 <= 0x04000807))
		||((comm_data.di1_di0.u32 >= 0x04010000)&&(comm_data.di1_di0.u32 <= 0x04010008)))
	{
	
		api_update_triffNo_pre_minute();
	}

/////////////////������ʾ��������Ҫ����///////
	if((comm_data.di1_di0.u32 == 0x04000302)||(comm_data.di1_di0.u32 == 0x04000303)||(comm_data.di1_di0.u32 == 0x04000310)||(comm_data.di1_di0.u32 == 0x040003A0)||(comm_data.di1_di0.u32 == 0x04040100))
	{
		mem_read(&gs_dis_param.auto_sec, ADR_BLOCK21_DIS_PARAM_E2P, LEN_BLOCK21_DIS_PARAM_E2P, MEM_E2P1);
		if((gs_dis_param.auto_sec<3)||(gs_dis_param.auto_sec>60))    gs_dis_param.auto_sec = 5;
    		if((gs_dis_param.key_sec<5)||(gs_dis_param.key_sec>60))    gs_dis_param.key_sec = 30;
	}	
	
	if((comm_data.di1_di0.u32 == 0x04040200)||(comm_data.di1_di0.u32 == 0x04040300))
	{
		mem_read(&gs_dis_param.auto_sec, ADR_BLOCK21_DIS_PARAM_E2P, LEN_BLOCK21_DIS_PARAM_E2P, MEM_E2P1);
		if((gs_dis_param.auto_sec<3)||(gs_dis_param.auto_sec>60))   gs_dis_param.auto_sec = 5;
    		if((gs_dis_param.key_sec<5)||(gs_dis_param.key_sec>60))   gs_dis_param.key_sec = 30;
	}
	
    // �������óɹ������֡���� //
    api_deal_even_class_recode(ID_CLASS_I_PROG,START);   //���ɱ���¼���¼ //
    gs_uart_iec_app_var[g_ch_comm].len= 1;
    Get_ACK_Answer(sptr);	 
    return(TRUE); 
}


//-------------------------------------------------------------------------------//
//  Function:     INT8U IEC_Cmd_Break_Deal(INT8U* sptr,INT8U len)
//  Description:   iec ͨѶ��ָֹ������
//  Parameters:   
//  Returns:        ��                          
//  Others:         
//-------------------------------------------------------------------------------//
INT8U IEC_Cmd_Break_Deal(INT8U* sptr)
{

       gs_uart_iec_app_var[g_ch_comm].iec_status |= COMM_BREAK_OK_IEC;
	 gs_uart_iec_app_var[g_ch_comm].len= 1;
       Get_ACK_Answer(sptr);	 
       return(TRUE);  
}

/*****************************************************************************
** Function name    :api_init_md_data_ram
**
** Description         :��ʼ����ǰ��������RAM�����ݣ�����λ��ʼ������        
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void lnk_tx_comm_ready( uint8 ch,uint8 start_index)
{
    uint16 u16_badu;
    //comm_IEC_Tx_Ready();   
    switch(gs_uart_iec_app_var[ch].baud_rate)
    {
        case CBaud_3:
            u16_badu =300;
        break;
        case CBaud_6:
            u16_badu =600;
        break;
        case CBaud_12:
            u16_badu =1200;
        break;
        case CBaud_24:
            u16_badu =2400;
        break;
        case CBaud_48:
            u16_badu =4800;
        break;
        case CBaud_96:
            u16_badu =9600;
        break;

        default:
            u16_badu =300;
        break;
    }

    P_IEC_BUFF = &gs_uart_drv_var[ch].buff[0] ;
	
    Tx_UART_frist(&P_IEC_BUFF[start_index], gs_uart_iec_app_var[ch].len,u16_badu,ch);        // ���ݷ��� //     
}


/*****************************************************************************
** Function name    :api_init_md_data_ram
**
** Description         :��ʼ����ǰ��������RAM�����ݣ�����λ��ʼ������        
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_handl_COMM_FRAME_ERROR( uint8 ch)
{
    if(ch==UART_CH0_IR)           
    {
        Lib_Clr_String(&gs_uart_iec_app_var[ch].len, sizeof(UART_COMM_APP_VAR));   
        Init_UART2_hard(300);  //reset_uart(UART_RESET_ALL); 
        Init_UART_soft(ch); 
    }
    
    if(ch==UART_CH1_RS)
    {
        Lib_Clr_String(&gs_uart_iec_app_var[ch].len, sizeof(UART_COMM_APP_VAR));   
        Init_UART4_hard(300);  //reset_uart(UART_RESET_ALL);  
        Init_UART_soft(ch); 
    }
    
    return;
}

//-------------------------------------------------------------------------------//
//  Function:      void init_comm_link(INT8U mode)         
//  Description:   ��ʼ��������·���������
//  Parameters:   mode: ͨѶͨ�����  
//  Returns:        ��                          
//  Others:         
//-------------------------------------------------------------------------------//
void process_iec62056_21 (INT8U ch)
{
 INT8U buff_size;
 INT8U start_index;
 INT8U meterID_len;

 INT8U tmp_8u_01[16];
 INT8U tmp_8u_02[32];

 INT16U  u16_badu;

    
    if(ch > UART_CH_INDEX_MAX )  return ;
    
    if(gs_uart_iec_app_var[ch].tx_delay_flg ==TRUE ) 
    {
        return ;    //���͵ȴ�״̬ʱ�˳� //
    }

    buff_size = Get_UART_rx_buff(&P_IEC_BUFF,ch);
    if(buff_size==0)   return;    // ÿ��ѭ����ȡһ�ν������ݳ��ȣ�=0���˳� //

/////////////////////////////////////////////////////////////////////////
    if((gs_uart_iec_app_var[ch].iec_status & (COMM_INFO_OK_IEC)) !=0)
    {
        CLRWDT();
        CLRWDT();
    }

    if((gs_uart_iec_app_var[ch].iec_status & (COMM_REQUIST_OK_IEC)) !=0)
    {
        CLRWDT();
        CLRWDT();
    }

    if((gs_uart_iec_app_var[ch].iec_status & (COMM_MIMA_OK_IEC)) !=0)
    {
        CLRWDT();
        CLRWDT();
    }

////////////////////////////////////////////////////////////////////////

    // ǰ���ֽڴ��� //
    for(start_index=0;start_index<10;start_index++)
    {
        if((P_IEC_BUFF[start_index]=='/')||(P_IEC_BUFF[start_index]==ACKCOM)||(P_IEC_BUFF[start_index]==SOH))  break;
    }

    if(start_index>5)
    {
        //���յ�����֡���󣬲��䴮�ڸ�λ����      //
        api_handl_COMM_FRAME_ERROR(ch);
        return;
    }

    gs_uart_iec_app_var[ch].tx_delay_flg =FALSE;   // �����ݽ���ʱ���������ʱ��ʶ //
    gs_uart_iec_app_var[ch].delay_10ms = 0;   // �����ݴ���ʱ�����ʱ������ //
    gs_uart_iec_app_var[ch].err_flg = 0;
    g_ch_comm = ch;
    
    if(((buff_size >2) &&((P_IEC_BUFF[buff_size-2]) == CR ||(P_IEC_BUFF[buff_size-2]) == ETX )) )
    {
        buff_size =buff_size-start_index;
        // ����֡���� //
        switch(P_IEC_BUFF[start_index])
        {
            case IEC_COMM_REQUEST:	
                if((gs_uart_iec_app_var[ch].iec_status & COMM_INFO_OK_IEC) !=0)
                {
                    api_handl_COMM_FRAME_ERROR(ch);
                    return;
                }

//                if((buff_size==IEC_START_LENTH05) &&(ch==UART_CH0_IR))
//                {
//                    api_handl_COMM_FRAME_ERROR(ch);
//                    return;
//                }
                mem_read (&tmp_8u_01[0],ADR_METER_PARAM1_METER_ID, 16,MEM_E2P1);
                meterID_len = get_meter_id_asclen(&tmp_8u_01[0], 16);	//��ȡ�����Чasc����
                Lib_BCD_AscA(&tmp_8u_02[0], &tmp_8u_01[0], 16);
                    
                if(IEC_Comm_Request_Cmd_Judge(&P_IEC_BUFF[start_index], buff_size, &tmp_8u_02[0],meterID_len)==TRUE)
                {
                    if(ch==UART_CH0_IR)   // ����1200BPS//
                   {
                         Get_IEC_Comm_Request_Cmd_Answer(&P_IEC_BUFF[start_index], Meter_INFO_LENTH,(uint8*)&meter_info_IR[0]);
                    }
                     if(ch==UART_CH1_RS)  // RS485 2400BPS//
                   {
                         Get_IEC_Comm_Request_Cmd_Answer(&P_IEC_BUFF[start_index], Meter_INFO_LENTH,(uint8*)&meter_info[0]);
                    }           
                    gs_uart_iec_app_var[ch].len = Meter_INFO_LENTH+3;
                    gs_uart_iec_app_var[ch].iec_status |= COMM_INFO_OK_IEC;    // ��������ɹ���ʶ //
                }
                else
                {
                    //���ǵ�����ʽͨѶ��ʧ��ʱ���������� //
                    api_handl_COMM_FRAME_ERROR(ch);
                    return;
                }
            break;

            case IEC_COMM_ACKNOWLEDGEMENT:
                if((gs_uart_iec_app_var[ch].iec_status & COMM_INFO_OK_IEC) ==0)
                {
                    api_handl_COMM_FRAME_ERROR(ch);
                    return;
                }
                if(IEC_Comm_Acknowledgement_Cmd_Judge(&P_IEC_BUFF[start_index],buff_size)==TRUE)
                {
                    gs_uart_iec_app_var[ch].baud_rate = P_IEC_BUFF[start_index+2];                                           //�����ʸ�ֵ  //
                    Get_IEC_Comm_Operand_Answer(&P_IEC_BUFF[start_index], MIMA_INFO_LENTH,(uint8*)&mima_info[0]);    // ��ȡ������֡ //
                    gs_uart_iec_app_var[ch].len = (MIMA_INFO_LENTH+6);
                    gs_uart_iec_app_var[ch].iec_status |= COMM_REQUIST_OK_IEC;  // ������������ɹ���ʶ //
                }
                else
                {
                    gs_uart_iec_app_var[ch].iec_status &= ~COMM_REQUIST_OK_IEC;  // clr ��������ɹ���ʶ //
                    Get_Error_Answer(&P_IEC_BUFF[start_index]);
                    gs_uart_iec_app_var[ch].len = 1;
                }

            break;

            case IEC_COMM_COMMAND:
                if((gs_uart_iec_app_var[ch].iec_status & COMM_REQUIST_OK_IEC) ==0)
                {
                    api_handl_COMM_FRAME_ERROR(ch);
                    return;
                }              
                if(IEC_Comm_Command_Cmd_Judge(&P_IEC_BUFF[start_index],buff_size) !=TRUE)
                {
                    // ���ݽ���ʧ�� //
                    Get_Error_Answer(&P_IEC_BUFF[start_index]);
                    gs_uart_iec_app_var[ch].len = 1;   		           
                }
            break;

            default:
                gs_uart_iec_app_var[ch].err_flg |= FRAME_ERROR;   //֡������Ҫ��λ  //	
            break;
        }

    }
    else
    {
        gs_uart_iec_app_var[ch].err_flg |= FRAME_ERROR;   //֡������Ҫ��λ  //	
    }

    if((gs_uart_iec_app_var[ch].err_flg & FRAME_ERROR) )
    {
        //���յ�����֡���󣬲��䴮�ڸ�λ����      //
        api_handl_COMM_FRAME_ERROR(ch);
        return;
    }
    else
    {
        
        gs_uart_iec_app_var[ch].tx_delay_flg =TRUE;
        gs_uart_iec_app_var[ch].tx_ready_10ms = COMM_DELAY_100MS;   // �����ݴ���ʱ�����ʱ������ //
        gs_uart_iec_app_var[ch].delay_10ms = 0;   
        if(gs_uart_iec_app_var[ch].iec_status ==(COMM_INFO_OK_IEC+COMM_REQUIST_OK_IEC))
        {
            gs_uart_iec_app_var[ch].tx_ready_10ms  += 30;   // �л�������ʱ��ʱ����300ms //
        }
        gs_uart_iec_app_var[ch].start_index = start_index;

    }
}


/*****************************************************************************
** Function name    :api_init_md_data_ram
**
** Description         :��ʼ����ǰ��������RAM�����ݣ�����λ��ʼ������        
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_handl_COMM_pre_10ms(uint8 ch)
{

    process_iec62056_21(ch);    
    
    if(gs_uart_iec_app_var[ch].delay_10ms >COMM_DELAY_3500MS)
    {   
        //��ʱ�˳����֣����½�����еȴ�״̬ //
        api_handl_COMM_FRAME_ERROR(ch);    
    }

    if((gs_uart_iec_app_var[ch].tx_ready_10ms ==0)&&(gs_uart_iec_app_var[ch].tx_delay_flg ==TRUE))
    {   
        //����׼������   //
        gs_uart_iec_app_var[ch].tx_delay_flg =FALSE;
        lnk_tx_comm_ready(ch,gs_uart_iec_app_var[ch].start_index);     
    }



}


/***************************************************************
*    END
****************************************************************/

