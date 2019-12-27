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

compiler::compiler(std::vector<std::map<std::string, std::string>> dt) {
    data = dt;
}

std::map< std::string, std::vector<double> > compiler::compile(std::string s) {
    lexer lxr = lexer();
    token_reader reader = lxr.tokenize(s);
    reader.dump();
    
    parser pser = parser();
    ast_node::ptr node = pser.analyze(reader);
    node->dump();
    
    std::cout << std::endl;
    parse_walker wkr = parse_walker();
    bool is = wkr.walker(node);
    if (is) {
        std::cout << "Parse walker lookup success!" << std::endl;
    }
    std::cout << std::endl;
    
    evaluator elr = evaluator(data);
    std::map< std::string, std::vector<double> > val = elr.evaluate(node);
    return val;
}
