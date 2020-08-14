//
//  ast_node.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "ast_node.hpp"

ast_node::ast_node(const ast_node_type &type, const std::string& text) {
    m_type = type;
    m_text = text;
}

ast_node::ptr ast_node::create(const ast_node_type &type, const std::string &text) {
    return std::make_shared<ast_node>(type, text);
}

void ast_node::add_child(ptr node) {
    if (node != nullptr) {
        m_child.push_back(node);
    }
}

ast_node_type ast_node::get_type() {
    return m_type;
};

std::string ast_node::get_text() {
    return m_text;
};

std::list<ast_node::ptr> ast_node::get_child() {
    return m_child;
};

ast_node::ptr ast_node::get_child(int idx) {
    int i = 0;
    for (std::list<ast_node::ptr>::iterator iter = m_child.begin(); iter != m_child.end(); iter++, i++) {
        if (i == idx) {
            return *iter;
        }
    }
    return nullptr;
}

std::string format_st(ast_node_type type) {
    switch (type) {
        case ast_node_type::root: return "Root"; break;
        case ast_node_type::identifier: return "Identifier"; break;
        case ast_node_type::digit_literal: return "Digit"; break;
        case ast_node_type::string_literal: return "String"; break;
        case ast_node_type::static_literal: return "Static"; break;
        case ast_node_type::assignment: return "Assignment"; break;
        case ast_node_type::return_assignment: return "ReturnAssign"; break;
        case ast_node_type::or_express: return "Or"; break;
        case ast_node_type::and_express: return "And"; break;
        case ast_node_type::equal_express: return "Equal"; break;
        case ast_node_type::rel_express: return "Rel"; break;
        case ast_node_type::add_express: return "Add"; break;
        case ast_node_type::mul_express: return "Mul"; break;
        case ast_node_type::fun_express: return "Fun"; break;
        default: return ""; break;
    }
}

void ast_node::print(int level, int idx) {
    if (!level) {
        std::cout << std::endl;
    }
    for (int i = 0; i < level; i++) {
        std::cout << '\t';
    }
    if (level == 1) {
        std::cout << "[" << idx << "] " << format_st(m_type) << " : " << m_text << std::endl;
    } else {
        std::cout << format_st(m_type) << " : " << m_text << std::endl;
    }
    int i = 0;
    for (auto& item : m_child) {
        item->print(level + 1, i);
        i ++;
    }
}

void ast_node::dump() {
    print(0, 0);
}
