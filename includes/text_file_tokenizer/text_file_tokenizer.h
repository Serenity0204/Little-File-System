#ifndef TEXT_FILE_TOKENIZER_H
#define TEXT_FILE_TOKENIZER_H
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "info.h"
#include "../helper/helper_functions.h"
using namespace std;


// tokenize the text file delete_all_file.txt and delete_all_folder.txt
// read all the string and tokenize it into levels(by distinguishing /)
// ex: ../../root/user/c.txt -> root/user/c.txt -> lv:3
// ex ../../root/user/b/ -> root/user/b/ -> lv:3
// have to know level, parent, and self value
class TextFileTokenizer
{
private:
    vector<string> _cache_folder;
    vector<string> _cache_file;
    vector<Info> _infos;
    void _read();

    void _tokenize_helper(bool file_or_folder, int idx);
public:
    TextFileTokenizer();
    ~TextFileTokenizer();
    void tokenize();
    vector<Info>& get_infos(){return this->_infos;}
};

    
#endif // TEXT_FILE_TOKENIZER_H