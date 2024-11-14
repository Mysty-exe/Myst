#include <ncurses/ncurses.h>
#include <iostream>
#include <filesystem>
#include <cstdio>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include "editor.h"
#include "cmd.h"

using namespace std;

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

void editorSpecialKeys(WINDOW *cmdWin, Editor &editor, CommandLine &cmd, int character)
/**
Checks what special character has been pressed in the editor tab

Args:
    (WINDOW*) cmdWin: CommandLine Window Object
    (Editor&) editor: Editor Object
    (CommandLine&) cmd: CommandLine Object
    (int) character: The special character

Returns:
    void
 */

{
    switch (character)
    {
    case 8:
        editor.backspace();
        cmd.clear(cmdWin);
        break;

    case 9:
        editor.tab();
        cmd.clear(cmdWin);
        break;

    case 10:
        editor.enter();
        cmd.clear(cmdWin);
        break;

    case (88 & 0x1F):
        editor.ctrlX();
        cmd.clear(cmdWin);
        break;

    case (83 & 0x1F):
        editor.ctrlS(cmdWin, cmd);
        break;

    case KEY_UP:
        editor.upArrow();
        break;

    case KEY_DOWN:
        editor.downArrow();
        break;

    case KEY_LEFT:
        editor.leftArrow();
        break;

    case KEY_RIGHT:
        editor.rightArrow();
        break;
    }
}

void cmdSpecialKeys(WINDOW *cmdWin, WINDOW *textWin, WINDOW *linesWin, CommandLine &cmd, Editor &editor, int character, int &mode)
/**
Checks what special character has been pressed in the command tab

Args:
    (WINDOW*) cmdWin: CommandLine Window
    (WINDOW*) textWin: Text Window
    (WINDOW*) linesWin: Line Window
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
    case 8:
        cmd.clear(cmdWin);
        cmd.backspace();
        break;

    case 10:
        mode = editor.enactCommand(cmdWin, cmd, cmd.enter(cmdWin));
        if (editor.getCursorX() != 0 || editor.getCursorY() != 0)
        {
            editor.writeToScreen(textWin, linesWin, false);
        }
        else
        {
            editor.writeToScreen(textWin, linesWin, true);
        }
        break;

    case KEY_LEFT:
        cmd.leftArrow();
        break;

    case KEY_RIGHT:
        cmd.rightArrow();
        break;
    }
}

int editorMode(WINDOW *textWin, WINDOW *linesWin, WINDOW *cmdWin, Editor &editor, CommandLine &cmd, int mode)
/**
Handles when user is in the editor tab

Args:
    (WINDOW*) textWin: Text Window
    (WINDOW*) linesWin: Line Window
    (WINDOW*) cmdWin: CommandLine Window
    (Editor&) editor: Editor object
    (CommandLine&) cmd: CommandLine object
    (int&) mode: Mode of the editor

Returns:
    int
 */

{
    int character = wgetch(textWin);

    if (character == 27)
    {
        mode = (mode == 1) ? 2 : 1;
    }

    // Check if character is inputtable
    if (character >= 32 && character <= 126)
    {
        if (editor.endOfLine())
        {
            editor.addCharacter(char(character));
            cmd.clear(cmdWin);
        }
        else
        {
            editor.insertCharacter(char(character));
            cmd.clear(cmdWin);
        }
    }

    editorSpecialKeys(cmdWin, editor, cmd, character);
    editor.writeToScreen(textWin, linesWin, false);

    if (mode == 2)
    {
        wmove(cmdWin, 0, cmd.getCursorX());
        wrefresh(cmdWin);
    }

    return mode;
}

int cmdMode(WINDOW *cmdWin, WINDOW *textWin, WINDOW *lineWin, CommandLine &cmd, Editor &editor, int mode)
/**
Handles when user is in the command tab

Args:
    (WINDOW*) cmdWin: CommandLine Window
    (WINDOW*) textWin: Text Window
    (WINDOW*) linesWin: Line Window
    (CommandLine&) cmd: CommandLine object
    (Editor&) editor: Editor object
    (int&) mode: Mode of the editor

Returns:
    int
 */

{
    int character = wgetch(cmdWin);

    if (character == 27)
    {
        mode = (mode == 2) ? 1 : 2;
    }

    // Check if character is inputtable
    if (character >= 32 && character <= 126)
    {
        if (cmd.endOfLine())
        {
            cmd.clear(cmdWin);
            cmd.addCharacter(char(character));
        }
        else
        {
            cmd.clear(cmdWin);
            cmd.insertCharacter(char(character));
        }
    }

    cmdSpecialKeys(cmdWin, textWin, lineWin, cmd, editor, character, mode);
    cmd.updateCommand(cmdWin);

    if (mode == 1)
    {
        cmd.clearCmd(cmdWin);
        wmove(textWin, editor.getCursorY(), editor.getCursorX());
        wrefresh(textWin);
    }

    return mode;
}

void openFile(WINDOW *textWin, WINDOW *linesWin, WINDOW *cmdWin, Editor &editor, CommandLine &cmd, string fileName, int mode)
/**
Opens "file" and checks for input from the user to update the terminal

Args:
    (WINDOW*) textWin: Window for the editor
    (WINDOW*) linesWin: Window for the lines
    (WINDOW*) cmdWin: Window for the command line
    (Editor) editor: Editor object
    (CommandLine&) cmd: CommandLine object
    (string) fileName: Name of the file being opened
    (int) mode: Mode of the editor

Returns:
    void
 */

{
    File file = File();

    file.open(fileName);
    editor.setFile(file);

    editor.writeToScreen(textWin, linesWin, true);

    // Loop till ESC button is pressed
    while (true)
    {
        if (mode == 1)
        {
            mode = editorMode(textWin, linesWin, cmdWin, editor, cmd, mode);
        }

        else if (mode == 2)
        {
            mode = cmdMode(cmdWin, textWin, linesWin, cmd, editor, mode);
        }
        else
        {
            break;
        }
    }
}

int main(int argc, char **argv)
{
    Editor editor;
    CommandLine cmd;
    int mode = 1;

    // Setup ncurses
    initscr();

    int w, h;
    getmaxyx(stdscr, h, w);
    noecho();
    raw();
    start_color();

    // Setup windows
    WINDOW *linesWindow = newwin(h - 1, 3, 0, 0);
    WINDOW *textWindow = newwin(h - 1, w - 3, 0, 3);
    WINDOW *cmdWindow = newwin(1, w, h - 1, 0);

    keypad(textWindow, true);
    keypad(cmdWindow, true);

    getmaxyx(textWindow, h, w);
    editor.setWidth(w);
    editor.setHeight(h);
    cmd.setWidth(w);

    // Get file from arguments passed when program is run
    string file = argc > 1 ? argv[1] : "";
    if (file == "-help")
    {
        cout << "save" << endl;
        cout << "saveas" << endl;
        cout << "switch" << endl;
        cout << "linenums" << endl;
        cout << "tabsize" << endl;
    }
    else if (fileError(file) && file != "")
    {
        cout << "Unknown File Location." << endl;
    }
    else
    {
        openFile(textWindow, linesWindow, cmdWindow, editor, cmd, file, mode);
    }

    endwin();

    return 0;
}
