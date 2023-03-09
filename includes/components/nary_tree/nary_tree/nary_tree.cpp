#include "nary_tree.h"

NaryTree::NaryTree()
{
    this->_root = nullptr;
}

NaryTree::NaryTree(string data)
{
    this->_root = make_shared<Node>(data);
}
NaryTree::~NaryTree(){}

std::ostream& operator << (std::ostream& outs, const NaryTree& print_me)
{
    print_tree(print_me._root);
    return outs;
}

void NaryTree::insert(shared_ptr<Node> parent, string data)
{
    shared_ptr<Node> newNode = make_shared<Node>(data);
    parent->_children.push_back(newNode);
}

string NaryTree::tree_string()
{
    return tree_to_string(this->_root);
}
