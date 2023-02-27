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

void CommandLine::reset()
{
    this->_fm.get_base_dir() = BASE_DIR_STRING;
    this->_parser.get_cur_dir() = BASE_DIR_STRING;
    this->_command_line.set_text(BASE_DIR_STRING);
}


int CommandLine::update_cmd_event(vector<string>& folder_str, vector<string>& file_str)
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
            cout << "Error in BACK, Cannot by pass the base dir" << endl;
            return INVALID;
        }
        string old_str = this->_fm.get_base_dir();
        int idx = 0;
        for(idx = old_str.length() - 2; idx >= 0; --idx) if(old_str[idx] == '/') break;
        string new_str = "";
        for(int i = 0; i <= idx; ++i) new_str += old_str[i];
        this->_fm.get_base_dir() = new_str;
        this->_parser.get_cur_dir() = new_str;
        this->_command_line.set_text(new_str);
        cout << "back" << endl;
        return BACK;
    }
    if(code == MKDIR)
    {
        if(this->_fm.folder_exist(subcmd)) return INVALID;
        bool success = this->_fm.add_folder(subcmd);  
        if(!success) return INVALID;
        this->_command_line.set_text(this->_fm.get_base_dir());
        cout << "mkdir" << endl;
        return MKDIR;
    }
    if(code == CD)
    {
        if(!this->_fm.folder_exist(subcmd)) return INVALID;
        this->_parser.get_cur_dir() += subcmd + "/";
        this->_fm.get_base_dir() += subcmd + "/";
        this->_command_line.set_text(this->_fm.get_base_dir());
        cout << "cd" << endl;
        return CD;
    }
    if(code == TOUCH)
    {
        if(this->_fm.file_exist(subcmd)) return INVALID;
        bool success = this->_fm.add_file(subcmd);  
        if(!success) return INVALID;
        this->_command_line.set_text(this->_fm.get_base_dir());
        cout << "touch" << endl;
        return TOUCH;
    }
    if(code == LS)
    {
        vector<string> sub_dir_folder;
        vector<string> sub_dir_file;
        sub_dir_folder.clear();
        sub_dir_file.clear();
        bool check = this->_fm.get_sub_dir(sub_dir_folder, sub_dir_file);
        if(!check) return INVALID;

        folder_str.clear();
        folder_str = sub_dir_folder;
        file_str.clear();
        file_str = sub_dir_file;

        if(folder_str.size() == 0) folder_str.push_back("");
        if(file_str.size() == 0) file_str.push_back("");
        this->_command_line.set_text(this->_fm.get_base_dir());
        cout << "ls" << endl;
        return LS;
    }
    if(code == RM)
    {
        if(!this->_fm.folder_exist(subcmd)) return INVALID;
        bool success = this->_fm.delete_folder(subcmd);
        if(!success) return INVALID;
        this->_command_line.set_text(this->_fm.get_base_dir());
        cout << "rm" << endl;
        return RM;
    }
    if(code == DEL)
    {
        if(!this->_fm.file_exist(subcmd)) return INVALID;
        bool success = this->_fm.delete_file(subcmd);
        if(!success) return INVALID;
        this->_command_line.set_text(this->_fm.get_base_dir());
        cout << "del" << endl;
        return DEL;
    }
    if(code == OPEN)
    {
        if(!this->_fm.file_exist(subcmd)) return INVALID;
        this->_fm.set_last_file_open(subcmd);
        middleware.load_file_name(subcmd);
        middleware.load_text_input(this->_fm.get_file_text(subcmd));
        this->_command_line.set_text(this->_fm.get_base_dir());
        cout << "open" << endl;
        return OPEN;
    }
    if(code == SAVE)
    {
        this->_command_line.set_text(this->_fm.get_base_dir());
        string last_file = this->_fm.get_last_file_open();
        // trying to save before open
        if(last_file.length() == 0) return INVALID;
        bool success = this->_fm.write_file(last_file);
        if(!success) return INVALID;
        cout << "save" << endl;
        return SAVE;
    }

    cout << "fail in event" << endl;
    return INVALID;
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