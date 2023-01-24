#include "folder_file_manager.h"

FolderFileManager::FolderFileManager()
{
    this->_base_dir = "../../root/user/";
    this->_delete_folder_dir = "../../root/delete_all_folder.txt";
    this->_delete_file_dir = "../../root/delete_all_file.txt";
    this->_init();
    this->_read_delete_file_folder();
}

void FolderFileManager::_init()
{
    mkdir("../../root/");
    ifstream ins;
    ins.open(this->_delete_file_dir);
    if(ins.fail())
    {
        ofstream outs;
        outs.open(this->_delete_file_dir);
        if(outs.fail()) return;
        outs.close();
    }
    ins.close();

    ins.open(this->_delete_folder_dir);
    if(ins.fail())
    {
        ofstream outs;
        outs.open(this->_delete_folder_dir);
        if(outs.fail()) return;
        outs.close();  
    }
    ins.close();

    mkdir(this->_base_dir.c_str());
}

FolderFileManager::~FolderFileManager(){}


bool FolderFileManager::file_exist(const string& path)
{
    if(this->_file_set.count(this->_base_dir + path) > 0) return true;
    return false;
}

bool FolderFileManager::folder_exist(const string& path)
{
    if(this->_folder_set.count(this->_base_dir + path) > 0) return true;
    return false;
}



bool FolderFileManager::add_folder(const string& path)
{

}



bool FolderFileManager::add_file(const string& path)
{
    ofstream outs;
    string file_path = this->_base_dir + path;
    if(this->_file_set.count(file_path) > 0) return false;
    this->_add_delete_file(path);
    outs.open(file_path);
    if(outs.fail()) return false;
    this->_file_set.insert(file_path);
    outs.close();
    return true;
}

void FolderFileManager::_read_delete_file_folder()
{
    string line;
    ifstream ins;
    ins.open(this->_delete_file_dir);
    if(ins.fail()) return;
    while(getline(ins, line)) this->_file_set.insert(line);
    ins.close();
    // if(this->_file_set.size() == 0)
    // {
    //     cout << "TRUE1" << endl;
    // }
    ins.open(this->_delete_folder_dir);
    if(ins.fail()) return;
    while(getline(ins, line)) this->_folder_set.insert(line);
    ins.close();

    // if(this->_folder_set.size() == 0)
    // {
    //     cout << "TRUE2" << endl;
    // }
}


void FolderFileManager::_add_delete_file(const string& path)
{
    ofstream outs;
    string file_path = this->_base_dir + path;
    outs.open(this->_delete_file_dir, std::ios_base::app);
    if(outs.fail()) return;
    outs << file_path << endl;
    outs.close();
}