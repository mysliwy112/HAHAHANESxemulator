#ifndef ROM_H
#define ROM_H

#include<Module.h>


class ROM : public Module
{
    public:
        ROM();
        virtual ~ROM();

        //iNES
            iNESstruct iNES;

            vector <Mem8> trainer;

            vector <Mem8> PRGrom;
            vector <Mem8> CHRrom;

            vector <Mem8> MISrom;

        virtual Mem8 readCPU(int address);
        virtual void writeCPU(int address, Mem8 value);

        virtual Mem8 readPPU(int address);
        virtual void writePPU(int address, Mem8 value);

    protected:

    private:
};

#endif // ROM_H
