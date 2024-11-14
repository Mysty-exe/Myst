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
	(bool) LINENUMS: Boolean to indicate whether line numbers are visible or not
	(int) tabSize: Size of the tab (as a number)
	(string) tabSpaces: Gets the tab spaces based on "tabSize"


Returns:
	void
 */

{
	width = height = 0;
	lineX = lineY = 0;
	cursorX = cursorY = 0;
	LINENUMS = true;
	tabSize = 8;
	tabSpaces = setTab();
}

File Editor::getFile()
/**
File Getter Function

Returns:
	File
 */

{
	return file;
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
	file.setTabSize(tabSpaces);
}

int Editor::getCursorX()
/**
CursorX Getter Function

Returns:
	int
 */

{
	return cursorX;
}

int Editor::getCursorY()
/**
CursorY Getter Function

Returns:
	int
 */

{
	return cursorY;
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

void Editor::toggleLineNums()
/**
LineNums Toggle Function

Returns:
	void
 */

{
	LINENUMS = not LINENUMS;
}

void Editor::changeTabSize(int size)
/**
Change the size of the tab

Args:
	(int) size: Size of the new tab

Returns:
	void
 */

{
	tabSize = size;
	tabSpaces = setTab();
}

string Editor::setTab()
/**
Tab Setter Function

Returns:
	string
 */

{
	string result = "";
	for (int i = 0; i < tabSize; i++)
	{
		result = result.append(" ");
	}
	return result;
}

bool Editor::endOfLine()
/**
Checks if cursor is at the endo of a line (regardless of wrapping)

Returns:
	bool
 */

{
	return (lineX == (int)file.getLineLength(lineY));
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
	file.insertChar(lineY, getTabX(lineX), character);
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
		int sub = 1;
		if (file.getLine(lineY)[getTabX(lineX) - 1] == '\t')
		{
			sub = tabSize;
		}
		file.delChar(lineY, getTabX(lineX) - 1);

		cursorX -= sub;
		lineX -= sub;
	}
	else if (cursorY > 0)
	{
		if (cursorX == 0)
		{
			if (lineX == 0)
			{
				lineY--;
				cursorX = getWrappedX(file.getLineLength(lineY));
				lineX = file.getLineLength(lineY);
				file.addStr(lineY, file.getLine(lineY + 1));
				file.delLine(lineY + 1);
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

void Editor::tab()
/**
Replicates an actual tab based on the size of the current tabspace

Returns:
	void
 */

{
	if (endOfLine())
	{
		lineX += tabSize;
		file.addChar(lineY, '\t');
		if (cursorX + (tabSize - 1) < width - 1) // Check if cursor is at the end of a line
		{
			cursorX += tabSize;
		}
		else
		{
			cursorX = tabSize - ((width - 1) - cursorX);
			cursorY++;
		}
	}
	else
	{
		file.insertChar(lineY, getTabX(lineX), '\t');
		lineX += tabSize;
		if (cursorX + tabSize < width - 1) // Check if cursor is at the end of a line
		{
			cursorX += tabSize;
		}
		else
		{
			cursorX = tabSize - ((width - 1) - cursorX);
			cursorY++;
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
		string text = file.getLine(lineY).substr(getTabX(lineX), file.getLineLength(lineY) - 1);
		file.setLine(lineY, file.getLine(lineY).substr(0, getTabX(lineX)));
		file.insertLine(lineY + 1, text);
	}

	cursorY++;
	cursorX = 0;
	lineX = 0;
	lineY++;
}

void Editor::ctrlX()
/**
Copies the line and deletes it

Returns:
	void
 */

{
	const char *str = file.getLine(lineY).c_str();
	const size_t len = strlen(str) + 1;

	HGLOBAL glob = GlobalAlloc(GMEM_FIXED, 32);
	memcpy(glob, str, len);

	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, glob);
	CloseClipboard();

	file.setLine(lineY, "");
	cursorY -= getWrappedY(lineX) - 1;
	cursorX = 0;
	lineX = 0;
}

void Editor::ctrlS(WINDOW *cmdWin, CommandLine &cmd)
/**
Saves the file

Args:
	(WINDOW*) cmdWin: Window of the command line
	(CommandLine&) cmd: CommandLine Object

Returns:
	void
 */

{
	if (file.save())
	{
		cmd.displayInfo(cmdWin, "Changes Saved.");
	}
	else
	{
		cmd.displayError(cmdWin, "Couldn't Save Changes. ( Try saveas {file} )");
	}
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
		cursorX = getWrappedX(file.getLineLength(lineY));
		lineX = file.getLineLength(lineY);
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
		int nextLineWrappedWidth = ceil((file.getLineLength(lineY + 1)) * 1.0 / (width - 1) * 1.0);
		nextLineWrappedWidth = (nextLineWrappedWidth == 0) ? 1 : nextLineWrappedWidth;

		int currentLineWrappedWidth = ceil((file.getLineLength(lineY)) * 1.0 / (width - 1) * 1.0);
		currentLineWrappedWidth = (currentLineWrappedWidth == 0) ? 1 : currentLineWrappedWidth;
		downIncrement = currentLineWrappedWidth - getWrappedY(lineX);

		cursorY += downIncrement + nextLineWrappedWidth;
		cursorX = getWrappedX(file.getLineLength(lineY + 1));
		lineX = file.getLineLength(lineY + 1);
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
		int sub = 1;

		if (file.getLine(lineY)[getTabX(lineX) - 1] == '\t')
		{
			sub = tabSize;
		}

		lineX -= sub;
		if (cursorX > 0)
		{
			cursorX -= sub;
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
		int add = 1;

		if (file.getLine(lineY)[getTabX(lineX)] == '\t')
		{
			add = tabSize;
		}

		lineX += add;

		// Check if cursor is not in a "wrapped" line
		if (cursorX < width - 1)
		{
			cursorX += add;
		}
		else
		{
			cursorX = 1;
			cursorY++;
		}
	}
}

void Editor::writeToScreen(WINDOW *textWin, WINDOW *linesWin, bool end)
/**
Clears the screen and writes each line based on the File object and refreshes the screen at the end

Args:
	(WINDOW*) textWin: Text window where the text of the file goes
	(WINDOW*) lineWin: Line Window where the line numbers go
	(WINDOW*) cmdWin: Line Window where the line numbers go
	(bool) end: Indicates whether cursor should go to the end

Returns:
	void
 */

{
	int w, h;
	getmaxyx(textWin, h, w);
	setWidth(w);
	setHeight(h);

	curs_set(0);
	int lineNum = 0;

	int tempX, tempY, endX;
	tempX = tempY = 0;
	endX = 0;

	werase(textWin);
	werase(linesWin);

	wmove(textWin, tempY, tempX);
	wmove(linesWin, 0, 0);

	for (const string &line : file.getLines())
	{
		lineNum++;
		wmove(linesWin, tempY, 0);
		if (LINENUMS) // Checks if line numbers should be shown
		{
			mvwprintw(linesWin, tempY, 0, to_string(lineNum).c_str());
		}
		else
		{
			mvwprintw(linesWin, tempY, 0, "~");
		}

		string copiedLine = file.replaceAll(line, "\t", tabSpaces); // Replaces the tabspaces
		while (true)
		{
			// Handles line wrapping
			if ((int)copiedLine.length() <= (width - 1))
			{
				mvwprintw(textWin, tempY, tempX, copiedLine.c_str());
				endX = copiedLine.length();
				tempY++;
				break;
			}
			else
			{
				mvwprintw(textWin, tempY, tempX, copiedLine.substr(0, width - 1).c_str());
				endX = copiedLine.substr(0, width - 1).length();
				copiedLine.erase(0, width - 1);
				tempY++;
			}
			if (end)
			{
				wmove(textWin, tempY, tempX);
			}
		}
	}

	if (!end)
	{
		wmove(textWin, cursorY, cursorX);
	}
	else
	{
		cursorX = endX;
		cursorY = tempY - 1;
		lineX = file.getLineLength(file.getLines().size() - 1);
		lineY = file.getLines().size() - 1;
	}

	for (int n = tempY; n < height; n++)
	{
		mvwprintw(linesWin, n, 0, "~");
	}

	curs_set(1);
	wrefresh(linesWin);
	wrefresh(textWin);
}

int Editor::enactCommand(WINDOW *cmdWin, CommandLine &cmd, vector<string> command)
/**
Clears the screen and writes each line based on the File object and refreshes the screen at the end

Args:
	(WINDOW*) cmdWin: Window for the command line
	(CommandLine&) lineWin: CommandLine Object
	(vector<string>) command: Vector of the command
	(int&) mode: Mode of the editor

Returns:
	void
 */

{
	if (command[0].length() != 0)
	{
		if (command[0] == "save")
		{
			ctrlS(cmdWin, cmd);
		}
		else if (command[0] == "linenums")
		{
			toggleLineNums();
			cmd.displayInfo(cmdWin, "Turned on Line Numbers.");
		}
		if (command[0] == "quit")
		{
			return 0;
		}
		else if (command[0] == "saveas")
		{
			if (file.getName().length() != 0)
			{
				try
				{
					filesystem::rename(file.getName(), command[1]);
				}
				catch (const std::exception &e)
				{
					cmd.displayError(cmdWin, "Invalid File Location.");
					return 1;
				}
			}
			file.setName(command[1]);
			ctrlS(cmdWin, cmd);
		}
		else if (command[0] == "switch")
		{
			fstream readFile(command[1]);
			if (readFile.fail() && command[1].length() != 0)
			{
				cmd.displayError(cmdWin, "Invalid File Location.");
			}
			else
			{
				file.setName(command[1]);
				file.open(command[1]);
				cmd.displayInfo(cmdWin, "Switched File to " + command[1] + ".");
			}
			readFile.close();
		}
		else if (command[0] == "tabsize")
		{
			changeTabSize(stoi(command[1]));
			cmd.displayInfo(cmdWin, "Changed Tabsize to " + command[1] + ".");
		}
		return 1;
	}
	return 2;
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

int Editor::getTabX(int x)
/**
Gets the cursorX value based on the amount of tabs in the line

Args:
	(int) x: Current index of the cursor

Returns:
	int
 */

{
	string copiedLine = file.replaceAll(file.getLine(lineY), "\t", tabSpaces);
	copiedLine = copiedLine.substr(0, x);
	copiedLine = file.replaceAll(copiedLine, tabSpaces, "\t");
	return copiedLine.length();
}
