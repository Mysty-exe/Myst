#pragma once
#include "app.h"

App::App(int w, int h, string path)
/**
App Class Constructor

Vars:
    (int) MODE: Mode of the editor
    (int) width: width of the editor
    (int) height: height of the editor

Returns:
    void
 */

{
    MODE = 1;
    width = w;
    height = h;
    projectPath = path;
}

void App::init()
/**
Initializes the class

Returns:
    void
 */

{
    settings.getSettings(projectPath);
    Editor editor(width, height);
    StatusBar status(width, height);
    Menu menu(width, height, settings, projectPath);
    editor.setSettings(settings);

    setSettings(settings);
    setEditor(editor);
    setStatus(status);
    setMenu(menu);

    setColor(settings.getColorScheme());

    keypad(stdscr, true);
    keypad(editor.textPad, true);
    keypad(status.statusWindow, true);
    keypad(menu.menuPad, true);
    nodelay(editor.textPad, true);
}

int App::getMode()
/**
MODE Getter

Returns:
    int
 */

{
    return MODE;
}

void App::setMode(int arg)
/**
MODE Setter

Args:
    (int) arg: new MODE

Returns:
    void
 */

{
    MODE = arg;
}

Settings App::getSettings()
/**
Settings object Getter

Returns:
    Settings object
 */

{
    return settings;
}

void App::setSettings(Settings arg)
/**
Settings object Setter

Args:
    (Settings) arg: new Settings object

Returns:
    void
 */

{
    settings = arg;
}

Editor App::getEditor()
/**
Editor object Getter

Returns:
    Editor object
 */

{
    return editor;
}

void App::setEditor(Editor arg)
/**
Editor object Setter

Args:
    (Editor) arg: new Editor object

Returns:
    void
 */

{
    editor = arg;
}

StatusBar App::getStatus()
/**
Status object Getter

Returns:
    Status object
 */

{
    return status;
}

void App::setStatus(StatusBar arg)
/**
Status object Setter

Args:
    (Status) arg: new Status object

Returns:
    void
 */

{
    status = arg;
}

Menu App::getMenu()
/**
Menu object Getter

Returns:
    Menu object
 */

{
    return menu;
}

void App::setMenu(Menu arg)
/**
Menu object Setter

Args:
    (Menu) arg: new Menu object

Returns:
    void
 */

{
    menu = arg;
}

void App::setColor(string color)
/**
Sets colours for the editro

Args:
    (string) color: Color of the editor

Returns:
    void
 */

