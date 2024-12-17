#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <limits.h>
#include <string>
#include <cstring>
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
    void getSettings(string projectFile);
    void saveToFile(string projectFile);
    void resetToDefaults();
};
