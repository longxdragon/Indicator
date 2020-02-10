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

@property (nonatomic, strong) NSMutableArray *list;
@property (nonatomic, strong) NSMutableDictionary *codeMap;

@end

@implementation INOCCompiler {
    @private
    compiler *_clr;
}

- (void)dealloc {
    free(_clr);
}

- (instancetype)initWithDataSource:(NSArray<NSDictionary *> *)datas {
    self = [super init];
    if (self) {
        self.list = [datas mutableCopy];
        
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
        _clr = new compiler(list);
    }
    return self;
}

- (NSDictionary *)compile {
    NSMutableDictionary *rt = [NSMutableDictionary new];
    
    for (NSString *key in self.codeMap.allKeys) {
        NSString *format = self.codeMap[key];
        
        string txt = string([format UTF8String]);
        result val = _clr->compile(txt);
        
        map< string, vector<double> > digit = val.get_digit_values();
        NSMutableDictionary *res1 = [NSMutableDictionary new];
        auto iter2 = digit.begin();
        while (iter2 != digit.end()) {
            string key = iter2->first;
            vector<double> val = iter2->second;
            NSString *k = [NSString stringWithCString:key.c_str() encoding:NSUTF8StringEncoding];
            NSMutableArray *v = [NSMutableArray new];
            for (int i = 0; i < val.size(); i++) {
                [v addObject:@(val[i])];
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
        
        rt[key] = @{ @"assign" : res1, @"draw_text" : res2 };
    }
    return [rt copy];
}

- (void)addCode:(NSString *)code forKey:(NSString *)key {
    if (!code.length || !key.length) return;
    self.codeMap[key] = code;
}

#pragma mark - Getters

- (NSMutableDictionary *)codeMap {
    if (!_codeMap) {
        _codeMap = [NSMutableDictionary new];
    }
    return _codeMap;
}

@end
