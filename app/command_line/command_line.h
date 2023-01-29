#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "../../includes/input_box/input_box.h"
#include "../../includes/config/config.h"
#include "../../lib/folder_file_manager/folder_file_manager.h"
using namespace std;


class CommandLine
{
private:
    InputBox _command_line;
    string _base_dir;
    FolderFileManager _fm;
public:
    CommandLine();
    ~CommandLine();

    void setFont(sf::Font &fonts){this->_command_line.setFont(fonts);}
	void typed_cmd(sf::Event &input);
	void update_cmd(sf::RenderWindow &window, sf::Event& event);	
    void draw_cmd(sf::RenderWindow &window);
};

#endif