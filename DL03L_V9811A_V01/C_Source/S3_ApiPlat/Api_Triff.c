/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Triff.c
**Author		: maji
**date			: 2016-04-21 
**description	: ���ʴ���Ӧ�ò���غ�������C�ļ�
**note			: MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-21   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#include <MyIncludes_H.h>


#if (TARIFF_MAX_NUM>1)

CURRENT_TRIFF_VAR gs_current_triff_var;


/*************************************************************************
**  ���ʹ���- �ڼ��ճ�ʼ��Ĭ������
*************************************************************************/
#if (MAX_NUM_HOLIDAY_TAB >0)
const  E2P_TRIFF_HOLIDAY_TABLE_MAP  code   default_triff_holiday_tab = 
{
    0,      0,      0,   //  holiday1 data
#if (MAX_NUM_HOLIDAY_TAB>1)
    0,      0,      0,   //  holiday2 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>2)
    0,      0,      0,   //  holiday3 data ��
#endif  

#if (MAX_NUM_HOLIDAY_TAB>3)
    0,      0,      0,   //  holiday4 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>4)
    0,      0,      0,   //  holiday5 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>5)
   0,      0,      0,   //  holiday6 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>6)
   0,      0,      0,   //  holiday7 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>7)
   0,      0,      0,   //  holiday8 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>8)
   0,      0,      0,   //  holiday9 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>9)
   0,      0,      0,   //  holiday10 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>10)
    0,      0,      0,   //  holiday11 data ��
#endif
   
#if (MAX_NUM_HOLIDAY_TAB>11)
  0,      0,      0,   //  holiday12 data ��
#endif
   
#if (MAX_NUM_HOLIDAY_TAB>12)
   0,      0,      0,   //  holiday13 data ��
#endif
    
#if (MAX_NUM_HOLIDAY_TAB>13)
   0,      0,      0,   //  holiday14 data ��
#endif
	
#if (MAX_NUM_HOLIDAY_TAB>14)
   0,      0,      0,   //  holiday15 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>15)
   0,      0,      0,   //  holiday16 data ��
#endif
	 
#if (MAX_NUM_HOLIDAY_TAB>16)
   0,      0,      0,   //  holiday17 data ��
#endif
	 
#if (MAX_NUM_HOLIDAY_TAB>17)
    0,      0,      0,   //  holiday18 data ��
#endif
	  
#if (MAX_NUM_HOLIDAY_TAB>18)
    0,      0,      0,   //  holiday19 data ��
#endif
	 
#if (MAX_NUM_HOLIDAY_TAB>19)
    0,      0,      0,   //  holiday20 data ��
#endif
	 
#if (MAX_NUM_HOLIDAY_TAB>20)
    0,      0,      0,   //  holiday21 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>21)
    0,      0,      0,   //  holiday22 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>22)
    0,      0,      0,   //  holiday23 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>23)
    0,      0,      0,   //  holiday24 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>24)
    0,      0,      0,   //  holiday25 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>25)
    0,      0,      0,   //  holiday26 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>26)
    0,      0,      0,   //  holiday27 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>27)
    0,      0,      0,   //  holiday28 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>28)
    0,      0,      0,   //  holiday29 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>29)
    0,      0,      0,   //  holiday30 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>30)
    0,      0,      0,   //  holiday31 data ��
#endif

#if (MAX_NUM_HOLIDAY_TAB>31)
    0,      0,      0,   //  holiday32 data ��
#endif

    0x0000, // csck  //
};
#endif


