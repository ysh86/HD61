-------------------------------------------------------------------------
 HD61     :  HD61700 CROSS ASSEMBLER for Win32 (Rev 0.33)
 System   :  Win95/98/98SE/NT4/2000/XP
 Produce  :  Copyright (c) BLUE (QZE12045@NIFTY) 2003 - 2004
          :  Published by JUN AMANO (VYU04421@nifty.ne.jp) 2003
 Homepage :  http://www.lsigame.com/  (Casio PB-1000 Forever!)
          :  http://hd61700.yukimizake.net/ (source code)
-------------------------------------------------------------------------
HD61 is a Win9x/NT4/2000/XP based HD61700 cross assembler for the CASIO PB-1000/
AI-1000/FX-870P/VX-3/VX-4 systems.

HD61 is free for your own personal use and can be distributed freely as long
as it is not modified. This text file must be included in any distribution.

item
------
1. HD61 has the top compatible function of the inclusion assembler of PB-1000.
2. Symbol label can used to 16 letters and it is able to define as long as memory permits.
3. Supporting an unpublished command numerously from CASIO.
   (ex)OPR 24h,25h,2Ch,2Dh,50h,53h,54h,C0h - CFh,E0h - EFh etc.
4. Output file form is DATA sentence of BASIC or PBF form (note 1).
5. Suportted directives are ORG/START/EQU/DB/DW/DS/LEVEL/#IF/#ELSE/#ENDIF/
   #LIST/#NOLIST/#INCLUDE.. etc.

(note 1)
PBF form is used [The mutual change program of the binary file, the text file].
It is disclosed [Casio PB-1000 Forever!( http://www.lsigame.com/ )]

The contents of the compression file
Readme(e).txt ----------- Document(English) :This File
Readme.txt    ----------- Document(Japanese)
HD61.EXE      ----------- HD61700 cross assembler execute file.
HD61700.s     ----------- All operation sample for HD61.(Japanese Commented)
LCD.s         ----------- LCD control sample (for PB-1000/C/AI-1000/FX-870P/VX-4)
Trans.b       ----------- ASCII --> BINARY converter for BAS form.(for PB-1000/C/AI-1000)
TransVx.b     ----------- ASCII --> BINARY converter for PBF form.(for FX-870P/VX-4/VX-3)

Using the HD61
-----------------
HD61 [name of the source file] [options(/p , /n ,/set)]

for example:
>hd61 hd61700.s [Enter]
HD61700 ASSEMBLER Rev 0.33
Input : hd61700.s 
 PASS 1 END 
 PASS 2 END
ASSEMBLY COMPLETE, NO ERRORS FOUND
>

Assembling is normal displaying [ASSEMBLY COMPLETE, NO ERRORS FOUND] it ends.
And output *.bas and *.lst file.
In the case that some errors occurred during assembling, displays the error line.

Options:
/p  -------- Output PBF format file.(default is output BASIC format.)
/n  -------- No optimize.
(/set) [symbol]=[value/symbol] --- Set symbol label.

when use /n option. Output compatible code for the PB-1000 inclusion assembler.
for example:
 Mnemonic       Output code
 LD $2,$0   -->   02 42    ; default( no /n options). output 2 byte code.
 LD $2,$0   -->   02 62 00 ; added /n option. output 3 byte code.
 LD $2,$30  -->   02 22    ; default( no /n options). output 2 byte code.
 LD $2,$30  -->   02 62 1E ; added /n option. output 3 byte code.
etc.
the information regarding /n option, please refer to HD61700.S(and hd61700.lst)

/set [symbol]=[value/symbol] or [symbol]=[value/symbol]
This option can be defined symbol label in command line.
 for example:
 >HD61 SAMPLE.S /SET BASE=0x7000 /SET MODEL=PB1000
or
 >HD61 SAMPLE.S BASE=0x7000 MODEL=PB1000

Error Messages
------------------
Invalid Source File Name
Line Length is Too Long
Oprand Length is Too Long
LABEL Length is Too Long
ORG Not Entry
Operand Not Entry
EQU without Label
Illigal Oprand
START Already Defined
Illigal [,]
Illigal ['']or[(]or[)]
LABEL Already Defined
LABEL Type Mismatch
Undefined LABEL
Operation Type Mismatch
Operand Range Over
Jump Address Over
Output Buffer Over Flow
Assemble Address Over Flow
Execute Address Illigal
Could not calculate
Illigal [#if] - [#endif]
Invalid Include File Name
Could Not Nest Include
Illigal Register Number

References:( for HD61 development )
-----------------------------------
1. [CASIO PB-1000 command reference] CASIO Co.,LTD.
2. [CASIO PB-1000 Technical Handbook] Modern Co.,LTD.
3. [Pockecom Journal]1989/12 [Undefinition command of HD61700 I] by MAIMU
4. [Pockecom Journal]1990/1  [Undefinition command of HD61700 II] by MAIMU
5. [Pockecom Journal]1990/8  ｢KC-Disasembler｣ by KOTACHAN
6. [Pockecom Journal]1990/8  ｢AI-MON｣ by KOTACHAN
7. [Pockecom Journal]1990/8  ｢VX-3 Graphic Subroutine Package｣ by KOTACHAN
8. [The mutual change program of the binary file, the text file.] by JUN AMANO
   (｢CASIO PB-1000 Forever!｣ URL: http://www.lsigame.com/)
9. [Pockecom Journal]1992/12 [AI-Assembler] by P,H,M
10.[Pockecom Journal]1993/4  [FX-870P Assembler] by 陶治彩絵
11.[Pockecom Journal]1995/2  [X-Assembler Ver.6」by N.Hayashi

History
-----------------
Rev 0.01  2003.01.06  First version.
Rev 0.16  2003.03.14  Support undefinition command.(BUPS/BDNS/PPO/STL)
Rev 0.17  2003.03.18  Support undefinition command.(BYU/BYD)
                      Fixed STL/STLW/STLM.
Rev 0.18  2003.04.01  Fixed a minor bug in DW/DB.
Rev 0.19  2003.04.06  Support JR +-IM7 form.
Rev 0.20  2003.04.22  Fixed a problem in loading of a source file.
                      Rewrite the error process.
Rev 0.21  2003.04.26  Support TS register.(PST/GST)
Rev 0.22  2003.04.26  Disable jump expansion.(op:0xD2,0xD4,0xDA,0xDB,0xDC,0xDD)
Rev 0.23  2003.05.16  "/SET" option Added.
Rev 0.24  2003.05.25  Fixed a problrem in assembling a 'null file'.
Rev 0.25  2003.05.30  Fixed a string immediate.
Rev 0.26  2003.06.27  Support 'single quotation' string.
                      for example)
                      LD  $0,'"'   ; Load $0 <- &H22(Double quotation chracter)
                      LD  $0,"'"   ; Load $0 <- &H27(Single quotation chracter)
Rev 0.27  2003.06.29  Fixed '#include'.
Rev 0.28  2003.07.25  Fixed 'JR addres check'.
                      /SET option modified.
                      /TAB option added. List file used 'TAB=8'.(Test implement)
Rev 0.29  2003.09.01  Fixed output PBF form.
Rev 0.30  2003.09.10  Changed output name '*.BIN'->'*.EXE' in bas/pbf file,
                      when 'START 0' setting.
Rev 0.31  2003.09.10  Fixed '()' in quotation string.
Rev 0.32  2004.01.16  Fixed a minor bug.
Rev 0.33  2004.12.24  'EQU' modified.
                      /Q option added. Output quick loader form.(Test implement)
