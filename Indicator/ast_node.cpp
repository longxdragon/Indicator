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
