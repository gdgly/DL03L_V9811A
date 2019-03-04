/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Lcd_Display.c
**Author		: maji
**date			: 2016-04-21 
**description	: Һ����ʾӦ�ò���غ�������C�ļ�
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#include <MyIncludes_H.h>


/*******************************************************************************
* ȫ�ֱ���������
*******************************************************************************/
DIS_PARAM_DATA   gs_dis_param;   // ������ʾ��ز���  //
DIS_CTL_VAR  gs_dis_ctl_var;
DIS_PIXEL_VAR  gs_dis_pixel_var;
LCDDISTAB   gs_LCDDISTAB_var;

/*******************************************************************************
* ��������
*******************************************************************************/
const DIS_PARAM_DATA  code default_dis_param_tab= {
    5,  //uint8  auto_sec;    // �Զ�ѭ����ʾ����ʱ��  //
    30, //uint8  key_sec;     // ������ʾ����ʱ��  //
    30,//uint8  bg_sec;     // �����������ʱ��  //
    0x80,//uint8  ec_form;     // ������ʽ  //
    2,//uint8  auto_item[11];    //0Ϊ��ʾ������1~10Ϊ��ʾ��Ŀ����������ʾ10����Ŀ  //
    6,1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,//uint8  auto_item[1~10];     //
    7,//uint8  key_item[11];    //0Ϊ��ʾ������1~10Ϊ��ʾ��Ŀ����������ʾ10����Ŀ  //
    36,37,32,31,6,1,34,0XFF,0XFF,0XFF,//uint8  key_item[1~10];     //
    2,//uint8  pwn_item[11];    //0Ϊ��ʾ������1~9Ϊ��ʾ��Ŀ����������ʾ9����Ŀ  //
    6,1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,//uint8  auto_item[1~9];     //    
    0x00,//INT16U  u16_csck;    //16λ�ۼӺ�У��ֵ//
};



//  �����ַ����� x//
const INT8U  code NumSeg[DS_Chr_All_NUM] = {
	DS_Chr_0, DS_Chr_1, DS_Chr_2, DS_Chr_3,
	DS_Chr_4, DS_Chr_5, DS_Chr_6, DS_Chr_7,
	DS_Chr_8, DS_Chr_9, DS_Chr_A, DS_Chr_b, 
	DS_Chr_C, DS_Chr_d, DS_Chr_E, DS_Chr_F,
};

// obis����ǰ��λ���� x//
const INT8U  code NumSegOBIS[DS_Chr_All_NUM] = {
	DS_OBIS_Chr_0, DS_OBIS_Chr_1, DS_OBIS_Chr_2, DS_OBIS_Chr_3,
	DS_OBIS_Chr_4, DS_OBIS_Chr_5, DS_OBIS_Chr_6, DS_OBIS_Chr_7,
	DS_OBIS_Chr_8, DS_OBIS_Chr_9, DS_OBIS_Chr_A, DS_OBIS_Chr_b, 
	DS_OBIS_Chr_C, DS_OBIS_Chr_d, DS_OBIS_Chr_E, DS_OBIS_Chr_F,
};


// ����OBIS ���һλ����//
const INT8U  code NumSegOBIS1[DS_Chr_All_NUM] = {
	DS_OBIS1_Chr_0, DS_OBIS1_Chr_1, DS_OBIS1_Chr_2, DS_OBIS1_Chr_3,
	DS_OBIS1_Chr_4, DS_OBIS1_Chr_5, DS_OBIS1_Chr_6, DS_OBIS1_Chr_7,
	DS_OBIS1_Chr_8, DS_OBIS1_Chr_9, DS_OBIS1_Chr_A, DS_OBIS1_Chr_b, 
	DS_OBIS1_Chr_C, DS_OBIS1_Chr_d, DS_OBIS1_Chr_E, DS_OBIS1_Chr_F,
};

