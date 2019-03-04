/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Lnk_EMU_Adj.c
**Author		: maji
**date			: 2016-04-20 
**description	: G80F92XD��EMU����ģ����·��У����C����
**note			: MCU- G80F92XD ��MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-20   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>



ST_EMU_ADJ_PARAM  gs_adj_emu_param;
ST_EMU_ADJ_VAR      gs_emu_adj_var;


/*********************************************************************************************************
**  У����ز�����ʼ��Ĭ������
********************************************************************************************************/
const  ST_EMU_ADJ_PARAM  code   default_adj_emu_param_tab = 
{
    86243328,  //uint32 w1gain;   //ͨ��1��������Ĵ���(�й��޹�ʹ��ͬһ��)  //
    7,  //uint32 p1cal;           //ͨ��1��ѹ������λ�����Ĵ���  //
    0,  //uint32 watt1os;      //ͨ��1�й�����ƫ��  //
    0,  //uint32 irms1os;      //ͨ��1������Чֵƫ��  //
    3653512704,  //uint32 w2gain;         //ͨ��2��������Ĵ���(�й��޹�ʹ��ͬһ��)  //
    7,  //uint32 p2cal;           //ͨ��2��ѹ������λ�����Ĵ���  //
    0,  //uint32 watt2os;      //ͨ��2�й�����ƫ��  //
    0,  //uint32 irms2os;      //ͨ��2������Чֵƫ��  //
    0.1099405,  //uint32 vconst_val_ch1;   //ͨ��1�����ߵ�ѹ�̶�ֵ //    
    0.07784639,  //uint32 vconst_val_ch2;   //ͨ��2�����ߵ�ѹ�̶�ֵ //
    9.657958e-006,  //float vrms_xs;          //��Ϊ����ĵ�ѹ��Чֵϵ��  //
    0.0001168467,  //float i1rms_xs;         //��Ϊ�����ͨ��1������Чֵϵ��  //
    8.279879e-005,  //float i2rms_xs;         //��Ϊ�����ͨ��2������Чֵϵ��  //
    0,  //uint16     csck;  //У��� //
};

const  ST_Adjust_CONST  code   cst_adj_const = 
{
    C_Un*10,        //uint32 U_ref;       //�αȵ�ѹֵ������0.1V  // 
    2*C_Ib*1000,     //uint32 I_ref;       //�αȵ���ֵ������0.001A  //     
    INITGATEP,     //uint32 GATEP;    // ��������ֵ //
    INITGATECP,   //uint32 C_GATECP;   // Ǳ������ֵ //
    REF_RMSPn,    // uint32 C_PCONST;   // ����ʵ�У׼���׼ֵ//
    K_RMSP,         //float   Kim_Prms;          //�й�������Чֵϵ��//   
};


const  EMU_CK_TAB  code   cst_emu_selfchck_tab[] = 
{
    &gs_adj_emu_param.w1gain,            SCP,    //ͨ��1��������Ĵ���(�й��޹�ʹ��ͬһ��)  //
    &gs_adj_emu_param.w2gain,            SCQ,    //ͨ��2��������Ĵ���(�й��޹�ʹ��ͬһ��)  //
    &gs_adj_emu_param.p1cal,            PHCCtrl1,    //ͨ��1��ѹ������λ�����Ĵ���  //
    &gs_adj_emu_param.p2cal,            PHCCtrl2,    //ͨ��2��ѹ������λ�����Ĵ���  //
    &gs_adj_emu_param.watt1os,            PARAPC,    //ͨ��1�й�����ƫ��  // 
    &gs_adj_emu_param.watt2os,            PARAQC,    //ͨ��2�й�����ƫ��  //
};

const  EMU_CONST_CK_TAB  code   cst_emu_constchck_tab[] = 
{
    INITGATEP,            GATEP,    //uint32 GATEP;    // ��������ֵ //
    INITGATECP,          GATECP,    //uint32 C_GATECP;   // Ǳ������ֵ //
    0,                         SCU,     // U32  ��ѹ��Чֵ�Ȳ�У��ֵ //
    0,                         SCI1,     // U32  I1 ������Чֵ�Ȳ�У��ֵ//
    0,                         SCI2,     // U32  I2 ������Чֵ�Ȳ�У��ֵ//
};

