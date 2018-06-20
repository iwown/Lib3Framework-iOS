//
//  ZRModel.h
//  Demo
//
//  Created by 曹凯 on 15/12/25.
//  Copyright © 2015年 ZR. All rights reserved.
//

#import "AutumnHeader.h"
#import "BLEAutumn.h"

@interface ZRModel : NSObject <NSCoding>

/*The Model default setted by SDK according protocol*/
+ (instancetype)defaultModel;
@end

@interface ZRClock : ZRModel <NSCoding>

/**
 * Index of clock .Most device valiable range is 0～3, special device valiable range is 0～7
 */
@property (nonatomic ,assign) NSUInteger clockId;

/***
 * Description: Use a Byte number identify repeat day ,recycle by a week .Detail of every byte as follows ,use b7~b1 declared :
 * b7:Valid mark, b6:Satueday, b5:Friday, b4:Thursday, b3:Wednesday, b2:Tuesday, b1:Monday, b0:Sunday
 * 1 means on ,0 indicate off .
 */
@property (nonatomic ,assign) NSUInteger weekRepeat;
@property (nonatomic ,assign) NSUInteger clockHour;
@property (nonatomic ,assign) NSUInteger clockMinute;

/***
 * RingSetting
 */
@property (nonatomic ,assign) NSUInteger clockRingSetting;

@property (nonatomic ,assign) NSUInteger clockTipsLenth;
@property (nonatomic ,copy) NSString *clockTips;

@end

@interface ZRSedentary : ZRModel <NSCoding,NSCopying>

/**
 * the state of reminder switch, default is NO ,means off.
 */
@property (nonatomic ,assign) BOOL switchStatus;

/*
 eg： @｛sedentaryId：0，startHour：8:00，endHour：12:00｝
 */
@property (nonatomic ,assign) NSUInteger sedentaryId;

/**
 * the repeats of sedentary ,to know more details to see @code weekRepeat methods。
 */
@property (nonatomic ,assign) NSUInteger weekRepeat ;

/**
 * the startTime of sedentary ,unit is hour .
 */
@property (nonatomic ,assign) NSUInteger startHour;

/**
 * the endTime of sedentary ,unit is hour .
 */
@property (nonatomic ,assign) NSUInteger endHour;

/**
 * the monitor duration ,unit is minute . your may demanded set a num is multiple of 5. 
 * default duration is 60 minutes and threshold is 50 steps if you set both zero.
 * Special device support
 */
@property (nonatomic ,assign) NSUInteger sedentaryDuration;
@property (nonatomic ,assign) NSUInteger sedentaryThreshold;

/**
 *  Switch for ”No break during lunch break”
 */
@property (nonatomic ,assign) BOOL noDisturbing;


@end

@interface ZRPersonal : ZRModel <NSCoding>

/**
 * height of personal setting , unit is cm .default is 170.
 */
@property (nonatomic ,assign) NSUInteger height;

/**
 * weight of personal setting , unit is kg .default is 170.
 */
@property (nonatomic ,assign) NSUInteger weight;

/**
 * gender of personal setting ,0 represent male ,1 represent female .default is 0 .
 */
@property (nonatomic ,assign) NSUInteger gender;

/**
 * age of personal setting .default is 20.
 */
@property (nonatomic ,assign) NSUInteger age;

@property (nonatomic ,assign)NSUInteger stepOnceDay;
/**
 * 步行步幅校正 范围 【50，200】
 */
@property (nonatomic ,assign) NSUInteger distanceSize;

/**
 * 跑行步幅校正 范围 【50，200】
 */
@property (nonatomic ,assign) NSUInteger distanceSizeRun;
@end

@interface ZRTargetOnceDay : ZRModel

/**
 * The number of single day goal in step.
 */
@property (nonatomic ,assign) NSUInteger stepOnceDay;

/**
 * The number of single day goal in calorie.
 */
@property (nonatomic ,assign) NSUInteger calorieOnceDay;

@end


@interface SportModel : ZRModel <NSCoding>
@property (nonatomic,assign,readonly)NSString *sportName;
@property (nonatomic,strong,readonly)NSString *unit;
@property (nonatomic,assign)sd_sportType type;
@property (nonatomic,assign)NSInteger targetNum;
@end

