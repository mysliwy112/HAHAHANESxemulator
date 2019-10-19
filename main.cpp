#include "Machine.h"
#include "ROMloader.h"

using namespace std;

struct components{

};


int main(int argc, char *argv[])
{
    ROM *rom;
    rom=loader::load(argv[1]);

    Machine nesser;
    nesser.insertROM(rom);

    return 0;
}
