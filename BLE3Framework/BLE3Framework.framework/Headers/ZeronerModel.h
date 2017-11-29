//
//  ZeronerModel.h
//  Demo
//
//  Created by 曹凯 on 15/12/25.
//  Copyright © 2015年 Zeroner. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "ZeronerBleHeader.h"
typedef enum {
    //    Model_Clock = 1,          //闹钟
    Model_Sedentary = 2,      //久坐
    Model_HWOption = 3,       //硬件功能
    Model_MESPush = 4,        //消息推送
    //    Model_Schedule = 5,  //日程
    Model_MotoControl = 6,  //震动
    Model_EXHRWParam = 7,    //运动心率参数
}ModelType;

/*eg. @{kDEFAULTS_BACKGROUD_COLOR:@YES}*/
static NSString *const kDEFAULTS_BACKGROUD_COLOR = @"kDEFAULTS_BACKGROUD_COLOR";
/*eg. @{kDEFAULTS_BACKGROUD_COLOR:[ZeronerEHRWP new]}*/
static NSString *const kDEFAULTS_EXHRW_RANGE = @"kDEFAULTS_EXHRW_RANGE";
/*eg. @{kDEFAULTS_EXHR_MOTOR:[ZeronerMotor new]}*/
static NSString* const kDEFAULTS_EXHR_MOTOR=@"kDEFAULTS_EXHR_MOTOR";

@interface ZeronerModel : NSObject <NSCoding>

/**
 * keyModel represent a special device. your are recommand to set a key like @"Bracelet-9999"
 */
+ (void)setCurrentKeyModel:(NSString *)keyModel;
+ (id)getModel:(ModelType)type;
+(void)clearCurrentKeyModel;
+ (void)saveModel:(id)model;

/**
 Call setCurrentKeyModel: method before initBLEModel, your must special the
 @return YES mean initial successfully.
 */
+ (BOOL)initBLEModel;
/** 自定义初始化 Custom initial
 *  @param defaults @see kDEFAULTS_BACKGROUD_COLOR
 */
+ (BOOL)initBLEModelWithDefaults:(NSDictionary *)defaults;

@end

@interface ZeronerClock : ZeronerModel <NSCoding>
+ (instancetype)defaultClock;

/**
 * Switch of clock ,defalult is NO.
 * 开关状态，闹钟的开关，默认是关。
 */
@property (nonatomic ,assign) BOOL switchStatus;

/**
 * This attribute denote that is this clock viable ,default is NO.
 * 表示闹钟是否可见，删除的闹钟或者该编号闹钟没有被添加的VISABLE为0
 */
@property (nonatomic ,assign) BOOL viable;

/**
 * Index of clock ,valiable range is 0～7.
 * 闹钟索引，支持8个闹钟，索引有效范围0～7
 */
@property (nonatomic ,assign) NSUInteger clockId;
@property (nonatomic ,readonly ,assign) NSUInteger clockType;

/***
 * Description: Use a Byte number identify repeat day ,recycle by a week .Detail of every byte as follows ,use b7~b1 declared :
 * b7:Repeat mark ,b6:Monday ,b5:Tuesday ,b4:Wednesday ,b3:Thursday ,b2:Friday ,b1:Satueday ,b0:Sunday
 * 1 means on ,0 indicate off .
 */
@property (nonatomic ,assign) NSUInteger weekRepeat;
@property (nonatomic ,assign) NSUInteger clockHour;
@property (nonatomic ,assign) NSUInteger clockMinute;
@property (nonatomic ,assign) NSUInteger clockTipsLenth;
@property (nonatomic ,copy) NSString *clockTips;

@end

@interface ZeronerSedentary : ZeronerModel <NSCoding,NSCopying>
+ (instancetype)defaultSedentary;

/**
 * the state of reminder switch, default is NO ,means off.
 * 久坐提醒的开关状态，默认关闭。
 */
@property (nonatomic ,assign) BOOL switchStatus;

/*
 *  可以设置多端，但时间不要交叉，id的取值范围是0-2
 eg： @｛sedentaryId：0，startHour：8:00，endHour：12:00｝，@｛sedentaryId：1，startHour：14:00，endHour：18:00｝is right
 but @｛sedentaryId：0，startHour：8:00，endHour：14:00｝，@｛sedentaryId：1，startHour：12:00，endHour：18:00｝is wrong
 */
@property (nonatomic ,assign) NSUInteger sedentaryId;

/**
 * the repeats of sedentary ,to know more details to see @code weekRepeat methods。
 * 久坐的重复设置 详情请参考 @code weekRepeat 函数。
 */
@property (nonatomic ,assign) NSUInteger weekRepeat ;

