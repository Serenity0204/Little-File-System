#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>
using namespace std;

class Middleware
{
private:
    string _input_box_text;
    string _file_name;
    string _text_input;
    string _text_copy;
public:
    Middleware();
    ~Middleware();
    void load_input_box_text(string text);
    string get_input_box_text();
    void load_file_name(string name);
    string get_file_name();
    void load_text_input(string text);
    string get_text_input();
    void load_text_copy(string text);
    string get_text_copy();
};

extern Middleware middleware;

#endif // !MIDDLEWARE_H