{
    if (color == "Arctic Horizon")
    {
        init_color(CUSTOM_MAIN, 431, 458, 522);
        init_color(CUSTOM_TEXT, 1000, 1000, 1000);
        init_color(CUSTOM_KEYWORD, 506, 631, 757);
        init_color(CUSTOM_STRING, 639, 745, 549);
        init_color(CUSTOM_COMMENT, 263, 298, 369);
        init_color(CUSTOM_NUMBER, 922, 796, 545);
        init_color(CUSTOM_DELIMITER, 561, 737, 733);
        init_color(CUSTOM_OPERATOR, 561, 737, 733);
        init_color(CUSTOM_SPECIAL, 533, 753, 816);
        init_color(CUSTOM_PUNCTUATION, 561, 737, 733);
        init_color(CUSTOM_OTHER, 298, 337, 416);
        init_color(CUSTOM_ERROR, 749, 380, 416);
        init_color(CUSTOM_HIGHLIGHT, 400, 400, 500);
    }
    else if (color == "Twilight Cascade")
    {
        init_color(CUSTOM_MAIN, 250, 250, 350);
        init_color(CUSTOM_TEXT, 850, 850, 950);
        init_color(CUSTOM_KEYWORD, 700, 300, 900);
        init_color(CUSTOM_STRING, 300, 600, 700);
        init_color(CUSTOM_COMMENT, 400, 400, 600);
        init_color(CUSTOM_NUMBER, 200, 850, 950);
        init_color(CUSTOM_DELIMITER, 700, 600, 900);
        init_color(CUSTOM_OPERATOR, 400, 300, 950);
        init_color(CUSTOM_SPECIAL, 700, 600, 900);
        init_color(CUSTOM_PUNCTUATION, 400, 300, 950);
        init_color(CUSTOM_OTHER, 300, 500, 950);
        init_color(CUSTOM_ERROR, 900, 200, 600);
        init_color(CUSTOM_HIGHLIGHT, 600, 500, 450);
    }
    else if (color == "Crimson Ember")
    {
        init_color(CUSTOM_MAIN, 300, 250, 250);
        init_color(CUSTOM_TEXT, 900, 800, 800);
        init_color(CUSTOM_KEYWORD, 850, 200, 200);
        init_color(CUSTOM_STRING, 750, 400, 400);
        init_color(CUSTOM_COMMENT, 600, 300, 300);
        init_color(CUSTOM_NUMBER, 900, 100, 100);
        init_color(CUSTOM_DELIMITER, 700, 300, 300);
        init_color(CUSTOM_OPERATOR, 800, 300, 300);
        init_color(CUSTOM_SPECIAL, 700, 300, 300);
        init_color(CUSTOM_PUNCTUATION, 600, 250, 200);
        init_color(CUSTOM_OTHER, 750, 200, 200);
        init_color(CUSTOM_ERROR, 950, 200, 100);
        init_color(CUSTOM_HIGHLIGHT, 300, 400, 500);
    }
    else if (color == "Azure Mist")
    {
        init_color(CUSTOM_MAIN, 250, 300, 400);
        init_color(CUSTOM_TEXT, 800, 900, 1000);
        init_color(CUSTOM_KEYWORD, 300, 600, 900);
        init_color(CUSTOM_STRING, 150, 500, 750);
        init_color(CUSTOM_COMMENT, 200, 300, 500);
        init_color(CUSTOM_NUMBER, 400, 650, 950);
        init_color(CUSTOM_DELIMITER, 250, 500, 800);
        init_color(CUSTOM_OPERATOR, 200, 500, 900);
        init_color(CUSTOM_SPECIAL, 500, 700, 900);
        init_color(CUSTOM_PUNCTUATION, 500, 700, 900);
        init_color(CUSTOM_OTHER, 200, 500, 900);
        init_color(CUSTOM_ERROR, 900, 300, 300);
        init_color(CUSTOM_HIGHLIGHT, 100, 200, 300);
    }
    else if (color == "Verdant Glow")
    {
        init_color(CUSTOM_MAIN, 300, 600, 300);
        init_color(CUSTOM_TEXT, 800, 900, 800);
        init_color(CUSTOM_KEYWORD, 500, 700, 300);
        init_color(CUSTOM_STRING, 400, 600, 200);
        init_color(CUSTOM_COMMENT, 300, 500, 300);
        init_color(CUSTOM_NUMBER, 200, 700, 100);
        init_color(CUSTOM_DELIMITER, 600, 700, 500);
        init_color(CUSTOM_OPERATOR, 700, 500, 100);
        init_color(CUSTOM_SPECIAL, 100, 600, 200);
        init_color(CUSTOM_PUNCTUATION, 300, 500, 400);
        init_color(CUSTOM_OTHER, 400, 700, 300);
        init_color(CUSTOM_ERROR, 1000, 200, 200);
        init_color(CUSTOM_HIGHLIGHT, 600, 800, 400);
    }
    else if (color == "Earthy Brown")
    {
        init_color(CUSTOM_MAIN, 300, 180, 90);
        init_color(CUSTOM_TEXT, 600, 400, 200);
        init_color(CUSTOM_KEYWORD, 800, 500, 150);
        init_color(CUSTOM_STRING, 500, 250, 120);
        init_color(CUSTOM_COMMENT, 350, 230, 100);
        init_color(CUSTOM_NUMBER, 700, 400, 80);
        init_color(CUSTOM_DELIMITER, 550, 300, 140);
        init_color(CUSTOM_OPERATOR, 850, 450, 80);
        init_color(CUSTOM_SPECIAL, 420, 210, 90);
        init_color(CUSTOM_PUNCTUATION, 550, 280, 100);
        init_color(CUSTOM_OTHER, 600, 350, 180);
        init_color(CUSTOM_ERROR, 1000, 50, 50);
        init_color(CUSTOM_HIGHLIGHT, 950, 800, 400);
    }

    init_pair(1, CUSTOM_MAIN, -1);
    init_pair(2, CUSTOM_TEXT, -1);
    init_pair(3, CUSTOM_KEYWORD, -1);
    init_pair(4, CUSTOM_STRING, -1);
    init_pair(5, CUSTOM_COMMENT, -1);
    init_pair(6, CUSTOM_NUMBER, -1);
    init_pair(7, CUSTOM_DELIMITER, -1);
    init_pair(8, CUSTOM_OPERATOR, -1);
    init_pair(9, CUSTOM_SPECIAL, -1);
    init_pair(10, CUSTOM_PUNCTUATION, -1);
    init_pair(11, CUSTOM_OTHER, -1);
    init_pair(12, CUSTOM_ERROR, -1);

    init_pair(13, CUSTOM_MAIN, CUSTOM_HIGHLIGHT);
    init_pair(14, CUSTOM_TEXT, CUSTOM_HIGHLIGHT);
    init_pair(15, CUSTOM_KEYWORD, CUSTOM_HIGHLIGHT);
    init_pair(16, CUSTOM_STRING, CUSTOM_HIGHLIGHT);
    init_pair(17, CUSTOM_COMMENT, CUSTOM_HIGHLIGHT);
    init_pair(18, CUSTOM_NUMBER, CUSTOM_HIGHLIGHT);
    init_pair(19, CUSTOM_DELIMITER, CUSTOM_HIGHLIGHT);
    init_pair(20, CUSTOM_OPERATOR, CUSTOM_HIGHLIGHT);
    init_pair(21, CUSTOM_SPECIAL, CUSTOM_HIGHLIGHT);
    init_pair(22, CUSTOM_PUNCTUATION, CUSTOM_HIGHLIGHT);
    init_pair(23, CUSTOM_OTHER, CUSTOM_HIGHLIGHT);
    init_pair(24, CUSTOM_ERROR, CUSTOM_HIGHLIGHT);
}

