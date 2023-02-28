#ifndef NARY_TREE_H
#define NARY_TREE_H
using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// define the n-ary tree node structure
struct Node {
    string data;
    vector<shared_ptr<Node>> children;
};

// function to print the subtree rooted at a node
void printSubtree(shared_ptr<Node> node, int depth, bool lastChild) {
    // print the node's data with appropriate indentation and prefix
    for (int i = 0; i < depth - 1; i++) {
        cout << "   ";
    }
    cout << (lastChild ? "└──" : "├──");
    cout << node->data << endl;

    // recursively print each child node
    for (int i = 0; i < node->children.size(); i++) {
        bool isLastChild = (i == node->children.size() - 1);
        printSubtree(node->children[i], depth + 1, isLastChild);
    }
}

// function to print the entire tree

void printTree(shared_ptr<Node> root) {
    printSubtree(root, 1, true);
}



void printSubtreeStr(shared_ptr<Node> node, int depth, bool lastChild, string& output) {
    // append the node's data with appropriate indentation and prefix
    for (int i = 0; i < depth - 1; i++) {
        output += "    ";
    }
    output += (lastChild ? "└──" : "├──");
    output += node->data + "\n";

    // recursively print each child node
    for (int i = 0; i < node->children.size(); i++) {
        bool isLastChild = (i == node->children.size() - 1);
        printSubtreeStr(node->children[i], depth + 1, isLastChild, output);
    }
}

// function to print the entire tree
string treeToString(shared_ptr<Node> root) {
    string output;
    printSubtreeStr(root, 1, true, output);
    return output;
}





// // example usage
// int main() {
//     // create an example n-ary tree
//     // auto root = make_shared<Node<string>>({"test1", {}});
//     vector<shared_ptr<Node<string>>> vec;
//     for(int i = 0; i <= 8; ++i)
//     {
//         auto root = make_shared<Node<string>>();
//         root->data = "test" + to_string(i);
//         root->children = {};
//         vec.push_back(root);
//     }
    
//     vec[0]->children = {vec[1], vec[2], vec[3]};
//     vec[1]->children = {vec[4], vec[5]};
//     vec[4]->children = {vec[6], vec[7]};
//     // print the tree using ASCII characters
//     printTree(vec[0]);
//     cout << endl;
//     string output = treeToString(vec[0]);
//     cout << output;
//     return 0;
// }

    
#endif // !NARY_TREE_H