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
        "PARTLINE2",
        "C", "L", "H", "O", "CLOSE", "LOW", "HIGH", "OPEN", "ISLASTBAR",
        "BARSLAST", "ABS",
        "MA", "EMA", "SMA", "REF", "REFX", "HHV", "LLV", "AVEDEV", "MAX", "MIN", "STD",
        "CROSS", "IF", "BACKSET", "VALUEWHEN",
        "DRAWTEXT", "DRAWCOLORLINE"
    };
    int pr[] = {
        -1,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1,
        2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 3, 2, 2,
        3, 4
    };
    for (int i = 0; i < length(ft) && i < length(pr); i++) {
        function_table.insert({ft[i], pr[i]});
    }
    
    std::string st[] = {
        "NULL", "DRAWNULL"
    };
    for (int i = 0; i < length(st); i++) {
        static_table.insert({st[i], true});
    }
    
    std::string propertys[] = {
        "COLORCYAN", "COLORRED", "COLORGREEN", "COLORBLACK",
        "LINETHICK3",
        "NODRAW"
    };
    for (int i = 0; i < length(propertys); i++) {
        property_table.insert({propertys[i], true});
    }
    
    std::string dr[] = {
        "DRAWTEXT", "DRAWCOLORLINE",
        "PARTLINE2", "STICKLINE",
    };
    for (int i = 0; i < length(dr); i++) {
        draw_table.insert({dr[i], true});
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

bool defined_table::is_draw(std::string str) {
    if (draw_table.find(str) == draw_table.end()) {
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

bool defined_table::is_property(std::string str) {
    if (property_table.find(str) == property_table.end()) {
        return false;
    }
    return true;
}