//-------------------------------------------------------------------------------//
//  Function:     Һ����ʾ��Ŀ��Ԫ�ر�       --��ROM��
//-------------------------------------------------------------------------------//
const LCDDISTAB code LcdDisTab[] =
 {  
//ID	obis		obis	addr			
    ////////////////////////////ALL  DISPLAY////////////////////////////////////////////////////////
    0,  0x8888,	0X0000,										0 ,	 				0,	OBIS_DIGIT_TYPE0,	// ALL DISPLAY  //
    ////////////////////////////ACTIVE ENERGY  DISPLAY////////////////////////////////////////////////////////
    0x01,  0x180F,	 (INT16U)&gs_energy_user_data.us_val[0][0].buf[0],               (MEM_RAM<<8)+6,	CHAR_AEC,OBIS_DIGIT_TYPE1,	// L0 ACTIVE ENERGY TOTAL 
    0x02,  0x181F,	 (INT16U)&gs_energy_user_data.us_val[0][1].buf[0],               (MEM_RAM<<8)+6,	CHAR_AEC,OBIS_DIGIT_TYPE1,	// L0 ACTIVE ENERGY T1
    0x03,  0x182F,	 (INT16U)&gs_energy_user_data.us_val[0][2].buf[0],               (MEM_RAM<<8)+6,	CHAR_AEC,OBIS_DIGIT_TYPE1,	// L0 ACTIVE ENERGY T1
    0x04,  0x183F,	 (INT16U)&gs_energy_user_data.us_val[0][3].buf[0],               (MEM_RAM<<8)+6,	CHAR_AEC,OBIS_DIGIT_TYPE1,	// L0 ACTIVE ENERGY T1
    0x05,  0x184F,	 (INT16U)&gs_energy_user_data.us_val[0][4].buf[0],               (MEM_RAM<<8)+6,	CHAR_AEC,OBIS_DIGIT_TYPE1,	// L0 ACTIVE ENERGY T1
    0X06,  0x1800, 	 ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_ec,				                            (MEM_E2P1<<8)+6,CHAR_AEC,OBIS_DIGIT_TYPE2,	//L1 ACTIVE ENERGY TOTAL 
    0X07,  0x1810, 	 ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_ec+1*LEN_EC_UNIT ,		 	       (MEM_E2P1<<8)+6,CHAR_AEC,OBIS_DIGIT_TYPE2,	//L1 ACTIVE ENERGY T1
    0X08,  0x1820, 	 ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_ec+ 2*LEN_EC_UNIT,				(MEM_E2P1<<8)+6,CHAR_AEC,OBIS_DIGIT_TYPE2,	//L1 ACTIVE ENERGY T2
    0X09,  0x1830, 	 ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_ec+ 3*LEN_EC_UNIT,				(MEM_E2P1<<8)+6,CHAR_AEC,OBIS_DIGIT_TYPE2,	//L1 ACTIVE ENERGY T3
    0X0A,  0x1840,    ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_ec+ 4*LEN_EC_UNIT,				(MEM_E2P1<<8)+6,CHAR_AEC,OBIS_DIGIT_TYPE2,	//L1 ACTIVE ENERGY T2
    0X0B,  0x1801, 	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_ec ,				                                   (MEM_E2P1<<8)+6,CHAR_AEC,OBIS_DIGIT_TYPE2,	//L1 ACTIVE ENERGY TOTAL 
    0X0C,  0x1811, 	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_ec+1*LEN_EC_UNIT,			              (MEM_E2P1<<8)+6,CHAR_AEC,OBIS_DIGIT_TYPE2,	//L1 ACTIVE ENERGY T1
    0X0D,  0x1821, 	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_ec+2*LEN_EC_UNIT,				       (MEM_E2P1<<8)+6,CHAR_AEC,OBIS_DIGIT_TYPE2,	//L1 ACTIVE ENERGY T2
    0X0E,  0x1831, 	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_ec+3*LEN_EC_UNIT,				       (MEM_E2P1<<8)+6,CHAR_AEC,OBIS_DIGIT_TYPE2,	//L1 ACTIVE ENERGY T3
    0X0F,  0x1841, 	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_ec+4*LEN_EC_UNIT,				       (MEM_E2P1<<8)+6,CHAR_AEC,OBIS_DIGIT_TYPE2,	//L1 ACTIVE ENERGY T2
    0X10,  0x160F, 	ADR_BLOCK01_MMD_L0_E2P + 0*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE1,	//L0 ACTIVE MAX DEMAND TOTAL  XX.XXXXKW
    0X11,  0x161F, 	ADR_BLOCK01_MMD_L0_E2P + 1*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE1,	//L0 ACTIVE MAX DEMAND T1  XX.XXXXKW
    0X12,  0x162F, 	ADR_BLOCK01_MMD_L0_E2P + 2*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE1,	//L0 ACTIVE MAX DEMAND T2  XX.XXXXKW
    0X13,  0x163F, 	ADR_BLOCK01_MMD_L0_E2P + 3*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE1,	//L0 ACTIVE MAX DEMAND T3  XX.XXXXKW
    0X14,  0x164F, 	ADR_BLOCK01_MMD_L0_E2P + 4*LEN_MMD_UNIT,			       (MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE1,	//L0 ACTIVE MAX DEMAND T4  XX.XXXXKW	
    0X15,  0x1600, 	ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_mmd+ 0*LEN_MMD_UNIT,			       (MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE2,	//L0 ACTIVE MAX DEMAND TOTAL  XX.XXXXKW
    0X16,  0x1610, 	ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_mmd+ 1*LEN_MMD_UNIT,			       (MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE2,	//L0 ACTIVE MAX DEMAND T1  XX.XXXXKW
    0X17,  0x1620, 	ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_mmd+ 2*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE2,	//L0 ACTIVE MAX DEMAND T2  XX.XXXXKW
    0X18,  0x1630, 	ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_mmd+ 3*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE2,	//L0 ACTIVE MAX DEMAND T3  XX.XXXXKW
    0X19,  0x1640, 	ADR_BLOCK101_BILL1_DATA_E2P+OFFSET_bill_data_mmd+ 4*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE2,	//L0 ACTIVE MAX DEMAND T4  XX.XXXXKW	
    0X1a,  0x1601, 	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_mmd+ 0*LEN_MMD_UNIT,		              (MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE2,	//L0 ACTIVE MAX DEMAND TOTAL  XX.XXXXKW
    0X1b,  0x1611, 	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_mmd+ 1*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE2,	//L0 ACTIVE MAX DEMAND T1  XX.XXXXKW
    0X1c,  0x1621, 	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_mmd+ 2*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE2,	//L0 ACTIVE MAX DEMAND T2  XX.XXXXKW
    0X1d,  0x1631, 	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_mmd+ 3*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE2,	//L0 ACTIVE MAX DEMAND T3  XX.XXXXKW
    0X1e,  0x1641, 	ADR_BLOCK102_BILL2_DATA_E2P+OFFSET_bill_data_mmd+ 4*LEN_MMD_UNIT,				(MEM_E2P1<<8)+3,CHAR_MD,OBIS_DIGIT_TYPE2,	//L0 ACTIVE MAX DEMAND T4  XX.XXXXKW	

    0X1F,  0x3270,	(INT16U)&gs_measure_var_data.gs_really[0].dw_u_val.B08[2],(MEM_RAM<<8)+2,	CHAR_V,OBIS_DIGIT_TYPE3,			// L1 ��ѹ (3+1)  A��
    0x20,  0x3170,	(INT16U)&gs_measure_var_data.gs_really[0].dw_i_val.B08[0],(MEM_RAM<<8)+3,	CHAR_A,OBIS_DIGIT_TYPE3,			// L1 ��ѹ (3+1)  A��
    0x21,  0x170F,	(INT16U)&gs_measure_var_data.gs_really[0].dw_p_val.B08[0],(MEM_RAM<<8)+3,	CHAR_KW,OBIS_DIGIT_TYPE1,	// total ac power	
    0x22,  0x1370,	(INT16U)&gs_measure_var_data.gs_really[0].dw_pf_val.B08[0],(MEM_RAM<<8)+2,	CHAR_PF,OBIS_DIGIT_TYPE3,	// total PF	
    0x23,  0x1470,	(INT16U)&gs_measure_var_data.gs_really[0].w_freq_val.B08[0],(MEM_RAM<<8)+2,	CHAR_HZ,OBIS_DIGIT_TYPE3,	// FREQUENCE
    0x24,  0x092F, 	(INT16U)&gs_CurDateTime.Year,			(MEM_RAM<<8)+3, 			CHAR_DATE,OBIS_DIGIT_TYPE1,	//���� ������
    0x25,  0x091F,	(INT16U)&gs_CurDateTime.Hour,				(MEM_RAM<<8)+3,				CHAR_TIME,OBIS_DIGIT_TYPE1,	//ʱ�� (ʱ-��-��)
    0x26,  0xC10F,	ADR_METER_PARAM1_METER_ID,               (MEM_E2P1<<8)+8,		0,OBIS_DIGIT_TYPE1,	//meter id    LOW 8byte  //
    0x27,  0x030F,	&sys_parm.meter_cons[0],		              (MEM_RAM<<8)+3,		0,OBIS_DIGIT_TYPE1,	//meter active constant  //
    0x28,  0xC712,	ADR_METER_PARAM1_SETL_DDHH,		(MEM_E2P1<<8)+2,		CHAR_SETTL,OBIS_DIGIT_TYPE4,	//meter active constant  //

} ;

/*****************************************************************************
** Function name    :api_init_md_data_ram
**
** Description         :ÿ�����Һ����ʾ��Ŀ       
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_init_display(void)
{
    mem_read(&gs_dis_param.auto_sec, ADR_BLOCK21_DIS_PARAM_E2P, LEN_BLOCK21_DIS_PARAM_E2P, MEM_E2P1);	 //     
    if((gs_dis_param.auto_sec<3)||(gs_dis_param.auto_sec>60))    gs_dis_param.auto_sec = 5;
    if((gs_dis_param.key_sec<5)||(gs_dis_param.key_sec>60))    gs_dis_param.key_sec = 30;
    gs_dis_ctl_var.mode = DIS_MODE_RESET;
    gs_dis_ctl_var.item = DIS_RESET;
    gs_dis_ctl_var.ptr[0] =1;  //����������� //
    gs_dis_ctl_var.keep_sec[0] = 0;
    gs_dis_ctl_var.keep_sec[1] = 0;
    gs_dis_ctl_var.keep_sec[2] = gs_dis_param.bg_sec;             //  �����ϵ����//
    gs_dis_ctl_var.keep_sec[3] = RESEAT_DIS_KEEP_3S; //  �ϵ�ȫ����ʾʱ��//
}

/*****************************************************************************
** Function name    :api_init_md_data_ram
**
** Description         :��ʼ����ǰ��������RAM�����ݣ�����λ��ʼ������        
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_handl_dis_key_10ms(void)
{
    if((gs_sys_run.back_fg&BIT2_BACK_DIS_KEY)==0)
    {
        return;
    }
         
    if((Judge_DIS_key()==TRUE))
    {
   	 gs_dis_ctl_var.cnt_10ms_dis_key_delay++;
    }
    else
    {
       gs_dis_ctl_var.cnt_10ms_dis_key_delay = 0;
       gs_sys_run.back_fg &= ~BIT2_BACK_DIS_KEY;
       return;
    }

   if(gs_dis_ctl_var.cnt_10ms_dis_key_delay<10)    // ����ʱ�����100ms ��ʾ������Ч //
   {
         return;
   }

    gs_dis_ctl_var.cnt_10ms_dis_key_delay = 0;
    gs_sys_run.back_fg &= ~BIT2_BACK_DIS_KEY;
        
    gs_dis_ctl_var.keep_sec[1] = gs_dis_param.key_sec; // ��������ʱ��//
    gs_dis_ctl_var.keep_sec[2] = gs_dis_param.bg_sec; // ������//

    if((gs_dis_ctl_var.mode == DIS_MODE_NOMAL)||(gs_dis_ctl_var.mode == DIS_MODE_RESET))
    {
        gs_dis_ctl_var.mode = DIS_MODE_MAN;
        mem_read(&gs_dis_param.key_item[0], ADR_DIS_PARAM_KEY_TAB, 11, MEM_E2P1);	 // 
        gs_dis_ctl_var.ptr[1] =0;
       gs_dis_ctl_var.item = gs_dis_param.key_item[gs_dis_ctl_var.ptr[1]+1];  //  0λ��Ϊ��ʾ��Ŀ������1λ�ÿ�ʼΪ��Ŀ //
		
    }
    else
    {
        gs_dis_ctl_var.item = api_get_next_dis_item();
    }

    api_updated_LCDDisplayPixel_per_second();
    
}

/*****************************************************************************
** Function name    :api_init_md_data_ram
**
** Description         :��ʼ����ǰ��������RAM�����ݣ�����λ��ʼ������        
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_handl_dis_sleep(void)
{
    gs_dis_ctl_var.mode = DIS_MODE_OFF;
    LCD_OFF();
}

/*****************************************************************************
** Function name    :api_init_md_data_ram
**
** Description         :��ʼ����ǰ��������RAM�����ݣ�����λ��ʼ������        
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_handl_dis_sleep_key(void)
{
    gs_dis_ctl_var.keep_sec[1] = gs_dis_param.key_sec; // ��������ʱ��//
    if(gs_dis_ctl_var.mode != DIS_MODE_SLEEP)
   {
       mem_read(&gs_dis_param.auto_sec, ADR_BLOCK21_DIS_PARAM_E2P, LEN_BLOCK21_DIS_PARAM_E2P, MEM_E2P1);	 // 
	if((gs_dis_param.auto_sec<3)||(gs_dis_param.auto_sec>60))    gs_dis_param.auto_sec = 5;
	if((gs_dis_param.key_sec<5)||(gs_dis_param.key_sec>60))    gs_dis_param.key_sec = 30;
       gs_dis_ctl_var.ptr[2] =0;
       gs_dis_ctl_var.item = gs_dis_param.pwn_item[gs_dis_ctl_var.ptr[2]+1];  //  0λ��Ϊ��ʾ��Ŀ������1λ�ÿ�ʼΪ��Ŀ //       
       gs_dis_ctl_var.mode = DIS_MODE_SLEEP;
   }
   else
  {
       gs_dis_ctl_var.item = api_get_next_dis_item();    
  }

  api_updated_LCDDisplayPixel_per_second();
}



/*****************************************************************************
** Function name    :api_updata_LCDDisplay_per_second
**
** Description         :ÿ�����Һ����ʾ����      
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_updated_LCDDisplayPixel_per_second(void)
{

    Lib_Set_String(&gs_dis_pixel_var.dis_buff[0],0,DS_UNIT);
    // ����Ӳ��У����ʾ���� //
    if((gs_dis_ctl_var.item>=DIS_ADJ_CH1_0) &&(gs_dis_ctl_var.item<=DIS_DATA_CLR))
    {
        api_LCDDisplay_adj_item(gs_dis_ctl_var.item);
        Link_Get_Dis_RealChar_buff();
        Link_Get_Dis_Drv_buff();		
        Write_LCD(&gs_dis_pixel_var.dis_buff[0]);         //������д��Һ������//
        return;
    }

    if(gs_dis_ctl_var.item>DIS_MAX_ITEM)
    {
        gs_dis_ctl_var.item = DIS_DEFAULT_ITEM;    // ϵͳ��ʾ��Ŀ�쳣���Ĭ��Ϊ��ʾϵͳ������  //
    }

    if(gs_dis_ctl_var.item == DIS_RESET)
    {
        Lib_Set_String(&gs_dis_pixel_var.dis_buff[0],0xff,DS_UNIT);
    }
    else
    {
        Link_Get_DisTab_Var(gs_dis_ctl_var.item) ;   // ��ʾ  err      		// ��ȡ��ʾ��Ŀ��Ϣ  //
        Link_Get_Dis_OBIS_Num_buff();   
        Link_Get_Dis_Data_Num_buff();
        Link_Get_Dis_Char_buff();            
        if(gs_sys_globaL_var.work_mode != SLEEP_MODE)   Link_Get_Dis_RealChar_buff();
        Link_Get_Dis_Drv_buff();		 
    }

    Write_LCD(&gs_dis_pixel_var.dis_buff[0]);         //������д��Һ������
}

/*****************************************************************************
** Function name    :api_updata_LCDDisplay_per_second
**
** Description         :ÿ�����Һ����ʾ����      
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_updated_BG_per_second(void)
{
    if(gs_dis_param.bg_sec>60)     //�����������ʱ�����60����Ĭ�ϱ����ϵ粻Ϩ��  //
    {
        LED_BG_ON();   
        return;
    }
    
    if(gs_dis_ctl_var.keep_sec[2]>0)
    {
        gs_dis_ctl_var.keep_sec[2]--;
        LED_BG_ON();  
    }
    else
    {
         LED_BG_OFF();    
    }

	if(gs_measure_status_judge_var.u8_status&REV_ACPOWER_L)
		PIN_Reverse_HIGH()
	else
		PIN_Reverse_LOW()
}



/*****************************************************************************
** Function name    :api_init_md_data_ram
**
** Description         :ÿ�����Һ����ʾ��Ŀ       
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_updated_LCDDisplayItem_per_second(void)
{

    switch (gs_dis_ctl_var.mode )
    {
        case DIS_MODE_RESET:			 
            gs_dis_ctl_var.keep_sec[3] --;
            if(gs_dis_ctl_var.keep_sec[3]==0)  
            {
                gs_dis_ctl_var.mode = DIS_MODE_NOMAL;
                gs_dis_ctl_var.keep_sec[0] = gs_dis_param.auto_sec;
                gs_dis_ctl_var.ptr[0] = 0;
                gs_dis_ctl_var.item = gs_dis_param.auto_item[gs_dis_ctl_var.ptr[0]+1];  //  0λ��Ϊ��ʾ��Ŀ������1λ�ÿ�ʼΪ��Ŀ //                
            }
        break;

        case DIS_MODE_MAN:			 
            gs_dis_ctl_var.keep_sec[1] --;
            if(gs_dis_ctl_var.keep_sec[1]==0)  
            {
                gs_dis_ctl_var.mode = DIS_MODE_NOMAL;
                gs_dis_ctl_var.keep_sec[0] = gs_dis_param.auto_sec;
                gs_dis_ctl_var.ptr[0] = 0;
                gs_dis_ctl_var.item = gs_dis_param.auto_item[gs_dis_ctl_var.ptr[0]+1];  //  0λ��Ϊ��ʾ��Ŀ������1λ�ÿ�ʼΪ��Ŀ //  
            }
        break;

        case DIS_MODE_NOMAL:			 
            gs_dis_ctl_var.keep_sec[0] --;
            if( gs_dis_ctl_var.keep_sec[0] == 0)
            {
                gs_dis_ctl_var.keep_sec[0] = gs_dis_param.auto_sec; //���Գ���ʱ��//
                gs_dis_ctl_var.item = api_get_next_dis_item();
            }
        break;

        default:
            gs_dis_ctl_var.mode = DIS_MODE_NOMAL;
        break;

    }   
}
	   
/*****************************************************************************
** Function name    :api_get_next_dis_item
**
** Description         :������һ����ʾ��Ŀ     
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
INT8U api_get_next_dis_item(void)
{
 INT8U vaild_len;
 INT8U item;

    item = DIS_DEFAULT_ITEM;
    if((gs_dis_ctl_var.mode  == DIS_MODE_NOMAL))
    {
        gs_dis_ctl_var.ptr[0]++;
        if((gs_dis_ctl_var.ptr[0]>=(gs_dis_param.auto_item[0]))||(gs_dis_ctl_var.ptr[0]>10))   //��ĿΪ0~9,��10�� //
        {
            gs_dis_ctl_var.ptr[0]=0;
        }

        item = gs_dis_param.auto_item[gs_dis_ctl_var.ptr[0]+1];  //  0λ��Ϊ��ʾ��Ŀ������1λ�ÿ�ʼΪ��Ŀ //
        if(item>DIS_MAX_ITEM)   
        {
            item =     DIS_DEFAULT_ITEM;
        }
    }

    if((gs_dis_ctl_var.mode ==DIS_MODE_MAN))
    {
        gs_dis_ctl_var.ptr[1]++;
        if((gs_dis_ctl_var.ptr[1]>=(gs_dis_param.key_item[0]))||(gs_dis_ctl_var.ptr[1]>10))  //��ĿΪ0~9,��10�� //
        {
            gs_dis_ctl_var.ptr[1]=0;
        }

        item = gs_dis_param.key_item[gs_dis_ctl_var.ptr[1]+1];  //  0λ��Ϊ��ʾ��Ŀ������1λ�ÿ�ʼΪ��Ŀ //
        if(item>DIS_MAX_ITEM)   
        {
            item =     DIS_DEFAULT_ITEM;
        }
    }

    if((gs_dis_ctl_var.mode ==DIS_MODE_SLEEP))
    {
        gs_dis_ctl_var.ptr[2]++;
        if((gs_dis_ctl_var.ptr[2]>=(gs_dis_param.pwn_item[0]))||(gs_dis_ctl_var.ptr[2]>9))  //��ĿΪ0~8,��9�� //
        {
            gs_dis_ctl_var.ptr[2]=0;
        }

        item = gs_dis_param.pwn_item[gs_dis_ctl_var.ptr[2]+1];  //  0λ��Ϊ��ʾ��Ŀ������1λ�ÿ�ʼΪ��Ŀ //
        if(item>DIS_MAX_ITEM)   
        {
            item =     DIS_DEFAULT_ITEM;
        }
    }
    
    return (item);
}

//*****************************************************************
//  Function:       INT8U Link_Get_DisIndex(u8_dis_itm)        
//  Description:    ��ȡ��ʾ��Ŀ��Ϣ                                        
//  Input:                                                                            
//  Output:         no                              
//  Return:         no                              
//  Others:         
//***************************************************************/
INT8U Link_Get_DisTab_Var(INT8U u8_dis_itm)
{
 INT8U i;
 INT8U u8_result=FALSE;

	if(u8_dis_itm>DIS_MAX_ITEM)
	{
		u8_dis_itm = DIS_DEFAULT_ITEM;    // ϵͳ��ʾ��Ŀ�쳣���Ĭ��Ϊ��ʾϵͳ������  //
	}

	for( i = 0 ; i <=DIS_MAX_ITEM ; i++ )
	{
		if( u8_dis_itm== LcdDisTab[i].DisID)
		{
			gs_LCDDISTAB_var.DisID = u8_dis_itm;
			gs_LCDDISTAB_var.ObisNum= LcdDisTab[i].ObisNum;
			gs_LCDDISTAB_var.Addr =LcdDisTab[i].Addr;
			gs_LCDDISTAB_var.DisInfo = LcdDisTab[i].DisInfo;
			gs_LCDDISTAB_var.chartype = LcdDisTab[i].chartype;
			gs_LCDDISTAB_var.obis_digit= LcdDisTab[i].obis_digit;
			u8_result = TRUE;
			return (u8_result);
		}
	}

	if(u8_result == FALSE )
	{
		gs_LCDDISTAB_var.DisID = DIS_DEFAULT_ITEM;  // Ĭ����ʾ��ǰ�й��� 
		gs_LCDDISTAB_var.ObisNum = LcdDisTab[0x01].ObisNum;
		gs_LCDDISTAB_var.Addr =LcdDisTab[0x01].Addr;
		gs_LCDDISTAB_var.DisInfo = LcdDisTab[0x01].DisInfo;
		gs_LCDDISTAB_var.chartype = LcdDisTab[0x01].chartype;		
	}
	return (u8_result);
			
}


//*****************************************************************
//  Function:      void Link_Get_Dis_OBIS_Num_buff(void)      
//  Description:    ��ȡOBIS������ʾ���ݣ� 4��8����                                       
//  Input:                                                                            
//  Output:         no                              
//  Return:         no                              
//  Others:         dis_obis_buff[0] ��ӦOBIS����ʾ�������1λ(��λ)
//***************************************************************/
void Link_Get_Dis_OBIS_Num_buff(void)
{ 
	 Lib_Set_String(&gs_dis_pixel_var.dis_obis_buff[0],0,4);
        gs_dis_pixel_var.dis_obis_buff[0]  =NumSegOBIS[ (gs_LCDDISTAB_var.ObisNum & 0xF000) >>12];
        gs_dis_pixel_var.dis_obis_buff[1]  = NumSegOBIS[ (gs_LCDDISTAB_var.ObisNum & 0x0F00) >>8];
	  gs_dis_pixel_var.dis_obis_buff[2]  = NumSegOBIS[ (gs_LCDDISTAB_var.ObisNum & 0x00F0) >>4];
	  if((gs_LCDDISTAB_var.ObisNum&0x000F) == 0x000F)    gs_dis_pixel_var.dis_obis_buff[3] =0;
	  else   gs_dis_pixel_var.dis_obis_buff[3]  = NumSegOBIS1[(gs_LCDDISTAB_var.ObisNum & 0x000F)];
}		
		


//*****************************************************************
//  Function:      void Link_Get_Dis_OBIS_Num_buff(void)      
//  Description:    ��ȡDATA������ʾ���ݣ� 8��8����                                       
//  Input:                                                                            
//  Output:         no                              
//  Return:         no                              
//  Others:         dis_data_buff[0] ��ӦNUM����ʾ�������1λ(��λ)
//***************************************************************/
void Link_Get_Dis_Data_Num_buff(void)
{
 ST_U32_U08   buffer,u32_tmp;
 INT8U  temp[6],i;
 INT8U buffertemp1[16];
 INT8U u8_len,u8_mem_type;
 INT8U u8_tmp;

  INT8U meterid_asclen;
  INT8U meterid_len;
		
 	u8_len = (INT8U)gs_LCDDISTAB_var.DisInfo;
	if(u8_len>6) u8_len= 6;

	u8_mem_type =  (INT8U)(gs_LCDDISTAB_var.DisInfo>>8);

	// ���ݻ�ȡ����  //
	switch (gs_LCDDISTAB_var.chartype)
	{
		case CHAR_AEC:			 
		     if((gs_LCDDISTAB_var.ObisNum&0x000F )!= 0x000F)      //��ʷ����
                    {
                      mem_read(&temp[0],  api_get_bill_record_addr(gs_LCDDISTAB_var.Addr),LEN_EC_UNIT, u8_mem_type );	//��ȡ��ʷ���� //
		      }
			else  // ��ǰ����
		      {	
			 mem_read(&temp[0],gs_LCDDISTAB_var.Addr, LEN_EC_UNIT, u8_mem_type);		//��ȡ��ǰ���� //
		      }
		      api_get_energy_LCD(&temp[0], gs_dis_param.ec_form,&buffer.B08[0]);
			break;
		case CHAR_MD:
		 if((gs_LCDDISTAB_var.ObisNum&0x000F) != 0x000F)      //��ʷ����
                   {
                      mem_read(&u32_tmp.B08[0],  api_get_bill_record_addr(gs_LCDDISTAB_var.Addr),4, u8_mem_type );	//��ȡ��ʷ���� //
		      }
			else  // ��ǰ����
			{	
			 mem_read(&u32_tmp.B08[0],gs_LCDDISTAB_var.Addr, 4, u8_mem_type);		//��ȡ��ǰ���� //
		       }

			Lib_long_bcd4(&buffer.B08[0],u32_tmp.u32);          //  16����ת10����// 
                    buffer.B08[0] = buffer.B08[1];
                    buffer.B08[1] = buffer.B08[2];
                    buffer.B08[2] = buffer.B08[3];
			break;

		case CHAR_V:
		case CHAR_HZ:
		case CHAR_PF:
                    mem_read(&u32_tmp.B08[2],gs_LCDDISTAB_var.Addr, 2, u8_mem_type);		//��ȡ��ǰ���� //
                    Lib_word_bcd2(&buffer.B08[0],u32_tmp.W16[1]);          //  16����ת10����// 
			break;

		case CHAR_A:
		case CHAR_KW:
                    mem_read(&u32_tmp.B08[0],gs_LCDDISTAB_var.Addr, 4, u8_mem_type);		//��ȡ��ǰ���� //
                    Lib_long_bcd4(&buffer.B08[0],u32_tmp.u32);          //  16����ת10����// 
                    buffer.B08[0] = buffer.B08[1];
                    buffer.B08[1] = buffer.B08[2];
                    buffer.B08[2] = buffer.B08[3];
			break;
            
	      case CHAR_DATE:	// ������ʾ DD.MM.YY//
		      buffer.B08[0] = gs_CurDateTime.Day;
                   buffer.B08[1] = gs_CurDateTime.Month;
                   buffer.B08[2] = gs_CurDateTime.Year;
                   break;

		default:
			mem_read(&buffer.B08[0],gs_LCDDISTAB_var.Addr, u8_len, u8_mem_type);		//��ȡ��ǰ���� //
			break;
	}


	//��ź�8λ	E2����ֱ�Ӷ�����ʽ��ת�� //
	if(gs_LCDDISTAB_var.DisID == 0x26)     
	{
		mem_read(&buffertemp1[0],gs_LCDDISTAB_var.Addr, 16, u8_mem_type);		//��ȡ��ǰ���� //
		meterid_asclen = Lib_get_data_0xFF_asclen(&buffertemp1[0], 16);
		meterid_len = meterid_asclen/2;
		if(meterid_len == 0) meterid_len = 1;
		if(meterid_len>3) 
		{
			buffer.B08[3] = buffertemp1[meterid_len-1];
			buffer.B08[2] = buffertemp1[meterid_len-2];
			buffer.B08[1] = buffertemp1[meterid_len-3];
			buffer.B08[0] = buffertemp1[meterid_len-4];
			u8_len = 4;
		}
		else if (meterid_len>2) 
		{
			buffer.B08[2] = buffertemp1[meterid_len-1];
			buffer.B08[1] = buffertemp1[meterid_len-2];
			buffer.B08[0] = buffertemp1[meterid_len-3];
			u8_len = 3;			
		}
		else if (meterid_len>1) 
		{
			buffer.B08[1] = buffertemp1[meterid_len-1];
			buffer.B08[0] = buffertemp1[meterid_len-2];
			u8_len = 2;						
		}
		else  
		{
			buffer.B08[0] = buffertemp1[meterid_len-1];
			u8_len = 1;			
		}	
		
	}
	
	// ��ʾBUFF���ݻ�ȡ //
	Lib_Set_String(&gs_dis_pixel_var.dis_data_buff[0],0,8);
	switch(u8_len)
	{
	       case 4:
		case 6:
//			gs_dis_pixel_var.dis_data_buff[0] = NumSeg[(buffer.B08[0]&0xF0)>>4]	;  
//			gs_dis_pixel_var.dis_data_buff[1] = NumSeg[(buffer.B08[0]&0x0F)]	; 
			gs_dis_pixel_var.dis_data_buff[2] = NumSeg[(buffer.B08[1]&0xF0)>>4]	;  
			gs_dis_pixel_var.dis_data_buff[3] = NumSeg[(buffer.B08[1]&0x0F)]	; 
			gs_dis_pixel_var.dis_data_buff[4] = NumSeg[(buffer.B08[2]&0xF0)>>4]	;  
			gs_dis_pixel_var.dis_data_buff[5] = NumSeg[(buffer.B08[2]&0x0F)]	; 
			gs_dis_pixel_var.dis_data_buff[6] = NumSeg[(buffer.B08[3]&0xF0)>>4]	;  
			gs_dis_pixel_var.dis_data_buff[7] = NumSeg[(buffer.B08[3]&0x0F)]	; 			
			break;

		case 3:
			gs_dis_pixel_var.dis_data_buff[2] = NumSeg[(buffer.B08[0]&0xF0)>>4]	;  
			gs_dis_pixel_var.dis_data_buff[3] = NumSeg[(buffer.B08[0]&0x0F)]	; 
			gs_dis_pixel_var.dis_data_buff[4] = NumSeg[(buffer.B08[1]&0xF0)>>4]	;  
			gs_dis_pixel_var.dis_data_buff[5] = NumSeg[(buffer.B08[1]&0x0F)]	; 
			gs_dis_pixel_var.dis_data_buff[6] = NumSeg[(buffer.B08[2]&0xF0)>>4]	;  
			gs_dis_pixel_var.dis_data_buff[7] = NumSeg[(buffer.B08[2]&0x0F)]	; 
			break;

		case 2:
			gs_dis_pixel_var.dis_data_buff[4] = NumSeg[(buffer.B08[0]&0xF0)>>4]	;  
			gs_dis_pixel_var.dis_data_buff[5] = NumSeg[(buffer.B08[0]&0x0F)]	; 
			gs_dis_pixel_var.dis_data_buff[6] = NumSeg[(buffer.B08[1]&0xF0)>>4]	;  
			gs_dis_pixel_var.dis_data_buff[7] = NumSeg[(buffer.B08[1]&0x0F)]	; 
			break;
		case 1:
			gs_dis_pixel_var.dis_data_buff[6] = NumSeg[(buffer.B08[0]&0xF0)>>4]	;  
			gs_dis_pixel_var.dis_data_buff[7] = NumSeg[(buffer.B08[0]&0x0F)]	; 
			break;
		default:	  // ����Ϊ0 ��ʾ��
			   break;
		 
			
	}
	
			
}
//*****************************************************************
//  Function:       void Link_Get_Dis_Char_buff(void) 
//  Description:    ��ȡ��ʾ������ַ���Ϣ                                      
//  Input:                                                                            
//  Output:         no                              
//  Return:         no                              
//  Others:         
//***************************************************************/
void Link_Get_Dis_Char_buff(void)
{
 	Lib_Set_String(&gs_dis_pixel_var.dis_char_buff[0] ,0,3);
	
	//OBIS ��С������Ż�ȡ  //
	switch(gs_LCDDISTAB_var.obis_digit)
	{
		case OBIS_DIGIT_TYPE1:	 // x.x.x
			gs_dis_pixel_var.dis_char_buff[0] |=CHAR_OBIS_P1+CHAR_OBIS_P2;//+CHAR_OBIS_P3;  S7 S8
			break;
		case OBIS_DIGIT_TYPE2:	// x.x.x.x
			gs_dis_pixel_var.dis_char_buff[0] |=CHAR_OBIS_P1+CHAR_OBIS_P2+CHAR_OBIS_P3;//+CHAR_OBIS_P4;  
			break;
		case OBIS_DIGIT_TYPE3:	// xx.x.x
			gs_dis_pixel_var.dis_char_buff[0] |=CHAR_OBIS_P2+CHAR_OBIS_P3;//+CHAR_OBIS_P4;  
			break;
		case OBIS_DIGIT_TYPE4:	// x.xx.x
			gs_dis_pixel_var.dis_char_buff[0] |=CHAR_OBIS_P1+CHAR_OBIS_P3;//+CHAR_OBIS_P4; 
			break;
		
		case OBIS_DIGIT_TYPE0:
		default:
			break;
	}
	
	// DATA ����С����͵�λ�ַ���ȡ //
	switch(gs_LCDDISTAB_var.chartype)
	{
		case CHAR_AEC:	 // ������ʾ xxxxxx.xx kwh//
			if(gs_dis_param.ec_form !=0x80)// ��λС��
		        {
			    gs_dis_pixel_var.dis_char_buff[1] |= CHAR_DATA_P11;  //
			    gs_dis_pixel_var.dis_char_buff[1] |= CHAR_UNIT_K+CHAR_UNIT_V;  //kv
			    gs_dis_pixel_var.dis_char_buff[2] |= CHAR_UNIT_V2_1+CHAR_UNIT_V2_2+CHAR_UNIT_H;  //vh
		        }
			 else  // 8����
		       {
			     gs_dis_pixel_var.dis_char_buff[1] |= CHAR_UNIT_K+CHAR_UNIT_V;  //kv
			     gs_dis_pixel_var.dis_char_buff[2] |= CHAR_UNIT_V2_1+CHAR_UNIT_V2_2+CHAR_UNIT_H;  //vh
		        }

		     if((gs_LCDDISTAB_var.ObisNum&0x000F) == 0x000F)      //��ǰ������
		     	{
		     	  if( (gs_LCDDISTAB_var.ObisNum&0x00F0)==0)           
				{
				   gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TOTAL ;  // ��ǰ��
		     	  	}
		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0010)   
				 {
				    gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF+CHAR_TARIFF1;  // ��ǰ��
		     	  	}
		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0020)   
				 {
				  	  gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF ;
					  gs_dis_pixel_var.dis_char_buff[1] |= CHAR_TARIFF2;
			        }
		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0030)   
				 {
				  	gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF;  
					gs_dis_pixel_var.dis_char_buff[2] |= CHAR_TARIFF3;
				} // ��ǰ��
		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0040)   
				 {
				    gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF;
				    gs_dis_pixel_var.dis_char_buff[2] |= CHAR_TARIFF4;
				 } // ��ǰ��
			 }
			 else   ////��ʷ��������
			 	{
			 	  if( (gs_LCDDISTAB_var.ObisNum&0x00F0)==0)           
				{
				   gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TOTAL ;  // ��ǰ��
		     	  	}
		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0010)   
				 {
				    gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF+CHAR_TARIFF1;  // ��ǰ��
		     	  	}
		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0020)   
				 {
				  	  gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF ;
					  gs_dis_pixel_var.dis_char_buff[1] |= CHAR_TARIFF2;
			        }
		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0030)   
				 {
				  	gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF;  
					gs_dis_pixel_var.dis_char_buff[2] |= CHAR_TARIFF3;
				} // ��ǰ��
		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0040)   
				 {
				    gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF;
				    gs_dis_pixel_var.dis_char_buff[2] |= CHAR_TARIFF4;
				 } // ��ǰ��
			 	}
		 break;
			
		case CHAR_MD:	 // ������ʾMD  xx.xxxx kw//
			gs_dis_pixel_var.dis_char_buff[0] |= CHAR_DATA_P8;  
			gs_dis_pixel_var.dis_char_buff[1] |= CHAR_CHR_MD+CHAR_UNIT_K+CHAR_UNIT_V;  //kv
			gs_dis_pixel_var.dis_char_buff[2] |= CHAR_UNIT_V2_1+CHAR_UNIT_V2_2;  //vh

			 if((gs_LCDDISTAB_var.ObisNum&0x000F) == 0x000F)      //��ǰ������
		     	{
    		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0)            gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TOTAL ;  // ��ǰ��
    		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0010)   gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF+CHAR_TARIFF1;  // ��ǰ��
    		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0020)   {gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF ; gs_dis_pixel_var.dis_char_buff[1] |= CHAR_TARIFF2;}
    		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0030)   {gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF;  gs_dis_pixel_var.dis_char_buff[2] |= CHAR_TARIFF3;}// ��ǰ��
    		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0040)   {gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF;  gs_dis_pixel_var.dis_char_buff[2] |= CHAR_TARIFF4;} // ��ǰ��
			 }
			 else  //��ʷ��������
			 {
			  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0)            gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TOTAL ;  // ��ǰ��
    		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0010)   gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF+CHAR_TARIFF1;  // ��ǰ��
    		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0020)   {gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF ; gs_dis_pixel_var.dis_char_buff[1] |= CHAR_TARIFF2;}
    		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0030)   {gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF;  gs_dis_pixel_var.dis_char_buff[2] |= CHAR_TARIFF3;}// ��ǰ��
    		     	  if((gs_LCDDISTAB_var.ObisNum&0x00F0)==0x0040)   {gs_dis_pixel_var.dis_char_buff[0] |= CHAR_TARIFF;  gs_dis_pixel_var.dis_char_buff[2] |= CHAR_TARIFF4;} // ��ǰ��
			
			 }

			break;
		case CHAR_V:	// ��ѹ��ʾ xxx.x V//
			gs_dis_pixel_var.dis_char_buff[1] |= CHAR_DATA_P12;  
			gs_dis_pixel_var.dis_char_buff[1] |= CHAR_UNIT_V;  //V
			break;
		case CHAR_A:	// ������ʾ xxx.xxx A//
			gs_dis_pixel_var.dis_char_buff[1] |= CHAR_DATA_P9;  
			gs_dis_pixel_var.dis_char_buff[2] |= CHAR_UNIT_V2_2+CHAR_UNIT_A_1+CHAR_UNIT_A_3;  //A
			break;
		case CHAR_KW:	 // ������ʾ xx.xxxx kw//
			gs_dis_pixel_var.dis_char_buff[0] |= CHAR_DATA_P8;  
			gs_dis_pixel_var.dis_char_buff[1] |= CHAR_UNIT_K+CHAR_UNIT_V;  //kv
			gs_dis_pixel_var.dis_char_buff[2] |= CHAR_UNIT_V2_1+CHAR_UNIT_V2_2;    //v 
			break;
		case CHAR_HZ:	// Ƶ����ʾ xx.xx HZ//
			gs_dis_pixel_var.dis_char_buff[1] |= CHAR_DATA_P11;  //
			gs_dis_pixel_var.dis_char_buff[2] |= CHAR_UNIT_H+CHAR_UNIT_Z;  //V
			break;
			
		case CHAR_TIME:	// ʱ����ʾ HH.MM.SS//			
			gs_dis_pixel_var.dis_char_buff[0] |= CHAR_DATA_P7+CHAR_DATA_P8;  //
			gs_dis_pixel_var.dis_char_buff[1] |= CHAR_DATA_P10+CHAR_DATA_P11;  //
			break;

		case CHAR_DATE:	// ������ʾ DD.MM.YY//
			gs_dis_pixel_var.dis_char_buff[0] |= CHAR_DATA_P8;  //
			gs_dis_pixel_var.dis_char_buff[1] |= CHAR_DATA_P11;  //
			break;

		case CHAR_PF:	// ����������ʾx.xxx  //
			gs_dis_pixel_var.dis_char_buff[1] |= CHAR_DATA_P9;  //
			break;

		case CHAR_SETTL:	// ������ʱ������ʾ xx.xx //
			gs_dis_pixel_var.dis_char_buff[1] |= CHAR_DATA_P11;  //
			break;
			
		default:
			break;
	}	
	
			
}

