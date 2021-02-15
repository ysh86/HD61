/************************************************************************/
/*                                                                      */
/*  NAME : HD61700 CROSS ASSEMBLER SOURCE CODE                          */
/*  FILE : hd61700.c                                                    */
/*  Copyright (c) あお 'BLUE' 2003-2004                                 */
/*                                                                      */
/*  REVISION HISTORY:                                                   */
/*  Rev : 0.01  2003.01.06  最初のバージョン                            */
/*                          取りあえず内蔵アセンブラ互換で動作          */
/*  Rev : 0.02  2003.01.07  メモリ利用効率を改善。アセンブル可能な      */
/*                          行数を最大4096行から無制限にした            */
/*  Rev : 0.03  2003.01.09  未定義オペランド指定を可能とした            */
/*  Rev : 0.04  2003.01.16  未定義命令をさらに追加                      */
/*                          出力形式をpbf/basから選択できる様にした     */
/*  Rev : 0.05  2003.01.17  ラベル指定改良(メモリインデックス利用可)    */
/*  Rev : 0.05a 2003.01.21  エラーメッセージ修正                        */
/*  Rev : 0.06  2003.01.22  バッファ上限を64KBフルまで対応とする        */
/*  Rev : 0.07  2003.02.03  AI-1000/FX-870P/VX-4アセンブラに準拠        */
/*                          ・ラベル演算(優先順位なし)サポート          */
/*                            利用可能な演算子(+-/*&|)                  */
/*                          ・ラベル桁指定(.U .D)、Bit反転(.N)サポート  */
/*                          ・オペランドに文字列を指定可能とした        */
/*                          ・マルチバイト系ニモニックをXXW→XXMに変更  */
/*                          ・オペコード0x0～0xf､0x80～0x8fに対して、   */
/*                            Jump拡張をイネーブルとした。              */
/*                          ・上記Jump拡張時のラベル指定をJR LABEL形式  */
/*                            も利用可能とした。(通常はLABELのみ記述)   */
/*                          ・DW疑似命令をイネーブルとした。            */
/*                          ・上記変更に伴い/u を廃止し、セカンドオペ   */
/*                            レーション指定をディフォルトとした。      */
/*                            (/nオプションでPB-1000互換動作)           */
/*                          ・LEVEL疑似命令サポート                     */
/*  Rev : 0.08  2003.02.09  ラベル演算処理の見直し                      */
/*                          演算子優先順位や括弧の使用を可能とした      */
/*                          メモリ効率改善。オペランド桁数制限を外した。*/
/*                          命令語サポート追加(これで終了予定)          */
/*                          細かいバグ修正                              */
/*  Rev : 0.09  2003.02.16  #if～#else～#endifマクロのサポート。        */
/*                          式の評価用に[!]演算子を追加。               */
/*                          ファイル名が8文字以上の時ワーニングを表示。 */
/*                          ラベル先頭文字が数字の場合､エラーとするよう */
/*                          修正。                                      */
/*  Rev : 0.10  2003.02.21  #INCLUDE,#LIST,#NOLIST,#EJECTサポート       */
/*                          ・インクルードファイルが扱えるように修正    */
/*                            (ネストは256レベルまで)                   */
/*                          ・リスト出力の許可/禁止/改ページをサポート  */
/*                          EQU宣言にて文字列を扱えるようにした。       */
/*                          命令コード(0xDA,0xDB)に対してJump拡張を許可 */
/*                          とした。(DIDM,DIUM,BYDM,BYUM,INVM,CMPM)     */
/*                          2進数(&B)指定を追加。                       */
/*                          エラーチェック処理修正                      */
/*  Rev : 0.11  2003.02.22  EQU,LDW時の文字列指定のエンディアンを逆に   */
/*                          した。                                      */
/*  Rev : 0.12  2003.02.28  ラベルテーブルを動的に確保するように改良。  */
/*                          最大登録数制限を外した。                    */
/*                          出力メッセージ修正。                        */
/*                          Win32/DOS版のソースを統合。                 */
/*  Rev : 0.12a 2003.03.04  pbfファイル出力を修正。(DOS版のみ発生)      */
/*  Rev : 0.13  2003.03.04  命令語追加。                                */
/*  Rev : 0.14  2003.03.05  予約語制限を緩和。                          */
/*                          内部レジスタ名をラベルとして利用可とした。  */
/*  Rev : 0.15  2003.03.07  最終アドレス出力部を修正                    */
/*                          文字列の扱いを拡張し、演算も可能とした。    */
/*                          KC形式のニモニックに対応。                  */
/*  Rev : 0.16  2003.03.14  括弧検出時の改行処理を修正。                */
/*                          関係(比較)演算子に対応。                    */
/*                          演算子種別を柔軟にした。                    */
/*  Rev : 0.17  2003.03.17  BYD/BYU追加。                               */
/*  Rev : 0.18  2003.03.25  ２パス目で値が確定しないラベルがあっても    */
/*                          エラーとならない場合があったのを修正。      */
/*  Rev : 0.19  2003.04.06  JR ±IM7形式のサポート。                    */
/*  Rev : 0.20  2003.04.22  ソースファイルに出力用の拡張子(lst/bas/pbf) */
/*                          を指定した場合の問題を修正。                */
/*                          エラー処理見直し。メッセージ妥当性を向上    */
/*  Rev : 0.21  2003.04.25  PST TS,xx,GST TS,$を追加。                  */
/*  Rev : 0.22  2003.04.26  命令コード(0xD2～0xDB)に対しJump拡張を禁止  */
/*                          (DIDM,DIUM,BYDM,BYUM,INVM,CMPM)             */
/*  Rev : 0.23  2003.05.15  /SETオプションを追加                        */
/*  Rev : 0.24  2003.05.25  CODEの無いソースに対応。                    */
/*                          全角スペースを無視するようにした。          */
/*  Rev : 0.25  2003.05.29  オペランド文字列の予約文字制限をなくした。  */
/*  Rev : 0.26  2003.06.26  シングルコーテーション指定をサポート        */
/*  Rev : 0.27  2003.06.29  #include文でフルパス指定を追加              */
/*  Rev : 0.28  2003.07.25  相対ジャンプ範囲チェック処理を修正          */
/*                          コマンドライン処理の改良。                  */
/*                          /SETオプションを不要にした。                */
/*                          リスト出力時にTAB指定(/tab)を追加。         */
/*  Rev : 0.29  2003.09.01  PBF出力時にゴミが残る場合があるのを修正     */
/*  Rev : 0.30  2003.09.10  START宣言のあるソースは、拡張子をEXEで出力  */
/*                          するように修正                              */
/*  Rev : 0.31  2003.09.14  コーテーション内の括弧"()"処理を修正        */
/*                          コンパイル時にワーニングが出ていたのを修正  */
/*  Rev : 0.32  2004.01.16  "JR"タグの指定がOPR2でできないのを修正      */
/*  Rev : 0.33  2004.12.24  シンボルラベル登録(EQU)処理を改良。         */
/*                          ・1パス目に値が確定していないラベルでも利用 */
/*                            可能とした                                */
/*                          ・シンボル登録時のエラーメッセージを修正    */
/*                          オペランド演算処理を改良                    */
/*                          ・正負表現を使えるようにした                */
/*                          /qオプション追加                            */
/*                          ・クイックローダ形式をサポート              */
/*                                                                      */
/************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include"hd61700.h"
/*------------------------------------------------------------------*/
/*  定数定義                                                        */
/*------------------------------------------------------------------*/
#define SJIS_SPACE	1				/* 1:全角スペースを無視する     */
#define FORDOS  	0				/* 1:DOS用にコンパイルする      */
#if FORDOS
char	name[]	="HD61700 ASSEMBLER FOR DOS ";	/* アセンブラ名称   */
#else
char	name[]	="HD61700 ASSEMBLER ";	/* アセンブラ名称           */
#endif
char	rev[]	="Rev 0.33";			/* Revision                 */
/* 利用可能文字列 */
char	LabelStr[]	= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@_";
char	DecStr[]	= "0123456789";
char	HexStr[]	= "0123456789ABCDEFabcdef";
/*------------------------------------------------------------------*/
/*  変数定義                                                        */
/*------------------------------------------------------------------*/
char	SrcFile[MAXLINE];			/* ソースファイル名             */
char	IncFile[MAXLINE];			/* インクルードファイル名       */
char	LstFile[MAXLINE];			/* リストファイル名             */
char	OutFile[MAXLINE];			/* 出力ファイル名               */
char	ExeFile[MAXLINE];			/* 実行ファイル名               */
FILE	*IncFD[MAXINC];				/* INCLUDEファイルディスクリプタ*/
FILE	*SrcFD;						/* ソースファイルディスクリプタ */
FILE	*LstFD;						/* リストファイルディスクリプタ */
FILE	*OutFD;						/* 出力ファイルディスクリプタ   */
unsigned short	pass;				/* アセンブルパス数(0、1)       */
unsigned short	SetLabel;			/* /SET オプション登録数        */
SETOPT			SetTbl[MAXOPT];		/* /SETオプション構造体         */
unsigned short	UndefOpr;			/* 1:未公開オプション選択       */
unsigned short	OutType;			/* 0:BASIC、1:PBF形式           */
unsigned short	pr;					/* 画面出力フラグ               */
unsigned short	Tab;				/* TAB出力フラグ                */
unsigned long 	StartAdr;			/* アセンブル開始アドレス       */
unsigned long 	ExecAdr;			/* 実行開始アドレス             */
unsigned long 	AsmAdr;				/* アセンブルアドレス           */
unsigned short	StartAdrFlag;		/* アセンブル開始アドレスフラグ */
unsigned short	ExecAdrFlag;		/* 実行開始アドレスフラグ       */
unsigned short	LabelCnt;			/* ラベル登録数                 */
LBL				* LabelTbl;			/* ラベル登録テーブルポインタ   */
struct	outtbl	OutTbl;				/* 構文解析結果テーブル         */
unsigned char*	OutBuf;				/* 命令出力バッファポインタ     */
char			calcwk[MAXLINE+2];	/* ラベル演算バッファ           */
int				CalcPtr;			/* 演算バッファポインタ         */
unsigned short	Ckind;				/* 演算中の名称解決フラグ       */
int				IfLevel;			/* #if～#endif レベル           */
unsigned char	AsmFlag;			/* アセンブル禁止/許可          */
unsigned char	IfStk[IFLEVEL];		/* アセンブル禁止/許可スタック  */
unsigned short	ListFlag;			/* リスト出力フラグ(0:出力)     */
unsigned short	LineFeed;			/* #eject要求フラグ(1:要求あり) */
unsigned short	IncLevel;			/* INCLUDEレベル(レベル1まで可) */
unsigned short	SrcLine;			/* ソースリスト行番号           */
unsigned short	IncLine[MAXINC];	/* インクルードリスト行番号     */
char 			oprwk[MAXLEN+2];	/* ニモニック/オペランド用ワーク*/
									/* ※排他利用に注意すること     */

/*------------------------------------------------------------------*/
/*  プロトタイプ宣言                                                */
/*------------------------------------------------------------------*/
int main(int argc, char *argv[]);
int AsmProcess( char * );
int InitAsm( char * File );
void ClearFlag( void );
int AsmLine( void );
int AsmCodeSet( void );
int SearchOpr( unsigned short op1 ,unsigned short op2 ,unsigned short op3 ,unsigned short op4 );
int GetJumpData( unsigned short jadr , unsigned short adr  , unsigned short byte ,unsigned short *op ,unsigned short *opdat );
int GetIndexKind( char * buff , unsigned short * kind , unsigned short * data );
int GetOprKind( int num , char * buff , unsigned short * kind , unsigned short * data );
int SetLabelTbl( char * buff , unsigned short adr );
int GetLabelAdr( char * buff , unsigned short * adr );
int GetIRegKind( char * buff , unsigned short * kind );
int GetFlagKind( char * buff , unsigned short * kind );
int GetMacKind( char * buff );
unsigned short GetMnemonicKind( char * buff );
int CheckLabel( char * buff );
int ChgCode( char * dst , char * src );
int ChgKcName( char * dst , char * src );
int GetReg( char * buff , unsigned short * data );
int GetLine( FILE *fd ,char *buff );
int GetParam( char *buff );
int GetData( char *buff , unsigned short * data );
int GetCalcData( char * buff , unsigned short * kind ,unsigned short * adr );
int CalcVal(unsigned short * value );
int CalcVal0(unsigned short * value );
int CalcVal1(unsigned short * value );
int CalcVal2(unsigned short * value );
int CalcVal3( unsigned short *value );
int GetValue(unsigned short *value );
int CheckSetOpt( char * name );
int CheckSetLbl( char * name ,unsigned short sts );
void PrintList( int cnt );
void ErrPut( int cnt , int err );