/*************************************************************************
**  ���ʹ���- ���ڱ��ʼ��Ĭ������
*************************************************************************/
const  E2P_TRIFF_SEASON_TABLE_MAP  code   default_triff_season_tab = 
{
    1,      1,      1,   //  season-tab1 data   1��1���ܱ�1
#if (MAX_YEAR_TAB_CHG>1)
    0,      0,      0,   //  season-tab2 data   ��
#endif

#if (MAX_YEAR_TAB_CHG>2)
    0,      0,      0,   //  season-tab3 data   ��
#endif

#if (MAX_YEAR_TAB_CHG>3)
    0,      0,      0,   //  season-tab4 data   ��
#endif

#if (MAX_YEAR_TAB_CHG>4)
    0,      0,      0,   //  season-tab5 data   ��
#endif

#if (MAX_YEAR_TAB_CHG>5)
    0,      0,      0,   //  season-tab6 data   ��
#endif

#if (MAX_YEAR_TAB_CHG>6)
    0,      0,      0,   //  season-tab7 data   ��
#endif

#if (MAX_YEAR_TAB_CHG>7)
    0,      0,      0,  //  season-tab8 data   ��
#endif

#if (MAX_YEAR_TAB_CHG>8)
    0,      0,      0,   //  season-tab9 data ��
#endif

#if (MAX_YEAR_TAB_CHG>9)
    0,      0,      0,   //  season-tab10 data ��
#endif

    0x0000, // csck  //
};


/*************************************************************************
**  ���ʹ���- �ܱ��ʼ��Ĭ������
*************************************************************************/
const  E2P_TRIFF_WEEK_TABLE_MAP  code   default_triff_week_tab = 
{
    1,  1,  1,  1,  1,  1,  1,    // week-tab1 data   ����~��6  ��ʱ�α�1//
#if (MAX_INDEX_WEEKDAY_TAB>1)
    1,  1,  1,  1,  1,  1,  1,    // week-tab2 data   ����~��6  ��ʱ�α�1//
#endif

#if (MAX_INDEX_WEEKDAY_TAB>2)
    1,  1,  1,  1,  1,  1,  1,    // week-tab3 data   ����~��6  ��ʱ�α�1//
#endif

#if (MAX_INDEX_WEEKDAY_TAB>3)
    1,  1,  1,  1,  1,  1,  1,    // week-tab4 data   ����~��6  ��ʱ�α�1//
#endif

#if (MAX_INDEX_WEEKDAY_TAB>4)
    1,  1,  1,  1,  1,  1,  1,    // week-tab5 data   ����~��6  ��ʱ�α�1//
#endif

#if (MAX_INDEX_WEEKDAY_TAB>5)
    1,  1,  1,  1,  1,  1,  1,    // week-tab6 data   ����~��6  ��ʱ�α�1//
#endif

#if (MAX_INDEX_WEEKDAY_TAB>6)
    1,  1,  1,  1,  1,  1,  1,    // week-tab17 data   ����~��6  ��ʱ�α�1//
#endif

#if (MAX_INDEX_WEEKDAY_TAB>7)
    1,  1,  1,  1,  1,  1,  1,    // week-tab8 data   ����~��6  ��ʱ�α�1//
#endif

    0x0000,   // csck  //
};


