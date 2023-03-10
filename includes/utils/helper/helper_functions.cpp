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

bool Helper::is_in(vector<Info> info_vec, Info find)
{
    for(int i = 0; i < info_vec.size(); ++i) if(info_vec[i] == find) return true;
    return false;
}

void Helper::count_string_dimension(const string& str, int& vertical, int& horizontal)
{
    horizontal = 0;
    vertical = 0;
    int count = 0;
    for(int i = 0; i < str.length(); ++i)
    {
        if(str[i] == '\n') 
        {
            horizontal = max(horizontal, count);
            vertical++;
            count = 0;
            continue;
        }
        count++;
    }
}

bool Helper::dir_exists(const std::string &path) 
{
    struct stat info;
    if (stat(path.c_str(), &info) == 0 && info.st_mode & S_IFDIR) {
        return true;
    }
    return false;
}