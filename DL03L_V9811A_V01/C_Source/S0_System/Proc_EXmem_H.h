/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Proc_EXmem_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: �ⲿ�洢��C����������ļ�
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#ifndef _Proc_EXmem_H
#define _Proc_EXmem_H

/***************************************************************
*    1     ������Ԥ����   
****************************************************************/
#define DM_FLASH_EN 0		//	 1:����оƬ�ڲ�FLASH 	0:��ʹ��
#define DM_E2P_EN   1		//	 1:����оƬ�ⲿE2P 	0:��ʹ��

//�洢���Ͷ���  //
//mem_table.type define
#define MEM_RAM				0X01			
#define MEM_EXRAM			(MEM_RAM+1)

#if (DM_E2P_EN==1)
#define MEM_E2P1			MEM_EXRAM   //MEM_DMFLASH 
#endif

#if (DM_FLASH_EN==1)	
#define MEM_DMFLASH         MEM_EXRAM//0X04  
#endif

#define E2P_PAGE   EE_PageMask


#define EE_AddrStart               0x0000U                                  //EEPROM��ʼ��ַ //
#define EE_DOUBLE_DATA_ADDR_START  EE_AddrStart      //˫��������������ʼ��ַ  //
#define E2PBAK_SIZE   (512)   //  E2P��������Ϊ��벿�ֵĿ�ʼ//
#define EE_SINGLE_DATA_ADDR_START  (EE_DOUBLE_DATA_ADDR_START+2*(E2PBAK_SIZE))      //��������������ʼ��ַ  //


/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
//E2P���ݼ������Ͷ���  //
typedef struct 
{
    uint8  u8_No;
    uint8  mem_type;
    uint16 u16_adr;
    uint16 u16_len; 
} E2P_CHECK_TAB;


//˫���ݴ�У��E2P�洢���ݸ�ʽ����  //
typedef struct 
{
    E2P_CURRENT_ENERGY_DATA_MAP   L0_energy_data;
    E2P_CURRENT_MD_DATA_MAP   L0_MD_data;
    E2P_METER_PARAM1_MAP  meter_param1;
    E2P_METER_VAR_MAP       meter_var;
    ST_EMU_ADJ_PARAM    emu_adj_param;       // ����оƬ�����У׼���� //
    DIS_PARAM_DATA   dis_param;
#if (TARIFF_MAX_NUM>1)
    E2P_TRIFF_PARAM_MAP  Triff_param;
#endif
#if (BILL_MAX_NUM>0)
    E2P_BILL_VAR_MAP    Bill_var;                    //���ݽ���ʱ����ر��� //
	EVEN_CLASSII_VAR    even_var;         // 7��2���¼�����//
#endif
} DBE2P_MAP;


//���ݴ�У��E2P�洢���ݸ�ʽ����  //
typedef struct 
{
#if (BILL_MAX_NUM>0)
    E2P_BILL_DATA_MAP_ONE  Bill_data[BILL_MAX_NUM];   // 12 ���½������� //
#endif
    E2P_EVEN_I_DATA_MAP    even_I;  // 2 ���¼���¼ //
	E2P_EVEN_II_DATA_MAP    even_II;  // 2 ���¼���¼ //
    INT8U       load_start_e2p;
} SGE2P_MAP;


/***************************************************************
*    3    ��������       
****************************************************************/
extern const  E2P_CHECK_TAB  code mem_table[] ;


/***************************************************************
*    4     ��������        
****************************************************************/
extern INT16U get_mem_ck_data( INT16U src, INT16U  lenth, INT8U memType );
extern INT8U get_mem_table_Index( INT16U adr, INT8U memType ) ;
extern void mem_to_mem( INT16U dst, INT16U src, 	INT16U lenth, INT8U mode );
extern void mem_fill( INT16U dst, INT16U lenth, INT8U xx, INT8U memType );
extern void mem_read( INT8U* dst,  INT16U src, INT16U lenth, INT8U memType );
extern void mem_write( INT16U dst,  INT8U *src, INT16U lenth, INT8U memType );
extern void mem_db_write( INT16U dst,  INT8U *src, INT16U len, INT8U memType );
extern void mem_db_check( void );
extern void mem_db_clr( uint8 type );

