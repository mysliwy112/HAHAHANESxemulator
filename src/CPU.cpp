#include "CPU.h"

CPU::CPU()
{
    //ctor
}
void CPU::powerUp(){
    P=0x34;
    A=X=Y=0;
    SP=0xFD;
    memory[0x4017]=0;
    memory[0x4015]=0;

}

uint8_t CPU::read(short address){
    if(address<0x2000){ //zero page, stack, ram
        return memory[address%0x800];
    }else if(address<0x4000){//PPU registers
        return memory[(address-0x2000)%0x8+0x2000];
    }else if(address<0x4018){//APU registers
        return memory[address];
    }else if(address<0x4020){//APU test registers
        return memory[address];
    }else{//ROM
        return memory[address];
    }

}

void CPU::write(short address, uint8_t value){
    if(address<0x2000){ //zero page, stack, ram
        memory[address%0x800]=value;
    }else if(address<0x4000){//PPU registers
        memory[(address-0x2000)%0x8+0x2000]=value;
    }else if(address<0x4018){//APU registers
        memory[address]=value;
    }else if(address<0x4020){//APU test registers
        memory[address]=value;
    }else{//ROM
        memory[address]=value;
    }
}

void CPU::reset(){
    SP-=3;
}

void CPU::action(){
    instruction();
    //interuption();
}

void CPU::instruction(){
    Mem8 instr(read(PC));
    switch(instr.gSmol(0,2)){
    case 0:

    break;
    case 1:

    break;
    case 2:

    break;
    default:
        cout<<"Unidentified (illegal) instruction."<<instr<<endl;
    }
}
