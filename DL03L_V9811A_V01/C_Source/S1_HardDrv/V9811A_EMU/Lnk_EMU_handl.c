/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Lnk_EMU_handl.c
**Author		: maji
**date			: 2016-04-20 
**description	: V9811A��EMU����ģ����·�㴦��C����
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>




EMU_RUN_VAR   gs_emu_run_var;

/*********************************************************************************************************
** ��������: Init_EMU
** ��������: ��ʼ��EMU
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void Init_EMU_RAM(void)
{
    Get_EMU_AdjParam();
}


/*********************************************************************************************************
** ��������: EMU_Verify
** ��������: EMU�Ĵ���У��
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void check_EMU_per_second(void)
{
   ST_U32_U08 regval;

    // ADC ���ü��  //
    if(gs_sys_globaL_var.work_mode==NORMAL_MODE)
    {
        if((CtrlADC6&(ADCAPDN+ADCBPDN+ADCUPDN)) != (ADCAPDN+ADCBPDN+ADCUPDN))
        {
            ADCOPEN(ADCAPDN+ADCBPDN+ADCUPDN);//OPEN ADC U A B
            SetMeterCfgACK(0X889374BC,PARABPF);    // �ֲ�Ҫ�� //
        }
    }
    if((gs_sys_globaL_var.work_mode ==DLX_MODE)||(gs_sys_globaL_var.work_mode ==CONST_MODE))
    {
        if((CtrlADC6&(ADCAPDN+ADCBPDN+ADCUPDN)) != (ADCAPDN+ADCBPDN))
        {
            ADCOPEN(ADCAPDN+ADCBPDN);//OPEN ADC  A B
            SetMeterCfgACK(0X911D3C9C,PARABPF);    // �ֲ�Ҫ�� // 
        }
    }

    if((CtrlADC0&(ADCA16X+ADCB4X+ADCU2X)) != (ADCA16X+ADCB4X+ADCU2X))
    {
        CtrlADC0=(ADCA16X+ADCB4X+ADCU2X); //ADC A 16X GAIN  ADC B 4x GAIN ADC U 4X GAIN	
    }

   // PMCtrl x ���   //
    regval.u32 = 0;
    regval.u32 = ReadMeterParaACK(PMCtrl1);
    if((regval.u32&0x000000ff) != 0x57)
    {
        SetMeterCfgACK(0x57,PMCtrl1);
    }

    regval.u32 = 0;
    regval.u32 = ReadMeterParaACK(PMCtrl2);
    if((regval.u32&0x000000ff) != 0x00)
    {
        SetMeterCfgACK(0x00,PMCtrl2);
    }

    regval.u32 = 0;
    regval.u32 = ReadMeterParaACK(PMCtrl3);
    if((regval.u32&0x000000ff) != 0x70)
    {
        SetMeterCfgACK(0x70,PMCtrl3);
    }

    regval.u32 = 0;
    regval.u32 = ReadMeterParaACK(PMCtrl4);
    if((regval.u32&0x000000ff) != 0xDA)
    {
        SetMeterCfgACK(0xDA,PMCtrl4);
    }

    //EMU�����������鴦��  //
    Check_EMU_AdjParam();
}


/*********************************************************************************************************
** ��������: Init_EMU
** ��������: ��ʼ��EMU
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void Init_EMU(uint8 u8_mode)
{
    if(u8_mode==SLEEP_MODE)
    {
        CtrlADC5=0X80;     //�ر�Mͨ�� //
        CtrlADC6=0;         //�ر�����AD���� //  
        PMG=1;              //�رռ���ʱ��  //
        return;
    }

    PMG=0;              //�򿪼���ʱ��  //
    //step1  //
    SetMeterCfgACK(0x00,PMCtrl4);   //�ر������ۼӡ�CF ����Լ���/Ǳ���жϵ�· //
    SetMeterCfgACK(0x00,PMCtrl1);   // �رռ���ͨ������ֹͣ����/��Чֵ����  //
    // step2  //
    CtrlADC5=0X80;   
    CtrlADC6=0;   
    if(u8_mode==NORMAL_MODE)
    {
        Set_EmuClock(EMUCLK_3M2);          // 3.2M ������Ƶ //
        ADCOPEN(ADCAPDN+ADCBPDN+ADCUPDN);//OPEN ADC U A B
        SetMeterCfgACK(0X889374BC,PARABPF);    // �ֲ�Ҫ�� //
    }
    else if((u8_mode ==DLX_MODE)||(u8_mode ==CONST_MODE))
    {
        Set_EmuClock(EMUCLK_800k);       // 800K������Ƶ //
        ADCOPEN(ADCAPDN+ADCBPDN);//OPEN ADC  A B
        SetMeterCfgACK(0X911D3C9C,PARABPF);    // �ֲ�Ҫ�� // 
    }
    else
    {
        sys_err();          // ��������쳣����ѭ���˳� //
    }
    CtrlADC0=(ADCA16X+ADCB4X+ADCU2X); //ADC A 4X GAIN  ADC B 4x GAIN ADC U 1X GAIN	

    // step3  //   
    SetMeterCfgACK(INITGATEP,GATEP);//���ü�����ʼֵ
    SetMeterCfgACK(INITGATEQ,GATEQ);

    // step4 // 
    SetMeterCfgACK(0,0x10f0);    //0x10f0  PPCNT  ���� E1 �����ۼӼĴ���  //
    SetMeterCfgACK(0,0x10f1);    //0x10f1  NPCNT  ���� E1 �����ۼӼĴ��� //
    SetMeterCfgACK(0,0x10f2);    //0x10f2  PPCFCNT  ���� E1 �������������   //
    SetMeterCfgACK(0,0x10f3);   //0x10f3  NPCFCNT  ���� E1 �������������   //
    SetMeterCfgACK(0,0x10f6);   //0x10f6  PQCNT  ���� E2 �����ۼӼĴ���//
    SetMeterCfgACK(0,0x10f7);   //0x10f7  NQCNT  ���� E2 �����ۼӼĴ���   //
    SetMeterCfgACK(0,0x10f8);   //0x10f8  PQCFCNT   ���� E2 �������������  //
    SetMeterCfgACK(0,0x10f9);   //0x10f9 NQCFCNT   ���� E2 �������������  //
    // step5// 
    SetMeterCfgACK(0xC8,PMCtrl4);		//  ?????  //
    SetMeterCfgACK(0x08,PMCtrl4);
    SetMeterCfgACK(0x00,PMCtrl4);
    // step6 // 
    SetMeterCfgACK(0,0x10f0);    //0x10f0  PPCNT  ���� E1 �����ۼӼĴ���  //
    SetMeterCfgACK(0,0x10f1);    //0x10f1  NPCNT  ���� E1 �����ۼӼĴ��� //
    SetMeterCfgACK(0,0x10f2);    //0x10f2  PPCFCNT  ���� E1 �������������   //
    SetMeterCfgACK(0,0x10f3);   //0x10f3  NPCFCNT  ���� E1 �������������   //
    SetMeterCfgACK(0,0x10f6);   //0x10f6  PQCNT  ���� E2 �����ۼӼĴ���//
    SetMeterCfgACK(0,0x10f7);   //0x10f7  NQCNT  ���� E2 �����ۼӼĴ���   //
    SetMeterCfgACK(0,0x10f8);   //0x10f8  PQCFCNT   ���� E2 �������������  //
    SetMeterCfgACK(0,0x10f9);   //0x10f9 NQCFCNT   ���� E2 �������������  //
    // step7// 
    SetMeterCfgACK(0x01,GATECP);//Ǳ��1   ,=1���ֹ���巢��    //
    SetMeterCfgACK(0x01,GATECQ);//Ǳ��2   ,=1���ֹ���巢��  //
    SetMeterCfgACK(0x00,DATACP);//�峣�����ʼĴ��� //

    // step8// 
    SetMeterCfgACK(0x57,PMCtrl1);//BIT7= 0  ����λȷ��Ϊ0  ; BIT6=1 ʹ�ܽǲ�У��  //
                                                  //BIT5= 0  IA--I1,IB--I2 ; BIT4=1 ʹ��PM�����źŴ���  //
                                                  //BIT3= 0  ����Mͨ�������ź�����; BIT2=1 ʹ��I2�����ź�����ʹ��  //
                                                  //BIT1= 1   ʹ��I1�����ź�����ʹ��; BIT0=1 ʹ��U�����ź�����ʹ��  //
    SetMeterCfgACK(0x00,PMCtrl2);// ����������Ĳ����Ĵ�����Ҫ��Ϊ0  //

    SetMeterCfgACK(0x70,PMCtrl3);//������·�й�,��ͨ�͵�ͨ�˲�����Ч //
    SetMeterCfgACK(0xD2,PMCtrl4);//BIT7= 1  E2 ����ͨ����/Ǳ���ж�ʹ��  ; BIT6=1  E2 ����ͨ����/Ǳ���ж�ʹ��  //
                                                  //BIT5= 0 E2 ���� CF ��������ر�; BIT4=1 ʹ��E1 ���� CF ������� //
                                                  //BIT3= 0 ��ֹ�����ۼӺ������������; BIT2=0  E1 ���� CF ��������� CF1 �����E2 ���� CF ��������� CF2 ���  //
                                                  //BIT1:0= 10 �������� //
    SetMeterCfgACK(0,0x10f0);    //0x10f0  PPCNT  ���� E1 �����ۼӼĴ���  //
    SetMeterCfgACK(0,0x10f1);    //0x10f1  NPCNT  ���� E1 �����ۼӼĴ��� //
    SetMeterCfgACK(0,0x10f2);    //0x10f2  PPCFCNT  ���� E1 �������������   //
    SetMeterCfgACK(0,0x10f3);   //0x10f3  NPCFCNT  ���� E1 �������������   //
    SetMeterCfgACK(0,0x10f6);   //0x10f6  PQCNT  ���� E2 �����ۼӼĴ���//
    SetMeterCfgACK(0,0x10f7);   //0x10f7  NQCNT  ���� E2 �����ۼӼĴ���   //
    SetMeterCfgACK(0,0x10f8);   //0x10f8  PQCFCNT   ���� E2 �������������  //
    SetMeterCfgACK(0,0x10f9);   //0x10f9 NQCFCNT   ���� E2 �������������  //
    // step9 // 
    SetMeterCfgACK(0xDA,PMCtrl4);//BIT7= 1  E2 ����ͨ����/Ǳ���ж�ʹ��  ; BIT6=1  E2 ����ͨ����/Ǳ���ж�ʹ��  //
                                                  //BIT5= 0 E2 ���� CF ��������ر�; BIT4=1 ʹ��E1 ���� CF ������� //
                                                  //BIT3= 1 ʹ�������ۼӺ������������; BIT2=0  E1 ���� CF ��������� CF1 �����E2 ���� CF ��������� CF2 ���  //
                                                  //BIT1:0= 10 �������� //
     // step10 // 
    SetMeterCfgACK(0,PHCCtrl1);//��0
    SetMeterCfgACK(0,PHCCtrl2);//��0

    SetMeterCfgACK(0x01,CFCtrl);           //��E1��������Ϊ���ݲ���CF	//

     // step11// 
    SetMeterCfgACK(0x00,DATACP);//�峣�����ʼĴ��� //

    // STEP 12 ��CF����  //
    CFLED_INITLIZE();
    EIE|=0x01;
    ExInt2IE|=BIT7;     // ����CF�ж� //

    gs_emu_run_var.delay_emu = 2;   // ��ʼ������ȶ�ʱ��Ϊ2�� //
}


/*******************************************************************************************
** ��������: Lnk_get_EMU_voltage
** ��������: ��ȡָ��ͨ����ѹ 
** �������: ch: ͨ�����0�������
** �������: uint32 ָ��ͨ����ѹֵ��HEX��,����Ϊ0.01V
** ˵��    : У��ϵ��Ϊ0.01V��/10תΪ0.1V
*******************************************************************************************/
uint32 Lnk_get_EMU_voltage(uint8 ch)
{
    uint32 val,tmpval;
    fp32   f32_tmp;

    if(ch==PHASE_TT) 
    {    
        val= ReadMeterParaACK(RMSU);   
        if(val>=0x80000000)
        {
            val=~val+1;  
        }       
        f32_tmp = (gs_adj_emu_param.vrms_xs*(fp32)val);
        tmpval = (uint32)f32_tmp;
    }
    else
    {
        tmpval = 0;
    }

    return(tmpval);
}

