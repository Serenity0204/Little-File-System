#include "helper_functions.h"

int Helper::first_not_space(string str, int startIdx)
{
    // find the first index that's not space
    for(int i = startIdx; i < str.length(); ++i) if(str[i] != ' ') return i;
    return -1;
}

int Helper::first_space(string str, int startIdx)
{
    // find the first index that's space
    for(int i = startIdx; i < str.length(); ++i) if(str[i] == ' ') return i;
    return -1;
}


string Helper::remove_space(string str)
{
    string res = "";
    for(int i = 0; i < str.length(); ++i) if(str[i] != ' ') res += str[i];
    return res;
}

bool Helper::isIn(vector<Info> info_vec, Info find)
{
    for(int i = 0; i < info_vec.size(); ++i) if(info_vec[i] == find) return true;
    return false;
}