/**********************************************************************/
/*   main    : main routine                                           */
/*                                                                    */
/*   処理    : メイン処理                                             */
/*   入力    : コマンドラインオプション                               */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int main(int argc, char *argv[])
{
int	rc,i;
char * ptr;

	/* 起動バージョンの表示 */
	printf( "%s%s\n",name,rev );

	/* コマンドラインのチェック */
	if( argc > (MAXOPT*2) ){
		printf("Invalid Parameters.\n");
		exit(1);
	}

	/* ソースファイル指定あり */
	if ( !argv[1] ){
		printf("Invalid Source File Name.\n");
		exit (1);
	}
	/* ファイル名称作成 */
	sprintf( SrcFile , "%s" , argv[1] );

	/* SETオプション初期化 */
	SetLabel = 0;
	memset( oprwk , 0 , MAXLEN+2 );
	memset( SetTbl , 0 , sizeof(SetTbl) );

	/* オプション初期化 */
	pr = 0;
	Tab = 0;
	UndefOpr = 1;
	OutType = 0;
	/* 起動オプション取得 */
	i=2;
	while( argv[i] ){
		/* TABリスト出力選択 */
		if (!strcmp("/tab",argv[i])||!strcmp("/TAB",argv[i])){ Tab = 1;i++; continue; }
		/* 未公開命令アセンブル選択 */
		if (!strcmp("/n",argv[i])||!strcmp("/N",argv[i])){ UndefOpr = 0;i++; continue; }
		/* PBFファイル出力選択 */
		if (!strcmp("/p",argv[i])||!strcmp("/P",argv[i])){ OutType = 1;i++; continue; }
		/* QLファイル出力選択 */
		if (!strcmp("/q",argv[i])||!strcmp("/Q",argv[i])){ OutType = 2;i++; continue; }
		/* SETオプション */
		if (!strcmp("/set",argv[i])||!strcmp("/SET",argv[i])){
			/* 次パラメータあり */
			if( !argv[++i] ){
				/* コマンドライン異常 */
				printf("Invalid /SET Parameters.\n");
				exit(1);
			}
		}
		/***********************/
		/* 代入文を登録する    */
		/***********************/
		/* コマンドライン取り出し */
		sprintf( oprwk , "%s" , argv[i] );
		/* "="を検索 */
		if ((ptr = strrchr( oprwk , '=' ))){
			if( ((int)(ptr - oprwk ) > MAXNAME )||( strlen(ptr) > (MAXNAME+1) ) ){
				/* コマンドライン異常 */
				printf("Invalid /SET name.\n");
				exit(1);
			}
			/* 登録ラベル名称取得 */
			memcpy(SetTbl[SetLabel].ent,oprwk,(int)(ptr-oprwk));
			/* 代入文字列取得 */
			sprintf(SetTbl[SetLabel].let,"%s", ptr+1 );
			/* 左辺=右辺または、同じシンボル登録ならエラー終了とする */
			if (!strcmp(SetTbl[SetLabel].ent,SetTbl[SetLabel].let)||!CheckSetOpt( SetTbl[SetLabel].ent ) ){
				/* コマンドライン異常 */
				printf("Invalid /SET name.\n");
				exit(1);
			}
			/* 16進表記を0x→&Hに修正 */
			if( !memcmp(SetTbl[SetLabel].let,"0x",2)||!memcmp(SetTbl[SetLabel].let,"0X",2) ){
				SetTbl[SetLabel].let[0]='&';
				SetTbl[SetLabel].let[1]='H';
			}
			/* SETシンボル数更新 */
			SetLabel++;
			i++;
			continue;
		}
		/* コマンドライン異常 */
		printf("Invalid Parameters.\n");
		exit(1);
	}

	/* アセンブル処理 */
	rc = AsmProcess( SrcFile );

	return(rc);
}

/**********************************************************************/
/*   InitAsm : Initialize Assembler Process                           */
/*                                                                    */
/*   処理    : アセンブラ処理初期化                                   */
/*   入力    : ソースファイル名                                       */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int InitAsm( char * File )
{
char * fptr;
char out[8];

	/* 出力バッファポインタ初期化 */
	OutBuf = 0;
	/* 各種フラグ/カウンタ初期化 */
	ClearFlag();
	/* LABELテーブル初期化 */
	LabelCnt = 0;
	LabelTbl = 0;
	/* ファイル名称作成 */
	sprintf( LstFile , "%s" , File );
	sprintf( OutFile , "%s" , File );
	/* 実行ファイル名作成 */
	if(fptr = strrchr(File,  0x5c ))
		ChgCode( ExeFile , &fptr[1] );
	else ChgCode( ExeFile , File );

	/* Listファイル名作成 */
	if ((fptr = strrchr(LstFile,  '.' )))
		sprintf( fptr,".lst" );
	else	strcat( LstFile, ".lst" ); 

	/* 出力ファイル名作成 */
	switch ( OutType ){
	case 0:
		sprintf( out ,".bas" );
		break;
	case 1:
		sprintf( out ,".pbf" );
		break;
	case 2:
		sprintf( out ,".ql" );
		break;
	}
	if ((fptr = strrchr(OutFile, '.' )))
		sprintf( fptr,"%s", out );
	else	strcat( OutFile, out );

	/* 入力ファイル名がlst/bas/pbf指定の場合、エラー終了する */
	if( !strcmp(OutFile,SrcFile) || !strcmp(LstFile,SrcFile) ){
		printf("Invalid Source File Name.\n");
		return INZERR;
	}
	/* ソースファイルOPEN */
	if ( ( SrcFD = fopen( SrcFile ,"rb" ) ) <= 0 ){
		printf("Invalid Source File Name.\n");
		return INZERR;
	}
	printf( "Input : %s \n", SrcFile );
	/* ファイル名が８文字以上の場合、ワーニングを表示 */
	if ( (strrchr(ExeFile, '.' ) - ExeFile ) > 8 ){
		printf("Warning! File Name Over 8 Chracters.\n");
	}
	return NORM;
}

/**********************************************************************/
/*   ClearFlag : Clear Flag Data                                      */
/*                                                                    */
/*   処理    : 各種フラグ初期化                                       */
/*   入力    : なし                                                   */
/*   出力    : なし                                                   */
/*                                                                    */
/**********************************************************************/
void ClearFlag( void )
{
	/* アセンブル開始アドレス初期化 */
	SrcLine = 0;
	ListFlag = 0;
	LineFeed = 0;
	IncLevel = 0;
	AsmAdr = 0;
	ExecAdr = 0;
	StartAdr = 0;
	StartAdrFlag = 0;
	ExecAdrFlag = 0;
	/* アセンブル許可 */
	AsmFlag = 0;
	/* #ifネストレベル初期化 */
	IfLevel = 0;
	/* #if～#endifスタック初期化 */
	memset( IfStk , 0 , sizeof(IfStk) );
	/* #include情報初期化 */
	memset( IncLine , 0 ,sizeof(IncLine));
	memset( IncFD , 0 , sizeof(IncFD));

}

