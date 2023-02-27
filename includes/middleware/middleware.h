#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

class Middleware
{
private:
    string _input_box_text;
    string _file_name;
public:
    Middleware();
    ~Middleware();
    void load_input_box_text(string text);
    string get_input_box_text();
    void load_file_name(string name);
    string get_file_name();
};

extern Middleware middleware;

#endif // !MIDDLEWARE_H