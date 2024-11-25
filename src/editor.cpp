#pragma once
#include "editor.h"

Editor::Editor(int w, int h)
/**
Editor Class Constructor

Vars:
	(int) width: width of the editor
	(int) height: height of the editor
	(int) cursorX: index that the cursor is on (regards wrapping)
	(int) cursorY: current line that the cursor is on (regards wrapping)
	(int) lineX: index that the cursor is on (disregards wrapping)
	(int) lineY: current line that the cursor is on (disregards wrapping)
	(int) scroll: How scrolled the text editor is
	(bool) highlighting: Whether something is being highlighting
	(vector<pair<int, int>>) selectedText: Indexes of text that is being highlighted
	(WINDOW*) textPad: Pad for the editor
	(WINDOW*) linesPad: Pad for the lines

Returns:
	void
 */

{
	maxHeight = 1000;
	width, height = w, h;
	lineNumbersWidth = 4;
	cursorX = cursorY = 0;
	lineX = lineY = 0;
	scroll = 0;

	highlighting = false;
	selectedText = {};
	selectedText.push_back(make_pair(0, 0));
	selectedText.push_back(make_pair(0, 0));

	specialCharacters = {'"', '\'', '(', '[', '{'};
	otherCharacters = {'"', '\'', ')', ']', '}'};

	textPad = newpad(maxHeight, w - lineNumbersWidth);
	linesPad = newpad(maxHeight, lineNumbersWidth);
	width -= lineNumbersWidth;
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

void Editor::setSettings(int tab, bool line, bool autocomp)
/**
Update the editor settings with arguments

Args:
	(int) tab: tab size
	(bool) line: bool if line numbers are shown
	(bool) autocomp: bool if autocomplete is on or not

Returns:
	void
 */

{
	tabSize = tab;
	lineNums = line;
	autoComplete = autocomp;
	tabSpaces = setTab();
	file.setTabSize(tabSpaces);
}

bool checkSpecialChar(char character)
/**
Check if character is a special character

Args:
	(char) character: character inputted
Returns:
	void
 */

{
	return any_of(begin(specialCharacters), end(specialCharacters), [=](char n)
				  { return n == character; });
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

int Editor::getScroll()
/**
Scroll Getter Function

Returns:
	int
 */

{
	return scroll;
}

int Editor::getTab()
/**
Tab Getter Function

Returns:
	int
 */

{
	return tabSize;
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
	file.setTabSize(tabSpaces);
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

bool Editor::getLineNumbers()
/**
LineNumbers Getter Function

Returns:
	bool
 */

{
	return lineNums;
}

bool Editor::getAutoComplete()
/**
AutoComplete Getter Function

Returns:
	bool
 */

{
	return autoComplete;
}

void Editor::toggleAutoComplete()
/**
autoComplete Toggle Function

Returns:
	void
 */

{
	autoComplete = not autoComplete;
}

void Editor::toggleLineNums()
/**
lineNums Toggle Function

Returns:
	void
 */

{
	lineNums = not lineNums;
}

void Editor::updateDimensions()
/**
Update size of editor and linenums if terminal size has been changed

Returns:
	void
 */

{
	delwin(textPad);
	delwin(linesPad);
	getmaxyx(stdscr, height, width);

	if (int(log10(lineY) + 1) >= 2)
	{
		lineNumbersWidth = int(log10(lineY) + 1) + 2;
	}

	textPad = newpad(maxHeight, width - lineNumbersWidth);
	linesPad = newpad(maxHeight, lineNumbersWidth);
	keypad(textPad, true);

	width -= lineNumbersWidth;
	cursorX = getWrappedX(lineX);
	cursorY = getWrappedCursorY(lineY, lineX);
	goToMouse();

	prefresh(linesPad, scroll, 0, 0, 0, height - 2, lineNumbersWidth);
	prefresh(textPad, scroll, 0, 0, lineNumbersWidth, height - 2, width + (lineNumbersWidth - 1));
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
	if (!autoComplete || !checkSpecialChar(character))
	{
		deleteHighlighted();
		endHightlight();
		file.addChar(lineY, character);
	}
	if (cursorX < width - 1) // Check if cursor is at the end of a line
	{
		cursorX++;
	}
	else
	{
		cursorX = 1;
		cursorY++;
		if (cursorY + 1 >= scroll + height)
		{
			scroll++;
		}
	}
	lineX++;
	if (autoComplete)
	{
		for (int i = 0; i < specialCharacters.size(); i++)
		{
			if (character == specialCharacters[i])
			{
				if (highlighting)
				{
					lineX = orderHighlight()[1].first;
					lineY = orderHighlight()[1].second;
					cursorX = getWrappedX(lineX);
					cursorY = getWrappedCursorY(lineY, lineX);
					file.insertChar(lineY, getTabX(lineX), otherCharacters[i]);
					lineX = orderHighlight()[0].first;
					lineY = orderHighlight()[0].second;
					cursorX = getWrappedX(lineX);
					cursorY = getWrappedCursorY(lineY, lineX);
					file.insertChar(lineY, getTabX(lineX), specialCharacters[i]);
					lineY = orderHighlight()[1].second;
					lineX = file.getLineLength(lineY) - 1;
					cursorX = getWrappedX(lineX);
					cursorY = getWrappedCursorY(lineY, lineX);
					if (selectedText[0].second == selectedText[1].second)
					{
						selectedText[0].first = selectedText[0].first + 1;
						selectedText[1].first = selectedText[1].first + 1;
					}
					else
					{
						if (orderHighlight()[1].second == selectedText[0].second)
						{
							selectedText[1].first = selectedText[1].first + 1;
							selectedText[0].first = lineX;
						}
						else
						{
							selectedText[0].first = selectedText[0].first + 1;
							selectedText[1].first = lineX;
						}
					}
				}
				else
				{
					file.addChar(lineY, character);
					file.addChar(lineY, otherCharacters[i]);
				}
			}
		}
	}
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
	if ((!autoComplete || !checkSpecialChar(character) || !highlighting))
	{
		deleteHighlighted();
		endHightlight();
		if (!checkSpecialChar(character) || !autoComplete || !(file.getLineWTabs(lineY)[lineX] == character) || highlighting)
		{
			file.insertChar(lineY, getTabX(lineX), character);
		}
	}
	lineX++;
	if (cursorX < width - 1) // Check if cursor is at the end of a line
	{
		cursorX++;
	}
	else
	{
		cursorX = 1;
		cursorY++;
		if (cursorY + 1 >= scroll + height)
		{
			scroll++;
		}
	}
	if (autoComplete)
	{
		for (int i = 0; i < specialCharacters.size(); i++)
		{
			if (character == specialCharacters[i])
			{
				if (highlighting)
				{
					lineX = orderHighlight()[1].first;
					lineY = orderHighlight()[1].second;
					cursorX = getWrappedX(lineX);
					cursorY = getWrappedCursorY(lineY, lineX);
					file.insertChar(lineY, getTabX(lineX), otherCharacters[i]);
					lineX = orderHighlight()[0].first;
					lineY = orderHighlight()[0].second;
					cursorX = getWrappedX(lineX);
					cursorY = getWrappedCursorY(lineY, lineX);
					file.insertChar(lineY, getTabX(lineX), specialCharacters[i]);
					lineY = orderHighlight()[1].second;
					if (selectedText[0].second == selectedText[1].second)
					{
						lineX = orderHighlight()[1].first + 1;
						cursorX = getWrappedX(lineX);
						cursorY = getWrappedCursorY(lineY, lineX);
						selectedText[0].first = selectedText[0].first + 1;
						selectedText[1].first = selectedText[1].first + 1;
					}
					else
					{
						lineX = orderHighlight()[1].first;
						cursorX = getWrappedX(lineX);
						cursorY = getWrappedCursorY(lineY, lineX);
						if (orderHighlight()[1].second == selectedText[0].second)
						{
							selectedText[1].first = selectedText[1].first + 1;
							selectedText[0].first = lineX;
						}
						else
						{
							selectedText[0].first = selectedText[0].first + 1;
							selectedText[1].first = lineX;
						}
					}
				}
			}
		}
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

		lineX -= sub;
		cursorX = getWrappedX(lineX);
		cursorY = getWrappedCursorY(lineY, lineX);

		if (cursorX == 0 && lineX != 0)
		{
			cursorX = width - 1;
			cursorY--;
		}
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

			if (cursorY < scroll)
			{
				scroll--;
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
	if (highlighting)
	{
		lineX += tabSize;
		selectedText[0].first = selectedText[0].first + tabSize;
		selectedText[1].first = lineX;
		cursorX = getWrappedX(lineX);
		cursorY = getWrappedCursorY(lineY, lineX);
		for (int i = orderHighlight()[0].second; i != orderHighlight()[1].second + 1; i++)
		{
			file.insertChar(i, 0, '\t');
		}
	}
	else
	{
		lineX += tabSize;
		if (endOfLine())
		{
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
}

void Editor::enter()
/**
Just moves the cursor to a new line if the cursor is at the end of the line.
Else moves the cursor a new line with the last part of the line (after the cursor) being the new line.

Returns:
	void
 */

{
	int startTabs = 0;
	for (int x = 0; x < file.getLine(lineY).length(); x++)
	{
		if (file.getLine(lineY)[x] == '\t')
		{
			startTabs += 1;
		}
		else
		{
			break;
		}
	}

	string text;
	if (((file.getLineWTabs(lineY)[lineX - 1] == '[' && file.getLineWTabs(lineY)[lineX] == ']') || (file.getLineWTabs(lineY)[lineX - 1] == '{' && file.getLineWTabs(lineY)[lineX] == '}') || (file.getLineWTabs(lineY)[lineX - 1] == '(' && file.getLineWTabs(lineY)[lineX] == ')')) && autoComplete)
	{
		text = file.getLine(lineY).substr(getTabX(lineX), file.getLineLength(lineY));
		file.setLine(lineY, file.getLine(lineY).substr(0, getTabX(lineX)));
		file.insertLine(lineY + 1, "");
		file.insertLine(lineY + 2, "");
		lineX = 0;
		cursorX = 0;
		lineY += 2;
		cursorY += 2;

		for (int x = 0; x < startTabs; x++)
		{
			tab();
		}
		file.addStr(lineY, text);

		lineX = 0;
		cursorX = 0;
		lineY -= 1;
		cursorY -= 1;

		for (int x = 0; x < startTabs; x++)
		{
			tab();
		}
		tab();
	}
	else
	{
		text = file.getLine(lineY).substr(getTabX(lineX), file.getLineLength(lineY));
		file.setLine(lineY, file.getLine(lineY).substr(0, getTabX(lineX)));
		file.insertLine(lineY + 1, "");
		cursorX = 0;
		cursorY++;
		lineX = 0;
		lineY++;

		if (cursorY >= scroll + (height - 1))
		{
			scroll++;
		}

		if (autoComplete)
		{
			for (int x = 0; x < startTabs; x++)
			{
				tab();
			}
		}
		file.addStr(lineY, text);
	}
}

void Editor::ctrlA()
{
	highlighting = true;
	selectedText[0].first = 0;
	selectedText[0].second = 0;
	selectedText[1].first = file.getLineLength(file.getLines().size() - 1);
	selectedText[1].second = file.getLines().size() - 1;
}

void Editor::ctrlC()
{
	FILE *pipe = popen("xclip -selection clipboard", "w");
	if (pipe)
	{
		string str;
		if (!highlighting)
		{
			str = file.getLine(lineY);
		}
		else
		{
			if (selectedText[0].second == selectedText[1].second)
			{
				str = file.getLine(lineY).substr(orderHighlight()[0].first, orderHighlight()[1].first - orderHighlight()[0].first);
			}
			else
			{
				for (int y = orderHighlight()[0].second; y <= orderHighlight()[1].second; y++)
				{
					if (y == orderHighlight()[0].second)
					{
						str += file.getLine(y).substr(orderHighlight()[0].first, file.getLineLength(y) - orderHighlight()[0].first);
						str += "\n";
					}
					else if (y == orderHighlight()[1].second)
					{
						str += file.getLine(y).substr(0, orderHighlight()[1].first);
					}
					else
					{
						str += file.getLine(y);
						str += "\n";
					}
				}
			}
		}
		fwrite(str.c_str(), sizeof(char), str.size(), pipe);
		pclose(pipe);
	}
}

void Editor::ctrlV()
{
	FILE *pipe = popen("xclip -selection clipboard -o", "r");
	if (pipe)
	{
		char buffer[128];
		string result;
		while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
		{
			result += buffer;
		}

		pclose(pipe);

		bool save = autoComplete;
		autoComplete = false;
		for (int x = 0; x < result.length(); x++)
		{
			if (result[x] == '\n')
			{
				enter();
			}
			else if (result[x] == '\t')
			{
				tab();
			}
			else if (result[x] != '\r')
			{
				addCharacter(result[x]);
			}
		}
		autoComplete = save;
	}
}

void Editor::ctrlX()
/**
Copies the line and deletes it

Returns:
	void
 */

{
	const string str = file.getLine(lineY);
	FILE *pipe = popen("xclip -selection clipboard", "w");
	if (pipe)
	{
		// Write the text to the pipe
		fwrite(str.c_str(), sizeof(char), str.size(), pipe);
		pclose(pipe);
		if (file.getLines().size() > 1)
		{
			file.delLine(lineY);
			cursorY -= getWrappedY(lineX) - 1;
		}
		else
		{
			file.setLine(lineY, "");
		}
		lineX = 0;
		cursorX = getWrappedX(lineX);
		if (lineY == file.getLines().size() && file.getLines().size() > 0)
		{
			lineY -= 1;
			cursorY = getWrappedCursorY(lineY, lineX);
		}
	}
}

void Editor::ctrlS(CommandLine &cmd)
/**
Saves the file

Args:
	(CommandLine&) cmd: CommandLine Object

Returns:
	void
 */

{
	if (file.save())
	{
		cmd.displayInfo("Changes Saved.");
	}
	else
	{
		cmd.displayError("Couldn't Save Changes. ( Try saveas {file} )");
	}
}

void Editor::goToMouse()
{
	if (!(cursorY + 1 > scroll && cursorY + 1 < scroll + height))
	{
		scroll = cursorY - (height / 2);
		if (scroll < 0)
		{
			scroll = 0;
		}
	}
}

void Editor::scrollUp()
{
	if (scroll > 0)
	{
		scroll--;
	}
}

void Editor::scrollDown()
{
	if (file.getLines().size() - scroll >= height / 2)
	{
		scroll++;
	}
}

void Editor::shiftUpArrow()
/**
Moves the cursor to the end of the previous line and hightlight

Returns:
	void
 */

{
	highlight();
	upArrow();
	selectedText[1].first = lineX;
	selectedText[1].second = lineY;
	if (selectedText[0].first == selectedText[1].first && selectedText[0].second == selectedText[1].second)
	{
		endHightlight();
	}
}

void Editor::shiftDownArrow()
/**
Moves the cursor to the end of the following line and highlight

Returns:
	void
 */

{
	highlight();
	downArrow();
	selectedText[1].first = lineX;
	selectedText[1].second = lineY;
	if (selectedText[0].first == selectedText[1].first && selectedText[0].second == selectedText[1].second)
	{
		endHightlight();
	}
}

void Editor::shiftLeftArrow()
/**
Moves cursor to the left if its not already at the beginning of the line (disregards wrapping) and higlight

Returns:
	void
 */

{
	highlight();
	leftArrow();
	selectedText[1].first = lineX;
	selectedText[1].second = lineY;
	if (selectedText[0].first == selectedText[1].first && selectedText[0].second == selectedText[1].second)
	{
		endHightlight();
	}
}

void Editor::shiftRightArrow()
/**
Moves cursor to the right of the lin if cursor isn't already at the end of the line (disregards wrapping) and highlight

Returns:
	void
 */

{
	highlight();
	rightArrow();
	selectedText[1].first = lineX;
	selectedText[1].second = lineY;
	if (selectedText[0].first == selectedText[1].first && selectedText[0].second == selectedText[1].second)
	{
		endHightlight();
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
		lineX = (lineX >= file.getLineLength(lineY)) ? file.getLineLength(lineY) : lineX;
		for (const int t : file.getTabs(lineY, tabSize))
		{
			if (lineX < t && lineX > t - tabSize)
			{
				lineX = t;
				break;
			}
		}
		cursorX = getWrappedX(lineX);
		cursorY = getWrappedCursorY(lineY, lineX);

		if (cursorY < scroll)
		{
			scroll -= getWrappedY(file.getLine(lineY).length() - 1);
		}
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
		lineY++;
		lineX = (lineX >= file.getLineLength(lineY)) ? file.getLineLength(lineY) : lineX;
		for (const int t : file.getTabs(lineY, tabSize))
		{
			if (lineX < t && lineX > t - tabSize)
			{
				lineX = t;
				break;
			}
		}

		cursorX = getWrappedX(lineX);
		cursorY = getWrappedCursorY(lineY, lineX);

		if (cursorY + 1 >= scroll + height)
		{
			scroll += getWrappedY(file.getLine(lineY).length() - 1);
		}
	}
	else
	{
		if (cursorY > scroll + height / 2)
		{
			scroll++;
		}
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
		cursorX = getWrappedX(lineX);
		cursorY = getWrappedCursorY(lineY, lineX);
	}
	else
	{
		upArrow();
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
		cursorX = getWrappedX(lineX);
		cursorY = getWrappedCursorY(lineY, lineX);
	}
	else
	{
		downArrow();
	}
}

void Editor::highlight()
{
	if (!highlighting)
	{
		highlighting = true;
		selectedText[0].first = lineX;
		selectedText[0].second = lineY;
	}
}

void Editor::endHightlight()
{
	selectedText[0].first = 0;
	selectedText[0].second = 0;
	selectedText[1].first = 0;
	selectedText[1].second = 0;
	highlighting = false;
}

vector<pair<int, int>> Editor::orderHighlight()
{
	if (selectedText[0].second > selectedText[1].second)
	{
		return {selectedText[1], selectedText[0]};
	}
	else if ((selectedText[0].second == selectedText[1].second) && selectedText[0].first > selectedText[1].first)
	{
		return {selectedText[1], selectedText[0]};
	}
	return selectedText;
}

void Editor::deleteHighlighted()
{
	if (highlighting)
	{
		lineX = orderHighlight()[1].first;
		lineY = orderHighlight()[1].second;
		cursorX = getWrappedX(lineX);
		cursorY = getWrappedCursorY(lineY, lineX);
		while (true)
		{
			backspace();
			if (lineX == orderHighlight()[0].first && lineY == orderHighlight()[0].second)
			{
				break;
			}
		}
	}
}

void Editor::printLine(bool end, string copiedLine, int lineNum, int &tempY, int &endX)
{
	while (true)
	{
		// Handles line wrapping
		if ((int)copiedLine.length() <= (width - 1))
		{
			string text = copiedLine;
			mvwprintw(textPad, tempY, 0, text.c_str());
			endX = copiedLine.length();
			tempY++;
			break;
		}
		else
		{
			string text = copiedLine.substr(0, width - 1);
			mvwprintw(textPad, tempY, 0, text.c_str());
			tempY++;
			copiedLine.erase(0, width - 1);
		}
		if (end)
		{
			wmove(textPad, tempY, 0);
		}
	}
}

void Editor::printLineByChar(string copiedLine, int lineNum, int &tempY, int &endX)
{
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	int printX = 0;
	for (int x = 0; x < copiedLine.length(); x++)
	{
		if (lineNum == orderHighlight()[0].second && lineNum == orderHighlight()[1].second)
		{
			if (x >= orderHighlight()[0].first && x <= orderHighlight()[1].first - 1)
			{
				wattron(textPad, COLOR_PAIR(1));
				mvwaddch(textPad, tempY, printX, copiedLine[x]);
				wattroff(textPad, COLOR_PAIR(1));
			}
			else
			{
				mvwaddch(textPad, tempY, printX, copiedLine[x]);
			}
		}
		else if ((lineNum == orderHighlight()[0].second && x >= orderHighlight()[0].first) || (lineNum == orderHighlight()[1].second && x < orderHighlight()[1].first))
		{
			wattron(textPad, COLOR_PAIR(1));
			mvwaddch(textPad, tempY, printX, copiedLine[x]);
			wattroff(textPad, COLOR_PAIR(1));
		}
		else
		{
			mvwaddch(textPad, tempY, printX, copiedLine[x]);
		}

		printX += 1;
		if (printX == width - 1)
		{
			printX = 0;
			tempY++;
		}
		endX = printX;
	}
	tempY++;
}

void Editor::writeToScreen(bool end)
/**
Clears the screen and writes each line based on the File object and refreshes the screen at the end

Args:
	(bool) end: Indicates whether cursor should go to the end

Returns:
	void
 */

{
	if ((lineNums && int(log10(lineY) + 1) >= 2 && lineNumbersWidth - 2 != int(log10(lineY) + 1)) || getWrappedCursorY(file.getLines().size() - 1, file.getLine(file.getLines().size() - 1).length()) + height >= maxHeight)
	{
		if (getWrappedCursorY(file.getLines().size() - 1, file.getLine(file.getLines().size() - 1).length()) + height >= maxHeight)
		{
			maxHeight += 1000;
		}
		updateDimensions();
	}

	int lineNum = 0;

	int tempX, tempY, endX;
	tempX = tempY = 0;
	endX = 0;

	werase(linesPad);
	werase(textPad);

	wmove(textPad, 0, 0);
	wmove(linesPad, 0, 0);

	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	for (const string &line : file.getLines())
	{
		lineNum++;
		wmove(linesPad, tempY, 0);
		string nums = "";
		if (lineNums) // Checks if line numbers should be shown
		{
			for (int i = 0; i < ((lineNumbersWidth - 1) - to_string(lineNum).length()); i++)
			{
				nums = nums.append(" ");
			}
			nums += to_string(lineNum);
			mvwprintw(linesPad, tempY, 0, nums.c_str());
		}
		else
		{
			for (int i = 0; i < (lineNumbersWidth - 2); i++)
			{
				nums = nums.append(" ");
			}
			nums += "~";
			mvwprintw(linesPad, tempY, 0, nums.c_str());
		}

		string copiedLine = file.replaceAll(line, "\t", tabSpaces); // Replaces the tabspaces

		if (highlighting)
		{
			if (lineNum - 1 > orderHighlight()[0].second && lineNum - 1 < orderHighlight()[1].second)
			{
				wattron(textPad, COLOR_PAIR(1));
				printLine(end, copiedLine, lineNum, tempY, endX);
				wattroff(textPad, COLOR_PAIR(1));
			}
			else if (lineNum - 1 == orderHighlight()[0].second || lineNum - 1 == orderHighlight()[1].second)
			{
				printLineByChar(copiedLine, lineNum - 1, tempY, endX);
			}
			else
			{
				printLine(end, copiedLine, lineNum, tempY, endX);
			}
		}
		else
		{
			printLine(end, copiedLine, lineNum, tempY, endX);
		}
	}

	if (!end)
	{
		wmove(textPad, cursorY, cursorX);
	}
	else
	{
		cursorX = endX;
		cursorY = tempY - 1;
		lineX = file.getLineLength(file.getLines().size() - 1);
		lineY = file.getLines().size() - 1;
	}

	wmove(linesPad, tempY, 0);
	string nums = "";
	for (int i = 0; i < (lineNumbersWidth - 2); i++)
	{
		nums = nums.append(" ");
	}
	nums.append("~");

	for (int n = tempY; n < file.getLines().size() + height * 2; n++)
	{
		mvwprintw(linesPad, n, 0, nums.c_str());
	}

	wattroff(textPad, COLOR_PAIR(1));
	prefresh(linesPad, scroll, 0, 0, 0, height - 2, lineNumbersWidth);
	prefresh(textPad, scroll, 0, 0, lineNumbersWidth, height - 2, width + (lineNumbersWidth - 1));

	if (cursorY + 1 > scroll && cursorY + 1 < scroll + height)
	{
		curs_set(1);
	}
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
		if (x > (width - 1))
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
		if (x > width - 1)
		{
			x -= (width);
			counter += 1;
		}
		else
		{
			break;
		}
	}
	return counter;
}

int Editor::getWrappedCursorY(int y, int x)
{
	int result = 0;
	for (int i = 0; i < y; i++)
	{
		result += getWrappedY(file.getLineLength(i));
	}
	result += getWrappedY(x);
	return result - 1;
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

	for (const int x : file.getTabs(lineY, tabSize))
	{
		if (x - tabSize < copiedLine.length())
		{
			copiedLine.replace(x - tabSize, tabSpaces.length(), "\t");
		}
		else
		{
			break;
		}
	}

	return copiedLine.length();
}

int Editor::enactCommand(CommandLine &cmd, vector<string> command)
/**
Enacts a command based on the arguments

Args:
	(CommandLine&) cmd: CommandLine Object
	(vector<string>) command: Vector of the command

Returns:
	int
 */

{
	if (command[0].length() != 0)
	{
		if (command[0] == "save")
		{
			ctrlS(cmd);
		}
		else if (command[0] == "linenums")
		{
			toggleLineNums();
			cmd.displayInfo("Turned on Line Numbers.");
		}
		else if (command[0] == "autocomplete")
		{
			toggleAutoComplete();
			cmd.displayInfo("Turned on Simple Auto Complete.");
		}
		else if (command[0] == "quit")
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
					cmd.displayError("Invalid File Location.");
					return 1;
				}
			}
			file.setName(command[1]);
			ctrlS(cmd);
		}
		else if (command[0] == "switch")
		{
			fstream readFile(command[1]);
			if (readFile.fail() && command[1].length() != 0)
			{
				cmd.displayError("Invalid File Location.");
			}
			else
			{
				lineX = lineY = 0;
				cursorX = cursorY = 0;
				file.setName(command[1]);
				file.open(command[1]);
				cmd.displayInfo("Switched File to " + command[1] + ".");
			}
			readFile.close();
		}
		else if (command[0] == "tabsize")
		{
			try
			{
				changeTabSize(stoi(command[1]));
				cmd.displayInfo("Changed Tabsize to " + command[1] + ".");
				lineX = file.getLineLength(lineY);
				cursorX = getWrappedX(lineX);
				cursorY += getWrappedY(lineX) - 1;
			}
			catch (const std::exception &e)
			{
				cmd.displayError("Invalid Tabsize.");
			}
		}
		return 1;
	}
	return 2;
}