/**********************************************************************/
/*   AsmProcess : Assembler Process Main Routine                      */
/*                                                                    */
/*   処理    : アセンブラ処理                                         */
/*   入力    : ソースファイル名                                       */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int AsmProcess( char * File )
{
char * fptr;
char out[8];
int rc,rc2,i,n;
unsigned short sum,sts,line;
unsigned short LineCnt;	/* 行番号カウンタ */
unsigned long  OutCnt,cnt;	/* 出力バイト数 */
unsigned long  BuffSize;	/* 出力バッファサイズ */
LBL *Label;
LBL *Labelwk;
	/* 初期設定 */
	if( rc = InitAsm( File ) ) return rc;

	/* SETオプション実行(確定値のみシンボル登録する) */
	if ( SetLabel ){
		/* ラベル登録実行 */
		for ( i = 0 ; i < SetLabel ; i++ ){
			/* 代入値を取得 */
			if( !( rc = GetData( SetTbl[i].let , &sts ) ) ){
				/* ラベル文字列チェック */
				if ( rc = CheckLabel( SetTbl[i].ent ) ){
					/* エラー表示 */
					printf("Invalid /SET name.\n");
					goto asm_end;
				}
				/* ラベルテーブルに登録する */
				if(rc = SetLabelTbl( SetTbl[i].ent , sts )){
					/* エラー表示 */
					printf("Invalid /SET name.\n");
					goto asm_end;
				}
			}
			/* 代入値はラベルである */
			else{
				/* ラベル文字列チェック */
				if ( rc = CheckLabel(SetTbl[i].let) ){
					/* エラー表示 */
					printf("Invalid /SET name.\n");
					goto asm_end;
				}
			}
		}
	}
	/* リストファイルOPEN */
	if ( ( LstFD = fopen( LstFile ,"w" ) ) <= 0 ){
		printf("File Create Error.\n");
		goto asm_end;
	}

	/* １パス目ラベルテーブルを作成する */
	LineCnt = 0;
	pass = 0;
	while( !rc ){
		rc = AsmLine();
		if ( rc && (rc != EOFERR) ) {
			/* エラー表示 */
			ErrPut( LineCnt , rc );
			goto asm_end;
		}
		/* 行番号更新 */
		LineCnt = !IncLevel ? ++SrcLine : ++IncLine[IncLevel-1];
	}
	/* #if～#enfifネスト異常発生 */
	if ( IfLevel ){
		/* エラー表示 */
		ErrPut( LineCnt-1 , IFNEST );
		goto asm_end;
	}
	/* コードは最大バッファ範囲内に収まる */
	if ( (BuffSize = (AsmAdr - StartAdr) ) > MAXOBJ ){
		/* 出力バッファオーバー */
		ErrPut( LineCnt-1 , AOFLOW );
		goto asm_end;
	}
	/* ソースファイル先頭にシークする */
	if( fseek(SrcFD , 0 , SEEK_SET )){
		printf("Sorce File Seek Error.\n");
		goto asm_end;
	}
	/* １パス目終了 */
	printf( " PASS 1 END \n" );

	/* 出力バッファを確保する(1Byte余分に取る) */
	if ( !( OutBuf = malloc( (unsigned short)(BuffSize+1) ) ) ){
		printf("Output Buffer Not Allocated.\n");
		goto asm_end;
	}
	/* 出力バッファ初期化 */
	memset( OutBuf, 0 , (unsigned short)(BuffSize+1) );
	/* 行番号、アセンブルアドレスを初期化する */
	ClearFlag();
	LineCnt = 0;
	OutCnt = 0;

	/* リスト出力開始 */
	fprintf( LstFD , "%s%s - ",name,rev );
	fprintf( LstFD ,"ASSEMBLE LIST OF [%s]\n", SrcFile );

	/* ２パス目ラベルアドレスを反映し、命令コードを出力する */
	rc = 0; rc2 = 0;pass++;
	while( !rc && !rc2 ){
		rc = AsmLine();
		if ( rc && (rc != EOFERR) ) {
			/* エラー表示 */
			ErrPut( LineCnt , rc );
			goto asm_end;
		}
		/* アセンブル許可状態の時のみ実行する */
		if (!AsmFlag){
			if ( rc2 = AsmCodeSet() ){
				ErrPut( LineCnt , rc2 );
				goto asm_end;
			}
			/* コードはバッファ範囲内に収まる */
			if ( ( OutCnt + (unsigned long)OutTbl.byte ) > BuffSize ){
				/* 出力バッファオーバー */
				ErrPut( LineCnt , AOFLOW );
				goto asm_end;
			}
			/* リストファイル出力 */
			PrintList( LineCnt );
			/* コード出力 */
			/* 通常命令／疑似命令種別取り出し */
			ChgCode( oprwk , OutTbl.opr[0] );
			sts = GetMnemonicKind( oprwk );
			/* ORG/DS命令以外なら、データ出力 */
			if (OutTbl.byte&&( sts != OP_ORG )&&( sts != OP_DS )){
				/* 命令コード格納 */
				memcpy( &OutBuf[OutCnt] , OutTbl.code , OutTbl.byte );
			}
			/* 出力バイト数更新 */
			OutCnt += OutTbl.byte;
		}
		else if (AsmFlag==1){
			/* リストファイル出力 */
			PrintList( LineCnt );
			AsmFlag++;
		}
		/* 行番号更新 */
		LineCnt = !IncLevel ? ++SrcLine : ++IncLine[IncLevel-1];
	}
	/* アセンブル正常終了 */
	printf( " PASS 2 END\n" );
	printf("ASSEMBLY COMPLETE, NO ERRORS FOUND\n");
	fprintf(LstFD,"\nASSEMBLY COMPLETE, NO ERRORS FOUND\n");

	/* ラベルテーブルを出力する */
	if ( LabelCnt ){
		/* ヘッダ出力 */
		fprintf( LstFD ,"\n%s%s - ",name,rev );
		fprintf( LstFD ,"MAP LIST OF [%s]\n", SrcFile );
		fprintf( LstFD ," LABEL           : ADDRESS(hex)    LABEL           : ADDRESS(hex)\n" );
		fprintf( LstFD ,"------------------------------------------------------------------\n" );
		Label = LabelTbl;
		i = 0;
		while ( Label ){
			if (!(i&1))	fprintf( LstFD ," %-16s:   %04Xh        " , Label->name , Label->adr );
			else fprintf( LstFD ," %-16s:   %04Xh\n" , Label->name , Label->adr );
			Label = Label->np;
			i++;
		}
		if (i&1) fprintf( LstFD ,"\n");
	}
	/* アセンブル情報出力 */
	fprintf( LstFD ,"\n START ADDRESS   = %04Xh\n", StartAdr );
	fprintf( LstFD ," END ADDRESS     = %04Xh\n", AsmAdr-1 );
	fprintf( LstFD ," EXECUTE ADDRESS = %04Xh\n", ExecAdr );

	/* 出力ファイル作成 */
	if ( OutCnt ){
		/* 出力用ファイルOPEN */
		if ( ( OutFD = fopen( OutFile ,"w" ) ) <= 0 ){
			printf("File Create Error.\n");
			goto asm_end;
		}
		/* 実行ファイル名作成 */
		if ( !ExecAdrFlag ) sprintf( out ,".BIN" );
		else sprintf( out ,".EXE" );
		if ((fptr = strrchr(ExeFile, '.' ))) sprintf( fptr ,"%s" ,out );
		else strcat( ExeFile ,out );
		/* ファイル作成 */
		switch( OutType ){
		/* basファイル作成 */
		case 0:
			line = 999;
#if FORDOS
			fprintf( OutFD ,"%d DATA %s,&H%X,&H%X,&H%X\n", line++,ExeFile,(unsigned short)StartAdr,(unsigned short)(AsmAdr-1),(unsigned short)ExecAdr );
#else
			fprintf( OutFD ,"%d DATA %s,&H%X,&H%X,&H%X\n", line++,ExeFile,StartAdr,AsmAdr-1,ExecAdr );
#endif
			for ( cnt = 0 , n = 0 , sum = 0 ; cnt < OutCnt ; cnt ++ ){
				/* 行番号出力 */
				if (!n) fprintf( OutFD ,"%d DATA ", line++ );
				fprintf( OutFD ,"%02X", OutBuf[cnt] );
				sum += OutBuf[cnt];
				n++;
				/* チェックサム/改行出力 */
				if ( n >= 8 ){
					fprintf( OutFD ,",%02X\n", sum&0xff );
					n = 0;
					sum = 0;
				}
			}
			/* チェックサム出力 */
			if (n) fprintf( OutFD ,",%02X\n", sum&0xff );
			break;
		/* pbfファイル作成要求あり */
		case 1:
#if FORDOS
			fprintf( OutFD ,"%s,%u,%u,%u\n", ExeFile,(unsigned short)StartAdr,(unsigned short)(AsmAdr-1),(unsigned short)ExecAdr );
#else
			fprintf( OutFD ,"%s,%u,%u,%u\n", ExeFile,StartAdr,AsmAdr-1,ExecAdr );
#endif
			for ( cnt = 0 , n = 0 , sum = 0 ; cnt < OutCnt ; cnt ++ ){
				fprintf( OutFD ,"%02X", OutBuf[cnt] );
				sum += OutBuf[cnt];
				n++;
				/* チェックサム/改行出力 */
				if ( n >= 120 ){
					fprintf( OutFD ,",%u\n", sum );
					n = 0;
					sum = 0;
				}
			}
			/* EOF出力 */
			if (n) fprintf( OutFD ,",%u\n", sum );
			break;
		/* クイックローダファイル作成 */
		case 2:
			line = 1000;
#if FORDOS
			fprintf( OutFD ,"%d DATA %u,%u,%u\n", line++,(unsigned short)StartAdr,(unsigned short)(AsmAdr-1),(unsigned short)ExecAdr );
#else
			fprintf( OutFD ,"%d DATA %u,%u,%u\n", line++,StartAdr,AsmAdr-1,ExecAdr );
#endif
			for ( cnt = 0 , n = 0 ; cnt < OutCnt ; cnt ++ ){
				/* 行番号出力 */
				if (!n) fprintf( OutFD ,"%d DATA ", line++ );
				fprintf( OutFD ,"%02X", OutBuf[cnt] );
				n++;
				if ( n >= 24 ){
					fprintf( OutFD ,"\n" );
					n = 0;
					continue;
				}
				/* カンマ出力 */
				if ( !( n % 6 ) ) fprintf( OutFD ,"," );
			}
			/* 残りを0出力 */
			while( n && ( n < 24 ) ){
				fprintf( OutFD ,"00" );
				n++;
				if ( n == 24 ){
					fprintf( OutFD ,"\n" );
					break;
				}
				/* カンマ出力 */
				if ( !( n % 6 ) ) fprintf( OutFD ,"," );
			}
			break;
		}
		/* EOF出力 */
		fprintf( OutFD ,"%c",0x1a);
		/* 出力ファイルクローズ */
		fclose(OutFD);
	}

asm_end:
	/* ラベルテーブルを解放する */
	Label = LabelTbl;
	while ( Label ){
		Labelwk = Label->np;
		free( Label );
		Label = Labelwk;
	}
	/* 出力バッファを解放する */
	if ( OutBuf ) free( OutBuf );
	/* INCLUDEファイルクローズ */
	if ( IncLevel ){
		for ( i = 0 ; i < IncLevel ;i++){
			fclose( IncFD[i] );
		}
	}
	/* ファイルクローズ */
	fclose(SrcFD);
	fclose(LstFD);

	return rc;
}
/**********************************************************************/
/*   AsmLine : Assembler Process ( one line )                         */
/*                                                                    */
/*   処理    : ソース行を１行アセンブルし、結果をOutTblに格納する     */
/*   入力    : なし                                                   */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int AsmLine( void )
{
FILE	*SourceFD;/* ソースファイルディスクリプタ */
char Work[MAXLINE+2];/* 行データ取得用ワーク */
int  rc,i,n,cnt,len,opr,kc;
unsigned short	op,opdat,sts;

	/* エラーステータス初期化 */
	rc = 0;

	/* コード変換バッファ初期化 */
	memset( &OutTbl.idx,0, sizeof(OUTTBL));
	/* 行ワークバッファ初期化 */
	memset( Work , 0 , sizeof(Work) );

	/* 現在のアセンブルアドレスを登録する */
	OutTbl.adr = (unsigned short)AsmAdr;

	/* ファイル切り替え */
	SourceFD = !IncLevel ? SrcFD : IncFD[IncLevel-1];

	/* ソースファイルから１行取り出す */
	rc = GetLine( SourceFD , Work );

	/* インクルードファイル終了 */
	if ( rc == EOFERR && IncLevel ){
		IncLevel--;
		fclose( IncFD[IncLevel] );
		IncFD[IncLevel] = 0;
		return NORM;
	}

	/* エラーか空白行である場合、終了 */
	if ( ( rc && ( rc!=EOFERR ) ) || !Work[0]) return rc;

	/* ラベル/ニモニック/オペランド/コメントに分解 */
	if( rc = GetParam( Work ) ) return rc;

	/******************************************/
	/* #if～#else～#endifマクロ処理           */
	/******************************************/
	/* ニモニック登録あり */
	if ( OutTbl.opr[0] ){
		/* 疑似命令種別チェック */
		ChgCode( oprwk , OutTbl.opr[0] );
		opr = GetMacKind( oprwk );
		switch( opr ){
		case OP_IF:
			/* ラベルかオペランド2エントリあり */
			if ( OutTbl.label || OutTbl.opr[2] ) return ILLOPR;
			/* 第1オペランドが式である */
			if( rc = GetCalcData( OutTbl.opr[1] , &op , &sts ) ) return rc;
			/* 名称が未解決な場合、処理終了する */
			if ( op == LBLNG ) return LBLNOENT;
			/* 現ネストレベルのAsmFlagを保存する */
			IfStk[IfLevel] = AsmFlag;
			/* アセンブル許可状態である */
			if (!AsmFlag){
				/* アセンブル禁止/許可セット */
				AsmFlag = (unsigned char)(sts ? 0 : (!AsmFlag ? 1 : 2 ));
			}
			/* #ifネストレベル+1 */
			IfLevel++;
			/* ネストレベルオーバー */
			if (IfLevel>=IFLEVEL) return IFNEST;
			return NORM;
		case OP_ELSE:
			/* ラベルかオペランドエントリあり */
			if ( OutTbl.label || OutTbl.opr[1] ) return ILLOPR;
			if ( !IfLevel ) return IFNEST;
			/* 上位ネストはアセンブル許可 */
			if ( !IfStk[IfLevel-1] ){
				/* アセンブル状態反転 */
				AsmFlag = (unsigned char)(AsmFlag ? 0 : 1);
			}
			return NORM;
		case OP_ENDIF:
			/* ラベルかオペランドエントリあり */
			if ( OutTbl.label || OutTbl.opr[1] ) return ILLOPR;
			if ( !IfLevel ) return IFNEST;
			/* #ifネストレベル-1 */
			IfLevel--;
			if ( IfLevel < 0 ) return IFNEST;
			/* アセンブル再開 */
			AsmFlag = IfStk[IfLevel];
			return NORM;
		default:
			break;
		}
	}
	/* アセンブル禁止なら処理終了 */
	if ( AsmFlag ) return NORM;

	/******************************************/
	/* シンボルラベル登録処理                 */
	/******************************************/
	/* ラベルあり */
	if ( OutTbl.label ){
		/* １パス目である */
		if (!pass){
			/* ラベル文字列チェック */
			if ( rc = CheckLabel(OutTbl.label) ) return rc;
			/* EQU要求である */
			ChgCode( oprwk , OutTbl.opr[0] );
			if (!strcmp( "EQU" , oprwk )){
				/* オペランドエントリが正常である */
				if ( !OutTbl.opr[1] || OutTbl.opr[2] ) return ILLOPR;
				/* 第1オペランドが数値である */
				if( !(rc = GetCalcData( OutTbl.opr[1] , &op , &sts )) ){
					/* 名称が未解決な場合、シンボル登録をしない */
					if ( op == LBLNG ) return NORM;
					/* SETオプション実行(確定値のみシンボル登録する) */
					if ( SetLabel ){
						/* ラベルは、/SET名称と一致 */
						if ( (rc = CheckSetLbl( OutTbl.label, sts )) == 1 ) return NORM;
						/* ラベル登録エラー発生 */
						if ( rc ) return rc;
					}
					/* ラベルテーブルに登録する */
					rc = SetLabelTbl( OutTbl.label, sts );
				}
				/* 行処理終了 */
				return rc;
			}
			/* EQU以外である */
			else{
				if ( !StartAdrFlag ) { rc = NOORG; return rc; }/* ORGなし */
				/* 現在のアセンブルアドレスをラベルテーブルに登録する */
				if(rc = SetLabelTbl( OutTbl.label, (unsigned short)AsmAdr )) return rc;
			}
		}
		/* ２パス目である */
		else{
			/* EQU要求である */
			ChgCode( oprwk , OutTbl.opr[0] );
			if (!strcmp( "EQU" , oprwk )){
				/* 既に登録済みなら抜ける */
				if ( GetLabelAdr( OutTbl.label , &sts ) != LBLNOENT ) return NORM;
				/* 第1オペランドが数値である */
				if( !(rc = GetCalcData( OutTbl.opr[1] , &op , &sts )) ){
					/* 名称が未解決な場合、処理終了する */
					if ( op == LBLNG ) return LBLNOENT;
					/* ラベルテーブルに登録する */
					if ( (rc = SetLabelTbl( OutTbl.label, sts )) ) return ILLLBL;
				}
				/* 行処理終了 */
				return rc;
			}
		}
	}
	/******************************************/
	/* 疑似命令/一般命令処理                  */
	/******************************************/
	/* ニモニック登録あり */
	if ( OutTbl.opr[0] ){
		/* 通常命令／疑似命令種別チェック */
		ChgCode( oprwk , OutTbl.opr[0] );
		opr = GetMnemonicKind( oprwk );
		switch( opr ){
		case OP_EQU:
			/* ラベルなしEQU処理(エラー終了) */
			if ( !pass ) rc = EQUNOLBL;
			break;
		case OP_ORG:
			/* ORG処理 */
			/* 第２オペランド以降に登録がある場合、エラー終了する */
			if ( OutTbl.opr[2] ){
				rc = ILLOPR;
				break;
			}
			/* オペランドエントリあり */
			if ( !OutTbl.opr[1] ) return ILLOPR;
			/* 第１オペランドが数値である */
			if( !(rc = GetCalcData( OutTbl.opr[1] , &op , &sts )) ){
				/* 名称が未解決な場合、処理終了する */
				if ( op == LBLNG ){ rc = LBLNOENT; break; }
				if ( sts < (unsigned short)AsmAdr ){
					rc = OFLOW;
					break;
				}
				/* 現在のアセンブルアドレスを更新する */
				if ( !StartAdrFlag ){
					StartAdr = sts;
					StartAdrFlag = 1;
				}
				else{
					/* ２回目以降は、指定バイト数分を確保する */
					OutTbl.byte = (unsigned char)( sts - (unsigned short)AsmAdr );
				}
				OutTbl.adr = sts;
				AsmAdr = sts;
			}
			break;
		case OP_START:
			/* START処理 */
			/* 第２オペランド以降に登録がある場合、エラー終了する */
			if ( OutTbl.opr[2] ){
				rc = ILLOPR;
				break;
			}
			/* 既にExecAdrエントリーあり */
			if ( ExecAdrFlag ){
				rc = ILLSTART;
				break;
			}
			/* オペランドエントリあり */
			if ( !OutTbl.opr[1] ) return ILLOPR;
			/* 第１オペランドが数値である */
			if( !(rc = GetCalcData( OutTbl.opr[1] , &op , &sts )) ){
				/* 名称解決している場合、アドレスを登録する */
				if ( op == LBLOK ){
					/* アドレスを登録する */
					ExecAdr = sts;
					ExecAdrFlag = 1;
				}
				/* 名称未解決でかつ2パス目ならエラー終了する */
				else if (pass){
					rc = LBLNOENT;
				}
			}
			break;
		case OP_DS:
			/* DS処理 */
			if ( !StartAdrFlag ) { rc = NOORG; break; }/* ORGなし */
			/* 第２オペランド以降に登録がある場合、エラー終了する */
			if ( OutTbl.opr[2] ){
				rc = ILLOPR;
				break;
			}
			/* 第１オペランドが数値である */
			if( !(rc = GetCalcData( OutTbl.opr[1] , &op , &sts )) ){
				/* 名称が未解決な場合、処理終了する */
				if ( op == LBLNG ){ rc = LBLNOENT; break; }
				/* 指定バイト数分を確保 */
				OutTbl.byte = sts;
				/* アドレスを更新する */
				if (( AsmAdr + sts ) <= MAXOBJ ) AsmAdr += sts;
				else rc = ADOFLOW;
				break;
			}
			rc = ILLOPR;
			break;
		case OP_DB:
			/* DB処理 */
			if ( !StartAdrFlag ) { rc = NOORG; break; }/* ORGなし */
			/* 第１オペランド以降に登録がない場合、エラー終了する */
			if ( !OutTbl.opr[1] ){
				rc = ILLOPR;
				break;
			}
			cnt = 0;
			i = 0;
			n = 0;
			/* オペランドエントリがある限り登録する */
			while( OutTbl.opr[cnt+1] ){
				/* 初回以外は、カンマのチェックをする */
				if ( cnt ){
					/* 先頭がカンマ以外である場合、エラー終了 */
					if ( *OutTbl.opr[cnt+1] != ',' ){
						rc = ILLCANMA;
						break;
					}
					/* 先頭文字をスキップ */
					i = 1;
				}
				/* 文字列である */
				len = strlen( OutTbl.opr[cnt+1]+i );
				/* 先頭および最終はコーテーション( = 文字列エントリ)である */
				if ( ((*(OutTbl.opr[cnt+1]+i) == 0x22 )&&(*(OutTbl.opr[cnt+1]+i+len-1) == 0x22 ))
					||((*(OutTbl.opr[cnt+1]+i) == 0x27 )&&(*(OutTbl.opr[cnt+1]+i+len-1) == 0x27 )) ){
					/* 文字列が３以下ならオペランド異常 */
					if( len < 3 ) {
						rc = ILLOPR;
						break;
					}
					/* コード登録する */
					memcpy( &OutTbl.code[n] , OutTbl.opr[cnt+1]+i+1 , len-2 );
					n += ( len - 2 );
					rc = NORM;
				}
				else{
					/* 計算式として処理する */
					if ( !(rc = GetCalcData( OutTbl.opr[cnt+1]+i , &op , &sts )) ) {
						/* 範囲外ならエラー */
						if ( sts >= 256 ){
							rc = OFLOW;
							break;
						}
						/* コード登録する */
						OutTbl.code[n++] = sts;
					}
					else break;
				}
				OutTbl.byte = (unsigned char)n;
				cnt++;
			}
			/* アドレスを更新する */
			if (( AsmAdr + n ) <= MAXOBJ ) AsmAdr += n;
			else rc = ADOFLOW;
			break;
		case OP_DW:
			/* DW処理 */
			if ( !StartAdrFlag ) { rc = NOORG; break; }/* ORGなし */
			/* 第１オペランド以降に登録がない場合、エラー終了する */
			if ( !OutTbl.opr[1] ){
				rc = ILLOPR;
				break;
			}
			cnt = 0;
			i = 0;
			n = 0;
			/* オペランドエントリがある限り登録する */
			while( OutTbl.opr[cnt+1] ){
				/* 初回以外は、カンマのチェックをする */
				if ( cnt ){
					/* 先頭がカンマ以外である場合、エラー終了 */
					if ( *OutTbl.opr[cnt+1] != ',' ){
						rc = ILLCANMA;
						break;
					}
					/* 先頭文字をスキップ */
					i = 1;
				}
				/* 計算式として処理する */
				if ( rc = GetCalcData( OutTbl.opr[cnt+1]+i , &op , &sts ) ) break;
				/* ワード単位でコード登録する */
				OutTbl.code[n++] = (unsigned char)(sts & 0xff);
				OutTbl.code[n++] = (unsigned char)((sts>>8) & 0xff);
				OutTbl.byte = (unsigned char)n;
				cnt++;
			}
			/* アドレスを更新する */
			if (( AsmAdr + n ) <= MAXOBJ ) AsmAdr += n;
			else rc = ADOFLOW;
			break;
		case OP_LEVEL:
			/* 第２オペランド以降に登録がある場合、エラー終了する */
			if ( OutTbl.opr[2] ){
				rc = ILLOPR;
				break;
			}
			/* 第１オペランドが数値である */
			if ( !(rc = GetCalcData( OutTbl.opr[1] ,&op ,&sts )) ){
				/* 名称が未解決な場合、処理終了する */
				if ( op == LBLNG ){ rc = LBLNOENT; break; }
				/* PB-1000互換コード切り替え */
				UndefOpr = (unsigned short)( sts ? 1 : 0 );
			}
			break;
		case OP_INCLUDE:
			/* 既にインクルードファイルOPEN中 */
			if ( IncLevel >= (MAXINC-1) ){ rc = INCERR; break; }
			/* オペランドエントリあり */
			if ( !OutTbl.opr[1] ){ rc = ILLOPR; break; }
			if ( (len = strlen(OutTbl.opr[1])) < 3 ){ rc = INCNOFILE; break; }
			/* 先頭および最終は括弧である */
			if ( ( OutTbl.opr[1][0] == '(' ) && ( OutTbl.opr[1][len-1] == ')' ) ){
				/* インクルードファイル名取り出し */
				memset( IncFile , 0 , sizeof(IncFile) );
				memcpy( IncFile , &OutTbl.opr[1][1] , len-2 );
				/* インクルードファイルOPEN */
				if ( ( IncFD[IncLevel] = fopen( IncFile ,"rb" ) ) <= 0 ){ rc = INCNOFILE; break; }
				/* 行番号クリア(この処理終了後+1されるので-1をセット) */
				IncLine[IncLevel] = -1;
				/* インクルードLEVEL更新 */
				IncLevel++;
				rc = NORM;
			}
			break;
		case OP_LIST:
			/* オペランドエントリあり */
			if ( OutTbl.opr[1] ) rc = ILLOPR;
			ListFlag = 0;
			break;
		case OP_NOLIST:
			/* オペランドエントリあり */
			if ( OutTbl.opr[1] ) rc = ILLOPR;
			/* リスト出力禁止 */
			ListFlag = 1;
			break;
		case OP_EJECT:
			/* オペランドエントリあり */
			if ( OutTbl.opr[1] ) rc = ILLOPR;
			/* リストLineFeed挿入要求セット */
			LineFeed = 1;
			break;
		default:
			/* 一般命令処理 */
			/* ニモニック文字長は正常 */
			if ( strlen( OutTbl.opr[0] ) >= MAXMN ) { rc = UNDEFOPR ; break; }
			/* ORGなし */
			if ( !StartAdrFlag ) { rc = NOORG; break; }
			/* 第5オペランド以降に登録がある場合、エラー終了 */
			if ( OutTbl.opr[5] ){
				rc = ILLOPR;
				break;
			}
			/* オペランド1～5を解析する */
			for ( i = 1 ; i < 5 ; i++ ){
				kc = 0;
				/* オペランド登録なしならループを抜ける */
				if (!OutTbl.opr[i]) break;
				/* 第２オペランド以降なら、先頭＝カンマ */
				if ( ( i >= 2 ) && *OutTbl.opr[i] &&( *OutTbl.opr[i] != ',' ) ){
					/* KC方式では無いか､括弧[(]以外である */
					if( !OutTbl.kc || *OutTbl.opr[i] != '(' ){
						rc = ILLCANMA;
						break;
					}
					kc = 1;
				}
				/* オペランド種別取得 */
				if ( rc = GetOprKind( i, OutTbl.opr[i]+( (i==1)||kc ? 0 : 1 ) , &op , &opdat ) ){
					if ( rc == NOENT ) rc = 0;
					break;
				}
				/* アドレス／数値 未解決ならエラー終了(２パス目) */
				if ( pass && (( op & LBLMASK ) == LBLNG ) ){
					rc = LBLNOENT;
					break;
				}
				/* オペランド種別／データを保存する */
				OutTbl.opkind[i-1] = op;
				OutTbl.opdata[i-1] = opdat;
			}
			/* オペランド種別チェックにてエラー発生 */
			if (rc) break;
			/* セカンドオペレーション拡張オプション（CASIO未公開）選択 */
			if( UndefOpr ){
				/* ニモニック＋第１～第４オペランドで検索(OP1/OP2ともR0,R30,R31有効) */
				if (!SearchOpr( MASKOP2 , MASKOP2 , MASKOP , MASKOP )) break;
				/* ニモニック＋第１～第４オペランドで検索(OP2のみR0,R30,R31有効) */
				if (!SearchOpr( MASKOP , MASKOP2 , MASKOP , MASKOP )) break;
				/* ニモニック＋第１～第４オペランドで検索(OP1のみR0,R30,R31有効) */
				if (!SearchOpr( MASKOP2 , MASKOP , MASKOP , MASKOP )) break;
			}
			/* ニモニック＋第１～第３オペランド種別 にて検索(R0,R30,R31指定なし) */
			rc = SearchOpr( MASKOP , MASKOP , MASKOP , MASKOP );
			break;
		}
	}
	return rc;
}

