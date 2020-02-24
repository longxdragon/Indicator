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

- (NSDictionary *)compileKlineDataSource:(NSArray<NSDictionary *> *)datas formula:(NSString *)formula;

@end

NS_ASSUME_NONNULL_END
