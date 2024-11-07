#pragma once
#include <iostream>
#include <ncurses/curses.h>
#include <vector>
#include <math.h>
#include "file.h"

using namespace std;

class Editor
/**
 * Class that represents a text editor
 */

{
private:
    File file;
    int width, height;
    int lineX, lineY;
    int cursorX, cursorY;

public:
    Editor();
    void setFile(File f);
    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    bool endOfLine();
    void addCharacter(char character);
    void insertCharacter(char character);
    void backspace();
    void enter();
    void upArrow();
    void downArrow();
    void leftArrow();
    void rightArrow();
    void writeToScreen(WINDOW *textWin, WINDOW *lineWin);
    int getWrappedX(int x);
    int getWrappedY(int x);
};