/*********************************************************************************************************
** ��������: Save_EMU_AdjParam
** ��������: EMU��ز����޸ĺ�ı�����´���
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void Save_EMU_AdjParam(void)
{
    gs_adj_emu_param.csck =Lib_get_csck_int16u_num((uint8 *)&gs_adj_emu_param,(LEN_BLOCK70_EMU_PARAM_E2P-2),CHECKWORD);
    mem_db_write(ADR_BLOCK70_EMU_PARAM_E2P, (uint8 *)&gs_adj_emu_param,(LEN_BLOCK70_EMU_PARAM_E2P-2),MEM_E2P1); 
}



/*********************************************************************************************************
** ��������: Save_EMU_AdjParam
** ��������: EMU��ز����޸ĺ�ı�����´���
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void Get_EMU_AdjParam(void)
{
   uint16  csck_u16;
   
    Lib_Set_String((uint8 *)&gs_adj_emu_param,0,sizeof(gs_adj_emu_param));
    //RAM ���ݼ��  //
    csck_u16 =Lib_get_csck_int16u_num((uint8 *)&gs_adj_emu_param,(LEN_BLOCK70_EMU_PARAM_E2P-2),CHECKWORD);
    if(csck_u16 != gs_adj_emu_param.csck)
    {
        mem_read((uint8 *)&gs_adj_emu_param, ADR_BLOCK70_EMU_PARAM_E2P, LEN_BLOCK70_EMU_PARAM_E2P, MEM_E2P1);
    }
}


/*********************************************************************************************************
** ��������: Check_EMU_AdjParam
** ��������: EMU�Ĵ���У��
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void Check_EMU_AdjParam(void)
{
   ST_U32_U08 regval;
   uint8 i;
   EMU_CK_TAB tmp_tab;
   EMU_CONST_CK_TAB  tmp_const_tab;

    // ���RAM�ڵ�У��������ݣ����У�鲻��ȷ���EEPROM�ڻ�ȡ //
    Get_EMU_AdjParam();   

    // �̶�ֵ���õ�У��������ݼ�� //    
    for(i=0;i<(dim(cst_emu_constchck_tab));i++)
    {
        tmp_const_tab.emuAdr = cst_emu_constchck_tab[i].emuAdr;
        tmp_const_tab.val = cst_emu_constchck_tab[i].val;
        regval.u32 = 0;
        regval.u32 = ReadMeterParaACK(tmp_const_tab.emuAdr);     //��������ֵ���  //
        if(regval.u32 != tmp_const_tab.val)
        {
            regval.u32 = tmp_const_tab.val;
            SetMeterCfgACK(regval.u32,tmp_const_tab.emuAdr);
        }  
    }

    // ��ȡ�洢оƬ�ڵ�У�����ݽ��м�� //
    for(i=0;i<(dim(cst_emu_selfchck_tab));i++)
    {
        tmp_tab.emuAdr = cst_emu_selfchck_tab[i].emuAdr;
        tmp_tab.ramAdr = cst_emu_selfchck_tab[i].ramAdr;
        regval.u32 = 0;
        regval.u32= ReadMeterParaACK(tmp_tab.emuAdr);
        if((tmp_tab.emuAdr==PHCCtrl1) ||(tmp_tab.emuAdr==PHCCtrl2))
        {
            if(regval.B08[3] != (uint8)(*tmp_tab.ramAdr))
            {
                regval.u32 = (uint8)(*tmp_tab.ramAdr);
                SetMeterCfgACK(regval.u32,tmp_tab.emuAdr);
            }      
        }
        else
        {
            if(regval.u32 != *tmp_tab.ramAdr)
            {
                regval.u32 = *tmp_tab.ramAdr;
                SetMeterCfgACK(regval.u32,tmp_tab.emuAdr);
            }
        }    
    }


    
}

/*********************************************************************************************************
** ��������: Get_Original_Power
** ��������: ��ȡԭʼ����ֵ
** ��ڲ���: avr_times-ƽ������ 
** ���ڲ���: ��		
********************************************************************************************************/
uint32 Get_Original_Power(uint8 avr_times,uint8 ch)
{
    uint32 val;
    uint8  i;
    uint32 aery_old;
    uint32 aery_val;
    uint32 avr_aery;

    CLRWDT();

    avr_aery=0;
    gs_emu_adj_var.sec_flg=FALSE; 
    for (i=0;i<avr_times;i++)
    {
        CLRWDT();
        while(gs_emu_adj_var.sec_flg==FALSE);
        gs_emu_adj_var.sec_flg=FALSE; 
        CLRWDT(); 
        if(ch==EMU_CH_L)
        {
            val=ReadMeterParaACK(DATAIP);	 
        }
        else
        {
            val=ReadMeterParaACK(DATAIQ);	   
        }

       if(val>=0x80000000)
       {
          val=~val+1;  
       }

       aery_old=val;
       avr_aery=avr_aery+aery_old;
    }   

    aery_val=avr_aery/avr_times;
    CLRWDT();
    NOP();
    return(aery_val);
}	 	



