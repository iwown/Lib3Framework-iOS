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
    RecortDate storeDate;
}DateDataInfo;

typedef struct {
    uint8_t dataType;
    uint8_t totaldays;
    DateDataInfo ddInfos[7];
}TDateStoreInfo;

typedef enum {
    ZRDITypeNormalData = 0x00, //Normal data in Colorful Screen Band.
    ZRDITypeGPSData = 0x8c, //GPS data in Colorful Screen Band.
    ZRDITypeHbridHealth = 0x28, //0x28,0x29,0x51,0x53. Hbrid data for classical band.
    ZRDITypeNormalHealth = 0x61, //Normal health data for Watch
    ZRDITypeGNSSData = 0x62, // GNSS data in Watch
    ZRDITypeECGHealth = 0x64,// ECG data in Watch
    ZRDITypeEarPhoneData = 0x68
} ZRDIType;

@interface DDInfo : NSObject

+ (instancetype)objectFrom:(DateDataInfo)ddInfo;
@property (nonatomic ,strong) NSDate *date;
@property (nonatomic ,assign) NSInteger seqStart;
@property (nonatomic ,assign) NSInteger seqEnd;
@property (nonatomic ,assign) NSInteger gpsStoreBlock;
@property (nonatomic ,assign) NSInteger gpsStoreSector;

@end

@class ZRHealthData;
@interface ZRDataInfo : NSObject

@property (nonatomic ,strong) NSArray <DDInfo *> *ddInfos;
@property (nonatomic ,assign) NSUInteger dataType;

+ (instancetype)zrDataInfoFromDateStoreInfo:(DateStoreInfo)dsInfo;
+ (instancetype)zrDataInfoFromTDateStoreInfo:(TDateStoreInfo)tdsInfo;
+ (instancetype)zrDataInfoFromZRHealthData:(NSDictionary *)dataDict;
+ (instancetype)zrDataInfoFromGPSDataInfoDict:(NSDictionary *)dataDict;

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
    HDTypePPG = 0x65,  //PPG数据
    HDTypeRRI = 0x66,  //房颤数据
    HDTypeEarPhoneHealth = 0x68, //耳机运动数据
    
    HDTypeZGStep = 0x8901,
    HDTypeZGExercise = 0x8B,
    HDTypeZGGPS = 0x8C,
    
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
//用户id，SDK内不赋值，可忽略
@property (nonatomic, strong)NSString  *uid;
//数据来源，设备名
@property (nonatomic, strong)NSString  *data_from;
//请忽略，查看recordDate
@property (nonatomic, strong)NSString  *date;
//16进制   0010 0001=21
@property (nonatomic, assign)NSInteger data_type;
//10进制 运动类型 sd_sportType
@property (nonatomic, assign)NSInteger sport_type;
@property (nonatomic, assign)NSInteger step;
@property (nonatomic, assign)float     distance;    //单位：米
@property (nonatomic, assign)float     calorie;     //单位：千卡
//10进制，运动状态，1-开始，2-结束，3-暂停，4-运动持续中
@property (nonatomic, assign)NSInteger state_type;
@property (nonatomic, assign)NSInteger second;      //秒
//自动识别某项运动，开始前已经运动的一段时间（单位：分钟），大于0表示运动为自动识别
@property (nonatomic, assign)NSInteger pre_minute;
//心率
@property (nonatomic, assign)NSInteger min_bpm;
@property (nonatomic, assign)NSInteger max_bpm;
@property (nonatomic, assign)NSInteger avg_bpm;
//hrv相关参数
@property (nonatomic, assign)NSInteger level;
@property (nonatomic, assign)NSInteger sdnn;
@property (nonatomic, assign)NSInteger rmssd;
@property (nonatomic, assign)NSInteger pnn50;
@property (nonatomic, assign)NSInteger mean;
//疲劳度
@property (nonatomic, assign)NSInteger fatigue;
//血压，sbp-收缩压 ；dbp-舒张压
@property (nonatomic, assign)NSInteger sbp;
@property (nonatomic, assign)NSInteger dbp;
@property (nonatomic, assign)NSInteger bpm;
//睡眠数据，用于计算睡眠用的，需写入.json文件中
@property (nonatomic, strong) id sleepCmd;

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


/**! PPG*/
@interface ZRPPGModel : ZRHealthData

@property (nonatomic, strong) NSString  *uid;
@property (nonatomic, strong) NSString  *data_from;
@property (nonatomic ,strong) NSArray *dataArray;

@end


/**! 房颤*/
@interface ZRRRIModel : ZRHealthData

@property (nonatomic, strong) NSString  *uid;
@property (nonatomic, strong) NSString  *data_from;
@property (nonatomic ,strong) NSArray *dataArray;

@end


@interface ZRData68Model : ZRHealthData

@property (nonatomic, strong)NSString  *uid;
@property (nonatomic, strong)NSString  *data_from;
@property (nonatomic, strong)NSString  *date;
@property (nonatomic, assign)NSInteger data_type;
@property (nonatomic, assign)NSInteger sport_type;
@property (nonatomic, assign)NSInteger state_type;
@property (nonatomic, assign)NSInteger step;
@property (nonatomic, assign)float distance;
@property (nonatomic, assign)float calorie;
@property (nonatomic, assign)NSInteger rateofstride_max;
@property (nonatomic, assign)NSInteger rateofstride_min;
@property (nonatomic, assign)NSInteger rateofstride_avg;
@property (nonatomic, assign)NSInteger flight_max;
@property (nonatomic, assign)NSInteger flight_min;
@property (nonatomic, assign)NSInteger flight_avg;
@property (nonatomic, assign)NSInteger touchdown_max;
@property (nonatomic, assign)NSInteger touchdown_min;
@property (nonatomic, assign)NSInteger touchdown_avg;
@property (nonatomic, assign)NSInteger touchdownpower_max;
@property (nonatomic, assign)NSInteger touchdownpower_min;
@property (nonatomic, assign)NSInteger touchdownpower_avg;
@property (nonatomic, assign)NSInteger touchdownpower_balance;
@property (nonatomic, assign)NSInteger touchdownpower_stop;
@property (nonatomic, assign)NSInteger min_hr;
@property (nonatomic, assign)NSInteger max_hr;
@property (nonatomic, assign)NSInteger avg_hr;

@property (nonatomic, strong)NSString  *cmd;

@end

@interface ZRExerciseDataModel : ZRHealthData

@property (nonatomic, assign)NSInteger exerciseSteps;      //训练的步数，实时更新
@property (nonatomic, assign)NSInteger exerciseCalories;   //训练的卡路里；一分钟更新一次；
@property (nonatomic, assign)NSInteger exerciseDistance;   //训练的距离；一分钟更新一次；（单位：米）
@property (nonatomic, assign)NSInteger exerciseMinutes;    //训练的分钟长度；一分钟更新一次；
@property (nonatomic, assign)NSInteger exerciseLkHeart;    //训练的及时心率， 实时更新
@property (nonatomic, assign)sd_sportType exerciseMode;    //当前训练的模式

@end

@interface ZRGPSModel : ZRHealthData

@property (strong ,nonatomic)NSArray *detailData;

@end

@interface ZRBloodPressureModel : ZRHealthData

@property (nonatomic, assign)NSInteger sbp;      //训练的步数，实时更新
@property (nonatomic, assign)NSInteger dbp;   //训练的卡路里；一分钟更新一次；

@end



