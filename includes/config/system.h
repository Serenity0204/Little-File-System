#ifndef SYSTEM_H
#define SYSTEM_H
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;



enum FONTS
{
    // ADD MORE FONTS HERE
    ARIAL = 0,
};


// Action code for buttons go here
enum ACTION_CODE
{
    INVALID = -1,
    // add more action code for button here
    TEST = 0,
};


// add more enum here



// windows
// ADD WINDOWS CONFIG VARIABLE HERE
const int WINDOW_HEIGHT = 650;
const int WINDOW_WIDTH = 1200;
const int INPUT_BOX_FONT_SIZE = 24;
const int HEADER_FONT_SIZE = 35;
const int CHAR_LIMIT = 150;





// system variable config
// ADD SYSTEM  VARIABLE HERE
const sf::Vector2f INPUT_BOX_SIZE = sf::Vector2f(700, 120);
const sf::Vector2f INPUT_BOX_POS = sf::Vector2f(430, 500);
const sf::Vector2f HEADER_SIZE = sf::Vector2f(300, 50);
const sf::Vector2f HEADER_POS = sf::Vector2f(430, 200);





#endif