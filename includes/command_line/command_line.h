#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../input_box/input_box.h"
#include "../config/config.h"
#include "../folder_file_manager/folder_file_manager.h"
#include "../cmd_parser/cmd_parser.h"
#include "../middleware/middleware.h"
using namespace std;

//class FolderFileManager;

class CommandLine
{
private:
    InputBox _command_line;
    string _base_dir;
    FolderFileManager _fm;
    CmdParser _parser;
    bool _open;
public:
    CommandLine();
    ~CommandLine();

    void setFont(sf::Font &fonts){this->_command_line.setFont(fonts);}
	void typed_cmd(sf::Event &input);
	void update_cmd(sf::RenderWindow &window, sf::Event& event);	
    int update_cmd_event(vector<string>& folder_str, vector<string>& file_str);
    void draw_cmd(sf::RenderWindow &window);
    void reset();
};

#endif