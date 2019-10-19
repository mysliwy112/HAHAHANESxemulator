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
        int multi=iNES.PRGOsizeLSB.gSmol(0,2)*2+1;
        PRGOsize=(2 << iNES.PRGOsizeLSB.gSmol(2,6))*multi;
    }else{
        PRGOsize=combine8(iNES.PRGOsizeLSB,iNES.PRGOsizeMSB)*16384;
    }
    {rom->PRGrom.resize(PRGOsize);
    char buffer[PRGOsize];
    file.read(buffer,PRGOsize);
    rom->PRGrom.insert(rom->PRGrom.begin(),&buffer[0],&buffer[512]);}

    long long CHROsize=0;
    if(iNES.CHROsizeMSB==0xF){
        int multi=iNES.CHROsizeLSB.gSmol(0,2)*2+1;
        CHROsize=(2 << iNES.CHROsizeLSB.gSmol(2,6))*multi;
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

}
