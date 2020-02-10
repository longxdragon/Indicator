//
//  lib_math.hpp
//  Indicator
//
//  Created by 许龙 on 2019/12/26.
//  Copyright © 2019 许龙. All rights reserved.
//

#ifndef lib_math_hpp
#define lib_math_hpp

#include <stdio.h>
#include <float.h>
#include <vector>
#include <map>
#include <string>
#include <deque>

#define INVAILED_VALUE -100000

using namespace std;

class lib_math {
    
public:
    static double string_2_double(string s);
    static int string_2_int(string s);
    
    static vector<double> c(vector<map<string, string>> data);
    static vector<double> o(vector<map<string, string>> data);
    static vector<double> l(vector<map<string, string>> data);
    static vector<double> h(vector<map<string, string>> data);
    static vector<double> is_lastbar(vector<map<string, string>> data);
    
    static vector<double> ma(vector<double> data, size_t n);
    static vector<double> ma(vector<double> data, vector<double> n);
    static vector<double> ema(vector<double> data, size_t n);
    static vector<double> sma(vector<double> data, size_t n, size_t m);
    
    static vector<double> ref(vector<double> data, vector<double> n);
    static vector<double> refx(vector<double> data, vector<double> n);
    static vector<double> hhv(vector<double> data, size_t n);
    static vector<double> hhv(vector<double> data, vector<double> n);
    static vector<double> llv(vector<double> data, size_t n);
    static vector<double> llv(vector<double> data, vector<double> n);
    static vector<double> eif(vector<double> data, vector<double> v1, vector<double> v2);
    static vector<double> cross(vector<double> v1, vector<double> v2);
    
    static vector<double> barslast(vector<double> data);
    static vector<double> backset(vector<double> data, vector<double> n);
    static vector<double> value_when(vector<double> data, vector<double> val);
};

#endif /* lib_math_hpp */
