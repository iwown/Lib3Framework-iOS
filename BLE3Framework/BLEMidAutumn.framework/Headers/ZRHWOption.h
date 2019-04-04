//
//  ZRHWOption.h
//  BLEMidAutumn
//
//  Created by A$CE on 2017/12/7.
//  Copyright © 2017年 A$CE. All rights reserved.
//

#import <Foundation/Foundation.h>

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
    braceletLanguageEnglish = braceletLanguageDefault,// some smartband did not support it ,use braceletLanguageDefault if you don't want set in simple chinese.
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
    braceletLanguagePolish = 12,
    braceletLanguageRomanian = 13,
    braceletLanguageSwedish = 14,
    braceletLanguageThai = 15,
    braceletLanguageTurkish = 16,
    braceletLanguageSimpleMarkings = 0xff, //This setting means no char ,all information replaced by figure. show simple icon only.
}braceletLanguage;

#import <BLEMidAutumn/BLEMidAutumn.h>

@interface ZRHWOption : ZRModel

/**
 * switch of led light ,default is NO ,brcelet i7 is not supported .
 * LED灯开关，默认为NO，i7手环不支持。
 */
@property (nonatomic ,assign) BOOL ledSwitch;

/**
 * switch of strong hand, default is YES, left.
 * 惯用手 默认YSE, 左手。
 */
@property (nonatomic,assign)BOOL leftHand;
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
 * Valid only when @ \ wristSwitch is YES, turning on the wrist lit screen function is available at set intervals. The value range is 0-24, indicating the whole hour.
 * 仅在 @\wristSwitch 为YES的时候有效，在设置的时间间隔内，翻腕点亮屏幕功能可用。取值范围在0-24，表示每个整点。
 */
@property (nonatomic, assign) NSInteger wristBlightStart;
@property (nonatomic, assign) NSInteger wristBlightEnd;

/**
 * switch of monitor heart rate automatilly ,turn off smart band would not motinor heart rate unless in sport time. default is YES .
 * 自动监测心率开关 ,关闭自动心率后非运动状态时不检测心率，默认为YES,。
 */
@property (nonatomic, assign) BOOL autoHeartRate;

/**
 * Valid only when @ \ autoHeartRate is YES, turning on the monitor heart rate automatilly function is available at set intervals. The value range is 0-23, indicating the whole hour.
 * 仅在 @\autoHeartRate 为YES的时候有效，在设置的时间间隔内，自动监测心率功能可用。取值范围在0-23，表示每个整点。
 */
@property (nonatomic, assign) NSInteger autoHeartRateStart;
@property (nonatomic, assign) NSInteger autoHeartRateEnd;

/**
 * Switch used for control "Automatic recognition motion" feature
 * 自动运动识别
 */
@property (nonatomic ,assign) BOOL autoSport;

/**
 * switch that control whether double touch AP work
 * 双击触摸开关
 */
@property (nonatomic ,assign) BOOL doubleTouch;

/**
 * switch that control whether wear recognize work
 * 佩戴识别开关
 */
@property (nonatomic ,assign) BOOL wearRecognize;

/** 0[default]: Celsius, 1: Fahrenheit */
@property (nonatomic ,assign) BOOL temperatureUnit;

@property (nonatomic ,copy) NSString *nickName;

- (void)copyOptionForWatch:(ZRHWOption *)hwOption;

- (void)copyOptionForHeadSet:(ZRHWOption *)hwOption;

@end
