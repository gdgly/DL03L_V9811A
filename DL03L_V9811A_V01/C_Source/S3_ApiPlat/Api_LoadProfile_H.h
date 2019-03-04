/*******************************************************************
*
*  FILE             :                                        
*  DATE            :                                  
*  DESCRIPTION :                    
*  CPU GROUP    :R8C,002                                                   
*                                                                  
*
*******************************************************************/
//#ifndef _Api_LoadProfile_H
//#define _Api_LoadProfile_H


//******************************************************************
//              1     ������Ԥ����                                            //                      
//******************************************************************


#define  FUNC_LoadPro 1
#define  ReaEC	      0     // �޹���������

#define	DEBUG_TEST    0 

//------------------------------------------------------------------------------
#define MaxLPReg	9//�Ĵ���������
#define MaxLPCh		1//ͨ�������
#define LP_RunPara_Len	4	//���в���
#define LP_E2P		1//=1��E2P�洢��=0��Ĭ����Flash




#define LP_MAX_LEN	2895//1455 	  //��¼�������ߵ�������� ��ֹ���չ���β��ˢ��


#define READLP_MAX_LEN	2880//1440 	  //��ȡ�������ߵ��������  ���ɼ�¼15���Ӽ�� 15��

#define FALSE_ERR 0xFF

#define BLOCK_MAX_LEN  5         //���ɼ�¼���������    ����֡����½��鲻Ҫ����5��

#define LPDataType 0xFF00
//��ص���
#define LPECType   0xF00//1111'0000'0000
#define LPECTypeBs 0x100
#define LPEC	   LPECTypeBs*(0+1)	
#define LPRevEC	   LPECTypeBs*(No_RevEC+1)
#define LPReaEC	   LPECTypeBs*(No_ReaEC+1)

#define CLPRegNum  (sizeof(LPReg)/sizeof(LPREG))

typedef struct
{
    INT8U	Code;	
    INT8U	*Reg;    // �Ĵ���������Դ��ָ��
    INT8U	DataLen; // ���ݳ���
    INT16U	Info; // ��Ϣ
} LPREG;

typedef struct
{
    INT8U 	Ch;//ͨ����//��0��ʼ
    INT16U	Ptr;//��ָ��(��ǰͨ����)
    INT8U	RegNum;	// �Ĵ����������
    INT16U	MaxRecNum;	//�̶�����������������õļ�¼���룬�ó����������
    INT8U	loadp_reg_code[1+9]; // ��һ�ֽڼĴ������볤��  
}LPREAD;

typedef struct
{
    INT16U	Ptr[MaxLPCh];
    INT16U	Num[MaxLPCh];
}LPRUNPARA;
typedef struct
{
    INT16U	Original_Ptr;
    INT16U	Original_FrameNum;
//	  INT8U FrameACK;
	  INT8U ReadLoraFlag;
}LPReadPRO;

////////////////////////////////////////////////////////////////////�ӿ�����
extern LPREAD	   LPRd;            //���ɼ�¼�洢��Ϣ
extern LPRUNPARA   LPRunPa;         //���ɼ�¼����
extern LPReadPRO  LPReadPara;

extern uchar ReadLPRunPa(void);  //��ȡ���ɼ�¼����
extern void LoadProRst(void);    //��λ���ɱ�
extern uchar LPRec_Read(void);   //�����ɱ�����
extern char Load_Rec(char Ch);   //�ֶ���¼��������
extern void LoadPro_Rec(void);
extern uchar LPRec_Read_1(INT8U *dst,INT16U idNo);
extern INT16U LPRec_Read_Block(INT8U *dst,INT16U StartARESS,INT16U EndARESS);
extern void Init_LoadPro_param(void);



