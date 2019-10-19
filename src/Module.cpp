#include "Module.h"

Module::Module(){}

short combine8(uint8_t a, uint8_t b){
    return (int(b) << 8) | a;
}

