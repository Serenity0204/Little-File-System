#ifndef NARY_TREE_H
#define NARY_TREE_H


#include "../nary_tree_functions/nary_tree_functions.h"
#include "../nary_node/nary_node.h"
#include <unordered_map>
#include <iostream>
using namespace std;


class NaryTree
{
public:
    NaryTree();
    ~NaryTree();
    friend std::ostream& operator << (std::ostream& outs, const NaryTree& print_me);
private:
    int depth;
    Node _root;
};






    
#endif // !NARY_TREE_H