#pragma once
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <windows.h>
#include <ncurses/curses.h>
#include <vector>
#include <math.h>
#include "cmd.h"
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
    bool LINENUMS;
    int tabSize;
    string tabSpaces;

public:
    Editor();
    File getFile();
    void setFile(File f);
    void changeTabSize(int size);
    string setTab();
    int getCursorX();
    int getCursorY();
    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    void toggleLineNums();
    bool endOfLine();
    void addCharacter(char character);
    void insertCharacter(char character);
    void backspace();
    void tab();
    void enter();
    void ctrlX();
    void ctrlS(WINDOW *cmdWin, CommandLine &cmd);
    void upArrow();
    void downArrow();
    void leftArrow();
    void rightArrow();
    void writeToScreen(WINDOW *textWin, WINDOW *lineWin, bool end);
    int enactCommand(WINDOW *cmdWin, CommandLine &cmd, vector<string> command);
    int getWrappedX(int x);
    int getWrappedY(int x);
    int getTabX(int x);
};