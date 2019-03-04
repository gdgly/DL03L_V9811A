/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_RTC.c
**Author		: maji
**date			: 2016-04-20 
**description	: RTCģ���Ӳ������C����
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
** ��������: Open_SecOut
** ��������: �����������
** ��ڲ���: ��
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void Open_SecOut(void)
{
    P13FS = 0x05; // 1 hz PLL���������  // 
		
    P1OE&=~BIT3;	// output 
    P1IE&=~BIT3;	//
}

/*******************************************************************************************
** ��������: Close_SecOut
** ��������: �ر����������
** ��ڲ���: ��
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void Close_SecOut(void)
{
    P13FS = 0x00; //GPIO  //
    RTC_OUT_LOW() ;	
    P1OE&=~BIT3;	// output 
    P1IE&=~BIT3;	//
}

/*******************************************************************************************
** ��������: Init_RTC
** ��������: ��ʼ��RTC
** ��ڲ���: ��
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void Init_RTC(void)
{
	EIE|=BIT1;
	ExInt3IE|=BIT6;
}

/*******************************************************************************************
** ��������: SetExtRTC
** ��������: ����RTC�жϻ��Ѽ��
** ��ڲ���: uint8 SEC: intRTC=7��ʱ������SEC�뻽��
**                        uint8 intRTC :intRTC ����˵��: 0, 1 �룻1, 1 �֣�2, 1 Сʱ��3, 1 �죻4, 500 ���룻
**                                           5, 250 ���룻6, 125 ���룻7, ���SECINT�����������ж�
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void SetExtRTC(uint8 SEC,uint8 intRTC)
{
    //RTC����д 
    RTCPEN = 0x96;      //password 1
    RTCPWD = 0x57;      //password 2
    Lib_Delay_2us(50);    // 5 OSC //
	
    INTRTC = intRTC;
/////////////////////////////////////////
//�����������ж�  2016-2-18 mj//
    if(intRTC ==7)
    {
        SECINT = BIT6 ;
        SECINT += SEC&0x3f ;    
    }
/////////////////////////////////////////

    Lib_Delay_2us(50);    // 5 OSC //
    //RTC��ֹд  
    RTCPEN = 0x96;
    RTCPWD = 0x56;
    Lib_Delay_2us(50);    // 5 OSC //

}

/*******************************************************************************************
** ��������: Get_RTCTime
** ��������: ��ȡRTCʱ��
** �������: ��
** �������: �� 
** ˵��    :  //  0-�� 1-�� 2-ʱ 3-�� 4-�� 5-�� 6-�� //  
*******************************************************************************************/
void Get_RTCTime(RTC_TYPE *pTime)
{
volatile INT8U RTCFLAG ;

    RTCFLAG=RTCLATCH;     //����Ҫ����������������RTC���ݣ���֤�ڶ�ȡ�Ĺ����в��仯  //
    Lib_Delay_2us(50);    // 5 OSC //
    pTime->Week = RTCWC;             // weekday  // 
    pTime->Year = RTCYC;              // year  // 
    pTime->Month = RTCMoC;               // month  // 
    pTime->Day = RTCDC;               // day  // 
    pTime->Hour = RTCHC;              // hour  // 
    pTime->Minute = RTCMiC;              // minu  // 
    pTime->Second = RTCSC;              // sec  // 
}
	
/*******************************************************************************************
** ��������: Get_RTCTime
** ��������: ��ȡRTCʱ��
** �������: ��
** �������: �� 
** ˵��    : //  0-�� 1-�� 2-ʱ 3-�� 4-�� 5-�� 6-�� //  
*******************************************************************************************/
uint8 Set_RTCTime(RTC_TYPE *pTime)
{
	//RTC����д 
    RTCPEN = 0x96;      //password 1
    RTCPWD = 0x57;      //password 2
    Lib_Delay_2us(50);    // 5 OSC //
    //дRTCʱ��
    RTCWC = pTime->Week;		//weekday
    RTCYC = pTime->Year;		//year
    RTCMoC = pTime->Month;	//month
    RTCDC = pTime->Day;		//day
    RTCHC = pTime->Hour;		//hour
    RTCMiC = pTime->Minute;	//minu
    RTCSC = pTime->Second;		//sec
    Lib_Delay_2us(2);
    //RTC��ֹд  

    RTCPEN = 0x96;
    RTCPWD = 0x56;
    Lib_Delay_2us(50);    // 5 OSC //

    return (TRUE);
}



