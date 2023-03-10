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
            bool ctrlC = (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::C));
            bool ctrlX = (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::X));
            bool ctrlV = (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::V));
            bool ctrlA = (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::A));
            this->_cmd.typed_cmd(event);
            if(this->_text_file_input_on) this->_text_file_input.typedOn(event);
            if(!ctrlC && !ctrlX && !ctrlV && !ctrlA) 
            {
                this->_is_selected = false;
                this->_text_file_input.setColor(sf::Color::Red);
            }
            break;
        }
        
        // update cmd event
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) this->_update_terminal_event();
        // update text file input
        if(this->_text_file_input_on) this->_text_file_input.update_input_box(this->_window, event);
        // calling update event helper functions
        this->_update_buttons_event(event);
        // update keyboard
        this->_update_keyboard_event();
        // update commandline
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
    if(this->_text_file_input_on) 
    {
        this->_text_file_input.drawTo(this->_window);
        this->_file_name.drawTo(this->_window);
    }
    if(!this->_text_file_input_on) this->_dir_tree_screen.drawTo(this->_window);

    // display buttons
    this->_buttons.draw_buttons(this->_window);

}


// run method for game
void Engine::run()
{
    // set the position and font before running
    sf::Font arial = config.get_font(ARIAL);
    this->_cmd.setFont(arial);

    this->_file_name.setFont(arial);
    this->_folder_terminal.setFont(arial);
    this->_file_terminal.setFont(arial);
    this->_dir_tree_screen.setFont(arial);

    this->_text_file_input.setFont(arial);
    this->_text_file_input.setLimit(true, TEXT_INPUT_LIMIT);
    

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
        middleware.load_input_box_text(this->_text_file_input.getText());
    }

}
// *****************************************************************************************************************






// Init
// *****************************************************************************************************************
// init the attributes
void Engine::_init()
{
    this->_text_file_input_on = false;
    this->_is_selected = false;

    // app components
    // initialize command line first b/c it will initialize file folder manager
    this->_cmd = CommandLine();
    this->_directory_tree = DirectoryTree();
    this->_directory_tree.build();

    // preowned
    this->_buttons = Buttons();
    this->_folder_terminal = Header("FOLDER TERMINAL", FOLDER_TERMINAL_SIZE, FOLDER_TERMINAL_POS, HEADER_FONT_SIZE, sf::Color::Black, sf::Color::Red);
    this->_file_terminal = Header("FILE TERMINAL", FILE_TERMINAL_SIZE, FILE_TERMINAL_POS, HEADER_FONT_SIZE, sf::Color::Black, sf::Color::Red);
    this->_file_name = Header("file name", FILE_NAME_SIZE, FILE_NAME_POS, FILE_NAME_FONT_SIZE, sf::Color::Black, sf::Color::Red);
    this->_dir_tree_screen = Header(this->_directory_tree.get_directory_tree_string(), TEXT_FILE_INPUT_SIZE, TEXT_FILE_INPUT_POS, TEXT_FILE_INPUT_FONT_SIZE, sf::Color::White, sf::Color::Red);
    this->_text_file_input= InputBox(TEXT_FILE_INPUT_FONT_SIZE, TEXT_FILE_INPUT_SIZE, TEXT_FILE_INPUT_POS, sf::Color::Red, sf::Color::White, false);
    
    int v = 0, h = 0;
    Helper::count_string_dimension(this->_directory_tree.get_directory_tree_string(), v, h);
    if(v >= 18 || h >= 50) 
    {
        this->_dir_tree_screen.setHeaderText("Your directory tree is too big! Type \"lfs clear\" to clear all of the directories \nor delete some unused files/folders");
        return;
    }

}
// *****************************************************************************************************************



// update events
// *****************************************************************************************************************

