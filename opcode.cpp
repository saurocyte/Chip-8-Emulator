#include "opcode.hpp"
#include <string>
#include <cstdlib>
#include <iostream>
#include <cctype>

void Opcode::parse() {
    char c = value.at(1);
    //Convert character to numbers in base 16
    X = strtol(&c, nullptr, 16);
    c = value.at(2);
    Y = strtol(&c, nullptr, 16);
    c = value.at(3);
    N = strtol(&c, nullptr, 16);
    //Convert substrings to numbers in base 16
    NN = std::stol(value.substr(2, 3), nullptr, 16);
    NNN = std::stol(value.substr(1, 3), nullptr, 16);

    //...
    switch (toupper(value[0])) {
        case '0': {
            if (value[1] == '0' && value[3] == '0') {
                //00E0
                type = "00E0";
            } else if (value[1] == '0' && toupper(value[3]) == 'E') {
                //00EE
                type = "00EE";
            } else {
                //0NNN (not needed)
                type = "0NNN";
            }
            break;
        }
        case '1': {
            //1NNN
            type = "1NNN";
            break;
        }
        case '2': {
            //2NNN
            type = "2NNN";
            break;
        }
        case '3': {
            //3XNN
            type = "3XNN";
            break;
        }
        case '4': {
            //4XNN
            type = "4XNN";
            break;
        }
        case '5': {
            //5XN0
            type = "5XN0";
            break;
        }
        case '6': {
            //6XNN
            type = "6XNN";
            break;
        }
        case '7': {
            //7XNN
            type = "7XNN";
            break;
        }
        case '8': {
            //8XY0
            if (value[3] == '0') type = "8XY0";
            //8XY1
            if (value[3] == '1') type = "8XY1";
            //8XY2
            if (value[3] == '2') type = "8XY2";
            //8XY3
            if (value[3] == '3') type = "8XY3";
            //8XY4
            if (value[3] == '4') type = "8XY4";
            //8XY5
            if (value[3] == '5') type = "8XY5";
            //8XY6
            if (value[3] == '6') type = "8XY6";
            //8XY7
            if (value[3] == '7') type = "8XY7";
            //8XYE
            if (toupper(value[3]) == 'E') type = "8XYE";
            break;
        }
        case '9': {
            //9XY0
            type = "9XY0";
            break;
        }
        case 'A': {
            
            //ANNN
            type = "ANNN";
            break;
        }
        case 'B': {
            
            //BNNN
            type = "BNNN";
            break;
        }
        case 'C': {
            //CXNN
            type = "CXNN";
            break;
        }
        case 'D': {
            //DXYN
            type = "DXYN";
            break;
        }
        case 'E': {
            //EX9E
            if (toupper(value[3]) == 'E') type = "EX9E";
            //EXA1
            if (value[3] == '1') 
                type = "EXA1";
            break;
        }
        case 'F': {            
            //FX07
            if (value[3] == '7') type = "FX07";
            //FX0A
            if (value[3] == '7') type = "FX0A";
            //FX18
            if (value[3] == '7') type = "FX18";
            //FX1E
            if (value[3] == '7') type = "FX1E";
            //FX29
            if (value[3] == '7') type = "FX29";
            //FX33
            if (value[3] == '7') type = "FX33";
            //FX15
            if (value[2] == '1') type = "FX15";
            //FX55
            if (value[2] == '5') type = "FX55";
            //FX65
            if (value[2] == '1') type = "FX65";
            break;
        }
    }
}