/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/
// E2P MAP //


//BLOCK00  ��ǰ������ //
#define  No_BLOCK00_EC_L0_E2P    0    // ������Ŀ������ //
#define ADR_BLOCK00_EC_L0_E2P   EE_DOUBLE_DATA_ADDR_START +ST_MB_OFFSET(DBE2P_MAP,L0_energy_data)   //0. ��ǰ�й������������׵�ַ  //
#define LEN_BLOCK00_EC_L0_E2P   sizeof(E2P_CURRENT_ENERGY_DATA_MAP)

//BLOCK01  ��ǰ����������� //
#define  No_BLOCK01_MMD_L0_E2P    1    // ������Ŀ������ //
#define ADR_BLOCK01_MMD_L0_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,L0_MD_data)   //  1. ��ǰ����������������׵�ַ  //
#define LEN_BLOCK01_MMD_L0_E2P   sizeof(E2P_CURRENT_MD_DATA_MAP)

//BLOCK20  ��������1 //
#define  No_BLOCK20_METER_PARAM1_E2P   20    // ������Ŀ������ //
#define ADR_BLOCK20_METER_PARAM1_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,meter_param1)   //  1. ��ǰ����������������׵�ַ  //
#define LEN_BLOCK20_METER_PARAM1_E2P   sizeof(E2P_METER_PARAM1_MAP)

//BLOCK21  ��������-��ʾ������ //
#define  No_BLOCK21_DIS_PARAM_E2P   21    // ������Ŀ������ //
#define ADR_BLOCK21_DIS_PARAM_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,dis_param)   //  1. ��ǰ����������������׵�ַ  //
#define LEN_BLOCK21_DIS_PARAM_E2P   sizeof(DIS_PARAM_DATA)

//BLOCK25  ������������ //
#define  No_BLOCK25_METER_VAR_E2P   25    // ������Ŀ������ //
#define ADR_BLOCK25_METER_VAR_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,meter_var)   //  1. ��ǰ����������������׵�ַ  //
#define LEN_BLOCK25_METER_VAR_E2P   sizeof(E2P_METER_VAR_MAP)

//BLOCK100  �½������������  //
#define  No_BLOCK26_BILL_VAR_E2P    26    // ������Ŀ������ //
#define ADR_BLOCK26_BILL_VAR_E2P           EE_DOUBLE_DATA_ADDR_START +ST_MB_OFFSET(DBE2P_MAP,Bill_var)   //0. ��ǰ�й������������׵�ַ  //
#define LEN_BLOCK26_BILL_VAR_E2P           sizeof(E2P_BILL_VAR_MAP)

//////////////////////BLOCK 27     METER_VAR/////////////
#define  ADR_CLASS2CNT_START_E2P         ADR_BLOCK27_EVENII_E2P+CLASSII_cnt_start
#define  ADR_CLASS2FLG_START_E2P         ADR_BLOCK27_EVENII_E2P+CLASSII_flg_start
#define  ADR_CLASS2DATA_START_E2P        ADR_BLOCK27_EVENII_E2P+CLASSII_data_start

// �¼���¼������// ���ݴ�У��//
#define  No_BLOCK27_EVENII_data   27    // ������Ŀ������ //
#define  ADR_BLOCK27_EVENII_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,even_var)   //

//BLOCK70  EMU У�������//
#define  No_BLOCK70_EMU_PARAM_E2P   70    // ������Ŀ������ //
#define ADR_BLOCK70_EMU_PARAM_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,emu_adj_param)   //  1. ��ǰ����������������׵�ַ  //
#define LEN_BLOCK70_EMU_PARAM_E2P   sizeof(ST_EMU_ADJ_PARAM)

