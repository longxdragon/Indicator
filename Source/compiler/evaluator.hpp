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
#include <algorithm>

#include "ast_node.hpp"
#include "common.hpp"
#include "result.hpp"

using namespace std;

class evaluator {
    
private:
    defined_table tb;
    std::vector< std::map<std::string, std::string> > data;
    std::map< std::string, std::vector<double> > variables;
    
    std::vector<double> _call_function(std::string name, ast_node::ptr root);
    vector< map<string, string> > _draw_function(std::string name, ast_node::ptr root);
    
    std::vector<double> _evaluate(ast_node::ptr root);
    std::vector<double> _add_evalute(ast_node::ptr root);
    std::vector<double> _mul_evalute(ast_node::ptr root);
    std::vector<double> _equal_evalute(ast_node::ptr root);
    std::vector<double> _and_evalute(ast_node::ptr root);
    std::vector<double> _or_evalute(ast_node::ptr root);
    std::vector<double> _rel_evalute(ast_node::ptr root);
    
    std::vector<std::string> _string_evalute(ast_node::ptr root);
    
public:
    evaluator(std::vector< std::map<std::string, std::string> > dt);
    result evaluate(ast_node::ptr root);
};

#endif /* evaluator_hpp */
