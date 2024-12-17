#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

enum Token
/**
 * Enum that represents a token
 */

{
    MAIN = 1,
    TEXT = 2,
    KEYWORD = 3,
    STRING = 4,
    COMMENT = 5,
    NUMBER = 6,
    DELIMITER = 7,
    OPERATOR = 8,
    SPECIAL = 9,
    PUNCTUATION = 10,
    OTHER = 11,
    SPACE = 12,
    DOC = 13
};

class LexerScanner
/**
 * Class that represents a lexer
 */

{
private:
    vector<string> punctuation;
    vector<string> delimiters;
    vector<string> singleOperators;
    vector<string> doubleOperators;
    vector<string> keyWords;
    vector<string> specialChars;
    vector<string> functions;
    bool docString;

public:
    LexerScanner();
    bool isNum(string txt);
    void setDocString(bool doc);
    vector<string> getLexemes(string code);
    vector<pair<string, Token>> getTokens(string code);
};