/**********************************************************************/
/*   SearchOpr : Search Operation Code                                */
/*                                                                    */
/*   処理    : 指定されたオペランド条件でOutBufの命令を検索する       */
/*             検索結果は、OutBufに格納される                         */
/*   入力    : オペランド検索条件(op1,op2,op3,op4)                    */
/*   出力    : エラー情報（0:該当命令あり、0以外:なし）               */
/*                                                                    */
/**********************************************************************/
int SearchOpr( unsigned short op1 ,unsigned short op2 ,unsigned short op3 ,unsigned short op4 )
{
unsigned short i;

	/* 検索対象ニモニックをHD61形式に変換する */
	if ( ChgKcName( oprwk , OutTbl.opr[0] ) ) return UNDEFOPR;
	/* ニモニック＋第１～第３オペランド種別 にて検索 */
	for ( i = 0 ; i < MAXOP ; i++ ){
		/* 該当命令あり */
		if ( !strcmp( codetbl[i].name , oprwk ) 
			&& ((codetbl[i].op1&MASKOP2) == (OutTbl.opkind[0]&op1) )
			&& ((codetbl[i].op2&MASKOP2) == (OutTbl.opkind[1]&op2) )
			&& ((codetbl[i].op3&MASKOP)  == (OutTbl.opkind[2]&op3) )
			&& ((codetbl[i].op4&MASKOP)  == (OutTbl.opkind[3]&op4) )){
			/* コードテーブルのインデックスを格納 */
			OutTbl.idx = i;
			OutTbl.byte = codetbl[i].byte;
			/* アセンブルアドレス更新 */
			if (( AsmAdr + codetbl[i].byte ) <= MAXOBJ ){
				AsmAdr += codetbl[i].byte;
				return NORM;
			}
			else return ADOFLOW;
		}
	}
	/* 該当命令なし */
	return UNDEFOPR;
}
/**********************************************************************/
/*   AsmCodeSet : Assembler Process ( 2 pass )                        */
/*                                                                    */
/*   処理    : １行分のアセンブル結果をコード化する（２パス目)        */
/*   入力    : なし                                                   */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int AsmCodeSet( void )
{
int  rc,n;
unsigned short op,opdat,sts,adr;

	/* エラーステータス初期化 */
	rc = 0;

	/* アセンブルアドレス更新 */
	adr = OutTbl.adr;

	/******************************************/
	/* #if～#else～#endifマクロ処理           */
	/******************************************/
	/* ニモニック登録あり */
	if ( OutTbl.opr[0] ){
		/* #if,#else,#endifチェック */
		ChgCode( oprwk , OutTbl.opr[0] );
		sts = (unsigned short)GetMacKind( oprwk );
		switch( sts ){
		case OP_IF:
		case OP_ELSE:
		case OP_ENDIF:
			return NORM;
		default:
			break;
		}
	}
	/******************************************/
	/* 疑似命令/一般命令処理                  */
	/******************************************/
	/* ニモニック登録あり */
	if ( OutTbl.opr[0] ){
		/* 通常命令／疑似命令種別チェック */
		ChgCode( oprwk , OutTbl.opr[0] );
		sts = GetMnemonicKind( oprwk );
		switch(sts){
		case OP_ORG:
		case OP_EQU:
		case OP_DS:
		case OP_DB:
		case OP_DW:
		case OP_INCLUDE:
		case OP_LIST:
		case OP_NOLIST:
		case OP_EJECT:
			break;
		case OP_START:
			/* START処理 */
			/* 実行開始アドレスが先頭アドレスより小さい場合はエラー終了 */
			if ( ExecAdrFlag && ( StartAdr > ExecAdr ) ) return EOFLOW;
			break;
		default:
			/* 一般命令登録あり */
			if ( OutTbl.byte ){
				/* JR命令用オペランド番号初期化 */
				n = 1;
				/* 命令コード出力 */
				OutTbl.code[0] = codetbl[OutTbl.idx].code;
				/* 命令実装種別にて分岐 */
				switch( codetbl[OutTbl.idx].kind ){
				case NU:	/* オペランドなし／1 byte 命令  */
					break;
				case IM8_NU:/* IM8        (２バイト命令）   */
					/* オペランドチェック */
					if (OutTbl.opdata[1] >= IM8bit ){ rc = OFLOW ; break; }
				case REG_NU:/* REG        (２バイト命令）   */
				case REG_NUJ:/* REG : IM7    (3バイト命令）   */
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop |(unsigned char)OutTbl.opdata[0];
					/* Jump拡張あり */
					if ( codetbl[OutTbl.idx].kind == REG_NUJ ){
						/* 相対ジャンプアドレス計算 */
						if(rc = GetJumpData( OutTbl.opdata[1] , adr ,OutTbl.byte ,&op , &opdat )) break;
						/* オペランドコード出力 */
						OutTbl.code[2] = (unsigned char)( op | opdat );
					}
					break;
				case IR_REG:/* IREG：REG  (２バイト)        */
				case IR_REGJ:/* IREG：REG :IM7 (3バイト)     */
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop |(unsigned char)OutTbl.opdata[1];
					/* Jump拡張あり */
					if ( codetbl[OutTbl.idx].kind == IR_REGJ ){
						/* 相対ジャンプアドレス計算 */
						if(rc = GetJumpData( OutTbl.opdata[2] , adr ,OutTbl.byte ,&op , &opdat )) break;
						/* オペランドコード出力 */
						OutTbl.code[2] = (unsigned char)( op | opdat );
					}
					break;
				case IR_IM8:/* IREG：IM8  (２バイト)        */
					/* オペランドチェック */
					if (OutTbl.opdata[1] >= IM8bit ){ rc = OFLOW ; break; }
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop;
					OutTbl.code[2] = (unsigned char)OutTbl.opdata[1];
					break;
				case REG_IM3:/* REG : IM3  (３バイト)        */
					/* オペランドチェック */
					if ((OutTbl.opdata[1] <= 1 )||(OutTbl.opdata[1] > IM3bit )){ rc = OFLOW ; break; }
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop|(unsigned char)OutTbl.opdata[0];
					OutTbl.code[2] = (unsigned char)((OutTbl.opdata[1]-1)<<5);
					break;
				case REG_I5I3:/* REG : IM5 : IM3  (３バイト)     */
				case REG_I5I3J:/* REG : IM5 : IM3 : IM7 (4バイト) */
					/* オペランドチェック */
					if ( OutTbl.opdata[1] > 31 ){ rc = OFLOW ; break; }
				case REG2_IM3:/* REG : REG : IM3  (３バイト)     */
				case REG2_IM3J:/* REG : REG : IM3 : IM7 (4バイト) */
					/* オペランドチェック */
					if ((OutTbl.opdata[2] <= 1 )||(OutTbl.opdata[2] > IM3bit )){ rc = OFLOW ; break; }
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop |(unsigned char)OutTbl.opdata[0];
					/* オペランドコード出力 */
					if (( codetbl[OutTbl.idx].kind == REG2_IM3 )||( codetbl[OutTbl.idx].kind == REG2_IM3J ) ){
						opdat = (!OutTbl.opdata[1]||(OutTbl.opdata[1]==31)||(OutTbl.opdata[1]==30)) ? (unsigned short)0 : OutTbl.opdata[1];
						OutTbl.code[2] = (unsigned char)opdat|(unsigned char)((OutTbl.opdata[2]-1)<<5);
					}
					else{
						/* オペランドコード出力 */
						OutTbl.code[2] = (unsigned char)OutTbl.opdata[1]|(unsigned char)((OutTbl.opdata[2]-1)<<5);
					}
					/* Jump拡張あり */
					if (( codetbl[OutTbl.idx].kind == REG2_IM3J )||( codetbl[OutTbl.idx].kind == REG_I5I3J )){
						/* 相対ジャンプアドレス計算 */
						if(rc = GetJumpData( OutTbl.opdata[3] , adr ,OutTbl.byte ,&op , &opdat )) break;
						/* オペランドコード出力 */
						OutTbl.code[3] = (unsigned char)( op | opdat );
					}
					break;
				case REG_IM7:/* REG ：IM7  (３バイト)        */
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop |(unsigned char)OutTbl.opdata[0];
					/* 相対ジャンプアドレス計算 */
					if(rc = GetJumpData( OutTbl.opdata[2] , adr ,OutTbl.byte ,&op , &opdat )) break;
					/* オペランドコード出力 */
					OutTbl.code[2] = (unsigned char)( op | opdat );
					break;
				case REG2_IM7:	/* REG : REG ：IM7  (４バイト)        */
								/* REG : IM8 ：IM7  (４バイト)        */
					/* オペランドチェック */
					if (OutTbl.opdata[1] >= IM8bit ){ rc = OFLOW ; break; }
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop |(unsigned char)OutTbl.opdata[0];
					OutTbl.code[2] = (unsigned char)OutTbl.opdata[1];
					/* 相対ジャンプアドレス計算 */
					if(rc = GetJumpData( OutTbl.opdata[2] , adr ,OutTbl.byte ,&op , &opdat )) break;
					/* オペランドコード出力 */
					OutTbl.code[3] = (unsigned char)( op | opdat );
					break;
				case REG_REG:/* REG ：REG  (３バイト)        */
				case REG_IM8:/* REG ：IM8  (３バイト)        */
					/* オペランドチェック */
					if (OutTbl.opdata[1] >= IM8bit ){ rc = OFLOW ; break; }
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop |(unsigned char)OutTbl.opdata[0];
					OutTbl.code[2] = OutTbl.opdata[1];
					break;
				case NU_IM8:/* NU ：IM8  (３バイト)        */
					/* オペランドチェック */
					if (OutTbl.opdata[0] >= IM8bit ){ rc = OFLOW ; break; }
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop;
					OutTbl.code[2] = OutTbl.opdata[0];
					break;
				case IM8_REG:/* IM8 ：REG  (３バイト)        */
				case MREG_REG:/* MREG ：REG  (３バイト)        */
					/* オペランドチェック */
					if (OutTbl.opdata[0] >= IM8bit ){ rc = OFLOW ; break; }
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop |(unsigned char)OutTbl.opdata[1];
					OutTbl.code[2] = OutTbl.opdata[0];
					break;
				case IM16_REG:/* IM16 : REG (４バイト) オペコード0xD0限定       */
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop;
					OutTbl.code[2] = (unsigned char)( OutTbl.opdata[0] & 0xff );
					OutTbl.code[3] = (unsigned char)( OutTbl.opdata[0] >> 8 );
					break;
				case REG_IM16:/* REG ：IM16 (４バイト) オペコード0xD1限定       */
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop |(unsigned char)OutTbl.opdata[0];
					OutTbl.code[2] = (unsigned char)( OutTbl.opdata[1] & 0xff );
					OutTbl.code[3] = (unsigned char)( OutTbl.opdata[1] >> 8 );
					break;
				case IR_IM16:/* IREG ：IM16 (４バイト)        */
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop;
					OutTbl.code[2] = (unsigned char)( OutTbl.opdata[1] & 0xff );
					OutTbl.code[3] = (unsigned char)( OutTbl.opdata[1] >> 8 );
					break;
				case IM7_NU:/* 数値(7bit):なし JR命令       */
					n = 0;
				case F_IM7:	/* フラグ:数値(7bit) JR命令     */
					if ( OutTbl.pm7 ){
						if ( OutTbl.opdata[n] >= 128 ) { rc = JOFLOW ; break; }
						/* 相対ジャンプアドレス設定(±IM7形式) */
						op = (unsigned short)(( OutTbl.pm7 == 2 ) ? 0x80 : 0 );
						opdat = OutTbl.opdata[n];
					}
					/* 相対ジャンプアドレス計算 */
					else if(rc = GetJumpData( OutTbl.opdata[n] , adr ,OutTbl.byte ,&op , &opdat )) break;
					/* オペランドコード出力 */
					OutTbl.code[1] = (unsigned char)( op | opdat );
					break;
				/* フラグ:数値(16bit)JP/CAL命令 */
				case F_IM16:
					/* オペランドコード出力 */
					OutTbl.code[1] = (unsigned char)( OutTbl.opdata[1] & 0xff );
					OutTbl.code[2] = (unsigned char)( OutTbl.opdata[1] >> 8 );
					break;
				/* 数値(16bit):なし JP/CAL命令  */
				case IM16_NU:
					/* オペランドコード出力 */
					OutTbl.code[1] = codetbl[OutTbl.idx].secop |(unsigned char)( OutTbl.opdata[0] & 0xff );
					OutTbl.code[2] = (unsigned char)( OutTbl.opdata[0] >> 8 );
					break;
				default:
					rc = UNDEFOPR;
					break;
				}
			}
			break;
		}
		/* アセンブルアドレス更新 */
		adr += OutTbl.byte;
	}

	return rc;
}
/**********************************************************************/
/*   GetJumpData : Get Jump Address data                              */
/*                                                                    */
/*   処理    : 相対ジャンプ数値データを取得する                       */
/*   入力    : 文字列ポインタ、データポインタ                         */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int GetJumpData( unsigned short jadr , unsigned short adr  , unsigned short byte ,unsigned short *op ,unsigned short *opdat )
{
	/* 相対ジャンプアドレス計算 */
	if ( jadr > adr ){
		/* ＋ジャンプ */
		*opdat = jadr - ( adr + ( byte - 1 ));
		*op = 0;
	}
	else{
		/* －ジャンプ */
		*opdat = ( adr + ( byte - 1 ) ) - jadr;
		*op = 0x80;
	}
	/* ジャンプアドレスオーバー */
	if ( *opdat >= IM7bit ) return JOFLOW;

	return NORM;
}
/**********************************************************************/
/*   GetLine : Get Source Line                                        */
/*                                                                    */
/*   処理    : ソースファイルから１行分の文字列を取得する             */
/*   入力    : ソースファイル名                                       */
/*   入力    : 入力ファイルＩＤ、出力バッファポインタ                 */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int GetLine( FILE *fd ,char *buff )
{
int	sts;
int	i;
	/* 1行終了まで取り出す */
	for( i = 0 ; i < MAXLINE ; i++ ){
		/* 1文字取り出し */
		sts = fgetc( fd );
		switch ( sts ){
		case '\r':
			break;
		/* １行終わり */
		case '\n':
			return NORM;
		/* ファイル終了 */
		case 0x1a:
		case EOF:
			return EOFERR;
		default:
			*buff++ = ( char )sts;
			break;
		}
	}
	return LOFLOW;
}

