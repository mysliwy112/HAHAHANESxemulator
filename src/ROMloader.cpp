#include "ROMloader.h"
#include "ROM.h"

ROM *loader::load(char* path){
    ifstream file;
    file.open(path,ios::binary);
    if(!file.good()){
        cout<<"Can't load file: "<<path<<endl;
        file.close();
        return NULL;
    }
    char type[5];
    string chNES("NES\x1A");
    file.read(type,4);
    if(chNES.compare(type)==0){
        return loadNES(file);
    }else{
        cout<<"Unsupported file format: "<<type<<endl;
    }
    file.close();
    return NULL;
}

ROM *loader::loadNES(ifstream &file){

    iNESstruct iNES;

    Mem8 header[16];
    file.seekg(0, file.beg);
    file.read((char*)header, 16);

    bool NES2;
    if (gSmol(header[7],1,2)==2){
        NES2=true;
        cout<<"NES 2.0 format"<<endl;
        iNES.PRGOsizeLSB=header[4];
        iNES.CHROsizeLSB=header[5];
        iNES.mirroring=gBit(header[6],0);
        iNES.battery=gBit(header[6],1);
        iNES.trainer=gBit(header[6],2);
        iNES.fourScreen=gBit(header[6],3);
        iNES.mapperType=gSmol(header[6],4,4);

        iNES.consoleType=gSmol(header[7],0,2);
        iNES.mapperType+=gSmol(header[7],4,4)*0xF;

        iNES.mapperType+=gSmol(header[8],0,4)*0xFF;
        iNES.submapperType=gSmol(header[8],4,4);

        iNES.PRGOsizeMSB=gSmol(header[9],0,4);
        iNES.CHROsizeMSB=gSmol(header[9],4,4);

        iNES.PRGAsize=gSmol(header[10],0,4);
        iNES.EEPROMsize=gSmol(header[10],4,4);

        iNES.CHRAsize=gSmol(header[11],0,4);
        iNES.CHRNVAsize=gSmol(header[11],4,4);

        iNES.CPPmode=gSmol(header[12],0,2);

        if(iNES.consoleType==1){
            iNES.vsPPUtype=gSmol(header[13],0,4);
            iNES.vsHWtype=gSmol(header[13],4,4);
        }else if(iNES.consoleType==3){
            iNES.ExConsoleType=gSmol(header[13],0,4);
        }

        iNES.misROMnumber=gSmol(header[14],0,2);

        iNES.defExDevice=gSmol(header[15],0,6);
    }else{
        NES2=false;
        cout<<"iNES format"<<endl;
        iNES.PRGOsizeLSB=header[4];
        iNES.PRGOsizeMSB=0;
        iNES.CHROsizeLSB=header[5];
        iNES.CHROsizeMSB=0;

        iNES.mirroring=gBit(header[6],0);
        iNES.battery=gBit(header[6],1);
        iNES.trainer=gBit(header[6],2);
        iNES.fourScreen=gBit(header[6],3);
        iNES.mapperType=gSmol(header[6],4,4);

        iNES.consoleType=0;
        if(gBit(header[7],0))
            iNES.consoleType=1;
        else if(gBit(header[7],1)){
            iNES.consoleType=2;
        }
        iNES.mapperType+=gSmol(header[7],4,4)*0xF;

        iNES.PRGAsize=header[8];

        iNES.CPPmode=gBit(header[9],0);

        //ignore biatch
        //iNES.TVtype=gBit(header[10],0);
    }

    ROM *rom=mapper(iNES.mapperType);

    rom->iNES=iNES;

    if(iNES.trainer==1){
        cout<<"Watch out for trainer"<<endl;
        char buffer[512];
        rom->trainer.resize(512);
        file.read(buffer,512);
        rom->trainer.insert(rom->trainer.begin(),&buffer[0],&buffer[512]);
    }

    long long PRGOsize=0;
    if(iNES.PRGOsizeMSB==0xF){
        int multi=gSmol(iNES.PRGOsizeLSB,0,2)*2+1;
        PRGOsize=(2 << gSmol(iNES.PRGOsizeLSB,2,6))*multi;
    }else{
        PRGOsize=combine8(iNES.PRGOsizeLSB,iNES.PRGOsizeMSB)*16384;
    }
    {rom->PRGrom.resize(PRGOsize);
    char buffer[PRGOsize];
    file.read(buffer,PRGOsize);
    rom->PRGrom.insert(rom->PRGrom.begin(),&buffer[0],&buffer[512]);}

    long long CHROsize=0;
    if(iNES.CHROsizeMSB==0xF){
        int multi=gSmol(iNES.CHROsizeLSB,0,2)*2+1;
        CHROsize=(2 << gSmol(iNES.CHROsizeLSB,2,6))*multi;
    }else{
        CHROsize=combine8(iNES.CHROsizeLSB,iNES.CHROsizeMSB)*16384;
    }
    {rom->CHRrom.resize(CHROsize);
    char buffer[CHROsize];
    file.read(buffer,CHROsize);
    rom->CHRrom.insert(rom->CHRrom.begin(),&buffer[0],&buffer[512]);}

    if(iNES.misROMnumber>0){
        int loc=file.tellg();
        file.seekg(0,file.end);
        int en=file.tellg();
        file.seekg(loc);
        int MISsiz=en-loc;
        rom->MISrom.resize(MISsiz);
        char buffer[MISsiz];
        file.read(buffer,MISsiz);
        rom->MISrom.insert(rom->MISrom.begin(),&buffer[0],&buffer[512]);
    }
    return rom;
}

ROM *loader::mapper(int type){

    switch(type){
        case 0:{
            ROM *rom=new ROM;
            return rom;
        break;}
    }
    throw "Mapper type not found.";
}
