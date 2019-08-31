#ifndef ROMLOADER_H
#define ROMLOADER_H

#include<Module.h>

struct iNES{
    uint8_t PRGOsize;
    uint8_t CHRsize;
    Mem8 F6;
    Mem8 F7;
    uint8_t PRGAsize;
    Mem8 F9;
    Mem8 F10;
    uint8_t name[5];


};



class ROMloader : public Module
{
    public:
        ROMloader();
        vector<>
        void load();

    protected:

    private:
};

#endif // ROMLOADER_H