/**********************************************************************/
/*   GetParam : Get Parameter String                                  */
/*                                                                    */
/*   処理    : 各パラメータ文字列を取得する                           */
/*   入力    : 行バッファポインタ                                     */
/*   出力    : エラー情報（0:あり、0以外:該当文字列なし）             */
/*                                                                    */
/**********************************************************************/
/* 
 処理：与えられたワークバッファ内の文字列をパラメータ毎に分解してOutTblに登録する。
       処理概要は以下の通り。
      (1)行先頭にあるタブ／スペースは削除する。
      (2)最初の文字列にコロン[:]を検出するとラベルとして格納する。
      (3)ニモニック登録中に[&]､[$]､[(]､タブ､スペースを検出すると改行してオペランドとして格納する。
      (4)文字列の先頭以外にカンマ[,]を検出すると改行（インデックスを更新）する。
      (5)文字列先頭もしくは、括弧内[( ～ )]に記述されたタブ／スペースは詰めて格納する。
       （タブ／スペースは基本的に格納しない）
        ただし、第3オペランド以降、JRタグを検出した場合は､スペースを1つだけ挿入する。
      (6)ダブルコーテーション["]を検出すると、次に["]が登場するか行末までそのまま格納する。
      (7)セミコロン[;]を検出すると、それ以降、行末までをコメントとして登録する。
        ただしダブルコーテーション中はそのまま登録する。
      (8)KC方式対応で、文字列先頭以外の括弧[(]を検出時に前の文字が[!+-*／＃|^%,($]以外の場合、
         改行する。この時、KCフラグをONにする。(ニモニック変換の妥当性をチェックする為）
      (9)シングルコーテーション[']を検出すると、次に[']が登場するか行末までそのまま格納する。
         ダブルコーテーションとは排他動作する。
*/
int GetParam( char *buff )
{
int	len;
int	j,n;
int label;
int kakko;
int dq,sq;
char *Opr;
	/* オペランドバッファポインタ初期化 */
	OutTbl.opr[0] = OutTbl.line;
	Opr = OutTbl.line;

	/* 1行終了まで取り出す */
	len = strlen( buff );
	for(  j = 0 , n = 0 ,label = 0,kakko = 0 ,dq = 0,sq = 0 ; ( n < MAXOPR )&&( j <len ) ; buff++ ){
		switch ( *buff & 0xff ){
		case ';':
			/* コメント検出 */
			/* コーテション時 */
			if ( dq || sq ){
				/* パラメータ登録する */
				Opr[j++] = *buff;
				break;
			}
			/* コメントポインタ設定 */
			OutTbl.comment = Opr+j+1;
			/* 残りの文字列をコメントとして格納 */
			memcpy( OutTbl.comment , buff , strlen(buff));
			/* エントリのないオペランドポインタはNULLにする */
			if (!j)	OutTbl.opr[n] = 0;
			return NORM;
		case '\n':
		case 0x0:
			/* 改行検出で終了 */
			/* 括弧およびコーテーション処理中ならエラー */
			if ( kakko || dq || sq ){
				return ILLDQUO;
			}
			/* エントリのないオペランドポインタはNULLにする */
			if (!j) OutTbl.opr[n] = 0;
			return NORM;
		case ':':
			/* コーテション/括弧内 */
			if ( dq || sq || kakko ){
				/* パラメータ登録する */
				Opr[j++]=*buff;
				break;
			}
			/* ラベル取り出し */
			if ( !label && !n ){
				/* ラベルを登録する */
				if ( j > MAXNAME ) return LBOFLOW;
				OutTbl.label = Opr;
				/* 格納バッファポインタを更新する */
				Opr += j + 1;
				OutTbl.opr[0] = Opr;
				j = 0;
				label++;
				break;
			}
			/* ２重ラベルはエラー終了 */
			else if (!n) return ILLLBL;
			return ILLOPR;
		case ',':
			/* 行の途中でカンマ検出 */
			if ( !dq && !sq && j ){
				/* 改行する */
				Opr += j + 1;
				OutTbl.opr[++n] = Opr;
				j = 0;
			}
			/* パラメータ登録する */
			Opr[j++]=*buff;
			break;
		case ')':
			/* パラメータ登録する */
			Opr[j++]=*buff;
			/* コーテション時 */
			if ( dq || sq ) break;
			/* とじ括弧検出 */
			if ( kakko ){
				kakko--;
				break;
			}
			/* エラー終了 */
			else return ILLDQUO;
#if SJIS_SPACE
		case 0x81:
			/* 全角スペースではない */
			if ( buff[1] != 0x40 ){
				/* パラメータ登録する */
				Opr[j++]=*buff;
				break;
			}
			/* コーテーション内は登録する */
			if ( dq||sq ){
				/* パラメータ登録する */
				Opr[j++]=*buff;
				break;
			}
			/* ポインタ更新 */
			buff++;
			/* 文字列先頭か括弧内なら読み飛ばす */
			if ( !j ) break;
			/* ニモニック登録中ならば、改行する */
			if ( !n ){
				/* 改行する */
				Opr += j + 1;
				OutTbl.opr[++n] = Opr;
				j = 0;
			}
			break;
#endif
		case 0x20:
		case '\t':
			/* 第２オペランド以降でかつ、JRタグである */
			if ( (n >= 2)&&( j == 3 )&&
				( !strcmp( &Opr[0],",jr" )||!strcmp( &Opr[0],",JR" ) ) ){
				/* スペースとして登録する */
				Opr[j++] = 0x20;
				break;
			}
			/* コーテーション内は登録する */
			if ( dq || sq ){
				/* パラメータ登録する */
				Opr[j++]=*buff;
				break;
			}
			/* 文字列先頭か括弧内なら読み飛ばす */
			if ( !j ) break;
			/* ニモニック登録中ならば、改行する */
			if ( !n ){
				/* 改行する */
				Opr += j + 1;
				OutTbl.opr[++n] = Opr;
				j = 0;
			}
			break;
		/* シングルコーテーションマーク検出 */
		case 0x27:
			/* ダブルコーテーション中なら、パラメータ登録する */
			if ( dq ){
				Opr[j++]=*buff;
				break;
			}
			/* シングルコーテーションマーク初検出 */
			if ( !sq ){
				sq++;
				/* 先頭オペランドである */
				if ( j && !n ){
					/* 改行する */
					Opr += j + 1;
					OutTbl.opr[++n] = Opr;
					j = 0;
				}
				/* パラメータ登録 */
				Opr[j++]=*buff;
			}
			else{
				sq--;
				/* パラメータ登録する */
				Opr[j++]=*buff;
			}
			break;
		case 0x22:
			/* シングルコーテーション中なら、パラメータ登録する */
			if ( sq ){
				Opr[j++]=*buff;
				break;
			}
			/* ダブルコーテーションマーク初検出 */
			if ( !dq ){
				dq++;
				/* 先頭オペランドである */
				if ( j && !n ){
					/* 改行する */
					Opr += j + 1;
					OutTbl.opr[++n] = Opr;
					j = 0;
				}
				/* パラメータ登録 */
				Opr[j++]=*buff;
			}
			else{
				dq--;
				/* パラメータ登録する */
				Opr[j++]=*buff;
			}
			break;
		case '(':
			/* 括弧検出 */
			if ( !dq && !sq ) kakko++;
			/* １つ前の文字が演算子およびカンマ以外の時、改行する(KC対応) */
			if ( n && j && !dq && !sq ){
				if ( !strchr( "!+-*/#|^%=<>,($&" , Opr[j-1] ) ){
					/* KC方式フラグセット */
					OutTbl.kc = 1;
					Opr += j + 1;
					OutTbl.opr[++n] = Opr;
					j = 0;
				}
			}
		case '+':
		case '-':
		case '&':
		case '$':
			/* これらの文字が先頭オペランドで検出された場合、改行する */
			if ( !n && !dq && !sq && j){
				Opr += j + 1;
				OutTbl.opr[++n] = Opr;
				j = 0;
			}
		default:
			/* 上記以外の場合、パラメータ登録する */
			Opr[j++]=*buff;
			break;
		}
		/* 最大オペランド長を越えた場合、処理終了 */
		if ( j >= MAXLEN ) return OPOFLOW;
	}
	/* 括弧およびコーテーション処理中ならエラー */
	if ( kakko || dq || sq ) return ILLDQUO;

	/* 正常終了 */
	return NORM;
}

