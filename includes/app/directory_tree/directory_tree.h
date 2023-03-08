#ifndef DIRECTORY_TREE_H
#define DIRECTORY_TREE_H
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
#include "../../components/nary_tree/nary_tree/nary_tree.h"
using namespace std;

class DirectoryTree
{
private:
    NaryTree _nary_tree;
public:
    DirectoryTree();
    ~DirectoryTree();
};




    
#endif // !DIRECTORY_TREE_H