# uC1_2022_Gonzales_Sebastian

**Curso:** Microcontroladores I

**Autor:** Gonzales Alvarado Sebastian

**Tarjeta** Curiosity Nano PIC18f57q84

**Entorno:** MPLAB X IDE

**Lenguaje:** AMS - C

UNIVERSIDAD NACIONAL DE PIURA, PERÚ

# **Contenido:**

 - **Retardos:**
   - *retardos.inc:*
	   Esta librería contiene las instrucciones necesarias para generar los siguientes retardos: 10us, 25us, 50us, 100us, 200us 250us, 500us, 1ms, 5ms, 10ms, 25ms, 50ms, 100ms, 200ms, 250ms. con un tiempo de oscilación de 4MHz. 
 - **P1-Corrimiento_Leds:**
	 - *P1-Corrimiento_Leds.s:*
	 Este es un programa que permite realizar un corrimiento de leds conectados al puerto C, con un retardo de 500 ms en un numero de corrimientos pares y un retardo de 250ms en un numero de corrimientos impares. El corrimiento inicia cuando se presiona el pulsador de la placa una vez y se detiene cuando se vuelve a presionar. Además cuenta con un visualizador del corrimiento par e impar en los puertos E1 y E0, respectivamente.

 - **P2-Display_7SEG:** 
	 -  *P2-Display_7SEG.s:*	
			 
		Este es un programa que permite mostrar los valores alfanuméricos (0-9 y A-F) en un display de 7 segmentos ánodo común, conectados al puerto D. Este programa cumple con las siguientes condiciones:
		- Si el botón de la placa no esta presionado, se muestran los valores numéricos del 0 al 9.
		- Si el botón de la placa se mantiene presionado, se muestran los valores de A hasta F.
- **Parcial_2_p1:** 
	 -  *Secuencia_leds.s:*	
Este es un programa para que al presionar el botón de placa se ejecute un patrón de encendidos de leds previamente establecido en los pines del puerto C de la placa. La secuencia se detiene al presionar otro pulsador externo conectado en el pin RB4 o hasta que el número de repeticiones sea 5. Otro pulsador externo conectado al RF2 reinicia toda la secuencia y apaga los leds.
