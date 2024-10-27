#include <ncurses/ncurses.h>

int main(int argc, char **argv)
{
    initscr();

    printw("Hello World");

    refresh();

    getch();

    return 0;
}