/**********************************************************************/
/*   GetOprKind : Get Opecode kind                                    */
/*                                                                    */
/*   処理    : 与えられた文字列を各種オペコードに分解する             */
/*   入力    : 入力ポインタ、オペコード種別                           */
/*   出力    : エラー情報（0:正常、0以外:エラー）                     */
/*                                                                    */
/**********************************************************************/
int GetOprKind( int num , char * buff , unsigned short * kind , unsigned short * data )
{
int rc;
unsigned short op,sts;
char mnwk[MAXMN];	/* ニモニック変換用ワーク */

	/* 種別情報初期化 */
	*kind = 0;
	*data = 0;
	/* 要求文字列エントリがない場合、エラー終了 */
	if ( !buff[0] ) return NOENT;

	/* 文字コード変換(Nullならエラー終了) */
	if(!( ChgCode( oprwk , buff ) ) ) return NOENT;

	/* JRタグである */
	if( !memcmp(oprwk,"JR ", 3 ) ){
		/* 計算式として処理する */
		rc = GetCalcData( &buff[3] , kind , data );
		return rc;
	}
	/* オペランド1の時のみチェックする */
	if ( num==1 ){
		/* 内部レジスタ指定である */
		if ( !GetIRegKind( buff , &op ) ){
			*kind = op;
			return NORM;
		}
		/* フラグ指定である */
		if ( !GetFlagKind( buff , &op ) ){
			*kind = op;
			return NORM;
		}
	}
	/* メインレジスタ指定である */
	if ( !( rc = GetReg( buff , &sts ) ) ){
		*data = sts;
		switch( sts ){
		case 0:  *kind = R00; break;
		case 30: *kind = R30; break;
		case 31: *kind = R31; break;
		default: *kind = REG; break;
		}
		return NORM;
	}
	/* オペランド記述がメインレジスタ指定以外 */
	if ( rc != ILLOPR ) return rc;
	/* メモリインデックス指定である */
	if ( !( rc = GetIndexKind( buff , &op , &sts ) ) ){
		*data = sts;
		*kind = op;
		return NORM;
	}
	/* オペランド記述がインデックス指定以外 */
	if ( rc != ILLOPR ) return rc;
	/* JR命令である */
	ChgCode( mnwk , OutTbl.opr[0] );
	if ( !strcmp( mnwk , "JR" ) ){
		/* ±IM7形式である */
		if( (buff[0]=='+')||(buff[0]=='-') ){
			OutTbl.pm7 = 1;
			if (buff[0]=='-')
				OutTbl.pm7 = 2;
			/* ポインタ更新 */
			buff++;
		}
	}
	/* 計算式として処理する */
	if ( !( rc = GetCalcData( buff , kind , data ) ) ) return NORM;
	return rc;
}

/**********************************************************************/
/*   GetIndexKind : Get Memory Index Kind                             */
/*                                                                    */
/*   処理    : メモリインデックス種別を取得する                       */
/*   入力    : 入力ポインタ、オペコード種別                           */
/*   出力    : ニモニック種別(kind/opr)                               */
/*           : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int GetIndexKind( char * buff , unsigned short * kind , unsigned short * data )
{
int	i,len,rc;
unsigned short opr,sts,knd;
char Indexwk[6];

	/* メモリインデックス指定である */
	len = strlen( buff );
	memcpy( oprwk , buff , len );
	if ( ( oprwk[0] == '(' )&&( oprwk[len-1] == ')' ) ){
		oprwk[len-1] = 0;
		/* メインレジスタによるインデックスである */
		if ( !( rc = GetReg( &oprwk[1] , &sts ) ) ){
			*data = sts;
			switch(sts){
			case 0:  *kind = MR00; break;
			case 30: *kind = MR30; break;
			case 31: *kind = MR31; break;
			default: *kind = MREG; break;
			}
			return NORM;
		}
		/* オペランド記述がメインレジスタ指定以外 */
		if ( rc != ILLOPR ) return rc;
		/* インデックス種別をサーチする */
		memcpy( Indexwk , oprwk , 4 );
		Indexwk[4] = 0;
		/* テーブルサーチ */
		for ( i = 0 ; i < MAXIDX ; i++ ){
			/* IX、IZ指定である */
			if (!strcmp( Indexwk , moprtbl[i].name )){
				sts = moprtbl[i].code;
				/* メインレジスタによるインデックスである */
				if ( !( rc = GetReg( &oprwk[4] , &opr ) ) ){
					*data = opr;
					switch(opr){
					case 0:  *kind = sts|(unsigned short)R00; break;
					case 30: *kind = sts|(unsigned short)R30; break;
					case 31: *kind = sts|(unsigned short)R31; break;
					default: *kind = sts|(unsigned short)REG; break;
					}
					return NORM;
				}
				/* オペランド記述がメインレジスタ指定以外 */
				if ( rc != ILLOPR ) return rc;
				/* 計算式として処理する */
				if ( !( rc = GetCalcData( &oprwk[4] , &knd , &opr ) ) ){
					/* 範囲外の値である */
					if ( opr > 255 ) return OFLOW;
					*data = opr;
					*kind = sts|knd;
					return NORM;
				}
				return rc;
			}
		}
	}
	/* 該当なし */
	return ILLOPR;
}
/**********************************************************************/
/*   GetIRegKind : Get Internal Register Kind                         */
/*                                                                    */
/*   処理    : 内部レジスタ種別を取得する                             */
/*   入力    : 入力ポインタ、オペコード種別                           */
/*   出力    : ニモニック種別(kind)                                   */
/*           : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int GetIRegKind( char * buff , unsigned short * kind )
{
int	i;
char mnwk[MAXMN];	/* ニモニック変換用ワーク */
	i = 0;
	/* ニモニック種別チェック */
	ChgCode( mnwk , OutTbl.opr[0] );
	/* 内部レジスタ利用命令テーブルサーチ */
	while( strcmp( mnwk , irtbl[i].name ) ){
		/* 該当命令では無い場合、処理終了 */
		if ( ++i >= MAXIR ) return ILLOPR;
	}
	/* オペランド長は正常である */
	if ( !strlen(buff) || strlen(buff)>MAXMN ) return ILLOPR;
	/* 大文字に変換する */
	ChgCode( mnwk , buff );
	/* 内部レジスタテーブルサーチ */
	for ( i = 0 ; i < MAXIREG ; i++ ){
		if (!strcmp( mnwk , regtbl[i].name )){
			/* 内部レジスタコードを返す */
			*kind = regtbl[i].code;
			return NORM;
		}
	}
	/* 該当なしを返す */
	return ILLOPR;
}
/**********************************************************************/
/*   GetFlagKind : Get Flag Register Kind                             */
/*                                                                    */
/*   処理    : 条件フラグ種別を取得する                               */
/*   入力    : 入力ポインタ、オペコード種別                           */
/*   出力    : ニモニック種別(kind)                                   */
/*           : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int GetFlagKind( char * buff , unsigned short * kind )
{
int	i;
char mnwk[MAXMN];	/* ニモニック変換用ワーク */
	i = 0;
	/* ニモニック種別チェック */
	ChgCode( mnwk , OutTbl.opr[0] );
	/* フラグ利用命令テーブルサーチ */
	while( strcmp( mnwk , fltbl[i].name ) ){
		/* 該当命令では無い場合、処理終了 */
		if ( ++i >= MAXFL ) return ILLOPR;
	}
	/* オペランド長は正常である */
	if ( !strlen(buff) || strlen(buff) > MAXMN ) return ILLOPR;
	/* 大文字に変換する */
	ChgCode( mnwk , buff );
	/* フラグテーブルサーチ */
	for ( i = 0 ; i < MAXFLAG ; i++ ){
		if (!strcmp( mnwk , flagtbl[i].name )){
			/* フラグコードを返す */
			*kind = flagtbl[i].code;
			return NORM;
		}
	}
	/* 該当なしを返す */
	return ILLOPR;
}
/**********************************************************************/
/*   GetReg : Get Register Number                                     */
/*                                                                    */
/*   処理    : 与えられた文字列からレジスタ番号を取得する             */
/*   入力    : 入力ポインタ、オペコード種別                           */
/*   出力    : レジスタ番号(data)                                     */
/*           : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int GetReg( char * buff , unsigned short * data )
{
unsigned short sts,kind;
int rc;
	/* レジスタ指定である */
	if ( buff[0] == '$' ){
		/* レジスタ番号取得 */
		if(!(rc = GetCalcData( &buff[1] , &kind , &sts ) )){
			/* 名称未解決の場合、エラー終了する */
			if ( kind == LBLNG ) return LBLNOENT;
			/* レジスタ番号正常 */
			if ( sts <= 31 ){
				*data = sts;
				return NORM;
			}
			/* エラー終了 */
			*data = 0;
			return REGERR;
		}
		else return rc;
	}
	/* エラー終了 */
	*data = 0;
	/* レジスタ指定ではない */
	return ILLOPR;
}
/**********************************************************************/
/*   SetLabelTbl : Entry Label table                                  */
/*                                                                    */
/*   処理    : ラベルテーブルにラベルとアドレスを登録する             */
/*   入力    : ラベルポインタ、登録アドレス値（0:以外）               */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int SetLabelTbl( char * buff , unsigned short adr )
{
LBL * Label;
LBL * Labelwk;

	/* 先頭ラベルポインタセット */
	Label = LabelTbl;
	while( Label ){
		/* 該当ラベル名検索 */
		if (!strcmp( Label->name , buff )){
			/* 既に同じ名称が使われている場合、エラー終了 */
			return DUPLBL;
		}
		/* 最終ラベルアドレス到達 */
		if ( !Label->np ) break;
		/* ラベルポインタ更新 */
		Label = Label->np;
	}
	/* ラベルテーブル確保 */
	if ( Labelwk = malloc( sizeof(LBL)+strlen(buff) ) ){
		memset( Labelwk , 0 , sizeof(LBL)+strlen(buff) );
	}
	else return LBNOALOC;

	/* 初回登録なら先頭ポインタに登録する */
	if ( !LabelTbl ) LabelTbl = Labelwk;
	/* 確保したポインタを次ポインタとして登録する */
	else Label->np = Labelwk;

	/* ラベルポインタ更新 */
	Label = Labelwk;
	/* ラベル名称をテーブルに登録する */
	memcpy( Label->name , buff , strlen(buff) );
	/* 現在のアセンブルアドレスをラベルテーブルに登録する */
	Label->adr = adr;
	/* ラベル登録数更新 */
	LabelCnt++;

	return NORM;
}

/**********************************************************************/
/*   GetLabelAdr : Get Label Address                                  */
/*                                                                    */
/*   処理    : ラベル名からアドレスを検索する                         */
/*   入力    : ラベルポインタ、登録アドレス値                         */
/*   出力    : エラー情報（0:正常、0以外:ラベル名エントリなし）       */
/*                                                                    */
/**********************************************************************/
int GetLabelAdr( char * buff , unsigned short * adr )
{
LBL * Label;
	/* 先頭ラベルポインタセット */
	Label = LabelTbl;
	while( Label ){
		/* 該当ラベル名検索 */
		if (!strcmp( Label->name , buff )){
			/* ラベルアドレスを返す */
			*adr = Label->adr;
			return NORM;
		}
		/* ラベルポインタ更新 */
		Label = Label->np;
	}
	return LBLNOENT;
}

/**********************************************************************/
/*   GetMacKind : Get Macro Kind                                      */
/*                                                                    */
/*   処理    : マクロ種別を決定する                                   */
/*   入力    : オペランドポインタ                                     */
/*   出力    : ニモニック種別                                         */
/*                                                                    */
/**********************************************************************/
int GetMacKind( char * buff )
{
int	i;
	/* 疑似命令テーブルサーチ */
	for ( i = 0 ; i < MACDIR ; i++ ){
		if (!strcmp( buff , MacTbl[i].name ))
			/* 疑似命令コードを返す */
			return MacTbl[i].code;
	}
	/* 該当なし（一般命令）を返す */
	return UNDEFOPR;
}

