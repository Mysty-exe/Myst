#pragma once
#include "settings.h"

Settings::Settings()
/**
Settings Class Constructor

Args:
    (string) lineNumbers: Whether line numbers are visible or not
    (string) tabSize: Tab size of the editor
    (string) programmingMode: Whether programming mode is on or not
    (string) colorScheme: Color of the editor
    (vector<string>) colors: Possible colors
    (int) colorIndex: Current index of the color

Returns:
    void
 */

{
    lineNumbers = "On";
    tabSize = "4";
    programmingMode = "On";
    colorScheme = "Arctic Horizon";
    colors = {"Arctic Horizon",
              "Twilight Cascade",
              "Crimson Ember",
              "Azure Mist",
              "Verdant Glow",
              "Earthy Brown"};
    colorIndex = 0;
}

string Settings::getLineNumbers()
/**
lineNumbers Getter Function

Returns:
    string
 */

{
    return lineNumbers;
}

void Settings::setLineNumbers(string nums)
/**
lineNumbers Setter Function

Args:
    (string) nums: new lineNumbers

Returns:
    void
 */

{
    lineNumbers = nums;
}

string Settings::getTabSize()
/**
tabSize Getter Function

Returns:
    string
 */

{
    return tabSize;
}

void Settings::setTabSize(string tab)
/**
tabSize Setter Function

Args:
    (string) tab: New tab

Returns:
    void
 */

{
    tabSize = tab;
}

string Settings::getProgrammingMode()
/**
programmingMode Getter Function

Returns:
    string
 */

{
    return programmingMode;
}

void Settings::setProgrammingMode(string programming)
/**
programmingMode Setter Function

Args:
    (string) proamming: New programming

Returns:
    void
 */

{
    programmingMode = programming;
}

string Settings::getColorScheme()
/**
colorScheme Getter Function

Returns:
    string
 */

{
    return colorScheme;
}

void Settings::setColorScheme(string color)
/**
colorScheme Setter Function

Args:
    (string) color: New color

Returns:
    void
 */

{
    colorScheme = color;
}

int Settings::getColorIndex()
/**
colorIndex Getter Function

Returns:
    int
 */

{
    return colorIndex;
}

void Settings::setColorIndex(int index)
{
    colorIndex = index;
}

vector<string> Settings::getColors()
/**
colors Getter Function

Returns:
    vector<string>
 */

{
    return colors;
}

int Settings::loadFromFile(void *user, const char *section, const char *name, const char *value)
/**
Loads the settings from .ini file

Args:
    idk
Returns:
    int
 */

{
    Settings *settings = static_cast<Settings *>(user);

    if (strcmp(section, "editor") == 0)
    {
        if (strcmp(name, "tabsize") == 0)
        {
            settings->tabSize = value;
        }
        else if (strcmp(name, "linenums") == 0)
        {
            settings->lineNumbers = value;
        }
        else if (strcmp(name, "programming") == 0)
        {
            settings->programmingMode = value;
        }
        else if (strcmp(name, "colours") == 0)
        {
            settings->colorScheme = value;
        }
    }
    return 1;
}

void Settings::getSettings(string projectPath)
/**
Loads settings

Returns:
    void
 */

{
    string f = projectPath + "/config/settings.ini";
    if (ini_parse(f.c_str(), loadFromFile, this) < 0)
    {
        cout << "Can't load 'settings.ini'\n";
    }
}

void Settings::saveToFile(string projectPath)
/**
Saves settings into .ini file

Returns:
    string
 */

{
    string f = projectPath + "/config/settings.ini";
    fstream file(f, ios::out | ios::trunc);
    file << "[editor]\n";
    file << "tabsize = " << tabSize << "\n";
    file << "linenums = " << lineNumbers << "\n";
    file << "programming = " << programmingMode << "\n";
    file << "colours = " << colorScheme << "\n";
    file.close();
}

void Settings::resetToDefaults()
/**
Resets settings to default

Returns:
    string
 */

{
    lineNumbers = "On";
    tabSize = "4";
    programmingMode = "On";
    colorScheme = "BLUE";
    colorIndex = 0;
}