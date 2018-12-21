//
//  IVBLEUtils.h
//  Pods
//
//  Created by 曹凯 on 15/10/15.
//
//
#define DEVELOPER_TEST 2  //1-open ,other-close

#import "ZRHWOption.h"
#import <Foundation/Foundation.h>

@interface IVBLEUtils : NSObject

+ (NSString *)getAscIIString:(NSString *)str;

+ (NSString *)getStringWithUtf8:(NSString *)str;

+ (NSString *)getUintStringWithUtf8:(NSString *)str;

//只支持ASCII码支持的字符
+ (NSString *)uint8StrArrayToAscIIString:(NSString *)str;

+ (NSInteger)uint16StrToInteger:(NSString *)str;

+ (NSInteger)uint24StrToInteger:(NSString *)str;

+ (NSInteger)uint32StrToInteger:(NSString *)str;

+ (NSString *)uint32StringfromInteger:(NSInteger)intNum;

+ (NSInteger)int32StrToInteger:(NSString *)str;

+ (NSInteger)int16StrToInteger:(NSString *)str;

+ (NSString *)int16StrFromInteger:(NSInteger)intNum;

//return YES means time interval < 30 s
+ (BOOL)compareTimeStr:(NSString *)timeA andStr:(NSString *)timeB;

+ (NSString *)getMotorString:(ZRMotor *)motor;

+ (NSString *)getMotorsStringBy:(NSArray<ZRMotor*> *)motors;

+ (NSString *)getCustomOptionString:(ZRCOption *)cOption;

+ (NSString *)getWeatherString:(ZRWeather *)weather;

+ (NSString *)getActionString:(ZRAction *)action;

+ (BOOL)cheakDateValidity:(NSDictionary *)dateDict;

+ (NSString *)stringFromDate:(NSDate *)date;
+ (NSDate *)dateFormatString:(NSString *)str;
+ (NSDate *)dateWithDict:(NSDictionary *)dict;
+ (NSDate *)dateWithArray:(int *)array; /*Array[0]:count*/
+ (NSDate *)dateAtStratOfday:(NSDate *)date;

+ (NSInteger)weekNum:(NSDate *)date;
+ (NSInteger)yearOfDate:(NSDate *)date ;
+ (NSInteger)monthOfDate:(NSDate *)date ;
+ (NSInteger)dayOfDate:(NSDate *)date;
+ (NSInteger)hourOfDate:(NSDate *)date;
+ (NSInteger)minuteOfDate:(NSDate *)date;
+ (NSInteger)secondOfDate:(NSDate *)date;
+ (BOOL)isSameDay:(NSDate *)dateA andDate:(NSDate *)dateB;
//创建文件
//创建文件夹
+ (BOOL)createDirWithPath:(NSString *)path Name:(NSString *)name;

+ (BOOL)createFileWithPath:(NSString *)path;

+ (BOOL)createFile:(NSString *)path;

//写文件
+ (BOOL)writeFileHead:(NSString *)str toPath:(NSString *)path;

//写文件
+ (void)writeFile:(NSString *)str toPath:(NSString *)path;

//删除文件
+ (void)deleteFileByPath:(NSString *)path;

//文件大小
+ (long long)fileSizeAtPath:(NSString *)filePath;

+ (NSString *)bleFileConnect;

+ (void)clearBLEFile;

//BLElog  read  write  以及 normal(常规log)
+ (void)writeBLELog:(NSString *)logStr andType:(bleLogType)type;

//获取app当前的系统语言
+ (NSString *)getCurrentAppLanguage;

@end
