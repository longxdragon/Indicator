//
//  token.hpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#ifndef token_hpp
#define token_hpp

#include <stdio.h>
#include <string>

using namespace std;

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
    double_and,     // && AND
    double_or,      // || OR
    single_equal,   // =
    exclamatory_mark,   // !
    no_equal,           // != <>
    
    add,            // +
    reduce,         // -
    multi,          // *
    divide,         // /
    
    and_a,          // AND_A
    or_o,           // OR_O
    or_or,          // OR_OR
    and_an,         // AND_AN
    and_and,        // AND_AND
    
    assignment,     // :=
    notes,          // //
    
    function_name,
    static_key
};

struct token {
    
public:
    dfa_state st = initial;
    string txt;
    string format_st();
    bool empty();
};

#endif /* token_hpp */
