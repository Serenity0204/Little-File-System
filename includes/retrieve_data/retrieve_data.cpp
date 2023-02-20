#include "retrieve_data.h"

RetrieveData retrieve_data = RetrieveData();


RetrieveData::RetrieveData(){}

RetrieveData::~RetrieveData(){}

string RetrieveData::get_input_box_text()
{
    return this->_input_box_text;
}

void RetrieveData::load_input_box_text(Engine& engine)
{
    this->_input_box_text= engine._text_file_input.getText();
}