void App::displayLogo()
/**
Displays the opening screen

Returns:
    None
 */

{
    curs_set(0);

    string text;
    int tempY = (height / 2) - (16 / 2);

    fstream readFile(projectPath + "/resources/logo.txt");
    while (getline(readFile, text))
    {
        if (tempY - ((height / 2) - (16 / 2)) < 13)
        {
            wattron(stdscr, COLOR_PAIR(1));
        }
        mvprintw(tempY, (width / 2) - (text.length() / 2), text.c_str(), "%s");
        wattroff(stdscr, COLOR_PAIR(1));

        tempY++;
    }

    readFile.close();
    getch();
}

void App::checkForSpecialChars(int character)
/**
Checks if character inputted is a special key

Args:
    (int) character: Character inputted
Returns:
    None
 */

{
    if (MODE == 1)
    {
        editorSpecialChars(character);
    }
    else if (MODE == 2 || MODE == 6 || MODE == 7)
    {
        statusSpecialChars(character);
    }
    else if (MODE == 3)
    {
        settingsSpecialChars(character);
    }
    else if (MODE == 4)
    {
        switchFileSpecialChars(character);
    }
    else if (MODE == 5)
    {
        preferencesSpecialChars(character);
    }
}

void App::editorSpecialChars(int character)
/**
Handles special keys in editor

Args:
    (int) character: Character inputted
Returns:
    None
 */

