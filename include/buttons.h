#pragma once
#include <iostream>
#include <ncurses.h>
#include <vector>
#include "file.h"

using namespace std;

class Button
/**
 * Class that represents a text editor
 */

{
private:
    string text;
    string toggle;
    int y;

public:
    Button(string txt, string t = "");
    string getText();
    string getToggle();
    void setToggle(string t);
    int getY();
};

class ButtonsList
/**
 * Class that represents a text editor
 */

{
private:
    int x;
    vector<Button> buttons;
    int currentButton;
    int scroll;

public:
    ButtonsList();
    void newButtonList(vector<Button> buttonsParam);

    vector<Button> getButtons();
    void setButtons(vector<Button> buttonsParm);
    int getCurrentButton();
    void setCurrentButton(int btn);

    void displayButtons(WINDOW *win, int height);
    void displayFiles(WINDOW *win, string directory);

    void upArrow(int &scroll);
    void downArrow(int height, int &scroll);
    int enter();
};
