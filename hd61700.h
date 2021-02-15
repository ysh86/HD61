/********************************************************************/
/*                                                                  */
/*  NAME : HD61700 ASSEMBLER HEADDER CODE                           */
/*  FILE : hd61700.h                                                */
/*                                                                  */
/*  REVISION HISTORY:                                               */
/*  Rev : 0.01 2003.01.06  �ŏ��̃o�[�W����                         */
/*  Rev : 0.03 2003.01.09  ����`���߂�ǉ�                         */
/*  Rev : 0.04 2003.01.16  ����`���߂�ǉ�                         */
/*  Rev : 0.05 2003.01.18  ����`���߂�ǉ�                         */
/*  Rev : 0.07 2003.02.02  �I�y�R�[�h0x0�`0xf�0x80�`0x8f�ɑ΂���    */
/*                         Jump�g�����C�l�[�u���Ƃ����B             */
/*  Rev : 0.08 2003.02.06  ���Z���̃G���[���b�Z�[�W�ǉ�             */
/*             2003.02.07  OutTbl�\���̂��C��                       */
/*             2003.02.09  ���ߌ�T�|�[�g�ǉ�                       */
/*  Rev : 0.10 2003.02.21  �G���[���b�Z�[�W�ǉ�/�C��                */
/*                         ���߃R�[�h(0xDA,0xDB)�ɑ΂���Jump�g����  */
/*                         ����                                     */
/*  Rev : 0.12 2003.02.28  ���x�������ő�16�o�C�g�Ƃ���             */
/*  Rev : 0.13 2003.03.04  ���ߌ�ǉ��B                             */
/*  Rev : 0.14 2003.03.05  �������W�X�^/�t���O�e�[�u���ǉ�          */
/*  Rev : 0.15 2003.03.07  ���ߌ�ǉ�                               */
/*  Rev : 0.16 2003.03.14  ���ߌ�ǉ�                               */
/*  Rev : 0.19 2003.04.09  JR �}IM7�`���̃T�|�[�g                   */
/*  Rev : 0.20 2003.04.22  �G���[�R�[�h/���b�Z�[�W�ǉ�              */
/*  Rev : 0.21 2003.04.25  PST TS,xx,GST TS,$ ��ǉ��B              */
/*  Rev : 0.22 2003.04.26  ���߃R�[�h(0xD2�`0xDB)��Jump�g�����֎~   */
/*                          (DIDM,DIUM,BYDM,BYUM,INVM,CMPM)         */
/*  Rev : 0.23 2003.05.15  /SET�I�v�V�����p�\���̂�ǉ�             */
/*                                                                  */
/********************************************************************/

/*------------------------------------------------------------------*/
/*  �萔��`                                                        */
/*------------------------------------------------------------------*/
#define		MAXNAME		16			/* ���x���ő咷                 */
#define		MAXLEN		256			/* �I�y�����h�ő咷             */
#define		MAXOPR		128			/* �I�y�����h����               */
#define		MAXOBJ		65536		/* �ő�t�@�C���T�C�Y           */
#define		FILEEND		2			/* �t�@�C���I��                 */
#define		MAXLINE		256			/* �P�s�ő�o�C�g��             */
#define		MAXINC		256			/* �ő�C���N���[�h�l�X�g��     */
#define		MAXOPT		8			/* �R�}���h���C���I�v�V������   */
/*------------------------------------------------------------------*/
/*  ���x������`                                                  */
/*------------------------------------------------------------------*/
#define		LBLMASK		0x000f		/* ���x����ʃ}�X�N�l           */

/*------------------------------------------------------------------*/
/*  ���W�X�^�^�I�y�����h��ʒ�`�i��P�A��Q�I�y�����h���p�j        */
/*------------------------------------------------------------------*/
#define		MASKOP		0xff88		/* �I�y�����h�����p�}�X�N�l     */
#define		MASKOP2		0xfff8		/* �I�y�����h�����p�}�X�N�l     */

#define		IM3			0x0008		/* �C�~�f�B�G�C�g�w��(3bit)     */
#define		IM5			0x0009		/* �C�~�f�B�G�C�g�w��(5bit)     */
#define		IM7			0x000a		/* �C�~�f�B�G�C�g�w��(7bit)     */
#define		IM8			0x000b		/* �C�~�f�B�G�C�g�w��(8bit)     */
#define		IM16		0x000c		/* �C�~�f�B�G�C�g�w��(16bit)    */
#define		LBLOK		0x000d		/* ��ʃ��x�� �A�h���X�����ς�  */
#define		LBLNG		0x000e		/* ��ʃ��x�� �A�h���X������    */
#define		REG			0x0080		/* ���W�X�^�w�� $0�`$31         */
#define		R00			0x0090		/* ���W�X�^�w�� $0              */
#define		R30			0x00a0		/* ���W�X�^�w�� $30             */
#define		R31			0x00b0		/* ���W�X�^�w�� $31             */
#define		MREG		0x0100		/* �C���f�b�N�X�w��($1)�`($31)  */
#define		MR00		0x0110		/* �C���f�b�N�X�w��($0)         */
#define		MR30		0x0120		/* �C���f�b�N�X�w��($30)        */
#define		MR31		0x0130		/* �C���f�b�N�X�w��($31)        */
#define		MIX_p		0x0200		/* �C���f�b�N�X�w��(IX+  )      */
#define		MIX_m		0x0300		/* �C���f�b�N�X�w��(IX-  )      */
#define		MIZ_p		0x0400		/* �C���f�b�N�X�w��(IZ+  )      */
#define		MIZ_m		0x0500		/* �C���f�b�N�X�w��(IZ-  )      */

/*------------------------------------------------------------------*/
/*  ���W�X�^�^�I�y�����h��ʒ�`(��P�I�y�����h�̂�)                */
/*------------------------------------------------------------------*/
#define		PE			0x0600		/* PE ���W�X�^                  */
#define		PD			0x0700		/* PD ���W�X�^                  */
#define		TS			0x0800		/* TS ���W�X�^                  */
#define		UA			0x0900		/* UA ���W�X�^                  */
#define		IA			0x0a00		/* IA ���W�X�^                  */
#define		IE			0x0b00		/* IE ���W�X�^                  */
#define		TM			0x0c00		/* TM ���W�X�^                  */
#define		KY			0x0d00		/* KY ���W�X�^                  */
#define		US			0x0e00		/* US ���W�X�^                  */
#define		SS			0x0f00		/* SS ���W�X�^                  */
#define		IX			0x1000		/* IX ���W�X�^                  */
#define		IY			0x1100		/* IY ���W�X�^                  */
#define		IZ			0x1200		/* IZ ���W�X�^                  */
#define		S0			0x1300		/* S0 ���W�X�^                  */
#define		S1			0x1400		/* S1 ���W�X�^                  */
#define		S2			0x1500		/* S2 ���W�X�^                  */

#define		ZF			0x1500		/* Z  �t���O                    */
#define		LZF			0x1600		/* LZ �t���O                    */
#define		UZF			0x1700		/* UZ �t���O                    */
#define		NZF			0x1800		/* NZ �t���O                    */
#define		CF			0x1900		/* C  �t���O                    */
#define		NCF			0x1a00		/* NC �t���O                    */
#define		NLZF		0x1b00		/* NLZ �t���O                   */

/*------------------------------------------------------------------*/
/*  ���ߎ�ʒ�`�i�I�y���[�V������ʔ��ʗp�j                        */
/*------------------------------------------------------------------*/
#define		NU			0x0			/* �I�y�����h�Ȃ��^1 byte ����  */
#define		REG_NU		0x1			/* REG        (�Q�o�C�g���߁j   */
#define		REG_NUJ		0x2			/* REG        (�R�o�C�g���߁j   */
#define		IR_REG		0x3			/* IREG�FREG  (�Q�o�C�g)        */
#define		IR_REGJ		0x4			/* IREG�FREG : IM7 (3�o�C�g)    */
#define		IR_IM8		0x5			/* IREG�FIM8  (�Q�o�C�g)        */
#define		REG_REG		0x6			/* REG �FREG  (�R�o�C�g)        */
#define		MREG_REG	0x7			/* REG �FREG  (�R�o�C�g)        */
#define		REG_IM3		0x8			/* REG �FIM3  (�Q�o�C�g)        */
#define		REG2_IM3	0x9			/* REG �FREG :IM3  (�R�o�C�g)   */
#define		REG2_IM3J	0xA			/* REG �FREG :IM3 :IM7(4�o�C�g) */
#define		REG_IM7		0xB			/* REG �FIM7  (�R�o�C�g)        */
#define		REG_IM8		0xC			/* REG �FIM8  (�R�o�C�g)        */
#define		REG2_IM7	0xD			/* REG : REG �FIM8  (�S�o�C�g)  */
#define		IM8_REG		0xE			/* IM8 �FREG  (�R�o�C�g)        */
#define		IR_IM16		0xF			/* IREG�FIM16 (�S�o�C�g)        */
#define		IM7_NU		0x10		/* ���l(7bit):�Ȃ� JR����       */
#define		F_IM7		0x11		/* �t���O:���l(7bit) JR����     */
#define		F_IM16		0x12		/* �t���O:���l(16bit)JP/CAL���� */
#define		IM8_NU		0x13		/* ���l(16bit):�Ȃ� JR/CAL����  */
#define		IM16_NU		0x14		/* ���l(16bit):�Ȃ� JR/CAL����  */
#define		IM16_REG	0x15		/* IM16 : REG (�S�o�C�g)        */
#define		REG_IM16	0x16		/* REG �FIM16 (�S�o�C�g)        */
#define		NU_IM8		0x17		/* NU : IM8�i�R�o�C�g) PFL�̂�? */
#define		REG_I5I3	0x18		/* REG �FIM5 :IM3  (�R�o�C�g)   */
#define		REG_I5I3J	0x19		/* REG �FIM5 :IM3 :IM7(4�o�C�g) */

#define		IM3bit		8			/* �R�r�b�g���ő�l             */
#define		IM7bit		128			/* �V�r�b�g���ő�l             */
#define		IM8bit		256			/* �W�r�b�g���ő�l             */

/*------------------------------------------------------------------*/
/*  �\����͌��ʏo�̓e�[�u���\���̒�`�iOutTbl�j                    */
/*------------------------------------------------------------------*/
typedef struct outtbl {
	unsigned short idx;				/* codetbl�C���f�b�N�X          */
	unsigned short adr;				/* ���ߊi�[�A�h���X             */
	unsigned short byte;			/* ���߃o�C�g��(0:�R�����g�̂�) */
	unsigned char  code[256]; 		/* ���߃R�[�h                   */
	unsigned short kc;				/* KC�����Ή��t���O(1:KC����)   */
	unsigned short pm7;				/* �}IM7�`���Ή��t���O(1:+,2:-) */
	unsigned short opkind[4];		/* �I�y�����h���               */
	unsigned short opdata[4];		/* �I�y�����h�ԍ�(ڼ޽�/���l)   */
	char	*label; 				/* �擪���x��(NULL:�o�^�Ȃ�)    */
	char	*opr[MAXOPR];			/* �I�y�����h(NULL:�o�^�Ȃ�)    */
	char	*comment;				/* �R�����g(NULL:�o�^�Ȃ�)      */
	char	line[MAXLINE*2];		/* ���̓o�b�t�@(512�o�C�g)      */
} OUTTBL;

/*------------------------------------------------------------------*/
/*  ���x���e�[�u���\���̒�`�ilbltbl�j                              */
/*------------------------------------------------------------------*/
typedef struct lbl {
	void * np;						/* �����x���\���̃|�C���^       */
	unsigned short adr;				/* �Ή��A�h���X                 */
	char	name[1];				/* ���x������(1Byte�ȏ�)        */
} LBL;

/*------------------------------------------------------------------*/
/*  �e��f�[�^�ϊ��e�[�u���\���̒�`                                */
/*------------------------------------------------------------------*/
/* �I�y�����h�ϊ��e�[�u���\�� */
typedef struct opr {
	unsigned short code;			/* �I�y�����h�R�[�h�ԍ�         */
	char	name[9];				/* �I�y�����h����               */
} OPR;

/* �������I�y�����h��ʃe�[�u�� */
#define		MAXIDX		12
struct opr moprtbl[MAXIDX] = {
{	MIX_p	,	"(IX+"		},
{	MIX_p	,	"(Ix+"		},
{	MIX_p	,	"(ix+"		},
{	MIX_m	,	"(IX-"		},
{	MIX_m	,	"(Ix-"		},
{	MIX_m	,	"(ix-"		},
{	MIZ_p	,	"(IZ+"		},
{	MIZ_p	,	"(Iz+"		},
{	MIZ_p	,	"(iz+"		},
{	MIZ_m	,	"(IZ-"		},
{	MIZ_m	,	"(Iz-"		},
{	MIZ_m	,	"(iz-"		}
};

/* ���W�X�^�I�y�����h��ʃe�[�u�� */
#define		MAXIREG		16
struct opr regtbl[MAXIREG] = {
{	PE		,	"PE"		},
{	PD		,	"PD"		},
{	TS		,	"TS"		},
{	UA		,	"UA"		},
{	IA		,	"IA"		},
{	IE		,	"IE"		},
{	TM		,	"TM"		},
{	KY		,	"KY"		},
{	US		,	"US"		},
{	SS		,	"SS"		},
{	IX		,	"IX"		},
{	IY		,	"IY"		},
{	IZ		,	"IZ"		},
{	S0		,	"S0"		},
{	S1		,	"S1"		},
{	S2		,	"S2"		}
};

/* �t���O��ʃe�[�u�� */
#define		MAXFLAG		8
struct opr flagtbl[MAXFLAG] = {
{	ZF		,	"Z"			},
{	LZF		,	"LZ"		},
{	UZF		,	"UZ"		},
{	NZF		,	"NZ"		},
{	CF		,	"C"			},
{	NCF		,	"NC"		},
{	NLZF	,	"LNZ"		},
{	NLZF	,	"NLZ"		}
};

/* �^�����ߎ�� */
#define		OP_EQU		0			/* EQU      */
#define		OP_ORG		1			/* ORG      */
#define		OP_START	2			/* START    */
#define		OP_DS		3			/* DS       */
#define		OP_DB		4			/* DB       */
#define		OP_DW		5			/* DW       */
#define		OP_LEVEL	6			/* LEVEL    */
#define		OP_INCLUDE	7			/* #INCLUDE */
#define		OP_LIST		8			/* #LIST    */
#define		OP_NOLIST	9			/* #NOLIST  */
#define		OP_EJECT	10			/* #EJECT   */

/* �^�����ߕϊ��e�[�u�� */
#define		MAXDIR		11
struct opr Directivetbl[MAXDIR] = {
{	OP_EQU		,	"EQU"		},
{	OP_ORG		,	"ORG"		},
{	OP_START	,	"START"		},
{	OP_DS		,	"DS"		},
{	OP_DB		,	"DB"		},
{	OP_DW		,	"DW"		},
{	OP_LEVEL	,	"LEVEL"		},
{	OP_INCLUDE	,	"#INCLUDE"	},
{	OP_LIST		,	"#LIST"		},
{	OP_NOLIST	,	"#NOLIST"	},
{	OP_EJECT	,	"#EJECT"	}
};

/* #if�`#else�`#endif�}�N���ϊ��e�[�u�� */
#define		IFLEVEL     255         /* #if�l�X�g���x�� */
#define		OP_IF		0			/* #if   */
#define		OP_ELSE		1			/* #else */
#define		OP_ENDIF	2			/* #endif*/

#define		MACDIR		3
struct opr MacTbl[MACDIR] = {
{	OP_IF		,	"#IF"		},
{	OP_ELSE		,	"#ELSE"		},
{	OP_ENDIF	,	"#ENDIF"	}
};

#define	MAXMN		6				/* �j���j�b�N�ő咷(6����) */
/* �������W�X�^/�t���O�g�p���ߓo�^�e�[�u���\�� */
typedef struct irfnc {
	char	name[MAXMN];
} IRFNC;

/* �������W�X�^�g�p���ߓo�^�e�[�u�� */
#define	MAXIR		5				/* �������W�X�^���p���ߐ� */
struct irfnc irtbl[MAXIR] = {
{"PST"},{"GST"},{"PRE"},{"GRE"},{"POR"}
};

/* �t���O�g�p���ߓo�^�e�[�u�� */
#define	MAXFL		4				/* �t���O���W�X�^���p���ߐ� */
struct irfnc fltbl[MAXFL] = {
{"JR"},{"JP"},{"CAL"},{"RTN"}
};

/* ���ߕϊ��e�[�u���\�� */
typedef struct fnc {
	unsigned char	code;			/* ���߃R�[�h�ԍ�               */
	unsigned char	secop;			/* �Z�J���h���߃R�[�h�ԍ�       */
	unsigned char	byte;			/* ���߃o�C�g��                 */
	unsigned char	kind;			/* ���ߌ���(�������i�[���)   */
	char			name[MAXMN];	/* �j���j�b�N����               */
	unsigned short	op1;			/* �I�y�����h�P���             */
	unsigned short	op2;			/* �I�y�����h�Q���             */
	unsigned short	op3;			/* �I�y�����h�R���             */
	unsigned short	op4;			/* �I�y�����h�S���             */
} FNC;