//BLOCK81~84 ���ʱ����������  //
#if (TARIFF_MAX_NUM>1)
#define  No_BLOCK80_TRIFF_PARAM_E2P   80    // ������Ŀ������ //
#define ADR_BLOCK80_TRIFF_PARAM_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,Triff_param)   //  3. ��ǰ����������������׵�ַ  //
#define LEN_BLOCK80_TRIFF_PARAM_E2P   sizeof(E2P_TRIFF_PARAM_MAP)
#if(MAX_NUM_HOLIDAY_TAB>0)  
#define  No_BLOCK81_HILIDAY_TAB_E2P   81    // ������Ŀ������ //
#define ADR_BLOCK81_HILIDAY_TAB_E2P   (ADR_BLOCK80_TRIFF_PARAM_E2P+OFFSET_HoliTab)
#define LEN_BLOCK81_HILIDAY_TAB_E2P    LEN_HoliTab
#endif
#define  No_BLOCK82_SEASON_TAB_E2P     82    // ������Ŀ������ //
#define ADR_BLOCK82_SEASON_TAB_E2P   (ADR_BLOCK80_TRIFF_PARAM_E2P+OFFSET_SeasonTab)
#define LEN_BLOCK82_SEASON_TAB_E2P     LEN_SeasonTab

#define  No_BLOCK83_WEEK_TAB_E2P    83    // ������Ŀ������ //
#define ADR_BLOCK83_WEEK_TAB_E2P   (ADR_BLOCK80_TRIFF_PARAM_E2P+OFFSET_WeekTab)
#define LEN_BLOCK83_WEEK_TAB_E2P      LEN_WeekTab

#define  No_BLOCK84_DAY_TAB_E2P    84    // ������Ŀ������ //
#define ADR_BLOCK84_DAY_TAB_E2P   (ADR_BLOCK80_TRIFF_PARAM_E2P+OFFSET_DayTab)
#define LEN_BLOCK84_DAY_TAB_E2P       LEN_DayTab
#endif


////////////////////             BLOCK 20        METER_PARAM1  /////////////
#define ADR_METER_PARAM1_MD                 (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,md_param))
#define ADR_METER_PARAM1_SETL_DDHH    (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,bill_ms_param))
#define ADR_METER_PARAM1_EMU_FAST    (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,EMU_fast_flg))
#define ADR_METER_PARAM1_METER_ID    (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,meter_id[0]))
#define ADR_METER_PARAM1_PW0    (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,password[0][0]))
#define ADR_METER_PARAM1_PW1    (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,password[1][0]))
#define ADR_METER_PARAM1_FC_CFG    (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,fac_cfg[0]))
#define ADR_METER_PARAM1_BAT_LEVEL    (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,bat_level[0]))
// �����������в���//
#define ADR_METER_PARAM1_LOAD_PTR   (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,load_Ptr_var))
#define ADR_METER_PARAM1_LOAD_NUM   (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,load_Num_var))
// ���ɼ�¼����//
#define ADR_METER_PARAM1_load_lptime_inv_var   (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,load_lptime_inv_var))
#define ADR_METER_PARAM1_load_egcode_var   (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,load_egcode_var[0]))


////////////////////            BLOCK21  ��������-��ʾ�����  /////////////
#define ADR_DIS_PARAM_AUTO_SEC                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,auto_sec))  // �Զ�ѭ����ʾ����ʱ��  //
#define ADR_DIS_PARAM_KEY_SEC                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,key_sec))  // ������ʾ����ʱ��  //
#define ADR_DIS_PARAM_BG_SEC                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,bg_sec))   // �����������ʱ��  //
#define ADR_DIS_PARAM_EC_FORM                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,ec_form)) // ������ʽ  //
#define ADR_DIS_PARAM_AUTO_TAB                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,auto_item))  //0Ϊ��ʾ������1~31Ϊ��ʾ��Ŀ����������ʾ31����Ŀ  //
#define ADR_DIS_PARAM_KEY_TAB                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,key_item))  //0Ϊ��ʾ������1~31Ϊ��ʾ��Ŀ����������ʾ31����Ŀ  //
#define ADR_DIS_PARAM_PWN_TAB                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,pwn_item))  //0Ϊ��ʾ������1~31Ϊ��ʾ��Ŀ����������ʾ31����Ŀ  //

