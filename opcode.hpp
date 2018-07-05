#ifndef OPCODE
#define OPCODE

#include <string>
#include "sys.hpp"
#include <vector>
#include "sprite.hpp"

class Regr;
class SDL_Surface;
namespace sf {class RenderWindow;}

class Opcode {
    friend void load(const std::string& prog,std::vector<Opcode>& memory);
    friend void exec(int& currAddr, Regr* V, std::vector<Opcode>& memory, Regr& I, sf::RenderWindow& window, std::vector<sf::RectangleShape> sprite);
    public:
        //Identify opcode type
        void parse();
        std::string getValue() const {return value;};
        std::string getType() const {return type;};
    private:
        std::string value = "NULL";
        std::string type = "";
        //Most significiant bit
        int msb = 0x0;
        //Bytes to draw
        int N = 0x0;
        //Number to use;
        int NN = 0x0;
        //Address
        int NNN = 0x0;
        //X register
        int X = 0x0;
        //Y register
        int Y = 0x0;
};

#endif