@interface ZRSportLists : ZRModel <NSCoding>

/*
 * 0-6 monday-sunday
 */
@property (nonatomic,assign)NSInteger day;
/**
 *  Add the first movement is set to walk (bracelet will be the default as a walk)
 */
@property (nonatomic,strong)NSMutableArray <SportModel *>*sportArr;
- (void)addSportModel:(SportModel *)sm;
@end


@interface ZRSchedule : NSObject
typedef enum {
    BLE_ScheduleInvalid = 0,
    BLE_ScheduleValid = 1,
}BLEScheduleState;
@property(nonatomic,copy)NSString *title;
@property(nonatomic,copy)NSString *subTitle;

@property(nonatomic,assign)NSInteger year;
@property(nonatomic,assign)NSInteger month;
@property(nonatomic,assign)NSInteger day;

@property(nonatomic,assign)NSInteger hour;
@property(nonatomic,assign)NSInteger minute;

/**
 高3位是铃声 0~7对应不同铃声
 低5位是反复次数 默认0x01
 High 3 is the ringtone 0 ~ 7 corresponds to different ringtones
 Low 5 is the number of iterations default 0x01
 */
@property(nonatomic,assign)NSInteger ringSetting;

@property(nonatomic,assign)BLEScheduleState state;

@property(nonatomic,strong)NSDate   *invalidDate;

- (instancetype)initWithTitile:(NSString *)title subTitle:(NSString *)subTitle year:(NSInteger)year month:(NSInteger)month day:(NSInteger)day hour:(NSInteger)hour minute:(NSInteger)minute;
@end

typedef NS_ENUM (NSInteger,ShakeType){
    ShakeTypeClock = 0,
    ShakeTypeCall = 1,
    ShakeTypeMsg = 2,
    ShakeTypeSedentary = 3,
    ShakeTypeCharging = 4,
    ShakeTypeSchedule = 5,
    ShakeTypeCommon = 6,
    ShakeTypeHRWarning = 7
};

typedef NS_ENUM (NSInteger,ShakeWay){
    
    ShakeWayStaccato = 4 ,  //断奏
    ShakeWayWave         ,  //波浪
    
    ShakeWayPitpat   = 7 ,  //心跳
    ShakeWayRadiate      ,  //放射
    
    ShakeWayLight    = 11,  //灯塔
    ShakeWaySymphony     ,  //交响乐
    
    ShakeWayRapid    = 15,  //快速
};

@interface ZRMotor : ZRModel<NSCoding>
+ (NSArray <ZRMotor *> *)defaultMotors;
/**! Used for device bleProtocol_colorful */
+ (NSArray <ZRMotor *> *)zgDefaultMotors;

@property (nonatomic,assign)ShakeType   type;
@property (nonatomic,assign)ShakeWay   modeIndex;
@property (nonatomic,assign)NSInteger   shakeCount;

+ (NSString *)chineseNameForShakeWay:(ShakeWay)modelIndex;
/**! Used for bleProtocol_colorful device, set in ZRSchedule & ZRClock*/
+ (NSInteger)getRingSettingWithShakeWay:(ShakeWay)way andCount:(NSInteger)count;

+ (ShakeWay)shakeWayFromRing:(NSInteger)ringSetting;
+ (NSInteger)shakeCountFromRing:(NSInteger)ringSetting;
+ (NSInteger)shakeIndexFrom:(ShakeWay)sWay;
+ (NSArray *)modelArray;
@end

@interface ZRCOption : ZRModel
/***
 * 0-close ,1-open ,
 * default -1 type not setting.
 */
@property (nonatomic, assign) NSInteger findPhoneSwitch;

/**
 * 0-1-2 ; low-normal-high
 * default -1 type not setting
 */
@property (nonatomic, assign) NSInteger wristDelicacy;

/**
 * 0-1 ; NO-YES
 * default -1 type not setting
 */
@property (nonatomic, assign) NSInteger readSleepData;
@end

typedef NS_ENUM (NSInteger,DNDType){
    DNDTypeNull = 0 ,         // mean closed dndMode
    DNDTypeOnlyNotSave ,
    DNDTypeNotSaveAndShow ,
};
@interface ZRDNDModel : ZRModel

/**
 When dndtype == DNDTypeNull, mean this smartBand has not set dnd model; you can also set dndType = 0 to close dnd model
 */