/**
 * the startTime of sedentary ,unit is hour .
 * 判断久坐的开始时间，整数，单位是小时
 */
@property (nonatomic ,assign) NSUInteger startHour;

/**
 * the endTime of sedentary ,unit is hour .
 * 判断久坐的结束时间，整数，单位是小时
 */
@property (nonatomic ,assign) NSUInteger endHour;

/**
 * the monitor duration ,unit is minute . your may demanded set a num is multiple of 5.
 * 判断久坐的时间长度，整数，单位是分钟
 * default duration is 60 minutes and threshold is 50 steps if you set both zero.
 */
@property (nonatomic ,assign) NSUInteger sedentaryDuration;
@property (nonatomic ,assign) NSUInteger sedentaryThreshold;

/**
 *  no disturbing switch
 *  免打扰开关
 */
@property (nonatomic ,assign) BOOL  noDisturbing;


@end

typedef enum{
    UnitTypeInternational = 0, // International units ,like km、meter、kg .国际制单位，如，千米 、米 、千克。
    UnitTypeEnglish            // Imperial units ,like feet、inch、pound .国际制单位，如，英尺 、英寸 、磅。
}UnitType;

typedef enum{
    TimeFlag24Hour = 0,
    TimeFlag12Hour
}TimeFlag;

typedef enum{
    braceletLanguageDefault = 0, //default is english equal @code braceletLanguageEnglish
    braceletLanguageEnglish  DEPRECATED_ATTRIBUTE ,// some smartband did not support it ,use braceletLanguageDefault if you don't want set in simple chinese.
    braceletLanguageSimpleChinese = 1,
    braceletLanguageItalian = 2,
    braceletLanguageJapanese = 3,
    braceletLanguageFrench = 4,
    braceletLanguageGerman = 5,
    braceletLanguagePortugal = 6,
    braceletLanguageSpanish = 7,
    braceletLanguageRussian = 8,
    braceletLanguageKorean = 9,
    braceletLanguageArabic = 10,
    braceletLanguageVietnamese = 11,
    braceletLanguageSimpleMarkings = 0xff, //This setting means no char ,all information replaced by figure. show simple icon only.
}braceletLanguage;

@interface ZeronerHWOption : ZeronerModel <NSCoding>
+ (instancetype)defaultHWOption;
/**
 * switch of led light ,default is NO ,brcelet i7 is not supported .
 * LED灯开关，默认为NO，i7手环不支持。
 */
@property (nonatomic ,assign) BOOL ledSwitch;

//惯用手 默认左手
@property (nonatomic,assign)BOOL  leftHand;

/**
 * switch of wrist ,default is YES.
 * 翻腕开关,默认为YES。
 */
@property (nonatomic ,assign) BOOL wristSwitch;


/**
 * switch of unitType changed ,default is UnitTypeInternational.
 * 公英制单位切换开关 ，默认是国际单位制。
 */
@property (nonatomic ,assign) UnitType unitType;

/**
 * switch of timeFlag changed ,default is TimeFlag24Hour.
 * 时间制式切换开关 ,默认是24小时制。
 */
@property (nonatomic ,assign) TimeFlag timeFlag;

/**
 * switch of autoSleep  ,default is YES ,that means bracelet monitor sleep state automatically .
 * 自动睡眠开关, 默认为YES, 也就是手环自动识别睡眠状态。
 */
@property (nonatomic ,assign) BOOL autoSleep;

@property (nonatomic ,assign) BOOL advertisementSwitch;
@property (nonatomic ,assign) NSUInteger backlightStart;
@property (nonatomic ,assign) NSUInteger backlightEnd;

/**
 *  backGroundColor for device, default is NO.  YES is white，NO is black
 *  屏幕背景颜色，默认为NO. YES为白色，NO为黑色.
 */
@property (nonatomic, assign) BOOL backColor;
/**
 * switch of what's language bracelet is used ,default is followed by iOS or use braceletLanguageDefault ,to know more about language that bracelet supported. @see braceletLanguage .
 * 手环使用的语言设置开关，默认设置受系统语言影响，未作适配的系统语言情况下为braceletLanguageDefault。
 */
@property (nonatomic ,assign) braceletLanguage language;

/**
 *  switch of disConnectTip, default is NO ,default is close the tips 0f disConnect.
 *  断连提醒，默认为NO,也就是关闭提醒。
 */
@property (nonatomic, assign) BOOL disConnectTip;
/**
 *  type formatter of date on smartband‘s screen ,0 means formatter is MM/dd ,type 1 means dd/MM .Default is 0
 *  手环显示的日期格式，0表示 月月／日日 ，1表示 日日／月月.默认是0
 */
