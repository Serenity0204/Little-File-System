#include "engine.h"


// Engine main
// *****************************************************************************************************************
Engine::Engine()
{
    //                                                  Change the name of the project here
    this->_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Little File System");
    this->_window.setKeyRepeatEnabled(true);

    // ADD MORE IN CTOR
    this->_init();
}

// RELEASE MEMORY IN DESTRUCTOR IF USED NEW
Engine::~Engine(){}

// taking input
void Engine::input()
{
    sf::Event event;
    while (this->_window.pollEvent(event))
    {
        // calling update event helper functions
        this->_update_buttons_event(event);

        // User quit
        if(event.type == sf::Event::Closed)
        {
            cout << "User Quit" << endl;
            this->_window.close();
            break;
        }
        // User input text
        if(event.type == sf::Event::TextEntered)
        {  
            this->_cmd.typed_cmd(event);
            if(this->_text_file_input_on) this->_text_file_input.typedOn(event);
            break;
        }
        
        // test retrieve
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            cout << "text is:" << retrieve_data.get_input_box_text() << endl;
            break;
        }

        // update cmd event
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            vector<string> strs_to_screen_folder;
            vector<string> strs_to_screen_file;
            strs_to_screen_folder.clear();
            strs_to_screen_file.clear();
            string to_screen_folder = "FOLDER TERMINAL:\n\n";
            string to_screen_file = "FILE TERMINAL:\n\n";
            bool control_file = false, control_folder = false;

            int code = this->_cmd.update_cmd_event(strs_to_screen_folder, strs_to_screen_file);
            if(code != INVALID)
            {
                if(code != LS && code != OPEN && code != SAVE)
                {
                    to_screen_file += "SUCCESS";
                    to_screen_folder += "SUCCESS";
                    this->_folder_terminal.setHeaderText(to_screen_folder);
                    this->_file_terminal.setHeaderText(to_screen_file);
                    break;
                }         
                if(code == OPEN)
                {
                    if(this->_text_file_input_on)
                    {
                        to_screen_folder += "OPEN FAILURE";
                        to_screen_file += "OPEN FAILURE";
                        this->_folder_terminal.setHeaderText(to_screen_folder);
                        this->_file_terminal.setHeaderText(to_screen_file);
                        break;
                    }
       
                    to_screen_file += "OPEN SUCCESS";
                    to_screen_folder += "OPEN SUCCESS";
                    this->_text_file_input_on = true;
                    this->_folder_terminal.setHeaderText(to_screen_folder);
                    this->_file_terminal.setHeaderText(to_screen_file);
                    break;
                }
                if(code == SAVE)
                {
                    if(!this->_text_file_input_on)
                    {
                        to_screen_file += "SAVE FAILURE";
                        to_screen_folder += "SAVE FAILURE";
                        this->_folder_terminal.setHeaderText(to_screen_folder);
                        this->_file_terminal.setHeaderText(to_screen_file);
                        break;
                    }
                    to_screen_file += "SAVE SUCCESS";
                    to_screen_folder += "SAVE SUCCESS";
                    this->_text_file_input_on = false;
                    this->_folder_terminal.setHeaderText(to_screen_folder);
                    this->_file_terminal.setHeaderText(to_screen_file);
                    break;
                }

                if(code == LS && strs_to_screen_folder.size() == 1 && strs_to_screen_folder[0] == "")
                {
                    to_screen_folder += "NO FOLDER EXISTS";
                    this->_folder_terminal.setHeaderText(to_screen_folder);
                    control_folder = true;
                }
                if(code == LS && strs_to_screen_file.size() == 1 && strs_to_screen_file[0] == "")
                {
                    to_screen_file += "NO FILE EXISTS";
                    this->_file_terminal.setHeaderText(to_screen_file);
                    control_file = true;
                }
                if(control_folder && control_file) break;

                for(int i = 0; i < strs_to_screen_folder.size(); ++i) to_screen_folder += strs_to_screen_folder[i] + '\n';
                for(int i = 0; i < strs_to_screen_file.size(); ++i) to_screen_file += strs_to_screen_file[i] + '\n';

                this->_folder_terminal.setHeaderText(to_screen_folder);
                this->_file_terminal.setHeaderText(to_screen_file);
                break;
            }
            to_screen_folder += "FAILURE";
            to_screen_file += "FAILURE";

            this->_folder_terminal.setHeaderText(to_screen_folder);
            this->_file_terminal.setHeaderText(to_screen_file);
            break;
        }
       if(this->_text_file_input_on) this->_text_file_input.update_input_box(this->_window, event);
       this->_cmd.update_cmd(this->_window, event);
    }
}


// main draw method, update screen
void Engine::display()
{
    // ADD MORE THINGS TO DRAW


    // display the input box for user to enter bet
    this->_cmd.draw_cmd(this->_window);

    this->_folder_terminal.drawTo(this->_window);
    this->_file_terminal.drawTo(this->_window);
    if(this->_text_file_input_on) this->_text_file_input.drawTo(this->_window);

    // display buttons
    this->_buttons.draw_buttons(this->_window);

}


// run method for game
void Engine::run()
{
    // set the position and font before running
    sf::Font arial = config.get_font(ARIAL);
    this->_cmd.setFont(arial);
    this->_folder_terminal.setFont(arial);
    this->_file_terminal.setFont(arial);
    this->_text_file_input.setFont(arial);

    // main loop
    while (this->_window.isOpen())
    {
        // taking input
        this->input();
        // clear the screen
        this->_window.clear(sf::Color(0, 102, 0));
        // draw the updated events
        this->display();
        // sfml method to display to the screen
        this->_window.display();
        // load data to retrieve data class
        retrieve_data.load_input_box_text(*this);
    }

}
// *****************************************************************************************************************






// Init
// *****************************************************************************************************************
// init the attributes
void Engine::_init()
{
    this->_text_file_input_on = false;
    this->_buttons = Buttons();
    this->_folder_terminal = Header("FOLDER TERMINAL", FOLDER_TERMINAL_SIZE, FOLDER_TERMINAL_POS, HEADER_FONT_SIZE, sf::Color::Black, sf::Color::Red);
    this->_file_terminal = Header("FILE TERMINAL", FILE_TERMINAL_SIZE, FILE_TERMINAL_POS, HEADER_FONT_SIZE, sf::Color::Black, sf::Color::Red);
    this->_text_file_input= InputBox(TEXT_FILE_INPUT_FONT_SIZE, TEXT_FILE_INPUT_SIZE, TEXT_FILE_INPUT_POS, sf::Color::Red, sf::Color::White, false);
    this->_cmd = CommandLine();
}
// *****************************************************************************************************************










// update buttons event
void Engine::_update_buttons_event(sf::Event& event)
{
    // to get which button the player clicks
    int action = this->_buttons.update_buttons(this->_window, event);

    // template for action code 
    // if(action == ACTION CODE DEFINED IN SYSTEM)
    // {

    // }

    // ex:
    if(action == ROOT)
    {
        this->_cmd.reset();
        return;
    }
}


