#include "nary_tree.h"

NaryTree::NaryTree()
{
    this->_root = nullptr;
}

void NaryTree::set_root(shared_ptr<Node> root)
{
    this->_root = root;
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

void NaryTree::insert(shared_ptr<Node> parent, shared_ptr<Node> self)
{
    self->_parent = parent->_data;
    self->_level = parent->_level + 1;
    parent->_children.push_back(self);
}

string NaryTree::tree_string()
{
    return tree_to_string(this->_root);
}
