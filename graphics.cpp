#include <iostream>
#include "opcode.hpp"
#include <vector>
#include "regr.hpp"
#include "sys.hpp"
#include <sstream>
#include "sprite.hpp"
#include <SFML/Graphics.hpp>
#include <string>


void draw(const int x, const int y, const int n, std::vector<sf::RectangleShape>& sprite, std::vector<std::string>& bytes) {
    std::cout << "Bytes:\n";
    for (int i = 0; i < bytes.size(); ++i) {
        std::cout << "b[" << i << "] " << bytes[i] << "\n";
    }
    std::cout << "----\n";
    for (int row = 0; row < bytes.size(); ++row) {
        for (int col = 0; col < 8; ++col) {
            if (bytes[row].at(col) == '1') {
                sprite.push_back(sf::RectangleShape(sf::Vector2f(5, 5)));
                sprite[sprite.size() - 1].setPosition(x * 5 + 5 * col, y * 5 + 5 * row);
                sprite[sprite.size() - 1].setFillColor(sf::Color::White);
            }
        }
    }
}