/**********************************************************************/
/*   GetMnemonicKind : Get Mnemonic Kind                              */
/*                                                                    */
/*   処理    : ニモニック種別を決定する                               */
/*   入力    : オペランドポインタ                                     */
/*   出力    : ニモニック種別                                         */
/*                                                                    */
/**********************************************************************/
unsigned short GetMnemonicKind( char * buff )
{
int	i;
	/* 疑似命令テーブルサーチ */
	for ( i = 0 ; i < MAXDIR ; i++ ){
		if (!strcmp( buff , Directivetbl[i].name ))
			/* 疑似命令コードを返す */
			return Directivetbl[i].code;
	}
	/* 該当なし（一般命令）を返す */
	return UNDEFOPR;
}
/**********************************************************************/
/*   CheckLabel : Check Label String                                  */
/*                                                                    */
/*   処理    : ラベル文字列の健全性をチェックする                     */
/*   入力    : オペランドポインタ                                     */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int CheckLabel( char * buff )
{
int	i,len;

	/* ラベル文字列長チェック */
	len = strlen( buff );
	if( !len  ) return ILLOPR;
	if( len > MAXNAME ) return OPOFLOW;
	/* 先頭文字が数字ではない */
	if( strchr( DecStr , buff[0] ) ) return ILLLBL;
	/* ラベル利用不可文字を検索する */
	for( i = 0 ; i < len ; i++ ){
		/* ラベル文字列チェック */
		if( !strchr( LabelStr , buff[i] ) ) return ILLLBL;
	}
	/* 正常終了 */
	return NORM;
}
/**********************************************************************/
/*   ChgCode : Change String code  (abc...->ABC...)                   */
/*                                                                    */
/*   処理    : アルファベット小文字を大文字に変換する                 */
/*   入力    : オペランドポインタ、出力バッファポインタ               */
/*   出力    : 変換文字列長                                           */
/*                                                                    */
/**********************************************************************/
int ChgCode( char * dst , char * src )
{
int	i,len;
	/* 出力先文字列クリア */
	dst[0] = 0;
	if (! src ) return 0;
	/* オペランド文字列長チェック */
	len = strlen( src );
	if( !len || ( len > MAXLEN ) ) return 0;
	/* 変換処理 */
	for( i = 0 ; i < len ; i++ ){
		/* 文字列チェック */
		if( (src[i] >= 'a')&&(src[i] <= 'z') ){
			/* アルファベット小文字なら大文字に変換 */
			dst[i] = (char)(src[i] - 0x20);
		}
		else{
			/* そのままコピー */
			dst[i] = src[i];
		}
	}
	/* 最終にNull挿入 */
	dst[i] = 0;
	return len;
}

/**********************************************************************/
/*   ChgKcName : Change KC Mnemonic Name  (KC->HD61)                  */
/*                                                                    */
/*   処理    : KC形式のニモニックをHD61形式に変換する                 */
/*   入力    : オペランドポインタ、出力バッファポインタ               */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int ChgKcName( char * dst , char * src )
{
int len;
char mnwk[MAXMN+1];	/* ニモニック変換用ワーク */
	/* ワークエリア初期化 */
	memset( mnwk , 0 , sizeof(mnwk) );
	/* 入力ニモニックあり */
	if (!( len = ChgCode( mnwk , src ) )) return UNDEFOPR;
	/* LDD/STD系列命令である */
	if ( !memcmp( mnwk , "LDM" , 3 )||!memcmp( mnwk , "STM" , 3 ) ){
		/* 8ビット、16ビット命令である(第3オペランドがない) */
		if(!OutTbl.opr[3]){
			mnwk[2]='D';
		}
		/* マルチワード要求である */
		else{
			/* KC形式要求あり */
			if( OutTbl.kc ){
				/* STMW､LDMW である */
				if( mnwk[3] == 'W' ){
					mnwk[2] = 'D';
					mnwk[3] = 'M';
				}
				else return UNDEFOPR;
			}
		}
	}
	else{
		/* KC形式要求あり */
		if( OutTbl.kc ){
			/* xxxxW である */
			if( mnwk[len-1] == 'W' ){
				mnwk[len-1] = 'M';
			}
			else  return UNDEFOPR;
		}
	}
	memcpy( dst , mnwk ,MAXMN );
	return NORM;
}

/**********************************************************************/
/*   GetCalcData : Get Calculate Data                                 */
/*                                                                    */
/*   処理    : 文字列として与えられた式を計算する                     */
/*   入力    : 文字列先頭ポインタ、登録アドレス値                     */
/*   出力    : エラー情報（0:正常、0以外:エラー発生）                 */
/*           : 種別(kind)  LBLOK(名称解決済み)､LBLNG(名称未解決)      */
/*           : 計算値(adr) LBLOK時のみ有効。それ以外は不正値          */
/**********************************************************************/
int GetCalcData( char * buff , unsigned short * kind ,unsigned short * adr )
{
int rc;
unsigned short val;

	/* オペランドエントリあり */
	if ( !buff ) return ILLOPR;

	/* 計算用文字列あり */
	if ( !strlen(buff) ) return ILLOPR;

	/* 計算バッファ初期化 */
	CalcPtr = 0;
	memset( calcwk , 0 , sizeof(calcwk) );
	/* 正負指定あり */
	if ( (buff[0]=='-') || (buff[0]=='+') )
		sprintf( calcwk , "0%s" , buff );
	else
		sprintf( calcwk , "%s" , buff );

	/* 名称解決済みセット */
	Ckind = LBLOK;

	/* 数式計算 */
	if ( rc = CalcVal( &val ) ) return rc;

	/* 2パス目に未定義ラベルあり */
	if ( pass && (Ckind==LBLNG) ) return LBLNOENT;

	/* 正常終了 */
	*adr = val;
	*kind = Ckind;
	return NORM;
}

/**********************************************************************/
/*   CalcVal : Calculate compare Logical                              */
/*                                                                    */
/*   処理    : 与えられた文字式を比較演算する(優先順位最低)           */
/*   入力    : 数値ポインタ                                           */
/*   出力    : エラー情報（0:正常、0以外:エラー）                     */
/*           : 計算値(value)                                          */
/*                                                                    */
/**********************************************************************/
int CalcVal(unsigned short * value )
{
int rc;
unsigned short val,wval;

	/* 先頭数式の値を取得 */
	if( rc = CalcVal0( &val ) ) return rc;
	while( 1 ){
		switch( calcwk[CalcPtr] ){
		/* = 処理 */
		case '=':
			CalcPtr ++;
			if ( calcwk[CalcPtr] == '>' ){
				CalcPtr ++;
				if ( rc = CalcVal0( &wval ) ) return rc;
				val = (unsigned short)(val >= wval);
				break;
			}
			if ( calcwk[CalcPtr] == '<' ){
				CalcPtr ++;
				if ( rc = CalcVal0( &wval ) ) return rc;
				val = (unsigned short)(val <= wval);
				break;
			}
			if ( rc = CalcVal0( &wval ) ) return rc;
			val = (unsigned short)(val == wval);
			break;
		/* > 処理 */
		case '>':
			CalcPtr ++;
			if ( calcwk[CalcPtr] == '=' ){
				CalcPtr ++;
				if ( rc = CalcVal0( &wval ) ) return rc;
				val = (unsigned short)(val >= wval);
				break;
			}
			if ( calcwk[CalcPtr] == '<' ){
				CalcPtr ++;
				if ( rc = CalcVal0( &wval ) ) return rc;
				val = (unsigned short)(val != wval);
				break;
			}
			if ( rc = CalcVal0( &wval ) ) return rc;
			val = (unsigned short)(val > wval);
			break;
		/* < 処理 */
		case '<':
			CalcPtr ++;
			if ( calcwk[CalcPtr] == '=' ){
				CalcPtr ++;
				if ( rc = CalcVal0( &wval ) ) return rc;
				val = (unsigned short)(val <= wval);
				break;
			}
			if ( calcwk[CalcPtr] == '>' ){
				CalcPtr ++;
				if ( rc = CalcVal0( &wval ) ) return rc;
				val = (unsigned short)(val != wval);
				break;
			}
			if ( rc = CalcVal0( &wval ) ) return rc;
			val = (unsigned short)(val < wval);
			break;
		case '(':
			return CALERR;
		/* 処理終了 */
		default:
			*value = val;
			return NORM;
		}
	}
}

/**********************************************************************/
/*   CalcVal0 : Calculate Logical                                     */
/*                                                                    */
/*   処理    : 与えられた文字式を論理演算する(優先順位+1)             */
/*   入力    : 数値ポインタ                                           */
/*   出力    : エラー情報（0:正常、0以外:エラー）                     */
/*           : 計算値(value)                                          */
/*                                                                    */
/**********************************************************************/
int CalcVal0(unsigned short * value )
{
int rc;
unsigned short val,wval;

	/* 先頭数式の値を取得 */
	if( rc = CalcVal1( &val ) ) return rc;
	while( 1 ){
		switch( calcwk[CalcPtr] ){
		/* AND処理 */
		case '#':
		case '&':
			CalcPtr ++;
			if ( rc = CalcVal1( &wval ) ) return rc;
			val &= wval;
			break;
		/* OR処理 */
		case '|':
			CalcPtr ++;
			if ( rc = CalcVal1( &wval ) ) return rc;
			val |= wval;
			break;
		/* XOR処理 */
		case '^':
			CalcPtr ++;
			if ( rc = CalcVal1( &wval ) ) return rc;
			val ^= wval;
			break;
		/* MOD処理 */
		case '%':
			CalcPtr ++;
			if ( rc = CalcVal1( &wval ) ) return rc;
			/* 0で除算 */
			if ( !wval ) return CALERR;
			val %= wval;
			break;
		case '(':
			return CALERR;
		/* 処理終了 */
		default:
			*value = val;
			return NORM;
		}
	}
}

/**********************************************************************/
/*   CalcVal1 : Calculate Add/Sub.                                    */
/*                                                                    */
/*   処理    : 与えられた文字式を加減算する(優先順位+2)               */
/*   入力    : 数値ポインタ                                           */
/*   出力    : エラー情報（0:正常、0以外:エラー）                     */
/*           : 計算値(value)                                          */
/*                                                                    */
/**********************************************************************/
int CalcVal1(unsigned short * value )
{
int rc;
unsigned short val,wval;

	/* 先頭数値取得 */
	if( rc = CalcVal2( &val ) ) return rc;
	while( 1 ) {
		switch( calcwk[CalcPtr] ){
		/* 加算処理 */
		case '+':
			CalcPtr ++;
			if ( rc = CalcVal2( &wval ) ) return rc;
			val += wval;
			break;
		/* 減算処理 */
		case '-':
			CalcPtr ++;
			if ( rc = CalcVal2( &wval ) ) return rc;
			val -= wval;
		/* 処理終了 */
		default:
			*value = val;
			return NORM;
		}
	}
}

/**********************************************************************/
/*   CalcVal2 : Calculate Multiple/Divide.                            */
/*                                                                    */
/*   処理    : 与えられた文字式を乗除算する(優先順位+3)               */
/*   入力    : 数値ポインタ                                           */
/*   出力    : エラー情報（0:正常、0以外:エラー）                     */
/*           : 計算値(value)                                          */
/*                                                                    */
/**********************************************************************/
int CalcVal2(unsigned short * value )
{
int rc;
unsigned short val,wval;

	/* 先頭数値取得 */
	if( rc = CalcVal3( &val ) ) return rc;
	while( 1 ) {
		switch( calcwk[CalcPtr] ){
		/* 乗算処理 */
		case '*':
			CalcPtr ++;
			if ( rc = CalcVal3( &wval ) ) return rc;
			val *= wval;
			break;
		/* 除算処理 */
		case '/':
			CalcPtr ++;
			if ( rc = CalcVal3( &wval ) ) return rc;
			/* 0で除算 */
			if ( !wval ) return CALERR;
			val /= wval;
		/* 処理終了 */
		default:
			*value = val;
			return NORM;
		}
	}
}

/**********************************************************************/
/*   CalcVal3 : Calculate ()                                          */
/*                                                                    */
/*   処理    : 括弧内の演算を行う(優先順位最高)                       */
/*   入力    : 数値ポインタ                                           */
/*   出力    : エラー情報（0:正常、0以外:エラー）                     */
/*           : 計算値(value)                                          */
/*                                                                    */
/**********************************************************************/
int CalcVal3( unsigned short *value )
{
int rc;
unsigned short val,flag;

	flag = 0;

	/* 式評価反転要求あり */
	if( calcwk[CalcPtr] == '!' ){
		CalcPtr++;
		flag = 1;
	}
	/* 括弧内処理である */
	if( calcwk[CalcPtr] == '(' ) {
		CalcPtr++;
		/* 括弧内の計算は最も優先順位の低い順に行う */
		if( rc = CalcVal( &val ) ) return rc;
		/* 括弧が閉じていない。*/
		if( calcwk[CalcPtr++] != ')' ) return ILLDQUO;
	}
	else{
		/* 数値またはラベルである */
		if( rc = GetValue( &val ) ) return rc;
	}
	/* 桁指定による値修正 */
	if ( calcwk[CalcPtr] == '.'){
		CalcPtr++;
		switch( calcwk[CalcPtr] ){
		/* 上位桁指定 */
		case 'u':
		case 'U':
		case 'h':
		case 'H':
			val = (unsigned short)(val >> 8);
			break;
		/* 下位桁指定 */
		case 'd':
		case 'D':
		case 'l':
		case 'L':
			val &= 0xff;
			break;
		/* ビット反転 */
		case 'n':
		case 'N':
			val = (unsigned short)(~val);
			break;
		default:
			return ILLOPR;
		}
		CalcPtr++;
	}
	/* 計算した数値を返す */
	*value = (unsigned short)(!flag ? val : !val);
	return NORM;
}

