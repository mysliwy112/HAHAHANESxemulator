#ifndef ROMLOADER_H
#define ROMLOADER_H

#include<fstream>

using namespace std;

class ROM;
namespace loader
{
    ROM *load(char* path);
    ROM *loadNES(ifstream &file);
    ROM *mapper(int type);
};

#endif // ROMLOADER_H
