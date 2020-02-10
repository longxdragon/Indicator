//
//  INOCCompiler.h
//  INCompiler
//
//  Created by 许龙 on 2020/2/10.
//  Copyright © 2020 ldd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface INOCCompiler : NSObject

- (instancetype)initWithDataSource:(NSArray<NSDictionary *> *)datas;

- (NSDictionary *)compile;

- (void)addCode:(NSString *)code forKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
