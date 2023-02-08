#ifndef FOLDER_FILE_MANAGER
#define FOLDER_FILE_MANAGER

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstdio>
#include <unordered_set>
#include <vector>
#include "../utils/helper_functions.h"

using namespace std;

class FolderFileManager
{
private:
    string _base_dir;
    string _delete_file_dir;
    string _delete_folder_dir;
    unordered_set<string> _folder_set;
    unordered_set<string> _file_set;

    void _init();
    void _read_delete_file_folder();
    // true for adding in file, false for adding in folder
    void _add_delete_file_folder(const string& path, bool control);
public:
    FolderFileManager();
    ~FolderFileManager();

    // search
    bool file_exist(string path);
    bool folder_exist(string path);
    
    // insert
    bool add_folder(string path);
    bool add_file(string path);

    // delete
    bool delete_folder(string path);
    bool delete_file(string path);

    // get
    bool get_sub_dir(const string& path, vector<string>& sub_dir);
    string& get_base_dir(){return this->_base_dir;}
};
    
#endif // !FOLDER_FILE_MANAGER