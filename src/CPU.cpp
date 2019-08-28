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

void CPU::push(int value){
    write(SP--+0x100,value);
}

Mem8 CPU::pull(){
    return read(++SP+0x100);
}


void CPU::action(){
    instruction();
    //interuption();
}

void CPU::instruction(){
    Mem8 instr(read(PC++));
    int address=0;

    switch(instr.gSmol(0,2)){
    case 0x0:
        switch(instr){
            case 0x0:{//BRK
                cycle+=7;
            break;}
            case 0x8:{//PHP
                cycle+=3;
                push(P);
                return;
            break;}
            case 0x10{//BPL

                return;
            break;}
            case 0x18:{//CLC

                return;
            break;}
            case 0x20:{//JSR

                return;
            break;}
            case 0x24:{//BIT

                return;
            break;}
            case 0x28:{//PLP

                return;
            break;}
            case 0x2C:{//BIT

                return;
            break;}
            case 0x30:{//BMI

                return;
            break;}
            case 0x38:{//SEC

                return;
            break;}
            case 0x40:{//RTI

                return;
            break;}
            case 0x48:{//PHA

                return;
            break;}
            case 0x4C:{//JMP

                return;
            break;}
            case 0x50:{//BVC

                return;
            break;}
            case 0x58:{//CLI

                return;
            break;}
            case 0x60:{//RTS

                return;
            break;}
            case 0x68:{//PLA

                return;
            break;}
            case 0xC:{//JMP

                return;
            break;}
            case 0x70:{//BVS

                return;
            break;}
            case 0x78:{//SEI

                return;
            break;}
            case 0x84:{//STY

                return;
            break;}
            case 0x88:{//DEY

                return;
            break;}
            case 0x8C:{//STY

                return;
            break;}
            case 0x90:{//BCC

                return;
            break;}
            case 0x94:{//STY

                return;
            break;}
            case 0x98:{//TYA

                return;
            break;}
            case 0x9C:{//SHY*

                return;
            break;}
            case 0xA0:{//LDY

                return;
            break;}
            case 0xA4:{//LDY

                return;
            break;}
            case 0xA8:{//TAY

                return;
            break;}
            case 0xAC:{//LDY

                return;
            break;}
            case 0xB0:{//BSC

                return;
            break;}
            case 0xB4:{//LDY

                return;
            break;}
            case 0xB8:{//CLV

                return;
            break;}
            case 0xBC:{//LDY

                return;
            break;}
            case 0xC0:{//CPY

                return;
            break;}
            case 0xC4:{//CPY

                return;
            break;}
            case 0xC8:{//INY

                return;
            break;}
            case 0xCC:{//CPY

                return;
            break;}
            case 0xD0:{//BNE

                return;
            break;}
            case 0xD8:{//CLD

                return;
            break;}
            case 0xE0:{//CPX

                return;
            break;}
            case 0xE4:{//CPX

                return;
            break;}
            case 0xE8:{//INX

                return;
            break;}
            case 0xEC:{//CPX

                return;
            break;}
            case 0xF0:{//BEQ

                return;
            break;}
            case 0xF8:{//SED

                return;
            break;}
            default:{
                insNOP();
                return;
            break;}
        }






















        }
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
                    insNOP();
                    return;
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
                return;
            break;}
            case 1:{//AND
                A=A&read(address);
                setZero(A);
                setNegative(A);
                return;
            break;}
            case 2:{//EOR
                A=A^read(address);
                setZero(A);
                setNegative(A);
                return;
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
                return;
            break;}
            case 4:{//STA
                write(address,A);
                //(no additional cycles)
                return;
            break;}
            case 5:{//LDA
                A=read(address);
                setZero(A);
                setNegative(A);
                return;
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
                return;
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
                return;
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








