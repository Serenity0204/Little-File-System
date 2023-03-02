#ifndef NARY_NODE_H
#define NARY_NODE_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// define the n-ary tree node structure
struct Node {
    string _data;
    vector<shared_ptr<Node>> _children;
    Node(string data="", vector<shared_ptr<Node>> children={});
    ~Node();
};

    
#endif // NARY_NODE_H