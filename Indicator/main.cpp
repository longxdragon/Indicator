//
//  main.cpp
//  Indicator
//
//  Created by 许龙 on 2019/11/12.
//  Copyright © 2019 许龙. All rights reserved.
//

#include <iostream>

#include "lexer.cpp"

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
    DRAWTEXT(HH1>LL1 && CLOSE<VAR1 && CCI>=100, HIGH+0.005, '卖');\
    DRAWTEXT(HH1<LL1 && CLOSE>VAR1 && CCI<=-100, LOW-0.005, '买');\
    \
    支撑位 := LLV(LOW,219);\
    压力位 := HHV(HIGH,219);\
    ";
    lexer lxr = lexer();
    lxr.dump(lxr.tokenize(str));
    
    return 0;
}


/**
 1、需求不明确，通用组件的概念太多，没明确到非常细的颗粒度。
 2、我这边的需求消化也没完全到位，特别是通用图表概念，估时高端了。
 3、需求变更太频繁。
 4、UI出图，不要只出示例，各种情况的组件，建议都出一份。
 
 技术不配合开发？UI的改动还是需要点技术理论知识，因为确实有些不好改。
 */