/* ���ߕϊ��e�[�u�� */
#define MAXOP		1061			/* �o�^���ߐ�                   */
struct fnc codetbl[MAXOP] = {
/*	opcode	,second	,byte,	kind	,func	,op1		,op2		,op3	,op4	*/
{	0x00	,0		,2	,REG_NU		,"ADC"	,REG		,R31		,0		,0		},
{	0x00	,0x20	,2	,REG_NU		,"ADC"	,REG		,R30		,0		,0		},
{	0x00	,0x40	,2	,REG_NU		,"ADC"	,REG		,R00		,0		,0		},
{	0x00	,0x60	,3	,REG_REG	,"ADC"	,REG		,REG		,0		,0		},
{	0x00	,0x80	,3	,REG_IM7	,"ADC"	,REG		,R31		,IM7	,0		},
{	0x00	,0xa0	,3	,REG_IM7	,"ADC"	,REG		,R30		,IM7	,0		},
{	0x00	,0xc0	,3	,REG_IM7	,"ADC"	,REG		,R00		,IM7	,0		},
{	0x00	,0xe0	,4	,REG2_IM7	,"ADC"	,REG		,REG		,IM7	,0		},
{	0x01	,0		,2	,REG_NU		,"SBC"	,REG		,R31		,0		,0		},
{	0x01	,0x20	,2	,REG_NU		,"SBC"	,REG		,R30		,0		,0		},
{	0x01	,0x40	,2	,REG_NU		,"SBC"	,REG		,R00		,0		,0		},
{	0x01	,0x60	,3	,REG_REG	,"SBC"	,REG		,REG		,0		,0		},
{	0x01	,0x80	,3	,REG_IM7	,"SBC"	,REG		,R31		,IM7	,0		},
{	0x01	,0xa0	,3	,REG_IM7	,"SBC"	,REG		,R30		,IM7	,0		},
{	0x01	,0xc0	,3	,REG_IM7	,"SBC"	,REG		,R00		,IM7	,0		},
{	0x01	,0xe0	,4	,REG2_IM7	,"SBC"	,REG		,REG		,IM7	,0		},
{	0x02	,0		,2	,REG_NU		,"LD"	,REG		,R31		,0		,0		},
{	0x02	,0x20	,2	,REG_NU		,"LD"	,REG		,R30		,0		,0		},
{	0x02	,0x40	,2	,REG_NU		,"LD"	,REG		,R00		,0		,0		},
{	0x02	,0x60	,3	,REG_REG	,"LD"	,REG		,REG		,0		,0		},
{	0x02	,0x80	,3	,REG_IM7	,"LD"	,REG		,R31		,IM7	,0		},
{	0x02	,0xa0	,3	,REG_IM7	,"LD"	,REG		,R30		,IM7	,0		},
{	0x02	,0xc0	,3	,REG_IM7	,"LD"	,REG		,R00		,IM7	,0		},
{	0x02	,0xe0	,4	,REG2_IM7	,"LD"	,REG		,REG		,IM7	,0		},
{	0x04	,0		,2	,REG_NU		,"ANC"	,REG		,R31		,0		,0		},
{	0x04	,0x20	,2	,REG_NU		,"ANC"	,REG		,R30		,0		,0		},
{	0x04	,0x40	,2	,REG_NU		,"ANC"	,REG		,R00		,0		,0		},
{	0x04	,0x60	,3	,REG_REG	,"ANC"	,REG		,REG		,0		,0		},
{	0x04	,0x80	,3	,REG_IM7	,"ANC"	,REG		,R31		,IM7	,0		},
{	0x04	,0xa0	,3	,REG_IM7	,"ANC"	,REG		,R30		,IM7	,0		},
{	0x04	,0xc0	,3	,REG_IM7	,"ANC"	,REG		,R00		,IM7	,0		},
{	0x04	,0xe0	,4	,REG2_IM7	,"ANC"	,REG		,REG		,IM7	,0		},
{	0x05	,0		,2	,REG_NU		,"NAC"	,REG		,R31		,0		,0		},
{	0x05	,0x20	,2	,REG_NU		,"NAC"	,REG		,R30		,0		,0		},
{	0x05	,0x40	,2	,REG_NU		,"NAC"	,REG		,R00		,0		,0		},
{	0x05	,0x60	,3	,REG_REG	,"NAC"	,REG		,REG		,0		,0		},
{	0x05	,0x80	,3	,REG_IM7	,"NAC"	,REG		,R31		,IM7	,0		},
{	0x05	,0xa0	,3	,REG_IM7	,"NAC"	,REG		,R30		,IM7	,0		},
{	0x05	,0xc0	,3	,REG_IM7	,"NAC"	,REG		,R00		,IM7	,0		},
{	0x05	,0xe0	,4	,REG2_IM7	,"NAC"	,REG		,REG		,IM7	,0		},
{	0x06	,0		,2	,REG_NU		,"ORC"	,REG		,R31		,0		,0		},
{	0x06	,0x20	,2	,REG_NU		,"ORC"	,REG		,R30		,0		,0		},
{	0x06	,0x40	,2	,REG_NU		,"ORC"	,REG		,R00		,0		,0		},
{	0x06	,0x60	,3	,REG_REG	,"ORC"	,REG		,REG		,0		,0		},
{	0x06	,0x80	,3	,REG_IM7	,"ORC"	,REG		,R31		,IM7	,0		},
{	0x06	,0xa0	,3	,REG_IM7	,"ORC"	,REG		,R30		,IM7	,0		},
{	0x06	,0xc0	,3	,REG_IM7	,"ORC"	,REG		,R00		,IM7	,0		},
{	0x06	,0xe0	,4	,REG2_IM7	,"ORC"	,REG		,REG		,IM7	,0		},
{	0x07	,0		,2	,REG_NU		,"XRC"	,REG		,R31		,0		,0		},
{	0x07	,0x20	,2	,REG_NU		,"XRC"	,REG		,R30		,0		,0		},
{	0x07	,0x40	,2	,REG_NU		,"XRC"	,REG		,R00		,0		,0		},
{	0x07	,0x60	,3	,REG_REG	,"XRC"	,REG		,REG		,0		,0		},
{	0x07	,0x80	,3	,REG_IM7	,"XRC"	,REG		,R31		,IM7	,0		},
{	0x07	,0xa0	,3	,REG_IM7	,"XRC"	,REG		,R30		,IM7	,0		},
{	0x07	,0xc0	,3	,REG_IM7	,"XRC"	,REG		,R00		,IM7	,0		},
{	0x07	,0xe0	,4	,REG2_IM7	,"XRC"	,REG		,REG		,IM7	,0		},
{	0x08	,0		,2	,REG_NU		,"AD"	,REG		,R31		,0		,0		},
{	0x08	,0x20	,2	,REG_NU		,"AD"	,REG		,R30		,0		,0		},
{	0x08	,0x40	,2	,REG_NU		,"AD"	,REG		,R00		,0		,0		},
{	0x08	,0x60	,3	,REG_REG	,"AD"	,REG		,REG		,0		,0		},
{	0x08	,0x80	,3	,REG_IM7	,"AD"	,REG		,R31		,IM7	,0		},
{	0x08	,0xa0	,3	,REG_IM7	,"AD"	,REG		,R30		,IM7	,0		},
{	0x08	,0xc0	,3	,REG_IM7	,"AD"	,REG		,R00		,IM7	,0		},
{	0x08	,0xe0	,4	,REG2_IM7	,"AD"	,REG		,REG		,IM7	,0		},
{	0x09	,0		,2	,REG_NU		,"SB"	,REG		,R31		,0		,0		},
{	0x09	,0x20	,2	,REG_NU		,"SB"	,REG		,R30		,0		,0		},
{	0x09	,0x40	,2	,REG_NU		,"SB"	,REG		,R00		,0		,0		},
{	0x09	,0x60	,3	,REG_REG	,"SB"	,REG		,REG		,0		,0		},
{	0x09	,0x80	,3	,REG_IM7	,"SB"	,REG		,R31		,IM7	,0		},
{	0x09	,0xa0	,3	,REG_IM7	,"SB"	,REG		,R30		,IM7	,0		},
{	0x09	,0xc0	,3	,REG_IM7	,"SB"	,REG		,R00		,IM7	,0		},
{	0x09	,0xe0	,4	,REG2_IM7	,"SB"	,REG		,REG		,IM7	,0		},
{	0x0A	,0		,2	,REG_NU		,"ADB"	,REG		,R31		,0		,0		},
{	0x0A	,0x20	,2	,REG_NU		,"ADB"	,REG		,R30		,0		,0		},
{	0x0A	,0x40	,2	,REG_NU		,"ADB"	,REG		,R00		,0		,0		},
{	0x0A	,0x60	,3	,REG_REG	,"ADB"	,REG		,REG		,0		,0		},
{	0x0A	,0x80	,3	,REG_IM7	,"ADB"	,REG		,R31		,IM7	,0		},
{	0x0A	,0xa0	,3	,REG_IM7	,"ADB"	,REG		,R30		,IM7	,0		},
{	0x0A	,0xc0	,3	,REG_IM7	,"ADB"	,REG		,R00		,IM7	,0		},
{	0x0A	,0xe0	,4	,REG2_IM7	,"ADB"	,REG		,REG		,IM7	,0		},
{	0x0B	,0		,2	,REG_NU		,"SBB"	,REG		,R31		,0		,0		},
{	0x0B	,0x20	,2	,REG_NU		,"SBB"	,REG		,R30		,0		,0		},
{	0x0B	,0x40	,2	,REG_NU		,"SBB"	,REG		,R00		,0		,0		},
{	0x0B	,0x60	,3	,REG_REG	,"SBB"	,REG		,REG		,0		,0		},
{	0x0B	,0x80	,3	,REG_IM7	,"SBB"	,REG		,R31		,IM7	,0		},
{	0x0B	,0xa0	,3	,REG_IM7	,"SBB"	,REG		,R30		,IM7	,0		},
{	0x0B	,0xc0	,3	,REG_IM7	,"SBB"	,REG		,R00		,IM7	,0		},
{	0x0B	,0xe0	,4	,REG2_IM7	,"SBB"	,REG		,REG		,IM7	,0		},
{	0x0C	,0		,2	,REG_NU		,"AN"	,REG		,R31		,0		,0		},
{	0x0C	,0x20	,2	,REG_NU		,"AN"	,REG		,R30		,0		,0		},
{	0x0C	,0x40	,2	,REG_NU		,"AN"	,REG		,R00		,0		,0		},
{	0x0C	,0x60	,3	,REG_REG	,"AN"	,REG		,REG		,0		,0		},
{	0x0C	,0x80	,3	,REG_IM7	,"AN"	,REG		,R31		,IM7	,0		},
{	0x0C	,0xa0	,3	,REG_IM7	,"AN"	,REG		,R30		,IM7	,0		},
{	0x0C	,0xc0	,3	,REG_IM7	,"AN"	,REG		,R00		,IM7	,0		},
{	0x0C	,0xe0	,4	,REG2_IM7	,"AN"	,REG		,REG		,IM7	,0		},
{	0x0D	,0		,2	,REG_NU		,"NA"	,REG		,R31		,0		,0		},
{	0x0D	,0x20	,2	,REG_NU		,"NA"	,REG		,R30		,0		,0		},
{	0x0D	,0x40	,2	,REG_NU		,"NA"	,REG		,R00		,0		,0		},
{	0x0D	,0x60	,3	,REG_REG	,"NA"	,REG		,REG		,0		,0		},
{	0x0D	,0x80	,3	,REG_IM7	,"NA"	,REG		,R31		,IM7	,0		},
{	0x0D	,0xa0	,3	,REG_IM7	,"NA"	,REG		,R30		,IM7	,0		},
{	0x0D	,0xc0	,3	,REG_IM7	,"NA"	,REG		,R00		,IM7	,0		},
{	0x0D	,0xe0	,4	,REG2_IM7	,"NA"	,REG		,REG		,IM7	,0		},
{	0x0E	,0		,2	,REG_NU		,"OR"	,REG		,R31		,0		,0		},
{	0x0E	,0x20	,2	,REG_NU		,"OR"	,REG		,R30		,0		,0		},
{	0x0E	,0x40	,2	,REG_NU		,"OR"	,REG		,R00		,0		,0		},
{	0x0E	,0x60	,3	,REG_REG	,"OR"	,REG		,REG		,0		,0		},
{	0x0E	,0x80	,3	,REG_IM7	,"OR"	,REG		,R31		,IM7	,0		},
{	0x0E	,0xa0	,3	,REG_IM7	,"OR"	,REG		,R30		,IM7	,0		},
{	0x0E	,0xc0	,3	,REG_IM7	,"OR"	,REG		,R00		,IM7	,0		},
{	0x0E	,0xe0	,4	,REG2_IM7	,"OR"	,REG		,REG		,IM7	,0		},
{	0x0F	,0		,2	,REG_NU		,"XR"	,REG		,R31		,0		,0		},
{	0x0F	,0x20	,2	,REG_NU		,"XR"	,REG		,R30		,0		,0		},
{	0x0F	,0x40	,2	,REG_NU		,"XR"	,REG		,R00		,0		,0		},
{	0x0F	,0x60	,3	,REG_REG	,"XR"	,REG		,REG		,0		,0		},
{	0x0F	,0x80	,3	,REG_IM7	,"XR"	,REG		,R31		,IM7	,0		},
{	0x0F	,0xa0	,3	,REG_IM7	,"XR"	,REG		,R30		,IM7	,0		},
{	0x0F	,0xc0	,3	,REG_IM7	,"XR"	,REG		,R00		,IM7	,0		},
{	0x0F	,0xe0	,4	,REG2_IM7	,"XR"	,REG		,REG		,IM7	,0		},
{	0x10	,0		,2	,REG_NU		,"ST"	,REG		,MR31		,0		,0		},
{	0x10	,0x20	,2	,REG_NU		,"ST"	,REG		,MR30		,0		,0		},
{	0x10	,0x40	,2	,REG_NU		,"ST"	,REG		,MR00		,0		,0		},
{	0x10	,0x60	,3	,REG_REG	,"ST"	,REG		,MREG		,0		,0		},
{	0x10	,0x80	,3	,REG_IM7	,"ST"	,REG		,MR31		,IM7	,0		},
{	0x10	,0xa0	,3	,REG_IM7	,"ST"	,REG		,MR30		,IM7	,0		},
{	0x10	,0xc0	,3	,REG_IM7	,"ST"	,REG		,MR00		,IM7	,0		},
{	0x10	,0xe0	,4	,REG2_IM7	,"ST"	,REG		,MREG		,IM7	,0		},
{	0x11	,0		,2	,REG_NU		,"LD"	,REG		,MR31		,0		,0		},
{	0x11	,0x20	,2	,REG_NU		,"LD"	,REG		,MR30		,0		,0		},
{	0x11	,0x40	,2	,REG_NU		,"LD"	,REG		,MR00		,0		,0		},
{	0x11	,0x60	,3	,REG_REG	,"LD"	,REG		,MREG		,0		,0		},
{	0x11	,0x80	,3	,REG_IM7	,"LD"	,REG		,MR31		,IM7	,0		},
{	0x11	,0xa0	,3	,REG_IM7	,"LD"	,REG		,MR30		,IM7	,0		},
{	0x11	,0xc0	,3	,REG_IM7	,"LD"	,REG		,MR00		,IM7	,0		},
{	0x11	,0xe0	,4	,REG2_IM7	,"LD"	,REG		,MREG		,IM7	,0		},
{	0x12	,0		,2	,REG_NU		,"STL"	,REG		,0			,0		,0		},/* LCD�o�� */
{	0x12	,0x80	,3	,REG_NUJ	,"STL"	,REG		,IM7		,0		,0		},/* LCD�o�� */
{	0x14	,0		,2	,REG_NU		,"PPO"	,REG		,0			,0		,0		},/* LCD����|�[�g */
{	0x14	,0x40	,2	,REG_NU		,"PFL"	,REG		,0			,0		,0		},
{	0x14	,0x80	,3	,REG_NUJ	,"PPO"	,REG		,IM7		,0		,0		},/* LCD����|�[�g */
{	0x14	,0xc0	,3	,REG_NUJ	,"PFL"	,REG		,IM7		,0		,0		},
{	0x16	,0		,2	,IR_REG		,"PST"	,PE			,REG		,0		,0		},
{	0x16	,0x20	,2	,IR_REG		,"PST"	,PD			,REG		,0		,0		},
{	0x16	,0x40	,2	,IR_REG		,"PST"	,TS			,REG		,0		,0		},
{	0x16	,0x60	,2	,IR_REG		,"PST"	,UA			,REG		,0		,0		},
{	0x16	,0x80	,3	,IR_REGJ	,"PST"	,PE			,REG		,IM7	,0		},
{	0x16	,0xa0	,3	,IR_REGJ	,"PST"	,PD			,REG		,IM7	,0		},
{	0x16	,0xc0	,3	,IR_REGJ	,"PST"	,TS			,REG		,IM7	,0		},
{	0x16	,0xe0	,3	,IR_REGJ	,"PST"	,UA			,REG		,IM7	,0		},
{	0x17	,0		,2	,IR_REG		,"PST"	,IA			,REG		,0		,0		},
{	0x17	,0x20	,2	,IR_REG		,"PST"	,IE			,REG		,0		,0		},
{	0x17	,0x80	,3	,IR_REGJ	,"PST"	,IA			,REG		,IM7	,0		},
{	0x17	,0xa0	,3	,IR_REGJ	,"PST"	,IE			,REG		,IM7	,0		},
{	0x18	,0		,2	,REG_NU		,"ROD"	,REG		,0			,0		,0		},
{	0x18	,0x20	,2	,REG_NU		,"ROU"	,REG		,0			,0		,0		},
{	0x18	,0x40	,2	,REG_NU		,"BID"	,REG		,0			,0		,0		},
{	0x18	,0x60	,2	,REG_NU		,"BIU"	,REG		,0			,0		,0		},
{	0x18	,0x80	,3	,REG_NUJ	,"ROD"	,REG		,IM7		,0		,0		},
{	0x18	,0xa0	,3	,REG_NUJ	,"ROU"	,REG		,IM7		,0		,0		},
{	0x18	,0xc0	,3	,REG_NUJ	,"BID"	,REG		,IM7		,0		,0		},
{	0x18	,0xe0	,3	,REG_NUJ	,"BIU"	,REG		,IM7		,0		,0		},
{	0x1A	,0		,2	,REG_NU		,"DID"	,REG		,0			,0		,0		},
{	0x1A	,0x20	,2	,REG_NU		,"DIU"	,REG		,0			,0		,0		},
{	0x1A	,0x40	,2	,REG_NU		,"BYD"	,REG		,0			,0		,0		},
{	0x1A	,0x60	,2	,REG_NU		,"BYU"	,REG		,0			,0		,0		},
{	0x1A	,0x80	,3	,REG_NUJ	,"DID"	,REG		,IM7		,0		,0		},
{	0x1A	,0xa0	,3	,REG_NUJ	,"DIU"	,REG		,IM7		,0		,0		},
{	0x1A	,0xc0	,3	,REG_NUJ	,"BYD"	,REG		,IM7		,0		,0		},
{	0x1A	,0xe0	,3	,REG_NUJ	,"BYU"	,REG		,IM7		,0		,0		},
{	0x1B	,0		,2	,REG_NU		,"CMP"	,REG		,0			,0		,0		},
{	0x1B	,0x40	,2	,REG_NU		,"INV"	,REG		,0			,0		,0		},
{	0x1B	,0x80	,3	,REG_NUJ	,"CMP"	,REG		,IM7		,0		,0		},
{	0x1B	,0xc0	,3	,REG_NUJ	,"INV"	,REG		,IM7		,0		,0		},
{	0x1C	,0		,2	,REG_NU		,"GPO"	,REG		,0			,0		,0		},
{	0x1C	,0x40	,2	,REG_NU		,"GFL"	,REG		,0			,0		,0		},
{	0x1C	,0x80	,3	,REG_NUJ	,"GPO"	,REG		,IM7		,0		,0		},
{	0x1C	,0xc0	,3	,REG_NUJ	,"GFL"	,REG		,IM7		,0		,0		},
{	0x1E	,0		,2	,IR_REG		,"GST"	,PE			,REG		,0		,0		},
{	0x1E	,0x20	,2	,IR_REG		,"GST"	,PD			,REG		,0		,0		},
{	0x1E	,0x40	,2	,IR_REG		,"GST"	,TS			,REG		,0		,0		},
{	0x1E	,0x60	,2	,IR_REG		,"GST"	,UA			,REG		,0		,0		},
{	0x1E	,0x80	,3	,IR_REGJ	,"GST"	,PE			,REG		,IM7	,0		},
{	0x1E	,0xa0	,3	,IR_REGJ	,"GST"	,PD			,REG		,IM7	,0		},
{	0x1E	,0xc0	,3	,IR_REGJ	,"GST"	,TS			,REG		,IM7	,0		},
{	0x1E	,0xe0	,3	,IR_REGJ	,"GST"	,UA			,REG		,IM7	,0		},
{	0x1F	,0		,2	,IR_REG		,"GST"	,IA			,REG		,0		,0		},
{	0x1F	,0x20	,2	,IR_REG		,"GST"	,IE			,REG		,0		,0		},
{	0x1F	,0x60	,2	,IR_REG		,"GST"	,TM			,REG		,0		,0		},
{	0x1F	,0x80	,3	,IR_REGJ	,"GST"	,IA			,REG		,IM7	,0		},
{	0x1F	,0xa0	,3	,IR_REGJ	,"GST"	,IE			,REG		,IM7	,0		},
{	0x1F	,0xe0	,3	,IR_REGJ	,"GST"	,TM			,REG		,IM7	,0		},
{	0x20	,0		,2	,REG_NU		,"ST"	,REG		,MIX_p|R31	,0		,0		},
{	0x20	,0x20	,2	,REG_NU		,"ST"	,REG		,MIX_p|R30	,0		,0		},
{	0x20	,0x40	,2	,REG_NU		,"ST"	,REG		,MIX_p|R00	,0		,0		},
{	0x20	,0x60	,3	,REG_REG	,"ST"	,REG		,MIX_p|REG	,0		,0		},
{	0x20	,0x80	,2	,REG_NU		,"ST"	,REG		,MIX_m|R31	,0		,0		},
{	0x20	,0xa0	,2	,REG_NU		,"ST"	,REG		,MIX_m|R30	,0		,0		},
{	0x20	,0xc0	,2	,REG_NU		,"ST"	,REG		,MIX_m|R00	,0		,0		},
{	0x20	,0xe0	,3	,REG_REG	,"ST"	,REG		,MIX_m|REG	,0		,0		},
{	0x21	,0		,2	,REG_NU		,"ST"	,REG		,MIZ_p|R31	,0		,0		},
{	0x21	,0x20	,2	,REG_NU		,"ST"	,REG		,MIZ_p|R30	,0		,0		},
{	0x21	,0x40	,2	,REG_NU		,"ST"	,REG		,MIZ_p|R00	,0		,0		},
{	0x21	,0x60	,3	,REG_REG	,"ST"	,REG		,MIZ_p|REG	,0		,0		},
{	0x21	,0x80	,2	,REG_NU		,"ST"	,REG		,MIZ_m|R31	,0		,0		},
{	0x21	,0xa0	,2	,REG_NU		,"ST"	,REG		,MIZ_m|R30	,0		,0		},
{	0x21	,0xc0	,2	,REG_NU		,"ST"	,REG		,MIZ_m|R00	,0		,0		},
{	0x21	,0xe0	,3	,REG_REG	,"ST"	,REG		,MIZ_m|REG	,0		,0		},
{	0x22	,0		,2	,REG_NU		,"STI"	,REG		,MIX_p|R31	,0		,0		},
{	0x22	,0x20	,2	,REG_NU		,"STI"	,REG		,MIX_p|R30	,0		,0		},
{	0x22	,0x40	,2	,REG_NU		,"STI"	,REG		,MIX_p|R00	,0		,0		},
{	0x22	,0x60	,3	,REG_REG	,"STI"	,REG		,MIX_p|REG	,0		,0		},
{	0x22	,0x80	,2	,REG_NU		,"STI"	,REG		,MIX_m|R31	,0		,0		},
{	0x22	,0xa0	,2	,REG_NU		,"STI"	,REG		,MIX_m|R30	,0		,0		},
{	0x22	,0xc0	,2	,REG_NU		,"STI"	,REG		,MIX_m|R00	,0		,0		},
{	0x22	,0xe0	,3	,REG_REG	,"STI"	,REG		,MIX_m|REG	,0		,0		},
{	0x23	,0		,2	,REG_NU		,"STI"	,REG		,MIZ_p|R31	,0		,0		},
{	0x23	,0x20	,2	,REG_NU		,"STI"	,REG		,MIZ_p|R30	,0		,0		},
{	0x23	,0x40	,2	,REG_NU		,"STI"	,REG		,MIZ_p|R00	,0		,0		},
{	0x23	,0x60	,3	,REG_REG	,"STI"	,REG		,MIZ_p|REG	,0		,0		},
{	0x23	,0x80	,2	,REG_NU		,"STI"	,REG		,MIZ_m|R31	,0		,0		},
{	0x23	,0xa0	,2	,REG_NU		,"STI"	,REG		,MIZ_m|R30	,0		,0		},
{	0x23	,0xc0	,2	,REG_NU		,"STI"	,REG		,MIZ_m|R00	,0		,0		},
{	0x23	,0xe0	,3	,REG_REG	,"STI"	,REG		,MIZ_m|REG	,0		,0		},
{	0x24	,0		,2	,REG_NU		,"STD"	,REG		,MIX_p|R31	,0		,0		},
{	0x24	,0x20	,2	,REG_NU		,"STD"	,REG		,MIX_p|R30	,0		,0		},
{	0x24	,0x40	,2	,REG_NU		,"STD"	,REG		,MIX_p|R00	,0		,0		},
{	0x24	,0x60	,3	,REG_REG	,"STD"	,REG		,MIX_p|REG	,0		,0		},
{	0x24	,0x80	,2	,REG_NU		,"STD"	,REG		,MIX_m|R31	,0		,0		},
{	0x24	,0xa0	,2	,REG_NU		,"STD"	,REG		,MIX_m|R30	,0		,0		},
{	0x24	,0xc0	,2	,REG_NU		,"STD"	,REG		,MIX_m|R00	,0		,0		},
{	0x24	,0xe0	,3	,REG_REG	,"STD"	,REG		,MIX_m|REG	,0		,0		},
{	0x25	,0		,2	,REG_NU		,"STD"	,REG		,MIZ_p|R31	,0		,0		},
{	0x25	,0x20	,2	,REG_NU		,"STD"	,REG		,MIZ_p|R30	,0		,0		},
{	0x25	,0x40	,2	,REG_NU		,"STD"	,REG		,MIZ_p|R00	,0		,0		},
{	0x25	,0x60	,3	,REG_REG	,"STD"	,REG		,MIZ_p|REG	,0		,0		},
{	0x25	,0x80	,2	,REG_NU		,"STD"	,REG		,MIZ_m|R31	,0		,0		},
{	0x25	,0xa0	,2	,REG_NU		,"STD"	,REG		,MIZ_m|R30	,0		,0		},
{	0x25	,0xc0	,2	,REG_NU		,"STD"	,REG		,MIZ_m|R00	,0		,0		},
{	0x25	,0xe0	,3	,REG_REG	,"STD"	,REG		,MIZ_m|REG	,0		,0		},
{	0x26	,0		,2	,REG_NU		,"PHS"	,REG		,0			,0		,0		},
{	0x27	,0		,2	,REG_NU		,"PHU"	,REG		,0			,0		,0		},
{	0x28	,0		,2	,REG_NU		,"LD"	,REG		,MIX_p|R31	,0		,0		},
{	0x28	,0x20	,2	,REG_NU		,"LD"	,REG		,MIX_p|R30	,0		,0		},
{	0x28	,0x40	,2	,REG_NU		,"LD"	,REG		,MIX_p|R00	,0		,0		},
{	0x28	,0x60	,3	,REG_REG	,"LD"	,REG		,MIX_p|REG	,0		,0		},
{	0x28	,0x80	,2	,REG_NU		,"LD"	,REG		,MIX_m|R31	,0		,0		},
{	0x28	,0xa0	,2	,REG_NU		,"LD"	,REG		,MIX_m|R30	,0		,0		},
{	0x28	,0xc0	,2	,REG_NU		,"LD"	,REG		,MIX_m|R00	,0		,0		},
{	0x28	,0xe0	,3	,REG_REG	,"LD"	,REG		,MIX_m|REG	,0		,0		},
{	0x29	,0		,2	,REG_NU		,"LD"	,REG		,MIZ_p|R31	,0		,0		},
{	0x29	,0x20	,2	,REG_NU		,"LD"	,REG		,MIZ_p|R30	,0		,0		},
{	0x29	,0x40	,2	,REG_NU		,"LD"	,REG		,MIZ_p|R00	,0		,0		},
{	0x29	,0x60	,3	,REG_REG	,"LD"	,REG		,MIZ_p|REG	,0		,0		},
{	0x29	,0x80	,2	,REG_NU		,"LD"	,REG		,MIZ_m|R31	,0		,0		},
{	0x29	,0xa0	,2	,REG_NU		,"LD"	,REG		,MIZ_m|R30	,0		,0		},
{	0x29	,0xc0	,2	,REG_NU		,"LD"	,REG		,MIZ_m|R00	,0		,0		},
{	0x29	,0xe0	,3	,REG_REG	,"LD"	,REG		,MIZ_m|REG	,0		,0		},
{	0x2A	,0		,2	,REG_NU		,"LDI"	,REG		,MIX_p|R31	,0		,0		},
{	0x2A	,0x20	,2	,REG_NU		,"LDI"	,REG		,MIX_p|R30	,0		,0		},
{	0x2A	,0x40	,2	,REG_NU		,"LDI"	,REG		,MIX_p|R00	,0		,0		},
{	0x2A	,0x60	,3	,REG_REG	,"LDI"	,REG		,MIX_p|REG	,0		,0		},
{	0x2A	,0x80	,2	,REG_NU		,"LDI"	,REG		,MIX_m|R31	,0		,0		},
{	0x2A	,0xa0	,2	,REG_NU		,"LDI"	,REG		,MIX_m|R30	,0		,0		},
{	0x2A	,0xc0	,2	,REG_NU		,"LDI"	,REG		,MIX_m|R00	,0		,0		},
{	0x2A	,0xe0	,3	,REG_REG	,"LDI"	,REG		,MIX_m|REG	,0		,0		},
{	0x2B	,0		,2	,REG_NU		,"LDI"	,REG		,MIZ_p|R31	,0		,0		},
{	0x2B	,0x20	,2	,REG_NU		,"LDI"	,REG		,MIZ_p|R30	,0		,0		},
{	0x2B	,0x40	,2	,REG_NU		,"LDI"	,REG		,MIZ_p|R00	,0		,0		},
{	0x2B	,0x60	,3	,REG_REG	,"LDI"	,REG		,MIZ_p|REG	,0		,0		},
{	0x2B	,0x80	,2	,REG_NU		,"LDI"	,REG		,MIZ_m|R31	,0		,0		},
{	0x2B	,0xa0	,2	,REG_NU		,"LDI"	,REG		,MIZ_m|R30	,0		,0		},
{	0x2B	,0xc0	,2	,REG_NU		,"LDI"	,REG		,MIZ_m|R00	,0		,0		},
{	0x2B	,0xe0	,3	,REG_REG	,"LDI"	,REG		,MIZ_m|REG	,0		,0		},
{	0x2C	,0		,2	,REG_NU		,"LDD"	,REG		,MIX_p|R31	,0		,0		},
{	0x2C	,0x20	,2	,REG_NU		,"LDD"	,REG		,MIX_p|R30	,0		,0		},
{	0x2C	,0x40	,2	,REG_NU		,"LDD"	,REG		,MIX_p|R00	,0		,0		},
{	0x2C	,0x60	,3	,REG_REG	,"LDD"	,REG		,MIX_p|REG	,0		,0		},
{	0x2C	,0x80	,2	,REG_NU		,"LDD"	,REG		,MIX_m|R31	,0		,0		},
{	0x2C	,0xa0	,2	,REG_NU		,"LDD"	,REG		,MIX_m|R30	,0		,0		},
{	0x2C	,0xc0	,2	,REG_NU		,"LDD"	,REG		,MIX_m|R00	,0		,0		},
{	0x2C	,0xe0	,3	,REG_REG	,"LDD"	,REG		,MIX_m|REG	,0		,0		},
{	0x2D	,0		,2	,REG_NU		,"LDD"	,REG		,MIZ_p|R31	,0		,0		},
{	0x2D	,0x20	,2	,REG_NU		,"LDD"	,REG		,MIZ_p|R30	,0		,0		},
{	0x2D	,0x40	,2	,REG_NU		,"LDD"	,REG		,MIZ_p|R00	,0		,0		},
{	0x2D	,0x60	,3	,REG_REG	,"LDD"	,REG		,MIZ_p|REG	,0		,0		},
{	0x2D	,0x80	,2	,REG_NU		,"LDD"	,REG		,MIZ_m|R31	,0		,0		},
{	0x2D	,0xa0	,2	,REG_NU		,"LDD"	,REG		,MIZ_m|R30	,0		,0		},
{	0x2D	,0xc0	,2	,REG_NU		,"LDD"	,REG		,MIZ_m|R00	,0		,0		},
{	0x2D	,0xe0	,3	,REG_REG	,"LDD"	,REG		,MIZ_m|REG	,0		,0		},
{	0x2E	,0		,2	,REG_NU		,"PPS"	,REG		,0			,0		,0		},
{	0x2F	,0		,2	,REG_NU		,"PPU"	,REG		,0			,0		,0		},
{	0x30	,0		,3	,F_IM16		,"JP"	,ZF			,IM16		,0		,0		},
{	0x31	,0		,3	,F_IM16		,"JP"	,NCF		,IM16		,0		,0		},
{	0x32	,0		,3	,F_IM16		,"JP"	,LZF		,IM16		,0		,0		},
{	0x33	,0		,3	,F_IM16		,"JP"	,UZF		,IM16		,0		,0		},
{	0x34	,0		,3	,F_IM16		,"JP"	,NZF		,IM16		,0		,0		},
{	0x35	,0		,3	,F_IM16		,"JP"	,CF			,IM16		,0		,0		},
{	0x36	,0		,3	,F_IM16		,"JP"	,NLZF		,IM16		,0		,0		},
{	0x37	,0		,3	,IM16_NU	,"JP"	,IM16		,0			,0		,0		},
{	0x38	,0		,2	,IR_REG		,"ADC"	,MIX_p|R31	,REG		,0		,0		},
{	0x38	,0x20	,2	,IR_REG		,"ADC"	,MIX_p|R30	,REG		,0		,0		},
{	0x38	,0x40	,2	,IR_REG		,"ADC"	,MIX_p|R00	,REG		,0		,0		},
{	0x38	,0x60	,3	,MREG_REG	,"ADC"	,MIX_p|REG	,REG		,0		,0		},
{	0x38	,0x80	,2	,IR_REG		,"ADC"	,MIX_m|R31	,REG		,0		,0		},
{	0x38	,0xa0	,2	,IR_REG		,"ADC"	,MIX_m|R30	,REG		,0		,0		},
{	0x38	,0xc0	,2	,IR_REG		,"ADC"	,MIX_m|R00	,REG		,0		,0		},
{	0x38	,0xe0	,3	,MREG_REG	,"ADC"	,MIX_m|REG	,REG		,0		,0		},
{	0x39	,0		,2	,IR_REG		,"ADC"	,MIZ_p|R31	,REG		,0		,0		},
{	0x39	,0x20	,2	,IR_REG		,"ADC"	,MIZ_p|R30	,REG		,0		,0		},
{	0x39	,0x40	,2	,IR_REG		,"ADC"	,MIZ_p|R00	,REG		,0		,0		},
{	0x39	,0x60	,3	,MREG_REG	,"ADC"	,MIZ_p|REG	,REG		,0		,0		},
{	0x39	,0x80	,2	,IR_REG		,"ADC"	,MIZ_m|R31	,REG		,0		,0		},
{	0x39	,0xa0	,2	,IR_REG		,"ADC"	,MIZ_m|R30	,REG		,0		,0		},
{	0x39	,0xc0	,2	,IR_REG		,"ADC"	,MIZ_m|R00	,REG		,0		,0		},
{	0x39	,0xe0	,3	,MREG_REG	,"ADC"	,MIZ_m|REG	,REG		,0		,0		},
{	0x3A	,0		,2	,IR_REG		,"SBC"	,MIX_p|R31	,REG		,0		,0		},
{	0x3A	,0x20	,2	,IR_REG		,"SBC"	,MIX_p|R30	,REG		,0		,0		},
{	0x3A	,0x40	,2	,IR_REG		,"SBC"	,MIX_p|R00	,REG		,0		,0		},
{	0x3A	,0x60	,3	,MREG_REG	,"SBC"	,MIX_p|REG	,REG		,0		,0		},
{	0x3A	,0x80	,2	,IR_REG		,"SBC"	,MIX_m|R31	,REG		,0		,0		},
{	0x3A	,0xa0	,2	,IR_REG		,"SBC"	,MIX_m|R30	,REG		,0		,0		},
{	0x3A	,0xc0	,2	,IR_REG		,"SBC"	,MIX_m|R00	,REG		,0		,0		},
{	0x3A	,0xe0	,3	,MREG_REG	,"SBC"	,MIX_m|REG	,REG		,0		,0		},
{	0x3B	,0		,2	,IR_REG		,"SBC"	,MIZ_p|R31	,REG		,0		,0		},
{	0x3B	,0x20	,2	,IR_REG		,"SBC"	,MIZ_p|R30	,REG		,0		,0		},
{	0x3B	,0x40	,2	,IR_REG		,"SBC"	,MIZ_p|R00	,REG		,0		,0		},
{	0x3B	,0x60	,3	,MREG_REG	,"SBC"	,MIZ_p|REG	,REG		,0		,0		},
{	0x3B	,0x80	,2	,IR_REG		,"SBC"	,MIZ_m|R31	,REG		,0		,0		},
{	0x3B	,0xa0	,2	,IR_REG		,"SBC"	,MIZ_m|R30	,REG		,0		,0		},
{	0x3B	,0xc0	,2	,IR_REG		,"SBC"	,MIZ_m|R00	,REG		,0		,0		},
{	0x3B	,0xe0	,3	,MREG_REG	,"SBC"	,MIZ_m|REG	,REG		,0		,0		},
{	0x3C	,0		,2	,IR_REG		,"AD"	,MIX_p|R31	,REG		,0		,0		},
{	0x3C	,0x20	,2	,IR_REG		,"AD"	,MIX_p|R30	,REG		,0		,0		},
{	0x3C	,0x40	,2	,IR_REG		,"AD"	,MIX_p|R00	,REG		,0		,0		},
{	0x3C	,0x60	,3	,MREG_REG	,"AD"	,MIX_p|REG	,REG		,0		,0		},
{	0x3C	,0x80	,2	,IR_REG		,"AD"	,MIX_m|R31	,REG		,0		,0		},
{	0x3C	,0xa0	,2	,IR_REG		,"AD"	,MIX_m|R30	,REG		,0		,0		},
{	0x3C	,0xc0	,2	,IR_REG		,"AD"	,MIX_m|R00	,REG		,0		,0		},
{	0x3C	,0xe0	,3	,MREG_REG	,"AD"	,MIX_m|REG	,REG		,0		,0		},
{	0x3D	,0		,2	,IR_REG		,"AD"	,MIZ_p|R31	,REG		,0		,0		},
{	0x3D	,0x20	,2	,IR_REG		,"AD"	,MIZ_p|R30	,REG		,0		,0		},
{	0x3D	,0x40	,2	,IR_REG		,"AD"	,MIZ_p|R00	,REG		,0		,0		},
{	0x3D	,0x60	,3	,MREG_REG	,"AD"	,MIZ_p|REG	,REG		,0		,0		},
{	0x3D	,0x80	,2	,IR_REG		,"AD"	,MIZ_m|R31	,REG		,0		,0		},
{	0x3D	,0xa0	,2	,IR_REG		,"AD"	,MIZ_m|R30	,REG		,0		,0		},
{	0x3D	,0xc0	,2	,IR_REG		,"AD"	,MIZ_m|R00	,REG		,0		,0		},
{	0x3D	,0xe0	,3	,MREG_REG	,"AD"	,MIZ_m|REG	,REG		,0		,0		},
{	0x3E	,0		,2	,IR_REG		,"SB"	,MIX_p|R31	,REG		,0		,0		},
{	0x3E	,0x20	,2	,IR_REG		,"SB"	,MIX_p|R30	,REG		,0		,0		},
{	0x3E	,0x40	,2	,IR_REG		,"SB"	,MIX_p|R00	,REG		,0		,0		},
{	0x3E	,0x60	,3	,MREG_REG	,"SB"	,MIX_p|REG	,REG		,0		,0		},
{	0x3E	,0x80	,2	,IR_REG		,"SB"	,MIX_m|R31	,REG		,0		,0		},
{	0x3E	,0xa0	,2	,IR_REG		,"SB"	,MIX_m|R30	,REG		,0		,0		},
{	0x3E	,0xc0	,2	,IR_REG		,"SB"	,MIX_m|R00	,REG		,0		,0		},
{	0x3E	,0xe0	,3	,MREG_REG	,"SB"	,MIX_m|REG	,REG		,0		,0		},
{	0x3F	,0		,2	,IR_REG		,"SB"	,MIZ_p|R31	,REG		,0		,0		},
{	0x3F	,0x20	,2	,IR_REG		,"SB"	,MIZ_p|R30	,REG		,0		,0		},
{	0x3F	,0x40	,2	,IR_REG		,"SB"	,MIZ_p|R00	,REG		,0		,0		},
{	0x3F	,0x60	,3	,MREG_REG	,"SB"	,MIZ_p|REG	,REG		,0		,0		},
{	0x3F	,0x80	,2	,IR_REG		,"SB"	,MIZ_m|R31	,REG		,0		,0		},
{	0x3F	,0xa0	,2	,IR_REG		,"SB"	,MIZ_m|R30	,REG		,0		,0		},
{	0x3F	,0xc0	,2	,IR_REG		,"SB"	,MIZ_m|R00	,REG		,0		,0		},
{	0x3F	,0xe0	,3	,MREG_REG	,"SB"	,MIZ_m|REG	,REG		,0		,0		},
{	0x40	,0		,3	,REG_IM8	,"ADC"	,REG		,IM8		,0		,0		},
{	0x40	,0x80	,4	,REG2_IM7	,"ADC"	,REG		,IM8		,IM7	,0		},
{	0x41	,0		,3	,REG_IM8	,"SBC"	,REG		,IM8		,0		,0		},
{	0x41	,0x80	,4	,REG2_IM7	,"SBC"	,REG		,IM8		,IM7	,0		},
{	0x42	,0		,3	,REG_IM8	,"LD"	,REG		,IM8		,0		,0		},
{	0x42	,0x80	,4	,REG2_IM7	,"LD"	,REG		,IM8		,IM7	,0		},
{	0x44	,0		,3	,REG_IM8	,"ANC"	,REG		,IM8		,0		,0		},
{	0x44	,0x80	,4	,REG2_IM7	,"ANC"	,REG		,IM8		,IM7	,0		},
{	0x45	,0		,3	,REG_IM8	,"NAC"	,REG		,IM8		,0		,0		},
{	0x45	,0x80	,4	,REG2_IM7	,"NAC"	,REG		,IM8		,IM7	,0		},
{	0x46	,0		,3	,REG_IM8	,"ORC"	,REG		,IM8		,0		,0		},
{	0x46	,0x80	,4	,REG2_IM7	,"ORC"	,REG		,IM8		,IM7	,0		},
{	0x47	,0		,3	,REG_IM8	,"XRC"	,REG		,IM8		,0		,0		},
{	0x47	,0x80	,4	,REG2_IM7	,"XRC"	,REG		,IM8		,IM7	,0		},
{	0x48	,0		,3	,REG_IM8	,"AD"	,REG		,IM8		,0		,0		},
{	0x48	,0x80	,4	,REG2_IM7	,"AD"	,REG		,IM8		,IM7	,0		},
{	0x49	,0		,3	,REG_IM8	,"SB"	,REG		,IM8		,0		,0		},
{	0x49	,0x80	,4	,REG2_IM7	,"SB"	,REG		,IM8		,IM7	,0		},
{	0x4A	,0		,3	,REG_IM8	,"ADB"	,REG		,IM8		,0		,0		},
{	0x4A	,0x80	,4	,REG2_IM7	,"ADB"	,REG		,IM8		,IM7	,0		},
{	0x4B	,0		,3	,REG_IM8	,"SBB"	,REG		,IM8		,0		,0		},
{	0x4B	,0x80	,4	,REG2_IM7	,"SBB"	,REG		,IM8		,IM7	,0		},
{	0x4C	,0		,3	,REG_IM8	,"AN"	,REG		,IM8		,0		,0		},
{	0x4C	,0x80	,4	,REG2_IM7	,"AN"	,REG		,IM8		,IM7	,0		},
{	0x4D	,0		,3	,REG_IM8	,"NA"	,REG		,IM8		,0		,0		},
{	0x4D	,0x80	,4	,REG2_IM7	,"NA"	,REG		,IM8		,IM7	,0		},
{	0x4E	,0		,3	,REG_IM8	,"OR"	,REG		,IM8		,0		,0		},
{	0x4E	,0x80	,4	,REG2_IM7	,"OR"	,REG		,IM8		,IM7	,0		},
{	0x4F	,0		,3	,REG_IM8	,"XR"	,REG		,IM8		,0		,0		},
{	0x4F	,0x80	,4	,REG2_IM7	,"XR"	,REG		,IM8		,IM7	,0		},
{	0x50	,0		,3	,IM8_REG	,"ST"	,IM8		,MR31		,0		,0		},
{	0x50	,0x20	,3	,IM8_REG	,"ST"	,IM8		,MR30		,0		,0		},
{	0x50	,0x40	,3	,IM8_REG	,"ST"	,IM8		,MR00		,0		,0		},
{	0x52	,0		,2	,IM8_NU		,"STL"	,IM8		,0			,0		,0		},/* LCD�o�� */
{	0x54	,0		,3	,NU_IM8		,"PPO"	,IM8		,0			,0		,0		},/* LCD����|�[�g */
{	0x54	,0x40	,3	,NU_IM8		,"PFL"	,IM8		,0			,0		,0		},
{	0x55	,0		,2	,IR_REG		,"POR"	,S0			,REG		,0		,0		},/* �d�l�s�� */
{	0x55	,0x20	,2	,IR_REG		,"POR"	,S1			,REG		,0		,0		},/* �d�l�s�� */
{	0x55	,0x40	,2	,IR_REG		,"POR"	,S2			,REG		,0		,0		},/* �d�l�s�� */
{	0x56	,0		,3	,IR_IM8		,"PST"	,PE			,IM8		,0		,0		},
{	0x56	,0x20	,3	,IR_IM8		,"PST"	,PD			,IM8		,0		,0		},
{	0x56	,0x40	,3	,IR_IM8		,"PST"	,TS			,IM8		,0		,0		},
{	0x56	,0x60	,3	,IR_IM8		,"PST"	,UA			,IM8		,0		,0		},
{	0x57	,0		,3	,IR_IM8		,"PST"	,IA			,IM8		,0		,0		},
{	0x57	,0x20	,3	,IR_IM8		,"PST"	,IE			,IM8		,0		,0		},
{	0x58	,0		,2	,IM8_NU		,"BUPS"	,IM8		,0			,0		,0		},
{	0x59	,0		,2	,IM8_NU		,"BDNS"	,IM8		,0			,0		,0		},
{	0x5C	,0		,2	,IM8_NU		,"SUP"	,IM8		,0			,0		,0		},
{	0x5D	,0		,2	,IM8_NU		,"SDN"	,IM8		,0			,0		,0		},
{	0x60	,0		,3	,REG_IM8	,"ST"	,REG		,MIX_p|IM8	,0		,0		},
{	0x60	,0x80	,3	,REG_IM8	,"ST"	,REG		,MIX_m|IM8	,0		,0		},
{	0x61	,0		,3	,REG_IM8	,"ST"	,REG		,MIZ_p|IM8	,0		,0		},
{	0x61	,0x80	,3	,REG_IM8	,"ST"	,REG		,MIZ_m|IM8	,0		,0		},
{	0x62	,0		,3	,REG_IM8	,"STI"	,REG		,MIX_p|IM8	,0		,0		},
{	0x62	,0x80	,3	,REG_IM8	,"STI"	,REG		,MIX_m|IM8	,0		,0		},
{	0x63	,0		,3	,REG_IM8	,"STI"	,REG		,MIZ_p|IM8	,0		,0		},
{	0x63	,0x80	,3	,REG_IM8	,"STI"	,REG		,MIZ_m|IM8	,0		,0		},
{	0x64	,0		,3	,REG_IM8	,"STD"	,REG		,MIX_p|IM8	,0		,0		},
{	0x64	,0x80	,3	,REG_IM8	,"STD"	,REG		,MIX_m|IM8	,0		,0		},
{	0x65	,0		,3	,REG_IM8	,"STD"	,REG		,MIZ_p|IM8	,0		,0		},
{	0x65	,0x80	,3	,REG_IM8	,"STD"	,REG		,MIZ_m|IM8	,0		,0		},
{	0x68	,0		,3	,REG_IM8	,"LD"	,REG		,MIX_p|IM8	,0		,0		},
{	0x68	,0x80	,3	,REG_IM8	,"LD"	,REG		,MIX_m|IM8	,0		,0		},
{	0x69	,0		,3	,REG_IM8	,"LD"	,REG		,MIZ_p|IM8	,0		,0		},
{	0x69	,0x80	,3	,REG_IM8	,"LD"	,REG		,MIZ_m|IM8	,0		,0		},
{	0x6A	,0		,3	,REG_IM8	,"LDI"	,REG		,MIX_p|IM8	,0		,0		},
{	0x6A	,0x80	,3	,REG_IM8	,"LDI"	,REG		,MIX_m|IM8	,0		,0		},
{	0x6B	,0		,3	,REG_IM8	,"LDI"	,REG		,MIZ_p|IM8	,0		,0		},
{	0x6B	,0x80	,3	,REG_IM8	,"LDI"	,REG		,MIZ_m|IM8	,0		,0		},
{	0x6C	,0		,3	,REG_IM8	,"LDD"	,REG		,MIX_p|IM8	,0		,0		},
{	0x6C	,0x80	,3	,REG_IM8	,"LDD"	,REG		,MIX_m|IM8	,0		,0		},
{	0x6D	,0		,3	,REG_IM8	,"LDD"	,REG		,MIZ_p|IM8	,0		,0		},
{	0x6D	,0x80	,3	,REG_IM8	,"LDD"	,REG		,MIZ_m|IM8	,0		,0		},
{	0x70	,0		,3	,F_IM16		,"CAL"	,ZF			,IM16		,0		,0		},
{	0x71	,0		,3	,F_IM16		,"CAL"	,NCF		,IM16		,0		,0		},
{	0x72	,0		,3	,F_IM16		,"CAL"	,LZF		,IM16		,0		,0		},
{	0x73	,0		,3	,F_IM16		,"CAL"	,UZF		,IM16		,0		,0		},
{	0x74	,0		,3	,F_IM16		,"CAL"	,NZF		,IM16		,0		,0		},
{	0x75	,0		,3	,F_IM16		,"CAL"	,CF			,IM16		,0		,0		},
{	0x76	,0		,3	,F_IM16		,"CAL"	,NLZF		,IM16		,0		,0		},
{	0x77	,0		,3	,IM16_NU	,"CAL"	,IM16		,0			,0		,0		},
{	0x78	,0		,3	,MREG_REG	,"ADC"	,MIX_p|IM8	,REG		,0		,0		},
{	0x78	,0x80	,3	,MREG_REG	,"ADC"	,MIX_m|IM8	,REG		,0		,0		},
{	0x79	,0		,3	,MREG_REG	,"ADC"	,MIZ_p|IM8	,REG		,0		,0		},
{	0x79	,0x80	,3	,MREG_REG	,"ADC"	,MIZ_m|IM8	,REG		,0		,0		},
{	0x7A	,0		,3	,MREG_REG	,"SBC"	,MIX_p|IM8	,REG		,0		,0		},
{	0x7A	,0x80	,3	,MREG_REG	,"SBC"	,MIX_m|IM8	,REG		,0		,0		},
{	0x7B	,0		,3	,MREG_REG	,"SBC"	,MIZ_p|IM8	,REG		,0		,0		},
{	0x7B	,0x80	,3	,MREG_REG	,"SBC"	,MIZ_m|IM8	,REG		,0		,0		},
{	0x7C	,0		,3	,MREG_REG	,"AD"	,MIX_p|IM8	,REG		,0		,0		},
{	0x7C	,0x80	,3	,MREG_REG	,"AD"	,MIX_m|IM8	,REG		,0		,0		},
{	0x7D	,0		,3	,MREG_REG	,"AD"	,MIZ_p|IM8	,REG		,0		,0		},
{	0x7D	,0x80	,3	,MREG_REG	,"AD"	,MIZ_m|IM8	,REG		,0		,0		},
{	0x7E	,0		,3	,MREG_REG	,"SB"	,MIX_p|IM8	,REG		,0		,0		},
{	0x7E	,0x80	,3	,MREG_REG	,"SB"	,MIX_m|IM8	,REG		,0		,0		},
{	0x7F	,0		,3	,MREG_REG	,"SB"	,MIZ_p|IM8	,REG		,0		,0		},
{	0x7F	,0x80	,3	,MREG_REG	,"SB"	,MIZ_m|IM8	,REG		,0		,0		},
{	0x80	,0		,2	,REG_NU		,"ADCW"	,REG		,R31		,0		,0		},
{	0x80	,0x20	,2	,REG_NU		,"ADCW"	,REG		,R30		,0		,0		},
{	0x80	,0x40	,2	,REG_NU		,"ADCW"	,REG		,R00		,0		,0		},
{	0x80	,0x60	,3	,REG_REG	,"ADCW"	,REG		,REG		,0		,0		},
{	0x80	,0x80	,3	,REG_IM7	,"ADCW"	,REG		,R31		,IM7	,0		},
{	0x80	,0xa0	,3	,REG_IM7	,"ADCW"	,REG		,R30		,IM7	,0		},
{	0x80	,0xc0	,3	,REG_IM7	,"ADCW"	,REG		,R00		,IM7	,0		},
{	0x80	,0xe0	,4	,REG2_IM7	,"ADCW"	,REG		,REG		,IM7	,0		},
{	0x81	,0		,2	,REG_NU		,"SBCW"	,REG		,R31		,0		,0		},
{	0x81	,0x20	,2	,REG_NU		,"SBCW"	,REG		,R30		,0		,0		},
{	0x81	,0x40	,2	,REG_NU		,"SBCW"	,REG		,R00		,0		,0		},
{	0x81	,0x60	,3	,REG_REG	,"SBCW"	,REG		,REG		,0		,0		},
{	0x81	,0x80	,3	,REG_IM7	,"SBCW"	,REG		,R31		,IM7	,0		},
{	0x81	,0xa0	,3	,REG_IM7	,"SBCW"	,REG		,R30		,IM7	,0		},
{	0x81	,0xc0	,3	,REG_IM7	,"SBCW"	,REG		,R00		,IM7	,0		},
{	0x81	,0xe0	,4	,REG2_IM7	,"SBCW"	,REG		,REG		,IM7	,0		},
{	0x82	,0		,2	,REG_NU		,"LDW"	,REG		,R31		,0		,0		},
{	0x82	,0x20	,2	,REG_NU		,"LDW"	,REG		,R30		,0		,0		},
{	0x82	,0x40	,2	,REG_NU		,"LDW"	,REG		,R00		,0		,0		},
{	0x82	,0x60	,3	,REG_REG	,"LDW"	,REG		,REG		,0		,0		},
{	0x82	,0x80	,3	,REG_IM7	,"LDW"	,REG		,R31		,IM7	,0		},
{	0x82	,0xa0	,3	,REG_IM7	,"LDW"	,REG		,R30		,IM7	,0		},
{	0x82	,0xc0	,3	,REG_IM7	,"LDW"	,REG		,R00		,IM7	,0		},
{	0x82	,0xe0	,4	,REG2_IM7	,"LDW"	,REG		,REG		,IM7	,0		},
{	0x84	,0		,2	,REG_NU		,"ANCW"	,REG		,R31		,0		,0		},
{	0x84	,0x20	,2	,REG_NU		,"ANCW"	,REG		,R30		,0		,0		},
{	0x84	,0x40	,2	,REG_NU		,"ANCW"	,REG		,R00		,0		,0		},
{	0x84	,0x60	,3	,REG_REG	,"ANCW"	,REG		,REG		,0		,0		},
{	0x84	,0x80	,3	,REG_IM7	,"ANCW"	,REG		,R31		,IM7	,0		},
{	0x84	,0xa0	,3	,REG_IM7	,"ANCW"	,REG		,R30		,IM7	,0		},
{	0x84	,0xc0	,3	,REG_IM7	,"ANCW"	,REG		,R00		,IM7	,0		},
{	0x84	,0xe0	,4	,REG2_IM7	,"ANCW"	,REG		,REG		,IM7	,0		},
{	0x85	,0		,2	,REG_NU		,"NACW"	,REG		,R31		,0		,0		},
{	0x85	,0x20	,2	,REG_NU		,"NACW"	,REG		,R30		,0		,0		},
{	0x85	,0x40	,2	,REG_NU		,"NACW"	,REG		,R00		,0		,0		},
{	0x85	,0x60	,3	,REG_REG	,"NACW"	,REG		,REG		,0		,0		},
{	0x85	,0x80	,3	,REG_IM7	,"NACW"	,REG		,R31		,IM7	,0		},
{	0x85	,0xa0	,3	,REG_IM7	,"NACW"	,REG		,R30		,IM7	,0		},
{	0x85	,0xc0	,3	,REG_IM7	,"NACW"	,REG		,R00		,IM7	,0		},
{	0x85	,0xe0	,4	,REG2_IM7	,"NACW"	,REG		,REG		,IM7	,0		},
{	0x86	,0		,2	,REG_NU		,"ORCW"	,REG		,R31		,0		,0		},
{	0x86	,0x20	,2	,REG_NU		,"ORCW"	,REG		,R30		,0		,0		},
{	0x86	,0x40	,2	,REG_NU		,"ORCW"	,REG		,R00		,0		,0		},
{	0x86	,0x60	,3	,REG_REG	,"ORCW"	,REG		,REG		,0		,0		},
{	0x86	,0x80	,3	,REG_IM7	,"ORCW"	,REG		,R31		,IM7	,0		},
{	0x86	,0xa0	,3	,REG_IM7	,"ORCW"	,REG		,R30		,IM7	,0		},
{	0x86	,0xc0	,3	,REG_IM7	,"ORCW"	,REG		,R00		,IM7	,0		},
{	0x86	,0xe0	,4	,REG2_IM7	,"ORCW"	,REG		,REG		,IM7	,0		},
{	0x87	,0		,2	,REG_NU		,"XRCW"	,REG		,R31		,0		,0		},
{	0x87	,0x20	,2	,REG_NU		,"XRCW"	,REG		,R30		,0		,0		},
{	0x87	,0x40	,2	,REG_NU		,"XRCW"	,REG		,R00		,0		,0		},
{	0x87	,0x60	,3	,REG_REG	,"XRCW"	,REG		,REG		,0		,0		},
{	0x87	,0x80	,3	,REG_IM7	,"XRCW"	,REG		,R31		,IM7	,0		},
{	0x87	,0xa0	,3	,REG_IM7	,"XRCW"	,REG		,R30		,IM7	,0		},
{	0x87	,0xc0	,3	,REG_IM7	,"XRCW"	,REG		,R00		,IM7	,0		},
{	0x87	,0xe0	,4	,REG2_IM7	,"XRCW"	,REG		,REG		,IM7	,0		},
{	0x88	,0		,2	,REG_NU		,"ADW"	,REG		,R31		,0		,0		},
{	0x88	,0x20	,2	,REG_NU		,"ADW"	,REG		,R30		,0		,0		},
{	0x88	,0x40	,2	,REG_NU		,"ADW"	,REG		,R00		,0		,0		},
{	0x88	,0x60	,3	,REG_REG	,"ADW"	,REG		,REG		,0		,0		},
{	0x88	,0x80	,3	,REG_IM7	,"ADW"	,REG		,R31		,IM7	,0		},
{	0x88	,0xa0	,3	,REG_IM7	,"ADW"	,REG		,R30		,IM7	,0		},
{	0x88	,0xc0	,3	,REG_IM7	,"ADW"	,REG		,R00		,IM7	,0		},
{	0x88	,0xe0	,4	,REG2_IM7	,"ADW"	,REG		,REG		,IM7	,0		},
{	0x89	,0		,2	,REG_NU		,"SBW"	,REG		,R31		,0		,0		},
{	0x89	,0x20	,2	,REG_NU		,"SBW"	,REG		,R30		,0		,0		},
{	0x89	,0x40	,2	,REG_NU		,"SBW"	,REG		,R00		,0		,0		},
{	0x89	,0x60	,3	,REG_REG	,"SBW"	,REG		,REG		,0		,0		},
{	0x89	,0x80	,3	,REG_IM7	,"SBW"	,REG		,R31		,IM7	,0		},
{	0x89	,0xa0	,3	,REG_IM7	,"SBW"	,REG		,R30		,IM7	,0		},
{	0x89	,0xc0	,3	,REG_IM7	,"SBW"	,REG		,R00		,IM7	,0		},
{	0x89	,0xe0	,4	,REG2_IM7	,"SBW"	,REG		,REG		,IM7	,0		},
{	0x8A	,0		,2	,REG_NU		,"ADBW"	,REG		,R31		,0		,0		},
{	0x8A	,0x20	,2	,REG_NU		,"ADBW"	,REG		,R30		,0		,0		},
{	0x8A	,0x40	,2	,REG_NU		,"ADBW"	,REG		,R00		,0		,0		},
{	0x8A	,0x60	,3	,REG_REG	,"ADBW"	,REG		,REG		,0		,0		},
{	0x8A	,0x80	,3	,REG_IM7	,"ADBW"	,REG		,R31		,IM7	,0		},
{	0x8A	,0xa0	,3	,REG_IM7	,"ADBW"	,REG		,R30		,IM7	,0		},
{	0x8A	,0xc0	,3	,REG_IM7	,"ADBW"	,REG		,R00		,IM7	,0		},
{	0x8A	,0xe0	,4	,REG2_IM7	,"ADBW"	,REG		,REG		,IM7	,0		},
{	0x8B	,0		,2	,REG_NU		,"SBBW"	,REG		,R31		,0		,0		},
{	0x8B	,0x20	,2	,REG_NU		,"SBBW"	,REG		,R30		,0		,0		},
{	0x8B	,0x40	,2	,REG_NU		,"SBBW"	,REG		,R00		,0		,0		},
{	0x8B	,0x60	,3	,REG_REG	,"SBBW"	,REG		,REG		,0		,0		},
{	0x8B	,0x80	,3	,REG_IM7	,"SBBW"	,REG		,R31		,IM7	,0		},
{	0x8B	,0xa0	,3	,REG_IM7	,"SBBW"	,REG		,R30		,IM7	,0		},
{	0x8B	,0xc0	,3	,REG_IM7	,"SBBW"	,REG		,R00		,IM7	,0		},
{	0x8B	,0xe0	,4	,REG2_IM7	,"SBBW"	,REG		,REG		,IM7	,0		},
{	0x8C	,0		,2	,REG_NU		,"ANW"	,REG		,R31		,0		,0		},
{	0x8C	,0x20	,2	,REG_NU		,"ANW"	,REG		,R30		,0		,0		},
{	0x8C	,0x40	,2	,REG_NU		,"ANW"	,REG		,R00		,0		,0		},
{	0x8C	,0x60	,3	,REG_REG	,"ANW"	,REG		,REG		,0		,0		},
{	0x8C	,0x80	,3	,REG_IM7	,"ANW"	,REG		,R31		,IM7	,0		},
{	0x8C	,0xa0	,3	,REG_IM7	,"ANW"	,REG		,R30		,IM7	,0		},
{	0x8C	,0xc0	,3	,REG_IM7	,"ANW"	,REG		,R00		,IM7	,0		},
{	0x8C	,0xe0	,4	,REG2_IM7	,"ANW"	,REG		,REG		,IM7	,0		},
{	0x8D	,0		,2	,REG_NU		,"NAW"	,REG		,R31		,0		,0		},
{	0x8D	,0x20	,2	,REG_NU		,"NAW"	,REG		,R30		,0		,0		},
{	0x8D	,0x40	,2	,REG_NU		,"NAW"	,REG		,R00		,0		,0		},
{	0x8D	,0x60	,3	,REG_REG	,"NAW"	,REG		,REG		,0		,0		},
{	0x8D	,0x80	,3	,REG_IM7	,"NAW"	,REG		,R31		,IM7	,0		},
{	0x8D	,0xa0	,3	,REG_IM7	,"NAW"	,REG		,R30		,IM7	,0		},
{	0x8D	,0xc0	,3	,REG_IM7	,"NAW"	,REG		,R00		,IM7	,0		},
{	0x8D	,0xe0	,4	,REG2_IM7	,"NAW"	,REG		,REG		,IM7	,0		},
{	0x8E	,0		,2	,REG_NU		,"ORW"	,REG		,R31		,0		,0		},
{	0x8E	,0x20	,2	,REG_NU		,"ORW"	,REG		,R30		,0		,0		},
{	0x8E	,0x40	,2	,REG_NU		,"ORW"	,REG		,R00		,0		,0		},
{	0x8E	,0x60	,3	,REG_REG	,"ORW"	,REG		,REG		,0		,0		},
{	0x8E	,0x80	,3	,REG_IM7	,"ORW"	,REG		,R31		,IM7	,0		},
{	0x8E	,0xa0	,3	,REG_IM7	,"ORW"	,REG		,R30		,IM7	,0		},
{	0x8E	,0xc0	,3	,REG_IM7	,"ORW"	,REG		,R00		,IM7	,0		},
{	0x8E	,0xe0	,4	,REG2_IM7	,"ORW"	,REG		,REG		,IM7	,0		},
{	0x8F	,0		,2	,REG_NU		,"XRW"	,REG		,R31		,0		,0		},
{	0x8F	,0x20	,2	,REG_NU		,"XRW"	,REG		,R30		,0		,0		},
{	0x8F	,0x40	,2	,REG_NU		,"XRW"	,REG		,R00		,0		,0		},
{	0x8F	,0x60	,3	,REG_REG	,"XRW"	,REG		,REG		,0		,0		},
{	0x8F	,0x80	,3	,REG_IM7	,"XRW"	,REG		,R31		,IM7	,0		},
{	0x8F	,0xa0	,3	,REG_IM7	,"XRW"	,REG		,R30		,IM7	,0		},
{	0x8F	,0xc0	,3	,REG_IM7	,"XRW"	,REG		,R00		,IM7	,0		},
{	0x8F	,0xe0	,4	,REG2_IM7	,"XRW"	,REG		,REG		,IM7	,0		},
{	0x90	,0		,2	,REG_NU		,"STW"	,REG		,MR31		,0		,0		},
{	0x90	,0x20	,2	,REG_NU		,"STW"	,REG		,MR30		,0		,0		},
{	0x90	,0x40	,2	,REG_NU		,"STW"	,REG		,MR00		,0		,0		},
{	0x90	,0x60	,3	,REG_REG	,"STW"	,REG		,MREG		,0		,0		},
{	0x90	,0x80	,3	,REG_IM7	,"STW"	,REG		,MR31		,IM7	,0		},
{	0x90	,0xa0	,3	,REG_IM7	,"STW"	,REG		,MR30		,IM7	,0		},
{	0x90	,0xc0	,3	,REG_IM7	,"STW"	,REG		,MR00		,IM7	,0		},
{	0x90	,0xe0	,4	,REG2_IM7	,"STW"	,REG		,MREG		,IM7	,0		},
{	0x91	,0		,2	,REG_NU		,"LDW"	,REG		,MR31		,0		,0		},
{	0x91	,0x20	,2	,REG_NU		,"LDW"	,REG		,MR30		,0		,0		},
{	0x91	,0x40	,2	,REG_NU		,"LDW"	,REG		,MR00		,0		,0		},
{	0x91	,0x60	,3	,REG_REG	,"LDW"	,REG		,MREG		,0		,0		},
{	0x91	,0x80	,3	,REG_IM7	,"LDW"	,REG		,MR31		,IM7	,0		},
{	0x91	,0xa0	,3	,REG_IM7	,"LDW"	,REG		,MR30		,IM7	,0		},
{	0x91	,0xc0	,3	,REG_IM7	,"LDW"	,REG		,MR00		,IM7	,0		},
{	0x91	,0xe0	,4	,REG2_IM7	,"LDW"	,REG		,MREG		,IM7	,0		},
{	0x92	,0		,2	,REG_NU		,"STLW"	,REG		,0			,0		,0		},/* LCD�o�� */
{	0x92	,0x80	,3	,REG_NU		,"STLW"	,REG		,IM7		,0		,0		},/* LCD�o�� */
{	0x94	,0		,2	,REG_NU		,"PPOW"	,REG		,0			,0		,0		},/* LCD����|�[�g */
{	0x94	,0x80	,3	,REG_NU		,"PPOW"	,REG		,IM7		,0		,0		},/* LCD����|�[�g */
{	0x96	,0		,2	,IR_REG		,"PRE"	,IX			,REG		,0		,0		},
{	0x96	,0x20	,2	,IR_REG		,"PRE"	,IY			,REG		,0		,0		},
{	0x96	,0x40	,2	,IR_REG		,"PRE"	,IZ			,REG		,0		,0		},
{	0x96	,0x60	,2	,IR_REG		,"PRE"	,US			,REG		,0		,0		},
{	0x96	,0x80	,3	,IR_REGJ	,"PRE"	,IX			,REG		,IM7	,0		},
{	0x96	,0xa0	,3	,IR_REGJ	,"PRE"	,IY			,REG		,IM7	,0		},
{	0x96	,0xc0	,3	,IR_REGJ	,"PRE"	,IZ			,REG		,IM7	,0		},
{	0x96	,0xe0	,3	,IR_REGJ	,"PRE"	,US			,REG		,IM7	,0		},
{	0x97	,0		,2	,IR_REG		,"PRE"	,SS			,REG		,0		,0		},
{	0x97	,0x80	,3	,IR_REGJ	,"PRE"	,SS			,REG		,IM7	,0		},
{	0x98	,0		,2	,REG_NU		,"RODW"	,REG		,0			,0		,0		},
{	0x98	,0x20	,2	,REG_NU		,"ROUW"	,REG		,0			,0		,0		},
{	0x98	,0x40	,2	,REG_NU		,"BIDW"	,REG		,0			,0		,0		},
{	0x98	,0x60	,2	,REG_NU		,"BIUW"	,REG		,0			,0		,0		},
{	0x98	,0x80	,3	,REG_NUJ	,"RODW"	,REG		,IM7		,0		,0		},
{	0x98	,0xa0	,3	,REG_NUJ	,"ROUW"	,REG		,IM7		,0		,0		},
{	0x98	,0xc0	,3	,REG_NUJ	,"BIDW"	,REG		,IM7		,0		,0		},
{	0x98	,0xe0	,3	,REG_NUJ	,"BIUW"	,REG		,IM7		,0		,0		},
{	0x9A	,0		,2	,REG_NU		,"DIDW"	,REG		,0			,0		,0		},
{	0x9A	,0x20	,2	,REG_NU		,"DIUW"	,REG		,0			,0		,0		},
{	0x9A	,0x40	,2	,REG_NU		,"BYDW"	,REG		,0			,0		,0		},
{	0x9A	,0x60	,2	,REG_NU		,"BYUW"	,REG		,0			,0		,0		},
{	0x9A	,0x80	,3	,REG_NUJ	,"DIDW"	,REG		,IM7		,0		,0		},
{	0x9A	,0xa0	,3	,REG_NUJ	,"DIUW"	,REG		,IM7		,0		,0		},
{	0x9A	,0xc0	,3	,REG_NUJ	,"BYDW"	,REG		,IM7		,0		,0		},
{	0x9A	,0xe0	,3	,REG_NUJ	,"BYUW"	,REG		,IM7		,0		,0		},
{	0x9B	,0		,2	,REG_NU		,"CMPW"	,REG		,0			,0		,0		},
{	0x9B	,0x40	,2	,REG_NU		,"INVW"	,REG		,0			,0		,0		},
{	0x9B	,0x80	,3	,REG_NUJ	,"CMPW"	,REG		,IM7		,0		,0		},
{	0x9B	,0xc0	,3	,REG_NUJ	,"INVW"	,REG		,IM7		,0		,0		},
{	0x9E	,0		,2	,IR_REG		,"GRE"	,IX			,REG		,0		,0		},
{	0x9E	,0x20	,2	,IR_REG		,"GRE"	,IY			,REG		,0		,0		},
{	0x9E	,0x40	,2	,IR_REG		,"GRE"	,IZ			,REG		,0		,0		},
{	0x9E	,0x60	,2	,IR_REG		,"GRE"	,US			,REG		,0		,0		},
{	0x9E	,0x80	,3	,IR_REGJ	,"GRE"	,IX			,REG		,IM7	,0		},
{	0x9E	,0xa0	,3	,IR_REGJ	,"GRE"	,IY			,REG		,IM7	,0		},
{	0x9E	,0xc0	,3	,IR_REGJ	,"GRE"	,IZ			,REG		,IM7	,0		},
{	0x9E	,0xe0	,3	,IR_REGJ	,"GRE"	,US			,REG		,IM7	,0		},
{	0x9F	,0		,2	,IR_REG		,"GRE"	,SS			,REG		,0		,0		},
{	0x9F	,0x20	,2	,IR_REG		,"GRE"	,KY			,REG		,0		,0		},
{	0x9F	,0x80	,3	,IR_REGJ	,"GRE"	,SS			,REG		,IM7	,0		},
{	0x9F	,0xa0	,3	,IR_REGJ	,"GRE"	,KY			,REG		,IM7	,0		},
{	0xA0	,0		,2	,REG_NU		,"STW"	,REG		,MIX_p|R31	,0		,0		},
{	0xA0	,0x20	,2	,REG_NU		,"STW"	,REG		,MIX_p|R30	,0		,0		},
{	0xA0	,0x40	,2	,REG_NU		,"STW"	,REG		,MIX_p|R00	,0		,0		},
{	0xA0	,0x60	,3	,REG_REG	,"STW"	,REG		,MIX_p|REG	,0		,0		},
{	0xA0	,0x80	,2	,REG_NU		,"STW"	,REG		,MIX_m|R31	,0		,0		},
{	0xA0	,0xa0	,2	,REG_NU		,"STW"	,REG		,MIX_m|R30	,0		,0		},
{	0xA0	,0xc0	,2	,REG_NU		,"STW"	,REG		,MIX_m|R00	,0		,0		},
{	0xA0	,0xe0	,3	,REG_REG	,"STW"	,REG		,MIX_m|REG	,0		,0		},
{	0xA1	,0		,2	,REG_NU		,"STW"	,REG		,MIZ_p|R31	,0		,0		},
{	0xA1	,0x20	,2	,REG_NU		,"STW"	,REG		,MIZ_p|R30	,0		,0		},
{	0xA1	,0x40	,2	,REG_NU		,"STW"	,REG		,MIZ_p|R00	,0		,0		},
{	0xA1	,0x60	,3	,REG_REG	,"STW"	,REG		,MIZ_p|REG	,0		,0		},
{	0xA1	,0x80	,2	,REG_NU		,"STW"	,REG		,MIZ_m|R31	,0		,0		},
{	0xA1	,0xa0	,2	,REG_NU		,"STW"	,REG		,MIZ_m|R30	,0		,0		},
{	0xA1	,0xc0	,2	,REG_NU		,"STW"	,REG		,MIZ_m|R00	,0		,0		},
{	0xA1	,0xe0	,3	,REG_REG	,"STW"	,REG		,MIZ_m|REG	,0		,0		},
{	0xA2	,0		,2	,REG_NU		,"STIW"	,REG		,MIX_p|R31	,0		,0		},
{	0xA2	,0x20	,2	,REG_NU		,"STIW"	,REG		,MIX_p|R30	,0		,0		},
{	0xA2	,0x40	,2	,REG_NU		,"STIW"	,REG		,MIX_p|R00	,0		,0		},
{	0xA2	,0x60	,3	,REG_REG	,"STIW"	,REG		,MIX_p|REG	,0		,0		},
{	0xA2	,0x80	,2	,REG_NU		,"STIW"	,REG		,MIX_m|R31	,0		,0		},
{	0xA2	,0xa0	,2	,REG_NU		,"STIW"	,REG		,MIX_m|R30	,0		,0		},
{	0xA2	,0xc0	,2	,REG_NU		,"STIW"	,REG		,MIX_m|R00	,0		,0		},
{	0xA2	,0xe0	,3	,REG_REG	,"STIW"	,REG		,MIX_m|REG	,0		,0		},
{	0xA3	,0		,2	,REG_NU		,"STIW"	,REG		,MIZ_p|R31	,0		,0		},
{	0xA3	,0x20	,2	,REG_NU		,"STIW"	,REG		,MIZ_p|R30	,0		,0		},
{	0xA3	,0x40	,2	,REG_NU		,"STIW"	,REG		,MIZ_p|R00	,0		,0		},
{	0xA3	,0x60	,3	,REG_REG	,"STIW"	,REG		,MIZ_p|REG	,0		,0		},
{	0xA3	,0x80	,2	,REG_NU		,"STIW"	,REG		,MIZ_m|R31	,0		,0		},
{	0xA3	,0xa0	,2	,REG_NU		,"STIW"	,REG		,MIZ_m|R30	,0		,0		},
{	0xA3	,0xc0	,2	,REG_NU		,"STIW"	,REG		,MIZ_m|R00	,0		,0		},
{	0xA3	,0xe0	,3	,REG_REG	,"STIW"	,REG		,MIZ_m|REG	,0		,0		},
{	0xA4	,0		,2	,REG_NU		,"STDW"	,REG		,MIX_p|R31	,0		,0		},
{	0xA4	,0x20	,2	,REG_NU		,"STDW"	,REG		,MIX_p|R30	,0		,0		},
{	0xA4	,0x40	,2	,REG_NU		,"STDW"	,REG		,MIX_p|R00	,0		,0		},
{	0xA4	,0x60	,3	,REG_REG	,"STDW"	,REG		,MIX_p|REG	,0		,0		},
{	0xA4	,0x80	,2	,REG_NU		,"STDW"	,REG		,MIX_m|R31	,0		,0		},
{	0xA4	,0xa0	,2	,REG_NU		,"STDW"	,REG		,MIX_m|R30	,0		,0		},
{	0xA4	,0xc0	,2	,REG_NU		,"STDW"	,REG		,MIX_m|R00	,0		,0		},
{	0xA4	,0xe0	,3	,REG_REG	,"STDW"	,REG		,MIX_m|REG	,0		,0		},
{	0xA5	,0		,2	,REG_NU		,"STDW"	,REG		,MIZ_p|R31	,0		,0		},
{	0xA5	,0x20	,2	,REG_NU		,"STDW"	,REG		,MIZ_p|R30	,0		,0		},
{	0xA5	,0x40	,2	,REG_NU		,"STDW"	,REG		,MIZ_p|R00	,0		,0		},
{	0xA5	,0x60	,3	,REG_REG	,"STDW"	,REG		,MIZ_p|REG	,0		,0		},
{	0xA5	,0x80	,2	,REG_NU		,"STDW"	,REG		,MIZ_m|R31	,0		,0		},
{	0xA5	,0xa0	,2	,REG_NU		,"STDW"	,REG		,MIZ_m|R30	,0		,0		},
{	0xA5	,0xc0	,2	,REG_NU		,"STDW"	,REG		,MIZ_m|R00	,0		,0		},
{	0xA5	,0xe0	,3	,REG_REG	,"STDW"	,REG		,MIZ_m|REG	,0		,0		},
{	0xA6	,0		,2	,REG_NU		,"PHSW"	,REG		,0			,0		,0		},
{	0xA7	,0		,2	,REG_NU		,"PHUW"	,REG		,0			,0		,0		},
{	0xA8	,0		,2	,REG_NU		,"LDW"	,REG		,MIX_p|R31	,0		,0		},
{	0xA8	,0x20	,2	,REG_NU		,"LDW"	,REG		,MIX_p|R30	,0		,0		},
{	0xA8	,0x40	,2	,REG_NU		,"LDW"	,REG		,MIX_p|R00	,0		,0		},
{	0xA8	,0x60	,3	,REG_REG	,"LDW"	,REG		,MIX_p|REG	,0		,0		},
{	0xA8	,0x80	,2	,REG_NU		,"LDW"	,REG		,MIX_m|R31	,0		,0		},
{	0xA8	,0xa0	,2	,REG_NU		,"LDW"	,REG		,MIX_m|R30	,0		,0		},
{	0xA8	,0xc0	,2	,REG_NU		,"LDW"	,REG		,MIX_m|R00	,0		,0		},
{	0xA8	,0xe0	,3	,REG_REG	,"LDW"	,REG		,MIX_m|REG	,0		,0		},
{	0xA9	,0		,2	,REG_NU		,"LDW"	,REG		,MIZ_p|R31	,0		,0		},
{	0xA9	,0x20	,2	,REG_NU		,"LDW"	,REG		,MIZ_p|R30	,0		,0		},
{	0xA9	,0x40	,2	,REG_NU		,"LDW"	,REG		,MIZ_p|R00	,0		,0		},
{	0xA9	,0x60	,3	,REG_REG	,"LDW"	,REG		,MIZ_p|REG	,0		,0		},
{	0xA9	,0x80	,2	,REG_NU		,"LDW"	,REG		,MIZ_m|R31	,0		,0		},
{	0xA9	,0xa0	,2	,REG_NU		,"LDW"	,REG		,MIZ_m|R30	,0		,0		},
{	0xA9	,0xc0	,2	,REG_NU		,"LDW"	,REG		,MIZ_m|R00	,0		,0		},
{	0xA9	,0xe0	,3	,REG_REG	,"LDW"	,REG		,MIZ_m|REG	,0		,0		},
{	0xAA	,0		,2	,REG_NU		,"LDIW"	,REG		,MIX_p|R31	,0		,0		},
{	0xAA	,0x20	,2	,REG_NU		,"LDIW"	,REG		,MIX_p|R30	,0		,0		},
{	0xAA	,0x40	,2	,REG_NU		,"LDIW"	,REG		,MIX_p|R00	,0		,0		},
{	0xAA	,0x60	,3	,REG_REG	,"LDIW"	,REG		,MIX_p|REG	,0		,0		},
{	0xAA	,0x80	,2	,REG_NU		,"LDIW"	,REG		,MIX_m|R31	,0		,0		},
{	0xAA	,0xa0	,2	,REG_NU		,"LDIW"	,REG		,MIX_m|R30	,0		,0		},
{	0xAA	,0xc0	,2	,REG_NU		,"LDIW"	,REG		,MIX_m|R00	,0		,0		},
{	0xAA	,0xe0	,3	,REG_REG	,"LDIW"	,REG		,MIX_m|REG	,0		,0		},
{	0xAB	,0		,2	,REG_NU		,"LDIW"	,REG		,MIZ_p|R31	,0		,0		},
{	0xAB	,0x20	,2	,REG_NU		,"LDIW"	,REG		,MIZ_p|R30	,0		,0		},
{	0xAB	,0x40	,2	,REG_NU		,"LDIW"	,REG		,MIZ_p|R00	,0		,0		},
{	0xAB	,0x60	,3	,REG_REG	,"LDIW"	,REG		,MIZ_p|REG	,0		,0		},
{	0xAB	,0x80	,2	,REG_NU		,"LDIW"	,REG		,MIZ_m|R31	,0		,0		},
{	0xAB	,0xa0	,2	,REG_NU		,"LDIW"	,REG		,MIZ_m|R30	,0		,0		},
{	0xAB	,0xc0	,2	,REG_NU		,"LDIW"	,REG		,MIZ_m|R00	,0		,0		},
{	0xAB	,0xe0	,3	,REG_REG	,"LDIW"	,REG		,MIZ_m|REG	,0		,0		},
{	0xAC	,0		,2	,REG_NU		,"LDDW"	,REG		,MIX_p|R31	,0		,0		},
{	0xAC	,0x20	,2	,REG_NU		,"LDDW"	,REG		,MIX_p|R30	,0		,0		},
{	0xAC	,0x40	,2	,REG_NU		,"LDDW"	,REG		,MIX_p|R00	,0		,0		},
{	0xAC	,0x60	,3	,REG_REG	,"LDDW"	,REG		,MIX_p|REG	,0		,0		},
{	0xAC	,0x80	,2	,REG_NU		,"LDDW"	,REG		,MIX_m|R31	,0		,0		},
{	0xAC	,0xa0	,2	,REG_NU		,"LDDW"	,REG		,MIX_m|R30	,0		,0		},
{	0xAC	,0xc0	,2	,REG_NU		,"LDDW"	,REG		,MIX_m|R00	,0		,0		},
{	0xAC	,0xe0	,3	,REG_REG	,"LDDW"	,REG		,MIX_m|REG	,0		,0		},
{	0xAD	,0		,2	,REG_NU		,"LDDW"	,REG		,MIZ_p|R31	,0		,0		},
{	0xAD	,0x20	,2	,REG_NU		,"LDDW"	,REG		,MIZ_p|R30	,0		,0		},
{	0xAD	,0x40	,2	,REG_NU		,"LDDW"	,REG		,MIZ_p|R00	,0		,0		},
{	0xAD	,0x60	,3	,REG_REG	,"LDDW"	,REG		,MIZ_p|REG	,0		,0		},
{	0xAD	,0x80	,2	,REG_NU		,"LDDW"	,REG		,MIZ_m|R31	,0		,0		},
{	0xAD	,0xa0	,2	,REG_NU		,"LDDW"	,REG		,MIZ_m|R30	,0		,0		},
{	0xAD	,0xc0	,2	,REG_NU		,"LDDW"	,REG		,MIZ_m|R00	,0		,0		},
{	0xAD	,0xe0	,3	,REG_REG	,"LDDW"	,REG		,MIZ_m|REG	,0		,0		},
{	0xAE	,0		,2	,REG_NU		,"PPSW"	,REG		,0			,0		,0		},
{	0xAF	,0		,2	,REG_NU		,"PPUW"	,REG		,0			,0		,0		},
{	0xB0	,0		,2	,F_IM7		,"JR"	,ZF			,IM7		,0		,0		},
{	0xB1	,0		,2	,F_IM7		,"JR"	,NCF		,IM7		,0		,0		},
{	0xB2	,0		,2	,F_IM7		,"JR"	,LZF		,IM7		,0		,0		},
{	0xB3	,0		,2	,F_IM7		,"JR"	,UZF		,IM7		,0		,0		},
{	0xB4	,0		,2	,F_IM7		,"JR"	,NZF		,IM7		,0		,0		},
{	0xB5	,0		,2	,F_IM7		,"JR"	,CF			,IM7		,0		,0		},
{	0xB6	,0		,2	,F_IM7		,"JR"	,NLZF		,IM7		,0		,0		},
{	0xB7	,0		,2	,IM7_NU		,"JR"	,IM7		,0			,0		,0		},
{	0xB8	,0		,2	,IR_REG		,"ADCW"	,MIX_p|R31	,REG		,0		,0		},
{	0xB8	,0x20	,2	,IR_REG		,"ADCW"	,MIX_p|R30	,REG		,0		,0		},
{	0xB8	,0x40	,2	,IR_REG		,"ADCW"	,MIX_p|R00	,REG		,0		,0		},
{	0xB8	,0x60	,3	,MREG_REG	,"ADCW"	,MIX_p|REG	,REG		,0		,0		},
{	0xB8	,0x80	,2	,IR_REG		,"ADCW"	,MIX_m|R31	,REG		,0		,0		},
{	0xB8	,0xa0	,2	,IR_REG		,"ADCW"	,MIX_m|R30	,REG		,0		,0		},
{	0xB8	,0xc0	,2	,IR_REG		,"ADCW"	,MIX_m|R00	,REG		,0		,0		},
{	0xB8	,0xe0	,3	,MREG_REG	,"ADCW"	,MIX_m|REG	,REG		,0		,0		},
{	0xB9	,0		,2	,IR_REG		,"ADCW"	,MIZ_p|R31	,REG		,0		,0		},
{	0xB9	,0x20	,2	,IR_REG		,"ADCW"	,MIZ_p|R30	,REG		,0		,0		},
{	0xB9	,0x40	,2	,IR_REG		,"ADCW"	,MIZ_p|R00	,REG		,0		,0		},
{	0xB9	,0x60	,3	,MREG_REG	,"ADCW"	,MIZ_p|REG	,REG		,0		,0		},
{	0xB9	,0x80	,2	,IR_REG		,"ADCW"	,MIZ_m|R31	,REG		,0		,0		},
{	0xB9	,0xa0	,2	,IR_REG		,"ADCW"	,MIZ_m|R30	,REG		,0		,0		},
{	0xB9	,0xc0	,2	,IR_REG		,"ADCW"	,MIZ_m|R00	,REG		,0		,0		},
{	0xB9	,0xe0	,3	,MREG_REG	,"ADCW"	,MIZ_m|REG	,REG		,0		,0		},
{	0xBA	,0		,2	,IR_REG		,"SBCW"	,MIX_p|R31	,REG		,0		,0		},
{	0xBA	,0x20	,2	,IR_REG		,"SBCW"	,MIX_p|R30	,REG		,0		,0		},
{	0xBA	,0x40	,2	,IR_REG		,"SBCW"	,MIX_p|R00	,REG		,0		,0		},
{	0xBA	,0x60	,3	,MREG_REG	,"SBCW"	,MIX_p|REG	,REG		,0		,0		},
{	0xBA	,0x80	,2	,IR_REG		,"SBCW"	,MIX_m|R31	,REG		,0		,0		},
{	0xBA	,0xa0	,2	,IR_REG		,"SBCW"	,MIX_m|R30	,REG		,0		,0		},
{	0xBA	,0xc0	,2	,IR_REG		,"SBCW"	,MIX_m|R00	,REG		,0		,0		},
{	0xBA	,0xe0	,3	,MREG_REG	,"SBCW"	,MIX_m|REG	,REG		,0		,0		},
{	0xBB	,0		,2	,IR_REG		,"SBCW"	,MIZ_p|R31	,REG		,0		,0		},
{	0xBB	,0x20	,2	,IR_REG		,"SBCW"	,MIZ_p|R30	,REG		,0		,0		},
{	0xBB	,0x40	,2	,IR_REG		,"SBCW"	,MIZ_p|R00	,REG		,0		,0		},
{	0xBB	,0x60	,3	,MREG_REG	,"SBCW"	,MIZ_p|REG	,REG		,0		,0		},
{	0xBB	,0x80	,2	,IR_REG		,"SBCW"	,MIZ_m|R31	,REG		,0		,0		},
{	0xBB	,0xa0	,2	,IR_REG		,"SBCW"	,MIZ_m|R30	,REG		,0		,0		},
{	0xBB	,0xc0	,2	,IR_REG		,"SBCW"	,MIZ_m|R00	,REG		,0		,0		},
{	0xBB	,0xe0	,3	,MREG_REG	,"SBCW"	,MIZ_m|REG	,REG		,0		,0		},
{	0xBC	,0		,2	,IR_REG		,"ADW"	,MIX_p|R31	,REG		,0		,0		},
{	0xBC	,0x20	,2	,IR_REG		,"ADW"	,MIX_p|R30	,REG		,0		,0		},
{	0xBC	,0x40	,2	,IR_REG		,"ADW"	,MIX_p|R00	,REG		,0		,0		},
{	0xBC	,0x60	,3	,MREG_REG	,"ADW"	,MIX_p|REG	,REG		,0		,0		},
{	0xBC	,0x80	,2	,IR_REG		,"ADW"	,MIX_m|R31	,REG		,0		,0		},
{	0xBC	,0xa0	,2	,IR_REG		,"ADW"	,MIX_m|R30	,REG		,0		,0		},
{	0xBC	,0xc0	,2	,IR_REG		,"ADW"	,MIX_m|R00	,REG		,0		,0		},
{	0xBC	,0xe0	,3	,MREG_REG	,"ADW"	,MIX_m|REG	,REG		,0		,0		},
{	0xBD	,0		,2	,IR_REG		,"ADW"	,MIZ_p|R31	,REG		,0		,0		},
{	0xBD	,0x20	,2	,IR_REG		,"ADW"	,MIZ_p|R30	,REG		,0		,0		},
{	0xBD	,0x40	,2	,IR_REG		,"ADW"	,MIZ_p|R00	,REG		,0		,0		},
{	0xBD	,0x60	,3	,MREG_REG	,"ADW"	,MIZ_p|REG	,REG		,0		,0		},
{	0xBD	,0x80	,2	,IR_REG		,"ADW"	,MIZ_m|R31	,REG		,0		,0		},
{	0xBD	,0xa0	,2	,IR_REG		,"ADW"	,MIZ_m|R30	,REG		,0		,0		},
{	0xBD	,0xc0	,2	,IR_REG		,"ADW"	,MIZ_m|R00	,REG		,0		,0		},
{	0xBD	,0xe0	,3	,MREG_REG	,"ADW"	,MIZ_m|REG	,REG		,0		,0		},
{	0xBE	,0		,2	,IR_REG		,"SBW"	,MIX_p|R31	,REG		,0		,0		},
{	0xBE	,0x20	,2	,IR_REG		,"SBW"	,MIX_p|R30	,REG		,0		,0		},
{	0xBE	,0x40	,2	,IR_REG		,"SBW"	,MIX_p|R00	,REG		,0		,0		},
{	0xBE	,0x60	,3	,MREG_REG	,"SBW"	,MIX_p|REG	,REG		,0		,0		},
{	0xBE	,0x80	,2	,IR_REG		,"SBW"	,MIX_m|R31	,REG		,0		,0		},
{	0xBE	,0xa0	,2	,IR_REG		,"SBW"	,MIX_m|R30	,REG		,0		,0		},
{	0xBE	,0xc0	,2	,IR_REG		,"SBW"	,MIX_m|R00	,REG		,0		,0		},
{	0xBE	,0xe0	,3	,MREG_REG	,"SBW"	,MIX_m|REG	,REG		,0		,0		},
{	0xBF	,0		,2	,IR_REG		,"SBW"	,MIZ_p|R31	,REG		,0		,0		},
{	0xBF	,0x20	,2	,IR_REG		,"SBW"	,MIZ_p|R30	,REG		,0		,0		},
{	0xBF	,0x40	,2	,IR_REG		,"SBW"	,MIZ_p|R00	,REG		,0		,0		},
{	0xBF	,0x60	,3	,MREG_REG	,"SBW"	,MIZ_p|REG	,REG		,0		,0		},
{	0xBF	,0x80	,2	,IR_REG		,"SBW"	,MIZ_m|R31	,REG		,0		,0		},
{	0xBF	,0xa0	,2	,IR_REG		,"SBW"	,MIZ_m|R30	,REG		,0		,0		},
{	0xBF	,0xc0	,2	,IR_REG		,"SBW"	,MIZ_m|R00	,REG		,0		,0		},
{	0xBF	,0xe0	,3	,MREG_REG	,"SBW"	,MIZ_m|REG	,REG		,0		,0		},
{	0xC0	,0		,3	,REG2_IM3	,"ADBCM",REG		,R31		,IM3	,0		},
{	0xC0	,0x20	,3	,REG2_IM3	,"ADBCM",REG		,R30		,IM3	,0		},
{	0xC0	,0x40	,3	,REG2_IM3	,"ADBCM",REG		,R00		,IM3	,0		},
{	0xC0	,0x60	,3	,REG2_IM3	,"ADBCM",REG		,REG		,IM3	,0		},
{	0xC0	,0x80	,4	,REG2_IM3J	,"ADBCM",REG		,R31		,IM3	,IM7	},
{	0xC0	,0xa0	,4	,REG2_IM3J	,"ADBCM",REG		,R30		,IM3	,IM7	},
{	0xC0	,0xc0	,4	,REG2_IM3J	,"ADBCM",REG		,R00		,IM3	,IM7	},
{	0xC0	,0xe0	,4	,REG2_IM3J	,"ADBCM",REG		,REG		,IM3	,IM7	},
{	0xC1	,0		,3	,REG2_IM3	,"SBBCM",REG		,R31		,IM3	,0		},
{	0xC1	,0x20	,3	,REG2_IM3	,"SBBCM",REG		,R30		,IM3	,0		},
{	0xC1	,0x40	,3	,REG2_IM3	,"SBBCM",REG		,R00		,IM3	,0		},
{	0xC1	,0x60	,3	,REG2_IM3	,"SBBCM",REG		,REG		,IM3	,0		},
{	0xC1	,0x80	,4	,REG2_IM3J	,"SBBCM",REG		,R31		,IM3	,IM7	},
{	0xC1	,0xa0	,4	,REG2_IM3J	,"SBBCM",REG		,R30		,IM3	,IM7	},
{	0xC1	,0xc0	,4	,REG2_IM3J	,"SBBCM",REG		,R00		,IM3	,IM7	},
{	0xC1	,0xe0	,4	,REG2_IM3J	,"SBBCM",REG		,REG		,IM3	,IM7	},
{	0xC2	,0		,3	,REG2_IM3	,"LDM"	,REG		,R31		,IM3	,0		},
{	0xC2	,0x20	,3	,REG2_IM3	,"LDM"	,REG		,R30		,IM3	,0		},
{	0xC2	,0x40	,3	,REG2_IM3	,"LDM"	,REG		,R00		,IM3	,0		},
{	0xC2	,0x60	,3	,REG2_IM3	,"LDM"	,REG		,REG		,IM3	,0		},
{	0xC2	,0x80	,4	,REG2_IM3J	,"LDM"	,REG		,R31		,IM3	,IM7	},
{	0xC2	,0xa0	,4	,REG2_IM3J	,"LDM"	,REG		,R30		,IM3	,IM7	},
{	0xC2	,0xc0	,4	,REG2_IM3J	,"LDM"	,REG		,R00		,IM3	,IM7	},
{	0xC2	,0xe0	,4	,REG2_IM3J	,"LDM"	,REG		,REG		,IM3	,IM7	},
{	0xC4	,0		,3	,REG2_IM3	,"ANCM"	,REG		,R31		,IM3	,0		},
{	0xC4	,0x20	,3	,REG2_IM3	,"ANCM"	,REG		,R30		,IM3	,0		},
{	0xC4	,0x40	,3	,REG2_IM3	,"ANCM"	,REG		,R00		,IM3	,0		},
{	0xC4	,0x60	,3	,REG2_IM3	,"ANCM"	,REG		,REG		,IM3	,0		},
{	0xC4	,0x80	,4	,REG2_IM3J	,"ANCM"	,REG		,R31		,IM3	,IM7	},
{	0xC4	,0xa0	,4	,REG2_IM3J	,"ANCM"	,REG		,R30		,IM3	,IM7	},
{	0xC4	,0xc0	,4	,REG2_IM3J	,"ANCM"	,REG		,R00		,IM3	,IM7	},
{	0xC4	,0xe0	,4	,REG2_IM3J	,"ANCM"	,REG		,REG		,IM3	,IM7	},
{	0xC5	,0		,3	,REG2_IM3	,"NACM"	,REG		,R31		,IM3	,0		},
{	0xC5	,0x20	,3	,REG2_IM3	,"NACM"	,REG		,R30		,IM3	,0		},
{	0xC5	,0x40	,3	,REG2_IM3	,"NACM"	,REG		,R00		,IM3	,0		},
{	0xC5	,0x60	,3	,REG2_IM3	,"NACM"	,REG		,REG		,IM3	,0		},
{	0xC5	,0x80	,4	,REG2_IM3J	,"NACM"	,REG		,R31		,IM3	,IM7	},
{	0xC5	,0xa0	,4	,REG2_IM3J	,"NACM"	,REG		,R30		,IM3	,IM7	},
{	0xC5	,0xc0	,4	,REG2_IM3J	,"NACM"	,REG		,R00		,IM3	,IM7	},
{	0xC5	,0xe0	,4	,REG2_IM3J	,"NACM"	,REG		,REG		,IM3	,IM7	},
{	0xC6	,0		,3	,REG2_IM3	,"ORCM"	,REG		,R31		,IM3	,0		},
{	0xC6	,0x20	,3	,REG2_IM3	,"ORCM"	,REG		,R30		,IM3	,0		},
{	0xC6	,0x40	,3	,REG2_IM3	,"ORCM"	,REG		,R00		,IM3	,0		},
{	0xC6	,0x60	,3	,REG2_IM3	,"ORCM"	,REG		,REG		,IM3	,0		},
{	0xC6	,0x80	,4	,REG2_IM3J	,"ORCM"	,REG		,R31		,IM3	,IM7	},
{	0xC6	,0xa0	,4	,REG2_IM3J	,"ORCM"	,REG		,R30		,IM3	,IM7	},
{	0xC6	,0xc0	,4	,REG2_IM3J	,"ORCM"	,REG		,R00		,IM3	,IM7	},
{	0xC6	,0xe0	,4	,REG2_IM3J	,"ORCM"	,REG		,REG		,IM3	,IM7	},
{	0xC7	,0		,3	,REG2_IM3	,"XRCM"	,REG		,R31		,IM3	,0		},
{	0xC7	,0x20	,3	,REG2_IM3	,"XRCM"	,REG		,R30		,IM3	,0		},
{	0xC7	,0x40	,3	,REG2_IM3	,"XRCM"	,REG		,R00		,IM3	,0		},
{	0xC7	,0x60	,3	,REG2_IM3	,"XRCM"	,REG		,REG		,IM3	,0		},
{	0xC7	,0x80	,4	,REG2_IM3J	,"XRCM"	,REG		,R31		,IM3	,IM7	},
{	0xC7	,0xa0	,4	,REG2_IM3J	,"XRCM"	,REG		,R30		,IM3	,IM7	},
{	0xC7	,0xc0	,4	,REG2_IM3J	,"XRCM"	,REG		,R00		,IM3	,IM7	},
{	0xC7	,0xe0	,4	,REG2_IM3J	,"XRCM"	,REG		,REG		,IM3	,IM7	},
{	0xC8	,0		,3	,REG2_IM3	,"ADBM"	,REG		,R31		,IM3	,0		},
{	0xC8	,0x20	,3	,REG2_IM3	,"ADBM"	,REG		,R30		,IM3	,0		},
{	0xC8	,0x40	,3	,REG2_IM3	,"ADBM"	,REG		,R00		,IM3	,0		},
{	0xC8	,0x60	,3	,REG2_IM3	,"ADBM"	,REG		,REG		,IM3	,0		},
{	0xC8	,0x80	,4	,REG2_IM3J	,"ADBM"	,REG		,R31		,IM3	,IM7	},
{	0xC8	,0xa0	,4	,REG2_IM3J	,"ADBM"	,REG		,R30		,IM3	,IM7	},
{	0xC8	,0xc0	,4	,REG2_IM3J	,"ADBM"	,REG		,R00		,IM3	,IM7	},
{	0xC8	,0xe0	,4	,REG2_IM3J	,"ADBM"	,REG		,REG		,IM3	,IM7	},
{	0xC9	,0		,3	,REG2_IM3	,"SBBM"	,REG		,R31		,IM3	,0		},
{	0xC9	,0x20	,3	,REG2_IM3	,"SBBM"	,REG		,R30		,IM3	,0		},
{	0xC9	,0x40	,3	,REG2_IM3	,"SBBM"	,REG		,R00		,IM3	,0		},
{	0xC9	,0x60	,3	,REG2_IM3	,"SBBM"	,REG		,REG		,IM3	,0		},
{	0xC9	,0x80	,4	,REG2_IM3J	,"SBBM"	,REG		,R31		,IM3	,IM7	},
{	0xC9	,0xa0	,4	,REG2_IM3J	,"SBBM"	,REG		,R30		,IM3	,IM7	},
{	0xC9	,0xc0	,4	,REG2_IM3J	,"SBBM"	,REG		,R00		,IM3	,IM7	},
{	0xC9	,0xe0	,4	,REG2_IM3J	,"SBBM"	,REG		,REG		,IM3	,IM7	},
{	0xCA	,0		,3	,REG_I5I3	,"ADBM"	,REG		,IM5		,IM3	,0		},
{	0xCA	,0x80	,4	,REG_I5I3J	,"ADBM"	,REG		,IM5		,IM3	,IM7	},
{	0xCB	,0		,3	,REG_I5I3	,"SBBM"	,REG		,IM5		,IM3	,0		},
{	0xCB	,0x80	,4	,REG_I5I3J	,"SBBM"	,REG		,IM5		,IM3	,IM7	},
{	0xCC	,0		,3	,REG2_IM3	,"ANM"	,REG		,R31		,IM3	,0		},
{	0xCC	,0x20	,3	,REG2_IM3	,"ANM"	,REG		,R30		,IM3	,0		},
{	0xCC	,0x40	,3	,REG2_IM3	,"ANM"	,REG		,R00		,IM3	,0		},
{	0xCC	,0x60	,3	,REG2_IM3	,"ANM"	,REG		,REG		,IM3	,0		},
{	0xCC	,0x80	,4	,REG2_IM3J	,"ANM"	,REG		,R31		,IM3	,IM7	},
{	0xCC	,0xa0	,4	,REG2_IM3J	,"ANM"	,REG		,R30		,IM3	,IM7	},
{	0xCC	,0xc0	,4	,REG2_IM3J	,"ANM"	,REG		,R00		,IM3	,IM7	},
{	0xCC	,0xe0	,4	,REG2_IM3J	,"ANM"	,REG		,REG		,IM3	,IM7	},
{	0xCD	,0		,3	,REG2_IM3	,"NAM"	,REG		,R31		,IM3	,0		},
{	0xCD	,0x20	,3	,REG2_IM3	,"NAM"	,REG		,R30		,IM3	,0		},
{	0xCD	,0x40	,3	,REG2_IM3	,"NAM"	,REG		,R00		,IM3	,0		},
{	0xCD	,0x60	,3	,REG2_IM3	,"NAM"	,REG		,REG		,IM3	,0		},
{	0xCD	,0x80	,4	,REG2_IM3J	,"NAM"	,REG		,R31		,IM3	,IM7	},
{	0xCD	,0xa0	,4	,REG2_IM3J	,"NAM"	,REG		,R30		,IM3	,IM7	},
{	0xCD	,0xc0	,4	,REG2_IM3J	,"NAM"	,REG		,R00		,IM3	,IM7	},
{	0xCD	,0xe0	,4	,REG2_IM3J	,"NAM"	,REG		,REG		,IM3	,IM7	},
{	0xCE	,0		,3	,REG2_IM3	,"ORM"	,REG		,R31		,IM3	,0		},
{	0xCE	,0x20	,3	,REG2_IM3	,"ORM"	,REG		,R30		,IM3	,0		},
{	0xCE	,0x40	,3	,REG2_IM3	,"ORM"	,REG		,R00		,IM3	,0		},
{	0xCE	,0x60	,3	,REG2_IM3	,"ORM"	,REG		,REG		,IM3	,0		},
{	0xCE	,0x80	,4	,REG2_IM3J	,"ORM"	,REG		,R31		,IM3	,IM7	},
{	0xCE	,0xa0	,4	,REG2_IM3J	,"ORM"	,REG		,R30		,IM3	,IM7	},
{	0xCE	,0xc0	,4	,REG2_IM3J	,"ORM"	,REG		,R00		,IM3	,IM7	},
{	0xCE	,0xe0	,4	,REG2_IM3J	,"ORM"	,REG		,REG		,IM3	,IM7	},
{	0xCF	,0		,3	,REG2_IM3	,"XRM"	,REG		,R31		,IM3	,0		},
{	0xCF	,0x20	,3	,REG2_IM3	,"XRM"	,REG		,R30		,IM3	,0		},
{	0xCF	,0x40	,3	,REG2_IM3	,"XRM"	,REG		,R00		,IM3	,0		},
{	0xCF	,0x60	,3	,REG2_IM3	,"XRM"	,REG		,REG		,IM3	,0		},
{	0xCF	,0x80	,4	,REG2_IM3J	,"XRM"	,REG		,R31		,IM3	,IM7	},
{	0xCF	,0xa0	,4	,REG2_IM3J	,"XRM"	,REG		,R30		,IM3	,IM7	},
{	0xCF	,0xc0	,4	,REG2_IM3J	,"XRM"	,REG		,R00		,IM3	,IM7	},
{	0xCF	,0xe0	,4	,REG2_IM3J	,"XRM"	,REG		,REG		,IM3	,IM7	},
{	0xD0	,0		,4	,IM16_REG	,"STW"	,IM16		,MR31		,0		,0		},
{	0xD0	,0x20	,4	,IM16_REG	,"STW"	,IM16		,MR30		,0		,0		},
{	0xD0	,0x40	,4	,IM16_REG	,"STW"	,IM16		,MR00		,0		,0		},
{	0xD1	,0		,4	,REG_IM16	,"LDW"	,REG		,IM16		,0		,0		},
{	0xD2	,0		,3	,REG_IM3	,"STLM"	,REG		,IM3		,0		,0		},/* LCD�o�� */
{	0xD4	,0		,3	,REG_IM3	,"PPOM"	,REG		,IM3		,0		,0		},/* LCD����|�[�g */
{	0xD6	,0		,4	,IR_IM16	,"PRE"	,IX			,IM16		,0		,0		},
{	0xD6	,0x20	,4	,IR_IM16	,"PRE"	,IY			,IM16		,0		,0		},
{	0xD6	,0x40	,4	,IR_IM16	,"PRE"	,IZ			,IM16		,0		,0		},
{	0xD6	,0x60	,4	,IR_IM16	,"PRE"	,US			,IM16		,0		,0		},
{	0xD7	,0		,4	,IR_IM16	,"PRE"	,SS			,IM16		,0		,0		},
{	0xD8	,0		,1	,NU			,"BUP"	,0			,0			,0		,0		},
{	0xD9	,0		,1	,NU			,"BDN"	,0			,0			,0		,0		},
{	0xDA	,0		,3	,REG_IM3	,"DIDM"	,REG		,IM3		,0		,0		},
{	0xDA	,0x20	,3	,REG_IM3	,"DIUM"	,REG		,IM3		,0		,0		},
{	0xDA	,0x40	,3	,REG_IM3	,"BYDM"	,REG		,IM3		,0		,0		},
{	0xDA	,0x60	,3	,REG_IM3	,"BYUM"	,REG		,IM3		,0		,0		},
{	0xDB	,0		,3	,REG_IM3	,"CMPM"	,REG		,IM3		,0		,0		},
{	0xDB	,0x40	,3	,REG_IM3	,"INVM"	,REG		,IM3		,0		,0		},
{	0xDC	,0		,2	,REG_NU		,"SUP"	,REG		,0			,0		,0		},
{	0xDD	,0		,2	,REG_NU		,"SDN"	,REG		,0			,0		,0		},
{	0xDE	,0		,2	,REG_NU		,"JP"	,MREG		,0			,0		,0		},
{	0xE0	,0		,3	,REG2_IM3	,"STM"	,REG		,MIX_p|R31	,IM3	,0		},
{	0xE0	,0x20	,3	,REG2_IM3	,"STM"	,REG		,MIX_p|R30	,IM3	,0		},
{	0xE0	,0x40	,3	,REG2_IM3	,"STM"	,REG		,MIX_p|R00	,IM3	,0		},
{	0xE0	,0x60	,3	,REG2_IM3	,"STM"	,REG		,MIX_p|REG	,IM3	,0		},
{	0xE0	,0x80	,3	,REG2_IM3	,"STM"	,REG		,MIX_m|R31	,IM3	,0		},
{	0xE0	,0xa0	,3	,REG2_IM3	,"STM"	,REG		,MIX_m|R30	,IM3	,0		},
{	0xE0	,0xc0	,3	,REG2_IM3	,"STM"	,REG		,MIX_m|R00	,IM3	,0		},
{	0xE0	,0xe0	,3	,REG2_IM3	,"STM"	,REG		,MIX_m|REG	,IM3	,0		},
{	0xE1	,0		,3	,REG2_IM3	,"STM"	,REG		,MIZ_p|R31	,IM3	,0		},
{	0xE1	,0x20	,3	,REG2_IM3	,"STM"	,REG		,MIZ_p|R30	,IM3	,0		},
{	0xE1	,0x40	,3	,REG2_IM3	,"STM"	,REG		,MIZ_p|R00	,IM3	,0		},
{	0xE1	,0x60	,3	,REG2_IM3	,"STM"	,REG		,MIZ_p|REG	,IM3	,0		},
{	0xE1	,0x80	,3	,REG2_IM3	,"STM"	,REG		,MIZ_m|R31	,IM3	,0		},
{	0xE1	,0xa0	,3	,REG2_IM3	,"STM"	,REG		,MIZ_m|R30	,IM3	,0		},
{	0xE1	,0xc0	,3	,REG2_IM3	,"STM"	,REG		,MIZ_m|R00	,IM3	,0		},
{	0xE1	,0xe0	,3	,REG2_IM3	,"STM"	,REG		,MIZ_m|REG	,IM3	,0		},
{	0xE2	,0		,3	,REG2_IM3	,"STIM"	,REG		,MIX_p|R31	,IM3	,0		},
{	0xE2	,0x20	,3	,REG2_IM3	,"STIM"	,REG		,MIX_p|R30	,IM3	,0		},
{	0xE2	,0x40	,3	,REG2_IM3	,"STIM"	,REG		,MIX_p|R00	,IM3	,0		},
{	0xE2	,0x60	,3	,REG2_IM3	,"STIM"	,REG		,MIX_p|REG	,IM3	,0		},
{	0xE2	,0x80	,3	,REG2_IM3	,"STIM"	,REG		,MIX_m|R31	,IM3	,0		},
{	0xE2	,0xa0	,3	,REG2_IM3	,"STIM"	,REG		,MIX_m|R30	,IM3	,0		},
{	0xE2	,0xc0	,3	,REG2_IM3	,"STIM"	,REG		,MIX_m|R00	,IM3	,0		},
{	0xE2	,0xe0	,3	,REG2_IM3	,"STIM"	,REG		,MIX_m|REG	,IM3	,0		},
{	0xE3	,0		,3	,REG2_IM3	,"STIM"	,REG		,MIZ_p|R31	,IM3	,0		},
{	0xE3	,0x20	,3	,REG2_IM3	,"STIM"	,REG		,MIZ_p|R30	,IM3	,0		},
{	0xE3	,0x40	,3	,REG2_IM3	,"STIM"	,REG		,MIZ_p|R00	,IM3	,0		},
{	0xE3	,0x60	,3	,REG2_IM3	,"STIM"	,REG		,MIZ_p|REG	,IM3	,0		},
{	0xE3	,0x80	,3	,REG2_IM3	,"STIM"	,REG		,MIZ_m|R31	,IM3	,0		},
{	0xE3	,0xa0	,3	,REG2_IM3	,"STIM"	,REG		,MIZ_m|R30	,IM3	,0		},
{	0xE3	,0xc0	,3	,REG2_IM3	,"STIM"	,REG		,MIZ_m|R00	,IM3	,0		},
{	0xE3	,0xe0	,3	,REG2_IM3	,"STIM"	,REG		,MIZ_m|REG	,IM3	,0		},
{	0xE4	,0		,3	,REG2_IM3	,"STDM"	,REG		,MIX_p|R31	,IM3	,0		},
{	0xE4	,0x20	,3	,REG2_IM3	,"STDM"	,REG		,MIX_p|R30	,IM3	,0		},
{	0xE4	,0x40	,3	,REG2_IM3	,"STDM"	,REG		,MIX_p|R00	,IM3	,0		},
{	0xE4	,0x60	,3	,REG2_IM3	,"STDM"	,REG		,MIX_p|REG	,IM3	,0		},
{	0xE4	,0x80	,3	,REG2_IM3	,"STDM"	,REG		,MIX_m|R31	,IM3	,0		},
{	0xE4	,0xa0	,3	,REG2_IM3	,"STDM"	,REG		,MIX_m|R30	,IM3	,0		},
{	0xE4	,0xc0	,3	,REG2_IM3	,"STDM"	,REG		,MIX_m|R00	,IM3	,0		},
{	0xE4	,0xe0	,3	,REG2_IM3	,"STDM"	,REG		,MIX_m|REG	,IM3	,0		},
{	0xE5	,0		,3	,REG2_IM3	,"STDM"	,REG		,MIZ_p|R31	,IM3	,0		},
{	0xE5	,0x20	,3	,REG2_IM3	,"STDM"	,REG		,MIZ_p|R30	,IM3	,0		},
{	0xE5	,0x40	,3	,REG2_IM3	,"STDM"	,REG		,MIZ_p|R00	,IM3	,0		},
{	0xE5	,0x60	,3	,REG2_IM3	,"STDM"	,REG		,MIZ_p|REG	,IM3	,0		},
{	0xE5	,0x80	,3	,REG2_IM3	,"STDM"	,REG		,MIZ_m|R31	,IM3	,0		},
{	0xE5	,0xa0	,3	,REG2_IM3	,"STDM"	,REG		,MIZ_m|R30	,IM3	,0		},
{	0xE5	,0xc0	,3	,REG2_IM3	,"STDM"	,REG		,MIZ_m|R00	,IM3	,0		},
{	0xE5	,0xe0	,3	,REG2_IM3	,"STDM"	,REG		,MIZ_m|REG	,IM3	,0		},
{	0xE6	,0		,3	,REG_IM3	,"PHSM"	,REG		,IM3		,0		,0		},
{	0xE7	,0		,3	,REG_IM3	,"PHUM"	,REG		,IM3		,0		,0		},
{	0xE8	,0		,3	,REG2_IM3	,"LDM"	,REG		,MIX_p|R31	,IM3	,0		},
{	0xE8	,0x20	,3	,REG2_IM3	,"LDM"	,REG		,MIX_p|R30	,IM3	,0		},
{	0xE8	,0x40	,3	,REG2_IM3	,"LDM"	,REG		,MIX_p|R00	,IM3	,0		},
{	0xE8	,0x60	,3	,REG2_IM3	,"LDM"	,REG		,MIX_p|REG	,IM3	,0		},
{	0xE8	,0x80	,3	,REG2_IM3	,"LDM"	,REG		,MIX_m|R31	,IM3	,0		},
{	0xE8	,0xa0	,3	,REG2_IM3	,"LDM"	,REG		,MIX_m|R30	,IM3	,0		},
{	0xE8	,0xc0	,3	,REG2_IM3	,"LDM"	,REG		,MIX_m|R00	,IM3	,0		},
{	0xE8	,0xe0	,3	,REG2_IM3	,"LDM"	,REG		,MIX_m|REG	,IM3	,0		},
{	0xE9	,0		,3	,REG2_IM3	,"LDM"	,REG		,MIZ_p|R31	,IM3	,0		},
{	0xE9	,0x20	,3	,REG2_IM3	,"LDM"	,REG		,MIZ_p|R30	,IM3	,0		},
{	0xE9	,0x40	,3	,REG2_IM3	,"LDM"	,REG		,MIZ_p|R00	,IM3	,0		},
{	0xE9	,0x60	,3	,REG2_IM3	,"LDM"	,REG		,MIZ_p|REG	,IM3	,0		},
{	0xE9	,0x80	,3	,REG2_IM3	,"LDM"	,REG		,MIZ_m|R31	,IM3	,0		},
{	0xE9	,0xa0	,3	,REG2_IM3	,"LDM"	,REG		,MIZ_m|R30	,IM3	,0		},
{	0xE9	,0xc0	,3	,REG2_IM3	,"LDM"	,REG		,MIZ_m|R00	,IM3	,0		},
{	0xE9	,0xe0	,3	,REG2_IM3	,"LDM"	,REG		,MIZ_m|REG	,IM3	,0		},
{	0xEA	,0		,3	,REG2_IM3	,"LDIM"	,REG		,MIX_p|R31	,IM3	,0		},
{	0xEA	,0x20	,3	,REG2_IM3	,"LDIM"	,REG		,MIX_p|R30	,IM3	,0		},
{	0xEA	,0x40	,3	,REG2_IM3	,"LDIM"	,REG		,MIX_p|R00	,IM3	,0		},
{	0xEA	,0x60	,3	,REG2_IM3	,"LDIM"	,REG		,MIX_p|REG	,IM3	,0		},
{	0xEA	,0x80	,3	,REG2_IM3	,"LDIM"	,REG		,MIX_m|R31	,IM3	,0		},
{	0xEA	,0xa0	,3	,REG2_IM3	,"LDIM"	,REG		,MIX_m|R30	,IM3	,0		},
{	0xEA	,0xc0	,3	,REG2_IM3	,"LDIM"	,REG		,MIX_m|R00	,IM3	,0		},
{	0xEA	,0xe0	,3	,REG2_IM3	,"LDIM"	,REG		,MIX_m|REG	,IM3	,0		},
{	0xEB	,0		,3	,REG2_IM3	,"LDIM"	,REG		,MIZ_p|R31	,IM3	,0		},
{	0xEB	,0x20	,3	,REG2_IM3	,"LDIM"	,REG		,MIZ_p|R30	,IM3	,0		},
{	0xEB	,0x40	,3	,REG2_IM3	,"LDIM"	,REG		,MIZ_p|R00	,IM3	,0		},
{	0xEB	,0x60	,3	,REG2_IM3	,"LDIM"	,REG		,MIZ_p|REG	,IM3	,0		},
{	0xEB	,0x80	,3	,REG2_IM3	,"LDIM"	,REG		,MIZ_m|R31	,IM3	,0		},
{	0xEB	,0xa0	,3	,REG2_IM3	,"LDIM"	,REG		,MIZ_m|R30	,IM3	,0		},
{	0xEB	,0xc0	,3	,REG2_IM3	,"LDIM"	,REG		,MIZ_m|R00	,IM3	,0		},
{	0xEB	,0xe0	,3	,REG2_IM3	,"LDIM"	,REG		,MIZ_m|REG	,IM3	,0		},
{	0xEC	,0		,3	,REG2_IM3	,"LDDM"	,REG		,MIX_p|R31	,IM3	,0		},
{	0xEC	,0x20	,3	,REG2_IM3	,"LDDM"	,REG		,MIX_p|R30	,IM3	,0		},
{	0xEC	,0x40	,3	,REG2_IM3	,"LDDM"	,REG		,MIX_p|R00	,IM3	,0		},
{	0xEC	,0x60	,3	,REG2_IM3	,"LDDM"	,REG		,MIX_p|REG	,IM3	,0		},
{	0xEC	,0x80	,3	,REG2_IM3	,"LDDM"	,REG		,MIX_m|R31	,IM3	,0		},
{	0xEC	,0xa0	,3	,REG2_IM3	,"LDDM"	,REG		,MIX_m|R30	,IM3	,0		},
{	0xEC	,0xc0	,3	,REG2_IM3	,"LDDM"	,REG		,MIX_m|R00	,IM3	,0		},
{	0xEC	,0xe0	,3	,REG2_IM3	,"LDDM"	,REG		,MIX_m|REG	,IM3	,0		},
{	0xED	,0		,3	,REG2_IM3	,"LDDM"	,REG		,MIZ_p|R31	,IM3	,0		},
{	0xED	,0x20	,3	,REG2_IM3	,"LDDM"	,REG		,MIZ_p|R30	,IM3	,0		},
{	0xED	,0x40	,3	,REG2_IM3	,"LDDM"	,REG		,MIZ_p|R00	,IM3	,0		},
{	0xED	,0x60	,3	,REG2_IM3	,"LDDM"	,REG		,MIZ_p|REG	,IM3	,0		},
{	0xED	,0x80	,3	,REG2_IM3	,"LDDM"	,REG		,MIZ_m|R31	,IM3	,0		},
{	0xED	,0xa0	,3	,REG2_IM3	,"LDDM"	,REG		,MIZ_m|R30	,IM3	,0		},
{	0xED	,0xc0	,3	,REG2_IM3	,"LDDM"	,REG		,MIZ_m|R00	,IM3	,0		},
{	0xED	,0xe0	,3	,REG2_IM3	,"LDDM"	,REG		,MIZ_m|REG	,IM3	,0		},
{	0xEE	,0		,3	,REG_IM3	,"PPSM"	,REG		,IM3		,0		,0		},
{	0xEF	,0		,3	,REG_IM3	,"PPUM"	,REG		,IM3		,0		,0		},
{	0xF0	,0		,1	,NU			,"RTN"	,ZF			,0			,0		,0		},
{	0xF1	,0		,1	,NU			,"RTN"	,NCF		,0			,0		,0		},
{	0xF2	,0		,1	,NU			,"RTN"	,LZF		,0			,0		,0		},
{	0xF3	,0		,1	,NU			,"RTN"	,UZF		,0			,0		,0		},
{	0xF4	,0		,1	,NU			,"RTN"	,NZF		,0			,0		,0		},
{	0xF5	,0		,1	,NU			,"RTN"	,CF			,0			,0		,0		},
{	0xF6	,0		,1	,NU			,"RTN"	,NLZF		,0			,0		,0		},
{	0xF7	,0		,1	,NU			,"RTN"	,0			,0			,0		,0		},
{	0xF8	,0		,1	,NU			,"NOP"	,0			,0			,0		,0		},
{	0xF9	,0		,1	,NU			,"CLT"	,0			,0			,0		,0		},
{	0xFA	,0		,1	,NU			,"FST"	,0			,0			,0		,0		},
{	0xFB	,0		,1	,NU			,"SLW"	,0			,0			,0		,0		},
{	0xFC	,0		,1	,NU			,"CANI"	,0			,0			,0		,0		},
{	0xFD	,0		,1	,NU			,"RTNI"	,0			,0			,0		,0		},
{	0xFE	,0		,1	,NU			,"OFF"	,0			,0			,0		,0		},
{	0xFF	,0		,1	,NU			,"TRP"	,0			,0			,0		,0		}
};

