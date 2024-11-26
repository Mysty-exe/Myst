#pragma once
#include <iostream>
#include <vector>

using namespace std;

class HistoryStack
/**
 * Class that represents the history stack
 */

{
private:
    int queueNum;
    vector<vector<string>> textStack;
    vector<pair<int, int>> cursorStack;

public:
    HistoryStack();
    void addToStack(vector<string> text, int lineX, int lineY);
    void updateStack(vector<string> text, int lineX, int lineY);
    void truncateStack();
    void updateCursorStack(int lineX, int lineY);
    void undo();
    void redo();
    vector<string> getText();
    int getLineX();
    int getLineY();
};
