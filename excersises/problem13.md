# E ies 13

<p> Se quiere construir un sistema de comunicación serie síncrona entre dos dispositivos, usando dos líneas:
R y D. Los datos se reciben bit a bit por la línea D, con un nuevo bit por cada flanco de bajada del reloj R, y
comenzando por el más significativo. Si no se reciben datos, la línea de reloj permanece a 1. Por ejemplo, el dato
11000100 (en binario):</p>

![imagen](../img/pb13.png)

<p>Esta información es mandada por el dispositivo origen, mientras que el dispositivo destino se encarga de
controlar los valores del reloj e ir leyendo de la línea de datos cuando sea oportuno. El receptor, dispone de un
controlador de E/S que recoge el valor de estas dos señales de manera constante y lo guarda en un registro de
datos (al guardar un nuevo valor, sustituye el valor anterior del registro anteriormente mencionado), al que se
puede acceder mediante una lectura a la dirección 0x1000. En este registro de 8 bits, el bit 0 se encuentra
conectado a la señal de reloj (R) y el bit 1 a la señal de datos (D).
Además, tiene un registro de control (accesible en la dirección 0x1001) mediante el que se controla la
activación del dispositivo: El bit 0 habilita el dispositivo si está a uno, y el bit 1, habilita la generación de
interrupciones). Si el dispositivo genera interrupciones, producirá una interrupción al procesador cuyo vector
de interrupción es el 27)</p>

### Apartado A

<p>Diseñe un programa que inicialice el periférico para la adquisición de datos por E/S por polling. El
programa ha de recoger 1024 bytes y después, desactivar el dispositivo. Recuerde que, por cada byte,
tendrá que hacer 8 lecturas de la señal D (una por bit), esperando los flancos de bajada de la señal R. 

Además, tendrá que concatenar estos bits mediante desplazamientos para obtener un byte. Cada vez
que forme un byte, deberá almacenarlo en un vector de 1024 posiciones (unsigned char v[1024];).
</p>

```c
#include <stdint.h>
#include <stdio.h>

//bit 0 conectado a señal de reloj(R) | The bit 0 connect to the watch signal
//bit 1 conectado a seññal de datos(D)| The bit 1 connect to the data signal
#define regDatos 0x1000
//bit 0 habilita el dispositivo si esta a uno  | The bit 0 enable the device if set to one
#define regControl 0x1001

int main(){

    unsigned char v[1024];
    unsigned char control=inb(regControl);

    unsigned char enable= control & 0x01;
    unsigned char type=(control & 0x02)>>1;
  

    if (enable==1)
    {
        polling(v);
        // we can do the same with ~0x01
        outb(control & 0xFE,regControl);
    }
   return 0;    
}

void polling(unsigned char *v){

    for (int i = 0; i < 1024; i++)
    {
       v[i]=read_byte();
    }
    

}

unsigned char read_byte(){
    int ac=0;
    unsigned char data=0;

    while (ac<8)
    {
        while ((inb(regDatos) & 0x01)!=0);
        //We isolate the bit that we want to add to the data
        unsigned char bit_d=(inb(regDatos)&0x2)>>1;
        //Now we shift 1 bit to the left and add the new data
        data=(data<<1) | bit_d;
        ac++;
        // wait to not read the same bit 
        while ((inb(regDatos) & 0x01) == 0);
    }
    return data;
}

### Apartado B



