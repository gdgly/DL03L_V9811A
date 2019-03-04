/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Measure_H.H
**Author		: maji
**date			: 2016-04-21 
**description	: c code for �������������ļ�
**note			: MCU- G80F92XD ��MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-21   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#ifndef _Api_Measure_H
#define _Api_Measure_H


/***************************************************************
*    1     ������Ԥ����   
****************************************************************/



/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
typedef struct 
{
    ST_U32_U08 dw_u_val;			//��ѹ�Ĵ�����len=4  //
    ST_U32_U08 dw_i_val;			//�����Ĵ�����len=4  //
    ST_U32_U08 dw_p_val;			//�й����ʼĴ�����len=4  //
    ST_U16_U08 dw_pf_val;			//���������Ĵ�����len=2  //
    ST_U16_U08 w_freq_val;		//����Ƶ�ʣ�len=2  //
}ELECTRIC_VAR_UNIT;

typedef struct  
{
    ELECTRIC_VAR_UNIT  gs_really[PHASE_MAX_UNM];   
    ST_U32_U08 		 dw_i_n_val;	        //���ߵ�����len=4  //
    ST_U32_U08 		 dw_p_n_val;        //���߹��ʣ�len=4  //
    ST_U16_U08		 w_temp;             //����¶ȣ�len=2  //
    ST_U16_U08		 w_bat_v;            //��ص�ѹ��len=2 //
    ST_U16_U08		 w_status;            //ͳһ�Ĳ�����״̬�֣�len=2 //
}MEASURE_VAR_DATA;


typedef struct  
{
    uint8  cnt_sec[3];        //״̬�ж��������,0-���ʷ���1-��·2-dimmer //
    uint8  cnt_dimmer;       // DIMMER �жϼ����� //
    uint8  u8_status;        //�ж�״̬ //
    uint8  emu_ch;           //��ǰ����ͨ��  //
}MEASURE_STATU_JUDGE_VAR;

/***************************************************************
*    3    ��������       
****************************************************************/
extern MEASURE_VAR_DATA gs_measure_var_data;
extern MEASURE_STATU_JUDGE_VAR gs_measure_status_judge_var;



/***************************************************************
*    4     ��������        
****************************************************************/
extern void api_Measure_ram_INIT(void);
extern void api_measure_deal_pre_second(void);
extern void api_measure_VBAT_pre_min(void);
extern void api_measure_temperature_pre_min(void);


/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/
//gs_measure_status_judge_var.u8_status define
#define REV_ACPOWER_L      BIT0       //L ��·���ʷ��� //
#define REV_ACPOWER_N     BIT1       //N ��·���ʷ��� //
#define STATUS_DIMMER     BIT2       //DIMMER ����ģʽ //
#define BYPASS_L                BIT3       //L ��·�ӵ�ָʾ //
#define BYPASS_N                BIT4       //L ��·�ӵ�ָʾ //
#define VBAT_LOW               BIT5       //��ص�ѹ�ͱ�ʶ  //



/***************************************************************
*    END
****************************************************************/

#endif
