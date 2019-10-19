#include "StandardController.h"

StandardController::StandardController()
{
    button=0;
    buttState=0;
}

void StandardController::OUTsignal(bool out)
{
    if(out==1){
        button=0;
    }
}

Mem8 StandardController::write()
{
    return buttState.gBit(button);

}

void StandardController::readReal(vector<int> input)
{
    for(int i=0;i++;i<maxButt)
        buttState.sBit(i,input[i]);
}
