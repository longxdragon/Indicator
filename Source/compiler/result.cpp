//
//  result.cpp
//  Indicator
//
//  Created by 许龙 on 2020/1/20.
//  Copyright © 2020 许龙. All rights reserved.
//

#include "result.hpp"

result::result() {
    
}

result::result(map< string, vector<double> > v1, map< string, vector< map<string, string> > > v2, vector<string> v3) {
    digit_values = v1;
    draw_text_values = v2;
    property_values = v3;
}

map< string, vector<double> > result::get_digit_values() {
    return digit_values;
}

map< string, vector< map<string, string> > > result::get_draw_text_values() {
    return draw_text_values;
}

vector<string> result::get_property_values() {
    return property_values;
}
