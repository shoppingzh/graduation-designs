
      AD_WR EQU P3.5;转换开始
      EOC EQU P3.6 ;芯片选择
      AD_RD EQU P3.7 ;RD=LOW,数字信号输出
      AD_INPUT_PORT EQU P1 ;定义数据位
      ;CounteR EQU 59H ;计数器,显示程序通过它得知现正显示哪个数码管
      DISPBUF EQU 52H ;显示缓冲区为5AH和5BH

      ORG 0000H
      AJMP MAIN
      ORG 0030H
MAIN:
      MOV SP,#70H ;设置堆栈
      MOV 63H,#0C0H
      ;MOV DPTR,#8000H
      ;MOVX @DPTR,A
      MOV P3,#0FFH
LOOP:
      LCALL ADC_DEMO ;调用AD子程序
     ;LCALL DISPLAY  ;调用显示子程序
      AJMP LOOP


;//==========================================
;// AD转换读取延时程序，显示读到的数值
;//==========================================
    ADC_DEMO:
     MOV AD_INPUT_PORT,#0FFH
     CLR AD_RD
     NOP
     NOP
     NOP
     SETB AD_RD
     NOP
     NOP
     NOP
     CLR AD_RD
     NOP
     NOP
WAIT:JNB EOC,WAIT
     SETB AD_WR
     NOP
     NOP
     NOP
     NOP
     
     MOV A,AD_INPUT_PORT
     MOV 32H,A
     CLR AD_WR
     NOP
     NOP
     NOP
     MOV A,32H
     MOV B,#100 ;AD转换出的值除100商为百位数
     DIV AB ; 取百位数 余数在B寄存器
     MOV DISPBUF,A ;把百位存入百位寄存器DISPBUF
     MOV A,B ;余数再送A
     MOV B,#10 ;余数除10商为十位数
    DIV AB ; 除法，余数在寄存器B
    MOV DISPBUF-1,A ;A是十位数存第二位显示寄存器
    MOV DISPBUF-2,B ; B是个位数存第三位显示寄存器
    LCALL DISPLAY
    RET
;//=================================================
;显示子程序
;===================================================
    DISPLAY:
           ACALL BIN_BCD
           ;ACALL T2_10
            PUSH ACC              ;保存ACC
            PUSH PSW
            ;MOV 63H,#0
            MOV R0,#60H
            MOV R3,#00010001B
       LOP: MOV A,R3
            MOV P2,A
            MOV A,@R0
            MOV P0,A
            ACALL DS1MS
            INC R0
            NOP
            NOP
            MOV A,R3
            RL A
            MOV R3,A
            CJNE R3,#00010001B,LOP
            POP PSW
            POP ACC
            RET
;====================================================
;BCD译码
;=====================================================
   BIN_BCD:MOV DPTR,#DISPTAB
           MOV R0,#62H
           MOV R4,#03H
           MOV R1,#52H
      BIN: MOV A,@R1
           MOVC A,@A+DPTR ;
           MOV @R0,A
           DEC R0
           DEC R1
           DJNZ R4,BIN
           RET
DISPTAB:DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H ;字形代码表
           ;0     1    2    3   4   5   6    7   8   9
DELAY1MS:                      ;延时子程序
           MOV R7,#2
        MM:MOV R6,#100
        PP:DJNZ R6,$ ;2us
           DJNZ R7,MM
           RET
 ;//************************************************** //
          ; 延时子程序
;//**************************************************//
     DS1MS: MOV R1,#2
     DSLLO: MOV R2,#100
        PO: DJNZ R2,$
            DJNZ R1,DSLLO
            RET                  ;延时返回
           END



