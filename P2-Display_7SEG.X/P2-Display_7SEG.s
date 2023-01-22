			   ;P2-Display_7SEG
;________________________________________________________________________________
;_______________________________________________________________________________
; @file: P2-Display_7SEG.s
; @brief:
;   Desarrollar un programa que permita mostrar los valores alfanuméricos(0-9
;    y A-F) en un display de 7 segmentos ánodo común, conectados al puerto D.
;    Los valores a mostrar serán seleccionados por la siguiente condición:
;	
;    -.	Si el botón de la placa no esta presionado,se muestran los valores
;	numéricos del 0al 9.
;    -.	Si el botón de la placa se mantiene presionado, se muestran los valores
;	de A hasta F.
;Todo ello con un retardo de 1 segundoentre transición.
; @date: 14/01/23
; @author: Gonzales Alvarado Sebastian
; @version: 1.0.0
;_______________________________________________________________________________
;_______________________________________________________________________________

PROCESSOR   18F57Q84
#include    "bit_config.inc"  /config statements should precede project file includes./
#include    <xc.inc>
#include    "retardos.inc"
    
PSECT udata_acs
    offset:  DS 1	    ;reserva 1 byte en acces ram
    
PSECT resetVect,class=CODE,reloc=2
    resetVect:
    goto Main
    
;Pasos para implementar computed goto
;1. Escribir el byte superior en PCLATU
;2. Escribir el byte alto en PCLATH
;3. Escribir el byte bajo en PCL
;NOTA: el offset debe ser multiplicado por 2 para el alineamiento en memoria
    
PSECT CODE
Main:
    CALL    Config_OSC
    CALL    Config_Port
    
Numeros:
    MOVLW   0		    ;definimos el valor del offset
Incremento:
    MOVWF   offset,0
    MOVLW   low highword(Conteo_numeros)
    MOVWF   PCLATU,1
    MOVLW   high(Conteo_numeros)
    MOVWF   PCLATH,1
    RLNCF   offset,0,0
    CALL    Conteo_numeros,1
    MOVWF   PORTD
    CALL    Delay_250ms,1
    CALL    Delay_250ms,1
    CALL    Delay_250ms,1
    CALL    Delay_250ms,1
    INCF    offset,0,0
    CALL    cambio2
    GOTO    Incremento
Conteo_numeros:		    ;Contiene los números del 0 al 9 en forma ascendente
    ADDWF   PCL,1,0
    RETLW   11000000B	    ;0
    RETLW   11111001B	    ;1
    RETLW   10100100B	    ;2
    RETLW   10110000B	    ;3
    RETLW   10011001B	    ;4
    RETLW   10010010B	    ;5
    RETLW   10000010B	    ;6
    RETLW   11111000B	    ;7
    RETLW   00000000B	    ;8
    RETLW   10011000B	    ;9
    GOTO    Numeros
    
Letras:
    BTFSC   PORTA,3,0
    GOTO    Numeros
    MOVLW   0
Incremento1:
    MOVWF   offset,0
    MOVLW   low highword(Conteo_letras)
    MOVWF   PCLATU,1
    MOVLW   high(Conteo_letras)
    MOVWF   PCLATH,1
    RLNCF   offset,0,0
    CALL    Conteo_letras,1
    MOVWF   PORTD
    CALL    Delay_250ms,1
    INCF    offset,0,0
    CALL    cambio1
    GOTO    Incremento1
    
Conteo_letras:		    ; Contiene las letras de A a F en forma ascendente
    ADDWF   PCL,1,0
    RETLW   10001000B	    ;A
    RETLW   10000011B	    ;B
    RETLW   11000110B	    ;C
    RETLW   10100001B	    ;D
    RETLW   10000110B	    ;E
    RETLW   10001110B	    ;F
    GOTO    Letras
    
cambio2:
    BTFSS   PORTA,3,0           ;PORTA<3> = 0? - Button press?
    GOTO    Letras
    RETURN
    
cambio1:
    BTFSC   PORTA,3,0           ;PORTA<3> = 0? - Button press?
    GOTO    Numeros
    RETURN
    
    
 Config_OSC:
    ;Configuracion del oscilador interno a una frecuencia de 4MHz
    BANKSEL OSCCON1 
    MOVLW   0x60                ;Seleccionamos el bloque del osc con un div:1
    MOVWF   OSCCON1,0
    MOVLW   0x02                ; Seleccionamos una frecuencia de 4MHz
    MOVWF   OSCFRQ,0
    RETURN
   
 Config_Port:  ;PORT-LAT-ANSEL-TRIS	    LED:RF3	BUTTON:RA3
    ;Config Led
    BANKSEL PORTD
    CLRF    PORTD,1	        ; PORTF = 0 
    SETF    LATD		; Pone en "1" a todas las salidas del puerto D
    CLRF    ANSELD,1	        ; ANSELF<7:0> = 0 -PORT F DIGITAL
    CLRF    TRISD		; Configura todos los pines del puerto D como salida

    ;Config Button
    BANKSEL PORTA
    CLRF    PORTA,1	        ; PORTA<7:0> = 0
    CLRF    ANSELA,1	        ; PortA digital
    BSF	    TRISA,3,1	        ; RA3 como entrada
    BSF	    WPUA,3,1	        ; Activamos la resistencia Pull-Up del pin RA3
    RETURN 
END resetVect