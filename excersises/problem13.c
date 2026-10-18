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

