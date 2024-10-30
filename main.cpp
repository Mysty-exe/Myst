#include <ncurses/ncurses.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

main(int argc, char **argv)
{
    int width, height = 0;
    int cursorX, cursorY = 0;
    vector<string> lines = {""};

    initscr();
    keypad(stdscr, true);
    noecho();

    while (true)
    {
        int c = getch();

        if (c >= 32 && c <= 126)
        {
            if (cursorX == lines.at(cursorY).length())
            {
                addch(char(c));
                lines.at(cursorY) = lines.at(cursorY) + char(c);
            }
            else
            {
                insch(char(c));
                move(cursorY, cursorX + 1);
                lines.at(cursorY) = lines.at(cursorY).substr(0, cursorX) + char(c) + lines.at(cursorY).substr(cursorX, lines.at(cursorY).length());
            }
        }

        switch (c)
        {
        case 8:
            move(cursorY, cursorX - 1);
            delch();
            if (cursorX == 0)
            {
                move(cursorY - 1, cursorX);
            }
            break;
        case 10:
            if (cursorX == 0)
            {
                lines.insert(lines.begin() + cursorY, "");
                insertln();
                move(cursorY + 1, 0);
            }
            else if (cursorX == lines.at(cursorY).length())
            {
                move(cursorY + 1, 0);
                lines.insert(lines.begin() + cursorY + 1, "");
                insertln();
            }
            else
            {
                string text = lines.at(cursorY).substr(cursorX, lines.at(cursorY).length() - 1);
                clrtoeol();
                move(cursorY + 1, 0);
                lines.insert(lines.begin() + cursorY + 1, text);
                insertln();
                printw(text.c_str());
                move(cursorY + 1, 0);
                refresh();
            }

            break;
        case KEY_UP:
            if (cursorY - 1 >= 0)
            {
                if (cursorX > lines.at(cursorY - 1).length())
                {
                    move(cursorY - 1, lines.at(cursorY - 1).length());
                }
                else
                {
                    move(cursorY - 1, cursorX);
                }
            }
            break;
        case KEY_DOWN:
            if (cursorY + 1 < lines.size())
            {
                if (cursorX > lines.at(cursorY + 1).length())
                {
                    move(cursorY + 1, lines.at(cursorY + 1).length());
                }
                else
                {
                    move(cursorY + 1, cursorX);
                }
            }

            break;
        case KEY_LEFT:
            move(cursorY, cursorX - 1);
            break;
        case KEY_RIGHT:
            if (cursorX < lines.at(cursorY).length())
            {
                move(cursorY, cursorX + 1);
            }
            break;
        }

        getmaxyx(stdscr, height, width);
        getyx(stdscr, cursorY, cursorX);
    }
    endwin();

    return 0;
}
