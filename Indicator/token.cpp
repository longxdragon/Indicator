//
//  token.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "token.hpp"

string token::format_st() {
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
        case single_equal: return "SingleEqual"; break;
        case exclamatory_mark: return "ExclamatoryMark"; break;
        case no_equal: return "NoEqual"; break;
            
        case add: return "Add"; break;
        case reduce: return "Reduce"; break;
        case multi: return "Multi"; break;
        case divide: return "Divide"; break;
            
        case assignment: return "Assignment"; break;
            
        case function_name: return "Function"; break;
        case static_key: return "Static"; break;
        default: return "Disable..."; break;
    };
}

bool token::empty() {
    return st == initial;
}
