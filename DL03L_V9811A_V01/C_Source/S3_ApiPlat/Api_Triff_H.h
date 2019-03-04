/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Triff_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: ���ʴ���Ӧ�ò���غ������������ļ�
**note			: MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-20   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#ifndef _Api_Triff_H
#define _Api_Triff_H


#if (TARIFF_MAX_NUM>1)
/***************************************************************
*    1     ������Ԥ����   
****************************************************************/
//Fee
#define MAX_DAY_TRIFF_CHG   8              //��ʱ�α�ÿ������л���  //
#define MAX_INDEX_DAY_TAB     4             //��ʱ�α����������  //
#define MAX_INDEX_WEEKDAY_TAB     4     //�ܱ����������  //
#define MAX_YEAR_TAB_CHG   8               //���ڱ������л���  //
#define MAX_NUM_HOLIDAY_TAB     0      //�ڼ���������  //

// Ĭ�Ϸ��ʺ� //
#define DEF_TRIFF_no   1        // Ĭ�Ϸ���Ϊ1 //
/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
typedef struct
{
    uint8 hour_BCD8;        //��ʼ��-Сʱ  //
    uint8 minute_BCD8;     //��ʼ��-����  //
    uint8 triff_No;       //�������1~4�������1�~4 //
}DAY_TABLE_UNIT;

typedef struct
{
    uint8 month_BCD8;        //��ʼ��-��  //
    uint8 day_BCD8;     //��ʼ��-��  //
    uint8 weekTable_No;       //��ʱ�α�ţ�1��ʼ //
}SEASON_TABLE_UNIT;

typedef struct
{
    uint8 Sun_Tab;     //����ʱ�α��  //
    uint8 Mon_Tab;     //��1ʱ�α��  //
    uint8 Tues_Tab;     //��2ʱ�α��  //
    uint8 Wed_Tab;     //��3ʱ�α��  //
    uint8 Thurs_Tab;     //��4ʱ�α��  //
    uint8 Fri_Tab;     //��5ʱ�α��  //
    uint8 Sat_Tab;     //��6ʱ�α��  //
}WEEK_TABLE_UNIT;


typedef struct
{
    uint8 month_BCD8;        //��ʼ��-��  //
    uint8 day_BCD8;     //��ʼ��-��  //
    uint8 dayTable_No;       //��ʱ�α�ţ�1��ʼ //
}HOLIDAY_TABLE_UNIT;


typedef struct
{
    DAY_TABLE_UNIT  tab[MAX_DAY_TRIFF_CHG];
}DAY_TABLE;

typedef struct
{
    WEEK_TABLE_UNIT  tab[MAX_INDEX_WEEKDAY_TAB];
}WEEK_TABLE;

typedef struct
{
    SEASON_TABLE_UNIT  tab[MAX_YEAR_TAB_CHG];
}SEASON_TABLE;

#if (MAX_NUM_HOLIDAY_TAB >0)
typedef struct
{
    HOLIDAY_TABLE_UNIT tab[MAX_NUM_HOLIDAY_TAB];
}HOLIDAY_TABLE;
#endif     // #if (MAX_NUM_HOLIDAY_TAB >0)  //

typedef struct
{
    uint8 triff_No;             //��ǰ���ʺ�1~4�������1�~4  //
    uint8 dayTab_No;        //��ǰ��ʱ�α��1~MAX_INDEX_DAY_TAB  //
    uint8 weekTab_No;     //��ǰ�ܱ��1~MAX_INDEX_WEEKDAY_TAB //
    uint8 seasonTab_No;     //��ǰ���ڱ��MAX_YEAR_TAB_CHG //
}CURRENT_TRIFF_VAR;


//���з����������E2P�洢���ݽṹ  //
#if (MAX_NUM_HOLIDAY_TAB >0)
typedef struct 
{
    HOLIDAY_TABLE   holiday_tab;
    INT16U  holiday_tab_csck;    //16λ�ۼӺ�У��ֵ//
} E2P_TRIFF_HOLIDAY_TABLE_MAP;
#endif     // #if (MAX_NUM_HOLIDAY_TAB >0)  //

