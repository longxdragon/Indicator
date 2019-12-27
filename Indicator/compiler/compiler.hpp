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

class compiler {
    std::vector<std::map<std::string, std::string>> data;
    
public:
    compiler(std::vector<std::map<std::string, std::string>> dt);
    std::map< std::string, std::vector<double> > compile(std::string s);
};

#endif /* compiler_hpp */
