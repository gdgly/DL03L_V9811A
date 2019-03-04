/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Event_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: �¼���¼����Ӧ�ò���غ��������ļ�
**note			: MCU- G80F92XD ��MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-20   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/



#ifndef _Api_Event_H
#define _Api_Event_H

/***************************************************************
*    1     ������Ԥ����   
****************************************************************/
#define MAX_CLASS_I_RECORD     10   // 2���¼�����¼���10��  //


//CLASS_I_TAB.id_even define 
#define ID_CLASS_I_PROG     0    //����¼� //
#define ID_CLASS_I_resetMD  1   //������λ�¼� //
#define ID_CLASS_I_setRtc  2   //ʱ���޸��¼� //

#define ID_CLASS_I_max 3
#define len_CLASSI_cnt  3   //1���¼�

//CLASS_2_TAB.id_even define 
#define	START	1
#define	DOING	0X55
#define END	0xFF

#define ID_CLASS_II_min  3  //����������ʼ //
#define ID_CLASS_II_PWN  4   //�����¼� //
#define ID_CLASS_II_lowbattery  5   //���ʧѹ�¼� //
#define ID_CLASS_II_COVER  6 
#define ID_CLASS_II_L1reverse  7  //L1�����¼� //


#define ID_CLASS_II_max  8  //������   //

#define len_CLASSII_cnt  4  //�����¼����� //

/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
typedef struct 
{
    ST_U16_U08  u16_num;    //�¼��ۼƷ�������  //
    uint8   dataTime[MAX_CLASS_I_RECORD][6];  //�¼���¼������ʱ�� //
    INT16U  u16_csck;    //16λ�ۼӺ�У��ֵ//
}CLASS_I_UNIT;

typedef struct 
{
	ST_U16_U08	u16_num;        //  �����¼������ܴ���//  2
	ST_U32_U08	accumTime;	// �����¼����ۻ�ʱ��(��λ:��)   4
	INT8U StartTm[MAX_CLASS_I_RECORD][6];	// �¼���ʼʱ��������ʱ���� 60 
  INT8U EndTm[MAX_CLASS_I_RECORD][6];		// �¼�����ʱ��  60 
  INT16U  u16_csck;    //16λ�ۼӺ�У��ֵ//    2
}CLASS_II_UNIT;

typedef struct 
{
    uint8     id_even;
    INT16U  addr_even;  
}CLASS_I_TAB;

typedef struct 
{
    CLASS_I_UNIT   prog;    // //
    CLASS_I_UNIT   resetMD;    // //
    CLASS_I_UNIT   setRtc;    // //
//    CLASS_I_UNIT   powerDown;    // //
} E2P_EVEN_I_DATA_MAP;

//�����¼���¼ 

typedef struct 
{
  CLASS_II_UNIT   PWN;    // //
	CLASS_II_UNIT   lowbattery;    // //
	CLASS_II_UNIT   Cover;    // //
  CLASS_II_UNIT   L1reverse; 
} E2P_EVEN_II_DATA_MAP;

typedef struct 
{
	INT8U   even_cnt[len_CLASSII_cnt];    // �����¼�������ʱʱ�� 6
	INT8U   doing_flg[len_CLASSII_cnt];    // �����¼�������ʶ 6
	ST_U32_U08  even_data[len_CLASSII_cnt]; // Ԥ������// 24
	INT16U  u16_csck;  
} EVEN_CLASSII_VAR;

typedef struct 
{
	INT8U   esc_cnt[len_CLASSII_cnt];    // �����¼������˳�ʱ����ʱ
	INT8U   into_cnt[len_CLASSII_cnt];    // �����¼���������ʱ����ʱ
	INT8U   even_fun_doingflg[len_CLASSII_cnt]; // �˷�����ʶ
} EVEN_FUN_VAR;

/***************************************************************
*    3    ��������       
****************************************************************/

extern   EVEN_FUN_VAR    gs_even_fun_var;
extern const  EVEN_CLASSII_VAR  code   gs_even_var ;

/***************************************************************
*    4     ��������        
****************************************************************/
extern void lnk_save_even_class1_recode(uint8 ID,uint16 adr,uint8 type);
extern void api_deal_even_class1_recode(uint8 even_id,uint8 type);
extern void api_clr_even_by_comm(void);

extern void GetTotalTime(INT8U *buftmp);
extern void api_pwl_cover_even_class_recode(uint8 even_id, uint8 type );
extern void api_even_Detect_sec(void);
extern INT8U api_even_Detect_lowbattery(void);

extern INT8U  api_even_Detect_L1reverse(void);
extern void api_deal_even_class_recode(uint8 even_id, uint8 type );
/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/

#define LEN_CLASS_I_UNIT   sizeof(CLASS_I_UNIT)
#define LEN_CLASS_II_UNIT   sizeof(CLASS_II_UNIT)  // �����¼�����//

#define LEN_CLASSII_VAR   sizeof(EVEN_CLASSII_VAR)  // �����¼���������//


#define CLASSII_cnt_start                 ST_MB_OFFSET(EVEN_CLASSII_VAR,even_cnt)
#define LEN_CLASSII_cnt	                 1

#define CLASSII_flg_start                 ST_MB_OFFSET(EVEN_CLASSII_VAR,doing_flg)
#define LEN_CLASSII_flg	                 1

#define CLASSII_data_start              ST_MB_OFFSET(EVEN_CLASSII_VAR,even_data)
#define LEN_CLASSII_data	          4

/***************************************************************
*    END
****************************************************************/

#endif