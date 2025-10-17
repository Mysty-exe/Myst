#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;

class File
/**
 * Class that represents a File
 */

{
private:
    string fileName, absoluteFile;
    string tabsize;
    vector<string> files;
    vector<string> lines;

public:
    File();
    bool unsavedFile();
    static bool overwrite(string fileName);
    static bool fileError(string filePath);

    string getName();
    string getDirectory();
    void setName(string n);
    void getFilesInDirectory();

    void open(string n);
    int save();

    void setTabSize(string tab);
    vector<string> getFiles();
    vector<string> getLines();
    void setLines(vector<string> lines);

    void printLines();
    int getLineLength(int lineNum);
    string getLine(int lineNum);
    string getLineWTabs(int lineNum);
    vector<int> getTabs(int lineNum, int tabSize);
    void setLine(int lineNum, string str);
    void addChar(int lineNum, char character);
    void insertChar(int lineNum, int x, char character);
    void delChar(int lineNum, int x);
    void addStr(int lineNum, string str);
    void insertLine(int lineNum, string line);
    void delLine(int lineNum);
    string replaceAll(string str, const string from, const string to);
};