//*****************************************************************
//  Function:       INT8U Link_Get_DisIndex(u8_dis_itm)        
//  Description:    ��ȡ��ʾ��Ŀ��Ϣ                                        
//  Input:                                                                            
//  Output:         no                              
//  Return:         no                              
//  Others:         
//***************************************************************/
void Link_Get_Dis_RealChar_buff(void)
{
	if((gs_measure_status_judge_var.u8_status &VBAT_LOW) != 0)            gs_dis_pixel_var.dis_buff[19] |= BIT1;	//���Ƿѹ
      // if()          gs_dis_pixel_var.dis_buff[1] |= BIT0;	//����
	if(TARIFF_MAX_NUM>1)
	{
		switch(gs_current_triff_var.triff_No)
		{
			case 1:
				gs_dis_pixel_var.dis_buff[0] |= BIT1;
				break;
			case 2:
				gs_dis_pixel_var.dis_buff[1] |= BIT2;
				break;
			case 3:
				gs_dis_pixel_var.dis_buff[0] |= BIT0;
				break;
			case 4:
				gs_dis_pixel_var.dis_buff[1] |= BIT1;
				break;
			default:
				gs_current_triff_var.triff_No = 1;
			       gs_dis_pixel_var.dis_buff[0] |= BIT1;
			      break;
		}
	 }




}


