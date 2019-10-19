#ifndef STANDARDCONTROLLER_H
#define STANDARDCONTROLLER_H

#include "IO.h"

class StandardController: public IO
{
    public:
        enum buttons{
            A,B,Select,Start,Up,Down,Left,Right
        };
        StandardController();

        int button;
        Mem8 buttState;
        const static int maxButt=8;

        virtual void OUTsignal(bool out);
        virtual Mem8 write();
        virtual void readReal(vector<int> input);

    protected:

    private:
};

#endif // STANDARDCONTROLLER_H
