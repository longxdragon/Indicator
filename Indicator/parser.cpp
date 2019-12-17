//
//  parser.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "parser.hpp"

ast_node::ptr parser::analyze(token_reader &reader) {
    ast_node::ptr node = nullptr;
    token t = reader.peek();
    if (!t.empty()) {
        if (t.st == static_key) {
            t = reader.read();
            node = ast_node::create(ast_node_type::declaration, t.txt);
            while (!reader.end()) {
                ast_node::ptr child;
                node->add_child(child);
            }
        }
    }
    return node;
}