//*****************************************************************
//  Function:      void Link_Get_Dis_Drv_buff(void)   
//  Description:    ��ȡ��ʾ����buff������                                    
//  Input:                                                                            
//  Output:         no                              
//  Return:         no                              
//  Others:         
//***************************************************************/
void Link_Get_Dis_Drv_buff(void)
{

	
 //  dis_var.dis_obis_buff[0:3] ��ת��//
       // ��һ��8
  	gs_dis_pixel_var.dis_buff[2] |= (gs_dis_pixel_var.dis_obis_buff[0] &(BIT0+BIT1));
       gs_dis_pixel_var.dis_buff[3] |= ((gs_dis_pixel_var.dis_obis_buff[0] &(BIT2+BIT3))>>2);
	gs_dis_pixel_var.dis_buff[4] |= ((gs_dis_pixel_var.dis_obis_buff[0] &(BIT4+BIT5))>>4);
	gs_dis_pixel_var.dis_buff[5] |= ((gs_dis_pixel_var.dis_obis_buff[0] &(BIT6))>>6);
  	gs_dis_pixel_var.dis_buff[6] |= (gs_dis_pixel_var.dis_obis_buff[1] &(BIT0+BIT1));
       gs_dis_pixel_var.dis_buff[7] |= ((gs_dis_pixel_var.dis_obis_buff[1] &(BIT2+BIT3))>>2);
	gs_dis_pixel_var.dis_buff[8] |= ((gs_dis_pixel_var.dis_obis_buff[1] &(BIT4+BIT5))>>4);
	gs_dis_pixel_var.dis_buff[9] |= ((gs_dis_pixel_var.dis_obis_buff[1] &(BIT6))>>6);
	gs_dis_pixel_var.dis_buff[10] |= (gs_dis_pixel_var.dis_obis_buff[2] &(BIT0+BIT1));
       gs_dis_pixel_var.dis_buff[11] |= ((gs_dis_pixel_var.dis_obis_buff[2] &(BIT2+BIT3))>>2);
	gs_dis_pixel_var.dis_buff[12] |= ((gs_dis_pixel_var.dis_obis_buff[2] &(BIT4+BIT5))>>4);
	gs_dis_pixel_var.dis_buff[13] |= ((gs_dis_pixel_var.dis_obis_buff[2] &(BIT6))>>6);
   // ���ĸ�8
	gs_dis_pixel_var.dis_buff[14] |= (gs_dis_pixel_var.dis_obis_buff[3] &(BIT0+BIT1));
       gs_dis_pixel_var.dis_buff[15] |= ((gs_dis_pixel_var.dis_obis_buff[3] &(BIT2+BIT3))>>2);
	gs_dis_pixel_var.dis_buff[19] |= ((gs_dis_pixel_var.dis_obis_buff[3] &(BIT4))>>4);
	gs_dis_pixel_var.dis_buff[20] |= ((gs_dis_pixel_var.dis_obis_buff[3] &(BIT6+BIT7))>>6);


	 

  
	 //  dis_var.dis_data_buff[0:7] ��ת��//
	gs_dis_pixel_var.dis_buff[0] |= ((gs_dis_pixel_var.dis_data_buff[0] &0x0F)<<2);
	gs_dis_pixel_var.dis_buff[1] |= ((gs_dis_pixel_var.dis_data_buff[0] &0xF0)>>2);
	gs_dis_pixel_var.dis_buff[2] |= ((gs_dis_pixel_var.dis_data_buff[1] &0x0F)<<2);
	gs_dis_pixel_var.dis_buff[3] |= ((gs_dis_pixel_var.dis_data_buff[1] &0xF0)>>2);
	gs_dis_pixel_var.dis_buff[4] |= ((gs_dis_pixel_var.dis_data_buff[2] &0x0F)<<2);
	gs_dis_pixel_var.dis_buff[5] |= ((gs_dis_pixel_var.dis_data_buff[2] &0xF0)>>2);
	gs_dis_pixel_var.dis_buff[6] |= ((gs_dis_pixel_var.dis_data_buff[3] &0x0F)<<2);
	gs_dis_pixel_var.dis_buff[7] |= ((gs_dis_pixel_var.dis_data_buff[3] &0xF0)>>2);
	gs_dis_pixel_var.dis_buff[8] |= ((gs_dis_pixel_var.dis_data_buff[4] &0x0F)<<2);
	gs_dis_pixel_var.dis_buff[9] |= ((gs_dis_pixel_var.dis_data_buff[4] &0xF0)>>2);
	gs_dis_pixel_var.dis_buff[10] |= ((gs_dis_pixel_var.dis_data_buff[5] &0x0F)<<2);
	gs_dis_pixel_var.dis_buff[11] |= ((gs_dis_pixel_var.dis_data_buff[5] &0xF0)>>2);
	gs_dis_pixel_var.dis_buff[12] |= ((gs_dis_pixel_var.dis_data_buff[6] &0x0F)<<2);
	gs_dis_pixel_var.dis_buff[13] |= ((gs_dis_pixel_var.dis_data_buff[6] &0xF0)>>2);
	gs_dis_pixel_var.dis_buff[14] |= ((gs_dis_pixel_var.dis_data_buff[7] &0x0F)<<2);
	gs_dis_pixel_var.dis_buff[15] |= ((gs_dis_pixel_var.dis_data_buff[7] &0xF0)>>2);



	 //  dis_var.dis_char_buff[0:2] ��ת��//
	 if(gs_dis_pixel_var.dis_char_buff[0] &CHAR_OBIS_P1)   	gs_dis_pixel_var.dis_buff[5] |= BIT1;
	 if(gs_dis_pixel_var.dis_char_buff[0] &CHAR_OBIS_P2)   	gs_dis_pixel_var.dis_buff[9] |= BIT1;
	 if(gs_dis_pixel_var.dis_char_buff[0] &CHAR_OBIS_P3)   	gs_dis_pixel_var.dis_buff[13] |= BIT1; 
       if(gs_dis_pixel_var.dis_char_buff[0] & CHAR_TOTAL)          gs_dis_pixel_var.dis_buff[18] |= BIT3;
       if(gs_dis_pixel_var.dis_char_buff[0] & CHAR_TARIFF)         gs_dis_pixel_var.dis_buff[18] |= BIT5;
       if(gs_dis_pixel_var.dis_char_buff[0] & CHAR_TARIFF1)        gs_dis_pixel_var.dis_buff[17] |= BIT5;
	 if(gs_dis_pixel_var.dis_char_buff[0] &CHAR_DATA_P7)   	gs_dis_pixel_var.dis_buff[5] |= BIT2;
	 if(gs_dis_pixel_var.dis_char_buff[0] &CHAR_DATA_P8)   	gs_dis_pixel_var.dis_buff[7] |= BIT2;

	 if(gs_dis_pixel_var.dis_char_buff[1] &CHAR_DATA_P9)   	gs_dis_pixel_var.dis_buff[9] |= BIT2;
	 if(gs_dis_pixel_var.dis_char_buff[1] &CHAR_DATA_P10)   	gs_dis_pixel_var.dis_buff[20] |= BIT5;
	 if(gs_dis_pixel_var.dis_char_buff[1] &CHAR_DATA_P11)   	gs_dis_pixel_var.dis_buff[11] |= BIT2;
	 if(gs_dis_pixel_var.dis_char_buff[1] &CHAR_DATA_P12)   	gs_dis_pixel_var.dis_buff[13] |= BIT2;
	 if(gs_dis_pixel_var.dis_char_buff[1] &CHAR_CHR_MD)   	     gs_dis_pixel_var.dis_buff[18] |= BIT4;  
         if(gs_dis_pixel_var.dis_char_buff[1] & CHAR_TARIFF2)        gs_dis_pixel_var.dis_buff[17] |= BIT4;
	 if(gs_dis_pixel_var.dis_char_buff[1] &CHAR_UNIT_K)   	      gs_dis_pixel_var.dis_buff[18] |= BIT2;
	 if(gs_dis_pixel_var.dis_char_buff[1] &CHAR_UNIT_V)		gs_dis_pixel_var.dis_buff[18] |= BIT0;

	 if(gs_dis_pixel_var.dis_char_buff[2] &CHAR_UNIT_V2_1)   	gs_dis_pixel_var.dis_buff[18] |= BIT1;
	 if(gs_dis_pixel_var.dis_char_buff[2] &CHAR_UNIT_V2_2)   	gs_dis_pixel_var.dis_buff[16] |= BIT1;
	 if(gs_dis_pixel_var.dis_char_buff[2] &CHAR_UNIT_A_1)   	gs_dis_pixel_var.dis_buff[15] |= BIT2;
         if(gs_dis_pixel_var.dis_char_buff[2] & CHAR_TARIFF3)        gs_dis_pixel_var.dis_buff[17] |= BIT3;
	 if(gs_dis_pixel_var.dis_char_buff[2] &CHAR_UNIT_A_3)   	 gs_dis_pixel_var.dis_buff[16] |= BIT2;
         if(gs_dis_pixel_var.dis_char_buff[2] & CHAR_TARIFF4)        gs_dis_pixel_var.dis_buff[17] |= BIT2;	 
	  if(gs_dis_pixel_var.dis_char_buff[2] &CHAR_UNIT_H)   	       gs_dis_pixel_var.dis_buff[16] |= BIT4;
        if(gs_dis_pixel_var.dis_char_buff[2] &CHAR_UNIT_Z)		 gs_dis_pixel_var.dis_buff[16] |= BIT5;


}





