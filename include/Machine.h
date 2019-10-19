#ifndef MACHINE_H
#define MACHINE_H

#include<CPU.h>
#include<ROM.h>
#include<IO.h>
//#include<APU.h>
//#include<PPU.h>



class Machine
{
    struct IOsignals{
        bool OUT0;
        bool OUT1;
        bool OUT2;
        bool OE1;
        bool OE2;
        Mem8 PAD1;
        Mem8 PAD2;

    };

    public:

        Machine();
        virtual ~Machine();

        //components
            ROM *rom;
            CPU cpu;
            //PPU *ppu;
            //APU *apu;

        //pads
            IO *expansion;
            IO *pad1;
            IO *pad2;

        //signals
            IOsignals IOsig;

        void powerUP();
        void reset();
        void insertROM(ROM *rom);

        void toIO();
        Mem8 fromIO(bool pad);

        void plugController(int port, IO *contr);
        void uplugController(int port);
        void swapController(int port, IO *contr);

    protected:

    private:
};

#endif // MACHINE_H
