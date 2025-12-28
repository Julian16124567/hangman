#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <ncurses.h>
#include <exception>
#include "game.hpp"
using std::string, std::vector;


//main
int main() {
    GameState g; 
    int input;

    //get username
    //enterName(g);
    
    //start/draw gui
    try
    {    
        GuiInit();
        DrawGui();
    } catch(const std::exception& e) {
        writeError(e);
    }

    /*has to go to the end of main!
    enter for starting game. all key
    inputs have to go here! */
    while (true) {
        input = getch();
        if (input == '\n') {
            vector<string> guesses;

            //declarations
            g.lives = 8;
            g.trys = 0;
            g.word = ReturnWord();
            g.displayWord = string(g.word.size(), '_'); 
            g.end = true;

            while (g.end) {
                drawMain(g, guesses, AsciiArt);
            }

            mvprintw(20, 0, "Press Enter to play again or 'q' to quit!");
            refresh();

            int c;
            while (true) {
                c = getch();  
                if (c == '\n') {  
                    break;  
                } else if (c == 'q' || c == 'Q') { 
                    endwin();
                    std::cout << "Exiting..." << std::endl;
                    return 0;
                }
            }
        }
    }
}


