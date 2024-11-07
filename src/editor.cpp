#pragma once
#include "editor.h"

Editor::Editor()
/**
Editor Class Constructor

Vars:
    (int) width: width of the editor
    (int) height: height of the editor
    (int) lineX: index that the cursor is on (disregards wrapping)
    (int) lineY: current line that the cursor is on (disregards wrapping)
    (int) cursorX: index that the cursor is on (regards wrapping)
    (int) cursorY: current line that the cursor is on (regards wrapping)

Returns:
    void
 */
{
    width = height = 0;
    lineX = lineY = 0;
    cursorX = cursorY = 0;
}

void Editor::setFile(File f)
/**
File Setter Function

Args:
    (File) f: File object

Returns:
    void
 */

{
    file = f;
}

int Editor::getWidth()
/**
Width Getter Function

Returns:
    int
 */

{
    return width;
}

void Editor::setWidth(int w)
/**
Width Setter Function

Args:
    (int) w: width of the editor

Returns:
    void
 */

{
    width = w;
}

int Editor::getHeight()
/**
Height Getter Function

Returns:
    int
 */

{
    return height;
}

void Editor::setHeight(int h)
/**
Height Setter Function

Args:
    (int) h: height of the editor

Returns:
    void
 */

{
    height = h;
}

bool Editor::endOfLine()
/**
Checks if cursor is at the endo of a line (regardless of wrapping)

Returns:
    bool
 */

{
    return (lineX == (int)file.getLine(lineY).length());
}

void Editor::addCharacter(char character)
/**
Adds a character to a line

Args:
    (char) character: Adds a character

Returns:
    void
 */

{
    file.addChar(lineY, character);
    if (cursorX < width - 1) // Check if cursor is at the end of a line
    {
        cursorX++;
    }
    else
    {
        cursorX = 1;
        cursorY++;
    }
    lineX++;
}

void Editor::insertCharacter(char character)
/**
Inserts a character into a line in a specific index based on the cursor

Args:
    (char character) character: Character to insert

Returns:
    void
 */

{
    file.insertChar(lineY, lineX, character);
    lineX++;
    if (cursorX < width - 1) // Check if cursor is at the end of a line
    {
        cursorX++;
    }
    else
    {
        cursorX = 1;
        cursorY++;
    }
}

void Editor::backspace()
/**
Deletes previous character if cursor is not at the beginning of a line.
Else cursor goes to the end of previous line and appends the line after it.

Returns:
    void
 */

{
    if (cursorX > 0)
    {
        file.delChar(lineY, lineX - 1);
        cursorX--;
        lineX--;
    }
    else if (cursorY > 0)
    {
        if (cursorX == 0)
        {
            if (lineX == 0)
            {
                lineY--;
                cursorX = getWrappedX(file.getLine(lineY).length());
                lineX = file.getLine(lineY).length();
                file.addStr(lineY, file.getLine(lineY + 1));
                file.delLine(lineY);
                cursorY--;
            }
            else
            {
                file.delChar(lineY, lineX - 1);
                cursorX = width - 2;
                cursorY--;
                lineX--;
            }
        }
    }
}

void Editor::enter()
/**
Just moves the cursor to a new line if the cursor is at the end of the line.
Else moves the cursor a new line with the last part of the line (after the cursor) being the new line.

Returns:
    void
 */
{
    if (lineX == 0)
    {
        file.insertLine(lineY, "");
    }
    else if (endOfLine())
    {
        file.insertLine(lineY + 1, "");
    }
    else
    {
        string text = file.getLine(lineY).substr(lineX, file.getLine(lineY).length() - 1);
        file.setLine(lineY, file.getLine(lineY).substr(0, lineX));
        file.insertLine(lineY + 1, text);
    }

    cursorY++;
    cursorX = 0;
    lineX = 0;
    lineY++;
}

void Editor::upArrow()
/**
Moves the cursor to the end of the previous line

Returns:
    void
 */

{
    if (lineY > 0)
    {
        lineY--;
        cursorY -= getWrappedY(lineX);
        cursorX = getWrappedX(file.getLine(lineY).length());
        lineX = file.getLine(lineY).length();
    }
}

