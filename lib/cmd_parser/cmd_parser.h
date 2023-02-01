#ifndef CMD_PARSER
#define CMD_PARSER
#include <bits/stdc++.h>
#include "../utils/helper_functions.h"
using namespace std;


class CmdParser
{
private:
    string _system_name;
    string _base_name;
    unordered_map<string, int> _available_cmd;
public:
    CmdParser();
    CmdParser(string base_name, string system_name);
    ~CmdParser();
    void set_available_cmd(const unordered_map<string, int>& cmds);
    bool parse(string cmd);
};


    
#endif // !CMD_PARSER