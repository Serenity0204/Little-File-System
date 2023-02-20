#ifndef RETRIEVE_DATA_H
#define RETRIEVE_DATA_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

class RetrieveData
{
private:
    string _input_box_text;
public:
    RetrieveData();
    ~RetrieveData();
    void load_input_box_text(string text);
    string get_input_box_text();
};

extern RetrieveData retrieve_data;

#endif // !RETRIEVE_DATA_H