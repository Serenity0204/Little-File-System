#include "middleware.h"

Middleware middleware = Middleware();


Middleware::Middleware(){}

Middleware::~Middleware(){}

string Middleware::get_input_box_text()
{
    return this->_input_box_text;
}

void Middleware::load_input_box_text(string text)
{
    this->_input_box_text= text;
}


void Middleware::load_file_name(string name)
{
    this->_file_name = name;
}

string Middleware::get_file_name()
{
    return this->_file_name;
}