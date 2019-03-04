/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_ADC_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: ADC模块的硬件驱动C代码的声明文件
**note			: V9811A ，
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#ifndef _Drv_ADC_H
#define _Drv_ADC_H

//******************************************************************
//              1     立即数预定义                                            
//                      
//******************************************************************
//M通道定义 //
#define M_ADC_CH1_TEMPERATURE  1    // 温度测量通道 //
#define M_ADC_CH2_VBAT                  2    // VBAT测量通道 //

//******************************************************************
//               2     数据结构声明                                                 //
//******************************************************************
typedef struct
{
    uint32 ul_TempParaA;      //系数A
    uint32 ul_TempParaB;      //系数B
    uint32 ul_TempParaC;      //系数C
    uint32 ul_TempParaD;      //系数D
    uint32 ul_TempParaE;      //系数E
    uint8  uc_Add33;          //和校验
}S_TEMPPARA;

//******************************************************************
//              3    变量声明                                                             //
//******************************************************************


//******************************************************************
//             4     函数声明                                                              //
//******************************************************************
extern void Enable_M_ADC(uint8  m_ch);
extern void Disable_M_ADC(void);
extern uint16  Samlpe_BatAdc(void);
extern int16  Samlpe_temperatureAdc(void);
extern float  Cal_temperature_data(void);



//******************************************************************
//             5     其他内容，例如伪指令等              //
//******************************************************************



/***************************************************************
*    END
****************************************************************/
#endif
