#ifndef HEADER_H
#define HEADER_H
#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>
using namespace std;


class Header
{
private:
    sf::RectangleShape _header;
    sf::Text _text;
    int _char_size;
public:
    Header();
    Header(std::string headerText, sf::Vector2f headerSize, sf::Vector2f headerPos, int charSize, sf::Color bgColor, sf::Color textColor);
    ~Header();
    string getHeaderText(){return this->_text.getString();}
    void setHeaderText(string text);
    void setHeaderFontSize(int size);
    int getHeaderFontSize(){return this->_char_size;}
    void setFont(sf::Font &fonts);
    void drawTo(sf::RenderWindow &window);
};

#endif