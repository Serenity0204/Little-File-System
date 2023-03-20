#ifndef DIRECTORY_TREE_H
#define DIRECTORY_TREE_H
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
#include "../nary_tree/nary_tree.h"
#include "../text_file_tokenizer/text_file_tokenizer.h"
using namespace std;

class DirectoryTree
{
private:
    TextFileTokenizer _tk;
    NaryTree _nary_tree;
    vector<shared_ptr<Node>> _cache;
    string _str_representation;
    // helper functions
    shared_ptr<Node> _find_parent(int level, string parent);
public:
    DirectoryTree();
    ~DirectoryTree();
    void build();
    string get_directory_tree_string(){return this->_str_representation;}
    friend std::ostream& operator << (std::ostream& outs, const DirectoryTree& print_me);
};




    
#endif // !DIRECTORY_TREE_H