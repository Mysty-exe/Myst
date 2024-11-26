// cd mnt/c/Users/ostou/Documents/Projects/Myst

#include <ncurses.h>
#include <iostream>
#include <filesystem>
#include <cstdio>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string.h>
#include "editor.h"
#include "cmd.h"
extern "C"
{
#include "ini.h"
}

using namespace std;

struct Settings
{
    int tabsize = 4;
    bool linenums = true;
    bool autocomplete = false;
};

int getSettings(void *user, const char *section, const char *name, const char *value)
/**
Get Settings from ini file

Args:
    (void*) user
    (const char*) section: Section of the variables
    (const char*) name: Name of the variable
    (const char*) value: Value of the variable

Returns:
    num
 */

{
    Settings *settings = (Settings *)user;

    if (strcmp(section, "editor") == 0)
    {
        if (strcmp(name, "tabsize") == 0)
        {
            settings->tabsize = atoi(value);
        }
        else if (strcmp(name, "linenums") == 0)
        {
            settings->linenums = strcmp(value, "true") == 0;
        }
        else if (strcmp(name, "autocomplete") == 0)
        {
            settings->autocomplete = strcmp(value, "true") == 0;
        }
    }
    return 1;
}

void setSettings(Settings settings)
/**
Sets Settings and updates ini file

Args:
    (Settings) settings: Settings object

Returns:
    void
 */

{
    fstream file("config/settings.ini", ios::out | ios::trunc);
    file << "[editor]\n";
    file << "tabsize = " << settings.tabsize << "\n";
    file << "linenums = " << (settings.linenums ? "true" : "false") << "\n";
    file << "autocomplete = " << (settings.autocomplete ? "true" : "false") << "\n";
    file.close();
}

bool fileError(string file)
/**
Checks if file location is valid

Args:
    (string) file: Name of the file

Returns:
    bool
 */

{
    fstream writeFile(file, ios::out);
    if (writeFile.fail())
    {
        return true;
    }
    writeFile.close();
    filesystem::remove(file);
    return false;
}

void displayLogo(int h, int w)
/**
Displays the logo onto the screen

Args:
    (int) h: Height of the terminal
    (int) w: Width of the terminal

Returns:
    void
 */

{
    curs_set(0);

    string text;
    int tempY = (h / 2) - (16 / 2);

    fstream readFile("resources/logo.txt");
    while (getline(readFile, text))
    {
        if (tempY - ((h / 2) - (16 / 2)) < 13)
        {
            wattron(stdscr, COLOR_PAIR(2));
        }
        mvprintw(tempY, (w / 2) - (text.length() / 2), text.c_str());
        wattroff(stdscr, COLOR_PAIR(2));

        tempY++;
    }

    readFile.close();
}

void editorSpecialKeys(Editor &editor, CommandLine &cmd, int character)
/**
Checks what special character has been pressed in the editor tab

Args:
    (Editor&) editor: Editor Object
    (CommandLine&) cmd: CommandLine Object
    (int) character: The special character

Returns:
    void
 */