typedef struct 
{
    SEASON_TABLE  season_tab;
    INT16U  season_tab_csck;    //16λ�ۼӺ�У��ֵ//
} E2P_TRIFF_SEASON_TABLE_MAP;

typedef struct 
{
    WEEK_TABLE  week_tab;
    INT16U  week_tab_csck;    //16λ�ۼӺ�У��ֵ//
} E2P_TRIFF_WEEK_TABLE_MAP;

typedef struct 
{
    DAY_TABLE day_tab[MAX_INDEX_DAY_TAB];
    INT16U  day_tab_csck;    //16λ�ۼӺ�У��ֵ//
} E2P_TRIFF_DAY_TABLE_MAP;

typedef struct 
{
#if (MAX_NUM_HOLIDAY_TAB >0)
    E2P_TRIFF_HOLIDAY_TABLE_MAP   holiday_tab;
#endif     // #if (MAX_NUM_HOLIDAY_TAB >0)  //
    E2P_TRIFF_SEASON_TABLE_MAP  season_tab;
    E2P_TRIFF_WEEK_TABLE_MAP  week_tab;
    E2P_TRIFF_DAY_TABLE_MAP day_tab;
} E2P_TRIFF_PARAM_MAP;



/***************************************************************
*    3    ��������       
****************************************************************/
extern CURRENT_TRIFF_VAR gs_current_triff_var;

#if (MAX_NUM_HOLIDAY_TAB >0)
extern const  E2P_TRIFF_HOLIDAY_TABLE_MAP  code   default_triff_holiday_tab;
#endif     // #if (MAX_NUM_HOLIDAY_TAB >0)  //
extern const  E2P_TRIFF_SEASON_TABLE_MAP  code   default_triff_season_tab;
extern const  E2P_TRIFF_WEEK_TABLE_MAP  code   default_triff_week_tab;
extern const  E2P_TRIFF_DAY_TABLE_MAP  code   default_triff_day_tab;
/***************************************************************
*    4     ��������        
****************************************************************/
extern void api_update_triffNo_pre_minute(void);
extern void api_init_triff_var_ram(void);

/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/
//��ǰ���ʺŶ��� //
#define EN_TRIFF_no     gs_current_triff_var.triff_No

//�������е����ݳ��ȶ���  //
#define LEN_HOLIDAY_TABLE	(sizeof(HOLIDAY_TABLE) )

#define LEN_SEASON_TABLE	(sizeof(SEASON_TABLE) )

#define LEN_WEEK_TABLE_ONE	(sizeof(WEEK_TABLE_UNIT) )
#define LEN_WEEK_TABLE          	(sizeof(WEEK_TABLE) ) 

#define LEN_DAY_TABLE_ONE		(sizeof(DAY_TABLE) )  
#define LEN_DAY_TABLE			(MAX_INDEX_DAY_TAB*LEN_DAY_TABLE_ONE) 

// �ⲿ�洢�洢����ƫ�����ͳ��ȶ��� //
#if (MAX_NUM_HOLIDAY_TAB >0)
#define OFFSET_HoliTab              ST_MB_OFFSET(E2P_TRIFF_PARAM_MAP,holiday_tab)
#define LEN_HoliTab	                (sizeof(E2P_TRIFF_HOLIDAY_TABLE_MAP))
#endif   //#if (MAX_NUM_HOLIDAY_TAB >0)     //

#define OFFSET_SeasonTab              ST_MB_OFFSET(E2P_TRIFF_PARAM_MAP,season_tab)
#define LEN_SeasonTab	                (sizeof(E2P_TRIFF_SEASON_TABLE_MAP))

#define OFFSET_WeekTab              ST_MB_OFFSET(E2P_TRIFF_PARAM_MAP,week_tab)
#define LEN_WeekTab	                (sizeof(E2P_TRIFF_WEEK_TABLE_MAP))

#define OFFSET_DayTab              ST_MB_OFFSET(E2P_TRIFF_PARAM_MAP,day_tab)
#define LEN_DayTab	                (sizeof(E2P_TRIFF_DAY_TABLE_MAP))


#endif  // #if (TARIFF_MAX_NUM>1) //

/***************************************************************
*    END
****************************************************************/

#endif
