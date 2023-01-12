#ifndef CONFIG_H
#define CONFIG_H
#include <bits/stdc++.h>
#include "system.h"
#include <SFML/Graphics.hpp>
using namespace std;


class Config
{
private:
    std::unordered_map<string, std::shared_ptr<sf::Texture>> _texture_map;
    std::unordered_map<int, std::shared_ptr<sf::Font>> _font_map;
    std::shared_ptr<sf::Font> _get_font(int key);
    std::shared_ptr<sf::Texture> _get_texture(string key);
    void _set_texture();
    void _set_font();
public:
    Config();
    ~Config();
    sf::Texture& get_texture(string index);
    sf::Font& get_font(int index);
};


// global instance here
extern Config config;



#endif