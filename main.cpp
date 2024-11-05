#include <ncurses/ncurses.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

void rewriteScreen(WINDOW *textWin, WINDOW *lineWin, vector<string> lines, int x, int y, int max, int height)
{
    int lineNum = 0;
    int lineY = 0;
    int tempX, tempY;
    tempX = tempY = 0;

    werase(textWin);
    werase(lineWin);
    wmove(textWin, tempY, tempX);
    wmove(lineWin, 0, 0);

    for (const string line : lines)
    {
        lineNum++;
        wmove(lineWin, tempY, 0);
        mvwprintw(lineWin, lineY, 0, to_string(lineNum).c_str());

        string copy = line;
        while (true)
        {
            lineY++;
            if (copy.length() <= max - 1)
            {
                mvwprintw(textWin, tempY, tempX, copy.c_str());
                tempY++;
                break;
            }
            else
            {
                mvwprintw(textWin, tempY, tempX, copy.substr(0, max - 1).c_str());
                copy.erase(0, max - 1);
                tempY++;
            }
        }
    }
    for (int n = tempY; n < height; n++)
    {
        mvwprintw(lineWin, n, 0, "~");
    }

    wmove(textWin, y, x);
    wrefresh(lineWin);
    wrefresh(textWin);
}

int getCurrentX(int x, int max)
{
    while (true)
    {
        if (x >= max)
        {
            x -= max;
        }
        else
        {
            break;
        }
    }
    return x;
}

int getIncrement(int x, int max)
{
    int counter = 1;
    while (true)
    {
        if (x >= max)
        {
            x -= max;
            counter += 1;
        }
        else
        {
            break;
        }
    }
    return counter;
}

main(int argc, char **argv)
{
    int width, height, currentX, currentLine;
    int cursorX, cursorY = 0;
    width = height = 0;
    cursorX = cursorY = 0;
    currentX = currentLine = 0;

    vector<string> lines = {""};

    initscr();

    getmaxyx(stdscr, height, width);
    noecho();
    raw();

    WINDOW *linesWindow = newwin(height, 3, 0, 0);
    WINDOW *textWindow = newwin(height, width, 0, 3);
    keypad(textWindow, true);

    rewriteScreen(textWindow, linesWindow, lines, 0, 0, width, height);

    int c;
    while ((c = wgetch(textWindow)) != 27)
    {
        if (c >= 32 && c <= 126)
        {
            if (currentX == lines.at(currentLine).length())
            {
                lines.at(currentLine) = lines.at(currentLine) + char(c);
                if (cursorX < width - 1)
                {
                    cursorX++;
                }
                else
                {
                    cursorX = 1;
                    cursorY++;
                }
                currentX++;
            }
            else
            {
                lines.at(currentLine) = lines.at(currentLine).substr(0, currentX) + char(c) + lines.at(currentLine).substr(currentX, lines.at(currentLine).length());
                currentX++;
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

        switch (c)
        {
        case 8:
            if (cursorX > 0)
            {
                lines.at(currentLine) = lines.at(currentLine).erase(currentX - 1, 1);
                cursorX--;
                currentX--;
            }
            else if (cursorY > 0)
            {
                if (cursorX == 0)
                {
                    if (currentX == 0)
                    {
                        int x = getCurrentX(lines.at(currentLine - 1).length(), width - 1);
                        currentX = lines.at(currentLine - 1).length();
                        lines.at(currentLine - 1) = lines.at(currentLine - 1) + lines.at(currentLine);
                        lines.erase(lines.begin() + currentLine);
                        currentLine--;
                        cursorX = x;
                        cursorY--;
                    }
                    else
                    {
                        lines.at(currentLine) = lines.at(currentLine).erase(currentX - 1, 1);
                        currentX--;
                        cursorY--;
                        cursorX = width - 2;
                    }
                }
            }

            break;
        case 10:
            if (currentX == 0)
            {
                lines.insert(lines.begin() + currentLine, "");
                currentLine++;
                currentX = 0;
            }
            else if (currentX == lines.at(currentLine).length())
            {
                lines.insert(lines.begin() + currentLine + 1, "");
                currentLine++;
                currentX = 0;
            }
            else
            {
                string text = lines.at(currentLine).substr(currentX, lines.at(currentLine).length() - 1);
                cout << text << endl;
                lines.at(currentLine) = lines.at(currentLine).substr(0, currentX);
                lines.insert(lines.begin() + currentLine + 1, text);
                currentLine++;
                currentX = 0;
            }
            cursorY++;
            cursorX = 0;
            break;
        case KEY_UP:
            if (currentLine > 0)
            {
                cursorY -= getIncrement(currentX, width - 1);
                cursorX = getCurrentX(lines.at(currentLine - 1).length(), width - 1);
                currentX = lines.at(currentLine - 1).length();
                currentLine--;
            }
            break;
        case KEY_DOWN:
            if (currentLine + 1 < lines.size())
            {
                int y = 0;
                int x = ceil((lines.at(currentLine + 1).length()) * 1.0 / (width - 1) * 1.0);
                if (x == 0)
                {
                    x = 1;
                }
                else
                {
                    int r = ceil((lines.at(currentLine).length()) * 1.0 / (width - 1) * 1.0);
                    if (r == 0)
                    {
                        r += 1;
                    }
                    y = r - getIncrement(currentX, width - 1);
                }

                cout << lines.at(currentLine).length() << ", " << getIncrement(currentX, width - 1);
                cursorY += y + x;
                cursorX = getCurrentX(lines.at(currentLine + 1).length(), width - 1);
                currentX = lines.at(currentLine + 1).length();
                currentLine++;
            }
            break;
        case KEY_LEFT:
            if (currentX > 0)
            {
                currentX--;
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
            break;
        case KEY_RIGHT:
            if (currentX < lines.at(currentLine).length())
            {
                currentX++;
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
            break;
        }

        // cout << cursorX << " " << cursorY << ", " << currentX << " " << currentLine << endl;
        getmaxyx(textWindow, height, width);
        // getyx(textWindow, cursorY, cursorX);
        rewriteScreen(textWindow, linesWindow, lines, cursorX, cursorY, width, height);
    }
    endwin();

    return 0;
}
