//
//  main.cpp
//  Indicator
//
//  Created by 许龙 on 2019/11/12.
//  Copyright © 2019 许龙. All rights reserved.
//

#include <iostream>

#include "lexer.hpp"
#include "parser.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    string str1 = "\
    HH := HHV(HIGH, 219);\
    LL := LLV(LOW, 219);\
    HH1 := BARSLAST((HH > REF(HH,1)));\
    LL1 := BARSLAST((LL < REF(LL,1)));\
    X := IF((HH1 < LL1), LL, HH);\
    Y := IF((HH1 > LL1), HH, LL);\
    DRAWTEXT(CROSS(HH1,LL1), HH, '空头');\
    DRAWTEXT(CROSS(LL1,HH1), LL, '多头');\
    \
    MA05 := MA(CLOSE,45);\
    MA10 := MA(CLOSE,13);\
    VAR1 := MA(CLOSE,55);\
    \
    M := 14;\
    TYP := (HIGH + LOW + CLOSE)/3;\
    CCI := (TYP-MA(TYP,M))/(0.015*AVEDEV(TYP,M));\
    ";
    
    string str = "\
    MA55:=MA(C,55);\
    \
    DRAWTEXT(CROSS(EMA(C,5),EMA(C,10)),L,'开多');\
    DRAWTEXT(CROSS(EMA(C,10),EMA(C,5)),H,'开空');\
    DRAWCOLORLINE(C>MA55,MA55,COLORRED,COLORCYAN);\
    \
    主趋势线:EMA(EMA(C,10),10);\
    B:=主趋势线>REF(主趋势线,1);\
    IF(B-1,主趋势线,NULL);\
    ";
    
    lexer lxr = lexer();
    token_reader reader = lxr.tokenize(str1);
//    reader.dump();
    
    parser pser = parser();
    ast_node::ptr node = pser.analyze(reader);
    node->dump();
    
    return 0;
}


