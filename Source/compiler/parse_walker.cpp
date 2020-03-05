//
//  parse_walker.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/26.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "parse_walker.hpp"

bool parse_walker::lookup_function(ast_node::ptr root) {
    for (ast_node::ptr child : root->get_child()) {
        ast_node_type ty = child->get_type();
        if (ty == ast_node_type::fun_express) {
            int param_cnt = tb.param_cnt_in_function(child->get_text());
            if (param_cnt != child->get_child().size()) {
                std::cout << "parse_walker function '" << child->get_text() << "' param count error" << std::endl;
                return false;
            }
        }
        if (!lookup_function(child)) {
            return false;  // jump out
        }
    }
    return true;
}

bool parse_walker::lookup_variale(ast_node::ptr root) {
    for (ast_node::ptr child : root->get_child()) {
        ast_node_type ty = child->get_type();
        if (ty == ast_node_type::identifier && var_map.find(child->get_text()) == var_map.end()) {
            std::cout << "parse_walker cannot find '" << child->get_text() << "'" << std::endl;
            return false;
        }
        if (!lookup_variale(child)) {
            return false;  // jump out
        }
    }
    return true;
}

bool parse_walker::lookup_statement(ast_node::ptr root) {
    for (ast_node::ptr child : root->get_child()) {
        ast_node_type ty = child->get_type();
        if (ty != ast_node_type::assignment && ty != ast_node_type::fun_express && ty != ast_node_type::return_assignment) {
            return false;
        } else if (ty == ast_node_type::assignment || ty == ast_node_type::return_assignment) {
            ast_node::ptr node = child->get_child(0);
            if (node != nullptr && node->get_type() == ast_node_type::identifier && child->get_child().size() == 2) {
                var_map.insert({node->get_text(), true});  // store all variable
                continue;
            }
            return false;
        }
    }
    return true;
}

parse_walker::parse_walker() {
    tb = defined_table();
}

bool parse_walker::walker(ast_node::ptr root) {
    if (!lookup_statement(root)) {
        std::cout << "parse_walker lookup statement error";
        return false;
    }
    if (!lookup_variale(root)) {
        return false;
    }
    if (!lookup_function(root)) {
        return false;
    }
    return true;
}
