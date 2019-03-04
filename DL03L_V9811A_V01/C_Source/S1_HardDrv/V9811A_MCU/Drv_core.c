/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_core.c
**Author		: maji
**date			: 2016-04-20 
**description	: MCU core�ں�ģ���Ӳ������C����
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
** ��������: Set_McuClock
** ��������:  MCU��Ƶ����
** �������: osc :   FSYSCLK_800k    FSYSCLK_1M6 
**                         PHZ :  50 0r  60 HZ
** ˵��    : 
*******************************************************************************************/
uint8 Set_McuClock(uint32 u32_freq )
{
    uint8 i=0;

    FWC=0;
    FSC=0;
    CtrlCLK|=(BIT6+BIT7); // ����BGP �Լ�PLL��·//
#if (C_Fq == 60)
    CtrlPLL = BIT5;
#else
    CtrlPLL = 0; 
#endif           

    switch(u32_freq)
    {
        case FSYSCLK_800k:
            CtrlCLK&=~(BIT0+BIT1);   // 00Ϊ 1x FSYSCLK_800k
            CtrlPLL =0;     //BIT5 =0 Ϊ50HZ
            break;

        case FSYSCLK_1M6:
            CtrlCLK |= BIT0;
            CtrlCLK&=~(BIT1);   // 10Ϊ 2x FSYSCLK_800k
            CtrlPLL =0;     //BIT5 =0 Ϊ50HZ
            break;

        case FSYSCLK_3M2:
            CtrlCLK&=~(BIT0);   // 10 Ϊ 4x FSYSCLK_800k
            CtrlCLK |= BIT1;
            break;

        case FSYSCLK_6M5:
            CtrlCLK |= BIT0;   // 11 Ϊ  8x FSYSCLK_800k
            CtrlCLK |= BIT1;
            break;

        case FSYSCLK_13M:
            CtrlCLK |= BIT0;     // 11 Ϊ  8x FSYSCLK_800k
            CtrlCLK |= BIT1;
            CtrlPLL |=BIT6;              // mcuclock x 2
            break;

        case FSYSCLK_26M:
            CtrlCLK |= BIT0;     // 11 Ϊ  8x FSYSCLK_800k
            CtrlCLK |= BIT1;
            CtrlPLL |=(BIT7+BIT6);       //  mcuclock x 4 
            break;

        default:
            sys_err();	
        break;
    }

    while(!(PLLLCK&BIT0))
    {
        i++;
        if(i>50)
        {
            return FALSE;       //��һ��ʱ����û������
        }
    }
    MCUFRQ=1; //MCUʱ��Դ: PLLʱ��
    i=0;

    while(!(MCUFRQ))
    {
        i++;
        if(i>50)
        {
            return FALSE;       //��һ��ʱ����û������
        }
    }

    CtrlCry0=0;                 //����������
    CryCtrl1=3;                // ʹ��RTC   
    CryCtrl2|=BIT5;        // ͣ��λ����//

    return TRUE;
}

/*******************************************************************************************
** ��������: Set_EmuClock
** ��������: ����ʱ������
** �������: Tpye:   EMUCLK_OFF �ؼ���
                              EMUCLK_800k  ʱ��ѡ��
**                         
** ˵��    : ע��EMU����Ƶ������ADC��Ƶ��4����8��
*******************************************************************************************/
uint8 Set_EmuClock(uint32 u32_freq)
{
    uint8 i=0;

    PMG = 0;
    CtrlCLK|=(BIT6+BIT7); // ����BGP �Լ�PLL��·//
 
    switch(u32_freq)
    {
        case EMUCLK_OFF:
            PMG = 1;
            return TRUE;

        case EMUCLK_800k:
            CtrlCLK&=~(BIT3+BIT2);   // 00Ϊ  1*EMUCLK_800k
            CtrlCLK&=~(BIT5+BIT4);   // 00Ϊ  1*ADCCLK_204k
            break;

        case EMUCLK_1M6:
            CtrlCLK |= BIT2;
            CtrlCLK&=~(BIT3);   // 01 Ϊ 2x EMUCLK_800k

        	CtrlCLK |= BIT4;
        	CtrlCLK&=~(BIT5);   // 01 Ϊ 2x ADCCLK_204k
            break;
	
        case  EMUCLK_3M2:
            CtrlCLK&=~(BIT2);   // 10 Ϊ 4x EMUCLK_800k
            CtrlCLK |= BIT3;

            CtrlCLK&=~(BIT4);   // 10 Ϊ 4x ADCCLK_204k
            CtrlCLK |= BIT5;
            break;

        default:
            sys_err();	
        break;
   }

    while(!(PLLLCK&BIT0))
    {
        i++;
        if(i>50)
        {
            return FALSE;       //��һ��ʱ����û������
        }
    }

    MEAFRQ=1;   //MEAʱ��Դ: PLLʱ��
    i=0;
    while(!(MEAFRQ))
    {
        i++;
        if(i>50)
        {
            return FALSE;       //��һ��ʱ����û������
        }
    }
	
    return TRUE;
}

/*******************************************************************************************
** ��������: Set_McuSleep
** ��������: ϵͳ���ߴ���
** �������: NONE
** �������: ��
** ˵��    : 
*******************************************************************************************/
void Set_McuSleep(void)
{
    uint8 i;
    FWC=0;
    FSC=0;

    CtrlADC6=0;             //�ر����е�ADC
    CtrlLDO = 0x00;

   for(i=0;i<20;i++);      //�ȴ�
    PMG=1;                  //�رռ���ʱ��

    if((Systate&BIT0)==0x01)
    {   
        sys_err();	  //����ϵ������ߴ��� //
    }

    MCUFRQ=0;
    while(MCUFRQ);

    if((Systate&BIT0)==0x01)
    {   
        sys_err();	  //����ϵ������ߴ��� //
    }

    for(i=0;i<3;i++);       //�ȴ�//
    CtrlCLK=0x00;
    while(CtrlCLK);

    SLEEP0 = 1;
    Lib_Delay_2us(10);    // 5 OSC //
}


/*******************************************************************************************
** ��������: Set_Mcu_core
** ��������: ϵͳ�ں˲�������
** �������: NONE
** �������: ��
** ˵��    : 
*******************************************************************************************/
void Set_Mcu_core(void)
{
     CtrlBGP = BIT2;    //������Ӱ��RTC�²�У׼�͸ߵ��µļ������  //
}

/*******************************************************************************************
**    END
*******************************************************************************************/
