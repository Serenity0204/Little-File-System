#ifndef NARY_TREE_FUNCTIONS_H
#define NARY_TREE_FUNCTIONS_H
#include "../nary_node/nary_node.h"
using namespace std;


void print_subtree(shared_ptr<Node> node, int depth, bool lastChild);
void print_tree(shared_ptr<Node> root);
void print_subtree_str(shared_ptr<Node> node, int depth, bool lastChild, string& output);
string tree_to_string(shared_ptr<Node> root);

    
#endif // !NARY_TREE_FUNCTIONS_H