//
//  main.cpp
//  Indicator
//
//  Created by 许龙 on 2020/2/10.
//  Copyright © 2020 ldd. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "compiler.hpp"
#include "lib_math.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    map<string, string> item_1;
    item_1.insert({"c", "2012"});
    item_1.insert({"o", "2022"});
    item_1.insert({"h", "2025"});
    item_1.insert({"l", "2001"});
    
    map<string, string> item_2;
    item_2.insert({"c", "2013"});
    item_2.insert({"o", "2022"});
    item_2.insert({"h", "2025"});
    item_2.insert({"l", "2001"});
    
    map<string, string> item_3;
    item_3.insert({"c", "2010"});
    item_3.insert({"o", "2022"});
    item_3.insert({"h", "2025"});
    item_3.insert({"l", "2001"});
    
    map<string, string> item_4;
    item_4.insert({"c", "2011"});
    item_4.insert({"o", "2022"});
    item_4.insert({"h", "2025"});
    item_4.insert({"l", "2001"});
    
    map<string, string> item_5;
    item_5.insert({"c", "2013"});
    item_5.insert({"o", "2022"});
    item_5.insert({"h", "2025"});
    item_5.insert({"l", "2001"});
    
    vector<map<string, string>> data;
    data.push_back(item_1);
    data.push_back(item_2);
    data.push_back(item_3);
    data.push_back(item_4);
    data.push_back(item_5);
    
    vector<double> n;
    n.push_back(1);
    n.push_back(0);
    n.push_back(1);
    n.push_back(0);
    n.push_back(0);
    vector<double> rt = lib_math::eif(n, lib_math::c(data), lib_math::o(data));
    
    
    string tx = "\
    MA55:=MA(C,55);\
    \
    //压力支撑1\
    MAL:=30;\
    FACTOR:=3;\
    TR:= MAX(MAX((HIGH-LOW),ABS(REF(CLOSE,1)-HIGH)),ABS(REF(CLOSE,1)-LOW));\
    ATR:= MA(TR,50);\
    CURRDN:=MA(CLOSE,MAL)+ ATR*FACTOR;\
    CURRUP:=MA(CLOSE,MAL)- ATR*FACTOR;\
    ";
    
    compiler clr = compiler(data);
    result val = clr.compile("UDD:=2 + 2*STD(CLOSE,26);");
        
    return 0;
}