/*------------------------------------------------------------------*/
/*  �G���[��ʒ�`                                                  */
/*------------------------------------------------------------------*/
#define		NORM		0			/* ����I��                     */
#define		INZERR		1			/* �������ُ�                   */
#define		EOFERR		2			/* �t�@�C���I��                 */
#define		LOFLOW		5			/* �P�s�̕��������I�[�o�[����   */
#define		OPOFLOW		6			/* �I�y�����h�������I�[�o�[���� */
#define		LBOFLOW		7			/* �P�s�̕��������I�[�o�[����   */
#define		NOORG		8			/* ORG���ߒ�`���Ȃ�            */
#define		NOENT		10			/* �I�y�����h�L�q�Ȃ�           */
#define		EQUNOLBL	11			/* EQU�Ƀ��x���G���g���Ȃ�      */
#define		ILLOPR		12			/* �I�y�����h�L�q�~�X           */
#define		ILLSTART	13			/* START�����Q�ȏ゠��        */
#define		ILLCANMA	14			/* �J���}�L�q����������         */
#define		ILLDQUO		15			/* ����ٺ�ð���/���� �ُ�       */
#define		DUPLBL		16			/* ���x���L�q���Q��ȏ゠��     */
#define		ILLLBL		17			/* ���x���ɗ��p�ł��Ȃ�����     */
#define		LBLNOENT	20			/* ���x���o�^�Ȃ�               */
#define		LBNOALOC	21			/* ���x���o�^�Ȃ�               */
#define		UNDEFOPR	22			/* �Y�����߂Ȃ�/�L�q���@�̃~�X  */
#define		OFLOW		23			/* �I�y�����h�l���͈͊O         */
#define		JOFLOW		24			/* ���΃W�����v���͈͊O         */
#define		AOFLOW		25			/* �o�̓o�b�t�@�I�[�o�[         */
#define		ADOFLOW		26			/* �A�Z���u���A�h���X�I�[�o�[   */
#define		EOFLOW		27			/* ���s�A�h���X��ORG��菬����  */
#define		CALERR		28			/* �v�Z�ُ�( 0 ���Z�� )������   */
#define		IFNEST		29			/* #if�`#else�`#endif�l�X�g�ُ� */
#define		INCNOFILE	30			/* #include�t�@�C�����Ȃ�       */
#define		INCERR		31			/* #include�l�X�g�ُ�           */
#define		REGERR		32			/* ���C�����W�X�^�ԍ��ُ�       */

