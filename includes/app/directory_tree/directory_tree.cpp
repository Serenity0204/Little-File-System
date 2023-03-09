#include "directory_tree.h"



DirectoryTree::DirectoryTree()
{
    this->_cache = vector<shared_ptr<Node>>();
    this->_nary_tree = NaryTree();
    this->_tk = TextFileTokenizer();
    this->_str_representation = "";
}

DirectoryTree::~DirectoryTree(){}

shared_ptr<Node> DirectoryTree::_find_parent(int level, string parent)
{
    for(int i = 0; i < this->_cache.size(); ++i)
    {
        shared_ptr<Node> node = this->_cache[i];
        assert(node != nullptr);
        if(node->_level == level && node->_data == parent) return node;
    }
    // this case will not hit since parent has to exist in cache
    return nullptr;
}
void DirectoryTree::build()
{
    this->_cache.clear();
    this->_tk.tokenize();
    vector<Info> infos = this->_tk.get_infos();
    
    shared_ptr<Node> root = make_shared<Node>("root");
    this->_nary_tree.set_root(root);
    this->_cache.push_back(root);
    
    // if not initialized
    if(infos.size() == 0)
    {
        shared_ptr<Node> user = make_shared<Node>("user");
        this->_nary_tree.insert(this->_nary_tree.get_root(), user);
        this->_cache.push_back(user);
        return;
    }

    // if initialized
    for(int i = 1; i < infos.size(); ++i)
    {
        Info info = infos[i];
        int level = info._level;
        string self = info._self;
        string parent = info._parent;

        // parent's level is self's level - 1, parent's data is self's parent
        shared_ptr<Node> parent_node = this->_find_parent(level - 1, parent);
        shared_ptr<Node> node = make_shared<Node>(self, level, parent);
        this->_nary_tree.insert(parent_node, node);
        this->_cache.push_back(node);
    }
    this->_str_representation = this->_nary_tree.tree_string();
}

std::ostream& operator << (std::ostream& outs, const DirectoryTree& print_me)
{
    outs << print_me._nary_tree << endl;
    return outs;
}