// update keyboard
void Engine::_update_keyboard_event()
{
    // copy
    if(this->_text_file_input_on && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {
        if(!this->_text_file_input.is_selected()) return;
        if(!this->_is_selected) return;
        cout << "copy:" << middleware.get_input_box_text() << endl;
        middleware.load_text_copy(middleware.get_input_box_text());
        this->_is_selected = false;
        return;
    }
    // cut
    if(this->_text_file_input_on && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        if(!this->_text_file_input.is_selected()) return;
        if(!this->_is_selected) return;
        cout << "cut:" << middleware.get_input_box_text() << endl;
        middleware.load_text_copy(middleware.get_input_box_text());
        this->_text_file_input.clear_text();
        this->_is_selected = false;
        return;
    }
    // paste
    if(this->_text_file_input_on && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::V))
    {
        if(!this->_text_file_input.is_selected()) return;
        cout << "paste:" << middleware.get_text_copy() <<endl;
        string text = middleware.get_text_copy();
        this->_text_file_input.set_text_no_limit(text);
        this->_is_selected = false;
        return;
    }
    if(this->_text_file_input_on && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if(!this->_text_file_input.is_selected()) return;
        cout << "select" << endl;
        this->_is_selected = true;
        this->_text_file_input.setColor(sf::Color::Blue);
        return;
    }
}


// update terminal
void Engine::_update_terminal_event()
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
        // if touch, mkdir, rm, del either one of these happens then rebuild directory tree
        if(code == DEL || code == RM || code == MKDIR || code == TOUCH || code == CLEAR)
        {
            this->_directory_tree.build();
            int v = 0, h = 0;
            Helper::count_string_dimension(this->_directory_tree.get_directory_tree_string(), v, h);
            if(v < 18 && h < 50) this->_dir_tree_screen.setHeaderText(this->_directory_tree.get_directory_tree_string());
            if(v >= 18 || h >= 50) 
            {
                this->_dir_tree_screen.setHeaderText("Your directory tree is too big! Type \"lfs clear\" to clear all of the directories \nor delete some unused files/folders");
                return;
            }
        }
        if(code != LS && code != OPEN && code != SAVE)
        {
            to_screen_file += "SUCCESS";
            to_screen_folder += "SUCCESS";
            this->_folder_terminal.setHeaderText(to_screen_folder);
            this->_file_terminal.setHeaderText(to_screen_file);
            return;
        }         
        if(code == OPEN)
        {
            to_screen_file += "OPEN SUCCESS";
            to_screen_folder += "OPEN SUCCESS";
            this->_text_file_input_on = true;
            this->_text_file_input.clear_text();
            this->_text_file_input.set_text_no_limit(middleware.get_text_input());
            this->_folder_terminal.setHeaderText(to_screen_folder);
            this->_file_terminal.setHeaderText(to_screen_file);
            this->_file_name.setHeaderText(middleware.get_file_name());
            return;
        }
        if(code == SAVE)
        {
            to_screen_file += "SAVE SUCCESS";
            to_screen_folder += "SAVE SUCCESS";
            this->_text_file_input_on = false;
            this->_text_file_input.clear_text();
            this->_folder_terminal.setHeaderText(to_screen_folder);
            this->_file_terminal.setHeaderText(to_screen_file);
            return;
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
        if(control_folder && control_file) return;

        for(int i = 0; i < strs_to_screen_folder.size(); ++i) to_screen_folder += strs_to_screen_folder[i] + '\n';
        for(int i = 0; i < strs_to_screen_file.size(); ++i) to_screen_file += strs_to_screen_file[i] + '\n';

        this->_folder_terminal.setHeaderText(to_screen_folder);
        this->_file_terminal.setHeaderText(to_screen_file);
        return;
    }
    to_screen_folder += "FAILURE";
    to_screen_file += "FAILURE";

    this->_folder_terminal.setHeaderText(to_screen_folder);
    this->_file_terminal.setHeaderText(to_screen_file);
}


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

// *****************************************************************************************************************

