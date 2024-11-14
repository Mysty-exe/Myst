#pragma once
#include <iostream>
#include <vector>
#include <ncurses/curses.h>

using namespace std;

class CommandLine
/**
 * Class that represents a text editor
 */

{
private:
    string cmdTxt, line;
    int width;
    int cursorX, cursorY;

public:
    CommandLine();
    int getWidth();
    int getCursorX();
    void setWidth(int w);
    bool endOfLine();
    void addCharacter(char character);
    void insertCharacter(char character);
    void backspace();
    vector<string> enter(WINDOW *cmdWin);
    void leftArrow();
    void rightArrow();
    void updateCommand(WINDOW *cmdWin);
    void displayInfo(WINDOW *cmdWin, string text);
    void displayError(WINDOW *cmdWin, string text);
    void clear(WINDOW *cmdWin);
    void clearCmd(WINDOW *cmdWin);
    vector<string> parseCommand(WINDOW *cmdWin);
};