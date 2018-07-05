#ifndef GRAPHICS
#define GRAPHICS

#include <vector>
#include <string>

class Sprite;
namespace sf {class RectangleShape;}

void draw(const int x, const int y, const int n, std::vector<sf::RectangleShape>& sprite, std::vector<std::string>& bytes);

#endif