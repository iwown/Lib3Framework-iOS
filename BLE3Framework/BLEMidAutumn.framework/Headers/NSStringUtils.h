//
//  NSStringUtils.h
//  BLELib3
//
//  Created by 曹凯 on 2017/1/5.
//  Copyright © 2017年 Iwown. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSStringUtils : NSObject

// 16进制NSData转换成NSString
+ (NSString *)NSDataToByteTohex:(NSData *)data;
+ (NSData *)stringToByte:(NSString *)string;
+ (NSString *)hexStringFromString:(NSString *)string;

//两位 16进制转换10进制（高低位互换）
+ (NSString *)ToHexString:(int)tmpid;
+ (int)ToHexInt:(NSString *)tmpid;
+ (NSString *)uint16ToString:(NSInteger)num;
//4位 16进制
+ (NSString *)hl32StringWithInt:(unsigned long)am;
+ (NSString *)hl32StringByString:(NSString *)string;
+ (NSString *)int64ToHex:(int64_t)tmpid;

+ (NSString *)signedInt64ToHex:(int64_t)intNumber;

@end
