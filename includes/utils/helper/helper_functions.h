#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
#include "../../components/text_file_tokenizer/info.h"





namespace Helper
{
    int first_not_space(string str, int startIdx);
    int first_space(string str, int startIdx);
    string remove_space(string str);
    bool isIn(vector<Info> info_vec, Info find);
};



#endif // !HELPER_FUNCTIONS_H