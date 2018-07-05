#include <string>
#include <vector>
#include <sstream>
#include <bitset>
#include <iostream>
#include "sys.hpp"
#include "opcode.hpp"
#include "regr.hpp"
#include "sprite.hpp"
#include "graphics.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>

std::string convertByte(std::string str) {
    std::stringstream ss;
    ss << std::hex << str;
    int num;
    ss >> num;
    std::bitset<8> b(num);
    return b.to_string();
}

std::string readText() {
    std::string prog = "";
    std::string currLine = "";
    std::cout << "reading file...\n";
    while (std::getline(std::cin, currLine)) {
        prog += (" " + currLine);
    }
    std::cout << "done!\nstored string: " << prog << "n";
    return prog;
}

void load(const std::string& prog, std::vector<Opcode>& memory) {
    Opcode currOpcode;
    Opcode nullOpcode;
    currOpcode.value = "";
    int len = prog.length();
    char c = '0';
    std::cout << "Programm length: " << len << "\n";
    std::cout << "Storing opcodes... \n";
    for (int i = 0; i < len; ++i) {
        c = prog[i];
        if (!isspace(c)) {
            currOpcode.value += c;
        //If space 
        } else {
            memory.push_back(nullOpcode);
            memory.push_back(currOpcode);
            std::cout << currOpcode.getValue() << " ";
            currOpcode.value = "";
        }
        //If last character
        if (i == len - 1) {
            memory.push_back(nullOpcode);
            memory.push_back(currOpcode);
            std::cout << currOpcode.getValue() << "\n";
            std::cout << "i: " << i << "\n";
        }
    }
    std::cout << "done!\n";
}

void exec(int& currAddr, Regr* V, std::vector<Opcode>& memory, Regr& I, sf::RenderWindow& window, std::vector<sf::RectangleShape> sprite) {
    Opcode opcode = memory[currAddr];

    //Using static = bad?
    static int prevAddr = 0;

    opcode.parse();

    int X = opcode.X;
    int Y = opcode.Y;
    int N = opcode.N;
    int NN = opcode.NN;
    int NNN = opcode.NNN;

    std::cout << "===\n";
    std::cout << "Executing opcode " << opcode.value << " - " << opcode.type << "\n"
         << "X: " << opcode.X << "\n"
         << "Y: " << opcode.Y << "\n"
         << "N: " << opcode.N << "\n"
         << "NN: " << opcode.NN << "\n"
         << "NNN: " << opcode.NNN << "\n";

    if (opcode.type == "6XNN") {
        V[X].store(NN);
    }
    if (opcode.type == "8XY0") {
        V[Y].store(V[X].getValue());
    }
    if (opcode.type == "7XNN") {
        V[X].add(NN, V[0xF]);
    }
    if (opcode.type == "8XY4") {
        V[X].add(V[Y].getValue(), V[0xF]);
    }
    if (opcode.type == "8XY5") {
        V[X].sub(V[Y].getValue(), V[0xF]);
    }
    if (opcode.type == "8XY7") {
        V[X].store(V[Y].sub(V[X].getValue(), V[0xF]));
    }
    if (opcode.type == "8XY2") {
        V[X].bAnd(V[Y].getValue());
    }
    if (opcode.type == "8XY1") {
        V[X].bOr(V[Y].getValue());
    }
    if (opcode.type == "8XY3") {
        V[X].bXor(V[Y].getValue());
    }
    if (opcode.type == "8XY6") {
        V[X].store(V[X].bRShift(V[Y].getValue(), V[0xF]));
    }
    if (opcode.type == "8XYE") {
        V[X].store(V[X].bLShift(V[Y].getValue(), V[0xF]));
    }
    if (opcode.type == "CXNN") {
        V[X].random(NNN);
    }
    if (opcode.type == "1NNN") {
        //-1 because for immediately increments currAddr
        currAddr = NNN - 2;
    }
    if (opcode.type == "BNNN") {
        currAddr = NNN + V[0].getValue() - 1;
    }
    if (opcode.type == "ANNN") {
        I.setValue(NNN);
    }
    if (opcode.type == "2NNN") {
        prevAddr = currAddr;
        currAddr = NNN;
    }
    if (opcode.type == "00EE") {
        currAddr = prevAddr;
    }
    if (opcode.type == "FX65") {
        std::cout << "here";
        std::string mem = "";
        for (int i = 0; i < X; ++i) {
            //Store value of opcode located at address I into V[i]
            mem = memory[I.getValue()].getValue();
            std::cout << "mem";
            V[i].store(std::stoi(mem, nullptr, 16));
            I.incr();
        }
    }
    if (opcode.type == "3XNN") {
        if (V[X].getValue() == NN) {
            currAddr += 2;
        }
    }
    if (opcode.type == "4XNN") {
        if (V[X].getValue() != NN) {
            ++currAddr;
        }
    }
    if (opcode.type == "FX33") {
        memory[I.getValue()].value = V[X].getValue() / 100 % 10;
        I.incr();
        memory[I.getValue()].value = V[X].getValue() / 10 % 10;
        I.incr();
        memory[I.getValue()].value = V[X].getValue() % 10;
        I.incr();
    }
    if (opcode.type == "00E0") {
        window.clear(sf::Color::Black);
        window.display();
    }
    if (opcode.type == "DXYN") {
        std::vector<std::string> bytes;
        //Two bytes are stored at address i
        std::string b1 = "";
        std::string b2 = "";
        std::string memString1 = "";
        std::string memString2 = "";
        for (int i = 0; i < N; i += 2) {
            memString1 = memory[I.getValue() + i].getValue().substr(0, 2);
            b1 = convertByte(memString1);
            bytes.push_back(b1);
            //Store second byte if required
            if (N % 2 == 0)
                memString2 = memory[I.getValue() + i].getValue().substr(2, 2);
                b2 = convertByte(memString2);
                bytes.push_back(b2);
        }
        draw(V[X].getValue(), V[Y].getValue(), N, sprite, bytes);
        for (int row = 0; row < sprite.size(); ++row) {
            window.draw(sprite[row]);
        }
        window.display();
        sprite.clear();
        //DOESN'T WORK WITHOUT SLEEP
        usleep(1000);
    }
    std::cout << "V[0] value: " << V[0].getValue() << "\n";
    std::cout << "V[X] value: " << V[X].getValue() << "\n";
}
