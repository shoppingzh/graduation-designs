       ORG 0000H
       AJMP MAIN


       ORG 0030H

  MAIN:
            MOV 20H,#00H
            MOV 21H,#00H
            MOV 22H,#00H
            MOV 23H,#00H
            MOV 24H,#00H
            MOV 25H,#00H

        LCALL DAC_0809
        LCALL PRO_1
        LCALL Displayer_1
        SJMP MAIN
        RET


DAC_0809:MOV R2,#02H
         MOV R1,#40H
         MOV DPTR,#0BF00H
         MOV A,#00H
     T1: MOVX @DPTR,A
          NOP
          NOP

     T2: MOV A,P1
         ANL A,#80H
         CJNE A,#80H,T3
         SJMP T2

     T3:SETB P1.7
        NOP
        NOP

        MOVX A,@DPTR
        NOP
        NOP
        MOV @R1,A
        INC R1
        INC DPTR
        DJNZ R2,T1
        RET





Displayer_1:MOV R0,#20H
            MOV R2,#06H
            MOV R3,#02H

         T4:MOV A,@R0
            MOV DPTR,#SEGTAB
            MOVC A,@A+DPTR
            MOV @R0,A
            INC R0
            DJNZ R2,T4

            MOV R0,#20H
         T5:MOV DPTR,#0FE00H
            MOV A,@R0
            ORL A,#80H
            MOVX @DPTR,A

            INC R0
            MOV DPTR,#0FD00H
            MOV A,@R0
            MOVX @DPTR ,A

            INC R0
            MOV DPTR,#0FB00H
            MOV A,@R0
            MOVX @DPTR,A
         ;   INC R0
         ;   LCALL DL_3S
         ;   DJNZ R3,T5
             RET
   SEGTAB: DB 3FH,06H,5BH,4FH
           DB 66H,6DH,7DH,07H
           DB 7FH,6FH,77H,7CH
           DB 39H,5EH,79H,71H



PRO_1:  MOV R0,#50H
        MOV R1,#40H
        MOV R3,#02H

     T6:MOV A,@R1
        MOV B,#100
        MUL AB
        MOV A,B
        MOV B,#05
        MUL AB
        MOV R5,A
        MOV A,B
        MOV @R0,A
        MOV A,R5
        INC R0
        MOV @R0,A
        INC R0
        INC R1
        DJNZ R3,T6


        MOV R0,#20H
        MOV R1,#50H
        MOV R4,#02H
   NEXT:MOV A,@R1
        CJNE A,#00H,D1
        INC R1
        MOV A,@R1
         CJNE A,#10,JP1
        JNC D3
    JP1:JC D2
        CJNE A,#100,JP2
        JNC D4
    JP2:JC D3
     D4:LCALL Diving_100
        MOV @R0,A
        INC R0
        MOV A,B
        LCALL Diving_10
        MOV @R0,A
        INC R0
        MOV A,B
        MOV @R0,A
        INC R0
        INC R1
        DJNZ R4,NEXT
        RET
     D1:MOV A,#0FFH
        LCALL Diving_100
        MOV 55H,A
        MOV 56H,B
        MOV A,#01H
        ADD A,56H
        MOV 56H,A
        INC R1
        MOV A,@R1
        LCALL Diving_100
        ADD A,55H

        MOV 55H,A
        MOV A,B
        ADD A,56H
        MOV 56H,A
        CJNE A,#100,JP3
    JP3:JC JP4
        MOV A,55H
        ADD A,#01H
        MOV 55H,A
        MOV A,56H
        SUBB A,#100
        MOV 56H,A
    JP4:MOV A,55H
        MOV @R0,A
        INC R0
        MOV A,56H
        LCALL Diving_10
        MOV @R0,A
        INC R0
        MOV A,B
        MOV @R0,A
        INC R0
        INC R1
     ;   DJNZ R4,NEXT
        RET
     D2:MOV @R0,#00H
        INC R0
        MOV @R0,#00H
        INC R0
        MOV @R0,A
        INC R0
        INC R1
    ;    DJNZ R4,NEXT
        RET
     D3:MOV @R0,#00H
        INC R0
        LCALL Diving_10
        MOV @R0,A
        INC R0
        MOV A,B
        MOV @R0,A
        INC R0
        INC R1
    ;    DJNZ R4,NEXT1
        RET
  NEXT1:LJMP NEXT
Diving_100:MOV B,#100
           DIV AB
           RET
 Diving_10:MOV B,#10
           DIV AB
           RET
 DL_3S:MOV R5,#250
   DL1:MOV R7,#2
   DL2:MOV R6,#250
   DL3:NOP
       NOP
       NOP
       NOP
       NOP
       NOP
       NOP
       NOP
       DJNZ R6,DL3
       DJNZ R7,DL2
       DJNZ R5,DL1
       RET



