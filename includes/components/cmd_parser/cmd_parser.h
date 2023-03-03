#ifndef CMD_PARSER
#define CMD_PARSER

#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
#include "../../core/config/config.h"   
#include "../utils/helper_functions.h"
using namespace std;


class CmdParser
{
private:
    string _system_name;
    string _cur_dir;
    // index 0 is parse code, index 1 is length of needed substr
    unordered_map<string, vector<int>> _available_cmd;
public:
    CmdParser();
    CmdParser(string base_name, string system_name);
    ~CmdParser();
    string& get_cur_dir(){return this->_cur_dir;}
    void set_available_cmd(const unordered_map<string, vector<int>>& cmds);
    int parse(string cmd, string& subcmd);
};


    
#endif // !CMD_PARSER