#pragma once
#include "file.h"

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
    fileName = "";
    absoluteFile = "";
    files = {};
    lines = {};
}

bool File::unsavedFile()
/**
Checks if file has been saved or not

Returns:
    bool
 */

{
    string text;
    int lineNum = 0;
    fstream readFile(absoluteFile);
    if (readFile.fail())
    {
        return true;
    }
    while (getline(readFile, text))
    {
        if ((int)lines.size() > lineNum)
        {
            if (text != getLine(lineNum))
            {
                return true;
            }
        }
        else
        {
            return true;
        }
        lineNum += 1;
    }
    return false;
}

bool File::overwrite(string fileName)
/**
Checks if file already exists

Args:
    (string) fileName: Name of the file
Returns:
    bool
 */

{
    string absoluteFile = filesystem::absolute(fileName);
    fstream readFile(absoluteFile);
    if (readFile.fail())
    {
        return false;
    }
    return true;
}

bool File::fileError(string filePath)
/**
Checks if file is valid

Args:
    (string) file: Name of the file

Returns:
    bool
 */

{
    filesystem::path dir = filesystem::path(filePath).parent_path();
    if (dir.empty())
    {
        dir = std::filesystem::current_path();
    }

    error_code ec;
    if (!filesystem::exists(dir) || !filesystem::is_directory(dir, ec))
    {
        cout << "Directory does not exist: " << dir << endl;
        return true;
    }

    auto perms = filesystem::status(dir).permissions();
    if ((perms & filesystem::perms::owner_write) == filesystem::perms::none)
    {
        cout << "Directory is not writable: " << dir << endl;
        return false;
    }

    return false;
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
    fstream readFile(absoluteFile);
    lines = {};
    if (readFile.fail())
    {
        insertLine(0, "");
    }
    else
    {
        lines = {};
        while (getline(readFile, text))
        {
            for (int x = text.length(); x != -1; x--)
            {
                if (text[x] == '\r' || text[x] == '\n')
                {
                    text = text.substr(0, text.length() - 1);
                }
            }
            insertLine(lineNum, text);
            lineNum++;
        }
    }
    if (lines.size() == 0)
    {
        insertLine(0, "");
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
    error_code ec;
    fstream writeFile(absoluteFile, ios::out | ios::trunc);
    if (filesystem::is_directory(absoluteFile, ec))
    {
        fstream writeFile(absoluteFile + "/" + fileName, ios::out | ios::trunc);
    }

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
    return fileName;
}

string File::getDirectory()
/**
Directory Getter Function

Returns:
    string
 */

{
    return absoluteFile;
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
    fileName = n;
    if (fileName == "")
    {
        absoluteFile = filesystem::current_path();
    }
    else
    {
        error_code ec;
        absoluteFile = filesystem::absolute(fileName);
        if (!filesystem::is_regular_file(absoluteFile, ec) && !filesystem::is_directory(absoluteFile, ec))
        {
            absoluteFile = filesystem::path(absoluteFile).parent_path();
        }

        if (fileName.find('/') != string::npos && !filesystem::is_directory(fileName, ec))
        {
            fileName = fileName.substr(fileName.find_last_of("/") + 1, fileName.length() - fileName.find_last_of("/"));
        }
        else if (filesystem::is_directory(fileName, ec))
        {
            fileName = "";
        }
    }

    getFilesInDirectory();
}

void File::getFilesInDirectory()
/**
Gets all the files in a directory and puts it into a vector

Returns:
    void
 */

{
    files = {};
    error_code ec;
    for (auto &p : filesystem::directory_iterator(filesystem::path(absoluteFile).parent_path()))
    {
        if (filesystem::is_regular_file(p.path(), ec))
        {

            files.push_back(p.path());
        }
    }
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

vector<string> File::getFiles()
/**
Files Getter Function

Returns:
    vector<string>
 */

{
    return files;
}

void File::setLines(vector<string> l)
/**
Lines Setter Function

Args:
    (vector<string>) l: Lines to replace

Returns:
    void
 */

{
    lines = l;
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

string File::getLineWTabs(int lineNum)
/**
Line Getter Function

Args:
    (int) lineNum: Line Number of the file

Returns:
    string
 */

{
    return replaceAll(lines.at(lineNum), "\t", tabsize);
}

vector<int> File::getTabs(int lineNum, int tabSize)
/**
Get the number of tabs in the line

Args:
    (int) lineNum: Line Number of the file
    (int) tabSize: Number tab size

Returns:
    string
 */

{
    vector<int> tabs = {};
    int value = 0;
    for (int x = 0; x < (int)getLine(lineNum).length(); x++)
    {
        if (getLine(lineNum)[x] == '\t')
        {
            value += tabSize;
            tabs.push_back(value);
        }
        else
        {
            value++;
        }
    }

    return tabs;
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
