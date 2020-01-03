#include "PPU.h"
#include "Machine.h"

PPU::PPU()
{
    memory.resize(0x4000);
}

void PPU::write(int address, Mem8 value)
{
    if(address<0x3F00){//CHR
        mod->rom->writePPU(address, value);
    }else if(address<0x4000){
        memory[address]=value;
    }else{
        throw "Out of range";
    }
}

Mem8 PPU::read(int address)
{
    if(address<0x3F00){//CHR
        return mod->rom->readPPU(address);
    }else if(address<0x4000){
        return memory[address];
    }else{
        throw "Out of range";
    }
}

void PPU::localWrite(int address, Mem8 value)
{
    if(address<0x2000){
        memory[address]=value;
    }else if(address<0x3F00){
        memory[(address-0x2000)%0x1000+0x2000]=value;
    }else if(address<0x4000){
        memory[address]=value;
    }else{
        throw "Out of range";
    }
}

Mem8 PPU::localRead(int address)
{
    if(address<0x2000){
        return memory[address];
    }else if(address<0x3F00){
        return memory[(address-0x2000)%0x1000+0x2000];
    }else if(address<0x4000){
        return memory[address];
    }else{
        throw "Out of range";
    }
}
