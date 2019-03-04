/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Proc_EXmem_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: Íâ²¿´æ´¢Æ÷C´úÂëµÄÉùÃ÷ÎÄ¼þ
**note			: V9811A £¬MERTER FOR DL03C
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
*    1     Á¢¼´ÊýÔ¤¶¨Òå   
****************************************************************/
#define DM_FLASH_EN 0		//	 1:²ÅÓÃÐ¾Æ¬ÄÚ²¿FLASH 	0:²»Ê¹ÓÃ
#define DM_E2P_EN   1		//	 1:²ÅÓÃÐ¾Æ¬Íâ²¿E2P 	0:²»Ê¹ÓÃ

//´æ´¢ÀàÐÍ¶¨Òå  //
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


#define EE_AddrStart               0x0000U                                  //EEPROMÆðÊ¼µØÖ· //
#define EE_DOUBLE_DATA_ADDR_START  EE_AddrStart      //Ë«±¸·ÝÊý¾ÝÇøµÄÆðÊ¼µØÖ·  //
#define E2PBAK_SIZE   (512)   //  E2P±¸·ÝÊý¾ÝÎªºó°ë²¿·ÖµÄ¿ªÊ¼//
#define EE_SINGLE_DATA_ADDR_START  (EE_DOUBLE_DATA_ADDR_START+2*(E2PBAK_SIZE))      //µ¥·ÝÊý¾ÝÇøµÄÆðÊ¼µØÖ·  //


/***************************************************************
*    2     Êý¾Ý½á¹¹ÉùÃ÷     
****************************************************************/
//E2PÊý¾Ý¼ì²é±íÀàÐÍ¶¨Òå  //
typedef struct 
{
    uint8  u8_No;
    uint8  mem_type;
    uint16 u16_adr;
    uint16 u16_len; 
} E2P_CHECK_TAB;


//Ë«±¸·Ý´øÐ£ÑéE2P´æ´¢Êý¾Ý¸ñÊ½ÉùÃ÷  //
typedef struct 
{
    E2P_CURRENT_ENERGY_DATA_MAP   L0_energy_data;
    E2P_CURRENT_MD_DATA_MAP   L0_MD_data;
    E2P_METER_PARAM1_MAP  meter_param1;
    E2P_METER_VAR_MAP       meter_var;
    ST_EMU_ADJ_PARAM    emu_adj_param;       // ¼ÆÁ¿Ð¾Æ¬µÄÎó²îÐ£×¼Êý¾Ý //
    DIS_PARAM_DATA   dis_param;
#if (TARIFF_MAX_NUM>1)
    E2P_TRIFF_PARAM_MAP  Triff_param;
#endif
#if (BILL_MAX_NUM>0)
    E2P_BILL_VAR_MAP    Bill_var;                    //Êý¾Ý½áËãÊ±µÄÏà¹Ø±äÁ¿ //
	EVEN_CLASSII_VAR    even_var;         // 7×é2ÀàÊÂ¼þ²ÎÊý//
#endif
} DBE2P_MAP;


//µ¥·Ý´øÐ£ÑéE2P´æ´¢Êý¾Ý¸ñÊ½ÉùÃ÷  //
typedef struct 
{
#if (BILL_MAX_NUM>0)
    E2P_BILL_DATA_MAP_ONE  Bill_data[BILL_MAX_NUM];   // 12 ¸öÔÂ½áËãÊý¾Ý //
#endif
    E2P_EVEN_I_DATA_MAP    even_I;  // 2 ÀàÊÂ¼þ¼ÇÂ¼ //
	E2P_EVEN_II_DATA_MAP    even_II;  // 2 ÀàÊÂ¼þ¼ÇÂ¼ //
    INT8U       load_start_e2p;
} SGE2P_MAP;


/***************************************************************
*    3    ±äÁ¿ÉùÃ÷       
****************************************************************/
extern const  E2P_CHECK_TAB  code mem_table[] ;


/***************************************************************
*    4     º¯ÊýÉùÃ÷        
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
*    5     ÆäËûÄÚÈÝ£¬ÀýÈçÎ±Ö¸ÁîµÈ       
****************************************************************/
// E2P MAP //


//BLOCK00  µ±Ç°µçÁ¿Çø //
#define  No_BLOCK00_EC_L0_E2P    0    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK00_EC_L0_E2P   EE_DOUBLE_DATA_ADDR_START +ST_MB_OFFSET(DBE2P_MAP,L0_energy_data)   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //
#define LEN_BLOCK00_EC_L0_E2P   sizeof(E2P_CURRENT_ENERGY_DATA_MAP)

