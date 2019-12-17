//
//  common.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "common.hpp"

template <class T>

int length(T& arr) {
    return sizeof(arr) / sizeof(arr[0]);
}

defined_table::defined_table() {
    std::string ft[] = {
        "C", "L", "H", "O",
        "MA", "EMA", "REF", "HHV", "LLV",
        "CROSS", "IF",
        "DRAWTEXT", "DRAWCOLORLINE"
    };
    std::string st[] = {
        "NULL"
    };
    for (int i = 0; i < length(ft); i++) {
        function_table.insert({ft[i], true});
    }
    for (int i = 0; i < length(st); i++) {
        static_table.insert({st[i], true});
    }
}

bool defined_table::is_function(std::string str) {
    if (function_table.find(str) == function_table.end()) {
        return false;
    }
    return true;
}

bool defined_table::is_static(std::string str) {
    if (static_table.find(str) == static_table.end()) {
        return false;
    }
    return true;
}
