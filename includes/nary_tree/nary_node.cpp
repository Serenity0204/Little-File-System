#include "nary_node.h"


Node::Node(string data, int level, string parent, vector<shared_ptr<Node>> children)
{
    this->_data = data;
    this->_level = level;
    this->_parent = parent;
    this->_children = children;
}

Node::~Node(){}

std::ostream& operator << (std::ostream& outs, const Node& print_me)
{
    outs << "data:" << print_me._data << endl;
    outs << "level:" << print_me._level << endl;
    outs << "parent:";
    if(print_me._parent.length() == 0) outs << "null" << endl;
    if(print_me._parent.length() != 0) outs << print_me._parent << endl;
    outs << "children:";
    if(print_me._children.size() == 0) outs << "No children" << endl;
    for(int i = 0; i < print_me._children.size(); ++i) outs << print_me._children[i] << " ";
    outs << endl;
    return outs;
}