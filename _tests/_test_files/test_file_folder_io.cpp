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
  const string path = "test.txt";
  FolderFileManager fm;
  if(!fm.file_exist(path))
  {
    bool test = fm.add_file(path);
    if(!test) return false;
  }
  return true;
}

bool test_folder_file2(bool debug=false)
{
  const string path = "/folder/test.txt";
  FolderFileManager fm;
  if(!fm.file_exist(path))
  {
    bool test = fm.add_file(path);
    if(!test) return true;
  }
  return false;
}


bool test_folder_file3(bool debug=false)
{
  const string path = "test_folder";
  FolderFileManager fm;
  if(!fm.folder_exist(path))
  {
    bool test = fm.add_folder(path);
    if(!test) return false;
  }
  return true;
}


//------------------------------------------------------------------------------
//@TODO: add more test functions here:



//------------------------------------------------------------------------------


// Lord help me! 
const bool debug = false;

TEST(TEST_FOLDER_FILE, TestFolderFile1)
{
  bool success = test_folder_file1(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_FOLDER_FILE, TestFolderFile2)
{
  bool success = test_folder_file2(debug);
  EXPECT_EQ(success, true);
}


TEST(TEST_FOLDER_FILE, TestFolderFile3)
{
  bool success = test_folder_file3(debug);
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
