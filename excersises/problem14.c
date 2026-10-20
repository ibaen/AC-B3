
#define regControl 0x30
#define regState 0x31
// A-10-1010, B-11-1011,C-12-1100
int main(){

    unsigned char control=inb(0x30);
    unsigned char state=inb(0x31);

    int sensorType= 2;
    int pumpActivate=2;

    tankFillingVerification();

    return 0;
}
int isFullWaterPumpisFullWaterPump(int sensorType){
    unsigned char control=inb(0x30);
    //clean bit s1 and s0 and leer_s to indicate read water sensor , and
    //next set the sensorType that we want to read
    control=(control & 0xF8)| (sensorType<<1);

    outb(control ,regControl); 

    while ((inb(0x31) & 0x04) !=0);

    unsigned char state=inb(regState);
    return ((state & 0x80)>>7);
    
    
}

void tankFillingVerification(){

    while (1)
    {
        /* code */
    }
    
}
