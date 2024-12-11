#pragma once
#include "menu.h"

Menu::Menu()
/**
Menu Class Constructor

Returns:
    void
 */

{
}

Menu::Menu(int w, int h, Settings &settings)
/**
Menu Class Constructor

Vars:
    (string) fact: random fact taken from file
    (int) maxHeight: Max Height of the editor
    (int) width: width of the editor
    (int) height: height of the editor
    (int) scroll: How scrolled the text editor is
    (int) currentMenu: current menu index
    (string) currentDirectory: current directory
    (vector<Button>) settingsButtons: Buttons vector in settings menu
    (vector<Button>) switchButtons: Buttons vector in switch file menu
    (vector<Button>) preferencesButtons: Buttons vector in preferences menu
    (ButtonsList) settingsList: ButtonsList for settings menu
    (ButtonsList) switchButtons: ButtonsList for switch file menu
    (ButtonsList) preferencesButtons: ButtonsList for preferences menu
    (WINDOW*) menuPad: Pad for the menu

Returns:
    void
 */

{
    srand((unsigned)time(NULL));

    fact = "";
    int lineNumber = 1;
    int random = 1 + (rand() % 101);
    fstream readFile("resources/facts.txt");
    while (getline(readFile, fact))
    {
        if (lineNumber == random)
        {
            break;
        }
        lineNumber++;
    }

    width = w;
    height = h;
    scroll = 0;
    currentMenu = 0;
    currentDirectory = filesystem::current_path();

    settingsButtons = {Button("Back"), Button("Save"), Button("Save As"), Button("Switch File"), Button("Preferences"), Button("Quit")};
    switchButtons = {};
    preferencesButtons = {Button("Back"), Button("Line Numbers", settings.getLineNumbers()), Button("Tabsize", settings.getTabSize()), Button("Programming", settings.getProgrammingMode()), Button("Colour", settings.getColorScheme())};

    settingsList.newButtonList(settingsButtons);
    switchList.newButtonList(switchButtons);
    preferencesList.newButtonList(preferencesButtons);

    if ((int)switchButtons.size() > height)
    {
        menuPad = newpad(switchButtons.size(), width);
    }
    else
    {
        menuPad = newpad(height, width);
    }
}

int Menu::getCurrentMenu()
/**
currentMenu Getter Function

Returns:
    int
 */

{
    return currentMenu;
}

void Menu::setCurrentMenu(int current)
/**
currentMenu Setter Function

Args:
    (int) current: New currentMenu

Returns:
    void
 */

{
    currentMenu = current;
}

int Menu::getWidth()
/**
width Getter Function

Returns:
    int
 */

{
    return width;
}

void Menu::setWidth(int w)
/**
width Setter Function

Args:
    (int) w: New width

Returns:
    void
 */

{
    width = w;
}

int Menu::getHeight()
/**
height Getter Function

Returns:
    int
 */

{
    return height;
}

void Menu::setHeight(int h)
/**
height Setter Function

Args:
    (int) h: New height

Returns:
    void
 */

{
    height = h;
}

int Menu::getScroll()
/**
scroll Getter Function

Returns:
    int
 */

{
    return scroll;
}

void Menu::setScroll(int s)
/**
scroll Setter Function

Args:
    (int) s: New scroll

Returns:
    void
 */

{
    scroll = s;
}

string Menu::getCurrentDirectory()
/**
currentDirectory Getter Function

Returns:
    string
 */

{
    return currentDirectory;
}

void Menu::setCurrentDirectory(string dir)
/**
currentDirectory Setter Function

Args:
    (string) dir: New currentDirectory

Returns:
    void
 */

{
    currentDirectory = dir;
}

void Menu::updateDimensions()
/**
Updates dimensions if terminal size changes

Returns:
    void
 */