//BLOCK01  µ±Ç°ÔÂ×î´óÐèÁ¿Çø //
#define  No_BLOCK01_MMD_L0_E2P    1    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK01_MMD_L0_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,L0_MD_data)   //  1. µ±Ç°ÔÂ×î´óÐèÁ¿Êý¾ÝÇøÊ×µØÖ·  //
#define LEN_BLOCK01_MMD_L0_E2P   sizeof(E2P_CURRENT_MD_DATA_MAP)

//BLOCK20  µç±í²ÎÊýÇø1 //
#define  No_BLOCK20_METER_PARAM1_E2P   20    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK20_METER_PARAM1_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,meter_param1)   //  1. µ±Ç°ÔÂ×î´óÐèÁ¿Êý¾ÝÇøÊ×µØÖ·  //
#define LEN_BLOCK20_METER_PARAM1_E2P   sizeof(E2P_METER_PARAM1_MAP)

//BLOCK21  µç±í²ÎÊýÇø-ÏÔÊ¾²ÎÊýÇø //
#define  No_BLOCK21_DIS_PARAM_E2P   21    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK21_DIS_PARAM_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,dis_param)   //  1. µ±Ç°ÔÂ×î´óÐèÁ¿Êý¾ÝÇøÊ×µØÖ·  //
#define LEN_BLOCK21_DIS_PARAM_E2P   sizeof(DIS_PARAM_DATA)

//BLOCK25  µç±í±äÁ¿Êý¾ÝÇø //
#define  No_BLOCK25_METER_VAR_E2P   25    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK25_METER_VAR_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,meter_var)   //  1. µ±Ç°ÔÂ×î´óÐèÁ¿Êý¾ÝÇøÊ×µØÖ·  //
#define LEN_BLOCK25_METER_VAR_E2P   sizeof(E2P_METER_VAR_MAP)

//BLOCK100  ÔÂ½áËã±äÁ¿Êý¾ÝÇø  //
#define  No_BLOCK26_BILL_VAR_E2P    26    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK26_BILL_VAR_E2P           EE_DOUBLE_DATA_ADDR_START +ST_MB_OFFSET(DBE2P_MAP,Bill_var)   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //
#define LEN_BLOCK26_BILL_VAR_E2P           sizeof(E2P_BILL_VAR_MAP)

//////////////////////BLOCK 27     METER_VAR/////////////
#define  ADR_CLASS2CNT_START_E2P         ADR_BLOCK27_EVENII_E2P+CLASSII_cnt_start
#define  ADR_CLASS2FLG_START_E2P         ADR_BLOCK27_EVENII_E2P+CLASSII_flg_start
#define  ADR_CLASS2DATA_START_E2P        ADR_BLOCK27_EVENII_E2P+CLASSII_data_start

// ÊÂ¼þ¼ÇÂ¼²ÎÊýÇø// µ¥·Ý´øÐ£Ñé//
#define  No_BLOCK27_EVENII_data   27    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define  ADR_BLOCK27_EVENII_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,even_var)   //

//BLOCK70  EMU Ð£±í²ÎÊýÇø//
#define  No_BLOCK70_EMU_PARAM_E2P   70    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK70_EMU_PARAM_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,emu_adj_param)   //  1. µ±Ç°ÔÂ×î´óÐèÁ¿Êý¾ÝÇøÊ×µØÖ·  //
#define LEN_BLOCK70_EMU_PARAM_E2P   sizeof(ST_EMU_ADJ_PARAM)

//BLOCK81~84 ·ÑÂÊ±íÏà¹ØÊý¾ÝÇø  //
#if (TARIFF_MAX_NUM>1)
#define  No_BLOCK80_TRIFF_PARAM_E2P   80    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK80_TRIFF_PARAM_E2P   EE_DOUBLE_DATA_ADDR_START+ ST_MB_OFFSET(DBE2P_MAP,Triff_param)   //  3. µ±Ç°ÔÂ×î´óÐèÁ¿Êý¾ÝÇøÊ×µØÖ·  //
#define LEN_BLOCK80_TRIFF_PARAM_E2P   sizeof(E2P_TRIFF_PARAM_MAP)
#if(MAX_NUM_HOLIDAY_TAB>0)  
#define  No_BLOCK81_HILIDAY_TAB_E2P   81    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK81_HILIDAY_TAB_E2P   (ADR_BLOCK80_TRIFF_PARAM_E2P+OFFSET_HoliTab)
#define LEN_BLOCK81_HILIDAY_TAB_E2P    LEN_HoliTab
#endif
#define  No_BLOCK82_SEASON_TAB_E2P     82    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK82_SEASON_TAB_E2P   (ADR_BLOCK80_TRIFF_PARAM_E2P+OFFSET_SeasonTab)
#define LEN_BLOCK82_SEASON_TAB_E2P     LEN_SeasonTab

