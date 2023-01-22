;P1-Corrimiento_Leds
;________________________________________________________________________________
;________________________________________________________________________________
; @file: P1-Corrimiento_Leds.s
; @brief:
;   Este es un programa que permita realizar un corrimiento de leds 
;   conectados al puerto C, con un retardo de 500 ms en un numero de
;   corrimientos pares y un retardo de 250ms en un numero de corrimientos 
;   impares. El corrimiento inicia cuando se presiona el pulsador de la placa
;   una vez y se detiene cuando se vuelve a presionar. Y los leds en los pines 
;   RE0 y RE1, permiten visualizar cuando se da el corrimiento par o impar.
; @date: 7/01/23
; @author: Gonzales Alvarado Sebastian
; @version: 1.0.0
;_______________________________________________________________________________
;_______________________________________________________________________________
    
PROCESSOR   18F57Q84
#include    "bit_config.inc"
#include    <xc.inc>
#include    "retardos.inc"
    
PSECT	udata_acs
	datos:	DS  1
PSECT resetVect,class=CODE,reloc=2
resetVect:
    goto Main
    
PSECT CODE
 Main:
    CALL    Config_OSC,1
    CALL    Config_Port,1
    CLRF    TRISC,0	    ; TRIS<0:7> = 0 (Se configura todos los pines del puerto C como salida)
    CLRF    TRISE,0	    ; RIS<0:7> = 0 (Se configura todos los pines del puerto E como salida)
    CLRF    PORTE
    CLRF    PORTC
    MOVLW   00000001B

Loop:
    BTFSC   PORTA,3,0	   ; PORTA<3> =0?  -  ¿Botón presionado?
    GOTO    stop
    BTFSS   PORTA,3,0      ; PORT<3>  =1?  -  ¿Botón presionado?
    goto    Corrimiento
stop:			   ; Detiene el contador en su ùltimo estado
    goto    Loop
    
Corrimiento:
    
Corrimiento_impar:
    BTFSS   PORTA,3,0      ; PORT<3>  =1?  -  ¿Botón presionado?
    GOTO    stop	   ; Sí
    CLRF    PORTE	   ; No
    MOVWF   PORTC
    MOVWF   datos
    CALL    Delay_250ms,1
    RLNCF   datos,0
    BTFSS   datos,7
    GOTO    Corrimiento_impar
Corrimiento_par:
    BTFSS   PORTA,3,0      ; PORT<3>  =1?  -  ¿Botón presionado?
    GOTO    stop	   ; Sí
    CLRF    PORTE	   ; No
    BSF	    PORTE,1
    MOVWF   PORTC
    MOVWF   datos
    CALL    Delay_250ms,1
    CALL    Delay_250ms,1
    RLNCF   datos,0
    BTFSS   datos,7
    GOTO    Corrimiento_par
    GOTO    Corrimiento_impar
    
Config_OSC:
    ;Configuracion del Oscilador Interno a una frecuencia de 4MHz
    BANKSEL OSCCON1
    MOVLW   0x60	   ; seleccionamos el bloque del osc interno con un div:1
    MOVWF   OSCCON1,1
    MOVLW   0x02	   ; seleccionamos una frecuencia de 4MHz
    MOVWF   OSCFRQ,1
    RETURN
 
 Config_Port:     ;PORT-ANSEL-TRIS-WUP     	BUTTON:RA3

    ;Config Button
    BANKSEL PORTA
    CLRF    PORTA,1	   ; PORTA<7:0> = 0
    CLRF    ANSELA,1	   ; PortA digital
    BSF	    TRISA,3,1      ; RA3 como entrada
    BSF	    WPUA,3,1	   ; Activamos la resistencia Pull-Up del pin RA3
    RETURN
    
END resetVect