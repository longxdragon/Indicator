//
//  compiler.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/27.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "compiler.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "parse_walker.hpp"
#include "evaluator.hpp"

compiler::compiler(std::vector< std::map<std::string, std::string> > dt) {
    data = dt;
}

result compiler::compile(std::string s) {
    
    lexer lxr = lexer();
    token_reader reader = lxr.tokenize(s);
    if (debug) {
        reader.dump();
    }
    
    parser pser = parser();
    ast_node::ptr node = pser.analyze(reader);
    if (debug) {
        node->dump();
    }
    
    parse_walker wkr = parse_walker();
    bool is = wkr.walker(node);
    if (!is) {
        return result();
    }
    
    evaluator elr = evaluator(data);
    result rt = elr.evaluate(node);
    return rt;
}