{
    delwin(menuPad);
    getmaxyx(stdscr, height, width);

    if ((int)switchButtons.size() > height)
    {
        menuPad = newpad(switchButtons.size(), width);
    }
    else
    {
        menuPad = newpad(height, width);
    }
    keypad(menuPad, true);

    if (currentMenu == 1)
    {
        prefresh(menuPad, scroll, 0, 3, 0, height - 4, width - 1);
    }
    else
    {
        prefresh(menuPad, scroll, 0, 0, 0, height - 1, width - 1);
    }
}

vector<Button> Menu::getButtons()
/**
Gets the vetor of buttons based on the current menu

Returns:
    vector<Button>
 */

{
    if (currentMenu == 0)
    {
        return settingsList.getButtons();
    }
    else if (currentMenu == 1)
    {
        return switchList.getButtons();
    }
    return preferencesList.getButtons();
}

void Menu::setButtons(vector<Button> buttons)
/**
buttons Setter Function

Args:
    (vector<Button>) buttons: New buttons

Returns:
    void
 */

{
    if (currentMenu == 0)
    {
        settingsList.setButtons(buttons);
    }
    else if (currentMenu == 2)
    {
        preferencesList.setButtons(buttons);
    }
}

void Menu::setFileButtons(string directory)
/**
Sets the buttons of the files based on the directory

Args:
    (string) directory: directory to get all the files from

Returns:
    void
 */

{
    switchButtons = {};
    error_code ec;
    if (filesystem::is_regular_file(directory, ec))
    {
        directory = std::filesystem::path(directory).parent_path();
    }
    for (auto &p : filesystem::directory_iterator(directory))
    {
        switchButtons.push_back(Button(p.path()));
    }
    if (switchButtons.size() == 0)
    {
        switchButtons.push_back(Button("No Files In Folder"));
    }
    setButtons(switchButtons);

    switchList.setButtons(switchButtons);
    int h, w;
    getmaxyx(menuPad, h, w);
    if ((int)switchButtons.size() > h)
    {
        updateDimensions();
    }
}

void Menu::displayButtons()
/**
Displays all the buttons

Returns:
    void
 */

{
    if (currentMenu == 0)
    {
        settingsList.displayButtons(menuPad, height);
    }
    else if (currentMenu == 1)
    {
        switchList.displayFiles(menuPad, currentDirectory);
    }
    else if (currentMenu == 2)
    {
        preferencesList.displayButtons(menuPad, height);
    }
}

vector<string> Menu::getMenuText(Editor &editor)
/**
Gets menu text

Returns:
    vector<string>
 */

{
    vector<string> text;
    string filename = (editor.getFile().getName() == "") ? "[Untitled File]" : editor.getFile().getName();
    text.push_back("File Information");
    text.push_back("File: " + filename);
    text.push_back("Lines: " + to_string(editor.getFile().getLines().size()));
    text.push_back("Col: " + to_string(editor.getCursorX() + 1));
    text.push_back("");
    text.push_back("Last Saved: " + editor.getLastSaved());
    text.push_back("");
    text.push_back("Shortcuts:");
    text.push_back("Ctrl-S   -   Save");
    text.push_back("Ctrl-F   -   Find/Replace");
    text.push_back("Ctrl-B   -   Previous File");
    text.push_back("Ctrl-N   -   Next File");
    text.push_back("Ctrl-E   -   Settings/Menu");
    text.push_back("Ctrl-T   -   Switch File");
    text.push_back("Ctrl-P   -   Preferences");
    text.push_back("Ctrl-Q   -   Quit");
    text.push_back("");
    text.push_back("Did You Know?");
    text.push_back(fact);
    return text;
}

vector<string> Menu::getPreferencesText(Settings &settings)
/**
Gets preferences text

Returns:
    vector<string>
 */

