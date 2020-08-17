//
//  lib_draw.hpp
//  Indicator
//
//  Created by 许龙 on 2020/1/19.
//  Copyright © 2020 许龙. All rights reserved.
//

#ifndef lib_draw_hpp
#define lib_draw_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <initializer_list>

using namespace std;

class lib_draw {
    
public:
    static vector< map<string, string> > draw_text(vector<double> data, vector<double> v1, vector<string> v2);
    static vector< map<string, string> > part_line2(vector<double> data, vector< vector<double> > v1, vector< vector<string> > v2);
};

#endif /* lib_draw_hpp */
