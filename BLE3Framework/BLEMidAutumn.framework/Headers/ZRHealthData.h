//
//  ZRHealthData.h
//  BLE3Framework
//
//  Created by 曹凯 on 16/10/12.
//  Copyright © 2016年 ZR. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ZRDataTypes.h"
#import "AutumnHeader.h"

typedef struct {
    uint16_t seqStart;
    uint16_t seqEnd;
    RecorDate storeDate;
}DateDataInfo;

typedef struct {
    uint8_t dataType;
    uint8_t totaldays;
    DateDataInfo ddInfos[7];
}TDateStoreInfo;

typedef enum {
    ZRDITypeNormalData = 0x00, //Normal data in Colorful Screen Band.
    ZRDITypeHbridHealth = 0x28, //0x28,0x29,0x51,0x53. Hbrid data for classical band.
    ZRDITypeNormalHealth = 0x61, //Normal health data for Watch
    ZRDITypeGNSSData = 0x62, // GNSS data in Watch
    ZRDITypeECGHealth = 0x64,// ECG data in Watch
} ZRDIType;

@interface DDInfo : NSObject

+ (instancetype)objectFrom:(DateDataInfo)ddInfo;
@property (nonatomic ,strong) NSDate *date;
@property (nonatomic ,assign) NSInteger seqStart;
@property (nonatomic ,assign) NSInteger seqEnd;

@end

@class ZRHealthData;
@interface ZRDataInfo : NSObject

@property (nonatomic ,strong) NSArray <DDInfo *> *ddInfos;
@property (nonatomic ,assign) NSUInteger dataType;

+ (instancetype)zrDataInfoFromDateStoreInfo:(DateStoreInfo)dsInfo;
+ (instancetype)zrDataInfoFromTDateStoreInfo:(TDateStoreInfo)tdsInfo;
+ (instancetype)zrDataInfoFromZRHealthData:(NSDictionary *)dataDict;

- (NSArray <NSDate *>*)getDateArray;

@end


typedef enum {
    HDTypeNull = 0x00,
    HDTypeSleep = 0x27, //0x8903
    HDTypeSport = 0x28, //0x8904 ,Sport&Exercise Segment data
    HDTypeSummary = 0x29,//0x60，0x8900   Summary health data in one day
    HDTypeHrHours = 0x53,//0x8902   static 
    HDTypeHealthMinute = 0x61, //Sport&Health per minute data
    HDTypeGNSSMinute = 0x62, //GNSS per minuter data
    HDTypeGNSSNow = 0x63,  //GNSS即时数据
    HDTypeECG = 0x64,  //ECG数据
    
    HDTypeZGStep = 0x8901,
} HDType;

typedef struct {
    int seq; //循环序列号，和二进制数据一致
    int number; //当前数据在本次同步数据的位置（progress=number/total）
    int total; //本次同步数据总数
    HDType hdType;//本次数据类型
} HealthDataInfo;

@interface ZRHealthData : NSObject

@property (nonatomic ,assign)HealthDataInfo hdInfo;
@property (strong ,nonatomic)NSDate *recordDate;
@property (class, copy ,nonatomic)NSString *dataFrom;
@property (nonatomic ,assign) int seq;

@property (nonatomic, strong)id data;

+ (id)objectFromDict:(NSDictionary *)dict;
@end

@interface ZRSummaryData : ZRHealthData
/**! Unit is meter*/
@property (nonatomic ,assign) float distance;
/**! Calorie , unit is kcal*/
@property (nonatomic ,assign) float calorie;
@property (nonatomic ,assign) int steps;

/**
 The training time for the day, Nil indicates that the current device does not have a training duration data for statistics. Please use updateNormalHealthData: to obtain the required data. different from 0
 */
@property (nonatomic ,strong) NSNumber *exerciseMinutes;

/**
 Like exerciseMinutes, which means sleep time, Nil indicates that the current device does not have a statistical value for the duration of sleep data, use updateNormalHealthData: to obtain the required data
 */
@property (nonatomic ,strong) NSNumber *sleepMinutes;

/**
 The value of the last detection of heart rate, Nil indicates that the current device does not have a recent average heart rate data, use updateNormalHealthData: to obtain the required data
 */
@property (nonatomic ,strong) NSNumber *heartRate;

@end


@interface ZRSleepData : ZRHealthData
@property (nonatomic ,assign) SleepType sleep_type;
/**! The same state duration ,unit is minutes*/
@property (nonatomic ,assign) int activity;

