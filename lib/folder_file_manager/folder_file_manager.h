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
#include "../../includes/config/config.h"
#include "../../includes/middleware/middleware.h"


using namespace std;

class FolderFileManager
{
private:
    string _base_dir;
    string _delete_file_dir;
    string _delete_folder_dir;
    string _last_file_open;
    string _last_dir_open;

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
    bool get_sub_dir(vector<string>& sub_dir_folder, vector<string>& sub_dir_file);
    string& get_base_dir(){return this->_base_dir;}

    // open file
    string get_file_text(string path);
    // write
    bool write_file(string path);

    // last file open
    void set_last_file_open(string path);    
    string get_last_dir_open(){return this->_last_dir_open;}
    string get_last_file_open(){return this->_last_file_open;}
};
    
#endif // !FOLDER_FILE_MANAGER