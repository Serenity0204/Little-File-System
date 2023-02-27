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
    ROOT = 0,
};


enum PARSE_KEY
{
    BACK=0,
    MKDIR=1,
    CD=2,
    TOUCH=3,
    LS = 4,
    RM=5,
    DEL=6,
    OPEN=7,
    SAVE=8,
};

// add more enum here



// windows
// ADD WINDOWS CONFIG VARIABLE HERE
const int WINDOW_HEIGHT = 650;
const int WINDOW_WIDTH = 1200;
const int INPUT_BOX_FONT_SIZE = 24;
const int CMD_FONT_SIZE = 20;
const int FILE_NAME_FONT_SIZE = 20;
const int HEADER_FONT_SIZE = 15;
const int TEXT_FILE_INPUT_FONT_SIZE = 20;
const int CHAR_LIMIT = 150;
const int TEXT_INPUT_LIMIT = 900;
const int CMD_CHAR_LIMIT = 105;
const int CHAR_DIVIDE = 12;
const int MAX_LEN_TERMINAL = 15;


// system variable config
// ADD SYSTEM  VARIABLE HERE
const sf::Vector2f TEXT_FILE_INPUT_SIZE = sf::Vector2f(700, 400);
const sf::Vector2f TEXT_FILE_INPUT_POS = sf::Vector2f(150, 150);

const sf::Vector2f FOLDER_TERMINAL_SIZE = sf::Vector2f(150, 500);
const sf::Vector2f FOLDER_TERMINAL_POS = sf::Vector2f(890, 0);

const sf::Vector2f FILE_TERMINAL_SIZE = sf::Vector2f(150, 500);
const sf::Vector2f FILE_TERMINAL_POS = sf::Vector2f(1045, 0);

const sf::Vector2f FILE_NAME_SIZE = sf::Vector2f(150, 35);
const sf::Vector2f FILE_NAME_POS = sf::Vector2f(150, 115);


const sf::Vector2f COMMAND_LINE_SIZE = sf::Vector2f(1150, 50);
const sf::Vector2f COMMAND_LINE_POS = sf::Vector2f(15, 580);

// global vars
const string BASE_DIR_STRING = "../../root/user/";
const unordered_map<string, vector<int>> LFS_CMD = {
    {"back", {BACK, 0}}, 
    {"touch", {TOUCH, 6}}, 
    {"mkdir", {MKDIR, 2}}, 
    {"cd", {CD, 2}}, 
    {"ls", {LS, 0}}, 
    {"rm", {RM, 2}}, 
    {"open", {OPEN, 2}},
    {"save", {SAVE, 0}},
    {"del", {DEL, 2}}
};


#endif