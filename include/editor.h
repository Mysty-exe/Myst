#pragma once
#include <iostream>
#include <cstdio>
#include <filesystem>
#include <algorithm>
#include <format>
#include <curses.h>
#include <vector>
#include <math.h>
#include "status.h"
#include "file.h"
#include "history.h"
#include "settings.h"
#include "scanner.h"

using namespace std;

class Editor
/**
 * Class that represents a text editor
 */

{
private:
    File file;
    HistoryStack stack;
    LexerScanner scanner;

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
    string state;

    int copiedLines;
    int pastedLines;

    bool highlighting;
    bool cursorVisible;
    string lastSaved;

public:
    WINDOW *textPad;
    WINDOW *linesPad;

    Editor();
    Editor(int w, int h);

    File getFile();
    void resetEditor();
    void setFile(File f);
    void previousFile();
    void nextFile();
    HistoryStack getStack();
    void setStack(HistoryStack s);
    void setSettings(Settings &settings);
    void setScanner(LexerScanner scanner);
    bool checkSpecialChar(char character);
    bool checkOtherChar(char character);
    string getState();

    int getCursorX();
    int getCursorY();
    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    int getNumbersWidth();
    int getScroll();

    int getTab();
    void changeTabSize(int size);
    string setTab();

    bool getLineNumbers();
    bool getAutoComplete();
    void toggleLineNums();
    void toggleAutoComplete();
    bool getHighlighting();
    bool getCursorVisible();
    string getLastSaved();

    void updateDimensions();

    bool endOfLine();
    void addCharacter(char character);
    void insertCharacter(char character);
    void backspace();
    void deleteLine();
    void tab();
    void enter();
    void ctrlS(StatusBar &status);
    void ctrlA();
    void ctrlC();
    void ctrlV();
    void ctrlX();
    void ctrlY();
    void ctrlZ();

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

    int find(string text);
    void replaceAllInstances(string from, string to);
    void printLine(string copiedLine, int &tempY);
    void printLineByChar(string copiedLine, int lineNum, int &tempY);
    void printLineByLexeme(string copiedLine, int lineNum, int &tempY);
    void findPrintLineByChar(string copiedLine, string findTxt, int &tempY);
    void findPrintLineByLexeme(string copiedLine, string findTxt, int &tempY);
    void updateStatus(StatusBar &status);
    void writeToScreen(StatusBar &status);

    int getWrappedX(int x);
    int getWrappedY(int x);
    int getWrappedCursorY(int y, int x);
    int getTabX(int x);
};
