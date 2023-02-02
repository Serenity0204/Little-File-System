#ifndef CMD_PARSER
#define CMD_PARSER
#include <bits/stdc++.h>
#include "../../includes/config/config.h"   
#include "../utils/helper_functions.h"
using namespace std;


class CmdParser
{
private:
    string _system_name;
    string _base_name;
    // index 0 is parse code, index 1 is length of needed substr
    unordered_map<string, vector<int>> _available_cmd;
public:
    CmdParser();
    CmdParser(string base_name, string system_name);
    ~CmdParser();
    void set_available_cmd(const unordered_map<string, vector<int>>& cmds);
    int parse(string cmd);
};


    
#endif // !CMD_PARSER