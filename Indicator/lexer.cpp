//
//  lexer.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "lexer.hpp"

string to_string(char ch) {
    return string(1, ch);
}

void trim(string &str) {
    size_t idx = 0;
    if (!str.empty()) {
        while ((idx = str.find(" ")) != string::npos) {
            str.erase(idx, 1);
        }
    }
}

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

dfa_state lexer::init_token(char ch) {
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

lexer::lexer() {
    tb = defined_table();
}

token_reader lexer::tokenize(string code) {
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
    return token_reader(list);
}