/* �G���[���b�Z�[�W�ϊ��e�[�u���\�� */
typedef struct err {
	unsigned short code;			/* �R�[�h�ԍ�                   */
	char	msg[32];				/* �G���[���b�Z�[�W(32�����ȓ�) */
} ERR;

/* �G���[���b�Z�[�W�ϊ��e�[�u�� */
#define		MAXERR		26
struct err errtbl[MAXERR] = {
{	LOFLOW	    ,	"Line Length is Too Long"		},
{	OPOFLOW	    ,	"Oprand Length is Too Long"		},
{	LBOFLOW	    ,	"LABEL Length is Too Long"		},
{	NOORG	    ,	"ORG Not Entry"					},
{	NOENT	    ,	"Operand Not Entry"				},
{	EQUNOLBL    ,	"EQU without Label"				},
{	ILLOPR	    ,	"Illigal Operand"				},
{	ILLSTART    ,	"START Already Defined"			},
{	ILLCANMA    ,	"Illigal [,]"					},
{	ILLDQUO	    ,	"Illigal ['']or[(]or[)]"		},
{	DUPLBL	    ,	"LABEL Already Defined"			},
{	ILLLBL	    ,	"LABEL Type Mismatch"			},
{	LBLNOENT    ,	"Undefined LABEL"				},
{	LBNOALOC    ,	"Could Not Defined LABEL"		},
{	UNDEFOPR    ,	"Operation Type Mismatch"		},
{	OFLOW	    ,	"Operand Range Over"			},
{	JOFLOW	    ,	"Jump Address Over"				},
{	AOFLOW	    ,	"Output Buffer Over Flow"		},
{	ADOFLOW	    ,	"Assemble Address Over Flow"	},
{	EOFLOW	    ,	"Execute Address Illigal"		},
{	CALERR	    ,	"Could Not Calculate"			},
{	IFNEST	    ,	"Illigal [#if] - [#endif]"		},
{	INCNOFILE   ,	"Invalid Include File Name"		},
{	INCERR	    ,	"Could Not Nest Include"		},
{	REGERR	    ,	"Illigal Register Number"		},
{	0		    ,	"Unknown"						}
};

/* /SET�I�v�V�����\���� */
typedef struct set {
	char	ent[MAXNAME+2];			/* �o�^���x������ */
	char	let[MAXNAME+2];			/* ������x������ */
} SETOPT;
