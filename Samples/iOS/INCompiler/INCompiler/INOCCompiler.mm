//
//  INOCCompiler.m
//  INCompiler
//
//  Created by 许龙 on 2020/2/10.
//  Copyright © 2020 ldd. All rights reserved.
//

#import "INOCCompiler.h"

#import "compiler.hpp"
#import "result.hpp"

@interface INOCCompiler ()

@end

@implementation INOCCompiler

- (NSDictionary *)compileKlineDataSource:(NSArray<NSDictionary *> *)datas formula:(NSString *)formula {
    
    vector< map<string, string> > list;
    for (NSDictionary *item in datas) {
        map<string, string> m;
        NSString *o = item[@"o"];
        NSString *c = item[@"c"];
        NSString *h = item[@"h"];
        NSString *l = item[@"l"];
        if ([o isKindOfClass:[NSString class]]) m["o"] = string([o UTF8String]);
        if ([c isKindOfClass:[NSString class]]) m["c"] = string([c UTF8String]);
        if ([h isKindOfClass:[NSString class]]) m["h"] = string([h UTF8String]);
        if ([l isKindOfClass:[NSString class]]) m["l"] = string([l UTF8String]);
        list.push_back(m);
    }
    
    string txt = string([formula UTF8String]);
    compiler clr = compiler(list);
    result val = clr.compile(txt);
    
    map< string, vector<double> > digit = val.get_digit_values();
    NSMutableDictionary *res1 = [NSMutableDictionary new];
    auto iter2 = digit.begin();
    while (iter2 != digit.end()) {
        string key = iter2->first;
        vector<double> val = iter2->second;
        NSString *k = [NSString stringWithCString:key.c_str() encoding:NSUTF8StringEncoding];
        NSMutableArray *v = [NSMutableArray new];
        for (int i = 0; i < val.size(); i++) {
            [v addObject:[NSString stringWithFormat:@"%f", val[i]]];
        }
        res1[k] = v;
        iter2++;
    }
    
    NSMutableDictionary *res2 = [NSMutableDictionary new];
    map< string, vector< map<string, string> > > draw = val.get_draw_text_values();
    map< string, vector< map<string, string> > >::iterator iter = draw.begin();
    while (iter != draw.end()) {
        string key = iter->first;
        vector< map<string, string> > val = iter->second;
        NSString *k = [NSString stringWithCString:key.c_str() encoding:NSUTF8StringEncoding];
        NSMutableArray *v = [NSMutableArray new];
        for (int i = 0; i < val.size(); i++) {
            map<string, string> xx = val[i];
            NSMutableDictionary *xxx = [NSMutableDictionary new];
            NSString *pt = [NSString stringWithCString:xx["pt"].c_str() encoding:NSUTF8StringEncoding];
            NSString *tx = [NSString stringWithCString:xx["tx"].c_str() encoding:NSUTF8StringEncoding];
            xxx[@"val"] = pt;
            xxx[@"desc"] = tx;
            if (xxx.count) {
                [v addObject:xxx];
            }
        }
        res2[k] = v;
        iter++;
    }
    
    NSMutableDictionary *res3 = [NSMutableDictionary new];
    map< string, vector<string> > pps = val.get_property_values();
    map< string, vector<string> >::iterator iter3 = pps.begin();
    while (iter3 != pps.end()) {
        string key = iter3->first;
        vector<string> val = iter3->second;
        NSString *k = [NSString stringWithCString:key.c_str() encoding:NSUTF8StringEncoding];
        NSMutableArray *v = [NSMutableArray new];
        for (int i = 0; i < val.size(); i++) {
            string xx = val[i];
            NSString *xxx = [NSString stringWithCString:xx.c_str() encoding:NSUTF8StringEncoding];
            if (xxx) {
                [v addObject:xxx];
            }
        }
        res3[k] = v;
        iter3++;
    }
    
    return @{ @"assign" : res1, @"draw_text" : res2, @"property" : res3 };
}

@end
