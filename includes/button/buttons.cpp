#include "buttons.h"




Buttons::Buttons()
{
    this->_buttons = vector<Button>();   
    this->_init_buttons();
}

Buttons::~Buttons(){}


// init buttons used in this project
void Buttons::_init_buttons()
{
    // example

    Button hit_btn("TEST", {150, 50}, 25, sf::Color::White, sf::Color::Red);
    hit_btn.setFont(config.get_font(ARIAL));
    hit_btn.setPosition({500, 300});
    this->_buttons.push_back(hit_btn);
}


// return action code 
int Buttons::update_buttons(sf::RenderWindow &window, sf::Event& event)
{
    for(int i = 0; i < this->_buttons.size(); ++i)
    {
        if(this->_buttons[i].isMouseOver(window))
        {
            this->_buttons[i].setBackColor(sf::Color::Yellow);
            continue;
        }
        this->_buttons[i].setBackColor(sf::Color::White);
    }
    for(int i = 0; i < this->_buttons.size(); ++i)
    {
        bool clicked = this->_buttons[i].isMouseOver(window) && event.type == sf::Event::MouseButtonPressed;
        // if(clicked && i == ACTION CODE DEFINED IN SYSTEM) return ACTION CODE DEFINED IN SYSTEM;
        // ex:
        if(clicked && i == TEST) return TEST;
    }
    return INVALID;
}

void Buttons::draw_buttons(sf::RenderWindow &window)
{
    for(int i = 0; i < this->_buttons.size(); ++i)
    {
        this->_buttons[i].setFont(config.get_font(ARIAL));
        this->_buttons[i].drawTo(window);
    }
}