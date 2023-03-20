#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <unistd.h>
#include "../text_file_tokenizer/info.h"





namespace Helper
{
    int first_not_space(string str, int startIdx);
    int first_space(string str, int startIdx);
    string remove_space(string str);
    bool is_in(vector<Info> info_vec, Info find);
    void count_string_dimension(const string& str, int& vertical, int& horizontal);
    bool dir_exists(const std::string &path);
};



#endif // !HELPER_FUNCTIONS_H