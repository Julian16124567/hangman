#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
using std::string, std::vector;

struct GameState {
    string word;
    int lives;
    int trys;
    int len_word;
    bool end;
    int maxTries = 7;
    string displayWord;
    string username;
};

string ReturnWord();
int lengthWord(const string& word);
void closeWindow();
void DrawGui();
void GuiInit();
void writeError(const std::exception& e);
void clearWindow(int height, int width);
bool drawMain(GameState& g, vector<string>& guesses, const vector<string>& AsciiArt);
bool enterName(GameState& g);

extern vector<string> AsciiStart;
extern vector<string> AsciiArt;

#endif
