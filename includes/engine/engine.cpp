#include "engine.h"


// Engine main
// *****************************************************************************************************************
Engine::Engine()
{
    //                                                  Change the name of the project here
    this->_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project Name");
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
            break;
        }
        // User press up and already entered bet
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            vector<string> strs_to_screen;
            strs_to_screen.clear();
            string to_screen = "";
            if(this->_cmd.update_cmd_event(strs_to_screen))
            {
                if(strs_to_screen.size() == 0)
                {
                    to_screen = "success";
                    this->_header.setHeaderText(to_screen);
                    break;
                }         
                for(int i = 0; i < strs_to_screen.size(); ++i) to_screen += strs_to_screen[i] + '\n';
                this->_header.setHeaderText(to_screen);
                break;
            }
            to_screen = "failed";
            this->_header.setHeaderText(to_screen);
            break;
        }

       this->_cmd.update_cmd(this->_window, event);
    }
}


// main draw method, update screen
void Engine::display()
{
    // ADD MORE THINGS TO DRAW


    // display the input box for user to enter bet
    this->_cmd.draw_cmd(this->_window);

    this->_header.drawTo(this->_window);

    // display buttons
    this->_buttons.draw_buttons(this->_window);

}


// run method for game
void Engine::run()
{
    // set the position and font before running
    sf::Font arial = config.get_font(ARIAL);
    this->_cmd.setFont(arial);
    this->_header.setFont(arial);

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
    }

}
// *****************************************************************************************************************






// Init
// *****************************************************************************************************************
// init the attributes
void Engine::_init()
{

    this->_buttons = Buttons();
    this->_header = Header("SCREEN", HEADER_SIZE, HEADER_POS, HEADER_FONT_SIZE, sf::Color(0, 102, 0), sf::Color::Red);
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
    if(action == TEST)
    {
        cout << "TEST" << endl;
        return;
    }
}


