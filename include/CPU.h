#ifndef CPU_H
#define CPU_H

#include<Module.h>

#include<ROM.h>

class ROM;
class Machine;

class CPU : public Module
{
/*    struct CPUmem{
        Mem8 memory[65536];
        Mem8& operator [] (short address){
            if(address<0x2000){ //zero page, stack, ram
                return memory[address%0x800];
            }else if(address<0x4018){//I/O
                return memory[(address-0x2000)%0x8+0x2000];
            }else if(address<0x4020){

            }
        }

    };*/

    enum flag{
        Carry,
        Zero,
        InterruptDis,
        Decimal,
        Break,
        Overflow=6,
        Negative
    };

    public:
        CPU();

        long long cycle=0;

        //modules

        //registers
            Mem16 PC; //Program Counter
            Mem8 SP; //Stack Pointer
            Mem8 A; //Accumulator
            Mem8 X; //Index Register
            Mem8 Y; //Index Register
            Mem8 P; //Processor Status (flags)

        vector<Mem8> memory;




        virtual void action();
        void powerUp();
        void reset();

        Mem8 read(int address);
        void write(int address, Mem8 value);

        void toPPU(int adress, Mem8 value);
        void toAPU(int adress, Mem8 value);
        void toIO(int adress, Mem8 value);

        Mem8 fromPPU(int adress);
        Mem8 fromAPU(int adress);
        Mem8 fromIO(int adress);

    protected:

        void instruction();

        void push(int value);
        Mem8 pull();

        void setNegative(Mem8 num){
            sBit(P,Negative,gBit(num,Negative));
        }

        void setZero(Mem8 num){
            sBit(P,Zero,!num);
        }

        //addressing modes
            int adrAccumulator(){
                cycle+=2;
                return 0x10001;
            }
            int adrImmediate(){
                cycle+=2;
                return PC++;
            }
            int adrZero(){
                cycle+=3;
                return read(PC++);
            }
            int adrZeroX(){
                cycle+=4;
                return (read(PC++)+X)%256;
            }
            int adrZeroY(){
                cycle+=4;
                return (read(PC++)+Y)%256;
            }
            int adrRelative(){
                //add cycle
                return static_cast<int>(read(PC++))+PC;
            }
            int adrAbsolute(){
                cycle+=4;
                return combine8(read(PC++),read(PC++));
            }
            int adrAbsoluteX(){
                cycle+=4;
                int address=combine8(read(PC++),read(PC++))+X;
                if(address>255){
                    cycle++;
                }
                return address;
            }
            int adrAbsoluteY(){
                cycle+=4;
                int address=combine8(read(PC++),read(PC++))+Y;
                if(address>255){
                    cycle++;
                }
                return address;
            }
            int adrIndirect(){
                cycle+=5;
                int address=combine8(read(PC++),read(PC++));
                return combine8(read(address),read(address+1));
            }
            int adrIndirectX(){
                cycle+=6;
                int address=PC+++X;
                address=combine8(read(address%256),read((address+1)%256));
                return address;
            }
            int adrIndirectY(){
                cycle+=5;
                int address=PC++;
                address=combine8(read(address),read((address+1)%256))+Y;
                if(address>255){
                    cycle++;
                }
                return address;
            }

        //special instructions
            void insNOP(){
                cycle+=2;
            }
};

#endif // CPU_H
