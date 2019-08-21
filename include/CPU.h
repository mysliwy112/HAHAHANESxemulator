#ifndef CPU_H
#define CPU_H


class CPU
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


        unsigned char memory[memsize];

    protected:
        void mirror();
        void sendData();
        void loadRom();
        void instruction();
        void writeData();

};

#endif // CPU_H
