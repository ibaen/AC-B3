
#define RegCabeza 0xA
#define RegSilla 0xB
unsigned char comando(unsigned char lateral, unsigned char inclinacion);

int main (){

    while (1)
    {
        //request to read 
        unsigned char cabeza=inb(RegCabeza);
        cabeza |= 0x80;
        outb(cabeza,RegCabeza);
        //confirm the request
        while((inb(RegCabeza) & 0x40) ==0);
        //get the info

        cabeza=inb(RegCabeza);
        unsigned char lateral=( cabeza & 0x0C)>>2;
        unsigned char inclinacion= cabeza & 0x03;


        while((inb(RegSilla)&0x02)!=0);
        //activate== 0 , so when you do <<2 you put the bit activate in 0
        outb((comando(lateral,inclinacion)<<2), RegSilla);

    }
    
    
    return 0;
}