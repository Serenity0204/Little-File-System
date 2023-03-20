#ifndef NARY_NODE_H
#define NARY_NODE_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// define the n-ary tree node structure
struct Node 
{
    string _data;
    int _level;
    string _parent;
    vector<shared_ptr<Node>> _children;
    Node(string data="", int level=0, string parent="", vector<shared_ptr<Node>> children={});
    ~Node();
    friend std::ostream& operator << (std::ostream& outs, const Node& print_me);
};

    
#endif // NARY_NODE_H