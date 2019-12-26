//
//  evaluator.hpp
//  Indicator
//
//  Created by 许龙 on 2019/12/26.
//  Copyright © 2019 许龙. All rights reserved.
//

#ifndef evaluator_hpp
#define evaluator_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

#include "ast_node.hpp"
#include "common.hpp"

class evaluator {
    
private:
    defined_table tb;
    std::vector<std::map<std::string, std::string>> data;
    std::map< std::string, std::vector<double> > variables;
    
    std::vector<double> _evaluate(ast_node::ptr root);
    std::vector<double> _call_function(std::string name, ast_node::ptr root);
    
public:
    evaluator(std::vector<std::map<std::string, std::string>> dt);
    std::map< std::string, std::vector<double> > evaluate(ast_node::ptr root);
};

#endif /* evaluator_hpp */