#define  No_BLOCK83_WEEK_TAB_E2P    83    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK83_WEEK_TAB_E2P   (ADR_BLOCK80_TRIFF_PARAM_E2P+OFFSET_WeekTab)
#define LEN_BLOCK83_WEEK_TAB_E2P      LEN_WeekTab

#define  No_BLOCK84_DAY_TAB_E2P    84    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
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
// ¸ººÉÇúÏßÔËÐÐ²ÎÊý//
#define ADR_METER_PARAM1_LOAD_PTR   (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,load_Ptr_var))
#define ADR_METER_PARAM1_LOAD_NUM   (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,load_Num_var))
// ¸ººÉ¼ÇÂ¼²ÎÊý//
#define ADR_METER_PARAM1_load_lptime_inv_var   (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,load_lptime_inv_var))
#define ADR_METER_PARAM1_load_egcode_var   (ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,load_egcode_var[0]))


////////////////////            BLOCK21  µç±í²ÎÊýÇø-ÏÔÊ¾²ÎÊýÇ  /////////////
#define ADR_DIS_PARAM_AUTO_SEC                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,auto_sec))  // ×Ô¶¯Ñ­»·ÏÔÊ¾³ÖÐøÊ±¼ä  //
#define ADR_DIS_PARAM_KEY_SEC                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,key_sec))  // °´¼üÏÔÊ¾³ÖÐøÊ±¼ä  //
#define ADR_DIS_PARAM_BG_SEC                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,bg_sec))   // ±³¹âµãÁÁ³ÖÐøÊ±¼ä  //
#define ADR_DIS_PARAM_EC_FORM                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,ec_form)) // µçÁ¿¸ñÊ½  //
#define ADR_DIS_PARAM_AUTO_TAB                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,auto_item))  //0ÎªÏÔÊ¾¸öÊý£¬1~31ÎªÏÔÊ¾ÏîÄ¿£¬×î´ó¿ÉÒÔÏÔÊ¾31¸öÏîÄ¿  //
#define ADR_DIS_PARAM_KEY_TAB                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,key_item))  //0ÎªÏÔÊ¾¸öÊý£¬1~31ÎªÏÔÊ¾ÏîÄ¿£¬×î´ó¿ÉÒÔÏÔÊ¾31¸öÏîÄ¿  //
#define ADR_DIS_PARAM_PWN_TAB                 (ADR_BLOCK21_DIS_PARAM_E2P+ST_MB_OFFSET(DIS_PARAM_DATA,pwn_item))  //0ÎªÏÔÊ¾¸öÊý£¬1~31ÎªÏÔÊ¾ÏîÄ¿£¬×î´ó¿ÉÒÔÏÔÊ¾31¸öÏîÄ¿  //

////////////////////////BLOCK 25     METER_VAR/////////////
#define ADR_METER_VAR_RTC                 (ADR_BLOCK25_METER_VAR_E2P+ST_MB_OFFSET(E2P_METER_VAR_MAP,save_rtc))

////////////////////////BLOCK 26     METER_VAR/////////////
#define ADR_BLOCK26_BILL_VAR_PTR_E2P   ADR_BLOCK26_BILL_VAR_E2P+OFFSET_bill_var_ptrNo
#define ADR_BLOCK26_BILL_VAR_DATETTIME_E2P   ADR_BLOCK26_BILL_VAR_E2P+OFFSET_bill_var_dateTime


///////////////////////////////////////////////////////////////////////////////////////////////////
//´øÐ£Ñéµ¥·ÝÊý¾ÝÇø////
//////////////////////////////////////////////////////////////
//BLOCK101~136 ÔÂ½áËãÊý¾ÝÇø  //
#if (BILL_MAX_NUM>0)
//BLOCK101  ÉÏ1ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK101_BILL1_DATA_E2P    101    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK101_BILL1_DATA_E2P   EE_SINGLE_DATA_ADDR_START   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //
#define LEN_BLOCK10X_BILLX_DATA_E2P   sizeof(E2P_BILL_DATA_MAP_ONE)

//BLOCK102 ÉÏ2ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK102_BILL2_DATA_E2P    102    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK102_BILL2_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[1])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //    

//BLOCK103  ÉÏ3ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK103_BILL3_DATA_E2P    103   // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK103_BILL3_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[2])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //
      

//BLOCK104  ÉÏ4ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK104_BILL4_DATA_E2P    104    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK104_BILL4_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[3])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //

//BLOCK105  ÉÏ5ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK105_BILL5_DATA_E2P    105    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK105_BILL5_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[4])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //

