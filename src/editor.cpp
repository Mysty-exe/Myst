#pragma once
#include "editor.h"

Editor::Editor()
/**
Editor Class Constructor

Returns:
	void
 */

{
}

Editor::Editor(int w, int h)
/**
Editor Class Constructor

Vars:
	(int) maxHeight: Max Height of the editor
	(int) width: width of the editor
	(int) height: height of the editor
	(int) lineNumbersWidth: width of the line numbers pad
	(int) cursorX: index that the cursor is on (regards wrapping)
	(int) cursorY: current line that the cursor is on (regards wrapping)
	(int) lineX: index that the cursor is on (disregards wrapping)
	(int) lineY: current line that the cursor is on (disregards wrapping)
	(int) scroll: How scrolled the text editor is
	(bool) cursorVisible: Check if cursor is visible
	(bool) highlighting: Whether something is being highlighting
	(vector<char>) specialCharacters: Array of special characters
	(vector<char>) otherCharacters: Array of other side of special characters
	(vector<pair<int, int>>) selectedText: Indexes of text that is being highlighted
	(string) state: Current state of editor
	(string) lastSaved: Last time file was saved
	(int) copiedLines: Check how many lines are being copied
	(int) pasgedLines: Check how many lines are being pasted
	(WINDOW*) textPad: Pad for the editor
	(WINDOW*) linesPad: Pad for the lines

Returns:
	void
 */

{
	maxHeight = 1000;
	width = w;
	height = h;
	height -= 1;
	lineNumbersWidth = 4;
	cursorX = cursorY = 0;
	lineX = lineY = 0;
	scroll = 0;
	cursorVisible = true;

	highlighting = false;
	selectedText = {};
	selectedText.push_back(make_pair(0, 0));
	selectedText.push_back(make_pair(0, 0));

	specialCharacters = {'"', '\'', '(', '[', '{'};
	otherCharacters = {'"', '\'', ')', ']', '}'};

	textPad = newpad(maxHeight, w - lineNumbersWidth);
	linesPad = newpad(maxHeight, lineNumbersWidth);
	width -= lineNumbersWidth;
	state = "";
	lastSaved = "";

	copiedLines = 0;
	pastedLines = 0;
}

void Editor::resetEditor()
/**
Resets editor

Returns:
	void
 */

{
	maxHeight = 1000;
	lineNumbersWidth = 4;
	cursorX = 0;
	cursorY = 0;
	lineX = 0;
	lineY = 0;
	scroll = 0;
	updateDimensions();
	cursorVisible = true;

	highlighting = false;
	selectedText = {};
	selectedText.push_back(make_pair(0, 0));
	selectedText.push_back(make_pair(0, 0));

	state = "";
	lastSaved = "";

	copiedLines = 0;
	pastedLines = 0;
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

void Editor::previousFile()
/**
Changes file to "previous" file in the directory

Args:
	(File) f: File object

Returns:
	void
 */

{
	for (int x = 0; x < (int)file.getFiles().size(); x++)
	{
		if (file.getFiles()[x] == file.getDirectory())
		{
			if (x == 0)
			{
				file.open(file.getFiles()[file.getFiles().size() - 1]);
			}
			else
			{
				file.open(file.getFiles()[x - 1]);
			}
			break;
		}
	}
	if (file.getName() != "")
	{
		setFile(file);
		resetEditor();
		stack.clear();
		setStack(stack);
	}
}

void Editor::nextFile()
/**
Changes file to "next" file in the directory

Args:
	(File) f: File object

Returns:
	void
 */

{
	for (int x = 0; x < (int)file.getFiles().size(); x++)
	{
		if (file.getFiles()[x] == file.getDirectory())
		{
			if (x == (int)file.getFiles().size() - 1)
			{
				file.open(file.getFiles()[0]);
			}
			else
			{
				file.open(file.getFiles()[x + 1]);
			}
			break;
		}
	}
	if (file.getName() != "")
	{
		setFile(file);
		resetEditor();
		stack.clear();
		setStack(stack);
	}
}

void Editor::setStack(HistoryStack s)
/**
Stack Setter Function

Args:
	(HistoryStack) s: HistoryStack object

Returns:
	void
 */

{
	stack = s;
	stack.addToStack(file.getLines(), lineX, lineY);
	stack.truncateStack();
}

void Editor::setSettings(Settings &settings)
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
	tabSize = stoi(settings.getTabSize());
	lineNums = settings.getLineNumbers() == "On" ? true : false;
	autoComplete = settings.getProgrammingMode() == "On" ? true : false;
	tabSpaces = setTab();
	file.setTabSize(tabSpaces);
}

