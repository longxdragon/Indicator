//
//  compiler.hpp
//  Indicator
//
//  Created by 许龙 on 2019/12/27.
//  Copyright © 2019 许龙. All rights reserved.
//

#ifndef compiler_hpp
#define compiler_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

#include "result.hpp"

using namespace std;

class compiler {
    
    vector< map<string, string> > data;
    
public:
    compiler(vector<map <string, string> > dt);
    result compile(string s);
    
    bool debug;
};

#endif /* compiler_hpp */
