//
//  parse_walker.hpp
//  Indicator
//
//  Created by 许龙 on 2019/12/26.
//  Copyright © 2019 许龙. All rights reserved.
//

#ifndef parse_walker_hpp
#define parse_walker_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "ast_node.hpp"
#include "common.hpp"

/** Just need 1. var check; 2. function param check;
 Do not need check the scope of action and function visable. */
class parse_walker {
    
private:
    std::map<std::string, bool> var_map;
    defined_table tb;
    
    bool lookup_function(ast_node::ptr root);
    bool lookup_variale(ast_node::ptr root);
    bool lookup_statement(ast_node::ptr root);
    
public:
    parse_walker();
    bool walker(ast_node::ptr root);
};

#endif /* parse_walker_hpp */