//BLOCK106  ÉÏ6ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK106_BILL6_DATA_E2P    106    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK106_BILL6_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[5])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //

//BLOCK107  ÉÏ7ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK107_BILL7_DATA_E2P    107    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK107_BILL7_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[6])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //

//BLOCK108  ÉÏ8ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK108_BILL8_DATA_E2P    108    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK108_BILL8_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[7])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //

//BLOCK109  ÉÏ9ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK109_BILL9_DATA_E2P    109    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK109_BILL9_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[8])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //

//BLOCK110  ÉÏ10ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK110_BILL10_DATA_E2P    110    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK110_BILL10_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[9])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //

//BLOCK111  ÉÏ11ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK111_BILL11_DATA_E2P    111   // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK111_BILL11_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[10])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //

//BLOCK112  ÉÏ12ÔÂ½áËãÊý¾ÝÇø  //
#define  No_BLOCK112_BILL12_DATA_E2P    112    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK112_BILL12_DATA_E2P   EE_SINGLE_DATA_ADDR_START +ST_MB_OFFSET(SGE2P_MAP,Bill_data[11])   //0. µ±Ç°ÓÐ¹¦µçÁ¿Êý¾ÝÇøÊ×µØÖ·  //
#endif


//BLOCK151  µç±íCLASSII ÀàÊÂ¼þÇø//
#define ADR_BLOCK150_EVENI_START_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_I)   //   2 ÀàÊÂ¼þ¼ÇÂ¼Êý¾ÝÇøÊ×µØÖ· //
#define  No_BLOCK150_EVENI_PROG_E2P  150    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK150_EVENI_PROG_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_I.prog)   //    //
#define  No_BLOCK151_EVENI_resetMD_E2P  151    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK151_EVENI_resetMD_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_I.resetMD)   //    //
#define  No_BLOCK152_EVENI_setRtc_E2P  152    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK152_EVENI_setRtc_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_I.setRtc)   //    //
//#define  No_BLOCK153_EVENI_powerDown_E2P  153    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
//#define ADR_BLOCK153_EVENI_powerDown_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_I.powerDown)   //    //
//#define LEN_BLOCK15X_EVENI_E2P               LEN_CLASS_I_UNIT
#define LEN_BLOCK15X_EVENI_E2P               LEN_CLASS_I_UNIT   // 
#define ADR_BLOCK_min_EVENI_E2P     ADR_BLOCK150_EVENI_PROG_E2P //     //
#define ADR_BLOCK_max_EVENI_E2P    ADR_BLOCK152_EVENI_setRtc_E2P  //    //

//¶þÀàÊý¾ÝÆðÊ¼


#define ADR_BLOCK160_EVENII_START_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,even_II)
#define  No_BLOCK161_EVENII_PWN_E2P  161    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK161_EVENII_PWN_E2P   ADR_BLOCK160_EVENII_START_E2P+ ST_MB_OFFSET(E2P_EVEN_II_DATA_MAP,PWN)   //    //

#define  No_BLOCK162_EVENII_lowbattery_E2P  162    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK162_EVENII_lowbattery_E2P   ADR_BLOCK160_EVENII_START_E2P+ ST_MB_OFFSET(E2P_EVEN_II_DATA_MAP,lowbattery)   //    //

#define  No_BLOCK163_EVENII_COVER_E2P  163    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define ADR_BLOCK163_EVENII_COVER_E2P   ADR_BLOCK160_EVENII_START_E2P+ ST_MB_OFFSET(E2P_EVEN_II_DATA_MAP,Cover)   //    //
#define  No_BLOCK164_EVENII_L1reverse_E2P  164   // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define  ADR_BLOCK164_EVENII_L1reverse_E2P   ADR_BLOCK160_EVENII_START_E2P+ ST_MB_OFFSET(E2P_EVEN_II_DATA_MAP,L1reverse)   //    //

#define LEN_BLOCK16X_EVENI_E2P            LEN_CLASS_II_UNIT   // 
#define ADR_BLOCK_min_EVENII_E2P     ADR_BLOCK161_EVENII_PWN_E2P //     //
#define ADR_BLOCK_max_EVENII_E2P    ADR_BLOCK164_EVENII_L1reverse_E2P  //    //




//¸ººÉÇúÏß180  µ¥·Ý  ²»Ð£Ñé//
#define  No_BLOCK180_LOAD_START_DATA   180    // Êý¾ÝÏîÄ¿Ë÷ÒýºÅ //
#define  ADR_BLOCK180_LOAD_START_E2P   EE_SINGLE_DATA_ADDR_START+ ST_MB_OFFSET(SGE2P_MAP,load_start_e2p)   //0x472  1138//

/***************************************************************
*    END
****************************************************************/

#endif
