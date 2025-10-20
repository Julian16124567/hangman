#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <ncurses.h>
#include <exception>
#include <ctime>
#include <typeinfo>
#include "game.hpp"
using std::string;


//get the random word 
string ReturnWord() {
    std::vector<string> words;
    std::ifstream file("/home/kali2/Schreibtisch/hangman/words/words.txt");    //hardcoded path!
    if (!file.is_open()) {
       std::cerr << "File couldn't be opened or found!\n";
    }
    string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        string word;
        while (iss >> word) {
            words.push_back(word);
            }
        }
        if (words.empty()) {
            std::cerr << "It seem's like the list with the words is Empty!";
        }
        
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, words.size() - 1);
    int number = dis(gen);
    std::string finalword = words[number];
    file.close();
    return finalword;
}


//closing ncurses window
/*change 'q' to a different button
it could be used in hangman*/
void closeWindow() {
    try {
        endwin();
        std::cout << "Exiting game" << std::endl;
    }
    catch(const std::exception& e) {
        writeError(e);
    }
}


//errorlog | write error from main in errorlog.txt
void writeError(const std::exception& e){
    std::ofstream file("/home/kali2/Schreibtisch/hangman/errorlog/errorlog.txt");    //hardcoded path!
    
    //datetimetime
    time_t timestamp;
    time(&timestamp);
    string datetime = ctime(&timestamp);

    //write error in errorlog
    file << datetime << "[" << e.what() << "]\n"; 
    file.close();
}


//length word
int lengthWord(const string& word) {
    return word.size();
}


//enter name 
bool enterName(GameState& g) {
    std::string name;
    std::cout << "Enter your username (max 12 chars): ";
    std::cin >> name;
    if (name.size() > 12) name = name.substr(0,12);
    g.username = name;
    return true;
}


//hangman pictures
std::vector<std::string> AsciiArt = {
R"(
  +---+
  |   |
  O   |
 /|\  |
 / \  |
      |
=========
)",
R"(
  +---+
  |   |
  O   |
 /|\  |
 /    |
      |
=========
)",
R"(
  +---+
  |   |
  O   |
 /|\  |
      |
      |
=========
)",
R"(
  +---+
  |   |
  O   |
 /|   |
      |
      |
=========
)",
R"(
  +---+
  |   |
  O   |
  |   |
      |
      |
=========
)",
R"(
  +---+
  |   |
  O   |
      |
      |
      |
=========
)",
R"(
  +---+
  |   |
      |
      |
      |
      |
=========
)"
};