{
    vector<string> text;
    text.push_back(string("1. Line Numbers ") + "[" + settings.getLineNumbers() + "]");
    text.push_back("Show or hide line numbers in the text editor.");
    text.push_back("Useful for coding or navigating large files.");
    text.push_back("");
    text.push_back(string("2. Tab Size ") + "[" + settings.getTabSize() + "]");
    text.push_back("Set the number of spaces for each tab.");
    text.push_back("Choose a size that suits your workflow.");
    text.push_back("");
    text.push_back(string("3. Programming Mode ") + "[" + settings.getProgrammingMode() + "]");
    text.push_back("Enable features like autocomplete and autotab.");
    text.push_back("Ideal for editing code.");
    text.push_back("");
    text.push_back(string("4. Colour Scheme ") + "[" + settings.getColorScheme() + "]");
    text.push_back("Select the editor's colour scheme.");
    return text;
}

void Menu::displayText(vector<string> texts)
/**
Display text in the menu

Returns:
    void
 */

{
    int line = height / 2 - 9;
    int x = (width - 30) / 2 - 20;
    for (string &text : texts)
    {
        if (currentMenu == 0)
        {
            if (line == (height / 2 - 9) || line == (height / 2 - 9) + 5 || line == (height / 2 - 9) + 7 || line == (height / 2 - 9) + 17)
            {
                wattron(menuPad, COLOR_PAIR(2));
            }
        }
        else if (currentMenu == 2)
        {
            if ((line - (height / 2 - 9)) % 4 == 0)
            {
                wattron(menuPad, COLOR_PAIR(2));
            }
        }
        mvwprintw(menuPad, line, x + 30, text.c_str(), "%s");
        wattroff(menuPad, COLOR_PAIR(2));
        line += 1;
    }
}

void Menu::upArrow()
/**
Handles when up arrow is pressed

Returns:
    void
 */

{
    if (currentMenu == 0)
    {
        settingsList.upArrow(scroll);
    }
    else if (currentMenu == 1)
    {
        switchList.upArrow(scroll);
    }
    else if (currentMenu == 2)
    {
        preferencesList.upArrow(scroll);
    }
}

void Menu::downArrow()
/**
Handles when down arrow is pressed

Returns:
    void
 */

{
    if (currentMenu == 0)
    {
        settingsList.downArrow(height, scroll);
    }
    else if (currentMenu == 1)
    {
        switchList.downArrow(height - 10, scroll);
    }
    else if (currentMenu == 2)
    {
        preferencesList.downArrow(height, scroll);
    }
}

int Menu::enter(File &file)
/**
Handles when enter is pressed

Returns:
    void
 */

{
    if (currentMenu == 0)
    {
        return settingsList.enter();
    }
    else if (currentMenu == 1)
    {
        int num = switchList.enter();
        error_code ec;
        const filesystem::path path(switchList.getButtons()[num].getText());
        if (filesystem::is_directory(path, ec))
        {
            switchList.setCurrentButton(0);
            scroll = 0;
            currentDirectory = switchList.getButtons()[num].getText();
            try
            {
                setFileButtons(path);
            }
            catch (const std::exception &e)
            {
                currentDirectory = currentDirectory.substr(0, currentDirectory.find_last_of("/"));
            }
        }
        else if (filesystem::is_regular_file(path, ec))
        {
            if (File::overwrite(path))
            {
                file.open(path);
            }
            return 1;
        }

        return 0;
    }
    return preferencesList.enter();
}

void Menu::back()
/**
Handles when back arrow is pressed in the switch file menu

Returns:
    void
 */

{
    currentDirectory = currentDirectory.substr(0, currentDirectory.find_last_of("/"));
    error_code ec;
    const filesystem::path path(currentDirectory);
    if (filesystem::is_directory(path, ec))
    {
        switchList.setCurrentButton(0);
        scroll = 0;
        setFileButtons(path);
    }
}

void Menu::resetPad()
/**
Resets the pad

Returns:
    void
 */

{
    currentMenu = 0;
    scroll = 0;
    settingsList.setCurrentButton(0);
    switchList.setCurrentButton(0);
    preferencesList.setCurrentButton(0);
}