void Editor::downArrow()
/**
Moves the cursor to the end of the following line

Returns:
    void
 */

{
    // Check if cursor isn't on the last line
    if (lineY + 1 < (int)file.getLines().size())
    {
        int downIncrement = 0;
        int nextLineWrappedWidth = ceil((file.getLine(lineY + 1).length()) * 1.0 / (width - 1) * 1.0);
        nextLineWrappedWidth = (nextLineWrappedWidth == 0) ? 1 : nextLineWrappedWidth;

        int currentLineWrappedWidth = ceil((file.getLine(lineY).length()) * 1.0 / (width - 1) * 1.0);
        currentLineWrappedWidth = (currentLineWrappedWidth == 0) ? 1 : currentLineWrappedWidth;
        downIncrement = currentLineWrappedWidth - getWrappedY(lineX);

        cursorY += downIncrement + nextLineWrappedWidth;
        cursorX = getWrappedX(file.getLine(lineY + 1).length());
        lineX = file.getLine(lineY + 1).length();
        lineY++;
    }
}

void Editor::leftArrow()
/**
Moves cursor to the left if its not already at the beginning of the line (disregards wrapping)

Returns:
    void
 */

{
    if (lineX > 0)
    {
        lineX--;
        if (cursorX > 0)
        {
            cursorX--;
        }
        else
        {
            cursorX = width - 2;
            cursorY--;
        }
    }
}

void Editor::rightArrow()
/**
Moves cursor to the right of the lin if cursor isn't already at the end of the line (disregards wrapping)

Returns:
    void
 */

{
    if (not endOfLine())
    {
        lineX++;
        // Check if cursor is not in a "wrapped" line
        if (cursorX < width - 1)
        {
            cursorX++;
        }
        else
        {
            cursorX = 1;
            cursorY++;
        }
    }
}

void Editor::writeToScreen(WINDOW *textWin, WINDOW *lineWin)
/**
Clears the screen and writes each line based on the File object and refreshes the screen at the end

Args:
    (WINDOW*) textWin: Text window where the text of the file goes
    (WINDOW*) lineWin: Line Window where the line numbers go

Returns:
    void
 */

{
    int lineNum = 0;

    int tempX, tempY;
    tempX = tempY = 0;

    werase(textWin);
    werase(lineWin);

    wmove(textWin, tempY, tempX);
    wmove(lineWin, 0, 0);

    for (const string line : file.getLines())
    {
        lineNum++;
        wmove(lineWin, tempY, 0);
        mvwprintw(lineWin, tempY, 0, to_string(lineNum).c_str());

        string copiedLine = line;
        while (true)
        {
            if ((int)copiedLine.length() <= (width - 1))
            {
                mvwprintw(textWin, tempY, tempX, copiedLine.c_str());
                tempY++;
                break;
            }
            else
            {
                mvwprintw(textWin, tempY, tempX, copiedLine.substr(0, width - 1).c_str());
                copiedLine.erase(0, width - 1);
                tempY++;
            }
        }
    }

    for (int n = tempY; n < height; n++)
    {
        mvwprintw(lineWin, n, 0, "~");
    }

    wmove(textWin, cursorY, cursorX);
    wrefresh(lineWin);
    wrefresh(textWin);
}

int Editor::getWrappedX(int x)
/**
Gets the cursor index of a wrapped line (line that exceeds the width) if it was at the last character

Args:
    (int) x: Current index of the cursor

Returns:
    int
 */

{
    while (true)
    {
        if (x >= (width - 1))
        {
            x -= (width - 1);
        }
        else
        {
            break;
        }
    }
    return x;
}

int Editor::getWrappedY(int x)
/**
Gets the number of lines you'll see in the terminal of a wrapped line (line that exceeds the width)

Args:
    (int) x: Current index of the cursor

Returns:
    int
 */

{
    int counter = 1;
    while (true)
    {
        if (x >= width - 1)
        {
            x -= (width - 1);
            counter += 1;
        }
        else
        {
            break;
        }
    }
    return counter;
}
