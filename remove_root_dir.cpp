#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <queue>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using namespace std;


bool dirExists(const std::string &path) {
    struct stat info;
    if (stat(path.c_str(), &info) == 0 && info.st_mode & S_IFDIR) {
        return true;
    }
    return false;
}



// remove bottom to top?
bool remove_all(bool debug=false)
{
    ifstream ins_folder, ins_file;
    string path_folder = "../../root/delete_all_folder.txt";
    string path_file = "../../root/delete_all_file.txt";
    string path_user = "../../root/user";
    string path_root = "../../root";
    if(!dirExists(path_root))
    {
      cout << "ROOT DNE" << endl;
      return true;
    }
    ins_file.open(path_file);
    if(ins_file.fail()) return false;
    ins_folder.open(path_folder);
    if(ins_folder.fail()) return false;
    string line_folder, line_file;

    queue<string> folder_q;
    queue<string> file_q;
    while(getline(ins_file, line_file)) file_q.push(line_file);
    while(getline(ins_folder, line_folder)) folder_q.push(line_folder);


    while(!file_q.empty()) 
    {
      int check = remove(file_q.front().c_str());
      if(check != -1)
      {
        file_q.pop();
        continue;;
      }
      string first = file_q.front();
      file_q.pop();
      file_q.push(first);
    }  

    while(!folder_q.empty())
    {
      int check = rmdir(folder_q.front().c_str());
      if(check != -1)
      {
        folder_q.pop();
        continue;
      }
      string first = folder_q.front();
      folder_q.pop();
      folder_q.push(first);
    }

    


    ins_file.close();
    ins_folder.close();
    ofstream out_folder, out_file;
    out_folder.open(path_folder);
    if(out_folder.fail()) return false;
    out_folder.close();

    out_file.open(path_file);
    if(out_file.fail()) return false;
    out_file.close();
    
    if(remove(path_file.c_str()) == -1) return false;
    if(remove(path_folder.c_str()) == -1) return false;
    if(rmdir(path_user.c_str()) == -1) return false;
    if(rmdir(path_root.c_str()) == -1) return false;

    return true;
}

//Lord help me! 
const bool debug = false;

TEST(MAIN_REMOVE, MainRemove)
{
  bool success = remove_all(debug);
  EXPECT_EQ(success, true);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}





