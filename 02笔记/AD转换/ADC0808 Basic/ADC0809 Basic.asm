LED_0	EQU 	30H		 		;存放三个数码管的段码
LED_1 	EQU 	31H
LED_2 	EQU 	32H

ADC		EQU		35H				;存放转换后的数据
ST 		BIT 	P3.2
OE 		BIT 	P3.0
EOC 	BIT 	P3.1
		ORG 	00H

START: 	MOV		LED_0,#00H
		MOV		LED_1,#00H
		MOV		LED_2,#00H
		MOV		DPTR,#TABLE		;送段码表首地址

		SETB	P3.4
		SETB	P3.5
		CLR		P3.6		 	;选择ADC0808的通道3

WAIT: 	CLR 	ST
		SETB 	ST
		CLR 	ST				;启动转换
 		JNB 	EOC,$		 	;等待转换结束
		SETB 	OE 				;允许输出
		MOV 	ADC,P1			;暂存转换结果
		CLR 	OE			  	;关闭输出
		MOV 	A,ADC			;将AD转换结果转换成BCD码
		MOV 	B,#100
		DIV 	AB
		MOV 	LED_2,A
		MOV 	A,B
		MOV 	B,#10
		DIV 	AB
		MOV 	LED_1,A
		MOV 	LED_0,B
		LCALL	DISP		  	;显示AD转换结果
		SJMP 	WAIT

DISP:	MOV		A,LED_0			;数码显示子程序
		MOVC	A,@A+DPTR
		CLR		P2.3
		MOV		P0,A
		LCALL	DELAY
		SETB	P2.3

		MOV		A,LED_1
		MOVC	A,@A+DPTR
		CLR		P2.2
		MOV		P0,A
		LCALL	DELAY
		SETB	P2.2

		MOV		A,LED_2
		MOVC	A,@A+DPTR
		CLR		P2.1
		MOV		P0,A
		LCALL	DELAY
		SETB	P2.1
		RET

DELAY:	MOV		R6,#10			;延时5毫秒
D1:		MOV		R7,#250
		DJNZ	R7,$
		DJNZ	R6,D1
		RET

TABLE: 	DB 		3FH,06H,5BH,4FH,66H
		DB 		6DH,7DH,07H,7FH,6FH
		END