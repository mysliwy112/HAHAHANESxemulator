#include "ROM.h"

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

}

void ROM::writePPU(int address, Mem8 value){

}