/*******************************************************************************************
** ��������: Clr_RTC_AdjParam
** ��������: ���RTC��У���Ĵ���
** �������: ��
** �������: �� 
** ˵��    :  ���²�����ı�Ҫ�����ϵ��ʼ��ʱ����ñ�����
*******************************************************************************************/
void Clr_RTC_AdjParam(void)
{
	//RTC����д 
    RTCPEN = 0x96;      //password 1
    RTCPWD = 0x57;      //password 2
    Lib_Delay_2us(50);    // 5 OSC //
	RTCCH = 0x00;
	RTCCL = 0x00;
    //RTC��ֹд  

    RTCPEN = 0x96;
    RTCPWD = 0x56;
    Lib_Delay_2us(50);    // 5 OSC //

}

/*******************************************************************************************
** ��������: SetRTCNormal
** ��������: У��RTCƵ��
** �������: int16 offset
** �������: �� 
** ˵��    : �²������е���
*******************************************************************************************/
void SetRTCNormal(int16 offset)
{
    ST_U32_U08 temp1,temp2;
    int16 temp3;

    temp2.u32=0;
    temp1.u32 =(uint16)offset;
    if((temp1.B08[2]>0x80))
    { 
        temp1.W16[1]=(~temp1.W16[1]);
        temp1.W16[1]&=0x1fff;
        temp1.u32=temp1.u32*20/30; 
        temp2.u32=(6553600/2) -1;
        temp2.u32=temp2.u32+(temp1.u32/2);
    }
    else
    {
        temp1.u32=(temp1.u32)*20/30;
        temp2.u32=(6553600/2);
        temp2.u32=temp2.u32-(temp1.u32/2);
    }

    temp3=offset/10;
    temp1.u32=(uint16)temp3;
    RTCPEN=0x96;              //          // 1S����//
    RTCPWD=0x57;
    Lib_Delay_2us(50);
    RTCCH=temp1.B08[2];
    RTCCL=temp1.B08[3];
    DIVTHH=temp2.B08[1];
    DIVTHM=temp2.B08[2];
    DIVTHL=temp2.B08[3];

    Lib_Delay_2us(50);
    RTCPEN=0x96;
    RTCPWD=0x56;
}


/*******************************************************************************************
** ��������: Handl_RTC_Adj_per_minu
** ��������: RTC�²����Ƴ���
** �������: ��
** �������: �� 
** ˵��    :  ���²�����ı�Ҫ�����ϵ��ʼ��ʱ����ñ�����
*******************************************************************************************/
float Handl_RTC_Adj_per_minu(void)
{
 uint8 i;  
 uint8 code *p;
 ST_U32_U08 temp1;
 float temperature; //��ǰ�¶�//

 int16 delta;
 int16  OSC;
 int32 Bpara;
 uint8 Ti;



    //���¶Ȳ������� //
    Enable_M_ADC(M_ADC_CH1_TEMPERATURE);
    Lib_Delay_ms(10);
        //��ȡ�¶� ���� //
    temperature = Cal_temperature_data();
    Disable_M_ADC();

#ifdef _RTC_CAL    //��Ҫ�²�����ʱִ���������� //
    Bpara = 0x061A80;
    Ti= 24;
    p=(uint8 code*)0x48C;		// RTC����ƫ��//

    for(i=0;i<3;i++)
    {
        Lib_FCpyTMem((uint8*)&temp1.B08[0],p+(i*4),4);	
        temp1.B08[2] = Lib_get_csck_int8u_num((uint8*)&temp1.B08[0],2,0x33);
        if(temp1.B08[2] == temp1.B08[3])
        {
            break;
        }
    }

    if(temp1.B08[2] != temp1.B08[3])
    {
        temp1.W16[0]= 0;		// У����� Ĭ��
    }
    delta=temp1.W16[0];


    //��������  //
    OSC=(int16)((((float)Bpara)*(temperature-((float)Ti))*(temperature-((float)Ti)))/1000000+delta);		// �����ṩ//
    //У׼����  //
    SetRTCNormal(OSC);
#endif

  return (temperature);

}



/*******************************************************************************************
**    END
*******************************************************************************************/
