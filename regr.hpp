#ifndef REGR
#define REGR

#include <vector>
#include <string>

class Opcode;

class Regr {
    public:
        void store(int val);
        int add(int val, Regr& F);
        int sub(int val, Regr& F);
        int bAnd(int val);
        int bOr(int val);
        int bXor(int val);
        int bRShift(int val, Regr& F);
        int bLShift(int val, Regr& F);
        int getValue() const {return value;}; 
        int random(int m);
        void setValue(int val) {value = val;};
        void incr() {++value;}
    private:
        int value = 0x0;
};

#endif