{
    MEVENT event;
    switch (character)
    {
    case KEY_MOUSE:
        if (getmouse(&event) == OK)
        {
            if (event.bstate & BUTTON4_PRESSED)
            {
                editor.scrollUp();
            }
            else if (event.bstate & BUTTON5_PRESSED)
            {
                editor.scrollDown();
            }
        }
        break;

    case KEY_RESIZE:
        curs_set(0);
        editor.updateDimensions();
        status.updateDimensions();
        menu.updateDimensions();
        curs_set(1);
        break;

    case KEY_BACKSPACE:
        editor.deleteHighlighted();
        if (!editor.getHighlighting())
        {
            editor.backspace();
        }
        editor.goToMouse();
        editor.endHightlight();
        break;

    case 9:
        editor.tab();
        editor.goToMouse();
        break;

    case 10:
        editor.deleteHighlighted();
        editor.endHightlight();
        editor.enter();
        editor.goToMouse();
        break;

    case (65 & 0x1f):
        editor.ctrlA();
        break;

    case (67 & 0x1f):
        editor.ctrlC();
        break;

    case (70 & 0x1f):
        status.setState("find");
        MODE = 2;
        break;

    case (81 & 0x1f):
        if (editor.getFile().unsavedFile())
        {
            status.resetStatus();
            status.setState("quit");
            MODE = 7;
        }
        else
        {
            MODE = 0;
        }
        break;

    case (86 & 0x1f):
        editor.ctrlV();
        editor.goToMouse();
        break;

    case (88 & 0x1f):
        editor.ctrlX();
        editor.goToMouse();
        break;

    case (89 & 0x1f):
        editor.ctrlY();
        editor.goToMouse();
        break;

    case (90 & 0x1f):
        editor.ctrlZ();
        editor.goToMouse();
        break;

    case (83 & 0x1f):
        editor.ctrlS(status);
        break;

    case (69 & 0x1f):
        werase(editor.linesPad);
        werase(editor.textPad);
        werase(status.statusWindow);
        MODE = 3;
        break;

    case (84 & 0x1f):
        werase(editor.linesPad);
        werase(editor.textPad);
        werase(status.statusWindow);
        MODE = 4;
        break;

    case (80 & 0x1f):
        werase(editor.linesPad);
        werase(editor.textPad);
        werase(status.statusWindow);
        MODE = 5;
        break;

    case (66 & 0x1f):
        editor.previousFile();
        break;

    case (78 & 0x1f):
        editor.nextFile();
        break;

    case (68 & 0x1f):
        MODE = 0;
        endwin();
        break;

    case KEY_SR:
        editor.shiftUpArrow();
        editor.goToMouse();
        break;

    case KEY_SF:
        editor.shiftDownArrow();
        editor.goToMouse();
        break;

    case KEY_SLEFT:
        editor.shiftLeftArrow();
        editor.goToMouse();
        break;

    case KEY_SRIGHT:
        editor.shiftRightArrow();
        editor.goToMouse();
        break;

    case KEY_UP:
        if (!editor.getHighlighting())
        {
            editor.upArrow();
        }
        editor.goToMouse();
        editor.endHightlight();
        break;

    case KEY_DOWN:
        if (!editor.getHighlighting())
        {
            editor.downArrow();
        }
        editor.goToMouse();
        editor.endHightlight();
        break;

    case KEY_LEFT:
        if (!editor.getHighlighting())
        {
            editor.leftArrow();
        }
        editor.goToMouse();
        editor.endHightlight();
        break;

    case KEY_RIGHT:
        if (!editor.getHighlighting())
        {
            editor.rightArrow();
        }
        editor.goToMouse();
        editor.endHightlight();
        break;
    }
}

void App::statusSpecialChars(int character)
/**
Handles special keys in StatusBar

Args:
    (int) character: Character inputted
Returns:
    None
 */

