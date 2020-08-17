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

vector< map<string, string> > lib_draw::part_line2(vector<double> data, vector< vector<double> > v1, vector< vector<string> > v2) {
    vector< map<string, string> > rt;
    vector<string> clrs(data.size());
    if (v1.size() == v2.size()) {
        for (size_t i = 0; i < v1.size(); i++) {
            vector<double> ss1 = v1[i];
            vector<string> ss2 = v2[i];
            for (size_t j = 0; j < ss1.size() && j < ss2.size(); j++) {
                if (ss1[j] > 0 && j < clrs.size()) {
                    clrs[j] = ss2[j];
                }
            }
        }
    }
    for (size_t i = 0; i < data.size() && i < clrs.size(); i++) {
        map<string, string> item;
        item["val"] = to_string(data[i]);
        item["color"] = clrs[i];
        rt.push_back(item);
    }
    return rt;
}