@property (nonatomic, assign) NSInteger dateFormatter;

/**
 *  Valid only @\wristSwitch is YES, duration the setting time, wrist to light screen is used. set wristBlightStart = wristBlightEnd = 0 mean all time is used . values of these param must in 0-23, type integral point.
 * 仅在 @\wristSwitch 为YES的时候有效，在设置的时间间隔内，翻腕点亮屏幕功能可用。wristBlightStart和wristBlightEnd都设置为0时表示24小时有效。取值范围在0-23，表示每个整点。
 */
@property (nonatomic, assign) NSInteger wristBlightStart;
@property (nonatomic, assign) NSInteger wristBlightEnd;

/**
 * switch of monitor heart rate automatilly ,turn off smart band would not motinor heart rate unless in sport time. default is YES .
 * 自动监测心率开关 ,关闭自动心率后非运动状态时不检测心率，默认为YES,。
 */
@property (nonatomic, assign) BOOL autoHeartRate;


/**
 * Switch used for control search phone feature
 * 找手机功能的开关 ,自动运动识别 （同一个字段，不同协议固件支持内容不同，findPhoneSwitch仅少量固件支持）
 */
@property (nonatomic ,assign) BOOL autoSport;
@property (nonatomic, assign) BOOL findPhoneSwitch;


@end



@interface ZeronerPersonal : ZeronerModel <NSCoding>

+ (instancetype)defaultPersonalModel;
/**
 * height of personal setting , unit is cm .default is 170.
 * 用户身高设置, 单位是厘米。 默认设置为170。
 */
@property (nonatomic ,assign) NSUInteger height;

/**
 * weight of personal setting , unit is kg .default is 170.
 * 用户体重设置, 单位是公斤。 默认设置为60。
 */
@property (nonatomic ,assign) NSUInteger weight;

/**
 * gender of personal setting ,0 represent male ,1 represent female .default is 0 .
 * 用户性别设置, 0表示男性，1表示女性。 默认设置为0。
 */
@property (nonatomic ,assign) NSUInteger gender;

/**
 * age of personal setting .default is 20.
 * 用户年龄设置。 默认设置为20。
 */
@property (nonatomic ,assign) NSUInteger age;

@property (nonatomic ,assign) NSUInteger target;
@end

@interface SportModel : ZeronerModel <NSCoding>
@property (nonatomic,assign)NSString *sportName;
@property (nonatomic,strong,readonly)NSString *unit;
@property (nonatomic,assign)sd_sportType type;
@property (nonatomic,assign)NSInteger targetNum;
@end

@interface ZeronerSportTarget : ZeronerModel <NSCoding>
+ (instancetype)defaultSportTargetModel;

/*
 * 0-6 monday-sunday
 */
@property (nonatomic,assign)NSInteger day;
/**
 *  添加的运动 请第一项设为步行（应该手环会默认作为步行处理）
 */
@property (nonatomic,strong)NSMutableArray *sportArr;
- (void)addSportModel:(SportModel *)sm;
@end


@interface ZeronerSchedule : NSObject
typedef enum {
    ScheduleUnSetting = 0,      //日程未写入
    ScheduleSetting = 1,        //日程已写入
    ScheduleInvalid = 2,        //日程无效（关闭的的日程）
}ScheduleState;
@property(nonatomic,copy)NSString *title;
@property(nonatomic,copy)NSString *subTitle;

@property(nonatomic,assign)NSInteger year;
@property(nonatomic,assign)NSInteger month;
@property(nonatomic,assign)NSInteger day;

@property(nonatomic,assign)NSInteger hour;
@property(nonatomic,assign)NSInteger minute;

@property(nonatomic,assign)NSInteger state;

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

@interface ZeronerMotor : ZeronerModel<NSCoding>
+ (NSArray <ZeronerMotor *> *)defaultMotors ;
@property (nonatomic,assign)ShakeType   type;
@property (nonatomic,assign)ShakeWay   modeIndex;
@property (nonatomic,assign)NSInteger   shakeCount;

+ (NSString *)nameForShakeWay:(ShakeWay)modelIndex;

@end

@interface ZeronerCOption : ZeronerModel
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

@end

typedef NS_ENUM (NSInteger,DNDType){
    DNDTypeNull = 0 , // mean closed dndMode
    DNDTypeNormal ,
    DNDTypeSleep ,   //  firmware must be supportted if used
    DNDTypeAllDay,   //  firmware must be supportted if used
};
@interface ZeronerDNDModel : ZeronerModel

