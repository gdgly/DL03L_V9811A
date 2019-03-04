/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Prco_Data_H.H
**Author		: maji
**date			: 2016-04-26
**description	: ϵͳ������ݴ���C�ļ�
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/



#ifndef _PROC_DATA_H
#define _PROC_DATA_H

/***************************************************************
*    1     ������Ԥ����   
****************************************************************/


/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
typedef struct 
{	
	INT8U	back_fg;                     // �ж��γɱ�ʶ //
	INT8U	font_fg;                     // ����������в�����ʶ //
} SYS_RUN_STATUS;


typedef struct 
{	
    INT8U	 reset_status;                     // ϵͳ��λ��ʶ�� //
    INT8U  work_mode;             // ϵͳ��Դ��ʶ //
    INT8U  delay_emu;                    // EMU �ȶ�ʱ�䣬��ʼ��ֵ=2�� //
    INT8U  gs_check_err_status;   //У��״̬��  //
    INT8U  gs_hard_err_status;   //Ӳ��״̬��//
    INT8U  gs_net_status;             //����״̬��//
    INT8U  meter_factory_status;     //�����״̬��=0x5A�����ڹ���״̬//
} SYS_GLOBAL_VAR;

typedef struct  
{
     INT8U      meter_cons[3];           //�����//
     INT8U      video[12];               //����汾��12���ֽ�ASCII��//
}SYS_PARM;





typedef struct 
{
    MD_PARAM                                md_param;
    BILL_MONTH_SETTLED_PARAM     bill_ms_param; 
    INT8U   EMU_fast_flg;  //EMU �ӱ���ʶ=0x3c Ϊ�ӱ�������Ϊ���� //
    INT8U   meter_id[16];
    INT8U   password[2][4];   //  2 ������ //
    INT8U   fac_cfg[4];          //  ������Ϣ������//
    INT8U   bat_level[2];          //  ��ص�ѹ��ֵ//
    INT8U   baoliu[32];
    
	  INT16U   load_Ptr_var;
    INT16U   load_Num_var;
    INT16U   load_lptime_inv_var;     //��ͨ����¼ʱ������Min��  	2       BCD  XXXX     
    INT8U    load_egcode_var[10];  // ���Ĵ�������(1+9)   			10      BCD  XXXX         ��һ��λ���� 
      
    INT16U  param1_csck;    //16λ�ۼӺ�У��ֵ//
} E2P_METER_PARAM1_MAP;

typedef struct 
{
    RTC_TYPE  save_rtc;  //�µ籣���ʱ�� //
    INT16U  var_csck;    //16λ�ۼӺ�У��ֵ//
} E2P_METER_VAR_MAP;


/***************************************************************
*    3    ��������       
****************************************************************/
extern SYS_RUN_STATUS  gs_sys_run;
extern SYS_GLOBAL_VAR gs_sys_globaL_var;

//������ //
extern const  E2P_METER_PARAM1_MAP  code   default_meter_parm1_tab;
extern const SYS_PARM code sys_parm;
/***************************************************************
*    4     ��������        
****************************************************************/
extern void Proc_sys_data_init(void);
extern void Proc_clr_meter(void);

/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/
//  gs_sys_globaL_var.work_mode define 
#define      NORMAL_MODE                0    //�е繩Ӧ״̬ //
#define      DLX_MODE                       1    // �����߹���״̬//
#define      CONST_MODE                   2   // ������������״̬//   
#define      SLEEP_MODE                    3   // �͹������߹���״̬//   

//  gs_sys_globaL_var.meter_factory_status define 
#define  METER_FACTORY_MARK      0x5A     // =0X5A �����ڹ���״̬//

//  gs_sys_run.back_fg define 
#define  BIT0_FONT_FG_10MS   BIT0   // 10ms �жϲ�����ʶ //
#define  BIT1_BACK_FG_RTC   BIT1   // RTC������1S�жϱ�ʶ //
#define  BIT2_BACK_DIS_KEY   BIT2   // ��ʾ�����������жϱ�ʶ //


/***************************************************************
*    END
****************************************************************/

#endif
