#pragma once
#include "history.h"

HistoryStack::HistoryStack()
/**
HistoryStack Class Constructor

Args:
    (int) queueNum: current queue in the history
    (vector<string>) textStack: vector of all text strings in history
    (vector<int, int>) queueNum: vector of cursor indexes in history

Returns:
    void
 */

{
    queueNum = -1;
    textStack = {};
    cursorStack = {};
}

int HistoryStack::getQueueNum()
/**
queueNum Getter Function

Returns:
    int
 */


{
    return queueNum;
}

int HistoryStack::getStackSize()
/**
stackSize Getter Function

Returns:
    int
 */


{
    return textStack.size();
}

vector<string> HistoryStack::getText()
/**
text Getter Function

Returns:
    vector<string>
 */

{
    return textStack[queueNum];
}

int HistoryStack::getLineX()
/**
lineX Getter Function

Returns:
    int
 */

{
    return cursorStack[queueNum].first;
}

int HistoryStack::getLineY()
/**
lineY Getter Function

Returns:
    int
 */

{
    return cursorStack[queueNum].second;
}

void HistoryStack::addToStack(vector<string> text, int lineX, int lineY)
/**
adds a queue to textStack and cursorStack

Args:
    (vector<string>) text: text to add
    (int) lineX: x index of cursor to add
    (int) lineY: y index of cursor to add
Returns:
    void
 */

{
    textStack.push_back(text);
    cursorStack.push_back(make_pair(lineX, lineY));
    queueNum++;
}

void HistoryStack::updateStack(vector<string> text, int lineX, int lineY)
/**
updates a queue to textStack and cursorStack

Args:
    (vector<string>) text: text to update
    (int) lineX: x index of cursor to update
    (int) lineY: y index of cursor to update
Returns:
    void
 */

{
    textStack[queueNum] = text;
    cursorStack[queueNum] = make_pair(lineX, lineY);
}

void HistoryStack::truncateStack()
/**
Truncates the stack if queue num is less than size of stack

Returns:
    void
 */

{
    for (int x = textStack.size() - 1; x != queueNum; x--)
    {
        textStack.erase(textStack.begin() + x);
        cursorStack.erase(cursorStack.begin() + x);
    }
}

void HistoryStack::updateCursorStack(int lineX, int lineY)
/**
Updates cursor in the stack

Args:
    (int) lineX: x index of cursor to add
    (int) lineY: y index of cursor to add
Returns:
    void
 */

{
    cursorStack[queueNum] = make_pair(lineX, lineY);
}

void HistoryStack::undo()
/**
goes back to previous queue in vector

Returns:
    void
 */

{
    if (queueNum > 0)
    {
        queueNum--;
    }
}

void HistoryStack::redo()
/**
goes to next queue in vector

Returns:
    void
 */

{
    if (queueNum < getStackSize() - 1)
    {
        queueNum++;
    }
}

void HistoryStack::clear()
/**
Clears the stack

Returns:
    void
 */

{
    queueNum = -1;
    textStack.clear();
    cursorStack.clear();
}
