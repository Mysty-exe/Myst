#pragma once
#include <iostream>
#include <vector>
#include "history.h"

HistoryStack::HistoryStack()
{
    queueNum = -1;
    textStack = {};
    cursorStack = {};
}

void HistoryStack::addToStack(vector<string> text, int lineX, int lineY)
{
    textStack.push_back(text);
    cursorStack.push_back(make_pair(lineX, lineY));
    queueNum++;
}

void HistoryStack::updateStack(vector<string> text, int lineX, int lineY)
{
    textStack[queueNum] = text;
    cursorStack[queueNum] = make_pair(lineX, lineY);
}

void HistoryStack::truncateStack()
{
    for (int x = textStack.size() - 1; x != queueNum; x--)
    {
        textStack.erase(textStack.begin() + x);
        cursorStack.erase(cursorStack.begin() + x);
    }
}

void HistoryStack::updateCursorStack(int lineX, int lineY)
{
    cursorStack[queueNum] = make_pair(lineX, lineY);
}

void HistoryStack::undo()
{
    if (queueNum > 0)
    {
        queueNum--;
    }
}

void HistoryStack::redo()
{
    if (queueNum < textStack.size() - 1)
    {
        queueNum++;
    }
}

vector<string> HistoryStack::getText()
{
    return textStack[queueNum];
}

int HistoryStack::getLineX()
{
    return cursorStack[queueNum].first;
}

int HistoryStack::getLineY()
{
    return cursorStack[queueNum].second;
}
