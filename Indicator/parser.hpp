//
//  parser.hpp
//  Indicator
//
//  Created by 许龙 on 2019/12/17.
//  Copyright © 2019 许龙. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include <string>

#include "ast_node.hpp"
#include "token_reader.hpp"

class parser {
    
    
public:
    ast_node::ptr analyze(token_reader& reader);
};

#endif /* parser_hpp */
