#include <stdint.h>
#include <stdio.h>

//bit 0 conectado a señal de reloj(R)
//bit 1 conectado a seññal de datos(D)
#define regDatos 0x1000; 
//bit 0 habilita el dispositivo si esta a uno
//bit 1 el bit 1, habilita la generación de interrupciones
#define regControl 0x1001;