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
    //cout << "root:" << command_string << endl;
    string subcmd = "";
    int code = this->_parser.parse(command_string, subcmd);
    //cout << "subcommand:" << subcmd << endl;
    if(code == BACK)
    {
        if(this->_fm.get_base_dir() == BASE_DIR_STRING) 
        {
            cout << "can't go back" << endl;
            return false;
        }
        string old_str = this->_fm.get_base_dir();
        int idx = 0;
        for(idx = old_str.length() - 2; idx >= 0; --idx) if(old_str[idx] == '/') break;
        string new_str = "";
        for(int i = 0; i <= idx; ++i) new_str += old_str[i];
        this->_fm.get_base_dir() = new_str;
        this->_parser.get_cur_dir() = new_str;
        this->_command_line.set_text(new_str);
        return true;
    }
    if(code == MKDIR)
    {
        cout << "mkdir" << endl;
        if(this->_fm.folder_exist(subcmd)) return false;
        bool success = this->_fm.add_folder(subcmd);  
        if(!success) return false;
        this->_command_line.set_text(this->_fm.get_base_dir());
        return true;
    }
    if(code == CD)
    {
        cout << "cd" << endl;
        if(!this->_fm.folder_exist(subcmd)) return false;
        this->_parser.get_cur_dir() += subcmd + "/";
        this->_fm.get_base_dir() += subcmd + "/";
        this->_command_line.set_text(this->_fm.get_base_dir());
        return true;
    }
    if(code == TOUCH)
    {
        if(this->_fm.file_exist(subcmd)) return false;
        bool success = this->_fm.add_file(subcmd);  
        if(!success) return false;
        this->_command_line.set_text(this->_fm.get_base_dir());
        return true;
    }
    if(code == LS)
    {
        vector<string> sub_dir;
        sub_dir.clear();
        bool check = this->_fm.get_sub_dir(sub_dir);
        if(!check) return false;
        for(int i = 0; i < sub_dir.size(); ++i) cout << sub_dir[i] << endl;
        if(sub_dir.size() == 0) cout << "Empty dir" << endl;
        cout << endl;
        this->_command_line.set_text(this->_fm.get_base_dir());
        return true;
    }
    if(code == RM)
    {
        if(!this->_fm.folder_exist(subcmd)) return false;
        bool success = this->_fm.delete_folder(subcmd);
        if(!success) return false;
        this->_command_line.set_text(this->_fm.get_base_dir());
        return true;
    }
    if(code == DEL)
    {
        if(!this->_fm.file_exist(subcmd)) return false;
        bool success = this->_fm.delete_file(subcmd);
        if(!success) return false;
        this->_command_line.set_text(this->_fm.get_base_dir());
        return true;
    }

    cout << "fail in event" << endl;
    return false;
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