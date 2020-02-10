//
//  result.hpp
//  Indicator
//
//  Created by 许龙 on 2020/1/20.
//  Copyright © 2020 许龙. All rights reserved.
//

#ifndef result_hpp
#define result_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

class result {
    
private:
    map< string, vector<double> > digit_values;
    map< string, vector< map<string, string> > > draw_text_values;
    
public:
    result();
    result(map< string, vector<double> > v1, map< string, vector< map<string, string> > > v2);
    
    map< string, vector<double> > get_digit_values();
    map< string, vector< map<string, string> > > get_draw_text_values();
};

#endif /* result_hpp */