{
    MEVENT event;
    switch (character)
    {
    case KEY_MOUSE:
        if (getmouse(&event) == OK && (status.getState() == "find" || status.getState() == "replace"))
        {
            if (event.bstate & BUTTON4_PRESSED)
            {
                editor.scrollUp();
            }
            else if (event.bstate & BUTTON5_PRESSED)
            {
                editor.scrollDown();
            }
        }
        break;

    case KEY_RESIZE:
        curs_set(0);
        status.updateDimensions();
        editor.updateDimensions();
        editor.writeToScreen(status);
        curs_set(1);
        break;

    case KEY_BACKSPACE:
        status.backspace();
        break;

    case 9:
        status.tab();
        break;

    case 10:
        if (MODE == 2)
        {
            if (status.enter())
            {
                editor.replaceAllInstances(status.getFindTxt(), status.getReplaceTxt());
                status.resetStatus();
                MODE = 1;
            }
        }
        else if (MODE == 6)
        {
            if (File::fileError(status.getFilename()) && editor.getFile().getName() != "")
            {
                status.setInfo("Invalid Save Location.", true);
            }
            else
            {
                string filename = status.getFilename();
                status.resetStatus();
                status.setFilename(filename);
                if (File::overwrite(status.getFilename()))
                {
                    clear();
                    status.setState("save");
                    MODE = 7;
                }
                else
                {
                    File file = editor.getFile();
                    file.setName(status.getFilename());
                    file.save();
                    editor.setFile(file);
                    editor.ctrlS(status);
                    file.getFilesInDirectory();
                    editor.setFile(file);
                    status.setFilename("");
                    editor.writeToScreen(status);
                    MODE = 1;
                }
            }
        }
        else if (MODE == 7)
        {
            if (status.getConfirm() == "y" || status.getConfirm() == "Y")
            {
                if (status.getState() == "save")
                {
                    File file = editor.getFile();
                    file.setName(status.getFilename());
                    editor.setFile(file);
                    editor.ctrlS(status);
                    editor.writeToScreen(status);
                    status.resetStatus();
                    MODE = 1;
                }
                else if (status.getState() == "quit")
                {
                    MODE = 0;
                }
            }
            else
            {
                status.resetStatus();
                MODE = 1;
            }
        }
        break;

    case KEY_LEFT:
        status.leftArrow();
        break;

    case KEY_RIGHT:
        status.rightArrow();
        break;

    case (70 & 0x1f):
        if (MODE == 2)
        {
            status.resetStatus();
            MODE = 1;
        }
        break;

    case (81 & 0x1f):
        if (status.getState() != "confirm")
        {
            if (editor.getFile().unsavedFile())
            {
                clear();
                status.resetStatus();
                status.setState("quit");
                editor.writeToScreen(status);
                MODE = 7;
            }
            else
            {
                MODE = 0;
            }
        }
        break;

    case (69 & 0x1f):
        status.setState("");
        werase(editor.linesPad);
        werase(editor.textPad);
        werase(status.statusWindow);
        MODE = 3;
        break;

    case (80 & 0x1f):
        werase(editor.linesPad);
        werase(editor.textPad);
        werase(status.statusWindow);
        MODE = 5;
        break;
    }
}

void App::settingsSpecialChars(int character)
/**
Handles special keys in Settings

Args:
    (int) character: Character inputted
Returns:
    None
 */

{
    switch (character)
    {
    case (KEY_RESIZE):
        menu.updateDimensions();
        editor.updateDimensions();
        status.updateDimensions();
        break;

    case (81 & 0x1f):
        if (editor.getFile().unsavedFile())
        {
            clear();
            status.resetStatus();
            status.setState("quit");
            editor.writeToScreen(status);
            MODE = 7;
        }
        else
        {
            MODE = 0;
        }
        break;

    case (KEY_UP):
        menu.upArrow();
        break;

    case (KEY_DOWN):
        menu.downArrow();
        break;

    case (10):
        File file = editor.getFile();
        int action = menu.enter(file);
        editor.setFile(file);
        if (action == 0)
        {
            clear();
            MODE = 1;
        }
        else if (action == 1)
        {
            clear();
            editor.ctrlS(status);
            MODE = 1;
        }
        else if (action == 2)
        {
            clear();
            status.setState("save as");
            editor.writeToScreen(status);
            MODE = 6;
        }
        else if (action == 3)
        {
            MODE = 4;
        }
        else if (action == 4)
        {
            clear();
            MODE = 5;
        }
        else if (action == 5)
        {
            if (editor.getFile().unsavedFile())
            {
                clear();
                status.resetStatus();
                status.setState("quit");
                editor.writeToScreen(status);
                MODE = 7;
            }
            else
            {
                MODE = 0;
            }
        }
        break;
    }
}

void App::switchFileSpecialChars(int character)
/**
Handles special keys in Switch Files Tab

Args:
    (int) character: Character inputted
Returns:
    None
 */

