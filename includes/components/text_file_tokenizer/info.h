#ifndef INFO_H
#define INFO_H
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct Info
{
public:
    string _parent;
    string _self;
    int _level;
    Info(){}
    Info(string parent, string self, int level)
    {
        this->_parent = parent;
        this->_self = self;
        this->_level = level;
    }
    ~Info(){}
    friend std::ostream& operator << (std::ostream& outs, const Info& print_me)
    {
        outs << "parent:" << print_me._parent << endl;
        outs << "self:" << print_me._self << endl;
        outs << "level:" << print_me._level << endl;
        return outs;
    }
    friend bool operator == (const Info& left, const Info& right)
    {
        if(left._level == right._level && left._parent == right._parent && left._self == right._self) return true;
        return false;
    }
    friend bool operator != (const Info& left, const Info& right)
    {
        return !(left == right);
    }
};

    
#endif // INFO_H