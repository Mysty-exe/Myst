#pragma once
#include <iostream>
#include <vector>
#include <curses.h>

using namespace std;

class CommandLine
/**
 * Class that represents a text editor
 */

{
private:
    string cmdTxt, line;
    int width, height;
    int cursorX, cursorY;

public:
    WINDOW *commandWindow;

    CommandLine(int w, int h);
    int getWidth();
    void setWidth(int w);
    int getCursorX();
    void updateDimensions();
    bool endOfLine();
    void addCharacter(char character);
    void insertCharacter(char character);
    void backspace();
    vector<string> enter();
    void leftArrow();
    void rightArrow();
    void updateCommand();
    void displayInfo(string text);
    void displayError(string text);
    void clear();
    void clearCmd();
    vector<string> parseCommand();
};