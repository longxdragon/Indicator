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
#include <cmath>

#define INVAILED_VALUE -100000

using namespace std;

class lib_math {
    
public:
    static double string_2_double(string s);
    static int string_2_int(string s);
    
    static vector<double> dd_c(vector< map<string, string> > data);
    static vector<double> dd_o(vector< map<string, string> > data);
    static vector<double> dd_l(vector< map<string, string> > data);
    static vector<double> dd_h(vector< map<string, string> > data);
    static vector<double> dd_is_lastbar(vector< map<string, string> > data);
    
    static vector<double> dd_ma(vector<double> data, size_t n);
    static vector<double> dd_ma(vector<double> data, vector<double> n);
    static vector<double> dd_ema(vector<double> data, size_t n);
    static vector<double> dd_sma(vector<double> data, size_t n, size_t m);
    
    static vector<double> dd_abs(vector<double> data);
    static vector<double> dd_max(vector<double> v1, vector<double> v2);
    static vector<double> dd_min(vector<double> v1, vector<double> v2);
    static vector<double> dd_std(vector<double> v1, size_t n);
    
    static vector<double> dd_ref(vector<double> data, vector<double> n);
    static vector<double> dd_refx(vector<double> data, vector<double> n);
    static vector<double> dd_hhv(vector<double> data, size_t n);
    static vector<double> dd_hhv(vector<double> data, vector<double> n);
    static vector<double> dd_llv(vector<double> data, size_t n);
    static vector<double> dd_llv(vector<double> data, vector<double> n);
    static vector<double> dd_eif(vector<double> data, vector<double> v1, vector<double> v2);
    static vector<double> dd_cross(vector<double> v1, vector<double> v2);
    
    static vector<double> dd_barslast(vector<double> data);
    static vector<double> dd_backset(vector<double> data, vector<double> n);
    static vector<double> dd_value_when(vector<double> data, vector<double> val);
};

#endif /* lib_math_hpp */
