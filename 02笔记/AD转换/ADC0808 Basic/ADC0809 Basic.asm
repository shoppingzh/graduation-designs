LED_0	EQU 	30H		 		;�����������ܵĶ���
LED_1 	EQU 	31H
LED_2 	EQU 	32H

ADC		EQU		35H				;���ת���������
ST 		BIT 	P3.2
OE 		BIT 	P3.0
EOC 	BIT 	P3.1
		ORG 	00H

START: 	MOV		LED_0,#00H
		MOV		LED_1,#00H
		MOV		LED_2,#00H
		MOV		DPTR,#TABLE		;�Ͷ�����׵�ַ

		SETB	P3.4
		SETB	P3.5
		CLR		P3.6		 	;ѡ��ADC0808��ͨ��3

WAIT: 	CLR 	ST
		SETB 	ST
		CLR 	ST				;����ת��
 		JNB 	EOC,$		 	;�ȴ�ת������
		SETB 	OE 				;�������
		MOV 	ADC,P1			;�ݴ�ת�����
		CLR 	OE			  	;�ر����
		MOV 	A,ADC			;��ADת�����ת����BCD��
		MOV 	B,#100
		DIV 	AB
		MOV 	LED_2,A
		MOV 	A,B
		MOV 	B,#10
		DIV 	AB
		MOV 	LED_1,A
		MOV 	LED_0,B
		LCALL	DISP		  	;��ʾADת�����
		SJMP 	WAIT

DISP:	MOV		A,LED_0			;������ʾ�ӳ���
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

DELAY:	MOV		R6,#10			;��ʱ5����
D1:		MOV		R7,#250
		DJNZ	R7,$
		DJNZ	R6,D1
		RET

TABLE: 	DB 		3FH,06H,5BH,4FH,66H
		DB 		6DH,7DH,07H,7FH,6FH
		END