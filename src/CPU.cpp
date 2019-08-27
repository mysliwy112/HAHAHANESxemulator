#include "CPU.h"

CPU::CPU()
{
    //ctor
}
void CPU::powerUp(){
    PC=0xFFFD;
    P=0x34;
    A=X=Y=0;
    SP=0xFD;
    write(0x4017,0);
    write(0x4015,0);
    for(int i=0x4000;i<0x4013;i++){
        write(i,0);
    }
}

void CPU::reset(){
    SP-=3;
}

Mem8 CPU::read(int address){
    if(address<0x2000){ //zero page, stack, ram
        return memory[address%0x800];
    }else if(address<0x4000){//PPU registers
        return memory[(address-0x2000)%0x8+0x2000];
    }else if(address<0x4018){//APU registers
        return memory[address];
    }else if(address<0x4020){//APU test registers
        return memory[address];
    }else if(address<0x10000){//ROM
        return memory[address];
    }else if(address==0x10001){
        return A;
    }
}

void CPU::write(int address, uint8_t value){
    if(address<0x2000){ //zero page, stack, ram
        memory[address%0x800]=value;
    }else if(address<0x4000){//PPU registers
        memory[(address-0x2000)%0x8+0x2000]=value;
    }else if(address<0x4018){//APU registers
        memory[address]=value;
    }else if(address<0x4020){//APU test registers
        memory[address]=value;
    }else if(address<0x10000){//ROM
        memory[address]=value;
    }else if(address==0x10001){
        A=value;
    }
}



void CPU::action(){
    instruction();
    //interuption();
}

void CPU::instruction(){
    Mem8 instr(read(PC++));
    int address=0;

    switch(instr.gSmol(0,2)){
    case 0:

    break;

    case 1:
        switch(instr.gSmol(2,3)){
            case 0:
                address=adrIndirectX();
            break;
            case 1:
                address=adrZero();
            break;
            case 2:
                if(instr==0x85){
                    //NOP
                }else{
                    address=adrImmediate();
                }
            break;
            case 3:
                address=adrAbsolute();
            break;
            case 4:
                address=adrIndirectY();
            break;
            case 5:
                address=adrZeroX();
            break;
            case 6:
                address=adrAbsoluteY();
            break;
            case 7:
                address=adrAbsoluteX();
            break;
        }

        switch(instr.gSmol(5,3)){
            case 0:{//ORA
                A=A|read(address);
                setZero(A);
                setNegative(A);
            break;}
            case 1:{//AND
                A=A&read(address);
                setZero(A);
                setNegative(A);
            break;}
            case 2:{//EOR
                A=A^read(address);
                setZero(A);
                setNegative(A);
            break;}
            case 3:{//ADC
                int a=read(address)+A+P.gBit(Carry);
                if (a>255)
                    P.sBit(Carry,1);
                else
                    P.sBit(Carry,0);
                A=a;
                setZero(A);
                setNegative(A);
            break;}
            case 4:{//STA
                write(address,A);
                //(no additional cycles)
            break;}
            case 5:{//LDA
                A=read(address);
                setZero(A);
                setNegative(A);
            break;}
            case 6:{//CMP
                int8_t a=A-read(address);
                if(a<0)
                    P.sBit(Negative,1);
                else if(a>0)
                    P.sBit(Carry,1);
                else{
                    P.sBit(Zero,1);
                }
            break;}
            case 7:{//SBC
                int a=A-read(address)-!P.gBit(Carry);
                if (a>255)
                    P.sBit(Carry,0);
                else
                    P.sBit(Carry,1);
                A=a;
                setZero(A);
                setNegative(A);
            break;}
        }
    break;

    case 2:

    break;
    default:
        cout<<"Unidentified (illegal) instruction."<<instr<<endl;
    }
}

//ADC








