#pragma once
#include <iostream>
#include <curses.h>
#include <editor.h>
#include <vector>
#include <string>
#include "file.h"
#include "buttons.h"
#include "settings.h"

using namespace std;

class Menu
{
private:
    int currentMenu;
    int width, height, scroll;
    string currentDirectory, fact;
    vector<Button> settingsButtons, switchButtons, preferencesButtons;
    ButtonsList settingsList, switchList, preferencesList;

public:
    WINDOW *menuPad;
    Menu();
    Menu(int w, int h, Settings &settings, string projectFile);
    int getCurrentMenu();
    void setCurrentMenu(int current);
    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    int getScroll();
    void setScroll(int s);
    string getCurrentDirectory();
    void setCurrentDirectory(string dir);
    void updateDimensions();
    vector<Button> getButtons();
    void setButtons(vector<Button> buttons);
    void setFileButtons(string directory);
    void displayButtons();
    vector<string> getMenuText(Editor &editor);
    vector<string> getPreferencesText(Settings &settings);
    void displayText(vector<string> texts);
    void upArrow();
    void downArrow();
    int enter(File &file);
    void back();
    void resetPad();
};
