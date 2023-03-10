#include "folder_file_manager.h"

FolderFileManager::FolderFileManager()
{
    this->_base_dir = "../../root/user/";
    this->_delete_folder_dir = "../../root/delete_all_folder.txt";
    this->_delete_file_dir = "../../root/delete_all_file.txt";
    this->_last_file_open = "";

    this->_folder_set = unordered_set<string>();
    this->_file_set = unordered_set<string>();

    this->_init();
    this->_read_delete_file_folder();
}

void FolderFileManager::_init()
{
    #ifdef WIN32
    mkdir("../../root/"); 
    #else
    mkdir("../../root/", 0755);
    #endif
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
    #ifdef WIN32
    mkdir(this->_base_dir.c_str());
    #else
    mkdir(this->_base_dir.c_str(), 0755);
    #endif
}

FolderFileManager::~FolderFileManager(){}


bool FolderFileManager::file_exist(string path)
{
    int idx = Helper::first_not_space(path, 0);
    if(idx == -1) return false;
    path = Helper::remove_space(path);

    if(this->_file_set.count(this->_base_dir + path) > 0) return true;
    return false;
}

bool FolderFileManager::folder_exist(string path)
{
    int idx = Helper::first_not_space(path, 0);
    if(idx == -1) return false;
    path = Helper::remove_space(path);

    if(this->_folder_set.count(this->_base_dir + path + "/") > 0) return true;
    return false;
}






bool FolderFileManager::add_folder(string path)
{
    int idx = Helper::first_not_space(path, 0);
    if(idx == -1) return false;
    path = Helper::remove_space(path);

    ofstream outs;
    string file_path = this->_base_dir + path + "/";
    if(this->_folder_set.count(file_path) > 0) return false;   
    if(!this->_count()) return false;
    
    #ifdef WIN32
    if(mkdir(file_path.c_str()) == -1) return false;
    #else
    if(mkdir(file_path.c_str(), 0755) == -1) return false;
    #endif

    this->_folder_set.insert(file_path);
    // add folder path including ending /
    this->_add_delete_file_folder(file_path, false);
    return true;
}



bool FolderFileManager::add_file(string path)
{
    int idx = Helper::first_not_space(path, 0);
    if(idx == -1) return false;
    
    path = Helper::remove_space(path);

    ofstream outs;
    string file_path = this->_base_dir + path;
    if(this->_file_set.count(file_path) > 0) return false;
    if(!this->_count()) return false;
    
    outs.open(file_path);
    if(outs.fail()) return false;
    this->_file_set.insert(file_path);
    outs.close();
    
    // only add if no error
    this->_add_delete_file_folder(file_path, true);
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
    ins.open(this->_delete_folder_dir);
    if(ins.fail()) return;
    while(getline(ins, line)) this->_folder_set.insert(line);
    ins.close();
}


void FolderFileManager::_add_delete_file_folder(const string& file_path, bool control)
{
    ofstream outs;
    if(control) outs.open(this->_delete_file_dir, std::ios_base::app);
    if(!control) outs.open(this->_delete_folder_dir, std::ios_base::app);
    if(outs.fail()) return;
    outs << file_path << endl;
    outs.close();
}

bool FolderFileManager::remove_all()
{

    ifstream ins_folder, ins_file;
    string path_folder = "../../root/delete_all_folder.txt";
    string path_file = "../../root/delete_all_file.txt";
    string path_user = "../../root/user";
    string path_root = "../../root";
    if(!Helper::dir_exists(path_root))
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
    

    return true;
}

bool FolderFileManager::delete_folder(string path)
{
    int idx = Helper::first_not_space(path, 0);
    if(idx == -1) return false;
    path = Helper::remove_space(path);
    string file_path = this->_base_dir + path + "/";
    if(!this->_folder_set.count(file_path)) return false;
    
    if(rmdir(file_path.c_str()) == -1) return false;
    
    this->_folder_set.erase(file_path);
    ofstream outs;
    outs.open(this->_delete_folder_dir);
    if(outs.fail()) return false;
 
    for(auto path : this->_folder_set) outs << path << endl;
    outs.close();
    return true;
}


bool FolderFileManager::delete_file(string path)
{
    int idx = Helper::first_not_space(path, 0);
    if(idx == -1) return false;
    path = Helper::remove_space(path);
    
    string file_path = this->_base_dir + path;
    if(!this->_file_set.count(file_path)) return false;
    if(remove(file_path.c_str()) == -1) return false;
    this->_file_set.erase(file_path);
    
    ofstream outs;
    outs.open(this->_delete_file_dir);
    if(outs.fail()) return false;
    for(auto path : this->_file_set) outs << path << endl;

    outs.close();
    return true;
}

bool FolderFileManager::_count()
{
    vector<string> _folders;
    vector<string> _files;
    _folders.clear();
    _files.clear();
    bool sub_dir = this->get_sub_dir(_folders, _files);
    if(!sub_dir) return false;
    if(_folders.size() + _files.size() >= 10) return false;
    return true;
}

bool FolderFileManager::get_sub_dir(vector<string>& sub_dir_folder, vector<string>& sub_dir_file)
{
    sub_dir_folder.clear();
    struct dirent *dp;
    DIR *dir = opendir(this->_base_dir.c_str());
    // Unable to open directory stream
    if(!dir) return false; 
    
    int file_index = 1, folder_index = 1;
    while ((dp = readdir(dir)) != NULL) 
    {
        if(dp->d_name[0] == '.') continue;
        string name = dp->d_name;

        if(this->file_exist(name)) 
        {
            name = to_string(file_index) + ": " + name;
            file_index++;
            sub_dir_file.push_back(name);
        }
        if(this->folder_exist(name)) 
        {
            name = to_string(folder_index) + ": " + name;
            folder_index++;
            sub_dir_folder.push_back(name);
        }
    }

    // Close directory stream
    closedir(dir); 
    return true;
}


bool FolderFileManager::write_file(string path)
{
    int idx = Helper::first_not_space(path, 0);
    if(idx == -1) return false;
    string message = middleware.get_input_box_text();
    path = Helper::remove_space(path);

    ofstream outs;
    string file_path = this->_base_dir + path;
    // if file DNE it's false
    if(!this->_file_set.count(file_path)) return false;
    outs.open(file_path);
    if(outs.fail()) return false;
    outs << message << endl;
    outs.close();
    return true;
}


string FolderFileManager::get_file_text(string path)
{
    int idx = Helper::first_not_space(path, 0);
    if(idx == -1) return "";
    path = Helper::remove_space(path);
    string file_path = this->_base_dir + path;
    if(!this->_file_set.count(file_path)) return "";

    string res = "";
    string line;

    ifstream ins;
    ins.open(file_path);
    if(ins.fail()) return "";
    while(getline(ins, line)) res += line + '\n';
    ins.close();
    // remove last \n
    res = res.substr(0, res.length() - 1);
    return res;
}


void FolderFileManager::set_last_file_open(string path)
{
    this->_last_dir_open = this->_base_dir;
    this->_last_file_open = path;
}