/*************************************************************************
**  ���ʹ���- ��ʱ�α�ÿ������л���Ϊ10����ʼ��Ĭ������ 
*************************************************************************/
const  E2P_TRIFF_DAY_TABLE_MAP  code   default_triff_day_tab = 
{
    //��ʱ�α�1  //
    0,      0,      1,   //  day-tab1-chg1  data  0ʱ0�ַ���1  //
    #if (MAX_DAY_TRIFF_CHG>1)
    0,      0,      0,   //  day-tab1-chg2  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>2)
    0,      0,      0,  //  day-tab1-chg3  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>3)
    0,      0,      0,  //  day-tab1-chg4  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>4)
    0,      0,      0,   //  day-tab1-chg5  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>5)
    0,      0,      0,   //  day-tab1-chg6  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>6)
    0,      0,      0,   //  day-tab1-chg7  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>7)
    0,      0,      0,  //  day-tab1-chg8  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>8)
    0,      0,      0,   //  day-tab1-chg9 data  0ʱ0�ַ���1  //
    #endif
    #if (MAX_DAY_TRIFF_CHG>9)
    0,      0,      0,   //  day-tab1-chg10 data  0ʱ0�ַ���1  //
    #endif

#if (MAX_INDEX_DAY_TAB>1)
    //��ʱ�α�2  //
    0,      0,      1,   //  day-tab2-chg1  data  0ʱ0�ַ���1  //
    #if (MAX_DAY_TRIFF_CHG>1)
    0,      0,      0,  //  day-tab2-chg2  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>2)
    0,      0,      0,   //  day-tab2-chg3  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>3)
    0,      0,      0,   //  day-tab2-chg4 data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>4)
    0,      0,      0,  //  day-tab2-chg5  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>5)
    0,      0,      0,   //  day-tab2-chg6  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>6)
    0,      0,      0,   //  day-tab2-chg7  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>7)
    0,      0,      0,  //  day-tab2-chg8  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>8)
    0,      0,      0,   //  day-tab2-chg9  data  0ʱ0�ַ���1  //
    #endif
    #if (MAX_DAY_TRIFF_CHG>9)
    0,      0,      0,  //  day-tab2-chg10  data  0ʱ0�ַ���1  //
    #endif
#endif

#if (MAX_INDEX_DAY_TAB>2)
    //��ʱ�α�3  //
    0,      0,      1,   //  day-tab3-chg1  data  0ʱ0�ַ���1  //
    #if (MAX_DAY_TRIFF_CHG>1)
    0,      0,      0,   //  day-tab3-chg2  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>2)
    0,      0,      0,   //  day-tab3-chg3  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>3)
    0,      0,      0,   //  day-tab3-chg4  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>4)
    0,      0,      0,   //  day-tab3-chg5  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>5)
    0,      0,      0,  //  day-tab3-chg6  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>6)
    0,      0,      0,  //  day-tab3-chg7  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>7)
    0,      0,      0,  //  day-tab3-chg8  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>8)
    0,      0,      0,   //  day-tab3-chg9  data  0ʱ0�ַ���1  //
    #endif
    #if (MAX_DAY_TRIFF_CHG>9)
    0,      0,      0,   //  day-tab3-chg10  data  0ʱ0�ַ���1  //
    #endif
#endif

#if (MAX_INDEX_DAY_TAB>3)
    //��ʱ�α�4 //
    0,      0,      1,   //  day-tab4-chg1  data  0ʱ0�ַ���1  //
    #if (MAX_DAY_TRIFF_CHG>1)
    0,      0,      0,   //  day-tab4-chg2  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>2)
    0,      0,      0,    //  day-tab4-chg3  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>3)
    0,      0,      0,    //  day-tab4-chg4  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>4)
    0,      0,      0,    //  day-tab4-chg5  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>5)
    0,      0,      0,    //  day-tab4-chg6  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>6)
    0,      0,      0,    //  day-tab4-chg7  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>7)
    0,      0,      0,   //  day-tab4-chg8  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>8)
    0,      0,      0,    //  day-tab4-chg9  data  0ʱ0�ַ���1  //
    #endif
    #if (MAX_DAY_TRIFF_CHG>9)
    0,      0,      0,    //  day-tab4-chg10  data  0ʱ0�ַ���1  //
    #endif
#endif

#if (MAX_INDEX_DAY_TAB>4)
    //��ʱ�α�5  //
    0,      0,      1,   //  day-tab5-chg1  data  0ʱ0�ַ���1  //
    #if (MAX_DAY_TRIFF_CHG>1)
    0,      0,      0,   //  day-tab5-chg2  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>2)
    0,      0,      0,   //  day-tab5-chg3  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>3)
    0,      0,      0,   //  day-tab5-chg4  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>4)
    0,      0,      0,  //  day-tab5-chg5  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>5)
    0,      0,      0,   //  day-tab5-chg6  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>6)
    0,      0,      0,   //  day-tab5-chg7  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>7)
    0,      0,      0,  //  day-tab5-chg8  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>8)
    0,      0,      0,   //  day-tab5-chg9  data  0ʱ0�ַ���1  //
    #endif
    #if (MAX_DAY_TRIFF_CHG>9)
    0,      0,      0,   //  day-tab5-chg10  data  0ʱ0�ַ���1  //
    #endif
#endif

#if (MAX_INDEX_DAY_TAB>5)
    //��ʱ�α�6  //
    0,      0,      1,   //  day-tab6-chg1  data  0ʱ0�ַ���1  //
    #if (MAX_DAY_TRIFF_CHG>1)
    0,      0,      0,  //  day-tab6-chg2  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>2)
    0,      0,      0,   //  day-tab6-chg3  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>3)
    0,      0,      0,   //  day-tab6-chg4  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>4)
    0,      0,      0,   //  day-tab6-chg5  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>5)
    0,      0,      0,   //  day-tab6-chg6  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>6)
    0,      0,      0,   //  day-tab6-chg7  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>7)
    0,      0,      0,  //  day-tab6-chg8  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>8)
    0,      0,      0,   //  day-tab6-chg9  data  0ʱ0�ַ���1  //
    #endif
    #if (MAX_DAY_TRIFF_CHG>9)
    0,      0,      0,   //  day-tab6-chg10  data  0ʱ0�ַ���1  //
    #endif
#endif

#if (MAX_INDEX_DAY_TAB>6)
    //��ʱ�α�7  //
    0,      0,      1,   //  day-tab7-chg1  data  0ʱ0�ַ���1  //
    #if (MAX_DAY_TRIFF_CHG>1)
    0,      0,      0,   //  day-tab7-chg2  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>2)
    0,      0,      0,   //  day-tab7-chg3  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>3)
    0,      0,      0,   //  day-tab7-chg4  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>4)
    0,      0,      0,   //  day-tab7-chg5  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>5)
    0,      0,      0,   //  day-tab7-chg6  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>6)
    0,      0,      0,   //  day-tab7-chg7  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>7)
    0,      0,      0,  //  day-tab7-chg8  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>8)
    0,      0,      0,   //  day-tab7-chg9  data  0ʱ0�ַ���1  //
    #endif
    #if (MAX_DAY_TRIFF_CHG>9)
    0,      0,      0,   //  day-tab7-chg10  data  0ʱ0�ַ���1  //
    #endif
#endif

#if (MAX_INDEX_DAY_TAB>7)
    //��ʱ�α�8  //
    0,      0,      1,   //  day-tab8-chg1  data  0ʱ0�ַ���1  //
    #if (MAX_DAY_TRIFF_CHG>1)
    0,      0,      0,   //  day-tab8-chg2  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>2)
    0,      0,      0,   //  day-tab8-chg3  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>3)
    0,      0,      0,   //  day-tab8-chg4  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>4)
    0,      0,      0,   //  day-tab8-chg5  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>5)
    0,      0,      0,   //  day-tab8-chg6  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>6)
    0,      0,      0,   //  day-tab8-chg7  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>7)
    0,      0,      0,  //  day-tab8-chg8  data  0ʱ0�ַ���1  //
    #endif

    #if (MAX_DAY_TRIFF_CHG>8)
    0,      0,      0,   //  day-tab8-chg9  data  0ʱ0�ַ���1  //
    #endif
    #if (MAX_DAY_TRIFF_CHG>9)
    0,      0,      0,   //  day-tab8-chg10  data  0ʱ0�ַ���1  //
    #endif
#endif


    0x0000,   // csck  //
};


