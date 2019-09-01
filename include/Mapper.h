#ifndef MAPPER_H
#define MAPPER_H

#include mo
class Mapper
{
    public:
        Mapper();

        virtual Mem8 readCPU(int address);
        virtual void writeCPU(int address, Mem8 value);

        virtual Mem8 readPPU(int address);
        virtual void writePPU(int address, Mem8 value);

    protected:

    private:
};

#endif // MAPPER_H
