/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_EMU_hard.c
**Author		: maji
**date			: 2016-04-20 
**description	: V9811A��EMU����ģ��Ӳ���ײ�����C����
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>


/*******************************************************************************************
** ��������: SetMeterCfgACK
** ��������: ˫��ram���ã�ʹ��ACK�ź�
** �������: u32PMdatal ����
**                      : addr  ��ַ
** �������: FALSE ����ʧ�ܣ�TRUE ���óɹ�;
** ˵��    : 
*******************************************************************************************/
INT8U SetMeterCfgACK(unsigned long u32PMdatal ,unsigned int addr)
{
    unsigned char  index;
    index=0;
	
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    while(XBYTE[ACK])
     {
       index++;
	   if(index>CFGDELAY)
	   	{
		  return FALSE	;
	   	}
     }
   XBYTE[BUFF0]=(INT8U)(u32PMdatal&0xff);
   XBYTE[BUFF1]=(INT8U)((u32PMdatal>>8)&(0xff));
   XBYTE[BUFF2]=(INT8U)((u32PMdatal>>16)&(0xff));
   XBYTE[BUFF3]=(INT8U)((u32PMdatal>>24)&(0xff));
   XBYTE[addr]=0;//�������ĵ�ַд��0�������������뵽�����ĵ�ַ
  for(index=0;index<CFGDELAY;index++)
  	_nop_();
   index=0;
   while(XBYTE[ACK])
      {
	  index++;
	  if(index>CFGDELAY)
		 return FALSE	;
      }
    
  return TRUE;  
}


/*******************************************************************************************
** ��������: ReadMeterParaACK
** ��������: ˫��ram���ã�ʹ��ACK�ź�
** �������: u32PMdatal ����
**                      : addr  ��ַ
** �������: FALSE ����ʧ�ܣ�TRUE ���óɹ�;
** ˵��    : 
*******************************************************************************************/
uint32 ReadMeterParaACK(uint16 addr)
{
    uint8 data index;
    uint32  u32PMdatal,temp;

    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
        return FALSE;
        }
    }

    index=XBYTE[addr];//��ȡ��ʵ��ַ���������ݵ�����//
    for(index=0;index<CFGDELAY;index++)
    _nop_();
    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
        return FALSE;
        }
    }
    u32PMdatal=(INT32U)XBYTE[BUFF0];
    temp=(INT32U)XBYTE[BUFF1]<<8;
    u32PMdatal+= temp;
    temp=(INT32U)XBYTE[BUFF2];
    temp=temp<<16;
    u32PMdatal+=temp;
    temp=(INT32U)XBYTE[BUFF3];
    temp=temp<<24;
    u32PMdatal+=temp;
    return u32PMdatal;
	 
}


/*******************************************************************************************
**    END
*******************************************************************************************/
