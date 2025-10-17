#pragma once
#include "buttons.h"

Button::Button(string textParam, string toggleParam)
/**
Button Class Constructor

Vars:
    (string) text: text inside the button
    (string) toggle: toggle that can change based on conditions

Returns:
    void
 */

{
    text = textParam;
    toggle = toggleParam;
}

string Button::getText()
/**
text Getter

Returns:
    string
 */

{
    return text;
}

int Button::getY()
/**
y Getter

Returns:
    int
 */

{
    return y;
}

string Button::getToggle()
/**
toggle Getter

Returns:
    string
 */

{
    return toggle;
}

void Button::setToggle(string toggleParam)
/**
toggle Setter

Args:
    (int) toggleParam: new toggle

Returns:
    void
 */

{
    toggle = toggleParam;
}

ButtonsList::ButtonsList()
/**
ButtonList Class Constructor

Returns:
    void
 */

{
}

void ButtonsList::newButtonList(vector<Button> buttonsParam)
/**
ButtonList Class Constructor

Vars:
    (vector<Button>) buttons: vector of buttons
    (int) currentButton: Current button being highlighted

Returns:
    void
 */

{
    buttons = buttonsParam;
    currentButton = 0;
}

vector<Button> ButtonsList::getButtons()
/**
buttons Getter

Returns:
    vector<Button>
 */

{
    return buttons;
}

void ButtonsList::setButtons(vector<Button> buttonsParam)
/**
buttons Setter

Args:
    (vector<Button>) arg: new buttons vector

Returns:
    void
 */

{
    buttons = buttonsParam;
}

int ButtonsList::getCurrentButton()
/**
currentButton Getter

Returns:
    int
 */

{
    return currentButton;
}

void ButtonsList::setCurrentButton(int btn)
/**
currentButton Setter

Args:
    (int) btn: new currentButton

Returns:
    void
 */

{
    currentButton = btn;
}

void ButtonsList::displayButtons(WINDOW *win, int height)
/**
Displays all the buttons

Args:
    (WINDOW*) win: window to display on
    (int) height: Height of the window

Returns:
    void
 */

{
    werase(win);
    int inc = height / 2 - 9;
    for (Button button : buttons)
    {
        if (inc - (height / 2 - 9) == currentButton * 3)
        {
            wattron(win, COLOR_PAIR(14));
        }
        string text = button.getText();
        if (button.getToggle() != "")
        {
            text += " = " + button.getToggle();
        }
        mvwprintw(win, inc, 10, text.c_str(), "%s");
        wattroff(win, COLOR_PAIR(14));
        inc += 3;
    }
}

void ButtonsList::displayFiles(WINDOW *win, string directory)
/**
Displays list of files as buttons

Args:
    (WINDOW*) win: window to display on
    (string) directory: directory of the files to display
    (int) height: Height of the window

Returns:
    void
 */

{
    werase(win);
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 0, 10, "Current Directory:");
    wattroff(win, COLOR_PAIR(1));
    mvwprintw(win, 1, 10, directory.c_str(), "%s");
    mvwprintw(win, 2, 10, "Press CTRL-T To Exit");

    int inc = 4;
    for (Button button : buttons)
    {
        if (inc - 4 == currentButton)
        {
            wattron(win, COLOR_PAIR(14));
        }
        string text = button.getText();
        int getSlashLoc = text.find_last_of("/");
        mvwprintw(win, inc, 10, text.substr(getSlashLoc, text.length() - getSlashLoc).c_str(), "%s");
        wattroff(win, COLOR_PAIR(14));
        inc += 1;
    }
}

void ButtonsList::upArrow(int &scroll)
/**
Handles what to do when up arrow is pressed

Args:
    (int) height: Height of the window
    (int) scroll: how much to scroll the pad down

Returns:
    void
 */

{
    if (currentButton > 0)
    {
        currentButton -= 1;
    }
    if (currentButton < scroll)
    {
        scroll -= 1;
    }
}

void ButtonsList::downArrow(int height, int &scroll)
/**
Handles what to do when down arrow is pressed

Args:
    (int) height: Height of the window
    (int) scroll: how much to scroll the pad down

Returns:
    void
 */

{
    if (currentButton < (int)buttons.size() - 1)
    {
        currentButton += 1;
    }
    if (currentButton >= height + scroll)
    {
        scroll += 1;
    }
}

int ButtonsList::enter()
/**
Handles what to do when enter is pressed

Returns:
    int
 */

{
    return currentButton;
}