{
    switch (character)
    {
    case (KEY_RESIZE):
        menu.updateDimensions();
        editor.updateDimensions();
        status.updateDimensions();
        break;

    case (KEY_UP):
        menu.upArrow();
        break;

    case (KEY_DOWN):
        menu.downArrow();
        break;

    case (10):
    {
        File file = editor.getFile();
        int x = menu.enter(file);
        if (x == 1)
        {
            MODE = 1;
            editor.resetEditor();
            editor.setFile(file);

            HistoryStack stack = editor.getStack();
            stack.clear();
            editor.setStack(stack);
        }

        break;
    }

    case (KEY_BACKSPACE):
        menu.back();
        break;

    case (81 & 0x1f):
        if (editor.getFile().unsavedFile())
        {
            clear();
            status.resetStatus();
            status.setState("quit");
            editor.writeToScreen(status);
            MODE = 7;
        }
        else
        {
            MODE = 0;
        }
        break;

    case (84 & 0x1f):
        MODE = 1;
        break;
    }
}

void App::preferencesSpecialChars(int character)
/**
Handles special keys in Preferences

Args:
    (int) character: Character inputted
Returns:
    None
 */

{
    switch (character)
    {
    case (KEY_RESIZE):
        menu.updateDimensions();
        editor.updateDimensions();
        status.updateDimensions();
        break;

    case (KEY_UP):
        menu.upArrow();
        break;

    case (KEY_DOWN):
        menu.downArrow();
        break;

    case (10):
    {
        File file = editor.getFile();
        int action = menu.enter(file);
        if (action == 0)
        {
            editor.setSettings(settings);
            settings.saveToFile(projectPath);
            MODE = 3;
            editor.setFile(file);
            return;
        }

        vector<Button>
            buttons = menu.getButtons();
        Button button = buttons[action];
        if (action == 1 || action == 3)
        {
            string toggle = (menu.getButtons()[action].getToggle() == "On") ? "Off" : "On";
            if (action == 1)
            {
                settings.setLineNumbers(toggle);
            }
            else if (action == 3)
            {
                settings.setProgrammingMode(toggle);
            }
            else
            {
                settings.setColorScheme(toggle);
            }
            button.setToggle(toggle);
        }
        if (action == 2)
        {
            if (stoi(button.getToggle()) >= 10)
            {
                button.setToggle("2");
                settings.setTabSize("2");
            }
            else
            {
                int num = stoi(button.getToggle());
                button.setToggle(to_string(num + 2));
                settings.setTabSize(to_string(num + 2));
            }
        }
        if (action == 4)
        {
            if (settings.getColorIndex() == 5)
            {
                settings.setColorIndex(-1);
            }
            settings.setColorIndex(settings.getColorIndex() + 1);
            settings.setColorScheme(settings.getColors()[settings.getColorIndex()]);
            button.setToggle(settings.getColorScheme());
            setColor(settings.getColorScheme());
        }
        buttons[action] = button;
        menu.setButtons(buttons);
        break;
    }

    case (81 & 0x1f):
        if (editor.getFile().unsavedFile())
        {
            clear();
            status.resetStatus();
            status.setState("quit");
            editor.writeToScreen(status);
            MODE = 7;
        }
        else
        {
            MODE = 0;
        }
        break;
    }
}

void App::editorMode()
/**
Handles what happens in the editor

Returns:
    None
 */

{
    int character = wgetch(editor.textPad);

    // Check if character is inputtable
    if (character >= 32 && character <= 126)
    {
        if (editor.endOfLine())
        {
            editor.addCharacter(char(character));
            editor.goToMouse();
        }
        else
        {
            editor.insertCharacter(char(character));
            editor.goToMouse();
        }
    }

    editorSpecialChars(character);

    if (MODE == 1)
    {
        if (editor.getState() == "ctrlshifts")
        {
            clear();
            status.setState("save as");
            editor.writeToScreen(status);
            MODE = 6;
            return;
        }
        else
        {
            editor.updateStatus(status);
            status.update();
            editor.writeToScreen(status);
        }
    }
    else
    {
        if (MODE == 2)
        {
            status.findAndReplace();
        }
        else
        {
            wrefresh(editor.linesPad);
            wrefresh(editor.textPad);
            wrefresh(status.statusWindow);
        }
    }

    if (editor.getCursorVisible())
    {
        curs_set(1);
    }
    else
    {
        curs_set(0);
    }
}

