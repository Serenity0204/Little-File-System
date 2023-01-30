#include "cmd_parser.h"


CmdParser::CmdParser(){}

CmdParser::CmdParser(int ignored_base, string system_name)
{
    this->ignored_base = ignored_base;
    this->_system_name = system_name;
}

CmdParser::~CmdParser()
{

}

void CmdParser::set_available_cmd(const unordered_map<string, int>& cmds)
{
    this->_available_cmd = cmds;
}



bool CmdParser::parse(string cmd)
{
    // command is not legal
    int legal_length = this->ignored_base + this->_system_name.length();
    if(cmd.length() <= legal_length) return false;
    if(cmd[legal_length] != ' ') return false;
    int startIdx = legal_length + 1;
    int endIdx = first_not_space(cmd, startIdx);
    // if no command entered
    if(endIdx == -1) return false;

    // if there's a command, check if it's in the command list
    string command = cmd.substr(startIdx, endIdx);
    if(!this->_available_cmd.count(command)) return false;

    // if it's a legal command, then check the required context string length for the command

    // cd ..-> 1 + 2
    // mkdir -> 1 + 1 not space
    // cd -> 1 + 1 not space
    // ls->0 
    // touch -> 1 + 1 not space
    // rm->0

    // if too short it's false
    if((cmd.length() - cmd.substr(0, endIdx).length()) < this->_available_cmd[command]) return false;
    return true;
}


