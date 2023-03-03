#ifndef BUTTONS_H
#define BUTTONS_H

#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
#include "../config/config.h"
#include "button.h"
#include <SFML/Graphics.hpp>



class Buttons
{
private:
    vector<Button> _buttons;
    void _init_buttons();
public:
    Buttons();
    ~Buttons();
    int update_buttons(sf::RenderWindow &window, sf::Event& event);
    void draw_buttons(sf::RenderWindow &window);
};

#endif // !BUTTONS_H