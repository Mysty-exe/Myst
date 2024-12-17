# Myst Text Editor
Myst is a lightweight, customizable, and terminal-based text editor. Features a variety of themes, keyboard shortcuts, and support for user preferences, Myst is ideal for programmers and writers who work in terminal environments.

## Features
- Customizable Themes: Choose from a range of themes like "Arctic Horizon," "Twilight Cascade," and more.
- Syntax Highlighting **(CURRENTLY ONLY FOR PYTHON FILES)**: Token-based coloring for strings, keywords, comments, and more.
- Keyboard Shortcuts: Quick navigation and editing with intuitive shortcuts.
- Configurable Settings
- Save and "Save As" options
- Seamless file switching

## Installation
    git clone https://github.com/yourusername/myst.git
    make
    myst.exe

## Usage
Running Myst:

- Run `myst.exe` in your terminal.
- Or provide a file name: `myst.exe [filename.txt]`.

Key Shortcuts:

* Ctrl-S   -   Save
* Ctrl-F   -   Find/Replace
* Ctrl-E   -   Settings/Menu
* Ctrl-P   -   Preferences
* Ctrl-B   -   Previous File
* Ctrl-N   -   Next File
* Ctrl-Q   -   Quit

## Configuration and Preferences:

Edit settings.ini in the /config/ directory to customize your preferences.
Myst will automatically apply changes on the next startup.

## Dependencies
- ncurses
- g++ or any C++17-compatible compiler

## Known Issues
- Terminal Compatibility: Some shortcuts may not work on certain terminals. Ensure your terminal supports ncurses properly.
- File Paths: Relative paths may cause issues if Myst is run outside its main directory. Ensure the resources/ folder is in the correct location.

## Screenshots
- [Myst Logo](resources/screenshots/Logo.png)
- [Example Python Code](resources/screenshots/Code.png)
- [List of Files To Switch](resources/screenshots/Files.png)
- [Settings](resources/screenshots/Settings.png)

## Contact
For issues or questions, please open an issue on GitHub or contact me directly at o.s.toure72@gmail.com.