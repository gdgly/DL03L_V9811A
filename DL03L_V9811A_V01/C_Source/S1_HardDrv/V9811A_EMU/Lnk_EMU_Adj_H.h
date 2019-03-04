/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Lnk_EMU_Adj_H.H
**Author		: maji
**date			: 2016-05-09 
**description	: G80F92XD��EMU����ģ����·��У����C����������ļ�
**note			: MCU- G80F92XD ��MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-05-09   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#ifndef _Lnk_EMU_Adj_H
#define _Lnk_EMU_Adj_H

/***************************************************************
*    1     ������Ԥ����   
****************************************************************/
// �Զ�У��������������//
#define HARD_EADJ_STEP0_L_INITLIZE    0  // ���ص���У׼  //
#define HARD_EADJ_STEP1_L_100IB_100L    1  // ���ص���У׼  //
#define HARD_EADJ_STEP2_L_100IB_50L    2  // ���ص���У׼  //
#define HARD_EADJ_STEP3_L_5IB_100L    3  // ���ص���У׼  //
#define HARD_EADJ_STEP4_N_INITLIZE    4  // ���ص���У׼  //
#define HARD_EADJ_STEP5_N_100IB_100L    5  // ���ص���У׼  //
#define HARD_EADJ_STEP6_N_100IB_50L    6  // ���ص���У׼  //
#define HARD_EADJ_STEP7_N_5IB_100L    7  // ���ص���У׼  //
#define HARD_EADJ_STEP8_METER_CLR    8  // ������㴦��//

// ����У׼��ز������ο������ĵ��м������ڵ����ݽ��и�ֵ //
#define INITGATECP 		0x5FFFFFFF     // ����EMU�ķ�Ǳ���ܽ��п��� //
#define INITGATECQ 		INITGATECP     // ����EMU�ķ�Ǳ���ܽ��п��� //

#define INITGATEP  		57428838      //E1���� ���������ֲ�ļ�����������*0.9  //
#define INITGATEQ  		INITGATEP    //E2����=  E1���� //
#define REF_RMSPn           9392805L       //���ѹ�ͻ�����������й���������ֵ //  
#define REF_RMSIAb         86961600L       //����ͨ��A�������10A��IA RMS ֵ����Դ�������Ŀ�ļ����� //  
#define REF_RMSIBb         108702000L       //����ͨ��B�������10A��IA RMS ֵ����Դ�������Ŀ�ļ����� //  
#define K_RMSP                0.002448683f       //������Чֵ����ϵ��������0.1w���ټ��� //  
#define REF_START_Pn         ((uint32) (REF_RMSPn*0.001f))       //��������0.001 �Ļ����㹦�ʱ�׼ֵ //  
#define REF_DLX_START_IA        ((uint32) (REF_RMSIAb/20L))       //����ͨ��A�����������жϵ�0.5A //  
#define REF_DLX_START_IB        ((uint32) (REF_RMSIBb/20L))       //����ͨ��B�����������жϵ�0.5A //  



/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
typedef struct
{
    uint32 w1gain;         //ͨ��1��������Ĵ���(�й��޹�ʹ��ͬһ��)  //
    uint32 p1cal;           //ͨ��1��ѹ������λ�����Ĵ���  //
    uint32 watt1os;      //ͨ��1�й�����ƫ��  //
    uint32 irms1os;      //ͨ��1������Чֵƫ��  //
    uint32 w2gain;         //ͨ��2��������Ĵ���(�й��޹�ʹ��ͬһ��)  //
    uint32 p2cal;           //ͨ��2��ѹ������λ�����Ĵ���  //
    uint32 watt2os;      //ͨ��2�й�����ƫ��  //
    uint32 irms2os;      //ͨ��2������Чֵƫ��  //
    float vconst_val_ch1;   //ͨ��1�����ߵ�ѹ�̶�ֵ //    
    float vconst_val_ch2;   //ͨ��2�����ߵ�ѹ�̶�ֵ //
    float vrms_xs;          //��Ϊ����ĵ�ѹ��Чֵϵ��  //
    float i1rms_xs;         //��Ϊ�����ͨ��1������Чֵϵ��  //
    float i2rms_xs;         //��Ϊ�����ͨ��2������Чֵϵ��  //
    uint16     csck;  //У��� //
}ST_EMU_ADJ_PARAM;


typedef struct
{
    uint32 U_ref;       //�αȵ�ѹֵ������0.1V  // 
    uint32 I_ref;       //�αȵ���ֵ������0.001A  //     
    uint32 C_GATEP;    // ��������ֵ //
    uint32 C_GATECP;   // Ǳ������ֵ //
    uint32 C_PCONST;   // ����ʵ�У׼���׼ֵ//
    float   Kim_Prms;          //�й�������Чֵϵ��//   
}ST_Adjust_CONST;

typedef struct 
{
    uint8   sec_flg;  //У׼�����е���仯��ʶ//
    uint8   adj_flg;  //У�����״̬��=0X55����У������� //
} ST_EMU_ADJ_VAR;


typedef struct 
{
    uint32   *ramAdr;                            //������ַ //
    uint16    emuAdr;                            //�Ĵ�����ַ //
}EMU_CK_TAB;   

typedef struct 
{
    uint32   val;                               //��������//
    uint16    emuAdr;                      //�Ĵ�����ַ //
}EMU_CONST_CK_TAB;   

/***************************************************************
*    3    ��������       
****************************************************************/
extern const  ST_EMU_ADJ_PARAM  code   default_adj_emu_param_tab;
extern const  ST_Adjust_CONST  code   cst_adj_const;
extern const  EMU_CK_TAB  code   cst_emu_selfchck_tab[];
extern const  EMU_CONST_CK_TAB  code   cst_emu_constchck_tab[];

extern ST_EMU_ADJ_PARAM  gs_adj_emu_param;
extern ST_EMU_ADJ_VAR      gs_emu_adj_var;



/***************************************************************
*    4     ��������        
****************************************************************/
extern void Get_EMU_AdjParam(void);
extern void Check_EMU_AdjParam(void);
extern void Hardware_AdjustDiv_Sub(void);
extern void Save_EMU_AdjParam(void);

/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/



/***************************************************************
*    END
****************************************************************/
#endif