/*********************************************************************************************************
** ��������: Get_Original_Irms
** ��������: ��ȡԭʼ������Чֵ����
** ��ڲ���: avr_times-ƽ������ 
** ���ڲ���: ��		
********************************************************************************************************/
uint32 Get_Original_Irms(uint8 avr_times,uint8 ch)
{
    uint32 val;
    uint8  i;
    uint32 aery_old;
    uint32 aery_val;
    uint32 avr_aery;

    CLRWDT();

    avr_aery=0;
    gs_emu_adj_var.sec_flg=FALSE; 
    for (i=0;i<avr_times;i++)
    {
        CLRWDT();
        while(gs_emu_adj_var.sec_flg==FALSE);
        gs_emu_adj_var.sec_flg=FALSE; 
        CLRWDT(); 
        if(ch==EMU_CH_L)
        {
            val=ReadMeterParaACK(RMSII1);	 
        }
        else
        {
            val=ReadMeterParaACK(RMSII2);	   
        }

       if(val>=0x80000000)
       {
          val=~val+1;  
       }

       aery_old=val;
       avr_aery=avr_aery+aery_old;
    }   

    aery_val=avr_aery/avr_times;
    CLRWDT();
    NOP();
    return(aery_val);
}	 


/*=========================================================================================\n
* @function_name: CalculateSC
* @function_file: EnergyBottom.c
* @����: �Ȳ���㹫ʽ
* 
* 
* @����: 
* @param:CurValue  :����й�����ֵ
* @param:TarValue  :��׼���й�����ֵ
* 
* @����: 
* @return: uint32 
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
INT32U CalculateSC(INT32U CurValue,INT32U TarValue)
{
    //  2016-5-20  mj //                
    INT32S s32_tmp0;
    double f_CurValue,f_TarValue,f_Error;
    double f_s32_tmp0,f_s32_tmp1,f_s32_tmp2,f_s32_tmp3;

    // ��ȡ��ǰ���  ((CurValue-TarValue)/TarValue )*100% //    
    f_CurValue = (double)CurValue;
    f_TarValue = (double)TarValue;
    f_Error = (f_CurValue-TarValue)*1.0/f_TarValue;

	f_s32_tmp0 = 1.0/(1+f_Error);

	f_s32_tmp1 = f_s32_tmp0 - 1.0;
	
	f_s32_tmp2 = f_s32_tmp1* 0x80000000;
	
	f_s32_tmp3 = floor(f_s32_tmp2);     // ����ȡ�� //
	s32_tmp0 = (INT32S)f_s32_tmp3;	
	return (s32_tmp0);
}

/*=========================================================================================\n
* @function_name: CalculateAC
* @function_file: EnergyBottom.c
* @����: �ǲ���㹫ʽ
* 
* 
* @����: 
* @param:CurValue   ������� 
* @param:TarValue   ����׼����
* 
* @����: 
* @return: uint8    
* @����:   lwb (2012-06-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
INT8U CalculateAC(INT32U CurValue,INT32U TarValue)
{
    //���㹫ʽ����,���ı�2011��7��14��//
    INT16U Error;                    
    INT8U Result;
	INT8U JCFH;
	
	JCFH = 0;
	if(TarValue < 50)   return 0;
	
	if(TarValue>CurValue)  
	{
		// ����� //
		Error=(TarValue-CurValue)*1000/TarValue;            //�������ֵ��������1000
		JCFH = 1;
	}
	else
	{
		// ����� //
		Error=(CurValue-TarValue)*1000/TarValue;            //�������ֵ��������1000
	}
    Result = (INT32U)3011*Error/2000;
	if(JCFH==1)
	{
		Result|=BIT7;
	}
    return Result; 
}

/*********************************************************************************************************
** ��������: SoftAdjust_IB_Process
** ��������: У׼����
** ��ڲ���: jzval�����۹���ֵ�����峣��/3600*��̨�������/1000*ICONT*8388608 �磺1200/3600/220*10/1000*96*8388608=576716
**           channel: ����ͨ�� 0-ͨ��1 1-ͨ��2       
** ���ڲ���: ��	
********************************************************************************************************/
void SoftAdjust_IB_Process(uint32 jzval,uint8 channel)
{
   uint32 val;
   uint32 adjust_wcval;

    CLRWDT();
    if(channel==EMU_CH_L)
    {
        val=0;
        SetMeterCfgACK(val,SCP);  //У����������
        SetMeterCfgACK(val,PARAPC);   
    }
    else
    {
        val=0;
        SetMeterCfgACK(val,SCQ);  //У����������
        SetMeterCfgACK(val,PARAQC);   
    }
   adjust_wcval=Get_Original_Power(2,channel); 
   val = CalculateSC(adjust_wcval,jzval);
   
    CLRWDT(); 
    if(channel==EMU_CH_L)
    {
        gs_adj_emu_param.w1gain=val;      
    }
    else
    {
        gs_adj_emu_param.w2gain=val;      
    }
    Save_EMU_AdjParam();
    Check_EMU_AdjParam();
    CLRWDT();
}	

