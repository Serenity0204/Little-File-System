#ifndef NARY_TREE_H
#define NARY_TREE_H


#include "../nary_tree_functions/nary_tree_functions.h"
#include "../nary_node/nary_node.h"
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;


class NaryTree
{
public:
    NaryTree();
    NaryTree(string data);
    ~NaryTree();
    friend std::ostream& operator << (std::ostream& outs, const NaryTree& print_me);
    void insert(shared_ptr<Node> parent, shared_ptr<Node> self);
    void set_root(shared_ptr<Node> root);
    string tree_string();
    shared_ptr<Node>& get_root(){return this->_root;}
private:
    shared_ptr<Node> _root;
};






    
#endif // !NARY_TREE_H