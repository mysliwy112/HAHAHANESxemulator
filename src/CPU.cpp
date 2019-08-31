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
        //return memory[address];
        return rom.readCPU();
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
        rom.writeCPU(value);
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
            case 0x10:{//BPL //add cycle
                cycle+=2;
                if(!P.gBit(Negative)){
                    cycle++;
                    PC=adrRelative();
                }
                return;
            break;}
            case 0x18:{//CLC
                cycle+=2;
                P.sBit(Carry,0);
                return;
            break;}
            case 0x20:{//JSR //check
                cycle+=6;
                push(PC);
                PC=adrAbsolute();
                return;
            break;}
            case 0x24:{//BIT

                return;
            break;}
            case 0x28:{//PLP
                cycle+=4;
                P=pull();
                return;
            break;}
            case 0x2C:{//BIT

                return;
            break;}
            case 0x30:{//BMI //add cycle
                cycle+=2;
                if(P.gBit(Negative)){
                    cycle++;
                    PC=adrRelative();
                }
                return;
            break;}
            case 0x38:{//SEC
                P.sBit(Carry,1);
                return;
            break;}
            case 0x40:{//RTI
                cycle+=6;
                P=pull();
                PC=pull();
                return;
            break;}
            case 0x48:{//PHA
                cycle+=3;
                push(A);
                return;
            break;}
            case 0x4C:{//JMP //add cycles
                cycle+=3;
                PC=adrAbsolute();
                return;
            break;}
            case 0x50:{//BVC //add cycles
                if(!P.gBit(Overflow)){
                    cycle++;
                    PC=adrRelative();
                }
                return;
            break;}
            case 0x58:{//CLI
                cycle+=2;
                P.sBit(InterruptDis,0);
                return;
            break;}
            case 0x60:{//RTS //minus one?
                cycle+=6;
                PC=pull();
                return;
            break;}
            case 0x68:{//PLA
                cycle+=4;
                A=pull();
                setZero(A);
                setNegative(A);
                return;
            break;}
            case 0xC:{//JMP
                cycle+=5;
                PC=adrIndirect();
                return;
            break;}
            case 0x70:{//BVS //add cycles
                if(P.gBit(Overflow)){
                    cycle++;
                    PC=adrRelative();
                }
                return;
            break;}
            case 0x78:{//SEI
                cycle+=2;
                P.sBit(InterruptDis,1);
                return;
            break;}
            case 0x84:{//STY
                write(adrZero(),Y);
                return;
            break;}
            case 0x88:{//DEY
                cycle+=2;
                Y--;
                setZero(Y);
                setNegative(Y);
                return;
            break;}
            case 0x8C:{//STY
                write(adrAbsolute(),Y);
                return;
            break;}
            case 0x90:{//BCC //add cycles
                if(P.gBit(Carry)){
                    cycle++;
                    PC=adrRelative();
                }
                return;
            break;}
            case 0x94:{//STY
                write(adrZeroX(),Y);
                return;
            break;}
            case 0x98:{//TYA
                cycle+=2;
                A=Y;
                setZero(A);
                setNegative(A);
                return;
            break;}
            case 0x9C:{//SHY*

                return;
            break;}
            case 0xA0:{//LDY
                Y=read(adrImmediate());
                setZero(Y);
                setNegative(Y);
                return;
            break;}
            case 0xA4:{//LDY
                Y=read(adrZero());
                setZero(Y);
                setNegative(Y);
                return;
            break;}
            case 0xA8:{//TAY
                cycle+=2;
                Y=A;
                setZero(Y);
                setNegative(Y);
                return;
            break;}
            case 0xAC:{//LDY
                Y=read(adrAbsolute());
                setZero(Y);
                setNegative(Y);
                return;
            break;}
            case 0xB0:{//BCS //add cycles
                if(!P.gBit(Carry)){
                    cycle++;
                    PC=adrRelative();
                }
                return;
            break;}
            case 0xB4:{//LDY
                Y=read(adrZeroX());
                setZero(Y);
                setNegative(Y);
                return;
            break;}
            case 0xB8:{//CLV
                cycle+=2;
                P.sBit(Overflow,0);
                return;
            break;}
            case 0xBC:{//LDY
                Y=read(adrAbsoluteX());
                setZero(Y);
                setNegative(Y);
                return;
            break;}
            case 0xC0:{//CPY
                int8_t y=Y-read(adrImmediate());
                if(y<0)
                    P.sBit(Negative,1);
                else
                    P.sBit(Carry,1);
                if(y==0){
                    P.sBit(Zero,1);
                }
                return;
            break;}
            case 0xC4:{//CPY
                int8_t y=Y-read(adrZero());
                if(y<0)
                    P.sBit(Negative,1);
                else
                    P.sBit(Carry,1);
                if(y==0){
                    P.sBit(Zero,1);
                }
                return;
            break;}
            case 0xC8:{//INY
                cycle+=2;
                Y++;
                setZero(Y);
                setNegative(Y);
                return;
            break;}
            case 0xCC:{//CPY
                int8_t y=Y-read(adrAbsolute());
                if(y<0)
                    P.sBit(Negative,1);
                else
                    P.sBit(Carry,1);
                if(y==0){
                    P.sBit(Zero,1);
                }
                return;
            break;}
            case 0xD0:{//BNE //add cycle
                if(!P.gBit(Zero)){
                    cycle++;
                    PC=adrRelative();
                }
                return;
            break;}
            case 0xD8:{//CLD
                cycle+=2;
                P.sBit(Decimal,0);
                return;
            break;}
            case 0xE0:{//CPX
                int8_t x=X-read(adrImmediate());
                if(x<0)
                    P.sBit(Negative,1);
                else
                    P.sBit(Carry,1);
                if(x==0){
                    P.sBit(Zero,1);
                }
                return;
            break;}
            case 0xE4:{//CPX
                int8_t x=X-read(adrZero());
                if(x<0)
                    P.sBit(Negative,1);
                else
                    P.sBit(Carry,1);
                if(x==0){
                    P.sBit(Zero,1);
                }
                return;
            break;}
            case 0xE8:{//INX
                cycle+=2;
                X++;
                setZero(X);
                setNegative(X);
                return;
            break;}
            case 0xEC:{//CPX
                int8_t x=X-read(adrAbsolute());
                if(x<0)
                    P.sBit(Negative,1);
                else
                    P.sBit(Carry,1);
                if(x==0){
                    P.sBit(Zero,1);
                }
                return;
            break;}
            case 0xF0:{//BEQ
                if(P.gBit(Zero)){
                    cycle++;
                    PC=adrRelative();
                }
                return;
            break;}
            case 0xF8:{//SED
                cycle+=2;
                P.sBit(Decimal,1);
                return;
            break;}
            default:{
                insNOP();
                return;
            break;}
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
                else
                    P.sBit(Carry,1);
                if(a==0){
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