/*********************************************************************************************************
** ��������: SoftAdjust_IB5_Process
** ��������: У׼С����
** ��ڲ���: jzval�����۹���ֵ ���峣��/3600*��̨�������/1000*ICONT*8388608 �磺1200/3600/220*0.5/1000*96*8388608=28835
**           channle:����ͨ���� 0-ͨ��1  1-ͨ��2
** ���ڲ���: ��	
********************************************************************************************************/
void SoftAdjust_IB5_Process(uint32 jzval,uint8 channel)
{
   bit Flag_fu=0;   //���ű�־	

   uint32 val;		 
   uint32 adjust_wcval;
              

    CLRWDT();
    val=0;
    if(channel==EMU_CH_L)
    {
        SetMeterCfgACK(val,PARAPC);   
    }
    else
    {
        SetMeterCfgACK(val,PARAQC);   
    }
   adjust_wcval=Get_Original_Power(3,channel); 
   val = CalculateAC(adjust_wcval,jzval);

    CLRWDT(); 
    if(channel==EMU_CH_L)
    {
        gs_adj_emu_param.watt1os=val;      
    }
    else
    {
        gs_adj_emu_param.watt2os=val;      
    }
    Save_EMU_AdjParam();
    Check_EMU_AdjParam();
    CLRWDT();

}
			
/*********************************************************************************************************
** ��������: SoftAdjust_Phase_Process
** ��������: ����У׼��λ
** ��ڲ���: jzval�����۹���ֵ ���峣��/3600*��̨�������/1000*ICONT*8388608 �磺1200/3600/220*5/1000*96*8388608=288358
**           channel��ͨ����
** ���ڲ���: ��	
********************************************************************************************************/
void SoftAdjust_Phase_Process(uint32 jzval,uint8 channel)
{   
   uint32 val;		 
   uint32 adjust_wcval;
              

    CLRWDT();
    val=0;
    if(channel==EMU_CH_L)
    {
        SetMeterCfgACK(val,PHCCtrl1);   
    }
    else
    {
        SetMeterCfgACK(val,PHCCtrl2);   
    }
    CLRWDT();

    gs_emu_adj_var.sec_flg=FALSE;
    while(gs_emu_adj_var.sec_flg==FALSE);              //��ʱ1�� �ȴ������ȶ�
    gs_emu_adj_var.sec_flg=FALSE; 

   adjust_wcval=Get_Original_Power(2,channel); 
   val = CalculateAC(adjust_wcval,jzval);
   
    CLRWDT(); 
    if(channel==EMU_CH_L)
    {
        gs_adj_emu_param.p1cal=val;      
    }
    else
    {
        gs_adj_emu_param.p2cal=val;      
    }
    Save_EMU_AdjParam();
    Check_EMU_AdjParam();
    CLRWDT();

}
      
