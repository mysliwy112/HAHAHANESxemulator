#ifndef CPU_H
#define CPU_H

#include<Module.h>
class CPU : Module
{
    public:
        CPU();
        //params
            int memsize=65535;

        //registers
            unsigned short PC; //Program Counter
            unsigned short SP; //Stack Pointer
            unsigned char A; //Accumulator
            unsigned char X; //Index Register
            unsigned char Y; //Index Register
            unsigned char P; //Processor Status (flags)


        //vector<int> memory(2);

    protected:
        void mirror();
        void sendData();
        void loadRom();
        void instruction();
        void writeData();
        vector<int> akk(2,0);

};

#endif // CPU_H
