/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_E2P_24CXXX_H.h
**Author		: maji
**date			: 2016-4-19
**description	: c code for read&Write 24CXXX
**note			:  Driver code for GENERAL
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-19   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#ifndef 	_Drv_E2P_24CXXX_H
#define	_Drv_E2P_24CXXX_H

//******************************************************************
//              1     ������Ԥ����                                            //                      
//******************************************************************
// ���������ֶ��� //
#define     WRITE_EEPROM_CMD              0xA0
#define     READ_EEPROM_CMD               WRITE_EEPROM_CMD+1

//�������Ͷ���  //
#define _E2P_TYPE_AT24               // ��ͨE2Pʱ���壬��������ʱ��ע�͵� //

//E2P ���Ͷ��� //
#define EE24XX32        0
#define EE24XX64        1
#define EE24XX128       2
#define EE24XX256       3
#define EE24XX512       4
#define EE24XX08        5
#define EE24XX16        6


#define EE_Chip         EE24XX512           //EEPROM chip(EE24XX08/EE24XX16/EE24XX32/EE24XX64/EE24XX128/EE24XX256/EE24XX512)
#if (EE_Chip == EE24XX08)
    #define EE_Capacity     0x03ffU         //ĩβ��ַ
    #define EE_PageMask     0x10U           //16Bytes,ҳ��С0~0f
#elif (EE_Chip == EE24XX16)
    #define EE_Capacity     0x07ffU         //ĩβ��ַ
    #define EE_PageMask     0x10U           //16Bytes,ҳ��С0~0f
#elif (EE_Chip == EE24XX32)
    #define EE_Capacity     0x0fffU         //ĩβ��ַ
    #define EE_PageMask     0x20U           //32Bytes,ҳ��С0~1f
#elif   (EE_Chip == EE24XX64)
    #define EE_Capacity     0x1fffU         //ĩβ��ַ
    #define EE_PageMask     0x20U           //32Bytes,ҳ��С0~1f
#elif   (EE_Chip == EE24XX128)
    #define EE_Capacity     0x3fffU         //ĩβ��ַ
    #define EE_PageMask     0x40U           //64Bytes,ҳ��С0~3f
#elif   (EE_Chip == EE24XX256)
    #define EE_Capacity     0x7fffU         //ĩβ��ַ
    #define EE_PageMask     0x40U           //64Bytes,ҳ��С0~3f
#elif   (EE_Chip == EE24XX512)
    #define EE_Capacity     0xffffU         //ĩβ��ַ
    #define EE_PageMask     0x80U           //128Bytes,ҳ��С0~7f
#else
    #error "Unrecognized EEPROM Chip!"
#endif

//******************************************************************
//               2     ���ݽṹ����                                                 //
//******************************************************************


//******************************************************************
//              3    ��������                                                             //
//******************************************************************


//******************************************************************
//             4     ��������                                                              //
//******************************************************************
extern uint8 Read_EEPROM_Page_Sub(uint8 *Buf,uint16 Addr,uint8 Len);
extern uint8 Write_EEPROM_Page_Sub(uint16 Addr,uint8 *Buf,uint8 Len);
extern uint8 Read_EEPROM_Page(uint8* u8p_dst, uint16 u16_src, uint8 u8_len);
extern uint8 Write_EEPROM_Page(uint16 u16_dst, uint8 *u8p_src, uint8 u8_len);
extern uint8  Write_EEPROM(uint16 u16_dst, uint8 *u8p_src, uint16 u16_len);
extern uint8 Read_EEPROM(uint8* u8p_dst, uint16 u16_src, uint16 u16_len);

//******************************************************************
//             5     �������ݣ�����αָ���              //
//******************************************************************
#define     Disable_WP()                  NOP()
#define     Enable_WP()                   NOP()


/***************************************************************
*    END
****************************************************************/

#endif