/*********************************************************************************************************
** ��������: SoftAdjust_dlxProcess	
** ��������: У׼������У׼
** ��ڲ���: jzval�����۹���ֵ ���峣��/3600*��̨�������/1000*ICONT*8388608 �磺1200/3600/220*5/1000*96*8388608=288358
**           channel��ͨ����
** ���ڲ���: ��	
********************************************************************************************************/
void SoftAdjust_dlxProcess(uint32 jzval,uint8 channel)
{
    uint32 xdata adjust_wcval;

    CLRWDT();
    Init_EMU(DLX_MODE);
    gs_emu_adj_var.sec_flg=FALSE;
    while(gs_emu_adj_var.sec_flg==FALSE);              //��ʱ1�� �ȴ������ȶ�
    gs_emu_adj_var.sec_flg=FALSE; 
    CLRWDT();

    gs_emu_adj_var.sec_flg=FALSE;
    while(gs_emu_adj_var.sec_flg==FALSE);              //��ʱ1�� �ȴ������ȶ�
    gs_emu_adj_var.sec_flg=FALSE;    
    CLRWDT();

    if(channel==EMU_CH_L)
    {
        //Dis_Adjust(7);		
        adjust_wcval=Get_Original_Irms(3,EMU_CH_L);		//��ȡAͨ��ʵ�� ������Чֵ���� //
       gs_adj_emu_param.vconst_val_ch1 =((float) jzval)/((float) adjust_wcval);   //��ȡAͨ���ĳ�������ϵ�� //
    }
    else
    {
        //Dis_Adjust(8);
        adjust_wcval=Get_Original_Irms(3,EMU_CH_N);   //��ȡBͨ��ʵ�� ������Чֵ���� //
        gs_adj_emu_param.vconst_val_ch2 =((float) jzval)/((float) adjust_wcval);   //��ȡBͨ���ĳ�������ϵ�� //
    }

    CLRWDT();
    Init_EMU(NORMAL_MODE);
    Save_EMU_AdjParam();
    Check_EMU_AdjParam();
    NOP();
    NOP();
}

