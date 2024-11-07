#pragma once
#include <iostream>

using namespace std;

class File
/**
 * Class that represents a File
 */

{
private:
    string name;
    vector<string> lines;

public:
    File();
    void setName(string n);
    vector<string> getLines();
    string getLine(int lineNum);
    void setLine(int lineNum, string str);
    void addChar(int lineNum, char character);
    void insertChar(int lineNum, int x, char character);
    void delChar(int lineNum, int x);
    void addStr(int lineNum, string str);
    void insertLine(int lineNum, string line);
    void delLine(int lineNum);
};