#define RegData 0x30
#define RegControl 0x31
#define RegState 0x32
#define InterruptVector 0x0A
#define SENSOR 2
/**
 * a)
 * Implement the system's initial configuration function. This function takes an integer parameter that indicates whether to
 *  configure the system in polling mode (1) or interrupt-driven mode. If interrupt-driven mode is selected, it must be registered
 *  with interrupt vector 0xA. Before beginning the configuration, you must check whether the system is powered on; if it is not, 
 * you must power it on and wait until it is ready.
 */

void isOn(void);
void config(int configMode);
void polling(int sensor);
void interruption(void);
void rsi(void);

int main(){
    
    int configMode=1;
    config(configMode);

    if(configMode==1){
        polling(SENSOR);
    }

    return 0.;
}

 void isOn(){
    unsigned char state=inb(RegState); 
    
     if((state & 0x04)==0){
        unsigned char control=inb(RegControl);
        outb(RegControl,control | 0x80); //on
        while((inb(RegState)&0x04)==0); // waiting until its on
     }
     
 }
 

void config(int configMode){

    isOn();

    unsigned char control= inb(RegControl);

    if(configMode==1){
        //Put bit 6 to one for select polling
        control |= 0x40; 
        outb(RegControl, control);
    }else{
        control &= ~0x40;
        outb(RegControl,control);
        interruption();
    }

}

void interruption(){

    if( registrar_irq(InterruptVector,rti,"dev/miDispositvo")==0){
        //enable interruption line
        enable_irq(InterruptVector);
    }
   
}

void rti(){

    disable();
    //attend when the interruption take action
    enable();

}

void polling(int sensor){
    unsigned char control=inb(RegControl);
    control &= ~0x38;   
    control|=(sensor<<4);

    outb(RegControl,control);

    while((inb(RegState) & 0x08)!=0);
    return inb(RegData);
}