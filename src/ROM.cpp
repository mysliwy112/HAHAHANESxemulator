#include "ROM.h"
#include "Machine.h"

ROM::ROM()
{
    //ctor
}

ROM::~ROM()
{
    //dtor
}



Mem8 ROM::readCPU(int address){
    return PRGrom[address-0x4020];
}

void ROM::writeCPU(int address, Mem8 value){
    PRGrom[address-0x4020]=value;
}

Mem8 ROM::readPPU(int address){
    if(address<0x2000){
        return CHRrom[address];
    }else if(address<0x2000){
        return mod->ppu.localRead(address);
    }
    throw "Bad address";
}

void ROM::writePPU(int address, Mem8 value){
    if(address<0x2000){
        CHRrom[address]=value;
    }else if(address<0x2000){
        mod->ppu.localWrite(address,value);
    }
}



