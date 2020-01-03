#ifndef PPU_H
#define PPU_H

#include<vector>

#include "Module.h"

using namespace std;

class Machine;
class PPU : public Module
{
    public:
        PPU();

        //registers


        vector<Mem8> memory;

        void write(int address, Mem8 value);
        Mem8 read(int address);

        void localWrite(int address, Mem8 value);
        Mem8 localRead(int address);

    protected:

    private:
};

#endif // PPU_H
