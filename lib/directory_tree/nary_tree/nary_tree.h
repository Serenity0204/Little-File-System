#ifndef NARY_TREE_H
#define NARY_TREE_H


#include "../nary_tree_functions/nary_tree_functions.h"
using namespace std;








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