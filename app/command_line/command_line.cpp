#include "command_line.h"






CommandLine::CommandLine()
{
    this->_base_dir = this->_fm.get_base_dir();
    this->_cur_dir = this->_base_dir;
    
    this->_command_line = InputBox(CMD_FONT_SIZE, COMMAND_LINE_SIZE, COMMAND_LINE_POS, sf::Color::Red, sf::Color::Black, true, this->_base_dir,false);
    this->_command_line.setLimit(true, CMD_CHAR_LIMIT);
    
    this->_fm = FolderFileManager();
    this->_parser = CmdParser(this->_base_dir, "lfs");
    this->_parser.set_available_cmd(LFS_CMD);

}
CommandLine::~CommandLine(){}

bool CommandLine::update_cmd_event()
{
    string command_string = this->_command_line.getText();
    cout << "root:" << command_string << endl;
    string subcmd = "";
    int code = this->_parser.parse(command_string, subcmd);
    if(code == MKDIR)
    {
        cout << "mkdir" << endl;
        if(this->_fm.folder_exist(subcmd)) return false;
        bool success = this->_fm.add_folder(subcmd);  
        if(!success) return false;
        return true;
    }
    if(code == CD)
    {
        cout << "cd" << endl;
        if(!this->_fm.folder_exist(subcmd)) return false;
        
    }
    else
    {
        cout << "fail" << endl;
    }
    cout << "subcommand:" << subcmd << endl;
    return true;
}

void CommandLine::typed_cmd(sf::Event &input)
{
    this->_command_line.typedOn(input);
}
void CommandLine::update_cmd(sf::RenderWindow &window, sf::Event& event)
{
    this->_command_line.update_input_box(window, event);
}

void CommandLine::draw_cmd(sf::RenderWindow &window)
{
    this->_command_line.drawTo(window);
}