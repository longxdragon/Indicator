//
//  ViewController.m
//  INCompilerDemo
//
//  Created by 许龙 on 2020/5/13.
//  Copyright © 2020 ldd. All rights reserved.
//

#import "ViewController.h"
#import "INOCCompiler.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    NSString *text = @"REC:REF(C,1);\
    REH:REF(H,1);\
    REL:REF(L,1);\
    P:IF(REC<O,REH+REL*2+REC,IF(REC>O,REH*2+REL+REC,REH+REL+REC*2));\
    R1:P/2-REL;\
    S1:P/2-REH";
    
    NSArray *datas = @[
        @{
            @"c" : @"380.69",
            @"o" : @"361.01",
            @"h" : @"383.17",
            @"l" : @"354.40"
        },
        @{
            @"c" : @"380.72",
            @"o" : @"378.51",
            @"h" : @"384.37",
            @"l" : @"377.50"
        }
    ];
    INOCCompiler *compiler = [[INOCCompiler alloc] init];
    NSDictionary *result = [compiler compileKlineDataSource:datas formula:text];
    NSLog(@"%@", result);
}


@end
