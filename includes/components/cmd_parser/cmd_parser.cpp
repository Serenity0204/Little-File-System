#include "cmd_parser.h"


CmdParser::CmdParser(){}

CmdParser::CmdParser(string base_name, string system_name)
{
    this->_cur_dir = base_name;
    this->_system_name = system_name;
}

CmdParser::~CmdParser(){}

void CmdParser::set_available_cmd(const unordered_map<string, vector<int>>& cmds)
{
    this->_available_cmd = cmds;
}



int CmdParser::parse(string cmd, string& subcmd)
{
    subcmd = "";
    // command is not legal
    int legal_length = this->_cur_dir.length() + this->_system_name.length();
    if(cmd.length() <= legal_length) return INVALID;
    // check if the command is called with system name
;
    string cmd_name = cmd.substr(this->_cur_dir.length(), this->_system_name.length());
    //cout << "cmd name: " << cmd_name << endl;
    if(cmd_name != this->_system_name) return INVALID;

    if(cmd[legal_length] != ' ') return INVALID;
    int startIdx = legal_length + 1;
    int endIdx = Helper::first_space(cmd, startIdx);
    //cout << "start:" << startIdx << " , end:" << endIdx << endl;


    // // if no command entered command string will be the entire slice from start idx to the end
    // if there's a command, check if it's in the command list
    string command = cmd.substr(startIdx, endIdx - startIdx);
    //cout << "command is:" << command << ",len:" << command.length() << endl;
    if(!this->_available_cmd.count(command)) return INVALID;

    // back->0
    // mkdir -> 1 + 1 not space == 2
    // cd -> 1 + 1 not space == 2
    // ls->0 
    // touch -> 1 + 1 not space == 2
    // rm->0

    // if endIdx == -1 means there's no subcommand entered, the command
    // is already validated because of above count, and this is a command that does not need subcommand
    if(endIdx == -1 && this->_available_cmd[command][1] == 0)
    {
        int code = this->_available_cmd[command][0];
        return code;
    }
    // if endIdx == -1 and it needs subcommand it's false, or if endIdx != -1 and it doesn't need subcommand it's false as well
    if((endIdx == -1 && this->_available_cmd[command][1] != 0) || (endIdx != -1 && this->_available_cmd[command][1] == 0)) return INVALID;
    
    string prepared_subcmd = Helper::remove_space(cmd.substr(endIdx));
    
    if((cmd.length() - cmd.substr(0, endIdx).length()) < this->_available_cmd[command][1]) return INVALID;
    //if(prepared_subcmd.length() > MAX_LEN_TERMINAL) return INVALID;
    
    // checking if the subcmd includes the required file format .txt
    if(command == "touch")
    {
        string txt = "";
        for(int i = prepared_subcmd.length() - 4; i < prepared_subcmd.length(); ++i) txt += prepared_subcmd[i];
        if(txt != ".txt") return INVALID;
    }

    // check if the folder name is legal(no .)
    if(command == "mkdir") 
    {
        // only A-Z, a-z, 0-9, and _ allowed
        for(int i = 0; i < prepared_subcmd.length(); ++i) 
        {
            if(prepared_subcmd[i] <= 90 && prepared_subcmd[i] >= 65) continue;
            if(prepared_subcmd[i] <= 122 && prepared_subcmd[i] >= 97) continue; 
            if(prepared_subcmd[i] <= 57 && prepared_subcmd[i] >= 48) continue;
            if(prepared_subcmd[i] == '_') continue;
            return INVALID;
        }
    }
    subcmd = prepared_subcmd;
    //cout << "subcommand:" << subcmd << endl;
    int code = this->_available_cmd[command][0];
    return code;
}


