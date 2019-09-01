#ifndef MODULE_H
#define MODULE_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

template<class T>
struct Mem
{
    Mem(){}
    Mem(T u):byt(u){}

    T byt;

    Mem& operator=(T a) {
        byt = a;
        return *this;
    }

    Mem& operator+=(T a) {
        byt+=a;
        return *this;
    }
    Mem& operator-=(T a) {
        byt-=a;
        return *this;
    }

    T& operator--(int) {
        T temp=byt--;
        return temp;
    }
    T& operator--() {
        return --byt;
    }
    T& operator++(int) {
        T temp=byt++;
        return temp;
    }
    T& operator++() {
        return ++byt;
    }

    operator T(){
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

class Module
{
    public:
        Module();

        long long cycle=0;

        //virtual void action()=0;

        short combine8(uint8_t a, uint8_t b){
            return (int(b) << 8) | a;

        }

    protected:

    private:
};

class CPU;
//class PPU;
class ROM;

#endif // MODULE_H
