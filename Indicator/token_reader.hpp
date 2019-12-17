//
//  token_reader.hpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#ifndef token_reader_hpp
#define token_reader_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

#include "token.hpp"

class token_reader {
    
    std::vector<token> token_list;
    int pos;
    
public:
    token_reader(const std::vector<token>& tokens);
    token peek();
    token read();
    void unread();
    bool end();
    bool empty();
    int get_pos();
    void set_pos(int p);
    void dump();
};

#endif /* token_reader_hpp */
