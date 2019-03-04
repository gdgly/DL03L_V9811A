/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Lcd_Display_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: 液晶显示处理应用层相关函数程序H文件
**note			: V9811A ，MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#ifndef _Api_Lcd_Display_H
#define _Api_Lcd_Display_H


/***************************************************************
*    1     立即数预定义   
****************************************************************/
//DIS_PIXEL_VAR 部分BUFF下标定义//
#define DS_UNIT			21 	//共18 个显示单元//
#define DS_DATANum		8  //大数字个数//
#define DS_OBISNum		4  //OBIS个数//
#define DS_CHARNum		3  //其他字符个数//

//  //
#define DIS_RESET 	  0   //全屏自检显示  //
#define DIS_DEFAULT_ITEM 	  1   //默认显示当前总有功电量项目  //
#define RESEAT_DIS_KEEP_3S   4	//刚上的复位全屏显示保持时间//
#define DIS_MAX_ITEM   40    // 最大显示序号41  //

// 硬件校表显示项目 //
#define DIS_ADJ_CH1_0 	  0XA0   //L 回路校表参数初始化 //
#define DIS_ADJ_CH1_1 	  0XA1  //L 回路1.0Ib 比差校准 //
#define DIS_ADJ_CH1_2 	  0XA2   //L 回路1.0Ib 0.5L 角差校准 //
#define DIS_ADJ_CH1_3 	  0XA3   //L 回路0.05Ib 小信号补偿校准 //
#define DIS_ADJ_CH2_0 	  0XA4   //N 回路校表参数初始化 //
#define DIS_ADJ_CH2_1 	  0XA5  //N 回路1.0Ib 比差校准 //
#define DIS_ADJ_CH2_2 	  0XA6   //N回路1.0Ib 0.5L 角差校准 //
#define DIS_ADJ_CH2_3 	  0XA7   //N回路0.05Ib 小信号补偿校准 //
#define DIS_DATA_CLR 	  0XA8   //电表清零 //


//DIS_CTL_VAR.mode define //
#define DIS_MODE_RESET	  0x01    //
#define DIS_MODE_NOMAL  0x02  	//
#define DIS_MODE_MAN      0x03   //
#define DIS_MODE_SLEEP   0x04   //下电 按键唤醒显示     //
#define DIS_MODE_OFF      0x5   //下电 关闭显示   //


//LCDDISTAB 定义//
//LCDDISTAB.chartype define //
#define CHAR_AEC		0x01		// 电量类
#define CHAR_MD			0x02		// 需量类
#define CHAR_MD_TIME	0x03		// 需量发生时间
#define CHAR_V			0x04		// 电压类
#define CHAR_A			0x05		// 电流类
#define CHAR_KW		0x06		// 功率类
#define CHAR_HZ			0x07		// 频率类
#define CHAR_TIME		0x08		// 时间类
#define CHAR_DATE		0x09		// 日期类
#define CHAR_PF			0x0A		// 功率因数类
#define CHAR_SETTL		0x0B		// 结算参数类
//LCDDISTAB.obis_digit define //
#define  OBIS_DIGIT_TYPE0  0  // no digit
#define  OBIS_DIGIT_TYPE1  1  // x.x.x
#define  OBIS_DIGIT_TYPE2  2  // x.x.x.x  or x.x.x.xx
#define  OBIS_DIGIT_TYPE3  3  // xx.x.x
#define  OBIS_DIGIT_TYPE4  4  // x.xx.x

/***************************************************************
*    2     数据结构声明     
****************************************************************/
//显示参数表区 //
typedef struct 
{
    uint8  auto_sec;    // 自动循环显示持续时间  //
    uint8  key_sec;     // 按键显示持续时间  //
    uint8  bg_sec;     // 背光点亮持续时间  //
    uint8  ec_form;     // 电量格式  //
    uint8  auto_item[11];    //自动循环显示项目，0为显示个数，1~10为显示项目，最大可以显示10个项目  //
    uint8  key_item[11];    //按键显示项目，0为显示个数，1~10为显示项目，最大可以显示10个项目  //
    uint8  pwn_item[10];    //下电显示项目，1~10为显示项目，最大可以显示10个项目  //
    INT16U  u16_csck;    //16位累加和校验值//
} DIS_PARAM_DATA;

