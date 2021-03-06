//
//  parser.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "parser.hpp"

ast_node::ptr express(token_reader& reader);

ast_node::ptr pri_express(token_reader& reader) {
    ast_node::ptr node = nullptr;
    token t = reader.peek();
    if (!reader.empty()) {
        if (t.st == dfa_state::identifier) {
            reader.read();
            node = ast_node::create(ast_node_type::identifier, t.txt);
        } else if (t.st == dfa_state::digit) {
            reader.read();
            node = ast_node::create(ast_node_type::digit_literal, t.txt);
        } else if (t.st == dfa_state::string_literal) {
            reader.read();
            node = ast_node::create(ast_node_type::string_literal, t.txt);
        } else if (t.st == dfa_state::static_key) {
            reader.read();
            node = ast_node::create(ast_node_type::static_literal, t.txt);
        } else if (t.st == dfa_state::property_key) {
            reader.read();
            node = ast_node::create(ast_node_type::property_literal, t.txt);
            
        } else if (t.st == dfa_state::left_paren) {
            reader.read();
            node = express(reader);
            t = reader.read(); // right_paren
            if (t.empty() || t.st != dfa_state::right_paren) {
                cout << "An valid expression is required! --- pri_express --- " << t.description() << endl;
                return nullptr;
            }
        } else if (t.st == dfa_state::function_name) {
            reader.read();  // consume 'function_name'
            node = ast_node::create(ast_node_type::fun_express, t.txt);
            t = reader.peek();
            if (t.st == dfa_state::left_paren) {
                reader.read();  // consume '('
                while (true) {
                    ast_node::ptr child = express(reader);
                    if (child != nullptr) {
                        node->add_child(child);
                        t = reader.peek();
                        if (t.st == dfa_state::comma) {
                            reader.read();  // consum ','
                        } else if (t.st == dfa_state::right_paren) {
                            reader.read();  // consum ')'
                            break;
                        } else {
                            cout << "An valid expression is required! --- pri_express --- " << t.description() << endl;
                            return nullptr;
                        }
                    } else {
                        break;
                    }
                }
            }
        } else {
            cout << "An valid expression is required! --- pri_express --- " << t.description() << endl;
            return nullptr;
        }
    } else {
        cout << "An valid expression is required! --- pri_express --- " << t.description() << endl;
        return nullptr;
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
            if (child_2 != nullptr) {
                node = ast_node::create(ast_node_type::mul_express, t.txt);
                node->add_child(child_1);
                node->add_child(child_2);
                child_1 = node;
            } else {
                cout << "An valid expression is required! --- mul_express --- " << t.description() << endl;
                return nullptr;
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
            if (child_2 != nullptr) {
                node = ast_node::create(ast_node_type::add_express, t.txt);
                node->add_child(child_1);
                node->add_child(child_2);
                child_1 = node;  // associativity
            } else {
                cout << "An valid expression is required! --- add_express --- " << t.description() << endl;
                return nullptr;
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
            if (child_2 != nullptr) {
                node = ast_node::create(ast_node_type::rel_express, t.txt);
                node->add_child(child_1);
                node->add_child(child_2);
                child_1 = node;
            } else {
                cout << "An valid expression is required! --- rel_express --- " << t.description() << endl;
                return nullptr;
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
            if (child_2 != nullptr) {
                node = ast_node::create(ast_node_type::equal_express, t.txt);
                node->add_child(child_1);
                node->add_child(child_2);
                child_1 = node;
            } else {
                cout << "An valid expression is required! --- equal_express --- " << t.description() << endl;
                return nullptr;
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
            if (child_2 != nullptr) {
                node = ast_node::create(ast_node_type::and_express, t.txt);
                node->add_child(child_1);
                node->add_child(child_2);
                child_1 = node;
            } else {
                cout << "An valid expression is required! --- and_express --- " << t.description() << endl;
                return nullptr;
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
            if (child_2 != nullptr) {
                node = ast_node::create(ast_node_type::or_express, t.txt);
                node->add_child(child_1);
                node->add_child(child_2);
                child_1 = node;
            } else {
                cout << "An valid expression is required! --- or_express --- " << t.description() << endl;
                return nullptr;
            }
        } else {
            break;
        }
    }
    return node;
}

ast_node::ptr express(token_reader& reader) {
    return or_express(reader);
}

ast_node::ptr assignment_express(token_reader& reader) {
    ast_node::ptr node = nullptr;
    ast_node::ptr child_1 = pri_express(reader);
    token t = reader.peek();
    if (child_1 != nullptr && !t.empty()) {
        if (t.st == dfa_state::assignment || t.st == dfa_state::colon) {
            reader.read();
            ast_node::ptr child_2 = or_express(reader);
            if (child_2 != nullptr) {
                if (t.st == dfa_state::colon) node = ast_node::create(ast_node_type::return_assignment, t.txt);
                else node = ast_node::create(ast_node_type::assignment, t.txt);
                node->add_child(child_1);
                node->add_child(child_2);
            } else {
                cout << "An valid expression is required! --- assignment --- " << t.description() << endl;
                return nullptr;
            }
        }
    }
    return node;
}

ast_node::ptr parser::analyze(token_reader& reader) {
    ast_node::ptr node = ast_node::create(ast_node_type::root, "Root");
    token t = reader.peek();
    while (!t.empty()) {
        ast_node::ptr child = nullptr;
        if (t.st == dfa_state::identifier) {
            child = assignment_express(reader);
        } else if (t.st == dfa_state::function_name) {
            child = pri_express(reader);
        }
        if (child == nullptr) { // error
            return node;
        }
        
        ast_node::ptr statement = ast_node::create(ast_node_type::statement, "Statement");
        ast_node::ptr pro = ast_node::create(ast_node_type::property, "Property");
        statement->add_child(child);
        statement->add_child(pro);
    
        node->add_child(statement);
        
        t = reader.peek();
        while (t.st != dfa_state::semicolon) {
            if (t.st == dfa_state::comma) {
                reader.read();
            } else {
                ast_node::ptr pp = pri_express(reader);
                if (pp != nullptr) {
                    pro->add_child(pp);
                }
            }
            t = reader.peek();
        }
        reader.read(); // consume ';'
        t = reader.peek();
    }
    return node;
}
