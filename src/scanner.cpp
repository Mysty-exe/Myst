#include "scanner.h"

LexerScanner::LexerScanner()
{
    punctuation = {","};
    delimiters = {"(", ")", "[", "]", "{", "}", ":", ";"};
    singleOperators = {"=", ">", "<", "+", "-", "*", "/", "%"};
    doubleOperators = {"==", "<=", ">=", "+=", "-=", "*=", "/=", "!="};
    specialChars = {R"(\n)", R"(\t)", R"(\r)", R"(\e)", R"(\a)", R"(\f)", R"(\v)", R"(\b)", R"(\')", R"(\")", R"(\\)"};
    keyWords = {"and", "as", "assert", "break", "class", "continue", "def", "del", "elif", "else", "except", "False", "True", "finally", "for", "from", "global", "if", "import", "in", "is", "lambda", "None", "nonlocal", "not", "or", "pass", "raise", "try", "while", "with", "return", "yield"};
    functions = {"abs", "all", "any", "ascii", "bin", "bool", "breakpoint", "bytearray",
                 "bytes", "callable", "chr", "classmethod", "compile", "complex", "delattr",
                 "dict", "dir", "divmod", "enumerate", "eval", "exec", "filter", "float",
                 "format", "frozenset", "getattr", "globals", "hasattr", "hash", "help",
                 "hex", "id", "input", "int", "isinstance", "issubclass", "iter", "len",
                 "list", "locals", "map", "max", "memoryview", "min", "next", "object",
                 "oct", "open", "ord", "pow", "print", "property", "range", "repr", "reversed",
                 "round", "set", "setattr", "slice", "sorted", "staticmethod", "str", "sum",
                 "super", "tuple", "type", "vars", "zip", "__import__"};
    docString = false;
}

bool LexerScanner::isNum(string txt)
/**
Checks if every character in txt is a number

Args:
    (string) txt: Text to check
Returns:
    bool
 */

{
    int decimal = 0;
    for (int x = 0; x < (int)txt.length(); x++)
    {
        if (txt[x] == '.')
        {
            decimal += 1;
        }
        else if (!isdigit(txt[x]))
        {
            return false;
        }
        if (decimal > 1)
        {
            return false;
        }
    }
    return true;
}

void LexerScanner::setDocString(bool doc)
/**
docString Setter Function

Args:
    (bool) doc = new doc bool
Returns:
    void
 */

{
    docString = doc;
}

vector<string> LexerScanner::getLexemes(string code)
/**
Gets all the lexemes in the line

Args:
    (string) code: Line to check
Returns:
    vector<string>
 */

{
    int i = 0;
    vector<string> lexemes = {};
    string currentLexeme = "";
    bool startString = false;
    bool comment = false;

    for (int x = 0; x < (int)code.length(); x++)
    {
        if (code.substr(i, 3) == "\"\"\"" || code.substr(i, 3) == "'''")
        {
            docString = not docString;
            if (currentLexeme != "")
            {
                lexemes.push_back(currentLexeme);
                currentLexeme = "";
            }
            currentLexeme += code[i];
        }
        else if ((code.substr(i, 1) == "\"" || code.substr(i, 1) == "'") && !comment)
        {
            if (!startString)
            {
                startString = true;
                if (currentLexeme != "")
                {
                    lexemes.push_back(currentLexeme);
                    currentLexeme = "";
                }
                currentLexeme += code[i];
            }
            else
            {
                currentLexeme += code[i];
                lexemes.push_back(currentLexeme);
                currentLexeme = "";
                startString = false;
            }
        }

        else if (startString || comment || docString)
        {
            currentLexeme += code[i];
        }
        else if (code.substr(i, 1) == "#")
        {
            comment = true;
            if (currentLexeme != "")
            {
                lexemes.push_back(currentLexeme);
                currentLexeme = "";
            }
            currentLexeme += code[i];
        }
        else if ((find(delimiters.begin(), delimiters.end(), code.substr(i, 1)) != delimiters.end() || code.substr(i, 1) == ",") && !startString && !comment)
        {
            if (currentLexeme != "")
            {
                lexemes.push_back(currentLexeme);
                currentLexeme = "";
            }
            lexemes.push_back(code.substr(i, 1));
        }
        else if (find(doubleOperators.begin(), doubleOperators.end(), code.substr(i, 2)) != doubleOperators.end() && !startString && !comment)
        {
            if (currentLexeme != "")
            {
                lexemes.push_back(currentLexeme);
                currentLexeme = "";
            }
            lexemes.push_back(code.substr(i, 2));
            i++;
        }
        else if (find(singleOperators.begin(), singleOperators.end(), code.substr(i, 1)) != singleOperators.end() && !startString && !comment)
        {
            if (currentLexeme != "")
            {
                lexemes.push_back(currentLexeme);
                currentLexeme = "";
            }
            lexemes.push_back(code.substr(i, 1));
        }
        else if (code.substr(i, 1) != " ")
        {
            currentLexeme += code[i];
        }
        else
        {
            if (currentLexeme != "")
            {
                lexemes.push_back(currentLexeme);
                currentLexeme = "";
            }
            lexemes.push_back(" ");
        }

        i++;

        if (i == (int)code.length())
        {
            if (currentLexeme != "")
            {
                lexemes.push_back(currentLexeme);
            }
            break;
        }
    }

    return lexemes;
}

