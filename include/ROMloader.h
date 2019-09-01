#ifndef ROMLOADER_H
#define ROMLOADER_H


#include<Module.h>
#include<ROM.h>

class ROMloader : Module
{
    public:
        ROMloader();

        ROM *load(char* path);

        ROM *loadNES();

        ROM *mapper(int type);

        ifstream file;
        iNESstruct iNES;



    protected:

    private:
};

#endif // ROMLOADER_H
