
#include <CPU.h>
#include <ROM.h>
#include <ROMloader.h>
using namespace std;

int main(int argc, char *argv[])
{
    cout<<sizeof(iNESstruct)<<endl;
    ROMloader loader;
    ROM *aa=loader.load("E:/nestopia/games/a.nes");

    CPU cp;
    cp.powerUp();
    delete aa;
    return 0;
}