bool Editor::checkSpecialChar(char character)
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

bool Editor::checkOtherChar(char character)
/**
Check if character is a special character

Args:
	(char) character: character inputted
Returns:
	void
 */

{
	return any_of(begin(otherCharacters), end(otherCharacters), [=](char n)
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

int Editor::getNumbersWidth()
/**
lineNumbersWidth Getter Function

Returns:
	int
 */

{
	return lineNumbersWidth;
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

bool Editor::getHighlighting()
/**
Highlighting Getter Function

Returns:
	bool
 */

{
	return highlighting;
}

bool Editor::getCursorVisible()
/**
cursorVisible Getter Function

Returns:
	bool
 */

{
	return cursorVisible;
}

string Editor::getLastSaved()
/**
lastSaved Getter Function

Returns:
	string
 */

{
	return lastSaved;
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
	height -= 1;

	lineNumbersWidth = to_string(file.getLines().size()).length() + 3;

	textPad = newpad(maxHeight, width - lineNumbersWidth);
	linesPad = newpad(maxHeight, lineNumbersWidth);
	keypad(textPad, true);
	nodelay(textPad, true);

	width -= lineNumbersWidth;
	cursorX = getWrappedX(lineX);
	cursorY = getWrappedCursorY(lineY, lineX);
	goToMouse();

	prefresh(linesPad, scroll, 0, 0, 0, height - 3, lineNumbersWidth);
	prefresh(textPad, scroll, 0, 0, lineNumbersWidth, height - 3, width + (lineNumbersWidth - 1));
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
	copiedLines = 0;
	if (state != "ctrlv")
	{
		pastedLines = 0;
	}

	if (state != "add" && state != "ctrlv")
	{
		state = "add";
		stack.addToStack(file.getLines(), lineX, lineY);
		stack.truncateStack();
	}
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
		for (int i = 0; i < (int)specialCharacters.size(); i++)
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

	if (state != "ctrlv")
	{
		stack.updateStack(file.getLines(), lineX, lineY);
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
	copiedLines = 0;
	pastedLines = 0;

	if (state != "insert")
	{
		state = "insert";
		stack.addToStack(file.getLines(), lineX, lineY);
		stack.truncateStack();
	}

	if (highlighting)
	{
		deleteHighlighted();
		endHightlight();
	}

	if (checkSpecialChar(file.getLineWTabs(lineY)[lineX - 1]) && checkOtherChar(file.getLineWTabs(lineY)[lineX]) && checkSpecialChar(character) && autoComplete)
	{
		auto it = std::find(specialCharacters.begin(), specialCharacters.end(), character);
		file.insertChar(lineY, getTabX(lineX), character);
		file.insertChar(lineY, getTabX(lineX + 1), otherCharacters[it - specialCharacters.begin()]);
	}

	else if (!checkOtherChar(character) || !autoComplete || !(file.getLineWTabs(lineY)[lineX] == character))
	{
		file.insertChar(lineY, getTabX(lineX), character);
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
		for (int i = 0; i < (int)specialCharacters.size(); i++)
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
	stack.updateStack(file.getLines(), lineX, lineY);
}

void Editor::backspace()
/**
Deletes previous character if cursor is not at the beginning of a line.
Else cursor goes to the end of previous line and appends the line after it.

Returns:
	void
 */

{
	copiedLines = 0;
	pastedLines = 0;

	if (cursorY != 0 || cursorX != 0)
	{
		if (endOfLine())
		{
			if (state != "end del")
			{
				state = "end del";
				stack.addToStack(file.getLines(), lineX, lineY);
				stack.truncateStack();
			}
		}
		else
		{
			if (state != "middle del")
			{
				state = "middle del";
				stack.addToStack(file.getLines(), lineX, lineY);
				stack.truncateStack();
			}
		}
	}
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
	stack.updateStack(file.getLines(), lineX, lineY);
}

void Editor::deleteLine()
/**
Deletes current line and moves cursor up

Returns:
	void
 */

{
	if (lineY == 0)
	{
		file.setLine(lineY, "");
		lineY = 0;
		lineX = 0;
		cursorX = 0;
		cursorY = getWrappedCursorY(lineY, lineX);
	}
	else
	{
		file.delLine(lineY);
		lineY -= 1;
		lineX = file.getLineLength(lineY);
		cursorX = getWrappedX(lineX);
		cursorY = getWrappedCursorY(lineY, lineX);
	}
}

void Editor::tab()
/**
Replicates an actual tab based on the size of the current tabspace

Returns:
	void
 */

{
	copiedLines = 0;
	if (state != "ctrlv")
	{
		pastedLines = 0;
	}

	if (state != "tab" && state != "ctrlv")
	{
		state = "tab";
		stack.addToStack(file.getLines(), lineX, lineY);
		stack.truncateStack();
	}
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
	if (state != "ctrlv")
	{
		stack.updateStack(file.getLines(), lineX, lineY);
		state = "";
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
	copiedLines = 0;
	if (state != "ctrlv")
	{
		pastedLines = 0;
	}

	if (state != "enter" and state != "ctrlv")
	{
		state = "enter";
		stack.addToStack(file.getLines(), lineX, lineY);
		stack.truncateStack();
	}
	int startTabs = 0;
	for (int x = 0; x < (int)file.getLine(lineY).length(); x++)
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
	if (state != "ctrlv")
	{
		stack.updateStack(file.getLines(), lineX, lineY);
	}
}

void Editor::ctrlS(StatusBar &status)
/**
Saves the file

Args:
	(StatusBar&) status: StatusBar Object

Returns:
	void
 */

{
	state = "ctrls";
	copiedLines = 0;
	pastedLines = 0;

	if (file.save())
	{
		status.setInfo("Changes Saved.", false);
		lastSaved = status.getDateString();
	}
	else
	{
		status.setInfo("Couldn't Save Changes.", true);
	}
}

void Editor::ctrlA()
{
	copiedLines = 0;
	pastedLines = 0;

	highlighting = true;
	selectedText[0].first = 0;
	selectedText[0].second = 0;
	selectedText[1].first = file.getLineLength(file.getLines().size() - 1);
	selectedText[1].second = file.getLines().size() - 1;
}

void Editor::ctrlC()
{
	pastedLines = 0;
	FILE *pipe = popen("xclip -selection clipboard", "w");
	if (pipe)
	{
		string str;
		if (!highlighting)
		{
			str = file.getLine(lineY);
			copiedLines = 1;
		}
		else
		{
			copiedLines = (orderHighlight()[1].second - orderHighlight()[0].second) + 1;
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
/**
Pastes text from clipboard

Returns:
	void
 */

{
	copiedLines = 0;
	pastedLines = 1;
	if (state != "ctrlv")
	{
		state = "ctrlv";
		stack.addToStack(file.getLines(), lineX, lineY);
		stack.truncateStack();
	}
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
		for (int x = 0; x < (int)result.length(); x++)
		{
			if (result[x] == '\n')
			{
				pastedLines += 1;
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
	stack.updateStack(file.getLines(), lineX, lineY);
	state = "";
}

void Editor::ctrlX()
/**
Copies the line and deletes it

Returns:
	void
 */

{
	copiedLines = 1;
	pastedLines = 0;
	if (state != "ctrlx")
	{
		state = "ctrlx";
		stack.addToStack(file.getLines(), lineX, lineY);
		stack.truncateStack();
	}
	const string str = file.getLine(lineY);
	FILE *pipe = popen("xclip -selection clipboard", "w");
	if (pipe)
	{
		// Write the text to the pipe
		fwrite(str.c_str(), sizeof(char), str.size(), pipe);
		pclose(pipe);
		deleteLine();
	}
	stack.updateStack(file.getLines(), lineX, lineY);
}

void Editor::ctrlY()
/**
Function that redoes

Returns:
	void
 */

{
	copiedLines = 0;
	pastedLines = 0;

	if (state != "ctrly")
	{
		state = "ctrly";
	}
	endHightlight();
	stack.redo();
	file.setLines(stack.getText());
	lineX = stack.getLineX();
	lineY = stack.getLineY();
	cursorX = getWrappedX(lineX);
	cursorY = getWrappedCursorY(lineY, lineX);
}

void Editor::ctrlZ()
/**
Function that undos

Returns:
	void
 */

{
	copiedLines = 0;
	pastedLines = 0;

	if (state != "ctrlz")
	{
		state = "ctrlz";
	}
	endHightlight();
	stack.undo();
	file.setLines(stack.getText());
	lineX = stack.getLineX();
	lineY = stack.getLineY();
	cursorX = getWrappedX(lineX);
	cursorY = getWrappedCursorY(lineY, lineX);
}

void Editor::goToMouse()
/**
Goes to the mouse if its not on the screen

Returns:
	void
 */

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
/**
Scrolls up

Returns:
	void
 */

{
	if (scroll > 0)
	{
		scroll--;
	}
}

void Editor::scrollDown()
/**
Scrolls down

Returns:
	void
 */

{
	if ((int)file.getLines().size() - scroll >= height / 2)
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
		stack.updateCursorStack(lineX, lineY);
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
	stack.updateCursorStack(lineX, lineY);
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
	}
	else
	{
		if (lineY != 0)
		{
			lineX = file.getLine(lineY - 1).length();
			lineY--;
		}
	}
	cursorX = getWrappedX(lineX);
	cursorY = getWrappedCursorY(lineY, lineX);
	stack.updateCursorStack(lineX, lineY);
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
	}
	else
	{
		if (lineY != (int)file.getLines().size() - 1)
		{
			lineX = 0;
			lineY++;
		}
	}
	cursorX = getWrappedX(lineX);
	cursorY = getWrappedCursorY(lineY, lineX);
	stack.updateCursorStack(lineX, lineY);
}

void Editor::highlight()
/**
Starts highlighting

Returns:
	void
 */

{
	if (!highlighting)
	{
		copiedLines = 0;
		pastedLines = 0;
		highlighting = true;
		selectedText[0].first = lineX;
		selectedText[0].second = lineY;
	}
}

void Editor::endHightlight()
/**
Ends highlighting

Returns:
	void
 */

{
	selectedText[0].first = 0;
	selectedText[0].second = 0;
	selectedText[1].first = 0;
	selectedText[1].second = 0;
	highlighting = false;
}

vector<pair<int, int>> Editor::orderHighlight()
/**
Orders the vector so first pair is the starting highlight index

Returns:
	vector<pair<int, int>>
 */

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
/**
Deletes all text that is highlighted

Returns:
	void
 */

{
	if (highlighting)
	{
		lineX = orderHighlight()[1].first;
		lineY = orderHighlight()[1].second;
		cursorX = getWrappedX(lineX);
		cursorY = getWrappedCursorY(lineY, lineX);
		while (true)
		{
			if (lineX == orderHighlight()[0].first && lineY == orderHighlight()[0].second)
			{
				break;
			}
			else if (lineY == orderHighlight()[1].second || lineY == orderHighlight()[0].second)
			{
				backspace();
			}
			else
			{
				deleteLine();
			}
		}
	}
}

int Editor::find(string text)
/**
Finds text in the file and returns how many times its found

Args:
	(string) text: text to find
Returns:
	int
 */

{
	if (text == "")
	{
		return 0;
	}
	int occurrences = 0;
	std::string::size_type pos = 0;
	for (const string &line : file.getLines())
	{
		while ((pos = line.find(text, pos)) != std::string::npos)
		{
			++occurrences;
			pos += text.length();
		}
		pos = 0;
	}

	return occurrences;
}

void Editor::replaceAllInstances(string from, string to)
/**
Replaces all of a specific string inside the file with another string

Args:
	(string) from: String that will be replaced
	(string) to: String that's replacing it
Returns:
	void
 */

{
	if (from != "")
	{
		for (int x = 0; x < (int)file.getLines().size(); x++)
		{
			file.setLine(x, file.replaceAll(file.getLine(x), from, to));
		}
		lineX = file.getLineLength(lineY);
		cursorX = getWrappedX(lineX);
		cursorY = getWrappedCursorY(lineY, lineX);
	}
}

void Editor::printLine(string copiedLine, int &tempY)
/**
prints whole line together

Args:
	(string) copiedLine: Line to print
	(int) &tempY: Current y position to print the line
Returns:
	void
 */

{
	while (true)
	{
		// Handles line wrapping
		if ((int)copiedLine.length() <= (width - 1))
		{
			string text = copiedLine;
			mvwprintw(textPad, tempY, 0, text.c_str(), "%s");
			tempY++;
			break;
		}
		else
		{
			string text = copiedLine.substr(0, width - 1);
			mvwprintw(textPad, tempY, 0, text.c_str(), "%s");
			tempY++;
			copiedLine.erase(0, width - 1);
		}
	}
}

void Editor::printLineByChar(string copiedLine, int lineNum, int &tempY)
/**
prints line by character to check for lines being highlighted

Args:
	(string) copiedLine: Line to print
	(int) lineNum: Current line number
	(int) &tempY: Current y position to print the line
Returns:
	void
 */

{
	int printX = 0;
	for (int x = 0; x < (int)copiedLine.length(); x++)
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
	}
	tempY++;
}

void Editor::findPrintLineByChar(string copiedLine, string findTxt, int &tempY)
/**
prints line and highlights characters that are being found using ctrl-f

Args:
	(string) copiedLine: Line to print
	(string) findTxt: text to be highlighted
	(int) &tempY: Current y position to print the line
Returns:
	void
 */

{
	vector<int> index = {};
	if (findTxt != "")
	{
		std::string::size_type pos = 0;
		while ((pos = copiedLine.find(findTxt, pos)) != std::string::npos)
		{
			index.push_back(pos);
			for (int i = 1; i < (int)findTxt.length(); i++)
			{
				index.push_back(pos + i);
			}
			pos += findTxt.length();
		}
	}

	if (index.size() > 0)
	{
		int printX = 0;
		for (int x = 0; x < (int)copiedLine.length(); x++)
		{
			if (std::find(index.begin(), index.end(), x) != index.end())
			{
				wattron(textPad, COLOR_PAIR(1));
			}
			mvwaddch(textPad, tempY, printX, copiedLine[x]);
			wattroff(textPad, COLOR_PAIR(1));

			printX += 1;
			if (printX == width - 1)
			{
				printX = 0;
				tempY++;
			}
		}
		tempY++;
	}
	else
	{
		printLine(copiedLine, tempY);
	}
}

void Editor::updateStatus(StatusBar &status)
/**
Updates status based on editor state

Args:
	(StatusBar&) status: StatusBar object
Returns:
	void
 */

{
	if (state == "ctrls")
	{
		return;
	}

	std::string text;
	if (state == "ctrlz")
	{
		if (stack.getQueueNum() > 0)
		{
			status.setInfo("Undo", false);
		}
		else
		{
			status.setInfo("Undo Limit Reached", true);
		}
	}
	else if (state == "ctrly")
	{
		if (stack.getQueueNum() < stack.getStackSize() - 1)
		{
			status.setInfo("Redo", false);
		}
		else
		{
			status.setInfo("Redo Limit Reached", true);
		}
	}
	else if (copiedLines > 0)
	{
		string word = copiedLines == 1 ? "Line" : "Lines";
		text = std::format("{} {} Copied", copiedLines, word);
		status.setInfo(text, false);
	}
	else if (pastedLines > 0)
	{
		string word = pastedLines == 1 ? "Line" : "Lines";
		text = std::format("{} {} Pasted", pastedLines, word);
		status.setInfo(text, false);
	}
	else if (highlighting)
	{
		string word = (orderHighlight()[1].second - orderHighlight()[0].second) + 1 == 1 ? "Line" : "Lines";
		text = std::format("{} {} Highlighted", (orderHighlight()[1].second - orderHighlight()[0].second) + 1, word);
		status.setInfo(text, false);
	}
	else
	{
		string filename = file.getName() == "" ? "Untitled File" : file.getName();
		text = std::format("Editing [{}]   |   Ln {} / {}", filename, lineY + 1, file.getLines().size());
		status.setInfo(text, false);
	}
}

void Editor::writeToScreen(StatusBar &status)
/**
Clears the screen and writes each line based on the File object and refreshes the screen at the end

Args:
	(bool) end: Indicates whether cursor should go to the end

Returns:
	void
 */

{
	int strSize = to_string(file.getLines().size()).length();
	if ((lineNums && strSize >= 1 && lineNumbersWidth - 3 != strSize) || getWrappedCursorY(file.getLines().size() - 1, file.getLine(file.getLines().size() - 1).length()) + height >= maxHeight)
	{
		if (getWrappedCursorY(file.getLines().size() - 1, file.getLine(file.getLines().size() - 1).length()) + height >= maxHeight)
		{
			maxHeight += 1000;
		}
		updateDimensions();
	}

	int lineNum = 0;

	int tempY = 0;

	werase(linesPad);
	werase(textPad);

	wmove(textPad, 0, 0);
	wmove(linesPad, 0, 0);

	for (const string &line : file.getLines())
	{
		lineNum++;
		wmove(linesPad, tempY, 0);
		string nums = "";
		if (lineNums) // Checks if line numbers should be shown
		{
			for (int i = 0; i < ((lineNumbersWidth - 2) - (int)to_string(lineNum).length()); i++)
			{
				nums = nums.append(" ");
			}
			nums += to_string(lineNum);
			mvwprintw(linesPad, tempY, 0, nums.c_str(), "%s");

			wattron(linesPad, COLOR_PAIR(2));
			mvwprintw(linesPad, tempY, lineNumbersWidth - 2, "| ");
			wattroff(linesPad, COLOR_PAIR(2));
		}
		else
		{
			for (int i = 0; i < (lineNumbersWidth - 3); i++)
			{
				nums = nums.append(" ");
			}
			nums += "~";
			mvwprintw(linesPad, tempY, 0, nums.c_str(), "%s");

			wattron(linesPad, COLOR_PAIR(2));
			mvwprintw(linesPad, tempY, lineNumbersWidth - 2, "| ");
			wattroff(linesPad, COLOR_PAIR(2));
		}

		string copiedLine = file.replaceAll(line, "\t", tabSpaces); // Replaces the tabspaces

		if (status.getState() != "find" && status.getState() != "replace")
		{
			if (highlighting)
			{
				if (lineNum - 1 > orderHighlight()[0].second && lineNum - 1 < orderHighlight()[1].second)
				{
					wattron(textPad, COLOR_PAIR(1));
					if (copiedLine.length() == 0)
					{
						mvwprintw(textPad, tempY, 0, " ");
					}
					printLine(copiedLine, tempY);
					wattroff(textPad, COLOR_PAIR(1));
				}
				else if (lineNum - 1 == orderHighlight()[0].second || lineNum - 1 == orderHighlight()[1].second)
				{
					printLineByChar(copiedLine, lineNum - 1, tempY);
				}
				else
				{
					printLine(copiedLine, tempY);
				}
			}
			else
			{
				printLine(copiedLine, tempY);
			}
		}
		else
		{
			findPrintLineByChar(copiedLine, status.getFindTxt(), tempY);
		}
	}

	wmove(textPad, cursorY, cursorX);

	wmove(linesPad, tempY, 0);
	string nums = "";
	for (int i = 0; i < (lineNumbersWidth - 3); i++)
	{
		nums = nums.append(" ");
	}
	nums.append("~");
	for (int n = tempY; n < (int)file.getLines().size() + height * 2; n++)
	{
		mvwprintw(linesPad, n, 0, nums.c_str(), "%s");

		wattron(linesPad, COLOR_PAIR(2));
		mvwprintw(linesPad, n, lineNumbersWidth - 2, "| ");
		wattroff(linesPad, COLOR_PAIR(2));
	}

	prefresh(linesPad, scroll, 0, 0, 0, height - 2, lineNumbersWidth);
	prefresh(textPad, scroll, 0, 0, lineNumbersWidth, height - 2, width + (lineNumbersWidth - 1));

	if (cursorY + 1 > scroll && cursorY + 1 < scroll + height)
	{
		cursorVisible = true;
	}
	else
	{
		cursorVisible = false;
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
/**
Gets the current cursor Y (no matter line wrapping)

Args:
	(string) copiedLine: Line to print
	(int) lineNum: Current line number
	(int) &tempY: Current y position to print the line
Returns:
	void
 */

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

	vector<int> tabs = file.getTabs(lineY, tabSize);
	for (int x = (int)tabs.size() - 1; x != -1; x--)
	{
		if (tabs[x] - tabSize < (int)copiedLine.length())
		{
			copiedLine.replace(tabs[x] - tabSize, tabSize, "\t");
		}
	}

	return copiedLine.length();
}
