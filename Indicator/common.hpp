//
//  common.hpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#ifndef common_hpp
#define common_hpp

#include <stdio.h>
#include <string>
#include <map>

class defined_table {
    
private:
    std::map<std::string, bool> function_table;
    std::map<std::string, bool> static_table;
    
public:
    defined_table();
    bool is_function(std::string str);
    bool is_static(std::string str);
};

#endif /* common_hpp */
