//
//  token_reader.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "token_reader.hpp"

token_reader::token_reader(const std::vector<token>& tokens) {
    token_list = tokens;
    pos = 0;
}

token token_reader::peek() {
    token t;
    if (!empty() && pos < token_list.size()) {
        t = token_list[pos];
    }
    return t;
}

token token_reader::read() {
    token t;
    if (pos < token_list.size()) {
        t = token_list[pos++];
    }
    return t;
}

void token_reader::unread() {
    pos--;
}

bool token_reader::end() {
    return (pos >= token_list.size() - 1) ? true : false;
}

bool token_reader::empty() {
    return token_list.empty();
}

int token_reader::get_pos() {
    return pos;
}

void token_reader::set_pos(int p) {
    pos = p;
}

void token_reader::dump() {
    int i = 0;
    for (vector<token>::iterator iter = token_list.begin(); iter != token_list.end(); iter++) {
        std::cout << "[" << i << "] " << iter->format_st() << " : " << iter->txt << std::endl;
        i ++;
    }
    std::cout << "" << std::endl;
}
