#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>

//------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/app/directory_tree/directory_tree.h"
//------------------------------------------------------------------------------

using namespace std;



bool test_directory_tree1(bool debug=false)
{
  DirectoryTree d;
  d.build();
  cout << "test directory tree 1 starts:" << endl << endl;
  cout << d;
  cout << "test directory tree 1 ends." << endl;
  return true;
}

bool test_directory_tree2(bool debug=false)
{
  DirectoryTree d;
  d.build();
  cout << "test directory tree 2 starts:" << endl << endl;
  cout << d.get_directory_tree_string() << endl;
  cout << "test directory tree 2 ends." << endl;
  return true;
}

//Lord help me! 
const bool debug = false;

TEST(TEST_DIRECTORY_TREE, TestDirectoryTree1)
{
  bool success = test_directory_tree1(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_DIRECTORY_TREE, TestDirectoryTree2)
{
  bool success = test_directory_tree2(debug);
  EXPECT_EQ(success, true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}