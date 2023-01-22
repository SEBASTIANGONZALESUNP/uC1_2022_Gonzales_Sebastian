; @file: Retardo.inc
; @brief:
    ; En esta librería se encuentran distintos códigos de intervalos de tiempo
    ;(retardos) aproximados para poder usados en los "Source Files" según se
    ; necesite alguno de estos en próximos programas.
; @date: 7/01/23
; @author: Gonzales Alvarado Sebastian
    
// Frecuencia oscilador = 4MHz
// Tiempo deinstrucción = 1us
    
PSECT udata_acs
contador1: DS 1				;reserva 1 byte en access ram
contador2: DS 1				;reserva 1 byte en access ram
contador3: DS 1
    
PSECT code    

;T=((4*K)+6)*Tcy  
Delay_10us:				;  CALL --> 2Tcy
	MOVLW  1			;  1Tcy, (k)
	MOVWF  contador1,0		;  1Tcy
    Loop1:
	NOP				;  (K)* Tcy
	DECFSZ  contador1,1,0		;  (K-1)Tcy + 3*Tcy
	GOTO    Loop1			;  (K-1)Tcy * 2Tcy
	RETURN				;  RETURN 2Tcy 

;Delay_25us
;T=((3*K)+7)*Tcy
Delay_25us:				;  CALL --> 2Tcy
	MOVLW  6			;  1Tcy, (K)
	MOVWF  contador1,0		;  1Tcy
	NOP				;  1Tcy
    Loop2:
	DECFSZ contador1,1,0		;  (K-1)Tcy + 3*Tcy
	GOTO   Loop2			;  (K-1)Tcy * 2Tcy
	RETURN				;  2Tcy
	
;Delay_50us
;T=((4*K)+6)*Tcy
Delay_50us:				;  CALL --> 2Tcy
	MOVLW  11			;  1Tcy, W -> (K)
	MOVWF  contador1,0		;  1Tcy

	Loop3:
	    NOP				;  (K) * Tcy
	    DECFSZ contador1,1,0	;  (K-1)Tcy + 3*Tcy
	    GOTO   Loop3		;  (K-1)Tcy * 2Tcy
	    RETURN			;  RETURN 2Tcy

;Delay_100us
;T=((3*K)+7)*Tcy
Delay_100us:				;  CALL --> 2Tcy
	MOVLW  31			;  1Tcy, (K)
	MOVWF  contador1,0		;  1Tcy
	NOP				;  1Tcy
	Loop4:
	    DECFSZ contador1,1,0	;  (K-1)Tcy + 3*Tcy
	    GOTO   Loop4		;  (K-1)Tcy * 2Tcy
	    RETURN			;  RETURN 2Tcy
	
;Delay_200us
;T=((3*K)+8)*Tcy
Delay_200us:				;  CALL --> 2Tcy
	MOVLW  64			;  1Tcy, (K)
	MOVWF  contador1,0		;  1Tcy
	NOP				;  1Tcy
	NOP				;  1Tcy
	Loop5:
	    DECFSZ contador1,1,0	;  (K-1)Tcy + 3*Tcy
	    GOTO   Loop5		;  (K-1)Tcy * 2Tcy
	    RETURN			;  RETURN 2Tcy
	
;Delay_250us
;T=((4*K)+6)*Tcy
Delay_250us:				;  CALL --> 2Tcy
	MOVLW  61			;  1Tcy, (K)
	MOVWF  contador1,0		;  1Tcy
	Loop6:
	    NOP				;  (K) * Tcy
	    DECFSZ contador1,1,0	;  (K-1)Tcy + 3*Tcy
	    GOTO   Loop6		;  (K-1)Tcy * 2Tcy
	    RETURN			;  RETURN 2Tcy
	
