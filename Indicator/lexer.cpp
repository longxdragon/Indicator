//
//  lexer.cpp
//  Indicator
//
//  Created by 许龙 on 2019/11/29.
//  Copyright © 2019 许龙. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "common.cpp"

enum dfa_state {
    initial,
    identifier,
    digit,
    string_literal,
    string_sub,
    
    gt,             // >
    ge,             // >=
    lt,             // <
    le,             // <=
    colon,          // :
    comma,          // ,
    semicolon,      // ;
    left_paren,     // (
    right_paren,    // )
    single_quotes,  // '
    single_and,     // &
    single_or,      // |
    double_and,     // &&
    double_or,      // ||
    
    add,            // +
    reduce,         // -
    multi,          // *
    divide,         // /
    
    assignment,
    return_assign,
    
    function_name,
    static_key
};

struct token {
    dfa_state st = initial;
    string txt;
    
    string format_st() {
        switch (this->st) {
            case initial: return "Initial"; break;
            case identifier: return "Identifier"; break;
            case digit: return "Digit"; break;
            case string_literal: return "StringLiteral"; break;
            case string_sub: return "StringSub"; break;
                
            case gt: return "GT"; break;
            case ge: return "GE"; break;
            case lt: return "LT"; break;
            case le: return "LE"; break;
            case colon: return "Colon"; break;
            case comma: return "Comma"; break;
            case semicolon: return "Semicolon"; break;
            case left_paren: return "LeftParen"; break;
            case right_paren: return "RightParen"; break;
            case single_quotes: return "SingleQuotes"; break;
            case single_and: return "SingleAnd"; break;
            case single_or: return "SingleOr"; break;
            case double_and: return "DoubleAnd"; break;
            case double_or: return "DoubleOr"; break;
                
            case add: return "Add"; break;
            case reduce: return "Reduce"; break;
            case multi: return "Multi"; break;
            case divide: return "Divide"; break;
                
            case assignment: return "Assignment"; break;
            case return_assign: return "ReturnAssign"; break;
                
            case function_name: return "Function"; break;
            case static_key: return "Static"; break;
            default: break;
        }
    }
};

static string to_string(char ch) {
    return string(1, ch);
}

static void trim(string &str) {
    size_t idx = 0;
    if (!str.empty()) {
        while ((idx = str.find(" ")) != string::npos) {
            str.erase(idx, 1);
        }
    }
}

class lexer {
    
private:
    string token_text = "";
    token t;
    vector<token> list;
    defined_table tb;
    
    bool is_alpha(char ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

    bool is_digit(char ch) {
        return (ch >= '0' && ch <= '9') || ch == '.';
    }
    
    bool is_chinese(char ch) {
        return ch < 0 || ch > 127;
    }
    
    bool is_blank(char ch) {
        return ch == ' ' || ch == '\t' || ch == '\n';
    }
    
    bool is_variable_start(char ch) {
        return is_alpha(ch) || ch == '_' || is_chinese(ch);
    }
    
    bool is_variable(char ch) {
        return is_alpha(ch) || ch == '_' || is_digit(ch) || is_chinese(ch);
    }
    
    dfa_state init_token(char ch) {
        if (token_text.size() > 0) {
            if (t.st == identifier) {
                if (tb.is_function(token_text)) {
                    t.st = function_name;
                } else if (tb.is_static(token_text)) {
                    t.st = static_key;
                }
            }
            t.txt = token_text;
            list.push_back(t);
            
            token_text = "";
            t = token();
        }
        
        dfa_state st = initial;
        if (is_variable_start(ch)) {
            st = identifier;
        } else if (is_digit(ch)) {
            st = digit;
        } else if (ch == '>') {
            st = gt;
        } else if (ch == '<') {
            st = lt;
        } else if (ch == ':') {
            st = colon;
        } else if (ch == ',') {
            st = comma;
        } else if (ch == ';') {
            st = semicolon;
        } else if (ch == '=') {
            st = assignment;
        } else if (ch == '\'') {
            st = single_quotes;
        } else if (ch == '(') {
            st = left_paren;
        } else if (ch == ')') {
            st = right_paren;
        } else if (ch == '&') {
            st = single_and;
        } else if (ch == '|') {
            st = single_or;
        } else if (ch == '+') {
            st = add;
        } else if (ch == '-') {
            st = reduce;
        } else if (ch == '*') {
            st = multi;
        } else if (ch == '/') {
            st = divide;
        }
        if (st != initial) {
            token_text += to_string(ch);
        }
        t.st = st;
        return st;
    }
    
public:
    lexer() {
        tb = defined_table();
    }
    
    vector<token> tokenize(string code) {
        trim(code);
        
        list.clear();
        token_text = "";
        t = token();
        dfa_state st = initial;
        
        for (int i = 0; i < code.size(); i++) {
            char ch = code[i];
            switch (st) {
                case initial: {
                    st = init_token(ch);
                } break;
                case identifier: {
                    if (is_variable(ch)) {
                        token_text += to_string(ch);
                    } else {
                        st = init_token(ch);
                    }
                } break;
                case digit: {
                    if (is_digit(ch)) {
                        token_text += to_string(ch);
                    } else {
                        st = init_token(ch);
                    }
                } break;
                case ge:
                case le:
                case left_paren:
                case right_paren:
                case comma:
                case semicolon:
                case string_literal:
                case double_and:
                case double_or:
                case add:
                case multi:
                case divide:
                case return_assign:
                case assignment: {
                    st = init_token(ch);
                } break;
                case reduce: {
                    if (is_digit(ch)) {
                        token_text += to_string(ch);
                        st = digit;
                        t.st = st;
                    } else {
                        st = init_token(ch);
                    }
                } break;
                case colon: {
                    if (ch == '=') {
                        token_text += to_string(ch);
                        st = return_assign;
                        t.st = st;
                    } else {
                        st = init_token(ch);
                    }
                } break;
                case gt: {
                    if (ch == '=') {
                        token_text += to_string(ch);
                        st = ge;
                        t.st = st;
                    } else {
                        st = init_token(ch);
                    }
                } break;
                case lt: {
                    if (ch == '=') {
                        token_text += to_string(ch);
                        st = le;
                        t.st = st;
                    } else {
                        st = init_token(ch);
                    }
                } break;
                case single_quotes:
                case string_sub: {
                    if (is_variable(ch)) {
                        token_text += to_string(ch);
                        st = string_sub;
                        t.st = st;
                    } else if (ch == '\'') {
                        token_text += to_string(ch);
                        st = string_literal;
                        t.st = st;
                    } else {
                        st = init_token(ch);
                    }
                } break;
                case single_and: {
                    if (ch == '&') {
                        token_text += to_string(ch);
                        st = double_and;
                        t.st = st;
                    } else {
                        st = init_token(ch);
                    }
                } break;
                case single_or: {
                    if (ch == '|') {
                        token_text += to_string(ch);
                        st = double_or;
                        t.st = st;
                    } else {
                        st = init_token(ch);
                    }
                } break;
                default:
                    break;
            }
        }
        if (token_text.size() > 0) {
            st = init_token(' ');
        }
        return list;
    }
    
    void dump(vector<token> list) {
        for (vector<token>::iterator iter = list.begin(); iter != list.end(); iter++) {
            std::cout << iter->format_st() << " : " << iter->txt << std::endl;
        }
    }
};