@property(nonatomic,assign)NSInteger dndType;  //when dndtype == DNDTypeNull, mean this smartBand has not set dnd model; you can also set dndType = 0 to close dnd model
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
    WeatherSandstorm = 9,        //沙尘暴
    WeatherNotContain = 10,
};

typedef NS_ENUM(NSInteger,TempUnit) {
    Centigrade = 0, //摄氏温度
    Fahrenheit = 1, //华氏温度
};

@interface ZeronerWeather : ZeronerModel

@property (nonatomic,assign)NSInteger temp;//温度值
@property (nonatomic,assign)TempUnit unit;
@property (nonatomic,assign)WeatherType  type;
@property (nonatomic,assign)NSInteger pm;

@end

typedef enum {
    DFUPlatformTi = 1,
    DFUPlatformNortic = 2,
    DFUPlatformDialog = 3,
    DFUPlatformMtk = 4,
} DFUPlatform;
@interface ZeronerDeviceInfo : ZeronerModel

@property (nonatomic,strong)    NSString *protocolVer;   // 协议版本
@property (nonatomic,strong)    NSString *model;        // model string
@property (nonatomic,strong)    NSString *version;      // version string
@property (nonatomic,readonly)  NSUInteger versionValue;// integer value of version
@property (nonatomic,readonly)  NSUInteger oadMode;     // over air update mode
@property (nonatomic,readonly)  NSUInteger batLevel;    // battery level
@property (nonatomic,strong)    NSString *seriesNo;      // series No. ble Addr for display
@property (nonatomic,strong)    NSString *bleAddr;      // series No. ble Addr for upload
@property (nonatomic,readonly)  NSUInteger hwVersion;  // integer value of hardware version

@property (nonatomic,strong)  NSString *hrVersion;    //心率版本号
@property (nonatomic,assign)  NSInteger hrVersionValue; //心率升级的版本号
@property (nonatomic,strong)  NSString *fontSupport;  //0 null ,1 e&&c ,2 128国
@property (nonatomic,assign)  NSUInteger protocalMap; //protocol map

+ (instancetype)defaultDeviceInfo;
- (void)updateDeviceInfo:(NSString *)deviceInfo;
- (void)updateBattery:(NSString *)batteryLevel;
- (void)updateHeartRateParam:(NSString *)body;

- (BOOL)isDialogDFU;
- (DFUPlatform)platformForDfu;
@end

@interface ZeronerAction : ZeronerModel

@property (nonatomic ,assign) NSInteger switchCtrl; //功能使能  0表示关闭，1表示开启

/**
 以下参数仅 switchCtrl == 1 时有效
 */
@property (nonatomic ,assign) NSInteger sensitivity; //识别动作的敏感度（单位为100，默认：18，即1800）
@property (nonatomic ,assign) NSInteger interval; //触发间隔（单位：0.5秒，默认：2，即1s）
@property (nonatomic ,assign) NSInteger motor; //开启振动 1：开启 0：关闭（默认：0）
@end

@interface ZeronerContacts : ZeronerModel

@property (nonatomic ,assign) NSInteger cId; //contactId(hash_id) 电话本唯一索引，建议用年月日时分秒的整数
@property (nonatomic ,copy) NSString *name; //18个字节，最长6个汉字，超出部分将被截断
@property (nonatomic ,copy) NSString *number; //电话号码，仅支持数字,不超过20位
@end

@interface ZeronerRoll : ZeronerModel
@property (nonatomic ,assign) NSInteger rId; //rollId(hash_id) 建议用年月日时分秒的整数,大小不要超过0xFFFFFFFF
@property (nonatomic ,copy) NSString *rollName; //rollId(hash_id) 建议用年月日时分秒的整数

@end

@interface ZeronerGPSPoint : ZeronerModel
@property (nonatomic ,assign) NSInteger timeZone; //时区
@property (nonatomic ,assign) float latitude; //纬度
@property (nonatomic ,assign) float longitude; //经度
@property (nonatomic ,assign) NSInteger altitude; //海拔

@end

@interface ZeronerEHRWP : ZeronerModel <NSCoding,NSCopying>
/*
 报警开关 默认为YES*/
@property (nonatomic ,assign) BOOL enable;
/*
 报警上限心率，高于该值触发报警，范围50～200，默认160*/
@property (nonatomic ,assign) NSInteger threshold_high;
/*
 报警下限心率，低于该值触发报警，范围40～190，默认50*/
@property (nonatomic ,assign) NSInteger threshold_low;
/*
 报警检测时间，单位秒，默认30*/
@property (nonatomic ,assign) NSInteger timerOut;
/*
 报警触发间隔，单位分钟，默认2*/
@property (nonatomic ,assign) NSInteger interval;
@end

