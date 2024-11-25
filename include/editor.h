#pragma once
#include <iostream>
#include <cstdio>
#include <filesystem>
#include <algorithm>
#include <curses.h>
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

    int maxHeight;
    int width, height;
    int lineNumbersWidth;
    int cursorX, cursorY;
    int lineX, lineY;
    int scroll;

    int tabSize;
    string tabSpaces;
    bool autoComplete, lineNums;
    vector<pair<int, int>> selectedText;
    vector<char> specialCharacters;
    vector<char> otherCharacters;

public:
    WINDOW *textPad;
    WINDOW *linesPad;
    bool highlighting;

    Editor(int w, int h);

    File getFile();
    void setFile(File f);
    void setSettings(int tab, bool line, bool autocomp);

    int getCursorX();
    int getCursorY();
    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    int getScroll();

    int getTab();
    void changeTabSize(int size);
    string setTab();

    bool getLineNumbers();
    bool getAutoComplete();
    void toggleLineNums();
    void toggleAutoComplete();

    void updateDimensions();

    bool endOfLine();
    void addCharacter(char character);
    void insertCharacter(char character);
    void backspace();
    void tab();
    void enter();
    void ctrlA();
    void ctrlC();
    void ctrlV();
    void ctrlX();
    void ctrlS(CommandLine &cmd);

    void goToMouse();
    void scrollUp();
    void scrollDown();
    void shiftUpArrow();
    void shiftDownArrow();
    void shiftLeftArrow();
    void shiftRightArrow();
    void upArrow();
    void downArrow();
    void leftArrow();
    void rightArrow();

    void highlight();
    void endHightlight();
    vector<pair<int, int>> orderHighlight();
    void deleteHighlighted();

    void printLine(bool end, string copiedLine, int lineNum, int &tempY, int &endX);
    void printLineByChar(string copiedLine, int lineNum, int &tempY, int &endX);
    void writeToScreen(bool end);

    int getWrappedX(int x);
    int getWrappedY(int x);
    int getWrappedCursorY(int y, int x);
    int getTabX(int x);
    int enactCommand(CommandLine &cmd, vector<string> command);
};