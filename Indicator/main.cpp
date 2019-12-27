//
//  main.cpp
//  Indicator
//
//  Created by 许龙 on 2019/11/12.
//  Copyright © 2019 许龙. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "compiler.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    map<string, string> item_1;
    item_1.insert({"c", "2012"});
    item_1.insert({"o", "2022"});
    item_1.insert({"h", "2025"});
    item_1.insert({"l", "2001"});
    
    map<string, string> item_2;
    item_2.insert({"c", "2012"});
    item_2.insert({"o", "2022"});
    item_2.insert({"h", "2025"});
    item_2.insert({"l", "2001"});
    
    map<string, string> item_3;
    item_3.insert({"c", "2012"});
    item_3.insert({"o", "2022"});
    item_3.insert({"h", "2025"});
    item_3.insert({"l", "2001"});
    
    map<string, string> item_4;
    item_4.insert({"c", "2012"});
    item_4.insert({"o", "2022"});
    item_4.insert({"h", "2025"});
    item_4.insert({"l", "2001"});
    
    map<string, string> item_5;
    item_5.insert({"c", "2012"});
    item_5.insert({"o", "2022"});
    item_5.insert({"h", "2025"});
    item_5.insert({"l", "2001"});
    
    vector<map<string, string>> data;
    data.push_back(item_1);
    data.push_back(item_2);
    data.push_back(item_3);
    data.push_back(item_4);
    data.push_back(item_5);
    
    
    
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
    FG02:=FG01=FD01 AND G1>D1 OR G1<=D1;\
    FD02:=FG01=FD01 AND G1<D1;\
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
    
    
    string cci = "\
    M := 14;\
    TYP := (HIGH + LOW + CLOSE)/3;\
    CCI := (TYP-MA(TYP,M))/(0.015*AVEDEV(TYP,M));\
    ";
    
    string ma = "\
    MA2 := MA(C, 2);\
    MA10 := MA(C, 10);\
    ";
    
    compiler clr = compiler(data);
    std::map< std::string, std::vector<double> > val = clr.compile(ma);
    
    return 0;
}


