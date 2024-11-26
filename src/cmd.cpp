#pragma once
#include "cmd.h"

CommandLine::CommandLine(int w, int h)
/**
Editor Class Constructor

Vars:
    (int) width: Width of the command line
    (int) height: Height of the command line
    (int) cursorX: X-Index that the cursor is on in the command line
    (int) cursorY: Y-Index that the cursor is on in the command line (always zero)
    (string) line: Error being displayed in the command line
    (string) cmdTxt: Command being written into the command line
    (WINDOW*) commandWindow: Window for the command line

Returns:
    void
 */

{
    width = w;
    height = h;
    cursorX = cursorY = 0;
    cmdTxt = "";
    line = "";
    commandWindow = newwin(1, width, height - 1, 0);
}

int CommandLine::getWidth()
/**
Width Getter Function

Returns:
    int
 */

{
    return width;
}

void CommandLine::setWidth(int w)
/**
Width Setter Function

Args:
    (int) w: New width of the command line

Returns:
    void
 */

{
    width = w;
}

int CommandLine::getCursorX()
/**
CursorX Getter Function

Returns:
    int
 */

{
    return cursorX;
}

void CommandLine::updateDimensions()
/**
Updates size of window if terminal has been changed

Returns:
    void
 */

{
    getmaxyx(stdscr, height, width);
    delwin(commandWindow);
    commandWindow = newwin(1, width, height - 1, 0);
    getmaxyx(commandWindow, height, width);
    keypad(commandWindow, true);
    wrefresh(commandWindow);
}

bool CommandLine::endOfLine()
/**
Checks if the cursor is at the end of the line

Returns:
    bool
 */

{
    return (cursorX >= (int)cmdTxt.length());
}

void CommandLine::addCharacter(char character)
/**
Adds a character to the command line

Args:
    (char) character: Character you want to add

Returns:
    void
 */

{
    if ((int)cmdTxt.length() < width - 1)
    {
        cursorX += 1;
        cmdTxt = cmdTxt + character;
    }
}

void CommandLine::insertCharacter(char character)
/**
Insert a character in between two characters in the command line

Args:
    (char) character: Character to insert

Returns:
    void
 */

{
    if ((int)cmdTxt.length() < width - 1)
    {
        cmdTxt = cmdTxt.substr(0, cursorX) + character + cmdTxt.substr(cursorX, cmdTxt.length());
        cursorX += 1;
    }
}

void CommandLine::backspace()
/**
Deletes a character in the command line

Returns:
    void
 */

{
    if (cursorX > 0)
    {
        cursorX -= 1;
        cmdTxt = cmdTxt.erase(cursorX, 1);
    }
}

vector<string> CommandLine::enter()
/**
Passes the command to "parseCommand()" and deletes it

Returns:
    void
 */

{
    vector<string> command = parseCommand();
    return command;
}

void CommandLine::leftArrow()
/**
Moves cursor to the left if its not already at the beginning of the command line

Returns:
    void
 */

{
    if (cursorX > 0)
    {
        cursorX--;
    }
}

void CommandLine::rightArrow()
/**
Moves cursor to the right of the lin if cursor isn't already at the end of the command line

Returns:
    void
 */

{
    if (cursorX <= (int)cmdTxt.length() - 1)
    {
        cursorX++;
    }
}

void CommandLine::updateCommand()
/**
Updates the command in the command line

Returns:
    void
 */

{
    if (line.length() == 0)
    {
        werase(commandWindow);
        mvwprintw(commandWindow, 0, 0, cmdTxt.c_str());
        wmove(commandWindow, cursorY, cursorX);
        getmaxyx(commandWindow, height, width);
        wrefresh(commandWindow);
    }
}

void CommandLine::displayInfo(string text)
/**
Displays an info message with colours in the command line

Args:
    (string) text: Text to display in the info message

Returns:
    void
 */

{
    line = text;
    cmdTxt = "";
    cursorX = 0;

    wattron(commandWindow, COLOR_PAIR(3));
    mvwprintw(commandWindow, 0, 0, text.c_str());
    wattroff(commandWindow, COLOR_PAIR(3));

    wrefresh(commandWindow);
}

void CommandLine::displayError(string text)
/**
Displays an error message with colours in the command line

Args:
    (string) text: Text to display in the error message

Returns:
    void
 */

{
    line = text;
    cmdTxt = "";
    cursorX = 0;

    wattron(commandWindow, COLOR_PAIR(4));
    mvwprintw(commandWindow, 0, 0, text.c_str());
    wattroff(commandWindow, COLOR_PAIR(4));

    wrefresh(commandWindow);
}

void CommandLine::clear()
/**
Clears all commands from the command line

Returns:
    void
 */

{
    if (line.length() > 0)
    {
        werase(commandWindow);
        wrefresh(commandWindow);
        line = "";
    }
}

void CommandLine::clearCmd()
/**
Clears all info and error messages from the command line

Returns:
    void
 */

{
    cmdTxt = "";
    cursorX = 0;
    updateCommand();
}

vector<string> CommandLine::parseCommand()
/**
Parses through the command if it has been entered

Returns:
    void
 */

{
    vector<string> commands = {"", ""};
    if (cmdTxt == "save" || cmdTxt == "linenums" || cmdTxt == "quit" || cmdTxt == "switch" || cmdTxt == "autocomplete")
    {
        commands[0] = cmdTxt;
    }

    string command;
    for (int x = 0; x < (int)cmdTxt.length(); x++)
    {
        if (cmdTxt[x] == ' ')
        {
            command = cmdTxt.substr(0, x);
            if (command == "saveas" || command == "switch")
            {
                commands[0] = command;
                commands[1] = cmdTxt.substr(x + 1, cmdTxt.length());
            }
            else if (command == "tabsize")
            {
                commands[0] = command;
                string size = cmdTxt.substr(x + 1);
                if (isdigit(size[0]) and size.length() == 1)
                {
                    commands[1] = size;
                }
            }
        }
    }

    if (cmdTxt == "tabsize" || (commands[0] == "tabsize" && commands[1].length() == 0))
    {
        displayError("Invalid Tabsize");
    }
    if (commands[0].length() == 0 and line.length() == 0)
    {
        displayError("Invalid Command. (Enter \"myst -help\" in your terminal to see a list of commands)");
    }

    clearCmd();
    return commands;
}
