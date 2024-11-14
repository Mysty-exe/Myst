#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

class File
/**
 * Class that represents a File
 */

{
private:
    string name;
    string tabsize;
    vector<string> lines;

public:
    File();
    string replaceAll(string str, const string from, const string to);
    string getName();
    void setName(string n);
    void open(string n);
    bool save();
    void setTabSize(string tab);
    vector<string> getLines();
    void printLines();
    int getLineLength(int lineNum);
    string getLine(int lineNum);
    void setLine(int lineNum, string str);
    void addChar(int lineNum, char character);
    void insertChar(int lineNum, int x, char character);
    void delChar(int lineNum, int x);
    void addStr(int lineNum, string str);
    void insertLine(int lineNum, string line);
    void delLine(int lineNum);
};