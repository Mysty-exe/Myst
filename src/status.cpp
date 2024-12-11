#pragma once
#include "status.h"

StatusBar::StatusBar()
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
}

StatusBar::StatusBar(int w, int h)
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
    line = "";
    date = "";
    state = "";
    findTxt = "";
    replaceTxt = "";
    filenameTxt = "";
    confirmTxt = "";
    matches = 0;
    error = false;
    modified = false;
    statusWindow = newwin(1, width, height - 1, 0);
}

int StatusBar::getWidth()
/**
Width Getter Function

Returns:
    int
 */

{
    return width;
}

void StatusBar::setWidth(int w)
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

int StatusBar::getCursorX()
/**
CursorX Getter Function

Returns:
    int
 */

{
    return cursorX;
}

string StatusBar::getState()
/**
state Getter Function

Returns:
    string
 */

{
    return state;
}

void StatusBar::setState(string s)
/**
state Setter Function

Args:
    (string) s: New state of the command line

Returns:
    void
 */

{
    state = s;
}

string StatusBar::getFindTxt()
/**
findTxt Getter Function

Returns:
    string
 */

{
    return findTxt;
}

string StatusBar::getReplaceTxt()
/**
replaceTxt Getter Function

Returns:
    string
 */

{
    return replaceTxt;
}

void StatusBar::setMatches(int m)
/**
matches Setter Function

Args:
    (int) m: New m

Returns:
    void
 */

{
    matches = m;
}

string StatusBar::getFilename()
/**
CursorX Getter Function

Returns:
    int
 */

{
    return filenameTxt;
}

void StatusBar::setFilename(string filename)
/**
filename Setter Function

Args:
    (string) filename: New filename

Returns:
    void
 */

{
    filenameTxt = filename;
}

string StatusBar::getConfirm()
/**
confirm Getter Function

Returns:
    string
 */

{
    return confirmTxt;
}

void StatusBar::updateDimensions()
/**
Updates size of window if terminal has been changed

Returns:
    void
 */

{
    getmaxyx(stdscr, height, width);
    delwin(statusWindow);
    statusWindow = newwin(1, width, height - 1, 0);
    getmaxyx(statusWindow, height, width);
    keypad(statusWindow, true);
    keypad(statusWindow, true);
    wrefresh(statusWindow);
}

bool StatusBar::endOfLine()
/**
Checks if cursor is at the end of the line

Returns:
    bool
 */

{
    if (state == "find")
    {
        return cursorX >= (int)findTxt.length() - 1;
    }
    else if (state == "replace")
    {
        return cursorX >= (int)replaceTxt.length() - 1;
    }
    else if (state == "save as")
    {
        return cursorX >= (int)filenameTxt.length() - 1;
    }
    else if (state == "save" || state == "quit")
    {
        return cursorX < 1;
    }

    return false;
}

void StatusBar::addCharacter(char character)
/**
Adds a character to the command line

Args:
    (char) character: Character you want to add

Returns:
    void
 */

{
    if (state == "find")
    {
        if ((int)findTxt.length() < width / 5)
        {
            cursorX += 1;
            findTxt = findTxt + character;
        }
    }
    else if (state == "replace")
    {
        if ((int)replaceTxt.length() < width / 5)
        {
            cursorX += 1;
            replaceTxt = replaceTxt + character;
        }
    }
    else if (state == "save as")
    {
        if ((int)filenameTxt.length() < width)
        {
            cursorX += 1;
            filenameTxt = filenameTxt + character;
        }
    }
    else if (state == "quit" || state == "save")
    {
        cursorX += 1;
        confirmTxt = character;
    }
}

void StatusBar::insertCharacter(char character)
/**
Insert a character in between two characters in the command line

Args:
    (char) character: Character to insert

Returns:
    void
 */

{
    if (state == "find")
    {
        if ((int)findTxt.length() < width / 5)
        {
            findTxt = findTxt.substr(0, cursorX) + character + findTxt.substr(cursorX, findTxt.length());
            cursorX += 1;
        }
    }
    else if (state == "replace")
    {
        if ((int)replaceTxt.length() < width / 5)
        {
            replaceTxt = replaceTxt.substr(0, cursorX) + character + replaceTxt.substr(cursorX, replaceTxt.length());
            cursorX += 1;
        }
    }
    else if (state == "save as")
    {
        if ((int)filenameTxt.length() < width / 5)
        {
            filenameTxt = filenameTxt.substr(0, cursorX) + character + filenameTxt.substr(cursorX, filenameTxt.length());
            cursorX += 1;
        }
    }
}

void StatusBar::backspace()
/**
Deletes a character in the command line

Returns:
    void
 */

{
    if (state == "find")
    {
        if (cursorX > 0)
        {
            cursorX -= 1;
            findTxt = findTxt.erase(cursorX, 1);
        }
    }
    else if (state == "replace")
    {
        if (cursorX > 0)
        {
            cursorX -= 1;
            replaceTxt = replaceTxt.erase(cursorX, 1);
        }
    }
    else if (state == "save as")
    {
        if (cursorX > 0)
        {
            cursorX -= 1;
            filenameTxt = filenameTxt.erase(cursorX, 1);
        }
    }
    else if (state == "quit" || state == "save")
    {
        if (cursorX > 0)
        {
            cursorX -= 1;
            confirmTxt = confirmTxt.erase(cursorX, 1);
        }
    }
}

void StatusBar::tab()
/**
Handles if tab is pressed

Returns:
    void
 */

