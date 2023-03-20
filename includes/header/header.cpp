#include "header.h"

Header::Header(){}

Header::Header(std::string headerText, sf::Vector2f headerSize, sf::Vector2f headerPos, int charSize, sf::Color bgColor, sf::Color textColor)
{
	_header.setSize(headerSize);
	_header.setFillColor(bgColor);
    _header.setPosition(headerPos);
    _text.setPosition(headerPos);

	_text.setString(headerText);
	_text.setCharacterSize(charSize);
	_text.setFillColor(textColor);

	_char_size = charSize;
}

Header::~Header(){}

void Header::setFont(sf::Font &fonts)
{
    _text.setFont(fonts);
}

void Header::setHeaderFontSize(int size)
{
	_char_size = size;
	_text.setCharacterSize(size);
}
void Header::drawTo(sf::RenderWindow &window)
{
	window.draw(_header);
	window.draw(_text);
}

void Header::setHeaderText(string text)
{
	_text.setString(text);
}