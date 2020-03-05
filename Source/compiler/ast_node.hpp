//
//  ast_node.hpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#ifndef ast_node_hpp
#define ast_node_hpp

#include <stdio.h>
#include <string>
#include <list>
#include <iostream>
#include <memory>

enum class ast_node_type {
    root,
    
    identifier,
    digit_literal,
    string_literal,
    static_literal,
    
    assignment,
    return_assignment,
    
    or_express,
    and_express,
    equal_express,
    rel_express,
    add_express,
    mul_express,
    fun_express,
};

class ast_node {
    
public:
    using ptr = std::shared_ptr<ast_node>;
    ast_node();
    ast_node(const ast_node_type &type, const std::string& text);
    static ptr create(const ast_node_type &type, const std::string& text);
    void add_child(ptr node);
    void dump();

    ast_node_type get_type();
    std::string get_text();
    std::list<ptr> get_child();
    ast_node::ptr get_child(int idx);
    
private:
    ast_node_type m_type;
    std::string m_text;
    std::list<ptr> m_child;
    void print(int level);
};

#endif /* ast_node_hpp */
