//
//  parser.c
//  CSE340_Project4
//
//  Created by Priya Ganguly on 4/10/20.
//  Copyright © 2020 idk. All rights reserved.
//

#include "parser.h"

#include <iostream>
#include <cstdlib>

using namespace std;

void Parser::syntax_error(){
    cout << "Syntax Error &!#@";
    exit(1);
}

Token Parser::expect(TokenType expected_type){
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

Token Parser::peek(){
    Token t = lexer.GetToken();
    lexer.UngetToken(t);
    return t;
}

void Parser::parse_program(){
    parse_scope();
}

void Parser::parse_scope(){
    expect(LBRACE);
    parse_scope_list();
    expect(RBRACE);
}

void Parser::parse_scope_list(){
    Token t = lexer.GetToken();
    if(t.token_type == LBRACE){
        lexer.UngetToken(t);
        parse_scope();
        t = peek();
        if(t.token_type == LBRACE || t.token_type == ID || t.token_type == WHILE){
            parse_scope_list();
        }
    }
    else if(t.token_type == ID){
        Token t2 = lexer.GetToken();
        if(t2.token_type == COMMA || t2.token_type == COLON){
            lexer.UngetToken(t2);
            lexer.UngetToken(t);
            parse_var_decl();
            t = peek();
            if(t.token_type == LBRACE || t.token_type == ID || t.token_type == WHILE){
                parse_scope_list();
            }
        }
        else if(t2.token_type == EQUAL){
            lexer.UngetToken(t2);
            lexer.UngetToken(t);
            parse_stmt();
            t = peek();
            if(t.token_type == LBRACE || t.token_type == ID || t.token_type == WHILE){
                parse_scope_list();
            }
        }
        else
            syntax_error();
    }
    else if(t.token_type == WHILE){
        lexer.UngetToken(t);
        parse_stmt();
        Token t = peek();
        if(t.token_type == LBRACE || t.token_type == ID || t.token_type == WHILE){
            parse_scope_list();
        }
    }
    else{
        syntax_error();
    }
}

void Parser::parse_var_decl(){
    parse_id_list();
    expect(COLON);
    parse_type_name();
    expect(SEMICOLON);
}

void Parser::parse_id_list(){
    expect(ID);
    Token t = peek();
    if(t.token_type == COMMA){
        expect(COMMA);
        parse_id_list();
    }
}

void Parser::parse_type_name(){
    Token t = peek();
    if(t.token_type == REAL)
        expect(REAL);
    else if(t.token_type == INT)
        expect(INT);
    else if(t.token_type == BOOLEAN)
        expect(BOOLEAN);
    else if(t.token_type == STRING)
        expect(STRING);
    else
        syntax_error();
}

void Parser::parse_stmt_list(){
    parse_stmt();
    Token t = peek();
    if(t.token_type == ID || t.token_type == WHILE){
        parse_stmt_list();
    }
}

void Parser::parse_stmt(){
    Token t = peek();
    if(t.token_type == ID){
        parse_assign_stmt();
    }
    else if(t.token_type == WHILE){
        parse_while_stmt();
    }
    else
        syntax_error();
}

void Parser::parse_assign_stmt(){
    expect(ID);
    expect(EQUAL);
    parse_expr();
    expect(SEMICOLON);
}

void Parser::parse_while_stmt(){
    expect(WHILE);
    expect(LPAREN);
    parse_condition();
    expect(RPAREN);
    Token t = peek();
    if(t.token_type == LBRACE){
        expect(LBRACE);
        parse_stmt_list();
        expect(RBRACE);
    }
    else if(t.token_type == ID || t.token_type == WHILE){
        parse_stmt();
    }
    else
        syntax_error();
}

void Parser::parse_expr(){
    Token t = peek();
    if(t.token_type == ID || t.token_type == NUM || t.token_type == REALNUM || t.token_type == STRING_CONSTANT || t.token_type == TRUE || t.token_type == FALSE){
        parse_primary();
    }
    else if(t.token_type == PLUS || t.token_type == MINUS || t.token_type == MULT || t.token_type == DIV){
        parse_arithmetic_expr();
    }
    else if(t.token_type == AND || t.token_type == OR || t.token_type == XOR || t.token_type == GREATER || t.token_type == GTEQ || t.token_type == LESS || t.token_type == NOTEQUAL || t.token_type == LTEQ || t.token_type == NOT){
        parse_boolean_expr();
    }
    else
        syntax_error();
}

void Parser::parse_arithmetic_expr(){
    Token t = peek();
    if(t.token_type == PLUS || t.token_type == MINUS || t.token_type == MULT || t.token_type == DIV){
        parse_arithmetic_operator();
        parse_arithmetic_expr();
        parse_arithmetic_expr();
    }
    else if(t.token_type == ID || t.token_type == NUM || t.token_type == REALNUM || t.token_type == STRING_CONSTANT){
        parse_arithmetic_primary();
    }
}

void Parser::parse_boolean_expr(){
    Token t = peek();
    //binary_boolean_op
    if(t.token_type == AND || t.token_type == OR || t.token_type == XOR){
        parse_binary_boolean_operator();
        parse_boolean_expr();
        parse_boolean_expr();
    }
    //relational_operator
    else if(t.token_type == GREATER || t.token_type == GTEQ || t.token_type == LESS || t.token_type == NOTEQUAL || t.token_type == LTEQ){
        parse_relational_operator();
        parse_expr();
        parse_expr();
    }
    //NOT
    else if(t.token_type == NOT){
        expect(NOT);
        parse_boolean_expr();
    }
    //boolean_primary
    else if(t.token_type == ID || t.token_type == TRUE || t.token_type == FALSE){
        parse_boolean_primary();
    }
    else
        syntax_error();
}

void Parser::parse_arithmetic_operator(){
    Token t = peek();
    if(t.token_type == PLUS)
        expect(PLUS);
    else if(t.token_type == MINUS)
        expect(MINUS);
    else if(t.token_type == MULT)
        expect(MULT);
    else if(t.token_type == DIV)
        expect(DIV);
    else
        syntax_error();
}

void Parser::parse_binary_boolean_operator(){
    Token t = peek();
    if(t.token_type == AND)
        expect(AND);
    else if(t.token_type == OR)
        expect(OR);
    else if(t.token_type == XOR)
        expect(XOR);
    else
        syntax_error();
}

void Parser::parse_relational_operator(){
    Token t = peek();
    if(t.token_type == GREATER)
        expect(GREATER);
    else if(t.token_type == GTEQ)
        expect(GTEQ);
    else if(t.token_type == LESS)
        expect(LESS);
    else if(t.token_type == NOTEQUAL)
        expect(NOTEQUAL);
    else if(t.token_type == LTEQ)
        expect(LTEQ);
    else
        syntax_error();
}

void Parser::parse_primary(){
    Token t = peek();
    if(t.token_type == ID)
        expect(ID);
    else if(t.token_type == NUM)
        expect(NUM);
    else if(t.token_type == REALNUM)
        expect(REALNUM);
    else if(t.token_type == STRING_CONSTANT)
        expect(STRING_CONSTANT);
    else if(t.token_type == TRUE || t.token_type == FALSE)
        parse_bool_const();
    else
        syntax_error();
}

void Parser::parse_arithmetic_primary(){
    Token t = peek();
    if(t.token_type == ID)
        expect(ID);
    else if(t.token_type == NUM)
        expect(NUM);
    else if(t.token_type == REALNUM)
        expect(REALNUM);
    else if(t.token_type == STRING_CONSTANT)
        expect(STRING_CONSTANT);
    else
        syntax_error();
}

void Parser::parse_boolean_primary(){
    Token t = peek();
    if(t.token_type == ID)
        expect(ID);
    else if(t.token_type == TRUE || t.token_type == FALSE)
        parse_bool_const();
    else
        syntax_error();
}

void Parser::parse_bool_const(){
    Token t = peek();
    if(t.token_type == TRUE)
        expect(TRUE);
    else if(t.token_type == FALSE)
        expect(FALSE);
    else
        syntax_error();
}

void Parser::parse_condition(){
    parse_boolean_expr();
}
