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

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...

    vector<map<string, string>> data;
    
    map<string, string> item1;
    item1.insert({"l", "354.40"});
    item1.insert({"o", "361.01"});
    item1.insert({"h", "383.17"});
    item1.insert({"c", "380.69"});
    data.push_back(item1);
    
    map<string, string> item2;
    item2.insert({"l", "354.40"});
    item2.insert({"o", "378.51"});
    item2.insert({"h", "383.17"});
    item2.insert({"c", "380.17"});
    data.push_back(item2);
    
    for (size_t i = 0; i < 26; i++) {
        map<string, string> item;
        item.insert({"l", "2013"});
        item.insert({"o", "2022"});
        item.insert({"h", "2025"});
        switch (i) {
            case 0: item.insert({"c", "451.6"}); break;
            case 1: item.insert({"c", "449.6"}); break;
            case 2: item.insert({"c", "458.9"}); break;
            case 3: item.insert({"c", "463.5"}); break;
            case 4: item.insert({"c", "458.0"}); break;
            case 5: item.insert({"c", "466.2"}); break;
            case 6: item.insert({"c", "480.2"}); break;
            case 7: item.insert({"c", "489.6"}); break;
            case 8: item.insert({"c", "499.7"}); break;
            case 9: item.insert({"c", "479.1"}); break;
            case 10: item.insert({"c", "464.0"}); break;
            case 11: item.insert({"c", "447.2"}); break;
            case 12: item.insert({"c", "404.9"}); break;
            case 13: item.insert({"c", "408.2"}); break;
            case 14: item.insert({"c", "415.4"}); break;
            case 15: item.insert({"c", "353.5"}); break;
            case 16: item.insert({"c", "357.3"}); break;
            case 17: item.insert({"c", "267.1"}); break;
            case 18: item.insert({"c", "244.9"}); break;
            case 19: item.insert({"c", "255.6"}); break;
            case 20: item.insert({"c", "283.5"}); break;
            case 21: item.insert({"c", "290.0"}); break;
            case 22: item.insert({"c", "253.7"}); break;
            case 23: item.insert({"c", "231.1"}); break;
            case 24: item.insert({"c", "229.0"}); break;
            case 25: item.insert({"c", "248.6"}); break;
            default: break;
        }
        data.push_back(item);
    }
    
    string tx = "N:=12;M:=20;TR:=EMA(EMA(EMA(CLOSE,N),N),N);REFTR:=REF(TR,1);TRIX:(TR-REFTR)/REFTR*100;TRMA:MA(TRIX,M);";
    
    
    compiler clr = compiler(data);
    clr.debug = true;
    result val = clr.compile(tx);
    
    return 0;
}
