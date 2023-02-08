#include "input_box.h"


InputBox::InputBox(){}

InputBox::InputBox(int font_size,sf::Vector2f box_size, sf::Vector2f position ,sf::Color text_color, sf::Color box_color, bool sel, string text_str, bool need_new_l) 
{
    isSelected = false;
	hasLimit = false;
    limit = 0;
    need_new_line = need_new_l;
    rect.setSize(box_size); 
    rect.setFillColor(box_color); 
    rect.setPosition(position); 
    textbox.setCharacterSize(font_size);
    textbox.setFillColor(text_color);
    textbox.setPosition(position);
    isSelected = sel;

    text = "";
    init_text_len = 0;
    set_text(text_str);
    // Check if the textbox is selected upon creation and display it accordingly:
    if(isSelected)
        textbox.setString(text + "|");
    else
        textbox.setString(text);
}



void InputBox::set_text(const string& str)
{
    text += str;
    init_text_len += str.length();
}

// Make sure font is passed by reference:
void InputBox::setFont(sf::Font &fonts) {
    textbox.setFont(fonts);
}

void InputBox::setPosition(sf::Vector2f point) {
    textbox.setPosition(point);
}

// Set char limits:
void InputBox::setLimit(bool ToF) {
    hasLimit = ToF;
}

void InputBox::setLimit(bool ToF, int lim) {
    hasLimit = ToF;
    limit = lim - 1;
}

// Change selected state:
void InputBox::setSelected(bool sel) {
    isSelected = sel;

    // If not selected, remove the '_' at the end:
    std::string newT = "";
    if (!sel) {
        std::string t = text;
        for (int i = 0; i < t.length(); i++) {
            newT += t[i];
        }
        textbox.setString(newT);
        return;
    }
}

std::string InputBox::getText() {
    return text;
}
void InputBox::drawTo(sf::RenderWindow &window) {

    window.draw(rect);
    window.draw(textbox);
}

// Function for event loop:
void InputBox::typedOn(sf::Event &input) {
    if (isSelected) {
        int charTyped = input.text.unicode;

        // Only allow normal inputs:
        if (charTyped < 128) {
            if (hasLimit) {
                // If there's a limit, don't go over it:
                if (text.length() <= limit) {
                    inputLogic(charTyped);
                }
                // But allow for char deletions:
                else if (text.length() > limit && charTyped == DELETE_KEY) {
                    deleteLastChar();
                }
                
            }
            // If no limit exists, just run the function:
            else {
                inputLogic(charTyped);
            }
        }
    }
}





// Delete the last character of the text:
void InputBox::deleteLastChar() {
    if(text.length() == init_text_len) return;
    std::string t = text;
    std::string newT = "";
    for (int i = 0; i < t.length() - 1; i++) {
        newT += t[i];
    }
    text = newT;
    textbox.setString(text + "|");
    //std::cout << text.str() << std::endl;
}

// Get user input:
void InputBox::inputLogic(int charTyped) {
    // If the key pressed isn't delete, or the two selection keys, then append the text with the char:
    if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
        text += static_cast<char>(charTyped);
        if(need_new_line && (text.length() + 1) % (int(rect.getSize().x / CHAR_DIVIDE)) == 0) text += '\n';
    }
    // If the key is delete, then delete the char:
    if (charTyped == DELETE_KEY) {
        if (text.length() > 0) {
            deleteLastChar();
        }
    }
    // Set the textbox text:
    string str = text + "|";
    textbox.setString(str);
    //std::cout << text.str() << std::endl;
}





void InputBox::update_input_box(sf::RenderWindow &window, sf::Event& event) {
	sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });

	sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

	float mouseX = realCoords.x;
	float mouseY = realCoords.y;

	int boxPosX = rect.getPosition().x;
	int boxPosY = rect.getPosition().y;

	int boxXPosWidth = rect.getPosition().x + rect.getGlobalBounds().width;
	int boxYPosHeight = rect.getPosition().y + rect.getGlobalBounds().height;

    bool clicked = event.type == sf::Event::MouseButtonPressed;
	if (mouseX < boxXPosWidth && mouseX > boxPosX && mouseY < boxYPosHeight && mouseY > boxPosY) {
		
        if(clicked)
        {
            this->setSelected(true);
            this->textbox.setString(this->getText() + "|");
            return;
        }
    }
    if(clicked || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->setSelected(false);
}