;Delay_500us
;T=((3*K)+8)*Tcy
Delay_500us:				;  CALL aporta 2Tcy
	MOVLW  164			;  1Tcy, (K)
	MOVWF  contador1,0		;  1Tcy
	NOP				;  1Tcy
	NOP				
    Loop7:
	DECFSZ contador1,1,0		;  (K-1)Tcy + 3*Tcy
	GOTO   Loop7			;  (K-1)Tcy * 2Tcy
	RETURN				;  RETURN 2Tcy
    
;Delay_1ms
;T=(k2*((5*K1)+6))+9*Tcy
    
Delay_1ms:				;  CALL --> 2Tcy
	MOVLW	1			;  1Tcy, (K2)
	MOVWF   contador2,0		;  1Tcy
	NOP				;  1Tcy
	NOP				;  1Tcy
	Loop_Ext1:
	    MOVLW   197			;  1Tcy, (K1).
	    MOVWF   contador1,0		;  1Tcy
	    NOP				;  1Tcy
	Loop_Int1:
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    DECFSZ  contador1,1,0	;  (K1-1)*K2*1Tcy + K2*3Tcy 
	    GOTO    Loop_Int1		;  (K1-1)*K2*2Tcy
	    NOP
	    DECFSZ  contador2,1,0	;  (K2-1)*1Tcy + 3Tcy 
	    GOTO    Loop_Ext2		;  (K2-1)*2Tcy
	    RETURN			;  RETURN 2Tcy
	
;Delay_5ms
;T = K2*((K1*6)+8)+10
Delay_5ms:				;  CALL --> 2Tcy
    MOVLW	5			;  1Tcy, (K2) 
    MOVWF   contador2,0			;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
	Loop_Ext2:				  
	    MOVLW   198			;  1Tcy, (K1).
	    MOVWF   contador1,0		;  1Tcy
	Loop_Int2:
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    DECFSZ  contador1,1,0	;  (K1-1)*K2*1Tcy + K2*3Tcy 
	    GOTO    Loop_Int2		;  (K1-1)*K2*2Tcy
	    NOP				;  K2*TcY
	    NOP				;  K2*TcY
	    NOP				;  K2*TcY
	    DECFSZ  contador2,1,0	;  (K2-1)*1Tcy + 3Tcy 
	    GOTO    Loop_Ext2		;  (K2-1)*2Tcy
	    RETURN			;  RETURN 2Tcy
;Delay_10ms
;T = k2*((k1*6)+9)
Delay_10ms:				;  CALL --> 2Tcy
    MOVLW	10			;  1Tcy, (K2) 
    MOVWF   contador2,0			;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
	Loop_Ext3:				  
	    MOVLW   165			;  1Tcy, (K1).
	    MOVWF   contador1,0		;  1Tcy
	Loop_Int3:
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    DECFSZ  contador1,1,0	;  (K1-1)*K2*1Tcy + K2*3Tcy 
	    GOTO    Loop_Int3		;  (K1-1)*K2*2Tcy
	    NOP
	    NOP
	    NOP
	    NOP
	    DECFSZ  contador2,1,0	;  (K2-1)*1Tcy + 3Tcy 
	    GOTO    Loop_Ext3		;  (K2-1)*2Tcy
	    RETURN			;  RETURN 2Tcy
;Delay_25ms:
;T = (k2*((k1*6)+5))+10	    
Delay_25ms:				;  CALL --> 2Tcy
    MOVLW	30			;  1Tcy, (K2) 
    MOVWF   contador2,0			;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
	Loop_Ext4:				  
	    MOVLW   138			;  1Tcy, (K1).
	    MOVWF   contador1,0		;  1Tcy
	Loop_Int4:
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    DECFSZ  contador1,1,0	;  (K1-1)*K2*1Tcy + K2*3Tcy
	    GOTO    Loop_Int4		;  (K1-1)*K2*2Tcy
	    DECFSZ  contador2,1,0	;  (K2-1)*1Tcy + 3Tcy 
	    GOTO    Loop_Ext4		;  (K2-1)*2Tcy
	    RETURN

