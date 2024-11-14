#pragma once
#include <iostream>
#include <vector>
#include "file.h"

using namespace std;

File::File()
/**
File Class Constructor

Vars:
    (string) name: Name of the file
    (vector<string?) lines: Lines that are in the file

Returns:
    void
 */

{
    name = "";
    lines = {};
}

string File::replaceAll(string str, const string from, const string to)
/**
Replaces all instances of a string inside another string

Args:
    (string) str: String that will have the string to be replaced
    (string) from: String that is being replaced in "str"
    (string) to: String that is replacing "from" in "str"

Returns:
    string
 */

{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) // Loop till "from" not in the string
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

void File::open(string n)
/**
Opens text file and puts it into lines vector

Args:
    (string) n: Name of the file

Returns:
    void
 */

{
    setName(n);

    int lineNum = 0;
    string text;
    lines = {};
    fstream readFile(name);
    if (readFile.fail())
    {
        insertLine(0, "");
    }
    else
    {
        while (getline(readFile, text))
        {
            insertLine(lineNum, text);
            lineNum++;
        }
    }

    readFile.close();
}

bool File::save()
/**
Saves the file

Returns:
    bool
 */

{
    fstream writeFile(name, ios::out | ios::trunc);
    if (writeFile.fail())
    {
        return false;
    }

    int counter = 0;
    for (const string &line : lines)
    {
        writeFile << line;
        if (counter != (int)lines.size() - 1)
        {
            writeFile << "\n";
        }
        counter += 1;
    }
    writeFile.close();

    return true;
}

void File::setTabSize(string tab)
/**
Sets size of the tab for the file

Args:
    (string) tab: Size of the new tab

Returns:
    void
 */

{
    tabsize = tab;
}

string File::getName()
/**
Name Getter Function

Returns:
    string
 */

{
    return name;
}

void File::setName(string n)
/**
Name Setter Function

Args:
    (string) n: Name to replace current name

Returns:
    void
 */

{
    name = n;
}

vector<string> File::getLines()
/**
Lines Getter Function

Returns:
    vector<string>
 */

{
    return lines;
}

void File::printLines()
/**
Prints each line out

Returns:
    Void
 */

{
    for (const string &line : lines)
    {
        cout << line << endl;
    }
}

int File::getLineLength(int lineNum)
/**
Gets Length of Line

Args:
    (int) lineNum: Line Number of the file

Returns:
    int
 */

{
    string copiedLine = replaceAll(lines.at(lineNum), "\t", tabsize);
    return copiedLine.length();
}

string File::getLine(int lineNum)
/**
Line Getter Function

Args:
    (int) lineNum: Line Number of the file

Returns:
    string
 */

{
    return lines.at(lineNum);
}

void File::setLine(int lineNum, string str)
/**
Line Setter Function

Args:
    (int) lineNum: Line number of the file
    (string) str: String that you want to replace line contents with

Returns:
    void
 */

{
    lines.at(lineNum) = str;
}

void File::addChar(int lineNum, char character)
/**
Adds a character to a line in the file

Args:
    (int) lineNum: Line Number of the file
    (char) character: Character you want to add

Returns:
    void
 */

{
    lines.at(lineNum) = lines.at(lineNum) + character;
}

void File::insertChar(int lineNum, int x, char character)
/**
Insert a character in between two characters in a line

Args:
    (int) lineNum: Line Number of the file
    (int) x: Index to insert the character
    (char) character: Character to insert

Returns:
    void
 */

{
    lines.at(lineNum) = lines.at(lineNum).substr(0, x) + character + lines.at(lineNum).substr(x, getLineLength(lineNum));
}

void File::delChar(int lineNum, int x)
/**
Delete a character in a line

Args:
    (int) lineNum: Line Number of the file
    (int) x: Index of the character to delete

Returns:
    void
 */

{
    lines.at(lineNum) = lines.at(lineNum).erase(x, 1);
}

void File::addStr(int lineNum, string str)
/**
Add a full string to a line

Args:
    (int) lineNum: Line Number of the file
    (string) str: String to add to the end of the line

Returns:
    void
 */

{
    lines.at(lineNum) = lines.at(lineNum) + str;
}

void File::insertLine(int lineNum, string line)
/**
Insert a line into the file

Args:
    (int) lineNum: Line Number of the file to insert from
    (string) line: String that you want to insert

Returns:
    void
 */

{
    lines.insert(lines.begin() + lineNum, line);
}

void File::delLine(int lineNum)
/**
Delete a line

Args:
    (int) lineNum: Line Number of the file to delete

Returns:
    void
 */

{
    lines.erase(lines.begin() + lineNum);
}