//
//  lib_draw.cpp
//  Indicator
//
//  Created by 许龙 on 2020/1/19.
//  Copyright © 2020 许龙. All rights reserved.
//

#include "lib_draw.hpp"

vector< map<string, string> > lib_draw::draw_text(vector<double> data, vector<double> v1, vector<string> v2) {
    vector< map<string, string> > rt;
    for (size_t i = 0; i < data.size() && i < v1.size() && i < v2.size(); i++) {
        map<string, string> item;
        item["pt"] = to_string(v1[i]);
        item["tx"] = (data[i] != 0) ? v2[i] : "";
        rt.push_back(item);
    }
    return rt;
}
