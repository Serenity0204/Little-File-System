#ifndef FOLDER_FILE_MANAGER
#define FOLDER_FILE_MANAGER
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <unordered_set>
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
    void _add_delete_file(const string& path);
public:
    FolderFileManager();
    ~FolderFileManager();

    bool add_folder(const string& path);
    bool add_file(const string& path);
};
    
#endif // !FOLDER_FILE_MANAGER