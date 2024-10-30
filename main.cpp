#include <ncurses/ncurses.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void writeLineNums(int height, vector<string> lines, int x, int y)
{
    for (int n = 0; n < height; n++)
    {
        move(n, 0);
        printw("~");
    }
    refresh();
}

void rewriteScreen(WINDOW *win, vector<string> lines, int x, int y, bool highlight = false)
{
    int tempX, tempY;
    tempX = tempY = 0;

    wclear(win);
    move(tempY, tempX);

    for (const string &line : lines)
    {
        mvwprintw(win, tempY, tempX, line.c_str());
        tempY++;
    }

    move(y, x);
}

main(int argc, char **argv)
{
    int width, height;
    int cursorX, cursorY = 0;
    width = height = 0;
    cursorX = cursorY = 0;
    vector<string> lines = {""};

    initscr();
    noecho();
    raw();
    getmaxyx(stdscr, height, width);

    WINDOW *textWindow = newwin(height, width, 0, 3);
    keypad(textWindow, true);

    writeLineNums(height, lines, cursorX, cursorY);

    int c;
    while ((c = wgetch(textWindow)) != 27)
    {
        if (c >= 32 && c <= 126)
        {
            if (cursorX == lines.at(cursorY).length())
            {
                waddch(textWindow, char(c));
                lines.at(cursorY) = lines.at(cursorY) + char(c);
            }
            else
            {
                winsch(textWindow, char(c));
                wmove(textWindow, cursorY, cursorX + 1);
                lines.at(cursorY) = lines.at(cursorY).substr(0, cursorX) + char(c) + lines.at(cursorY).substr(cursorX, lines.at(cursorY).length());
            }
        }

        switch (c)
        {
        case 8:
            if (cursorX > 0)
            {
                lines.at(cursorY) = lines.at(cursorY).erase(cursorX - 1, 1);
                wmove(textWindow, cursorY, cursorX - 1);
                wdelch(textWindow);
            }
            if (cursorY > 0)
            {
                if (cursorX == 0)
                {
                    int x = lines.at(cursorY - 1).length();
                    wdeleteln(textWindow);
                    wmove(textWindow, cursorY - 1, x);
                    lines.at(cursorY - 1) = lines.at(cursorY - 1) + lines.at(cursorY);
                    wprintw(textWindow, lines.at(cursorY).c_str());
                    lines.erase(lines.begin() + cursorY);
                    wmove(textWindow, cursorY - 1, x);
                }
            }
            break;
        case 10:
            if (cursorX == 0)
            {
                lines.insert(lines.begin() + cursorY, "");
                winsertln(textWindow);
                wmove(textWindow, cursorY + 1, 0);
            }
            else if (cursorX == lines.at(cursorY).length() - 1)
            {
                wmove(textWindow, cursorY + 1, 0);
                lines.insert(lines.begin() + cursorY + 1, "");
                winsertln(textWindow);
                move(cursorY + 1, 0);
            }
            else
            {
                string text = lines.at(cursorY).substr(cursorX, lines.at(cursorY).length() - 1);
                wclrtoeol(textWindow);
                wmove(textWindow, cursorY + 1, 0);
                lines.at(cursorY) = lines.at(cursorY).substr(0, cursorX);
                lines.insert(lines.begin() + cursorY + 1, text);
                winsertln(textWindow);
                wprintw(textWindow, text.c_str());
                wmove(textWindow, cursorY + 1, 0);
            }

            break;
        case KEY_UP:
            if (cursorY - 1 >= 0)
            {
                if (cursorX > lines.at(cursorY - 1).length())
                {
                    wmove(textWindow, cursorY - 1, lines.at(cursorY - 1).length());
                }
                else
                {
                    wmove(textWindow, cursorY - 1, cursorX);
                }
            }
            break;
        case KEY_DOWN:
            if (cursorY + 1 < lines.size())
            {
                if (cursorX > lines.at(cursorY + 1).length())
                {
                    wmove(textWindow, cursorY + 1, lines.at(cursorY + 1).length());
                }
                else
                {
                    wmove(textWindow, cursorY + 1, cursorX);
                }
            }

            break;
        case KEY_LEFT:
            wmove(textWindow, cursorY, cursorX - 1);
            break;
        case KEY_RIGHT:
            if (cursorX < lines.at(cursorY).length())
            {
                wmove(textWindow, cursorY, cursorX + 1);
            }
            break;
        }

        getmaxyx(textWindow, height, width);
        getyx(textWindow, cursorY, cursorX);
    }
    endwin();

    return 0;
}
