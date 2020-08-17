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
        "NULL", "NODRAW",
    };
    for (int i = 0; i < length(st); i++) {
        static_table.insert({st[i], true});
    }
    
    std::string colors[] = {
        "COLORCYAN", "COLORRED", "COLORGREEN", "COLORBLACK"
    };
    for (int i = 0; i < length(colors); i++) {
        color_table.insert({colors[i], true});
    }
    
    std::string lines[] = {
        "LINETHICK3"
    };
    for (int i = 0; i < length(lines); i++) {
        line_table.insert({lines[i], true});
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

bool defined_table::is_color(std::string str) {
    if (color_table.find(str) == color_table.end()) {
        return false;
    }
    return true;
}

bool defined_table::is_line(std::string str) {
    if (line_table.find(str) == line_table.end()) {
        return false;
    }
    return true;
}