;Delay_50ms:
;T = (k2*((k1*4)+7))+13
Delay_50ms:				;  CALL --> 2Tcy
    MOVLW	193			;  1Tcy, (K2) 
    MOVWF   contador2,0			;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
	Loop_Ext5:				  
	    MOVLW   63			;  1Tcy, (K1).
	    MOVWF   contador1,0		;  1Tcy
	Loop_Int5:
	    NOP				;  (K1*K2)*1Tcy
	    DECFSZ  contador1,1,0	;  (K1-1)*K2*1Tcy + K2*3Tcy
	    GOTO    Loop_Int5		;  (K1-1)*K2*2Tcy
	    NOP				;  (K2)* Tcy
	    NOP				;  (K2)* Tcy
	    DECFSZ  contador2,1,0	;  (K2-1)*1Tcy + 3Tcy 
	    GOTO    Loop_Ext5		;  (K2-1)*2Tcy
	    RETURN
;Delay_100ms:
;T = (k2*((4*k1)+6))+10
Delay_100ms:				;  CALL --> 2Tcy
    MOVLW	165			;  1Tcy, (K2) 
    MOVWF   contador2,0			;  1Tcy
    NOP					;  1Tcy   
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
	Loop_Ext6:				  
	    MOVLW   150			;  1Tcy, (K1).
	    MOVWF   contador1,0		;  1Tcy
	Loop_Int6:
	    NOP				;  (K1*K2)*1Tcy
	    DECFSZ  contador1,1,0	;  (K1-1)*K2*1Tcy + K2*3Tcy
	    GOTO    Loop_Int6		;  (K1-1)*K2*2Tcy
	    NOP				;  (K2)* Tcy
	    DECFSZ  contador2,1,0	;  (K2-1)*1Tcy + 3Tcy 
	    GOTO    Loop_Ext6		;  (K2-1)*2Tcy
	    RETURN
	    
;Delay_200ms:
;T = (k2*((4*(k1))+7))+11
Delay_200ms:				;  CALL --> 2Tcy
    MOVLW	243			;  1Tcy, (K2) 
    MOVWF   contador2,0			;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
    NOP					;  1Tcy
	Loop_Ext7:				  
	    MOVLW   204			;  1Tcy, (K1).
	    MOVWF   contador1,0		;  1Tcy
	Loop_Int7:
	    NOP				;  (K1*K2)*1Tcy
	    DECFSZ  contador1,1,0	;  (K1-1)*K2*1Tcy + K2*3Tcy
	    GOTO    Loop_Int7		;  (K1-1)*K2*2Tcy
	    NOP				;  (K2)* Tcy
	    NOP				;  (K2)* Tcy
	    DECFSZ  contador2,1,0	;  (K2-1)*1Tcy + 3Tcy 
	    GOTO    Loop_Ext7		;  (K2-1)*2Tcy
	    RETURN
;Delay_250ms
;T = (K2*((9*K1)+9))+7	    
Delay_250ms:				;  CALL --> 2Tcy
    MOVLW	141			;  1Tcy, (K2) 
    MOVWF   contador2,0			;  1Tcy
    NOP					;  1Tcy
	Loop_Ext8:				  
	    MOVLW   196			;  1Tcy, (K1).
	    MOVWF   contador1,0		;  1Tcy
	Loop_Int8:
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    NOP				;  (K1*K2)*1Tcy
	    DECFSZ  contador1,1,0	;  (K1-1)*K2*1Tcy + K2*3Tcy
	    GOTO    Loop_Int8		;  (K1-1)*K2*2Tcy
	    NOP				;  (K2)* Tcy
	    NOP				;  (K2)* Tcy
	    NOP				;  (K2)* Tcy
	    NOP				;  (K2)* Tcy
	    DECFSZ  contador2,1,0	;  (K2-1)*1Tcy + 3Tcy 
	    GOTO    Loop_Ext8		;  (K2-1)*2Tcy
	    RETURN