/*******************************************************************************************
** ��������: Lnk_get_EMU_current
** ��������: ��ȡָ��ͨ������
** �������: ch: ͨ�����0�������
** �������: uint32 ָ��ͨ������ֵ��HEX��,����Ϊ0.001A
** ˵��    : 
*******************************************************************************************/
uint32 Lnk_get_EMU_current(uint8 ch)
{
   uint32 val,tmpval;
   fp32   f32_tmp;

    if(ch==WIRE_L) 
    {
        val = ReadMeterParaACK(RMSII1);  
        if(val>=0x80000000)
        {
            val=~val+1;  
        } 
        f32_tmp = gs_adj_emu_param.i1rms_xs*val;
        tmpval = (uint32)f32_tmp;
    }
    else  if(ch==WIRE_N) 
    {
        val = ReadMeterParaACK(RMSII2);   
        if(val>=0x80000000)
        {
            val=~val+1;  
        }
        f32_tmp = gs_adj_emu_param.i2rms_xs*val;
        tmpval = (uint32)f32_tmp;
    }
    else
    {
        tmpval = 0;
    }

    if( tmpval <VAL_CURRENT_ZERO)   tmpval =0;

    return (tmpval);

}

/*******************************************************************************************
** ��������: Lnk_get_EMU_activePower
** ��������: ��ȡָ��ͨ������
** �������: ch: ͨ�����
** �������: uint32 ָ��ͨ������ֵ��HEX��,����Ϊ0.1W
** ˵��    : 
*******************************************************************************************/
uint32 Lnk_get_EMU_activePower(uint8 ch)
{
   uint32 val,tmpval;
   fp32   f32_tmp;

    if(ch==WIRE_L) 
    {
       gs_emu_run_var.net_flg &= ~REV_L_ACPOWER;
       val=ReadMeterParaACK(DATAIP);	 
       if(val>=0x80000000)
       {
          val=~val+1;  
          gs_emu_run_var.net_flg |= REV_L_ACPOWER;
       }
				
    }
   else  if(ch==WIRE_N) 
    {
        gs_emu_run_var.net_flg &= ~REV_N_ACPOWER;
       val=ReadMeterParaACK(DATAIQ);	 
       if(val>=0x80000000)
       {
          val=~val+1; 
           gs_emu_run_var.net_flg |= REV_N_ACPOWER;  
       }	
    }
    else
    {
        val = 0;
    }

    if(val<REF_START_Pn)
    {
        tmpval =0;    
        if(ch==WIRE_L) gs_emu_run_var.net_flg &= ~REV_L_ACPOWER;
        if(ch==WIRE_N) gs_emu_run_var.net_flg &= ~REV_N_ACPOWER;
    }
    else
    {
        f32_tmp = cst_adj_const.Kim_Prms*val;
        tmpval = (uint32)f32_tmp;  	        
    }

    return (tmpval);
}

