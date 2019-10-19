#include "Machine.h"

Machine::Machine()
{
    cpu.setMachine(this);
}

Machine::~Machine()
{
    //dtor
}

void Machine::insertROM(ROM *rom){
    this->rom=rom;
}

void Machine::powerUP()
{

}

void Machine::reset()
{

}

void Machine::toIO()
{
    pad1->OUTsignal(IOsig.OUT0);
    pad2->OUTsignal(IOsig.OUT0);
}

Mem8 Machine::fromIO(bool pad)
{
    Mem8 in=0;
    if(pad=0)
        in=pad1->write();
    else
        in=pad2->write();
    return 0;
}




void Machine::plugController(int port, IO *contr){
    switch(port){
        case 0:
            if(expansion==nullptr){
                expansion=contr;
            }else{
                throw "Already plugged";
            }
            break;
        case 1:
            if(pad1==nullptr){
                pad1=contr;
            }else{
                throw "Already plugged";
            }
            break;
        case 2:
            if(pad2==nullptr){
                pad2=contr;
            }else{
                throw "Already plugged";
            }
            break;
        default:
            throw "Invalid controller port";
    }
}

void Machine::uplugController(int port){
    switch(port){
        case 0:
            if(expansion!=nullptr){
                delete[] expansion;
            }else{
                throw "Not plugged controller";
            }
            break;
        case 1:
            if(pad1!=nullptr){
                delete[] pad1;
            }else{
                throw "Not plugged controller";
            }
            break;
        case 2:
            if(pad2!=nullptr){
                delete[] pad2;
            }else{
                throw "Not plugged controller";
            }
            break;
        default:
            throw "Invalid controller port";
    }
}

void Machine::swapController(int port, IO* contr){
    uplugController(port);
    plugController(port,contr);
}