////////////////////////BLOCK 25     METER_VAR/////////////
#define ADR_METER_VAR_RTC                 (ADR_BLOCK25_METER_VAR_E2P+ST_MB_OFFSET(E2P_METER_VAR_MAP,save_rtc))

////////////////////////BLOCK 26     METER_VAR/////////////
#define ADR_BLOCK26_BILL_VAR_PTR_E2P   ADR_BLOCK26_BILL_VAR_E2P+OFFSET_bill_var_ptrNo
#define ADR_BLOCK26_BILL_VAR_DATETTIME_E2P   ADR_BLOCK26_BILL_VAR_E2P+OFFSET_bill_var_dateTime


///////////////////////////////////////////////////////////////////////////////////////////////////
//��У�鵥��������////
//////////////////////////////////////////////////////////////
//BLOCK101~136 �½���������  //
#if (BILL_MAX_NUM>0)
//BLOCK101  ��1�½���������  //
#define  No_BLOCK101_BILL1_DATA_E2P    101    // ������Ŀ������ //
#define ADR_BLOCK101_BILL1_DATA_E2P   EE_SINGLE_DATA_ADDR_START   //0. ��ǰ�й������������׵�ַ  //
#define LEN_BLOCK10X_BILLX_DATA_E2P   sizeof(E2P_BILL_DATA_MAP_ONE)

//BLOCK102 ��2�½���������  //
#define  No_BLOCK102_BILL2_DATA_E2P    102    // ������Ŀ������ //
#define ADR_BLOCK102_BILL2_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[1])   //0. ��ǰ�й������������׵�ַ  //    

//BLOCK103  ��3�½���������  //
#define  No_BLOCK103_BILL3_DATA_E2P    103   // ������Ŀ������ //
#define ADR_BLOCK103_BILL3_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[2])   //0. ��ǰ�й������������׵�ַ  //
      

//BLOCK104  ��4�½���������  //
#define  No_BLOCK104_BILL4_DATA_E2P    104    // ������Ŀ������ //
#define ADR_BLOCK104_BILL4_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[3])   //0. ��ǰ�й������������׵�ַ  //

//BLOCK105  ��5�½���������  //
#define  No_BLOCK105_BILL5_DATA_E2P    105    // ������Ŀ������ //
#define ADR_BLOCK105_BILL5_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[4])   //0. ��ǰ�й������������׵�ַ  //

//BLOCK106  ��6�½���������  //
#define  No_BLOCK106_BILL6_DATA_E2P    106    // ������Ŀ������ //
#define ADR_BLOCK106_BILL6_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[5])   //0. ��ǰ�й������������׵�ַ  //

//BLOCK107  ��7�½���������  //
#define  No_BLOCK107_BILL7_DATA_E2P    107    // ������Ŀ������ //
#define ADR_BLOCK107_BILL7_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[6])   //0. ��ǰ�й������������׵�ַ  //

//BLOCK108  ��8�½���������  //
#define  No_BLOCK108_BILL8_DATA_E2P    108    // ������Ŀ������ //
#define ADR_BLOCK108_BILL8_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[7])   //0. ��ǰ�й������������׵�ַ  //

//BLOCK109  ��9�½���������  //
#define  No_BLOCK109_BILL9_DATA_E2P    109    // ������Ŀ������ //
#define ADR_BLOCK109_BILL9_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[8])   //0. ��ǰ�й������������׵�ַ  //

//BLOCK110  ��10�½���������  //
#define  No_BLOCK110_BILL10_DATA_E2P    110    // ������Ŀ������ //
#define ADR_BLOCK110_BILL10_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[9])   //0. ��ǰ�й������������׵�ַ  //

