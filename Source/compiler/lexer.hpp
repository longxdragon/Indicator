//
//  lexer.hpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#ifndef lexer_hpp
#define lexer_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <regex>

#include "token_reader.hpp"
#include "common.hpp"


using namespace std;

class lexer {

private:
    string token_text;
    token t;
    vector<token> list;
    defined_table tb;
    
    dfa_state init_token(char ch);
    
public:
    lexer();
    token_reader tokenize(string code);
};

#endif /* lexer_hpp */
