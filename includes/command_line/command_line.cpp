#include "command_line.h"



CommandLine::CommandLine()
{
    this->_base_dir = this->_fm.get_base_dir();
    this->_command_line = InputBox(INPUT_BOX_FONT_SIZE, INPUT_BOX_SIZE, INPUT_BOX_POS, sf::Color::Red, sf::Color::Black, true, this->_base_dir);
    this->_command_line.setLimit(true, CHAR_LIMIT);
    this->_fm = FolderFileManager();
}
CommandLine::~CommandLine()
{

}



void CommandLine::typed_cmd(sf::Event &input)
{
    this->_command_line.typedOn(input);
}
void CommandLine::update_cmd(sf::RenderWindow &window, sf::Event& event)
{
    this->_command_line.update_input_box(window, event);
}

void CommandLine::draw_cmd(sf::RenderWindow &window)
{
    this->_command_line.drawTo(window);
}