/*****************************************************************************
** Function name    :api_get_holidayTab_No
**
** Description         :���ݵ�ǰ�������ݺͽڼ��ձ����ݻ�ȡ��ǰ��ʱ�α��
**
** Parameters         :NONE          
**
** Returned value   :INT8U result;����ʱ�α�ţ�=0XFFʱ�����ȡʧ��//
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
#if (MAX_NUM_HOLIDAY_TAB >0)
INT8U api_get_holidayTab_No(void)
{
  HOLIDAY_TABLE  s_holiday_data;
  INT8U i;
  INT8U result;
 INT8U table_ok_len;

   
    //��ȡ�ڼ�������  //
    mem_read( (char*)&s_holiday_data.tab[0].month_BCD8,ADR_BLOCK81_HILIDAY_TAB_E2P,LEN_HOLIDAY_TABLE ,MEM_E2P1);

    //������Ч�ڼ��ձ���  //
    table_ok_len=0;
    for(i=0;i<MAX_NUM_HOLIDAY_TAB;i++)
    {
        if((s_holiday_data.tab[i].month_BCD8==0) ||(s_holiday_data.tab[i].month_BCD8 >0x12))    break;    // �������ж� //
        if((s_holiday_data.tab[i].day_BCD8==0) ||(s_holiday_data.tab[i].day_BCD8 >0x31))    break;    // �������ж� //
        if((s_holiday_data.tab[i].dayTable_No==0) ||(s_holiday_data.tab[i].dayTable_No >MAX_INDEX_DAY_TAB))    break;    // �������ж� //
        table_ok_len++;
    }
    if((table_ok_len==0) ||(table_ok_len>MAX_NUM_HOLIDAY_TAB))
    {
        return (0xff) ;   // ����ڼ�������ȫ���Ƿ� //
    }

    //��ȡ�ڼ�����ʱ�α��  //
    result =0xff;
    for(i=0;i<table_ok_len;i++)
    {
        if((s_holiday_data.tab[i].month_BCD8==0) ||(s_holiday_data.tab[0].month_BCD8 >0x12))    break;    // �������ж� //
        if((s_holiday_data.tab[i].day_BCD8==0) ||(s_holiday_data.tab[0].day_BCD8 >0x31))    break;    // �������ж� //
        if((s_holiday_data.tab[i].month_BCD8==gs_CurDateTime.Month) &&(s_holiday_data.tab[i].day_BCD8==gs_CurDateTime.Day)) 
        {
            result =   s_holiday_data.tab[i].dayTable_No;
            if((result==0)||(result>MAX_INDEX_DAY_TAB))
            {
                result = 0xff;   
            }
            break;
        }
    }
    
    return (result) ; 
    
}
#endif

/*****************************************************************************
** Function name    :api_get_seasonTab_No
**
** Description         :���ݵ�ǰ�������ݺͼ��ڱ����ݻ�ȡ��ǰ�ܱ��
**
** Parameters         :NONE          
**
** Returned value   :INT8U result;��ǰ�ܱ�ţ�=0XFFʱ�����ȡʧ��
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
INT8U api_get_seasonTab_No(void)
{
  SEASON_TABLE  s_season_data;
  INT8U i;
  INT8U result;
  INT8U table_ok_len;


    //��ȡ���ڱ�����  //
    mem_read( (char*)&s_season_data.tab[0].month_BCD8,ADR_BLOCK82_SEASON_TAB_E2P,LEN_SEASON_TABLE ,MEM_E2P1);

    //������Ч���ڱ���  //
    table_ok_len=0;
    for(i=0;i<MAX_YEAR_TAB_CHG;i++)
    {
        if((s_season_data.tab[i].month_BCD8==0) ||(s_season_data.tab[i].month_BCD8 >0x12))    break;    // �������ж� //
        if((s_season_data.tab[i].day_BCD8==0) ||(s_season_data.tab[i].day_BCD8 >0x31))    break;    // �������ж� //
        if((s_season_data.tab[i].weekTable_No==0) ||(s_season_data.tab[i].weekTable_No >MAX_INDEX_WEEKDAY_TAB))    break;    // �������ж� //
        table_ok_len++;
    }
    
    if((table_ok_len==0) ||(table_ok_len>MAX_YEAR_TAB_CHG))
    {
        return (0XFF) ;   // �����ȡʧ�� //
    }

    //��ȡ���ڱ��ڵ��ܱ��  //
    result =0XFF;
    gs_current_triff_var.seasonTab_No =0;
    for(i=0;i<table_ok_len;i++)
    {
        if((s_season_data.tab[i].month_BCD8==0) ||(s_season_data.tab[i].month_BCD8 >0x12))    break;    // �������ж� //
        if((s_season_data.tab[i].day_BCD8==0) ||(s_season_data.tab[i].day_BCD8 >0x31))    break;    // �������ж� //


        if(s_season_data.tab[i].month_BCD8 < gs_CurDateTime.Month) 
        {
            gs_current_triff_var.seasonTab_No++;
            result=s_season_data.tab[i].weekTable_No;
        }
        else if(s_season_data.tab[i].month_BCD8== gs_CurDateTime.Month)
        {
            if(s_season_data.tab[i].day_BCD8<=gs_CurDateTime.Day)
            {
                gs_current_triff_var.seasonTab_No++;
                result =s_season_data.tab[i].weekTable_No;               
            }
            else
            {
                if(i==0)
                {
                    gs_current_triff_var.seasonTab_No =table_ok_len;
                    result =s_season_data.tab[table_ok_len-1].weekTable_No;  
                    break;
                }
                else
                {
                    break;
                }
            }   
        }
        else
        {
                if(i==0)
                {
                    gs_current_triff_var.seasonTab_No =table_ok_len;
                    result =s_season_data.tab[table_ok_len-1].weekTable_No;  
                    break;
                }
                else
                {
                    break;
                }
        }
    }
    
    gs_current_triff_var.seasonTab_No ++; //seasonTab_No��1��ʼ����������+1 //
    return (result) ; 
    
}



/*****************************************************************************
** Function name    :api_get_dayTab_No
**
** Description         :���ݵ�ǰRTC�����ݺ��ܱ�Ż�ȡ��ǰ��ʱ�α��
**
** Parameters         :INT8U weekTab_no : �ܱ��    
**
** Returned value   :INT8U result;��ǰ��ʱ�α�ţ�=0XFFʱ�����ȡʧ��
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
INT8U api_get_dayTab_No(INT8U weekTab_no)
{
    WEEK_TABLE_UNIT  s_weekTab_data; 
    INT8U result;

    //�����жϴ���  //
    if((weekTab_no==0) ||(weekTab_no>MAX_INDEX_WEEKDAY_TAB))
    {
        gs_current_triff_var.weekTab_No =1;
         weekTab_no = 1;    
    }
    //��ȡ�ܱ�����  //
    mem_read( (char*)&s_weekTab_data.Sun_Tab,ADR_BLOCK83_WEEK_TAB_E2P+((weekTab_no-1)*LEN_WEEK_TABLE_ONE),LEN_WEEK_TABLE_ONE ,MEM_E2P1);
    

    //��ȡ��Ӧ�ܱ��е���ʱ�α��  //
    switch(gs_CurDateTime.Week)
    {
        case WEEK_Sunday:
            result= s_weekTab_data.Sun_Tab;    
            break;
        case WEEK_Monday:
            result= s_weekTab_data.Mon_Tab;    
            break;
        case WEEK_Tuesday:
            result= s_weekTab_data.Tues_Tab;    
            break;
        case WEEK_Wednesday:
            result= s_weekTab_data.Wed_Tab;    
            break;
        case WEEK_Thursday:
            result= s_weekTab_data.Thurs_Tab;    
            break;
        case WEEK_Friday:
            result= s_weekTab_data.Fri_Tab;    
            break;
        case WEEK_Saturday:
            result= s_weekTab_data.Sat_Tab;    
            break;
        default:
            sys_err();          //RTC ����ϵͳ��λ���� //
            break;
    }

    if((result==0)||(result>MAX_INDEX_DAY_TAB))
    {
        result=0xff;       
    }
   
    return (result) ; 
    
}


/*****************************************************************************
** Function name    :api_get_dayTab_No
**
** Description         :���ݵ�ǰRTC�����ݺ��ܱ�Ż�ȡ��ǰ��ʱ�α��
**
** Parameters         :INT8U weekTab_no : �ܱ��    
**
** Returned value   :INT8U result;��ǰ��ʱ�α�ţ�=0XFFʱ�����ȡʧ��
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
INT8U api_get_triff_No(INT8U dayTab_no)
{
 DAY_TABLE s_dayTab_data;
 INT8U i;
 INT8U table_ok_len;
 INT8U result;
  
    
     //�����жϴ���  //
    if((dayTab_no==0)||(dayTab_no>MAX_INDEX_DAY_TAB))
    {
        gs_current_triff_var.dayTab_No =1;
        dayTab_no = 1;          
    }

    //��ȡ��ǰѡ����ʱ�α�����  //
    mem_read( (char*)&s_dayTab_data.tab[0].hour_BCD8,ADR_BLOCK84_DAY_TAB_E2P+((dayTab_no-1)*LEN_DAY_TABLE_ONE),LEN_DAY_TABLE_ONE ,MEM_E2P1);

    //������Ч��ʱ�α���  //
    table_ok_len=0;
    for(i=0;i<MAX_DAY_TRIFF_CHG;i++)
    {
        if(Lib_BCDCHK(&s_dayTab_data.tab[i].hour_BCD8,2) ==FALSE )  break;    // ʱ�����ݷǷ� //
        if(s_dayTab_data.tab[i].hour_BCD8>0X23 )    break;    // Сʱ�����ж� //
        if(s_dayTab_data.tab[i].minute_BCD8>0X59 )    break;    // ���������ж� //
        if((s_dayTab_data.tab[i].triff_No==0) ||(s_dayTab_data.tab[i].triff_No >TARIFF_MAX_NUM))    break;    // ���������ж� //
        table_ok_len++;
    }
    
    if((table_ok_len==0) ||(table_ok_len>MAX_DAY_TRIFF_CHG))
    {
        return (0XFF) ;   // �����ȡʧ�� //
    }


    //��ȡ���ڱ��ڵ��ܱ��  //
    result =0XFF;
    gs_current_triff_var.seasonTab_No =0;
    for(i=0;i<table_ok_len;i++)
    {
        if(Lib_BCDCHK(&s_dayTab_data.tab[i].hour_BCD8,2) ==FALSE )  break;    // ʱ�����ݷǷ� //
        if(s_dayTab_data.tab[i].hour_BCD8>0X23 )    break;    // Сʱ�����ж� //
        if(s_dayTab_data.tab[i].minute_BCD8>0X59 )    break;    // ���������ж� //


        if(s_dayTab_data.tab[i].hour_BCD8 < gs_CurDateTime.Hour) 
        {
            result=s_dayTab_data.tab[i].triff_No;
        }
        else if(s_dayTab_data.tab[i].hour_BCD8== gs_CurDateTime.Hour)
        {
            if(s_dayTab_data.tab[i].minute_BCD8<=gs_CurDateTime.Minute)
            {
                result=s_dayTab_data.tab[i].triff_No;              
            }
            else
            {
                if(i==0)
                {
                    result =s_dayTab_data.tab[table_ok_len-1].triff_No;  
                    break;
                }
                else
                {
                    break;
                }
            }   
        }
        else
        {
                if(i==0)
                {
                   result =s_dayTab_data.tab[table_ok_len-1].triff_No;  
                    break;
                }
                else
                {
                    break;
                }
        }
    }
    
    return (result) ; 

}


/*****************************************************************************
** Function name    :api_update_triffNo_pre_minute
**
** Description         :���µ�ǰ���ʺ���
**
** Parameters         :NONE   
**
** Returned value   :NONE   
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_update_triffNo_pre_minute(void)
{
INT8U u8_temp;

    // ���жϽڼ���  //
#if (MAX_NUM_HOLIDAY_TAB >0)
    u8_temp = api_get_holidayTab_No();
#else
    u8_temp=0xff;
#endif
    if(u8_temp!=0xff)
    {
        //��ǰ����Ϊ�ڼ���  //
        gs_current_triff_var.dayTab_No = u8_temp;
        
    }
    else
    {
        // ��ȡ���ڱ�λ�� //  
        u8_temp = api_get_seasonTab_No();
        if(u8_temp==0xFF)
        {
            gs_current_triff_var.seasonTab_No =1;
            gs_current_triff_var.weekTab_No = 1;
        }
        else
        {
            gs_current_triff_var.weekTab_No = u8_temp;   
        }
        gs_current_triff_var.dayTab_No = api_get_dayTab_No(gs_current_triff_var.weekTab_No);
        
    }

    u8_temp = api_get_triff_No(gs_current_triff_var.dayTab_No);
    if((u8_temp ==0) ||(u8_temp >TARIFF_MAX_NUM))
    {
        u8_temp = DEF_TRIFF_no;
    }

    gs_current_triff_var.triff_No = u8_temp;
 
}




#endif
/***************************************************************
*    END
****************************************************************/