/**
 Here for the introduction of the concept of sleep data, each group of data contains such content, the first data sleepType 1, followed by a fixed effective sleep data (sleepType == 3 | sleepType == 4), and finally A data sleepType is 2 (that means the end of the normal, this sleep data is valid) or 5 (that this is a place data, for example, put the bracelet on the table, may produce such data, the algorithm that this is not valid Sleep data, which is disturbing information), some bracelet will produce sleepType == 6 data that awake, you can also use the interval between the two groups that awake
 sleep_enter : The start of the group is one minute, the date and start_time are the same
 sleep_exit : Similar to sleep_enter.
 mode : 2 or 5.
 */
@property (nonatomic ,assign) int sleep_enter;
@property (nonatomic ,assign) int sleep_exit;
@property (nonatomic ,assign) int mode;

@property (nonatomic ,strong) NSDate *start_time;
@property (nonatomic ,strong) NSDate *end_time;
@end

@interface ZRSportData : ZRHealthData
/**! Numbers of counting sports, like SD_SPORT_TYPE_ROPE_SKIPPING*/
@property (nonatomic ,assign) int countNumbers;
/**! Sport activity ,unit is minutes*/
@property (nonatomic ,assign) int activity;
/**! Calorie , unit is kcal*/
@property (nonatomic ,assign) float calorie;
@property (nonatomic ,assign) int steps;
/**! Unit is meter*/
@property (nonatomic ,assign) float distance;
@property (nonatomic ,strong) NSDate *start_time;
@property (nonatomic ,strong) NSDate *end_time;
@property (nonatomic ,assign) sd_sportType sportType;
/**! Mean heart rate per minute in segmented movement<##>*/
@property (nonatomic ,strong) NSArray *heartBeats;

/**
 maxSpm,avgSpm: 0 means not support
 maxHeart,avgHeart: 0 means do not got
 */
@property (nonatomic ,assign) int maxSpm;
@property (nonatomic ,assign) int avgSpm;
@property (nonatomic ,assign) int maxHeart;
@property (nonatomic ,assign) int avgHeart;

@end

@interface ZRHRateHoursData : ZRHealthData

/**
 Hour in one day ,ranger is 0-23. When it is 8, the value of detaildata belongs to 8: 00-9: 00
 */
@property (nonatomic ,assign) int hours;

/**
 The 60 values in the array represent the average heart rate per minute.
 */
@property (strong ,nonatomic)NSArray *detailData;

@end

@interface ZRStepData : ZRHealthData

@property (nonatomic ,strong)NSArray *stepArr;
@end


@interface ZRData61Model : ZRHealthData

@property (nonatomic, strong)NSString  *uid;
@property (nonatomic, strong)NSString  *data_from;
@property (nonatomic, strong)NSString  *date;
@property (nonatomic, assign)NSInteger data_type;//16进制   0010 0001=21
@property (nonatomic, assign)NSInteger sport_type;  //10进制
@property (nonatomic, assign)NSInteger step;
@property (nonatomic, assign)float     distance;    //单位：米
@property (nonatomic, assign)float     calorie;     //单位：千卡
@property (nonatomic, assign)NSInteger state_type;
@property (nonatomic, assign)NSInteger second;      //秒
@property (nonatomic, assign)NSInteger pre_minute;  //自动识别某项运动，开始前已经运动的一段时间（单位：分钟）
@property (nonatomic, assign)NSInteger min_bpm;
@property (nonatomic, assign)NSInteger max_bpm;
@property (nonatomic, assign)NSInteger avg_bpm;
@property (nonatomic, assign)NSInteger level;
@property (nonatomic, assign)NSInteger sdnn;
@property (nonatomic, assign)NSInteger rmssd;
@property (nonatomic, assign)NSInteger pnn50;
@property (nonatomic, assign)NSInteger mean;
@property (nonatomic, assign)NSInteger fatigue;
//hrv
@property (nonatomic, assign)NSInteger sbp;
@property (nonatomic, assign)NSInteger dbp;
@property (nonatomic, assign)NSInteger bpm;

@property (nonatomic, strong)NSString  *cmd;

@end


/**
 分钟冻结GNSS数据
 */
@interface ZRData62Model : ZRHealthData

@property (nonatomic, strong)NSString  *uid;
@property (nonatomic, strong)NSString  *data_from;
@property (nonatomic, strong)NSString  *date;
@property (nonatomic, assign)NSInteger freq;
@property (nonatomic, assign)NSInteger num;//经纬度个数
@property (nonatomic, copy)NSString *jsonData;//经纬度 Json字符串

@property (nonatomic ,strong) NSArray *dataArray;//经纬度 数组
@property (nonatomic, strong)NSString  *cmd;
@end

/**
 ECG数据
 */
@interface ZRECGModel : ZRHealthData

@property (nonatomic, strong)NSString  *uid;
@property (nonatomic, strong)NSString  *data_from;
@property (nonatomic, strong)NSString  *date;
@property (nonatomic, copy)NSString  *jsonData;// Json字符串
@property (nonatomic, strong)NSString  *cmd;
@end