/**********************************************************************/
/*   GetValue : Get Data Value                                        */
/*                                                                    */
/*   処理    : ラベルまたは数値から、値を取り出す                     */
/*   入力    : 数値ポインタ                                           */
/*   出力    : エラー情報（0:正常、0以外:エラー）                     */
/*           : 取得値(value)                                          */
/*           : ラベル名称解決フラグ(Ckind) (LBLNG:名称未解決)         */
/*                                                                    */
/**********************************************************************/
int GetValue(unsigned short *value ) {
unsigned short val;
int		i,rc,quo;
char	lblwk[MAXLINE+2];   /* 計算値取得用ラベル名ワーク   */
char	QuoChar;
	/* データ初期化 */
	*value = 0;
	/* ラベル/数値取得用バッファ初期化 */
	memset( lblwk , 0 , sizeof(lblwk) );

	/* 演算子検出まで繰り返す */
	i = 0;
	quo = 0;
	QuoChar = 0;
	while ( 1 ){
		/* 文字列検出 */
		if ( !quo ){
			/* コーテーション種別（シングル/ダブル)を取得 */
			if ( ( calcwk[CalcPtr] == 0x22 )||( calcwk[CalcPtr] == 0x27 )){
				QuoChar = calcwk[CalcPtr];
				quo ++;
			}
		}
		/* コーテーション閉じた？ */
		else if ( calcwk[CalcPtr] == QuoChar ) quo ++;
		/* 演算子またはNull検出にて終了 */
		if ( !calcwk[CalcPtr] || (!quo && strchr( "+-*/#|^%().<>=" , calcwk[CalcPtr] )) ) break;
		/* 先頭以外の&検出で終了 */
		if ( !quo && ( calcwk[CalcPtr] == '&' && i ) ) break;
		/* 文字列コピー */
		lblwk[i++] = calcwk[CalcPtr++];
		/* コーテーションが閉じたら終了する */
		if ( quo == 2 ) break;
	}
	/* 取り出した文字列は数値である */
	if ( rc = GetData( lblwk , &val ) ){
		/* オペランド記述が数値以外 */
		if (rc != ILLOPR ) return rc;
		/* ラベルである */
		if ( rc = CheckLabel( lblwk ) ) return ILLOPR;
		/* ラベルアドレス取り出し */
		if ( GetLabelAdr ( lblwk , &val ) ){
			/* ラベル名称未解決とする */
			Ckind = LBLNG;
			val = 0;
		}
	}
	/* 求めた値を返す */
	*value = val;
	return NORM;
}

/**********************************************************************/
/*   GetData : Get Immediate Data                                     */
/*                                                                    */
/*   処理    : 文字列から数値データを取得する                         */
/*   入力    : 文字列ポインタ、データポインタ                         */
/*   出力    : 値(data)                                               */
/*           : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int GetData( char *buff , unsigned short * data )
{
int	i,len;
unsigned long sts;
	/* オペランド文字列長チェック */
	len = strlen( buff );
	if( !len  ) return ILLOPR;
	if( len > MAXLEN ) return OPOFLOW;

	/* 先頭および最終はコーテーション(=文字列エントリ)である */
	if ( (( buff[0] == 0x22 ) && ( buff[len-1] == 0x22 ))
		|| (( buff[0] == 0x27 ) && ( buff[len-1] == 0x27 )) ){
		/* 文字列長が３か４である */
		if( len == 3 ){
			/* 種別は暫定で16ビット数値とする */
			*data = (unsigned short)(buff[1]&0xff);
			return NORM;
		}
		else{
			if( len == 4 ){
				/* 種別は暫定で16ビット数値とする */
				*data = (unsigned short)( (buff[1]&0xff)|((buff[2]&0xff)<<8) );
				return NORM;
			}
			else return ILLOPR;
		}
	}
	/* ２進数指定である */
	if ( (buff[0] == '&')&&((buff[1] == 'B')||(buff[1] == 'b')) ){
		for( i = 2 , sts = 0; i < len ; i++ ){
			/* 2進数桁上げ */
			sts *= 2;
			/* 文字列チェック */
			switch ( buff[i] ){
			case '1':
				sts |= 0x1;
			case '0':
				break;
			default:
				return ILLOPR;
			}
		}
		/* 範囲オーバーである */
		if ( sts >= 65536 ) return OFLOW;
		/* 正常終了 */
		*data = (unsigned short )sts;
		return NORM;
	}
	/* １６進数指定である */
	if ( (buff[0] == '&')&&((buff[1] == 'H')||(buff[1] == 'h')) ){
		for( i = 2 ; i < len ; i++ ){
			/* 文字列チェック */
			if( !strchr( HexStr , (int)buff[i] ) ){
			 return ILLOPR;
			 }
		}
		/* １６進数に変換 */
#if FORDOS
		if ( sscanf( &buff[2] , "%Lx" , &sts ) == EOF ) return ILLOPR;
#else
		if ( sscanf( &buff[2] , "%x" , &sts ) == EOF ) return ILLOPR;
#endif
		/* 範囲オーバーである */
		if ( sts >= 65536 ) return OFLOW;
		/* 正常終了 */
		*data = (unsigned short)sts;
		return NORM;
	}
	/* １０進数処理 */
	for( i = 0 ; i < len ; i++ ){
		/* 文字列チェック */
		if( !strchr( DecStr , (int)buff[i] ) ) return ILLOPR;
	}
	/* １０進数に変換 */
#if FORDOS
	if ( sscanf( buff , "%Ld" , &sts ) == EOF ) return ILLOPR;
#else
	if ( sscanf( buff , "%d" , &sts ) == EOF ) return ILLOPR;
#endif
	/* 範囲オーバーである */
	if ( sts >= 65536 ) return OFLOW;

	/* 正常終了 */
	*data = (unsigned short )sts;
	return NORM;
}

/**********************************************************************/
/*   CheckSetOpt : Check /SET Option Name                             */
/*                                                                    */
/*   処理    : /SETオプション時の登録チェック処理を行う               */
/*   入力    : なし                                                   */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int CheckSetOpt( char * name )
{
int	i;
	/* ラベル登録をチェックする */
	for ( i = 0 ; i < SetLabel ; i++ ){
		/* 登録ラベルと一致 */
		if( !strcmp( SetTbl[i].ent , name ) ) return 0;
	}
	return 2;
}

/**********************************************************************/
/*   CheckSetLbl : Check /SET Option Name                             */
/*                                                                    */
/*   処理    : /SETオプション時の登録チェック処理を行う               */
/*   入力    : なし                                                   */
/*   出力    : エラー情報（0:正常、0以外:異常）                       */
/*                                                                    */
/**********************************************************************/
int CheckSetLbl( char * name ,unsigned short sts )
{
int	i,ent,rc;
	ent = 0;
	/* ラベル登録をチェックする */
	for ( i = 0 ; i < SetLabel ; i++ ){
		/* 登録ラベルと一致 */
		if( !strcmp( SetTbl[i].ent , name ) ){
			ent++;
		}
		/* 代入ラベルと一致 */
		if( !strcmp( SetTbl[i].let , name ) ){
			/* ラベルテーブルに登録する */
			if( rc = SetLabelTbl( SetTbl[i].ent , sts ) ) return rc;
		}
	}
	/* 登録ラベルと一致した場合、ラベル登録無しを返す */
	if ( ent ) return 1;

	/* 該当なし */
	return NORM;
}

/**********************************************************************/
/*   PrintList : Print List File                                      */
/*                                                                    */
/*   処理    : OutTblに従い、１行分のリストを出力する                 */
/*   入力    : 行番号カウンタ                                         */
/*   出力    : なし                                                   */
/*                                                                    */
/**********************************************************************/
void PrintList( int count )
{
int	i,cnt,n,len;
unsigned short sts;
	/* リスト出力要求がない場合、処理終了 */
	if ( ListFlag ) return;
	len = 0;
	/* 行番号出力 */
	if (pr) printf( "%05d:%04X  " , count+1 , OutTbl.adr );
	fprintf( LstFD ,"%05d:%04X  " , count+1 , OutTbl.adr );

	/* 通常命令／疑似命令種別取り出し */
	ChgCode( oprwk , OutTbl.opr[0] );
	sts = GetMnemonicKind( oprwk );
	/* ORG命令以外は命令語コード出力 */
	if (OutTbl.byte && ( sts != OP_ORG ) ){
		/* データあり */
		for ( cnt = 0 ; cnt < 4 ; cnt++ ){
			if ( cnt < OutTbl.byte){
				/* DS命令時は、0を出力する */
				if ( sts == OP_DS ){
					if (pr) printf( "00" );
					fprintf( LstFD ,"00" );
				}
				 else{
					if (pr) printf( "%02X" , OutTbl.code[cnt] );
					fprintf( LstFD ,"%02X" , OutTbl.code[cnt] );
				}
			}
			else{
				if (pr) printf( "  " );
				if (!Tab) fprintf( LstFD ,"  " );
			}
		}
		if (pr) printf( "  " );
		if (!Tab) fprintf( LstFD ,"  " );
		else fprintf( LstFD ,"%s", ( ( OutTbl.byte & 0x3 ) == 1) ? "\t\t" : "\t" );
	}
	else{
		/* データなし */
		cnt = OutTbl.byte;
		if (pr) printf( "          " );
		if ( !Tab ) fprintf( LstFD ,"          " );
		else fprintf( LstFD ,"\t\t" );
	}
	/* ラベルコード出力 */
	if ( OutTbl.label ){
		sprintf( oprwk , "%s:" , OutTbl.label );
		if (pr) printf("%-13s" , oprwk );
		if (!Tab) fprintf( LstFD ,"%-13s" , oprwk );
		else{
			fprintf( LstFD ,"%s" , oprwk );
			if ( strlen(oprwk) < 8 )
				fprintf( LstFD ,"\t" );
		}
	}
	else{
		if ( OutTbl.opr[0] ){
			/* 空白出力 */
			if (pr) printf( "             " );
			if ( !Tab )	fprintf( LstFD ,"             " );
			else fprintf( LstFD ,"\t" );
		}
	}
	/* ニモニック出力 */
	if ( OutTbl.opr[0] ){
		if (pr) printf( "%-08s" , OutTbl.opr[0] );
		if (!Tab) fprintf( LstFD ,"%-08s" , OutTbl.opr[0] );
		else{
			fprintf( LstFD ,"%s" , OutTbl.opr[0] );
			if ( strlen(OutTbl.opr[0]) < 8 )
				fprintf( LstFD ,"\t" );
		}
		len += 8;
	}
	/* オペランド出力 */
	i = 1;
	while( OutTbl.opr[i] ){
		if (pr) printf( "%s" , OutTbl.opr[i] );
		fprintf( LstFD ,"%s" , OutTbl.opr[i] );
		len += strlen(OutTbl.opr[i]);
		i++;
	}
	/* コメント出力 */
	if ( OutTbl.comment ){
		if (pr) printf( "%s" , OutTbl.comment );
		/* 空白出力 */
		if ( len ){
			if (!Tab){
				n = ( len > 30 ) ? 0 : ( 30 - len );
				for ( i = 0 ; i < n ; i++ ) fprintf( LstFD ," " );
			}
			else{
				n = ( len > 31 ) ? 0 : ( 4 - (len/8) );
				for ( i = 0 ; i < n ; i++ ) fprintf( LstFD ,"\t" );
			}
		}
		fprintf( LstFD ,"%s" , OutTbl.comment );
	}
	/* 改行 */
	if (pr) printf( "\n" );
	fprintf( LstFD ,"\n" );

	/* 命令語コード出力 */
	while( OutTbl.byte && ( cnt < OutTbl.byte ) ){
		if (pr) printf("            ");
		fprintf(LstFD , "            ");
		/* データあり */
		for ( i = 0 ; i < 4 ; i++ , cnt++ ){
			if ( cnt < OutTbl.byte){
				/* DS命令時は、0を出力する */
				if ( sts == OP_DS ){
					if (pr) printf( "00" );
					fprintf( LstFD ,"00" );
				}
				 else{
					if (pr) printf( "%02X" , OutTbl.code[cnt] );
					fprintf( LstFD ,"%02X" , OutTbl.code[cnt] );
				}
			}
			else{
				if (pr) printf( "  " );
				if (!Tab) fprintf( LstFD ,"  " );
			}
		}
		/* TAB出力 */
		if ( Tab ) {
			fprintf( LstFD ,"\t");
			if ( ( OutTbl.byte & 0x3 ) == 1 ) fprintf( LstFD ,"\t");
		}
		/* 改行 */
		if (pr) printf( "\n" );
		fprintf( LstFD ,"\n" );
	}
	/* EJECT要求あり */
	if ( LineFeed ){
		/* Line Feed(0xc)出力 */
		fprintf( LstFD ,"%c", 0xc );
		/* ヘッダ出力 */
		fprintf( LstFD , "%s%s - ",name,rev );
		fprintf( LstFD ,"ASSEMBLE LIST OF [%s]\n", SrcFile );
		LineFeed = 0;
	}
}

/**********************************************************************/
/*   ErrPut : Error Print                                             */
/*                                                                    */
/*   処理    : エラーメッセージを出力する                             */
/*   入力    : 行番号カウンタ、エラー番号                             */
/*   出力    : なし                                                   */
/*                                                                    */
/**********************************************************************/
void ErrPut( int cnt , int err )
{
int	i;
	/* エラー発生行の出力 */
	pr = 1;
	ListFlag = 0;
	PrintList( cnt );

	/* 入力コードに該当するエラーメッセージを出力 */
	for ( i = 0 ; i < MAXERR-1 ; i++ ){
		if ( errtbl[i].code==err )	break;
	}
	printf("LINE:%d ERROR CODE:%03d %s\n" , cnt+1, err , errtbl[i].msg );
	fprintf( LstFD ,"LINE:%d ERROR CODE:%03d %s\n" , cnt+1, err , errtbl[i].msg );
}
