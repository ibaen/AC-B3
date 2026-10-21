
#define regControl 0x30
#define regState 0x31
// A-10-1010, B-11-1011,C-12-1100
int main(){

    tankFillingVerification();

    return 0;
}
int isFullWaterPump(int sensorType){
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
        for (int i = 0; i < 4; i++)
        {
            if (isFullWaterPump(i)!=1)
            {
                unsigned char control=inb(regControl);
                control &=0x1F;

                //Select the pomp and activate 
                control |=(i<<6) |0x20;
                outb(control, regControl);

                //wait unti it is  detected to be full
                while (isFullWaterPump(i)==0);

                control=inb(regControl );
                control &=0xDF;
                outb(control,regControl);
                

                
            }
            
        }
        
    }
    
}
