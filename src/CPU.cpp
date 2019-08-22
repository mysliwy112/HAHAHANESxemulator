#include "CPU.h"

CPU::CPU()
{
    //ctor
}


char CPU::readData(short address){
    if(address<0x2000){
        return memory[address%0x800];
    }else if(address<0x4020){

    }else{

    }
}

void CPU::action(){
    instruction();
    interuption();
}

void CPU::instruction(){
    Mem8 instr=readData(PC);
    switch(instr.gSmol(0,2)){
    case 0:

    break;
    case 1:

    break;
    case 2:

    break;
    case default:
        cout<<"Unidentified (illegal) instruction"<<instr<<endl;



    }


}
