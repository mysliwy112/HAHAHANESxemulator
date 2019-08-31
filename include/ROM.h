#ifndef ROM_H
#define ROM_H

#include<Module.h>

#include<CPU.h>

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

class ROM : public Module
{
    public:
        ROM();
        virtual ~ROM();

        ifstream rom;

        //iNES
            iNESstruct iNES;

            vector <Mem8> trainer;

            vector <Mem8> PRGrom;
            vector <Mem8> CHRrom;

            vector <Mem8> MISrom;

            const char chNES[5]="NES\x1A";


        void load(char* path);

        void loadNES();

        void mapper();






    protected:

    private:
};

#endif // ROM_H
