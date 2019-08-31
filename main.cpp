
#include <CPU.h>
#include <ROM.h>
using namespace std;

int main()
{
    cout<<sizeof(iNESstruct)<<endl;
    ROM aa;

    CPU cp;
    cp.powerUp();
    return 0;
}