{
    if (state == "find")
    {
        cursorX = replaceTxt.length();
        state = "replace";
    }
    else if (state == "replace")
    {
        cursorX = findTxt.length();
        state = "find";
    }
}

bool StatusBar::enter()
/**
Passes the command to "parseCommand()" and deletes it

Returns:
    void
 */

{
    if (state == "replace")
    {
        return true;
    }
    return false;
}

void StatusBar::leftArrow()
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

void StatusBar::rightArrow()
/**
Moves cursor to the right of the lin if cursor isn't already at the end of the command line

Returns:
    void
 */

{
    if (state == "find")
    {
        if (cursorX <= (int)findTxt.length() - 1)
        {
            cursorX++;
        }
    }
    else if (state == "replace")
    {
        if (cursorX <= (int)replaceTxt.length() - 1)
        {
            cursorX++;
        }
    }
    else if (state == "save as")
    {
        if (cursorX <= (int)filenameTxt.length() - 1)
        {
            cursorX++;
        }
    }
}

string StatusBar::getDateString()
/**
date Getter Function

Returns:
    string
 */

{
    return date;
}

void StatusBar::getDate()
/**
Gets the current date

Returns:
    void
 */

{
    std::time_t currentTime = std::time(nullptr);
    std::tm *localTime = std::localtime(&currentTime);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%A %d, %Y %H:%M:%S", localTime);
    if (date != string(buffer))
    {
        modified = true;
        date = string(buffer);
    }
}

void StatusBar::displayDate()
/**
Display the date

Returns:
    void
 */

{
    mvwprintw(statusWindow, 0, width - (int)date.length(), date.c_str(), "%s");
}

void StatusBar::setInfo(string text, bool err = false)
/**
Displays an info message with colours in the command line

Args:
    (string) text: Text to display in the info message

Returns:
    void
 */

{
    error = err;
    if (line != text)
    {
        modified = true;
        line = text;
    }
}

void StatusBar::update()
/**
Updates the statusbar

Returns:
    void
 */

{
    getDate();
    if (modified)
    {
        curs_set(0);
        modified = false;
        clear();
        displayDate();
        if (error)
        {
            wattron(statusWindow, COLOR_PAIR(4));
        }
        else
        {
            wattron(statusWindow, COLOR_PAIR(2));
        }
        mvwprintw(statusWindow, 0, 0, line.c_str(), "%s");
        wattroff(statusWindow, COLOR_PAIR(2));
        wattroff(statusWindow, COLOR_PAIR(4));
        wrefresh(statusWindow);
    }
}

void StatusBar::findAndReplace()
/**
Handles when ctrl-f is pressed

Returns:
    void
 */

{
    clear();

    wattron(statusWindow, COLOR_PAIR(2));
    wprintw(statusWindow, "Find: ");

    wattroff(statusWindow, COLOR_PAIR(2));
    wprintw(statusWindow, findTxt.c_str(), "%s");
    wprintw(statusWindow, "   ");

    wattron(statusWindow, COLOR_PAIR(2));
    wprintw(statusWindow, "Replace: ");

    wattroff(statusWindow, COLOR_PAIR(2));
    wprintw(statusWindow, replaceTxt.c_str(), "%s");

    wattron(statusWindow, COLOR_PAIR(2));
    mvwprintw(statusWindow, 0, width - (9 + to_string(matches).length()), "Matches: ");

    wattroff(statusWindow, COLOR_PAIR(2));
    mvwprintw(statusWindow, 0, width - to_string(matches).length(), to_string(matches).c_str(), "%s");

    if (state == "find")
    {
        wmove(statusWindow, 0, cursorX + 6);
    }
    else if (state == "replace")
    {
        wmove(statusWindow, 0, cursorX + findTxt.length() + 18);
    }
    wrefresh(statusWindow);
}

void StatusBar::resetStatus()
/**
Resets the status bar

Returns:
    void
 */

{
    state = "";
    findTxt = "";
    replaceTxt = "";
    filenameTxt = "";
    confirmTxt = "";
    matches = 0;
    cursorX = 0;
}

void StatusBar::saveAs()
/**
Save as function to save as a new file in statusbar

Returns:
    void
 */

{
    clear();

    wattron(statusWindow, COLOR_PAIR(2));
    wprintw(statusWindow, "File Name: ");
    wattroff(statusWindow, COLOR_PAIR(2));
    mvwprintw(statusWindow, 0, 11, filenameTxt.c_str(), "%s");

    wmove(statusWindow, 0, cursorX + 11);
    wrefresh(statusWindow);
}

void StatusBar::confirm()
/**
confirm function to confirm an action in statusbar

Returns:
    void
 */

{
    clear();

    wattron(statusWindow, COLOR_PAIR(2));
    if (state == "quit")
    {
        wprintw(statusWindow, "Quit Without Saving? (y/n): ");
        wattroff(statusWindow, COLOR_PAIR(2));
        mvwprintw(statusWindow, 0, 28, confirmTxt.c_str(), "%s");
        wmove(statusWindow, 0, cursorX + 28);
    }
    else if (state == "save")
    {
        wprintw(statusWindow, "Overwrite File? (y/n): ");
        wattroff(statusWindow, COLOR_PAIR(2));
        mvwprintw(statusWindow, 0, 23, confirmTxt.c_str(), "%s");
        wmove(statusWindow, 0, cursorX + 23);
    }
    wrefresh(statusWindow);
}

void StatusBar::clear()
/**
Clears all commands from the command line

Returns:
    void
 */

{
    werase(statusWindow);
}