/*****************************************************************************
** Function name    :api_clr_current_energy_data
**
** Description         : ������������ת��
**
** Parameters         :  type ��������     0Ĭ��ȫ���� 
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_get_energy_LCD(uint8*  temp, uint8 type, uint8*  result)
{
 ST_U32_U08   u32_result, BCD_temp;
 INT8U  i;
 US_EC_DATA_UNIT ec_tmp;
   
     if(type!=0x80)     type= 0x62;
    //������ʽ���ݸ�ֵ //
    Lib_Copy_Str_TwoArry(&ec_tmp.buf[0], temp, LEN_EC_UNIT);
    u32_result.u32 =0;
    if(type==0x80)
    {
        if(ec_tmp.val.integ_hex32>=100000000)   ec_tmp.val.integ_hex32 -=100000000;
        Lib_long_bcd4(&u32_result.B08[0],ec_tmp.val.integ_hex32);       
    }
    
    if(type==0x62)
    {
        // �������ִ��� //
        if(ec_tmp.val.integ_hex32>=1000000)   ec_tmp.val.integ_hex32 -=1000000;
        Lib_long_bcd4(&BCD_temp.B08[0],ec_tmp.val.integ_hex32);
        u32_result.B08[0]= BCD_temp.B08[1];
        u32_result.B08[1]= BCD_temp.B08[2];
        u32_result.B08[2]= BCD_temp.B08[3];

         // С�����ִ��� //
         ec_tmp.val.decim_hex16  /= METER_CONST_10WH;
         u32_result.B08[3] = Lib_byte_bcd((INT8U)ec_tmp.val.decim_hex16);

    }
 
    //������� //
    Lib_Copy_Str_TwoArry(result, &u32_result.B08[0], 4);

}



/*****************************************************************************
** Function name    :api_init_md_data_ram
**
** Description         :ÿ�����Һ����ʾ��Ŀ       
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_chg_LCDDisplay_adj_item(uint8 u8_item)
{
    if((u8_item>=DIS_ADJ_CH1_0) &&(u8_item<=DIS_DATA_CLR))
    {
        //����У׼��ʾ��Ŀ//
        gs_dis_ctl_var.mode = DIS_MODE_NOMAL;
        gs_dis_ctl_var.keep_sec[0] = 5;    //ǿ����ʾ5�� //
        gs_dis_ctl_var.ptr[0] = 0;
        gs_dis_ctl_var.item = u8_item;    
    }
    else
    {
        //�쳣�������ʾ�Զ�ѭ����Ŀ //
        gs_dis_ctl_var.mode = DIS_MODE_NOMAL;
        gs_dis_ctl_var.keep_sec[0] = gs_dis_param.auto_sec;
        gs_dis_ctl_var.ptr[0] = 0;
        gs_dis_ctl_var.item = gs_dis_param.auto_item[gs_dis_ctl_var.ptr[0]+1];  //  0λ��Ϊ��ʾ��Ŀ������1λ�ÿ�ʼΪ��Ŀ //  
    }

    api_updated_LCDDisplayPixel_per_second();
}

/*****************************************************************************
** Function name    :api_init_md_data_ram
**
** Description         :ÿ�����Һ����ʾ��Ŀ       
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_LCDDisplay_adj_item(uint8 u8_item)
{
    if((u8_item<DIS_ADJ_CH1_0) &&(u8_item>DIS_DATA_CLR))
    {
        return;
    }

    Lib_Set_String(&gs_dis_pixel_var.dis_data_buff[0],0,DS_DATANum);	
    Lib_Set_String(&gs_dis_pixel_var.dis_obis_buff[0],0,DS_OBISNum);
    Lib_Set_String(&gs_dis_pixel_var.dis_char_buff[0] ,0,DS_CHARNum);

    // ���ݻ�ȡ����  //
    switch (u8_item)
    {
        case DIS_ADJ_CH1_0:	//L ��·У�������ʼ�� //
        case DIS_ADJ_CH1_1:	//L ��·У�������ʼ�� //
        case DIS_ADJ_CH1_2:	//L ��·У�������ʼ�� //
        case DIS_ADJ_CH1_3:	//L ��·У�������ʼ�� //
            gs_dis_pixel_var.dis_data_buff[0] = NumSeg[0X0C]	;      //LCD-D1  C  //
            gs_dis_pixel_var.dis_data_buff[1] = 0XE6	;                                //LCD-D2  H  //
            gs_dis_pixel_var.dis_data_buff[2] = NumSeg[0X01]	;     //LCD-D3  1  //
            gs_dis_pixel_var.dis_data_buff[3] = 0X40	; 	                          //LCD-D4  -//
            gs_dis_pixel_var.dis_data_buff[4] = NumSeg[(u8_item&0X0F)]	;     //LCD-D5  0~3  //
        break;

        case DIS_ADJ_CH2_0:	//L ��·У�������ʼ�� //
        case DIS_ADJ_CH2_1:	//L ��·У�������ʼ�� //
        case DIS_ADJ_CH2_2:	//L ��·У�������ʼ�� //
        case DIS_ADJ_CH2_3:	//L ��·У�������ʼ�� //
            gs_dis_pixel_var.dis_data_buff[0] = NumSeg[0X0C]	;      //LCD-D1  C  //
            gs_dis_pixel_var.dis_data_buff[1] = 0XE6	;                                //LCD-D2  H  //
            gs_dis_pixel_var.dis_data_buff[2] = NumSeg[0X02]	;     //LCD-D3  2  //
            gs_dis_pixel_var.dis_data_buff[3] = 0X40	; 	                          //LCD-D4  -//
            gs_dis_pixel_var.dis_data_buff[4] = NumSeg[(u8_item&0X0F)-4]	;     //LCD-D5  0~3  //
        break;

        case DIS_DATA_CLR:	//L ��·У�������ʼ�� //
            gs_dis_pixel_var.dis_data_buff[0] = NumSeg[0X0C]	;      //LCD-D1  C  //
            gs_dis_pixel_var.dis_data_buff[1] = 0X07	;                                //LCD-D2  L  //
            gs_dis_pixel_var.dis_data_buff[2] = 0x42	;                               //LCD-D3  r  //
        break;

        default:	
            sys_err();
        break;
    }
 
}

/***************************************************************
*    END
****************************************************************/


