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
    int endIdx = first_space(cmd, startIdx);
    //cout << "start:" << startIdx << " , end:" << endIdx << endl;


    // // if no command entered command string will be the entire slice from start idx to the end
    // if there's a command, check if it's in the command list
    string command = cmd.substr(startIdx, endIdx - startIdx);
    //cout << "command is:" << command << ",len:" << command.length() << endl;
    if(!this->_available_cmd.count(command)) return INVALID;


    // lfs rmdir ab 
    // [lfs, rmdir, ab]
    // [SYSTEM, COMMAND, SUBCOMMAND, FLAG]

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
    
    subcmd = remove_space(cmd.substr(endIdx));
    //cout << "subcommand:" << subcmd << endl;
    if((cmd.length() - cmd.substr(0, endIdx).length()) < this->_available_cmd[command][1]) return INVALID;

    int code = this->_available_cmd[command][0];
    return code;
}


