#pragma once
#include <iostream>
#include <vector>
#include "file.h"

using namespace std;

File::File()
/**
File Class Constructor

Vars:
    vector<string? lines: Lines that are in the file

Returns:
    void
 */

{
    lines = {""};
}

void File::setName(string n)
/**
Name Setter Function

Args:
    (string) n: Name of the file

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

string File::getLine(int lineNum)
/**
Line Getter Function

Args:
    (int) lineNum: Line Number of the file

Returns:
    strinb
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
    lines.at(lineNum) = lines.at(lineNum).substr(0, x) + character + lines.at(lineNum).substr(x, lines.at(lineNum).length());
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