vector<pair<string, Token>> LexerScanner::getTokens(string code)
/**
Gets all tokens from the lexemes in a line of code

Args:
    (string) code: Line of code to check
Returns:
    vector<pair<string, Token>>
 */

{
    vector<pair<string, Token>> lexicalizedCode;
    vector<string> lexemes = getLexemes(code);

    for (string lexeme : lexemes)
    {
        if (lexeme == " ")
        {
            lexicalizedCode.push_back(make_pair(" ", SPACE));
        }
        else if (find(delimiters.begin(), delimiters.end(), lexeme) != delimiters.end() && lexeme != ",")
        {
            lexicalizedCode.push_back(make_pair(lexeme, DELIMITER));
        }
        else if (lexeme == ",")
        {
            lexicalizedCode.push_back(make_pair(lexeme, PUNCTUATION));
        }
        else if (find(singleOperators.begin(), singleOperators.end(), lexeme) != singleOperators.end() || find(doubleOperators.begin(), doubleOperators.end(), lexeme) != doubleOperators.end())
        {
            lexicalizedCode.push_back(make_pair(lexeme, OPERATOR));
        }
        else if (lexeme[0] == '#')
        {
            lexicalizedCode.push_back(make_pair(lexeme, COMMENT));
        }
        else if (lexeme[0] == '\'' || lexeme[0] == '"' || docString)
        {
            string txt = "";
            int i = 0;
            for (int x = 0; x < (int)lexeme.length(); x++)
            {
                if (find(specialChars.begin(), specialChars.end(), lexeme.substr(i, 2)) != specialChars.end())
                {
                    lexicalizedCode.push_back(make_pair(txt, STRING));
                    lexicalizedCode.push_back(make_pair(lexeme.substr(i, 2), SPECIAL));
                    txt = "";
                    i++;
                }
                else
                {
                    txt += lexeme[i];
                }
                i++;

                if (i == (int)lexeme.length())
                {
                    break;
                }
            }
            if ((int)txt.length() > 0)
            {
                lexicalizedCode.push_back(make_pair(txt, STRING));
            }
        }
        else if (find(keyWords.begin(), keyWords.end(), lexeme) != keyWords.end())
        {
            lexicalizedCode.push_back(make_pair(lexeme, KEYWORD));
        }
        else if (find(functions.begin(), functions.end(), lexeme) != functions.end() && lexeme != ",")
        {
            lexicalizedCode.push_back(make_pair(lexeme, OTHER));
        }
        else if (isNum(lexeme))
        {
            lexicalizedCode.push_back(make_pair(lexeme, NUMBER));
        }
        else
        {
            if (lexeme.find('.') != std::string::npos)
            {
                string txt = "";
                for (int x = 0; x < (int)lexeme.length(); x++)
                {
                    if (lexeme[x] == '.')
                    {
                        if ((int)txt.length() > 0)
                        {
                            lexicalizedCode.push_back(make_pair(txt, TEXT));
                            txt = "";
                        }
                        lexicalizedCode.push_back(make_pair(".", PUNCTUATION));
                    }
                    else
                    {
                        txt += lexeme[x];
                    }
                }
                if ((int)txt.length() > 0)
                {
                    lexicalizedCode.push_back(make_pair(txt, TEXT));
                }
            }
            else
            {
                lexicalizedCode.push_back(make_pair(lexeme, TEXT));
            }
        }
    }

    return lexicalizedCode;
}
