#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "../config/config.h"
#include "../input_box/input_box.h"
#include "../button/buttons.h"
#include "../header/header.h"
#include "../../app/command_line/command_line.h"
#include "../../utils/middleware/middleware.h"
#include "../../app/directory_tree/directory_tree.h"
using namespace std;



class Engine 
{
private:
    // sfml private members here
    sf::RenderWindow _window;

    // system setup here
    Buttons _buttons;

    Header _folder_terminal;
    Header _file_terminal;
    Header _file_name;
    Header _dir_tree_screen;

    InputBox _text_file_input;

    CommandLine _cmd;
    DirectoryTree _directory_tree;
    // private member variables here
    bool _text_file_input_on;
    bool _is_selected;

    // private helper functions here
    // init
    void _init();
    // update
    void _update_buttons_event(sf::Event& event);
    void _update_keyboard_event();
    void _update_terminal_event();
public:
    // friend class
    friend class Middleware;
    // constructors and destructors
    Engine();
    ~Engine();
    // game processing
    void input();
    void run();
    void display();
};




#endif