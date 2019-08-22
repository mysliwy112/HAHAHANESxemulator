#ifndef CPU_H
#define CPU_H

#include<Module.h>







class CPU : public Module
{
    struct CPUmem{
        Mem8 memory[65536];
        Mem8& operator [] (short i){
            if(i<8)
                return memory[i];
            else
                return memory[0];
        }
    };
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
            static const int memsize=65535;

        long long cycle=0;

        //registers
            Mem16 PC; //Program Counter
            Mem8 SP; //Stack Pointer
            Mem8 A; //Accumulator
            Mem8 X; //Index Register
            Mem8 Y; //Index Register
            Mem8 P; //Processor Status (flags)
            CPUmem memory;

        virtual void action();
    protected:
        void mirror();
        void sendData();
        void loadRom();
        void instruction();




};

#endif // CPU_H