/*******************************************************************************************
** ��������: Lnk_get_EMU_freq
** ��������: ��ȡָ��ͨ������Ƶ��
** �������: ch: ͨ�����0�������
** �������: uint32 ָ��ͨ��Ƶ��ֵ��HEX��,����Ϊ0.01Hz
** ˵��    : 
*******************************************************************************************/
uint32 Lnk_get_EMU_freq(uint8 ch)
{
    uint32 val,tmpval;

    if(ch==PHASE_TT) 
    {    
        val= ReadMeterParaACK(DATAFREQ);          
        tmpval= (819200 *100)/val;			// 819200ΪADC Ƶ��  //
    }
    else
    {
        tmpval = 0;
    }

    return(tmpval);
}

/*******************************************************************************************
** ��������: uint8 lnk_CAL_EMU_constSum_per_second(uint8 *bypass_flg,uint8 work_mode)
** ��������: ��������ÿ�����
** �������: work_mode : NORMAL_MODE/DLX_MODE/CONST_MODE����ѡ������ģʽ�˳�
**                       *bypass_flg :��·ת̬�֣����������·״̬
** �������: uint8 �������ǰ����ͨ��
** ˵��    :  ��Ƶļ������ó���������ʽ�����ڴ˺���������·�͵����ߵ�
**                   ����ͨ��ѡ��ͳ����Ĵ����ĸ�ֵ��
**                   �������Ǽ�����ʮ����Ҫ�ĺ�������TOU���ļ��ڵ��봦���ڵ���
*******************************************************************************************/
uint8 lnk_CAL_EMU_constSum_per_second(uint8 *net_status,uint8 work_mode)
{
   uint32 val1,val2,sumval;
   fp32   f32_tmp;

    sumval = 0;
    (*net_status) &=(~BYPASS_L);       
    (*net_status) &=(~BYPASS_N);   

    (*net_status) &= (~REV_ACPOWER_L);
    (*net_status) &= (~REV_ACPOWER_N);

    //�Ǵ���ģʽ��������������Ĵ������˳�  // 
    if(work_mode>CONST_MODE)
    {
        sumval = 0;
        SetMeterCfgACK(sumval,DATACP); 
        return (EMU_CH_L);   //����ͨ��ΪL //        
    }

#if((_METER_TYPE_CFG == _METER_TYPE_1P2W_0))
    //A·���ʻ�ȡ //
    val1=ReadMeterParaACK(DATAIP);	 
    if(val1>=0x80000000)
    {
        val1=~val1+1;  
         (*net_status) |=   REV_ACPOWER_L;  
    }
    sumval = val1;

	if(val1<REF_START_Pn)
    {
    	sumval = 0;
    	SetMeterCfgACK(sumval,DATACP);
     	(*net_status) &=  (~REV_ACPOWER_L);  
    }
    SetMeterCfgACK(sumval,DATACP); 
    return (EMU_CH_L);   //����ͨ��ΪL //   
#endif

#if((_METER_TYPE_CFG == _METER_TYPE_1P2W_1)||(_METER_TYPE_CFG == _METER_TYPE_1P2W_2))
    if(work_mode==NORMAL_MODE)
    {
        //A·���ʻ�ȡ //
        val1=ReadMeterParaACK(DATAIP);	 
        if(val1>=0x80000000)
        {
            val1=~val1+1;  
             (*net_status) |=   REV_ACPOWER_L;  
        }

        //B·���ʻ�ȡ //
        val2=ReadMeterParaACK(DATAIQ);	 
        if(val2>=0x80000000)
        {
            val2=~val2+1;  
             (*net_status) |=   REV_ACPOWER_N;  
        }

        if((val1<REF_START_Pn)&&(val2<REF_START_Pn)) 
        {
            sumval = 0;
            SetMeterCfgACK(sumval,DATACP);
             (*net_status) &=   (~REV_ACPOWER_L);
             (*net_status) &=   (~REV_ACPOWER_N);
            return (EMU_CH_L);   //����ͨ��Ĭ��ΪL //   
        }

        if((val1>REF_START_Pn)&&(val2<REF_START_Pn))
        {
            sumval = val1;
            SetMeterCfgACK(sumval,DATACP);
             (*net_status)|=   BYPASS_N;   
              (*net_status) &=   (~REV_ACPOWER_N);           
            return (EMU_CH_L);   //����ͨ��Ĭ��ΪL //      
        }

        if((val1<REF_START_Pn)&&(val2>REF_START_Pn))
        {
            sumval = val2;
            SetMeterCfgACK(sumval,DATACP);
             (*net_status) |=   BYPASS_L;  
             (*net_status) &=   (~REV_ACPOWER_L);
            return (EMU_CH_N);   //����ͨ��Ĭ��ΪN //          
        }

        if((val1>REF_START_Pn)&&(val2>REF_START_Pn))
        {
            if((val2*95) >(val1*100))
            {
                sumval = val2;
                SetMeterCfgACK(sumval,DATACP);
                (*net_status) |=   BYPASS_L;  
                return (EMU_CH_N);   //����ͨ��Ĭ��ΪN //         
            }
            else  if((val1*95) >(val2*100))
            {
                sumval = val1;
                SetMeterCfgACK(sumval,DATACP);
                 (*net_status) |=   BYPASS_N;   
                return (EMU_CH_L);   //����ͨ��Ĭ��ΪL //                 
            }
            else
            {
                sumval = val1;
                SetMeterCfgACK(sumval,DATACP);
                return (EMU_CH_L);   //����ͨ��Ĭ��ΪL //    
            }
        }
    }

    if((work_mode==DLX_MODE)||(work_mode ==CONST_MODE))
    {
        //A·����˲ʱ��Чֵ��ȡ //
        val1=ReadMeterParaACK(RMSII1);	 
        if(val1>=0x80000000)
        {
            val1=~val1+1;  
        }

        //B·����˲ʱ��Чֵ��ȡ //
        val2=ReadMeterParaACK(RMSII2);	 
        if(val2>=0x80000000)
        {
            val2=~val2+1;  
        }  
        
        // �����߻�·�����ж� //
        if((val1<REF_DLX_START_IA) &&(val2>REF_DLX_START_IB))
        {
                f32_tmp = val2*gs_adj_emu_param.vconst_val_ch2;   //  //
                sumval = (uint32)f32_tmp;
                SetMeterCfgACK(sumval,DATACP); 
                return (EMU_CH_N);   //����ͨ��ΪN //                         
        }
        
        if((val1>REF_DLX_START_IA) &&(val2<REF_DLX_START_IB))
        {
                f32_tmp = val1*gs_adj_emu_param.vconst_val_ch1;   //  //
                sumval = (uint32)f32_tmp;
                SetMeterCfgACK(sumval,DATACP); 
                return (EMU_CH_L);   //����ͨ��ΪL //                         
        }
        else
        {
                sumval = 0;
                SetMeterCfgACK(sumval,DATACP); 
                return (EMU_CH_L);   //����ͨ��ΪL //                      
        }
        /////////////////////
              
    }
#endif

    return (EMU_CH_L);   //����ͨ��ΪL //     
}



/*******************************************************************************************
**    END
*******************************************************************************************/


