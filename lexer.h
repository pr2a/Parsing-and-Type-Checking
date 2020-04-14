//
//  lexer.h
//  CSE340_Project4
//
//  Created by Priya Ganguly on 4/10/20.
//  Copyright © 2020 idk. All rights reserved.
//

#ifndef lexer_h
#define lexer_h

#include <vector>
#include <string>
#include <stdio.h>

#include "inputbuf.h"

// ------- token types -------------------

typedef enum { END_OF_FILE = 0,
    REAL, INT, BOOLEAN, STRING,
    WHILE,TRUE, FALSE, COMMA, COLON, SEMICOLON,
    LBRACE, RBRACE, LPAREN, RPAREN,
    EQUAL, PLUS, MINUS, MULT, DIV, AND, OR, XOR, NOT,
    GREATER, GTEQ, LESS, LTEQ, NOTEQUAL,
    ID, NUM, REALNUM, STRING_CONSTANT, ERROR
} TokenType;

class Token {
public:
    void Print();

    std::string lexeme;
    TokenType token_type;
    int line_no;
};

class LexicalAnalyzer {
public:
    Token GetToken();
    TokenType UngetToken(Token);
    LexicalAnalyzer();
    int get_line_no();

private:
    std::vector<Token> tokens;
    int line_no;
    Token tmp;
    InputBuffer input;

    bool SkipSpace();
    bool IsKeyword(std::string);
    TokenType FindKeywordIndex(std::string);
    Token ScanIdOrKeyword();
    Token ScanStringCons();
    Token ScanNumber();
};

#endif /* lexer_h */
