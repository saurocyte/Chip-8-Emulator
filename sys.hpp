#ifndef SYS
#define SYS

#include <vector>
#include <string>
#include "sprite.hpp"

class Opcode;
class Regr;
namespace sf {class RenderWindow;}

//Read text
std::string readText();

//Load text into memory
void load(const std::string& prog, std::vector<Opcode>& memory);

//Execute opcode
void exec(int& currAddr, Regr* V, std::vector<Opcode>& memory, Regr& I, sf::RenderWindow& window, std::vector<sf::RectangleShape> sprite);

//Convert hex string to bit string
std::string convertByte(std::string str);

#endif