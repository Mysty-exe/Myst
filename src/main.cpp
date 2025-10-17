#include <ncurses.h>
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <limits.h>
#include <string>
#include <cstring>
#include "app.h"

std::string getProjectPathFromEnv()
{
    const char *path = std::getenv("MYST_PROJECT_PATH");
    if (path)
    {
        return std::string(path);
    }
    return filesystem::current_path();
}

int main(int argc, char **argv)
{
    std::string projectPath = getProjectPathFromEnv();
    if (projectPath.empty())
    {
        std::cout << "Project path is not set in the environment variable." << std::endl;
    }

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

    App app(w, h, projectPath);
    app.init();

    if (argc < 3)
    {
        // Get file from arguments passed when program is run
        string file = argc > 1 ? argv[1] : "";
        if (file == "-help")
        {
            endwin();
            string text;
            fstream readFile(projectPath + "/resources/help.txt");
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
