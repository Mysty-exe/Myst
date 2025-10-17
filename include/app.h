#pragma once
#include <ncurses.h>
#include <iostream>
#include <stdio.h>
#include "editor.h"
#include "status.h"
#include "menu.h"
#include "settings.h"

#define CUSTOM_MAIN 8
#define CUSTOM_TEXT 9
#define CUSTOM_KEYWORD 10
#define CUSTOM_STRING 11
#define CUSTOM_COMMENT 12
#define CUSTOM_NUMBER 13
#define CUSTOM_DELIMITER 14
#define CUSTOM_OPERATOR 15
#define CUSTOM_SPECIAL 16
#define CUSTOM_PUNCTUATION 17
#define CUSTOM_OTHER 18
#define CUSTOM_ERROR 19
#define CUSTOM_HIGHLIGHT 20

using namespace std;

class App
{
private:
    int MODE;
    int width, height;
    string projectPath;

    Settings settings;
    Editor editor;
    StatusBar status;
    Menu menu;

public:
    App(int w, int h, string path);

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