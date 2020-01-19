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
        "C", "L", "H", "O", "CLOSE", "LOW", "HIGH", "OPEN", "ISLASTBAR",
        "MA", "EMA", "SMA", "REF", "REFX", "HHV", "LLV", "AVEDEV",
        "CROSS", "IF", "BARSLAST", "BACKSET", "VALUEWHEN",
        "DRAWTEXT", "DRAWCOLORLINE"
    };
    int pr[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 2, 3, 2, 2, 2, 2, 2,
        2, 3, 1, 2, 2,
        3, 4
    };
    std::string st[] = {
        "NULL", "NODRAW"
    };
    for (int i = 0; i < length(ft) && i < length(pr); i++) {
        function_table.insert({ft[i], pr[i]});
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

int defined_table::param_cnt_in_function(std::string str) {
    auto iter = function_table.find(str);
    if (iter == function_table.end()) {
        return 0;
    }
    return iter->second;
}
