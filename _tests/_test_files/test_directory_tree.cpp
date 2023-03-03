#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>

//------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/components/directory_tree/nary_tree/nary_tree.h"

//------------------------------------------------------------------------------

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

bool test_nary_tree1(bool debug=false)
{
  // auto root = make_shared<Node<string>>({"test1", {}});
  vector<shared_ptr<Node>> vec;
  for(int i = 0; i <= 8; ++i)
  {
      auto root = make_shared<Node>();
      root->_data = "test" + to_string(i);
      root->_children = {};
      vec.push_back(root);
  }
  
  vec[0]->_children = {vec[1], vec[2], vec[3]};
  vec[1]->_children = {vec[4], vec[5]};
  vec[4]->_children = {vec[6], vec[7]};
  // print the tree using ASCII characters
  print_tree(vec[0]);
  cout << endl;
  string output = tree_to_string(vec[0]);
  cout << output;
  return true;
}


//Lord help me! 
const bool debug = false;

TEST(TEST_NARY_TREE, TestNaryTree1)
{
  bool success = test_nary_tree1(debug);
  EXPECT_EQ(success, true);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}