#ifndef IO_H
#define IO_H

#include"Module.h"

class IO : public Module
{
    public:
        IO();
        virtual void OUTsignal(bool out);
        virtual void read(Mem8 in);
        virtual Mem8 write();
        virtual void readReal(vector<int> input);

    protected:

    private:
};

#endif // IO_H