//显示控制变量区 //
typedef struct 
{
    uint8  mode;    // 显示模式 //
    uint8  item;      // 当前显示项目  //
    uint8  ptr[4];    //各种显示模式的项目指针，0序号常规显示模式 1序号为上电按键显示，2序号为下电按键显示 //
    uint8  keep_sec[4];  // 显示类持续时间, 0序号为自动循环显示,1序号为按键显示保持时间2为背光维持时间3为上电自检显示尺寸时间//
    uint8  cnt_10ms_dis_key_delay;    //显示按键10ms延时滤波  //
} DIS_CTL_VAR;

//显示元素变量区 //
typedef struct 
{
    uint8  dis_buff[DS_UNIT];    // 显示模式 //
    uint8  dis_data_buff[DS_DATANum];				// data区8 位数据显示转换数据 //
    uint8  dis_obis_buff[DS_OBISNum];				// OBIS 区 4 位数据显示转换数据 //
    uint8  dis_char_buff[DS_CHARNum];				// 组合CHAR区24个符号显示转换数据 //
} DIS_PIXEL_VAR;


//显示像素表结构定义
typedef struct  
{
    INT8U      DisID;               //显示ID//
    INT16U     ObisNum;         // OBIS数据,简化为4个数字//
    INT16U     Addr;                //ram或 E2 地址//
    INT16U     DisInfo ;            // 存储类型(H)+ 显示位数(L) // 
    INT8U      chartype;            // 数据类型 //        
    INT8U      obis_digit;           //OBIS小数格式类型//
}LCDDISTAB;

/***************************************************************
*    3    变量声明       
****************************************************************/
extern DIS_PARAM_DATA   gs_dis_param;   // 电量显示相关参数  //
extern DIS_CTL_VAR  gs_dis_ctl_var;
extern DIS_PIXEL_VAR  gs_dis_pixel_var;
extern LCDDISTAB   gs_LCDDISTAB_var;

extern const DIS_PARAM_DATA  code default_dis_param_tab;

/***************************************************************
*    4     函数声明        
****************************************************************/
extern void api_init_display(void);
extern void api_handl_dis_key_10ms(void);
extern void api_handl_dis_sleep(void);  
extern void api_handl_dis_sleep_key(void);
extern void api_updated_LCDDisplayPixel_per_second(void);
extern void api_updated_BG_per_second(void);
extern void api_updated_LCDDisplayItem_per_second(void);
extern INT8U api_get_next_dis_item(void);
extern INT8U Link_Get_DisTab_Var(INT8U u8_dis_itm);
extern void Link_Get_Dis_OBIS_Num_buff(void);
extern void Link_Get_Dis_Data_Num_buff(void);
extern void Link_Get_Dis_Char_buff(void);
extern void Link_Get_Dis_RealChar_buff(void);
extern void Link_Get_Dis_Drv_buff(void);
extern void api_get_energy_LCD(uint8*  temp, uint8 type, uint8*  result);

extern void api_chg_LCDDisplay_adj_item(uint8 u8_item);
extern void api_LCDDisplay_adj_item(uint8 u8_item);

/***************************************************************
*    5     其他内容，例如伪指令等       
****************************************************************/
//********************************************************************
// 上排数字1~8的字段数据的液晶字符定义SEG0~SEG16
// LCD character bitmap
//  char:   b  g  c  dp  a  f  e  d        
//  val:    7  6  5  4   3  2  1  0
// LCD character bitmap
//          3                a
//       -----            -----
//       |     |          |     |
//      2|     |7        f|     |b
//       |  6  |          |  g  |
//        -----            -----
//       |     |          |     |
//      1|     |5        e|     |c
//       |  0  |          |  d  |
//        -----  *4        -----  *dpc
//******************************************************************* 
//********************************************************************
// 常规数据区
//*******************************************************************                   								
#define DS_Chr_0     0xAF   // 0: 
#define DS_Chr_1     0xA0   // 1:
#define DS_Chr_2     0xCB   // 2: 
#define DS_Chr_3     0xE9   // 3: 
#define DS_Chr_4     0xE4   // 4: 
#define DS_Chr_5     0x6D   // 5: 
#define DS_Chr_6     0x6F   // 6: 
#define DS_Chr_7     0xA8   // 7: 
#define DS_Chr_8     0xEF   // 8: 
#define DS_Chr_9     0xED   // 9: 
#define DS_Chr_A     0xEE   // A: 
#define DS_Chr_b     0x67   // B: 
#define DS_Chr_C     0x0F   // C: 
#define DS_Chr_d     0xE3   // D: 
#define DS_Chr_E     0x4F   // E: 
#define DS_Chr_F     0x4E   // F: 