@property(nonatomic,assign)NSInteger dndType;

/**
 Hour取值范围：0~23
 Minute取值范围：0~59
 */
@property(nonatomic,assign)NSInteger startHour;
@property(nonatomic,assign)NSInteger startMinute;
@property(nonatomic,assign)NSInteger endHour;
@property(nonatomic,assign)NSInteger endMinute;

@end


typedef NS_ENUM(NSInteger,WeatherType) {
    WeatherFine = 0,            //晴
    WeatherCloudy = 1,          //多云
    WeatherOvercast = 2,        //阴天
    WeatherLightRain = 3,       //小雨
    WeatherModerateRain = 4,    //中雨
    WeatherHeavyRain = 5,       //大雨
    WeatherShower = 6,          //阵雨
    WeatherSnow = 7,            //雪
    WeatherHaze = 8,            //雾霾
    WeatherSandstorm = 9,       //沙尘暴
    WeatherSunCloud = 10,       //多云转晴
    WeatherThunderStorm = 11,   //雷雨
    WeatherNotContain = 0xff,
};

typedef NS_ENUM(NSInteger,TempUnit) {
    Centigrade = 0, //摄氏温度
    Fahrenheit = 1, //华氏温度
};

@interface ZRWeather : ZRModel <NSCopying>

@property (nonatomic,assign)NSInteger temp;//温度值
@property (nonatomic,assign)TempUnit unit;
@property (nonatomic,assign)WeatherType  type;
@property (nonatomic,assign)NSInteger pm;

- (NSInteger)celsiusDegree;
- (NSInteger)fahrenheitDegree;

@end


@interface ZRDayWeather : ZRModel 

@property (nonatomic,assign)NSInteger tempMax;
@property (nonatomic,assign)NSInteger tempMin;
@property (nonatomic,assign)WeatherType type;

@end


@interface ZR24Weather : ZRModel

@property (nonatomic,assign)NSInteger year;
@property (nonatomic,assign)NSInteger month;
@property (nonatomic,assign)NSInteger day;
@property (nonatomic,assign)NSInteger hour;

@property (nonatomic,assign)TempUnit unit;
/**! Groups numbers 24, means 24 hours weather data ,You must sort the data by date*/
@property (nonatomic,strong)NSArray <ZRWeather *>*weather24Arrs;

@property (nonatomic,strong)NSArray <ZRDayWeather *>*weather7Arrs;

@end

@interface ZRAction : ZRModel

/**! Function enable 0 means off, 1 means on*/
@property (nonatomic ,assign) NSInteger switchCtrl;

/**
 The following parameters are valid only for switchCtrl == 1
 以下参数仅 switchCtrl == 1 时有效
 */
/**! Sensitivity to identify actions (in units of 100, default: 18, ie 1800)*/
@property (nonatomic ,assign) NSInteger sensitivity;
/**! Trigger interval (unit: 0.5 seconds, default: 2, that is, 1s)*/
@property (nonatomic ,assign) NSInteger interval;
/**! Turn on vibration 1: turn on 0: turn off (default: 0)<##>*/
@property (nonatomic ,assign) NSInteger motor;
@end

@interface ZRContacts : ZRModel

/**
 * contactId (hash_id): The unique index of the phone book, it is recommended to use the year, month, day, hour, minute and second integer
 */
@property (nonatomic ,assign) NSInteger cId;
/**! 18 bytes, up to 6 characters, the excess will be cut off<##>*/
@property (nonatomic ,copy) NSString *name;
/**! Phone numbers, numbers only, no more than 20 digits*/
@property (nonatomic ,copy) NSString *number;
@end


@interface ZRRoll : ZRModel
/**! rollId (hash_id): Please use an integer, the size should not exceed 0xFFFFFFFF*/
@property (nonatomic ,assign) NSInteger rId;

@property (nonatomic ,copy) NSString *rollName;

@end

@interface ZRGPSPoint : ZRModel
@property (nonatomic ,assign) NSInteger timeZone; //时区
@property (nonatomic ,assign) float latitude; //纬度
@property (nonatomic ,assign) float longitude; //经度
@property (nonatomic ,assign) NSInteger altitude; //海拔

