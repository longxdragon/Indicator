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

enum class ast_node_type {
    declaration,
};

class ast_node {
    
public:
    using ptr = std::shared_ptr<ast_node>;
    ast_node();
    ast_node(const ast_node_type &type, const std::string& text);
    static ptr create(const ast_node_type &type, const std::string& text);
    void add_child(ptr node);

private:
    ast_node_type m_type;
    std::string m_text;
    std::list<ptr> m_child;
};

#endif /* ast_node_hpp */
