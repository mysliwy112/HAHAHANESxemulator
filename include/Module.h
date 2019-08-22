#ifndef MODULE_H
#define MODULE_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

using namespace std;

template<class T>
struct Mem
{
    Mem(){}
    Mem(T u):byt(u){}

    T byt;

    Mem& operator=(T a) {
        byt = a;
        return *this;
    }

    Mem& operator+=(T a) {
        byt+=a;
        return *this;
    }
    Mem& operator-=(T a) {
        byt-=a;
        return *this;
    }

    T& operator--(int) {
        T temp=byt--;
        return temp;
    }
    T& operator--() {
        return --byt;
    }
    T& operator++(int) {
        T temp=byt++;
        return temp;
    }
    T& operator++() {
        return ++byt;
    }

    operator T(){
        return byt;
    }

    bool gBit(int i){
        return (byt >> i) & 0x1;
    }
    void sBit(int i,bool v){
        byt ^= (-v ^ byt) & (0x1 << i);
    }
    T gSmol(int i, int siz){
        return (byt >> i) & (2^siz)-1;
    }
};

using Mem8=Mem<uint8_t>;
using Mem16=Mem<uint16_t>;
using Mem32=Mem<uint32_t>;
using Mem64=Mem<uint64_t>;


class Module
{
    public:


        long long cycle=0;
        virtual void action()=0;

        Module();

    protected:

    private:
};

#endif // MODULE_H
