#ifndef CPU_H
#define CPU_H

#include<Module.h>

#include<ROM.h>

class CPU : public Module
{
//    struct CPUmem{
//        Mem8 memory[65536];
//        Mem8& operator [] (short address){
//            if(address<0x2000){ //zero page, stack, ram
//                return memory[address%0x800];
//            }else if(address<0x4018){//I/O
//                return memory[(address-0x2000)%0x8+0x2000];
//            }else if(address<0x4020){
//
//            }
//        }
//
//    };

    enum flag{
        Carry,
        Zero,
        InterruptDis,
        Decimal,
        Break,
        Overflow=6,
        Negative
    };

    public:
        CPU();

        //params
            static const int memsize=0x10000;

        long long cycle=0;

        //modules
            //PPU *ppu;
            //APU *apu;
            ROM *rom;

        //registers
            Mem16 PC; //Program Counter
            Mem8 SP; //Stack Pointer
            Mem8 A; //Accumulator
            Mem8 X; //Index Register
            Mem8 Y; //Index Register
            Mem8 P; //Processor Status (flags)

        Mem8 memory [65536];


        virtual void action();
        void powerUp();
        void reset();

        Mem8 read(int address);
        void write(int address, uint8_t value);
        //uint8_t accessData(bool write, short address, uint8_t value);

        void push(int value);
        Mem8 pull();



    protected:
        void mirror();
        void sendData();
        void loadRom();
        void instruction();

        void setNegative(Mem8 num){
            P.sBit(Negative,num.gBit(Negative));
        }

        void setZero(Mem8 num){
            P.sBit(Zero,!num);
        }


        //addressing modes
        int adrAccumulator(){
            cycle+=2;
            return 0x10001;
        }
        int adrImmediate(){
            cycle+=2;
            return PC++;
        }
        int adrZero(){
            cycle+=3;
            return read(PC++);
        }
        int adrZeroX(){
            cycle+=4;
            return (read(PC++)+X)%256;
        }
        int adrZeroY(){
            cycle+=4;
            return (read(PC++)+Y)%256;
        }
        int adrRelative(){
            //add cycle
            return static_cast<int>(read(PC++))+PC;
        }
        int adrAbsolute(){
            //relative? 4
            return combine8(read(PC++),read(PC++));
        }
        int adrAbsoluteX(){
            //add cycle
            cycle+=4;
            return combine8(read(PC++),read(PC++))+X;
        }
        int adrAbsoluteY(){
            //add cycle
            cycle+=4;
            return combine8(read(PC++),read(PC++))+Y;
        }
        int adrIndirect(){
            //+5 only JMP
            int address=combine8(read(PC++),read(PC++));
            return combine8(read(address),read(address+1));
        }
        int adrIndirectX(){
            cycle+=6;
            int address=PC+++X;
            return read(combine8(read(address%256),read((address+1)%256)));
        }
        int adrIndirectY(){
            //add cycle
            cycle+=5;
            int address=PC++;
            return read(combine8(read(address),read((address+1)%256))+Y);
        }

        //special instructions
        void insNOP(){
            cycle+=2;
        }



};

#endif // CPU_H
