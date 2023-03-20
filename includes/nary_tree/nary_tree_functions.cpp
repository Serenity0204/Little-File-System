#include "nary_tree_functions.h"




// function to print the subtree rooted at a node
void print_subtree(shared_ptr<Node> node, int depth, bool lastChild) {
    // print the node's data with appropriate indentation and prefix
    for (int i = 0; i < depth - 1; i++) {
        cout << "    ";
    }
    cout << (lastChild ? "|___" : "|---");
    cout << node->_data << endl;

    // recursively print each child node
    for (int i = 0; i < node->_children.size(); i++) {
        bool isLastChild = (i == node->_children.size() - 1);
        print_subtree(node->_children[i], depth + 1, isLastChild);
    }
}

// function to print the entire tree

void print_tree(shared_ptr<Node> root) {
    print_subtree(root, 1, true);
}



void subtree_str(shared_ptr<Node> node, int depth, bool lastChild, string& output) {
    // append the node's data with appropriate indentation and prefix
    for (int i = 0; i < depth - 1; i++) {
        output += "    ";
    }
    output += (lastChild ? "|___" : "|---");
    output += node->_data + "\n";

    // recursively print each child node
    for (int i = 0; i < node->_children.size(); i++) {
        bool isLastChild = (i == node->_children.size() - 1);
        subtree_str(node->_children[i], depth + 1, isLastChild, output);
    }
}

// function to print the entire tree
string tree_to_string(shared_ptr<Node> root) {
    string output = "";
    subtree_str(root, 1, true, output);
    return output;
}