//BLOCK111  ��11�½���������  //
#define  No_BLOCK111_BILL11_DATA_E2P    111   // ������Ŀ������ //
#define ADR_BLOCK111_BILL11_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[10])   //0. ��ǰ�й������������׵�ַ  //

//BLOCK112  ��12�½���������  //
#define  No_BLOCK112_BILL12_DATA_E2P    112    // ������Ŀ������ //
#define ADR_BLOCK112_BILL12_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[11])   //0. ��ǰ�й������������׵�ַ  //
#endif


//BLOCK151  ���CLASSII ���¼���//
#define ADR_BLOCK150_EVENI_START_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_I)   //   2 ���¼���¼�������׵�ַ //
#define  No_BLOCK150_EVENI_PROG_E2P  150    // ������Ŀ������ //
#define ADR_BLOCK150_EVENI_PROG_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_I.prog)   //    //
#define  No_BLOCK151_EVENI_resetMD_E2P  151    // ������Ŀ������ //
#define ADR_BLOCK151_EVENI_resetMD_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_I.resetMD)   //    //
#define  No_BLOCK152_EVENI_setRtc_E2P  152    // ������Ŀ������ //
#define ADR_BLOCK152_EVENI_setRtc_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_I.setRtc)   //    //
//#define  No_BLOCK153_EVENI_powerDown_E2P  153    // ������Ŀ������ //
//#define ADR_BLOCK153_EVENI_powerDown_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_I.powerDown)   //    //
//#define LEN_BLOCK15X_EVENI_E2P               LEN_CLASS_I_UNIT
#define LEN_BLOCK15X_EVENI_E2P               LEN_CLASS_I_UNIT   // 
#define ADR_BLOCK_min_EVENI_E2P     ADR_BLOCK150_EVENI_PROG_E2P //     //
#define ADR_BLOCK_max_EVENI_E2P    ADR_BLOCK152_EVENI_setRtc_E2P  //    //

//����������ʼ


#define ADR_BLOCK160_EVENII_START_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_II)
#define  No_BLOCK161_EVENII_PWN_E2P  161    // ������Ŀ������ //
#define ADR_BLOCK161_EVENII_PWN_E2P   ADR_BLOCK160_EVENII_START_E2P+ ST_MB_OFFSET(E2P_EVEN_II_DATA_MAP,PWN)   //    //

#define  No_BLOCK162_EVENII_lowbattery_E2P  162    // ������Ŀ������ //
#define ADR_BLOCK162_EVENII_lowbattery_E2P   ADR_BLOCK160_EVENII_START_E2P+ ST_MB_OFFSET(E2P_EVEN_II_DATA_MAP,lowbattery)   //    //

#define  No_BLOCK163_EVENII_COVER_E2P  163    // ������Ŀ������ //
#define ADR_BLOCK163_EVENII_COVER_E2P   ADR_BLOCK160_EVENII_START_E2P+ ST_MB_OFFSET(E2P_EVEN_II_DATA_MAP,Cover)   //    //
#define  No_BLOCK164_EVENII_L1reverse_E2P  164   // ������Ŀ������ //
#define  ADR_BLOCK164_EVENII_L1reverse_E2P   ADR_BLOCK160_EVENII_START_E2P+ ST_MB_OFFSET(E2P_EVEN_II_DATA_MAP,L1reverse)   //    //

#define LEN_BLOCK16X_EVENI_E2P            LEN_CLASS_II_UNIT   // 
#define ADR_BLOCK_min_EVENII_E2P     ADR_BLOCK161_EVENII_PWN_E2P //     //
#define ADR_BLOCK_max_EVENII_E2P    ADR_BLOCK164_EVENII_L1reverse_E2P  //    //




//��������180  ����  ��У��//
#define  No_BLOCK180_LOAD_START_DATA   180    // ������Ŀ������ //
#define  ADR_BLOCK180_LOAD_START_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,load_start_e2p)   //0x472  1138//

/***************************************************************
*    END
****************************************************************/

#endif
