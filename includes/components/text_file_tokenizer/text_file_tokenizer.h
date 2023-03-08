#ifndef TEXT_FILE_TOKENIZER_H
#define TEXT_FILE_TOKENIZER_H
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


// tokenize the text file delete_all_file.txt and delete_all_folder.txt
// read all the string and tokenize it into levels(by distinguishing /)
// ex: ../../root/user/c.txt -> root/user/c.txt -> lv:3
// ex ../../root/user/b/ -> root/user/b/ -> lv:3
// have to know level, parent, and self value
class TextFileTokenizer
{
private:
    vector<string> _cache;
    void read();
public:
    TextFileTokenizer();
    ~TextFileTokenizer();
    
};

    
#endif // TEXT_FILE_TOKENIZER_H