{
    MEVENT event;
    switch (character)
    {
    case KEY_MOUSE:
        if (getmouse(&event) == OK)
        {
            if (event.bstate & BUTTON4_PRESSED)
            {
                editor.scrollUp();
            }
            else if (event.bstate & BUTTON5_PRESSED)
            {
                editor.scrollDown();
            }
        }
        break;

    case KEY_RESIZE:
        curs_set(0);
        editor.updateDimensions();
        cmd.updateDimensions();
        curs_set(1);
        break;

    case KEY_BACKSPACE:
        editor.deleteHighlighted();
        if (!editor.highlighting)
        {
            editor.backspace();
        }
        editor.goToMouse();
        editor.endHightlight();
        cmd.clear();
        break;

    case 9:
        editor.tab();
        editor.goToMouse();
        cmd.clear();
        break;

    case 10:
        editor.deleteHighlighted();
        editor.endHightlight();
        editor.enter();
        editor.goToMouse();
        cmd.clear();
        break;

    case (65 & 0x1F):
        editor.ctrlA();
        break;

    case (67 & 0x1F):
        editor.ctrlC();
        break;

    case (86 & 0x1F):
        editor.ctrlV();
        editor.goToMouse();
        break;

    case (88 & 0x1F):
        editor.ctrlX();
        editor.goToMouse();
        cmd.clear();
        break;

    case (89 & 0x1F):
        editor.ctrlY();
        editor.goToMouse();
        cmd.clear();
        break;

    case (90 & 0x1F):
        editor.ctrlZ();
        editor.goToMouse();
        cmd.clear();
        break;

    case (83 & 0x1F):
        editor.ctrlS(cmd);
        break;

    case KEY_SR:
        editor.shiftUpArrow();
        editor.goToMouse();
        break;

    case KEY_SF:
        editor.shiftDownArrow();
        editor.goToMouse();
        break;

    case KEY_SLEFT:
        editor.shiftLeftArrow();
        editor.goToMouse();
        break;

    case KEY_SRIGHT:
        editor.shiftRightArrow();
        editor.goToMouse();
        break;

    case KEY_UP:
        if (!editor.highlighting)
        {
            editor.upArrow();
        }
        editor.goToMouse();
        editor.endHightlight();
        break;

    case KEY_DOWN:
        if (!editor.highlighting)
        {
            editor.downArrow();
        }
        editor.goToMouse();
        editor.endHightlight();
        break;

    case KEY_LEFT:
        if (!editor.highlighting)
        {
            editor.leftArrow();
        }
        editor.goToMouse();
        editor.endHightlight();
        break;

    case KEY_RIGHT:
        if (!editor.highlighting)
        {
            editor.rightArrow();
        }
        editor.goToMouse();
        editor.endHightlight();
        break;
    }
}

void cmdSpecialKeys(Settings &settings, CommandLine &cmd, Editor &editor, int character, int &mode)
/**
Checks what special character has been pressed in the command tab

Args:
    (Settings&) settings: Settings object
    (CommandLine&) cmd: CommandLine object
    (Editor&) editor: Editor object
    (int) character: The special character
    (int&) mode: Mode of the editor

Returns:
    void
 */

{
    switch (character)
    {
    case KEY_RESIZE:
        curs_set(0);
        cmd.updateDimensions();
        editor.updateDimensions();
        editor.writeToScreen(false);
        curs_set(1);
        break;

    case KEY_BACKSPACE:
        cmd.backspace();
        cmd.clear();
        break;

    case 10:
        mode = editor.enactCommand(cmd, cmd.enter());
        settings.tabsize = editor.getTab();
        settings.linenums = editor.getLineNumbers();
        settings.autocomplete = editor.getAutoComplete();

        if (editor.getCursorX() != 0 || editor.getCursorY() != 0)
        {
            editor.writeToScreen(false);
        }
        else
        {
            editor.writeToScreen(true);
        }
        setSettings(settings);
        break;

    case KEY_LEFT:
        cmd.leftArrow();
        break;

    case KEY_RIGHT:
        cmd.rightArrow();
        break;
    }
}

int editorMode(Editor &editor, CommandLine &cmd, int mode)
/**
Handles when user is in the editor tab

Args:
    (Editor&) editor: Editor object
    (CommandLine&) cmd: CommandLine object
    (int&) mode: Mode of the editor

Returns:
    int
 */

