#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
//------------------------------------------------------------------------------
//@TODO: include all files we are testing:

#include "../../lib/folder_file_manager/folder_file_manager.h"

//------------------------------------------------------------------------------


bool test_folder_file1(bool debug=false)
{
  FolderFileManager fm;
  bool test = fm.add_file("test.txt");
  if(!test) return false;
  // string root = "../../root/";
  // if(!dirExists(root))
  // {
  //   if(mkdir(root.c_str()) == -1) return false;
  // }

  // ofstream out;
  
  // out.open(root + "test.txt", std::ios_base::app);
  // if(out.fail()) return false;
  // out << "Test message 101" << endl;
  // out.close();
  return true;
}

//------------------------------------------------------------------------------
//@TODO: add more test functions here:



//------------------------------------------------------------------------------


// Lord help me! 
const bool debug = false;

TEST(TEST_STUB, TestStub)
{
  bool success = test_folder_file1(debug);
  EXPECT_EQ(success, true);
}

//------------------------------------------------------------------------------
//@TODO: add more test sets to call test functions here:



//------------------------------------------------------------------------------


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}
