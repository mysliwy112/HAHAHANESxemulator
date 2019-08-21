#ifndef MODULE_H
#define MODULE_H


class Module
{
    public:

        struct MyByte{

            unsigned char byt;

            //MyByte& operator=(MyByte& a) { return a; }
            MyByte& operator=(int a) {
                byt = a;
                return *this;
            }
            operator int(){
                return byt;
            }

            bool gBit(int i){
                return (byt >> i) & 0x1;
            }
            void sBit(int i,bool v){
                byt ^= (-v ^ byt) & (0x1 << i);
            }
        };

        Module();

    protected:

    private:
};

#endif // MODULE_H