void App::statusMode()
/**
Handles what happens in the status bar

Returns:
    None
 */

{
    curs_set(1);

    if (MODE == 2)
    {
        status.findAndReplace();
    }
    else if (MODE == 6)
    {
        status.saveAs();
    }
    else if (MODE == 7)
    {
        status.confirm();
    }

    int character = wgetch(status.statusWindow);

    // Check if character is inputtable
    if (character >= 32 && character <= 126)
    {
        if (status.endOfLine())
        {
            status.addCharacter(char(character));
        }
        else if (MODE != 7)
        {
            status.insertCharacter(char(character));
        }
    }

    statusSpecialChars(character);
    if (MODE == 2)
    {
        status.setMatches(editor.find(status.getFindTxt()));
    }
    editor.writeToScreen(status);
}

void App::settingsMode()
/**
Handles what happens in settings

Returns:
    None
 */

{
    curs_set(0);
    menu.displayButtons();
    menu.displayText(menu.getMenuText(editor));
    prefresh(menu.menuPad, menu.getScroll(), 0, 0, 0, menu.getHeight() - 1, menu.getWidth() - 1);
    int character = wgetch(menu.menuPad);
    settingsSpecialChars(character);
    if (MODE != 3)
    {
        menu.resetPad();
        if (MODE != 6 && MODE != 7)
        {
            werase(menu.menuPad);
            wrefresh(menu.menuPad);
        }
    }
}

void App::switchFileMode()
/**
Handles what happens in the switch files tab

Returns:
    None
 */

{
    curs_set(0);
    menu.displayButtons();
    prefresh(menu.menuPad, menu.getScroll(), 0, 3, 0, menu.getHeight() - 4, menu.getWidth() - 1);
    int character = wgetch(menu.menuPad);
    switchFileSpecialChars(character);
    if (MODE != 4)
    {
        menu.resetPad();
        if (MODE != 7)
        {
            menu.setCurrentDirectory(editor.getFile().getDirectory());
            werase(menu.menuPad);
            wrefresh(menu.menuPad);
        }
    }
}

void App::preferencesMode()
/**
Handles what happens in the preferences mode

Returns:
    None
 */

{
    curs_set(0);
    menu.displayButtons();
    menu.displayText(menu.getPreferencesText(settings));
    prefresh(menu.menuPad, menu.getScroll(), 0, 0, 0, menu.getHeight() - 1, menu.getWidth() - 1);
    int character = wgetch(menu.menuPad);
    preferencesSpecialChars(character);
    if (MODE != 5)
    {
        menu.resetPad();
        if (MODE != 7)
        {
            werase(menu.menuPad);
            wrefresh(menu.menuPad);
        }
    }
}

void App::stateLoop(string filename)
/**
Checks current state and handles it accordingly

Args:
    (string) filename: Name of the file used in arg when entering {myst.exe (filename)} command
Returns:
    None
 */

{
    File file = File();
    HistoryStack stack = HistoryStack();
    LexerScanner scanner = LexerScanner();

    file.open(filename);
    editor.setFile(file);
    editor.setStack(stack);
    editor.setScanner(scanner);
    menu.setCurrentDirectory(editor.getFile().getDirectory());

    editor.updateDimensions();
    editor.updateStatus(status);
    editor.writeToScreen(status);

    while (true)
    {
        if (MODE == 1)
        {
            editorMode();
        }
        else if (MODE == 2 || MODE == 6 || MODE == 7)
        {
            statusMode();
        }
        else if (MODE == 3)
        {
            menu.setCurrentMenu(0);
            settingsMode();
        }
        else if (MODE == 4)
        {
            if (menu.getCurrentMenu() != 1)
            {
                menu.setCurrentMenu(1);
                menu.setFileButtons(editor.getFile().getDirectory());
            }
            switchFileMode();
        }
        else if (MODE == 5)
        {
            if (menu.getCurrentMenu() != 2)
            {
                menu.updateDimensions();
            }
            menu.setCurrentMenu(2);
            preferencesMode();
        }
        else
        {
            break;
        }
    }
}
