#pragma once
#include <iostream>
#include <ctime>
#include <format>
#include <vector>
#include <curses.h>

using namespace std;

class StatusBar
/**
 * Class that represents a text editor
 */

{
private:
    string line, date;
    string state, findTxt, replaceTxt, filenameTxt, confirmTxt;
    int width, height;
    int cursorX, cursorY;
    int matches;
    bool error;
    bool modified;

public:
    WINDOW *statusWindow;

    StatusBar();
    StatusBar(int w, int h);

    int getWidth();
    void setWidth(int w);
    int getCursorX();
    string getState();
    void setState(string s);
    string getFindTxt();
    string getReplaceTxt();
    void setMatches(int m);
    string getFilename();
    void setFilename(string filename);
    string getConfirm();
    
    void updateDimensions();
    bool endOfLine();
    void addCharacter(char character);
    void insertCharacter(char character);
    void backspace();
    void tab();
    bool enter();
    void leftArrow();
    void rightArrow();
    string getDateString();
    void getDate();
    void displayDate();
    void setInfo(string text, bool err);
    void update();
    void findAndReplace();
    void resetStatus();
    void saveAs();
    void confirm();
    void clear();
};