@end
/**! Exercise Heart Rate Warning*/
@interface ZREHRWP : ZRModel <NSCoding,NSCopying>
/** Switch of this feature ,default is YES*/
@property (nonatomic ,assign) BOOL enable;
/** Alarm upper limit of heart rate, higher than this value to trigger alarm, the range of 50 ~ 200, the default 160*/
@property (nonatomic ,assign) NSInteger threshold_high;
/** Alarm lower limit of heart rate, lower than the value of the trigger alarm, the range of 40 ~ 190, the default 50*/
@property (nonatomic ,assign) NSInteger threshold_low;
/** Alarm detection time in seconds, the default 30*/
@property (nonatomic ,assign) NSInteger timerOut;
/** Alarm trigger interval, unit minutes, default 2*/
@property (nonatomic ,assign) NSInteger interval;
@end

@interface ZRGnssParam : ZRModel

/*时区*/
@property (nonatomic ,assign) NSInteger timeZone;
/*经度*/
@property (nonatomic ,assign) float latitude;
/*纬度*/
@property (nonatomic ,assign) float longitude;
/*海拔*/
@property (nonatomic ,assign) NSInteger altitude;

@end



typedef NS_ENUM (NSInteger,ZRRollMsgType){
    ZRRollMsgForQQ          = (1<<15),
    ZRRollMsgForWechat      = (1<<14),
    ZRRollMsgForSina        = (1<<13),
    ZRRollMsgForFacebook    = (1<<12),
    ZRRollMsgForLine        = (1<<11),
    ZRRollMsgForInstagram   = (1<<10),
    ZRRollMsgForKakaoTalk   = (1<<9),
    ZRRollMsgForGmail       = (1<<8),
    ZRRollMsgForTwitter     = (1<<7),
    ZRRollMsgForLinkin      = (1<<6),
    ZRRollMsgForWhatsapp    = (1<<5),
    ZRRollMsgForSkype       = (1<<4),
    ZRRollMsgForMobileSMS   = (1<<3),
    ZRRollMsgForMoblieEmail = (1<<2),
};


@interface ZRMesgPush : ZRModel

/**
 * Call reminder switch, turn off the call reminder switch without bracelet does not receive calls reminder, the default is YES.
 */
@property (nonatomic, assign) BOOL comingCallEnable;

/**
 * Valid only when @ \ comingCallEnable is YES, alerting at a set interval. The value range is 0-23, which means every whole hour.
 * 仅在 @\comingCallEnable 为YES的时候有效，在设置的时间间隔内，来电提醒。取值范围在0-23，表示每个整点。
 
 */
@property (nonatomic, assign) NSInteger comingCallStart;
@property (nonatomic, assign) NSInteger comingCallEnd;

/**
 * Message reminder switch, do not receive the message after closing, the default is YES.
 */
@property (nonatomic, assign) BOOL messageEnable;

/**
 * Valid only if @ \ messageEnable is YES, a message reminded at the set time interval. The value range is 0-23, which means every whole hour.
 * 仅在 @\messageEnable 为YES的时候有效，在设置的时间间隔内，消息提醒。取值范围在0-23，表示每个整点。
 */
@property (nonatomic, assign) NSInteger messageStart;
@property (nonatomic, assign) NSInteger messageEnd;

/**
 * Valid only if @ \ messageEnable is YES, and at the set time interval. List of supported blacklist apps, ZRRollMsgType cannot be repeated;
 * 仅在 @\messageEnable 为YES, 并且在设置的时间间隔内有效。支持的黑名单的APP列表，ZRRollMsgType不能重复;
 */
@property (nonatomic, strong) NSArray  *rollMsgList;
@property (nonatomic, strong) NSString *rollMsgListJsonString;


@end


@interface ZRStartSetting : ZRModel

/**
 * Set the offset of the current GPS time zone, for example, Beijing is +8.
 * 设置 GPS 当前时区的偏移, 比如说北京是+8。
 */
@property (nonatomic, assign) NSInteger utc_offset;

/**
 * Greeting display content, max 10 bytes;
 * 问候语的显示内容, 开机显示问候语最大10个byte。
 */
@property (nonatomic, strong) NSString *username_data;

/**
 * 13BYTE 备用
 */
@property (nonatomic, strong) NSString *blank;

- (NSString *)getSetCmdStr;

@end


