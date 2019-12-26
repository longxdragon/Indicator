//
//  lib_math.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/26.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "lib_math.hpp"

double lib_math::string_2_double(string s) {
    return atof(const_cast<const char *>(s.c_str()));
}

int lib_math::string_2_int(string s) {
    return atoi(const_cast<const char *>(s.c_str()));
}

vector<double> lib_math::c(vector<map<string, string>> data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        rt.push_back(string_2_double(m["c"]));
    }
    return rt;
}

vector<double> lib_math::o(vector<map<string, string>> data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        rt.push_back(string_2_double(m["o"]));
    }
    return rt;
}

vector<double> lib_math::l(vector<map<string, string>> data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        rt.push_back(string_2_double(m["l"]));
    }
    return rt;
}

vector<double> lib_math::h(vector<map<string, string>> data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        rt.push_back(string_2_double(m["h"]));
    }
    return rt;
}

vector<double> lib_math::ma(vector<double> data, size_t n) {
    std::vector<double> ma;
    if (n < 1) {
        return ma;
    }
    double t = 0;
    for (size_t i = 0; i < data.size(); i++) {
        t += data[i];
        if (i < n - 1) {
            ma.push_back(INVAILED_VALUE);
        } else {
            if (i - n >= 0) t -= data[i - n];
            double v = t / n;
            ma.push_back(v);
        }
    }
    return ma;
}
