//
//  parser.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "parser.hpp"

ast_node::ptr pri_express(token_reader& reader) {
    ast_node::ptr node = nullptr;
    token t = reader.peek();
    if (!reader.empty()) {
        if (t.st == dfa_state::identifier) {
            node = ast_node::create(ast_node_type::identifier, t.txt);
        }
    }
    return node;
}

ast_node::ptr mul_express(token_reader& reader) {
    ast_node::ptr child_1 = pri_express(reader);
    ast_node::ptr node = child_1;
    while (true) {
        token t = reader.peek();
        if (node != nullptr && !t.empty() && (t.st == multi || t.st == divide)) {
            t = reader.read();
            ast_node::ptr child_2 = pri_express(reader);
            node = ast_node::create(ast_node_type::mul_express, t.txt);
            node->add_child(child_1);
            if (child_2 != nullptr) {
                node->add_child(child_2);
            } else {
                cout << "An valid expression is required!" << endl;
            }
        } else {
            break;
        }
    }
    return node;
}

ast_node::ptr add_express(token_reader& reader) {
    ast_node::ptr child_1 = mul_express(reader);
    ast_node::ptr node = child_1;
    while (true) {
        token t = reader.peek();
        if (node != nullptr && !t.empty() && (t.st == add || t.st == reduce)) {
            t = reader.read();
            ast_node::ptr child_2 = mul_express(reader);
            node = ast_node::create(ast_node_type::add_express, t.txt);
            node->add_child(child_1);
            if (child_2 != nullptr) {
                node->add_child(child_2);
            } else {
                cout << "An valid expression is required!" << endl;
            }
        } else {
            break;
        }
    }
    return node;
}

ast_node::ptr rel_express(token_reader& reader) {
    ast_node::ptr child_1 = add_express(reader);
    ast_node::ptr node = child_1;
    while (true) {
        token t = reader.peek();
        if (node != nullptr && !t.empty() && (t.st == gt || t.st == ge || t.st == lt || t.st == le)) {
            t = reader.read();
            ast_node::ptr child_2 = add_express(reader);
            node = ast_node::create(ast_node_type::rel_express, t.txt);
            node->add_child(child_1);
            if (child_2 != nullptr) {
                node->add_child(child_2);
            } else {
                cout << "An valid expression is required!" << endl;
            }
        } else {
            break;
        }
    }
    return node;
}

ast_node::ptr equal_express(token_reader& reader) {
    ast_node::ptr child_1 = rel_express(reader);
    ast_node::ptr node = child_1;
    while (true) {
        token t = reader.peek();
        if (node != nullptr && !t.empty() && (t.st == single_equal || t.st == no_equal)) {
            t = reader.read();
            ast_node::ptr child_2 = rel_express(reader);
            node = ast_node::create(ast_node_type::equal_express, t.txt);
            node->add_child(child_1);
            if (child_2 != nullptr) {
                node->add_child(child_2);
            } else {
                cout << "An valid expression is required!" << endl;
            }
        } else {
            break;
        }
    }
    return node;
}

ast_node::ptr and_express(token_reader& reader) {
    ast_node::ptr child_1 = equal_express(reader);
    ast_node::ptr node = child_1;
    while (true) {
        token t = reader.peek();
        if (node != nullptr && !t.empty() && (t.st == single_and || t.st == double_and)) {
            t = reader.read();
            ast_node::ptr child_2 = equal_express(reader);
            node = ast_node::create(ast_node_type::and_express, t.txt);
            node->add_child(child_1);
            if (child_2 != nullptr) {
                node->add_child(child_2);
            } else {
                cout << "An valid expression is required!" << endl;
            }
        } else {
            break;
        }
    }
    return node;
}

ast_node::ptr or_express(token_reader& reader) {
    ast_node::ptr child_1 = and_express(reader);
    ast_node::ptr node = child_1;
    while (true) {
        token t = reader.peek();
        if (node != nullptr && !t.empty() && (t.st == single_or || t.st == double_or)) {
            t = reader.read();
            ast_node::ptr child_2 = and_express(reader);
            node = ast_node::create(ast_node_type::or_express, t.txt);
            node->add_child(child_1);
            if (child_2 != nullptr) {
                node->add_child(child_2);
            } else {
                cout << "An valid expression is required!" << endl;
            }
        } else {
            break;
        }
    }
    return node;
}

ast_node::ptr express(token_reader& reader) {
    ast_node::ptr child_1 = or_express(reader);
    ast_node::ptr node = child_1;
    token t = reader.peek();
    if (node != nullptr && !t.empty()) {
        if (t.st == dfa_state::assignment) {
            reader.read();
            ast_node::ptr child_2 = express(reader);
            node = ast_node::create(ast_node_type::assignment, t.txt);
            node->add_child(child_1);
            if (child_2 != nullptr) {
                node->add_child(child_2);
            } else {
                cout << "An valid expression is required!" << endl;
            }
        }
    }
    return node;
}

ast_node::ptr parser::analyze(token_reader& reader) {
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
        } else {
            node = express(reader);
        }
    }
    return node;
}