{
    int character = wgetch(editor.textPad);
    if (character == KEY_F(1))
    {
        mode = (mode == 1) ? 2 : 1;
    }

    // Check if character is inputtable
    if (character >= 32 && character <= 126)
    {
        if (editor.endOfLine())
        {
            editor.addCharacter(char(character));
            editor.goToMouse();
            cmd.clear();
        }
        else
        {
            editor.insertCharacter(char(character));
            editor.goToMouse();
            cmd.clear();
        }
    }

    editorSpecialKeys(editor, cmd, character);

    curs_set(0);
    editor.writeToScreen(false);

    if (mode == 2)
    {
        wmove(cmd.commandWindow, 0, cmd.getCursorX());
        wrefresh(cmd.commandWindow);
    }

    return mode;
}

int cmdMode(Settings &settings, CommandLine &cmd, Editor &editor, int mode)
/**
Handles when user is in the command tab

Args:
    (Settings&) settings: Settings object
    (CommandLine&) cmd: CommandLine object
    (Editor&) editor: Editor object
    (int&) mode: Mode of the editor

Returns:
    int
 */

{
    int character = wgetch(cmd.commandWindow);
    if (character == KEY_F(1))
    {
        mode = (mode == 2) ? 1 : 2;
    }

    // Check if character is inputtable
    if (character >= 32 && character <= 126)
    {
        if (cmd.endOfLine())
        {
            cmd.clear();
            cmd.addCharacter(char(character));
        }
        else
        {
            cmd.clear();
            cmd.insertCharacter(char(character));
        }
    }

    cmdSpecialKeys(settings, cmd, editor, character, mode);
    cmd.updateCommand();

    if (mode == 1)
    {
        cmd.clearCmd();
        prefresh(editor.textPad, editor.getScroll(), 0, 0, editor.getNumbersWidth(), editor.getHeight() - 2, editor.getWidth() + (editor.getNumbersWidth() - 1));
    }

    return mode;
}

void openFile(Settings &settings, Editor &editor, CommandLine &cmd, string fileName, int mode)
/**
Opens "file" and checks for input from the user to update the terminal

Args:
    (Settings&) settings: Settings object
    (Editor) editor: Editor object
    (CommandLine&) cmd: CommandLine object
    (string) fileName: Name of the file being opened
    (int) mode: Mode of the editor

Returns:
    void
 */

{
    File file = File();
    HistoryStack stack = HistoryStack();

    file.open(fileName);
    editor.setFile(file);
    editor.setStack(stack);

    editor.writeToScreen(true);

    // Loop till ESC button is pressed
    while (true)
    {
        if (mode == 1)
        {
            mode = editorMode(editor, cmd, mode);
        }
        else if (mode == 2)
        {
            mode = cmdMode(settings, cmd, editor, mode);
        }
        else
        {
            break;
        }
    }
}

int main(int argc, char **argv)
{
    Settings settings;

    // Setup ncurses
    initscr();

    int w, h;
    getmaxyx(stdscr, h, w);

    noecho();
    cbreak();
    raw();
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    use_default_colors();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_RED, -1);

    Editor editor(w, h);
    CommandLine cmd(w, h);
    int mode = 1;

    if (argc < 3)
    {
        // Get file from arguments passed when program is run
        string file = argc > 1 ? argv[1] : "";
        if (file == "-help")
        {
            string text;
            fstream readFile("resources/help.txt");
            while (getline(readFile, text))
            {
                cout << text << endl;
            }
        }

        else if (fileError(file) && file != "")
        {
            cout << "Unknown File Location." << endl;
        }

        else
        {
            keypad(stdscr, true);
            keypad(editor.textPad, true);
            keypad(cmd.commandWindow, true);

            // Parse the INI file and fill the settings struct
            if (ini_parse("config/settings.ini", getSettings, &settings) < 0)
            {
                cout << "Can't load 'settings.ini'\n";
            }
            editor.setSettings(settings.tabsize, settings.linenums, settings.autocomplete);

            if (file == "")
            {
                displayLogo(h, w);
                getch();
            }

            openFile(settings, editor, cmd, file, mode);
        }
    }
    else
    {
        cout << "Unknown Command." << endl;
    }

    endwin();

    return 0;
}
