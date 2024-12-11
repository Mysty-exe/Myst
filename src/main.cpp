#include <ncurses.h>
#include <iostream>
#include <filesystem>
#include <string.h>
#include "app.h"

int main(int argc, char **argv)
{
    cout << "\033]0;Myst Editor\007";

    // Setup ncurses
    initscr();

    refresh();

    int w, h;
    getmaxyx(stdscr, h, w);

    noecho();
    cbreak();
    raw();
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    use_default_colors();
    start_color();
    init_color(COLOR_BLUE, 31, 239, 345);
    init_color(COLOR_RED, 957, 267, 306);
    init_color(COLOR_GREEN, 314, 784, 471);
    init_color(COLOR_YELLOW, 980, 855, 369);
    init_color(COLOR_MAGENTA, 306, 165, 518);
    init_color(COLOR_CYAN, 0, 545, 545);
    init_color(COLOR_BLACK, 0, 0, 0);

    App app(w, h);
    app.init();

    if (argc < 3)
    {
        endwin();
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

        else if (File::fileError(file) && file != "")
        {
            cout << "Unknown File Location." << endl;
        }

        else
        {
            app.displayLogo();
            app.stateLoop(file);
        }
    }
    else
    {
        endwin();
        cout << "Unknown Command." << endl;
    }

    endwin();

    return 0;
}
