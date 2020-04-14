//
//  parser.h
//  CSE340_Project4
//
//  Created by Priya Ganguly on 4/10/20.
//  Copyright © 2020 idk. All rights reserved.
//

#ifndef parser_h
#define parser_h

#include <stdio.h>
#include <stdio.h>
#include "lexer.h"

using namespace std;

class Parser{
private:
    
public:
    LexicalAnalyzer lexer;
    
    void syntax_error();
    Token expect(TokenType expected_type);
    Token peek();
    
    void parse_program();
    void parse_scope();
    void parse_scope_list();
    void parse_var_decl();
    void parse_id_list();
    void parse_type_name();
    void parse_stmt_list();
    void parse_stmt();
    void parse_assign_stmt();
    void parse_while_stmt();
    void parse_expr();
    void parse_arithmetic_expr();
    void parse_boolean_expr();
    void parse_arithmetic_operator();
    void parse_binary_boolean_operator();
    void parse_relational_operator();
    void parse_primary();
    void parse_arithmetic_primary();
    void parse_boolean_primary();
    void parse_bool_const();
    void parse_condition();
};




#endif /* parser_h */
