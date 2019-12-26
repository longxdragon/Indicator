//
//  evaluator.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/26.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "evaluator.hpp"
#include "lib_math.hpp"

std::vector<double> evaluator::_call_function(std::string name, ast_node::ptr root) {
    std::vector<double> rt;
    
    if (name.compare("C") == 0) {
        rt = lib_math::c(data);
    } else if (name.compare("O") == 0) {
        rt = lib_math::o(data);
    } else if (name.compare("H") == 0) {
        rt = lib_math::h(data);
    } else if (name.compare("L") == 0) {
        rt = lib_math::l(data);
    } else if (name.compare("MA") == 0) {
        ast_node::ptr c1 = root->get_child(0);
        ast_node::ptr c2 = root->get_child(1);
        std::vector<double> v1 = _evaluate(c1);
        std::vector<double> v2 = _evaluate(c2);
        if (v2.size()) {
            rt = lib_math::ma(v1, (size_t)v2[0]);
        }
    }
    return rt;
}

std::vector<double> evaluator::_evaluate(ast_node::ptr root) {
    std::vector<double> rt;
    ast_node_type ty = root->get_type();
    
    if (ty == ast_node_type::digit_literal) {
        rt.push_back(lib_math::string_2_double(root->get_text()));
    } else if (ty == ast_node_type::fun_express) {
        rt = _call_function(root->get_text(), root);
    }
    return rt;
}

std::map< std::string, std::vector<double> > evaluator::evaluate(ast_node::ptr root) {
    std::map< std::string, std::vector<double> > rt;
    for (ast_node::ptr node : root->get_child()) {
        if (node->get_type() == ast_node_type::assignment) {
            ast_node::ptr c1 = node->get_child(0);
            ast_node::ptr c2 = node->get_child(1);
            std::vector<double> val = _evaluate(c2);
            if (val.size()) {
                variables.insert({c1->get_text(), val});
                rt.insert({c1->get_text(), val});
            }
        }
    }
    return rt;
}

evaluator::evaluator(std::vector<std::map<std::string, std::string>> dt) {
    tb = defined_table();
    data = dt;
}
