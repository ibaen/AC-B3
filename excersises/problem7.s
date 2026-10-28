.text

    // dir reg state and control
    li x10,0xAC
    //Read reg state and control
    lw x11, 0(x10)
    //clear bit 6 and 4
    andi x11, x11, 0xAF
    // put bit 6 and 4 to read temeperature
    ori x11, x11, 0x40

    sb x11,0(x10)
// a loop to comporbate if  reg data have the data
wait:
    // read reg state and control
    lw x12, 0(x10)
    // get the bit disp, if 0 have the data
    andi x12, x12, 0x04
    //if is not cero ,repeat
    bnez x12,wait
    //read data from dir 0xAD, remember: 1(x10) 0xAC->0xAD 
    lhu x5,1(x10)




