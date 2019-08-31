#include "ROM.h"

ROM::ROM()
{
    //ctor
}

ROM::~ROM()
{
    //dtor
}

void ROM::load(char* path){
    rom.open(path,ios::binary);
    if(!rom.good()){
        cout<<"Can't load rom."<<endl;
        rom.close();
        return;
    }
    char type[4];
    rom.read(type,4);
    if(type==chNES){
        loadNES();
    }else{
        cout<<"Unsupported file format: "<<type<<endl;
    }
}

void ROM::loadNES(){
    Mem8 header[16];
    rom.read((char*)header, 12);

    bool NES2;
    if (header[7].gSmol(1,2)==2){
        NES2=true;
        cout<<"NES 2.0 format"<<endl;
        iNES.PRGOsizeLSB=header[4];
        iNES.CHROsizeLSB=header[5];
        iNES.mirroring=header[6].gBit(0);
        iNES.battery=header[6].gBit(1);
        iNES.trainer=header[6].gBit(2);
        iNES.fourScreen=header[6].gBit(3);
        iNES.mapperType=header[6].gSmol(4,4);

        iNES.consoleType=header[7].gSmol(0,2);
        iNES.mapperType+=header[7].gSmol(4,4)*0xF;

        iNES.mapperType+=header[8].gSmol(0,4)*0xFF;
        iNES.submapperType=header[8].gSmol(4,4);

        iNES.PRGOsizeMSB=header[9].gSmol(0,4);
        iNES.CHROsizeMSB=header[9].gSmol(4,4);

        iNES.PRGAsize=header[10].gSmol(0,4);
        iNES.EEPROMsize=header[10].gSmol(4,4);

        iNES.CHRAsize=header[11].gSmol(0,4);
        iNES.CHRNVAsize=header[11].gSmol(4,4);

        iNES.CPPmode=header[12].gSmol(0,2);

        if(iNES.consoleType==1){
            iNES.vsPPUtype=header[13].gSmol(0,4);
            iNES.vsHWtype=header[13].gSmol(4,4);
        }else if(iNES.consoleType==3){
            iNES.ExConsoleType=header[13].gSmol(0,4);
        }

        iNES.misROMnumber=header[14].gSmol(0,2);

        iNES.defExDevice=header[15].gSmol(0,6);
    }else{
        NES2=false;
        cout<<"iNES format"<<endl;
        iNES.PRGOsizeLSB=header[4];
        iNES.PRGOsizeMSB=0;
        iNES.CHROsizeLSB=header[5];
        iNES.CHROsizeMSB=0;

        iNES.mirroring=header[6].gBit(0);
        iNES.battery=header[6].gBit(1);
        iNES.trainer=header[6].gBit(2);
        iNES.fourScreen=header[6].gBit(3);
        iNES.mapperType=header[6].gSmol(4,4);

        iNES.consoleType=0;
        if(header[7].gBit(0))
            iNES.consoleType=1;
        else if(header[7].gBit(1)){
            iNES.consoleType=2;
        }
        iNES.mapperType+=header[7].gSmol(4,4)*0xF;

        iNES.PRGAsize=header[8];

        iNES.CPPmode=header[9].gBit(0);

        //ignore biatch
        //iNES.TVtype=header[10].gBit(0);
    }
    bool dbg=1;
    if(dbg){


    }

    if(iNES.trainer==1){
        char buffer[512];
        trainer.resize(512);
        rom.read(buffer,512);
        trainer.insert(trainer.begin(),&buffer[0],&buffer[512]);
    }

    long long PRGOsize=0;
    if(iNES.PRGOsizeMSB==0xF){
        int multi=iNES.PRGOsizeLSB.gSmol(0,2)*2+1;
        PRGOsize=(2 << iNES.PRGOsizeLSB.gSmol(2,6))*multi;
    }else{
        PRGOsize=combine8(iNES.PRGOsizeLSB,iNES.PRGOsizeMSB)*16384;
    }
    {PRGrom.resize(PRGOsize);
    char buffer[PRGOsize];
    rom.read(buffer,PRGOsize);
    PRGrom.insert(PRGrom.begin(),&buffer[0],&buffer[512]);}

    long long CHROsize=0;
    if(iNES.CHROsizeMSB==0xF){
        int multi=iNES.CHROsizeLSB.gSmol(0,2)*2+1;
        CHROsize=(2 << iNES.CHROsizeLSB.gSmol(2,6))*multi;
    }else{
        CHROsize=combine8(iNES.CHROsizeLSB,iNES.CHROsizeMSB)*16384;
    }
    {CHRrom.resize(CHROsize);
    char buffer[CHROsize];
    rom.read(buffer,CHROsize);
    CHRrom.insert(CHRrom.begin(),&buffer[0],&buffer[512]);}

    if(iNES.misROMnumber>0){
        int loc=rom.tellg();
        rom.seekg(0,rom.end);
        int en=rom.tellg();
        rom.seekg(loc);
        int MISsiz=en-loc;
        MISrom.resize(MISsiz);
        char buffer[MISsiz];
        rom.read(buffer,MISsiz);
        MISrom.insert(MISrom.begin(),&buffer[0],&buffer[512]);

    }


}
