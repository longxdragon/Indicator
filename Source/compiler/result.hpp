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

class var_model {
    
public:
    string name;
    vector<double> datas;
    var_model();
};

class result {
    
private:
    map< string, vector<double> > digit_values;
    map< string, vector< map<string, string> > > draw_text_values;
    map< string, vector<string> > property_values;
    vector<var_model> var_values;
    
public:
    result();
    result(map< string, vector<double> > v1, map< string, vector< map<string, string> > > v2, map< string, vector<string> > v3, vector<var_model> v4);
    
    map< string, vector<double> > get_digit_values();
    map< string, vector< map<string, string> > > get_draw_text_values();
    map< string, vector<string> > get_property_values();
    vector<var_model> get_var_values();
};

#endif /* result_hpp */
