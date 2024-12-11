#pragma once
#include <ncurses.h>
#include <iostream>
#include <stdio.h>
#include "editor.h"
#include "status.h"
#include "menu.h"
#include "settings.h"

using namespace std;

class App
{
private:
    int MODE;
    int width, height;

    Settings settings;
    Editor editor;
    StatusBar status;
    Menu menu;

public:
    App(int w, int h);

    void init();
    int getMode();
    void setMode(int arg);
    Settings getSettings();
    void setSettings(Settings arg);
    Editor getEditor();
    void setEditor(Editor arg);
    StatusBar getStatus();
    void setStatus(StatusBar arg);
    Menu getMenu();
    void setMenu(Menu arg);
    void setColor(string color);

    void displayLogo();

    void checkForSpecialChars(int character);
    void editorSpecialChars(int character);
    void statusSpecialChars(int character);
    void settingsSpecialChars(int character);
    void switchFileSpecialChars(int character);
    void preferencesSpecialChars(int character);

    void editorMode();
    void statusMode();
    void settingsMode();
    void switchFileMode();
    void preferencesMode();

    void stateLoop(string filename);
};