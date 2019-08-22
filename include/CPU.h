#ifndef CPU_H
#define CPU_H

#include<Module.h>

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

        //registers
            Mem16 PC; //Program Counter
            Mem8 SP; //Stack Pointer
            Mem8 A; //Accumulator
            Mem8 X; //Index Register
            Mem8 Y; //Index Register
            Mem8 P; //Processor Status (flags)
            Mem8 memory[65536];

        virtual void action();
        void powerUp();
        void reset();

        uint8_t read(short address);
        void write(short address, uint8_t value);
        //uint8_t accessData(bool write, short address, uint8_t value);

    protected:
        void mirror();
        void sendData();
        void loadRom();
        void instruction();





};

#endif // CPU_H
