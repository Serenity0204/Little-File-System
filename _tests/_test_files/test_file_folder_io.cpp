#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
//------------------------------------------------------------------------------
//@TODO: include all files we are testing:

#include "../../includes/folder_file_manager/folder_file_manager.h"

//------------------------------------------------------------------------------
// USE THE SCRIPT TO CLEAR THE ROOT BEFORE RUNNING THIS TEST

// adding file
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

// adding file in a folder that DNE
bool test_folder_file2(bool debug=false)
{
  const string path = "/folder/test.txt";
  FolderFileManager fm;

  bool test = fm.add_file(path);
  if(!test) return true;
  
  return false;
}


// adding folder
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

// adding folder and delete the folder
bool test_folder_file4(bool debug=false)
{
  const string path = "test_folder_to_delete";
  FolderFileManager fm;
  if(!fm.folder_exist(path))
  {
    bool test = fm.add_folder(path);
    if(!test) return false;
  }
  if(fm.folder_exist(path))
  {
    bool test = fm.delete_folder(path);
    if(!test) return false;
  }
  return true;
}

// adding folder then adding the file
bool test_folder_file5(bool debug=false)
{
  const string path_folder = "test_folder2";
  const string path_file = "test_file2.txt";

  FolderFileManager fm;
  if(!fm.folder_exist(path_folder))
  {
    bool test = fm.add_folder(path_folder);
    if(!test) return false;
  }
  if(fm.folder_exist(path_folder))
  {
    string nested_path = path_folder + "/" + path_file;
    if(!fm.file_exist(nested_path))
    {
      bool test = fm.add_file(nested_path);
      if(!test) return false;
    }
  }
  return true;
}


// delete the folder that DNE
bool test_folder_file6(bool debug=false)
{
  const string path = "test_folder5";
  FolderFileManager fm;
  bool test = fm.delete_folder(path);
  if(!test) return true;
  return false;
}

// delete the file that DNE
bool test_folder_file7(bool debug=false)
{
  const string path = "test_file5.txt";
  FolderFileManager fm;
  bool test = fm.delete_file(path);
  if(!test) return true;
  return false;
}


// adding file and delete the file
bool test_folder_file8(bool debug=false)
{
  const string path = "my_file.txt";
  FolderFileManager fm;
  if(!fm.file_exist(path))
  {
    bool test = fm.add_file(path);
    if(!test) return false;
  }
  if(fm.file_exist(path))
  {
    bool test = fm.delete_file(path);
    if(!test) return false;
  }
  return true;
}


// test sub dir 1
bool test_folder_file9(bool debug=false)
{
  FolderFileManager fm;
  fm.get_base_dir() += "test_folder2/";
  vector<string> folder;
  vector<string> file;
  bool test = fm.get_sub_dir(folder, file);
  if(!test) return false;
  if(debug) 
  {
    cout << "folders: " << endl;
    for(int i = 0; i < folder.size(); ++i) cout << folder[i] << endl;
    cout << endl;
    cout << "files: " << endl;
    for(int i = 0; i < file.size(); ++i) cout << file[i] << endl;
  }
  if(file.size() == 1 && folder.size() == 0) return true;

  return false;
}

// test sub dir 2
bool test_folder_file10(bool debug=false)
{
  FolderFileManager fm;
  fm.get_base_dir() += "test_folder/";
  vector<string> folder;
  vector <string> file;
  bool test = fm.get_sub_dir(folder, file);
  if(!test) return false;
  if(debug) 
  {
    cout << "folders: " << endl;
    for(int i = 0; i < folder.size(); ++i) cout << folder[i] << endl;
    cout << endl;
    cout << "files: " << endl;
    for(int i = 0; i < file.size(); ++i) cout << file[i] << endl;
  }
  if(folder.size() == 0 && file.size() == 0) return true;

  return false;
}


// adding empty file
bool test_folder_file11(bool debug=false)
{
  const string path = "       ";
  FolderFileManager fm;

  bool test = fm.add_file(path);
  if(!test) return true;

  return false;
}

// adding empty folder
bool test_folder_file12(bool debug=false)
{
  const string path = "     ";
  FolderFileManager fm;

  bool test = fm.add_folder(path);
  if(!test) return true;

  return false;
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

TEST(TEST_FOLDER_FILE, TestFolderFile4)
{
  bool success = test_folder_file4(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_FOLDER_FILE, TestFolderFile5)
{
  bool success = test_folder_file5(debug);
  EXPECT_EQ(success, true);
}


TEST(TEST_FOLDER_FILE, TestFolderFile6)
{
  bool success = test_folder_file6(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_FOLDER_FILE, TestFolderFile7)
{
  bool success = test_folder_file7(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_FOLDER_FILE, TestFolderFile8)
{
  bool success = test_folder_file8(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_FOLDER_FILE, TestFolderFile9)
{
  bool success = test_folder_file9(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_FOLDER_FILE, TestFolderFile10)
{
  bool success = test_folder_file10(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_FOLDER_FILE, TestFolderFile11)
{
  bool success = test_folder_file11(debug);
  EXPECT_EQ(success, true);
}


TEST(TEST_FOLDER_FILE, TestFolderFile12)
{
  bool success = test_folder_file12(debug);
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
