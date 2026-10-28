#define RegControl 0x30
#define RegState 0x31
#define RegData 0x32
#define InterruptionVector 0xA
#define configMode 0 // 1 for polling and 0 for interruption

void configuration(int config);
void powerOnCheck();
void rti();
unsigned char polling(int sensor);

int main(){

    if(configMode>1 || configMode<0){
        printf("ERROR- Select the correct configMode");
    }else{
        configuration(configMode);
    }


    return 0;
}
//a

void configuration(int config){

    powerOnCheck();
    unsigned char control= inb(RegControl);

    if (config!=0)
    {
       control |=0x40;
       outb(RegControl,control);
    }else{
        control &=~0x40;
       outb(RegControl,control);
        if(request_irq(InterruptionVector,rti,"/dev/miDisposititvo")==0){
            enable_irq(InterruptionVector);
        }
    }
    
}



//b

unsigned char  polling(int sensor){
    if(sensor>3){
        printf("ERROR-Select the correct Sensor(0-3)");
        return 0;
    }else{
        unsigned char control=inb(RegControl);
        control &= ~ 0x0E;
        control |= (sensor<<2);
        outb(RegControl,control);
        while(((inb(RegState)&0x04)!=0));
        return inb(RegData);
    }
}
//c
void rti(){
    disable();

    unsigned char state= inb(RegState);
    unsigned char control= inb(RegControl);

    if((state & 0x80)!=0){
        int siren= (state & 0x60)>>5;

        control &= ~0x1C;
        control |=siren<<2;
        control |= 0x10;

        outb(RegControl,control);
       
    }

    enable();
}
