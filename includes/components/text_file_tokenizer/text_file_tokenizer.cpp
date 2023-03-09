#include "text_file_tokenizer.h"



TextFileTokenizer::TextFileTokenizer()
{
    this->_cache_file = vector<string>();
    this->_cache_folder = vector<string>();
    this->_infos = vector<Info>();
    this->_read();
    this->tokenize();
}

TextFileTokenizer::~TextFileTokenizer()
{

}

void TextFileTokenizer::_read()
{
    this->_cache_file.clear();
    this->_cache_folder.clear();

    string line;
    ifstream ins;
    ins.open("../../root/delete_all_file.txt");
    if(ins.fail()) return;
    while(getline(ins, line)) 
    {
        line = line.substr(6, line.length());
        line += "/";
        this->_cache_file.push_back(line);
    }
    ins.close();
    ins.open("../../root/delete_all_folder.txt");
    if(ins.fail()) return;
    while(getline(ins, line)) 
    {
        line = line.substr(6, line.length());
        this->_cache_folder.push_back(line);
    }


    cout << "read:" << endl;
    for(int i = 0; i < this->_cache_file.size(); ++i) cout << this->_cache_file[i] << endl;
    for(int i = 0; i < this->_cache_folder.size(); ++i) cout << this->_cache_folder[i] << endl;
    cout << "end read" << endl << endl;


    ins.close();
}

void TextFileTokenizer::_tokenize_helper(bool file_or_folder, int idx)
{
    int level = 0;
    string parent = "null";
    string concat = "";
    string input_str = (file_or_folder) ? this->_cache_file[idx] : this->_cache_folder[idx];
    for(int j = 0; j < input_str.length(); ++j)
    {
        if(input_str[j] == '/')
        {
            Info info(parent, concat, level);
            if(!Helper::isIn(this->_infos, info)) this->_infos.push_back(info);
            level++;
            parent = concat;
            concat = "";
            continue;
        }
        concat += input_str[j];
    }
}


void TextFileTokenizer::tokenize()
{
    this->_infos.clear();
    for(int i = 0; i < this->_cache_folder.size(); ++i) this->_tokenize_helper(false, i);
    for(int i = 0; i < this->_cache_file.size(); ++i) this->_tokenize_helper(true, i);

    for(int i = 0; i < this->_infos.size(); ++i) cout << this->_infos[i] << endl;
    
}