//
//  result.cpp
//  Indicator
//
//  Created by 许龙 on 2020/1/20.
//  Copyright © 2020 许龙. All rights reserved.
//

#include "result.hpp"

var_model::var_model() {
    
}

result::result() {
    
}

result::result(map< string, vector<double> > v1, map< string, vector< map<string, string> > > v2, map< string, vector<string> > v3, vector<var_model> v4) {
    digit_values = v1;
    draw_text_values = v2;
    property_values = v3;
    var_values = v4;
}

map< string, vector<double> > result::get_digit_values() {
    return digit_values;
}

map< string, vector< map<string, string> > > result::get_draw_text_values() {
    return draw_text_values;
}

map< string, vector<string> > result::get_property_values() {
    return property_values;
}

vector<var_model> result::get_var_values() {
    return var_values;
}
