#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
extern "C"
{
#include "ini.h"
}

using namespace std;

class Settings
{
private:
    string lineNumbers;
    string tabSize;
    string programmingMode;
    string colorScheme;
    vector<string> colors;
    int colorIndex;

public:
    Settings();
    string getLineNumbers();
    void setLineNumbers(string nums);
    string getTabSize();
    void setTabSize(string tab);
    string getProgrammingMode();
    void setProgrammingMode(string programming);
    string getColorScheme();
    void setColorScheme(string color);
    int getColorIndex();
    void setColorIndex(int index);
    vector<string> getColors();
    static int loadFromFile(void *user, const char *section, const char *name, const char *value);
    void getSettings();
    void saveToFile();
    void resetToDefaults();
};
