#include <ncurses/ncurses.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include "editor.h"

using namespace std;

void checkSpecialKeys(Editor &editor, int character)
{
    switch (character)
    {
    case 8:
        editor.backspace();
        break;

    case 10:
        editor.enter();
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

void openFile(Editor editor, WINDOW *linesWin, WINDOW *textWin, string fileName)
{
    File file = File();
    editor.setFile(file);

    editor.writeToScreen(textWin, linesWin);

    // Loop till ESC button is pressed
    int character;
    while ((character = wgetch(textWin)) != 27)
    {
        // Check if character is inputtable
        if (character >= 32 && character <= 126)
        {
            if (editor.endOfLine())
            {
                editor.addCharacter(char(character));
            }
            else
            {
                editor.insertCharacter(char(character));
            }
        }

        checkSpecialKeys(editor, character);

        // Get width and height of the window
        int w, h;
        getmaxyx(textWin, h, w);
        editor.setWidth(w);
        editor.setHeight(h);

        editor.writeToScreen(textWin, linesWin);
    }
}

int main(int argc, char **argv)
{
    Editor editor;

    // Setup ncurses
    initscr();

    int w, h;
    getmaxyx(stdscr, h, w);
    noecho();
    raw();

    // Setup windows
    WINDOW *linesWindow = newwin(h, 3, 0, 0);
    WINDOW *textWindow = newwin(h, w - 3, 0, 3);
    keypad(textWindow, true);

    getmaxyx(textWindow, h, w);
    editor.setWidth(w);
    editor.setHeight(h);

    openFile(editor, linesWindow, textWindow, "");

    endwin();

    return 0;
}
