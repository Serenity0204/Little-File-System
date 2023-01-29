#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
using namespace std;


class InputBox {
public:
	InputBox();
	InputBox(int font_size,sf::Vector2f box_size, sf::Vector2f position ,sf::Color text_color, sf::Color box_color, bool sel, string text_str="");
	// Make sure font is passed by reference:
	void setFont(sf::Font &fonts);

	void setPosition(sf::Vector2f point);

	// Set char limits:
	void setLimit(bool ToF);

	void setLimit(bool ToF, int lim);

	// Change selected state:
	void setSelected(bool sel);

	std::string getText();

	sf::Text& get_text_box(){return this->textbox;}
	void drawTo(sf::RenderWindow &window);
	// Function for event loop:
	void typedOn(sf::Event &input);
	void set_text(const string& str){ this->text += str;}
	
	void update_input_box(sf::RenderWindow &window, sf::Event& event);	
private:
	sf::Text textbox;
	string text;
	int init_text_len;
	bool isSelected;
	bool hasLimit;
	int limit;
	sf::RectangleShape rect;

	// Delete the last character of the text:
	void deleteLastChar();

	// Get user input:
	void inputLogic(int charTyped);
};




#endif