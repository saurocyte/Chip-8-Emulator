#include "regr.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

void Regr::store(int val) {
    value = val;
}

int Regr::add(int val, Regr& F) {
    value += val;
    //Overflow detection
    if (value > 0xFF) {
        F.value = 1;
        value -= 256;
    }
    return value;
}

int Regr::sub(int val, Regr& F) {
    value -= val;
    //Overflow detection
    if (value < 0x0) {
        F.value = 1;
        value = 0;
    }
    return value;
}

int Regr::bAnd(int val) {
    value = value & val;
    return value;
}

int Regr::bOr(int val) {
    value = value | val;
    return value;
}

int Regr::bXor(int val) {
    value = value ^ val;
    return value;
}

int Regr::bRShift(int val, Regr& F) {
    //Shifting bits so only desired one remains remains
    F.value = val << 7;
    value = val >> 1;
    return value;
}

int Regr::bLShift(int val, Regr& F) {
    F.value = val >> 7;
    value = value << 1;
    return value;
}

int Regr::random(int m) {
    int randVal = rand() % 255;
    int masked = randVal & m;
    value = masked;
    std::cout << "Rand num: " << randVal << "\n";
    std::cout << "Masked: " << masked << "\n";
    return masked;
}