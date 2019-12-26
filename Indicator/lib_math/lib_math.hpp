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
#include <vector>
#include <map>
#include <string>

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
    static vector<double> ma(vector<double> data, size_t n);
    
};

#endif /* lib_math_hpp */
