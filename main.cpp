#include <iostream>
#include "sys.hpp"
#include "opcode.hpp"
#include "regr.hpp"
#include <string>
#include <vector>
#include "graphics.hpp"
#include "sprite.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>

using namespace std;
//TBD: Do not look at spriting stuff
//     Event and main loops. Maybe separate drawing opcodes from the rest?
//     SFML doesn't draw stuff correctly without delay?
int main(int argc, char *argv[]) {
    Regr V[16];
    Regr I;
    Opcode nullOpcode;
    vector<Opcode> memory;
    vector<sf::RectangleShape> sprite;
    //Fill first 200 addresses
    for (int i = 0; i < 0x1ff; ++i) {
        memory.push_back(nullOpcode);
    }
    //Load programm into memory
    std::string prog = "6000 6100 a222 c201 3201 a21e d014 7004 3040 1204 6000 7104 3120 1204 121c 8040 2010 2040 8010z";
    //std::string prog = "00E0 A204 D002 1200 101F";
    load(prog, memory);
    int len = memory.size();
    cout << "Memory size: " << len << "\n";

    //Initialize window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chip8Emu");
    window.clear(sf::Color::Black);
    window.display();

    sf::Event event;

    int currAddr = 0x200;

    srand(time(NULL));
    
    int i = 0;

    //Main loop
    while (window.isOpen() || currAddr < len) {
        //Check event 
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                cout << "---WINDOW CLOSED---";
                window.close();
            }
        }
        //If address if valid
        if (currAddr < len) {
            exec(currAddr, V, memory, I, window, sprite);
        } else {
            cout << "Invalid address!";
        }
        cout << "V[A] value:  " << V[0xA].getValue() << "\n"
             << "V[3] value:  " << V[3].getValue() << "\n"
             << "V[F] value:  " << V[0xF].getValue() << "\n"
             << "I value:     " << I.getValue() << "\n"
             << "currentAddr: " << currAddr << "\n";
        currAddr += 2;
    }
    return 0;
}