/*********************************************************************************************************
** ��������: Hardware_AdjustDiv_Sub
** ��������: Ӳ���̽� У׼�����ж�
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void Hardware_AdjustDiv_Sub(void)
{
   uint8 i;
    uint32 val;
   uint32 tmpval;
   uint32 tmpval1=0;	 
   uint32 jzwcval;
	uint8 ajust_type;
   uint32 cmp_val[4];
   uint32 adjust_wcval;

    if(EA==0)  return;

    //  ׼���׶�  ����ȡ����ֵ���жϽ�����һ����У��//
    gs_emu_adj_var.adj_flg =0x55;   // =0X55 ��ʶĿǰ����У��״̬ //
    //Dis_Adjust(99);   //׼���׶� 

    jzwcval=cst_adj_const.C_PCONST;     // ����ʵ�Ĺ���У׼��������//
    cmp_val[0]=jzwcval*25/10;         //250% IB ����У����������Ĭ��ֵ��ʼ�� //
    cmp_val[1]=jzwcval*70/100;       // ������У׼ //
    cmp_val[2]=jzwcval*35/100;       // �ǲ�У׼ //
    cmp_val[3]=jzwcval*3/100;         // С�ź�У׼ //

    CLRWDT(); 	 	 
    adjust_wcval=Get_Original_Power(4,EMU_CH_L);	 //��ȡʵ�ʹ���
#if((_METER_TYPE_CFG ==_METER_TYPE_1P2W_1) || (_METER_TYPE_CFG ==_METER_TYPE_1P2W_2)||(_METER_TYPE_CFG ==_METER_TYPE_1P3W_11)  ) 
    if(adjust_wcval>cmp_val[0])
    {
        ajust_type=HARD_EADJ_STEP0_L_INITLIZE;//IB 1.0 ch0;
    }
    else if(adjust_wcval>cmp_val[1])
    {
        ajust_type=HARD_EADJ_STEP1_L_100IB_100L;//IB 1.0 ch0;
    }
    else if(adjust_wcval>cmp_val[2])
    {
        ajust_type=HARD_EADJ_STEP2_L_100IB_50L;//IB 0.5 ch0;   
    }   
    else if(adjust_wcval>cmp_val[3])
    {
        ajust_type=HARD_EADJ_STEP3_L_5IB_100L;//5%IB 1.0 ch0;   
    }
    else
    {
        adjust_wcval=Get_Original_Power(4,EMU_CH_N);	 //��ȡʵ�ʹ���
        if(adjust_wcval>cmp_val[0])
        {
            ajust_type=HARD_EADJ_STEP4_N_INITLIZE;//IB 1.0 ch0;
        }
        else if(adjust_wcval>cmp_val[1])
        {
            ajust_type=HARD_EADJ_STEP5_N_100IB_100L;//IB 1.0 ch1;
        }
        else if(adjust_wcval>cmp_val[2])
        {
            ajust_type=HARD_EADJ_STEP6_N_100IB_50L;//IB 0.5 ch1;     
        }   
        else if(adjust_wcval>cmp_val[3])
        {
            ajust_type=HARD_EADJ_STEP7_N_5IB_100L;//5%IB 1.0 ch1;   
        }
        else
        {
            ajust_type=HARD_EADJ_STEP8_METER_CLR;// �������  //   
        }
    }
#endif

#if((_METER_TYPE_CFG ==_METER_TYPE_1P2W_0)  ) 
    if(adjust_wcval>cmp_val[0])
    {
        ajust_type=HARD_EADJ_STEP0_L_INITLIZE;//IB 1.0 ch0;
    }
    else if(adjust_wcval>cmp_val[1])
    {
        ajust_type=HARD_EADJ_STEP1_L_100IB_100L;//IB 1.0 ch0;
    }
    else if(adjust_wcval>cmp_val[2])
    {
        ajust_type=HARD_EADJ_STEP2_L_100IB_50L;//IB 0.5 ch0;   
    }   
    else if(adjust_wcval>cmp_val[3])
    {
        ajust_type=HARD_EADJ_STEP3_L_5IB_100L;//5%IB 1.0 ch0;   
    }
    else
    {
    	 ajust_type=HARD_EADJ_STEP8_METER_CLR;// �������  //   
    }
#endif

    //   �ֲ���У׼����   //
    //  HARD_EADJ_STEP0_L_INITLIZE   L��·�Ȳ�Ĵ�����ʼ��//
    if(ajust_type==HARD_EADJ_STEP0_L_INITLIZE)
    {                      
        gs_adj_emu_param.w1gain = 0;   //��ʼ��L1ͨ���Ȳ�Ĵ���  //
        Save_EMU_AdjParam();
        Check_EMU_AdjParam();
        CLRWDT();
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_0);   // Һ����ʾ //
    }

    //  HARD_EADJ_STEP1_L_100IB_100L   L��·100%Ib, 1.0L У׼//
    if(ajust_type==HARD_EADJ_STEP1_L_100IB_100L)
    {                      
        //Dis_Adjust(1);  
        // L��·�й�����У׼ // 
        SoftAdjust_IB_Process(jzwcval,EMU_CH_L); 

        // L��·������Чֵ����У׼ //  	
        tmpval=0;
        for(i=0;i<8;i++)
        {
            Lib_Delay_ms(30);
            val = ReadMeterParaACK(RMSII1);
            if(val>=0x80000000)
            {
                val=~val+1;  
            } 		  		
            tmpval=tmpval+val;
            CLRWDT();          
        }
        tmpval=tmpval/8;
        //������Чֵ��λ���ڴ˴�������ȡ����cst_adj_const.I_ref�ͻ������������ı���//
        gs_adj_emu_param.i1rms_xs=(float)cst_adj_const.I_ref/(float)tmpval;  
        //��ѹ��Чֵ����У׼ //             		
        tmpval=0;
        for(i=0;i<8;i++)
        {
            Lib_Delay_ms(30);
            val = ReadMeterParaACK(RMSIU);
            if(val>=0x80000000)
            {
                val=~val+1;  
            } 		  		
            tmpval=tmpval+val;
            CLRWDT();        
        }
        tmpval=tmpval/8;      
        //��ѹ��Чֵ��λ���ڴ˴�������ȡ����cst_adj_const.U_ref�ͻ�����ѹ�����ı���//
        gs_adj_emu_param.vrms_xs=(float)cst_adj_const.U_ref/(float)tmpval;  

#if( (_METER_TYPE_CFG ==_METER_TYPE_1P2W_2) ) 
        // L��·�����ߵ�ѹ����У׼//  
        CLRWDT();            
        //Dis_Adjust(99);   //׼���׶�    
        SoftAdjust_dlxProcess(jzwcval,EMU_CH_L);
#endif

        Save_EMU_AdjParam();
        Check_EMU_AdjParam();
        CLRWDT();
		
	  api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_1);   // Һ����ʾ //
    }

    //  HARD_EADJ_STEP2_L_100IB_50L   L��·100%Ib, 0.5L У׼//
    if(ajust_type==HARD_EADJ_STEP2_L_100IB_50L)
    {                            
        //Dis_Adjust(2);
        jzwcval=jzwcval/2;
        SoftAdjust_Phase_Process(jzwcval,EMU_CH_L);  
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_2);   // Һ����ʾ //
    }
    //  HARD_EADJ_STEP3_L_5IB_100L   L��·5%Ib, 1.0L У׼//
    if(ajust_type==HARD_EADJ_STEP3_L_5IB_100L)
    {                            
        //Dis_Adjust(3);
        jzwcval=jzwcval/20;
        SoftAdjust_IB5_Process(jzwcval,EMU_CH_L);   
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_3);   // Һ����ʾ //   
    }

#if((_METER_TYPE_CFG ==_METER_TYPE_1P2W_1) || (_METER_TYPE_CFG ==_METER_TYPE_1P2W_2)||(_METER_TYPE_CFG ==_METER_TYPE_1P3W_11)  ) 
    //  HARD_EADJ_STEP4_N_INITLIZE   N��·�Ȳ�Ĵ�����ʼ��//
    if(ajust_type==HARD_EADJ_STEP4_N_INITLIZE)
    {                      
        gs_adj_emu_param.w2gain = 0;   //��ʼ��L1ͨ���Ȳ�Ĵ���  //
        Save_EMU_AdjParam();
        Check_EMU_AdjParam();
        CLRWDT();
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_0);   // Һ����ʾ //
    }

    //  HARD_EADJ_STEP4_N_100IB_100L   N��·100%Ib, 1.0L У׼//
    if(ajust_type==HARD_EADJ_STEP5_N_100IB_100L)
    {              
        //Dis_Adjust(1);  
        // L��·�й�����У׼ // 
        SoftAdjust_IB_Process(jzwcval,EMU_CH_N); 

        // L��·������Чֵ����У׼ //  	
        tmpval=0;
        for(i=0;i<8;i++)
        {
            Lib_Delay_ms(30);
            val = ReadMeterParaACK(RMSII2);
            if(val>=0x80000000)
            {
                val=~val+1;  
            } 		  		
            tmpval=tmpval+val;
            CLRWDT();          
        }
        tmpval=tmpval/8;
        //������Чֵ��λ���ڴ˴�������ȡ����cst_adj_const.I_ref�ͻ������������ı���//
        gs_adj_emu_param.i2rms_xs=(float)cst_adj_const.I_ref/(float)tmpval;  

#if( (_METER_TYPE_CFG ==_METER_TYPE_1P2W_2) ) 
        // N��·�����ߵ�ѹ����У׼//  
        CLRWDT();            
        //Dis_Adjust(99);   //׼���׶�    
        SoftAdjust_dlxProcess(jzwcval,EMU_CH_N);
#endif

        Save_EMU_AdjParam();
        Check_EMU_AdjParam();
        CLRWDT();
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_1);   // Һ����ʾ //		
    }

    //  HARD_EADJ_STEP6_N_100IB_50L   N��·100%Ib, 0.5L У׼//
    if(ajust_type==HARD_EADJ_STEP6_N_100IB_50L)
    {                      
        //Dis_Adjust(5);
        jzwcval=jzwcval/2;
        SoftAdjust_Phase_Process(jzwcval,EMU_CH_N);  
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_2);   // Һ����ʾ //
    }    
    //  HARD_EADJ_STEP7_N_5IB_100L   N��·5%Ib, 1.0L У׼//
    if(ajust_type==HARD_EADJ_STEP7_N_5IB_100L)
    {                         
        //Dis_Adjust(6);
        jzwcval=jzwcval/20;
        SoftAdjust_IB5_Process(jzwcval,EMU_CH_N);   
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_3);   // Һ����ʾ //   
    }
#endif

    if(ajust_type==HARD_EADJ_STEP8_METER_CLR)
    {        
        Proc_clr_meter();
        api_chg_LCDDisplay_adj_item(DIS_DATA_CLR);   // Һ����ʾ //
    }

    gs_emu_adj_var.adj_flg =0;   // =0X0 ��ʶĿǰ�˳�У��״̬ //	

}


/*******************************************************************************************
**    END
*******************************************************************************************/


