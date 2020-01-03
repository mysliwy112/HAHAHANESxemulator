#ifndef MODULE_H
#define MODULE_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
class Machine;

template<class T>
bool gBit(T &byt,int i){
    return (byt >> i) & 0x1;
}
template<class T>
void sBit(T &byt, int i,bool v){
    byt ^= (-v ^ byt) & (0x1 << i);
}
template<class T>
T gSmol(T &byt,int i, int siz){
    return (byt >> i) & ((0x2 << siz)-1);
}
typedef uint8_t Mem8;
typedef uint16_t Mem16;
typedef uint32_t Mem32;
typedef uint64_t Mem64;

struct iNESstruct{
    Mem8 PRGOsizeLSB;
    Mem8 CHROsizeLSB;
    Mem8 mirroring;
    Mem8 battery;
    Mem8 trainer;
    Mem8 fourScreen;

    Mem8 mapperType;
    Mem8 submapperType;

    Mem8 consoleType;

    Mem8 PRGOsizeMSB;
    Mem8 CHROsizeMSB;

    Mem8 PRGAsize;
    Mem8 EEPROMsize;

    Mem8 CHRAsize;
    Mem8 CHRNVAsize;

    Mem8 CPPmode;

    Mem8 vsPPUtype;
    Mem8 vsHWtype;

    Mem8 ExConsoleType;

    Mem8 misROMnumber;

    Mem8 defExDevice;
};

short combine8(uint8_t a, uint8_t b);


class Module
{
    public:
        Module();

        Machine *mod;
        long long cycle=0;

        //virtual void action()=0;
        void setMachine(Machine *mach);


    protected:

    private:
};

//class CPU;
//class PPU;
//class ROM;

//class Machine;

#endif // MODULE_H
