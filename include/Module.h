#ifndef MODULE_H
#define MODULE_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
class Machine;

template<class T>
struct Mem
{
    Mem(){}
    Mem(T u):byt(u){}

    T byt;

//    Mem& operator=(Mem& a) {
//        cout<<int(a)<<endl;
//        byt = a.byt;
//        return *this;
//    }

    template <class T2>
    Mem<T>& operator=( const Mem<T2>& number )
    {
        byt = number.byt;
        return *this;
    }

//    Mem& operator+=(T a) {
//        byt+=a;
//        return *this;
//    }
//    Mem& operator-=(T a) {
//        byt-=a;
//        return *this;
//    }
//
//    T operator--(int) {
//        T temp=byt--;
//        return temp;
//    }
//    T operator--() {
//        return --byt;
//    }
//    T operator++(int) {
//        T temp=byt++;
//        return temp;
//    }
//    T operator++() {
//        return ++byt;
//    }

    operator T ()const{
        return byt;
    }
    operator T&(){
        return byt;
    }
    bool gBit(int i){
        return (byt >> i) & 0x1;
    }
    void sBit(int i,bool v){
        byt ^= (-v ^ byt) & (0x1 << i);
    }
    T gSmol(int i, int siz){
        return (byt >> i) & ((0x2 << siz)-1);
    }
};

using Mem8=Mem<uint8_t>;
using Mem16=Mem<uint16_t>;
using Mem32=Mem<uint32_t>;
using Mem64=Mem<uint64_t>;

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
