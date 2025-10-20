#include <string>
#include <iostream>
#include <ncurses.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include "game.hpp"
using std::string, std::vector;

int x;
int y;

//declare gui 
void GuiInit() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

//ascii art start 
vector<string> AsciiStart = {
" /$$",
"| $$",
"| $$$$$$$   /$$$$$$  /$$$$$$$   /$$$$$$  /$$$$$$/$$$$   /$$$$$$  /$$$$$$$",
"| $$__  $$ |____  $$| $$__  $$ /$$__  $$| $$_  $$_  $$ |____  $$| $$__  $$",
"| $$  \\ $$  /$$$$$$$| $$  \\ $$| $$  \\ $$| $$ \\ $$ \\ $$  /$$$$$$$| $$  \\ $$",
"| $$  | $$ /$$__  $$| $$  | $$| $$  | $$| $$ | $$ | $$ /$$__  $$| $$  | $$",
"| $$  | $$|  $$$$$$$| $$  | $$|  $$$$$$$| $$ | $$ | $$|  $$$$$$$| $$  | $$",
"|__/  |__/ \\_______/|__/  |__/ \\____  $$|__/ |__/ |__/ \\_______/|__/  |__/",
"                               /$$  \\ $$",
"                              |  $$$$$$/",
"                               \\______/"
};


//draw StartButton
void DrawStart(const vector<string>& AsciiStart) {
    int termWidth, termHeight;
    getmaxyx(stdscr, termHeight, termWidth); 

    y = termHeight / 2 - AsciiStart.size() / 2;

    size_t maxWidth = 0;
    for (const auto &line : AsciiStart)
        if (line.size() > maxWidth) maxWidth = line.size();
    x = termWidth / 2 - maxWidth / 2;

    for (size_t i = 0; i < AsciiStart.size(); i++) {
        mvprintw(y + i, x, "%s", AsciiStart[i].c_str());
    }

    mvprintw(y + AsciiStart.size() + 1, x, "Press Enter to Start >");
    refresh();
}


//draw Gui
void DrawGui() {
    
    //start button
    DrawStart(AsciiStart);

    //print text above start
    mvprintw(y + AsciiStart.size() + 1, x, "Press Enter to Start>  ");
    refresh();
}


//clear screen custom 
void clearScreen(int height, int width) {
    for (int i = 0; i < height; i++) {
        move(y + i, x);
        for (int j = 0; j < width; j++){
            addch(' ');
        }
    }
    refresh();
}


//draw hangman ascii art
void drawAscii(const vector<string>& AsciiArt, const GameState& g) {
    int termWidth, termHeight;
    getmaxyx(stdscr, termHeight, termWidth);
    int artY = 2;

    // Berechne, welches ASCII-Bild angezeigt wird
    int index = 6 - g.trys;
    if (index < 0) index = 0;
    if (index >= AsciiArt.size()) index = AsciiArt.size() - 1;

    std::istringstream iss(AsciiArt[index]);
    std::string line;
    while (std::getline(iss, line)) {
        int artX = (termWidth - line.size()) / 2;
        mvprintw(artY++, artX, "%s", line.c_str());
    }
    refresh();
}


bool drawMain(GameState &g, std::vector<std::string> &guesses, const std::vector<std::string> &AsciiArt) {
    if (g.word.empty()) {
        g.word = ReturnWord();
        g.displayWord = std::string(g.word.size(), '_');
        g.trys = 0;
        g.lives = g.maxTries;
        guesses.clear();
    }

    clear();
    int index = std::min(g.trys, (int)AsciiArt.size() - 1);
    drawAscii(AsciiArt, g);

    mvprintw(11, 0, "Welcome %s", g.username.c_str());
    mvprintw(14, 0, "Word: %s", g.displayWord.c_str());
    mvprintw(15, 0, "Lives: %d", g.lives);
    mvprintw(16, 0, "Tries: %d", g.trys);

    mvprintw(17, 0, "Guesses: ");
    int pos = 9;
    for (auto &l : guesses) {
        mvprintw(17, pos, "%s ", l.c_str());
        pos += 2;
    }

    int ch = getch();
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        char letter = tolower(ch);
        if (std::find(guesses.begin(), guesses.end(), std::string(1, letter)) == guesses.end()) {
            guesses.push_back(std::string(1, letter));
            if (g.word.find(letter) == std::string::npos) {
                g.trys++;
                g.lives--;
            } else {
                for (size_t i = 0; i < g.word.size(); i++) {
                    if (g.word[i] == letter) g.displayWord[i] = letter;
                }
            }
        } else {
            mvprintw(18, 0, "Already Guessed!");
        }
    } else {
        mvprintw(18, 0, "Invalid Input");
    }

    if (g.displayWord == g.word) {
        mvprintw(19, 0, "You won! Press Enter to play again.");
        g.end = false;
    }

    if (g.lives <= 0 || g.trys >= g.maxTries) {
        mvprintw(19, 0, "The right word was %s", g.word.c_str());
        mvprintw(20, 0, "Game Over! Press Enter to play again.");
        g.end = false;
    }

    refresh();
    return g.end;
}