//********************************************************************
// 下排OBIS   前3 位数字 
//*******************************************************************                 								
#define DS_OBIS_Chr_0     0x7B   // 0: 
#define DS_OBIS_Chr_1     0x28   // 1:
#define DS_OBIS_Chr_2     0x5E   // 2: 
#define DS_OBIS_Chr_3     0x6E   // 3: 
#define DS_OBIS_Chr_4     0x2D   // 4: 
#define DS_OBIS_Chr_5     0x67   // 5: 
#define DS_OBIS_Chr_6     0x77   // 6: 
#define DS_OBIS_Chr_7     0x2A   // 7: 
#define DS_OBIS_Chr_8     0x7F   // 8: 
#define DS_OBIS_Chr_9     0x6F   // 9: 
#define DS_OBIS_Chr_A     0x3F   // A: 
#define DS_OBIS_Chr_b     0x75   // B: 
#define DS_OBIS_Chr_C     0x53   // C: 
#define DS_OBIS_Chr_d     0x7C   // D: 
#define DS_OBIS_Chr_E     0x57   // E: 
#define DS_OBIS_Chr_F     0x17   // F: 

//********************************************************************
// 下排OBIS  最后一 位数字 8
//*******************************************************************                 								
#define DS_OBIS1_Chr_0     0xDB   // 0: 
#define DS_OBIS1_Chr_1     0x88   // 1:
#define DS_OBIS1_Chr_2     0x5E   // 2: 
#define DS_OBIS1_Chr_3     0x9E   // 3: 
#define DS_OBIS1_Chr_4     0x8D   // 4: 
#define DS_OBIS1_Chr_5     0x97   // 5: 
#define DS_OBIS1_Chr_6     0xD7   // 6: 
#define DS_OBIS1_Chr_7     0x8A   // 7: 
#define DS_OBIS1_Chr_8     0xDF   // 8: 
#define DS_OBIS1_Chr_9     0x9F   // 9: 
#define DS_OBIS1_Chr_A     0xCF   // A: 
#define DS_OBIS1_Chr_b     0xD5   // B: 
#define DS_OBIS1_Chr_C     0x53   // C: 
#define DS_OBIS1_Chr_d     0xDC   // D: 
#define DS_OBIS1_Chr_E     0x57   // E: 
#define DS_OBIS1_Chr_F    0x47   // F: 


#define DS_Chr_All_NUM 16   


//dis_var.dis_char_buff[0]  bit7:bit0      //
#define CHAR_OBIS_P1 	BIT0  //s7
#define CHAR_OBIS_P2 	BIT1   //s8
#define CHAR_OBIS_P3 	BIT2   //s9
#define CHAR_TOTAL     	BIT3   //s22
#define CHAR_TARIFF 	BIT4   //s23
#define CHAR_TARIFF1 	BIT5  //S24
#define CHAR_DATA_P7 	BIT6  //s1
#define CHAR_DATA_P8 	BIT7  //s2
//dis_var.dis_char_buff[1]  bit7:bit0      //
#define CHAR_DATA_P9 	BIT0   //s3
#define CHAR_DATA_P10 	BIT1   //S5
#define CHAR_DATA_P11 	BIT2   //S4
#define CHAR_DATA_P12 	BIT3  //S6
#define CHAR_CHR_MD 	BIT4 //s21
#define CHAR_TARIFF2 	BIT5   //s25
#define CHAR_UNIT_K 	BIT6       //s30
#define CHAR_UNIT_V 	BIT7        //S31
//dis_var.dis_char_buff[2]  bit7:bit0      //
#define CHAR_UNIT_V2_1 	BIT0		//S32
#define CHAR_UNIT_V2_2 	BIT1		//S33
#define CHAR_UNIT_A_1 	BIT2		 //S34 
#define CHAR_TARIFF3 	BIT3	 //S26	 
#define CHAR_UNIT_A_3	BIT4	         //36	 
#define CHAR_TARIFF4 	BIT5     // 27
#define CHAR_UNIT_H 	BIT6   //s38
#define CHAR_UNIT_Z		BIT7  //S29

 		




/***************************************************************
*    END
****************************************************************/

#endif

