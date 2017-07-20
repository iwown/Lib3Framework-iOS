//
//  BLELib3Protocol.h
//  BLE3Framework
//
//  Created by 曹凯 on 16/9/27.
//  Copyright © 2016年 Zeroner. All rights reserved.
//

#ifndef BLELib3Protocol_h
#define BLELib3Protocol_h

typedef enum{
    CurrentBLEProtocol2_0 = 0,
    CurrentBLEProtocol3_0
}CurrentBLEProtocol;

typedef enum{
    KSyscDataStateBegin = 0, //同步开始
    KSyscDataState29End,     //29结束
    KSyscDataStateSleepEnd , //28结束
    KSyscDataStateHeartRateEnd , //51结束
    KSyscDataStateInFinished , //全部结束
}KSyscDataState;

/**
 * If your smartband supportted this option ,that is meant this device might show message sign replaced a bluetooth icon noticed connectted state .If you don't want to ,Please implement 
\@method \bleParamSignSetting of \@protocol \BleConnectDelegate .use \@code \BLEParamSignConnect you will get bluetooth icon on screen of your smartband;
 * 如果你的手环支持这个协议，你将在手环上看到一个消息标示而不是一个表示连接状态的蓝牙图标。如果你不想要这样，请实现bleParamSignSetting方法，使用BLEParamSignConnect选项，你就可以在你手环屏幕上看到那个可爱的蓝牙图标了。
 */
typedef enum{
    BLEParamSignConnect  = 0, //同旧手环，显示蓝牙（连接OR断开）状态
    BLEParamSignMSGOption   ,//消息图标（苹果）模式，依赖ANCS显示消息推送（可用OR不可用）状态
    BLEParamSignMSGOptionDelay DEPRECATED_ATTRIBUTE,    //消息图标延时（安卓）模式
}BLEParamSign;

typedef void(^NFCSuccessData)(id data);

@class ZeronerBlePeripheral;
@class ZeronerDeviceInfo;
@class ZeronerClock;
@class ZeronerSedentary;
@class ZeronerDNDModel;
@class ZeronerPersonal;
@class ZeronerHWOption;
@class ZeronerSportTarget;
@class ZeronerRoll;
@class ZeronerCOption;
@protocol BleDiscoverDelegate <NSObject>

@required


/**
 * This method is invoked while scanning

 @param iwDevice Instance contain a CBPeripheral object and the device's MAC address
 */
- (void)IWBLEDidDiscoverDeviceWithMAC:(ZeronerBlePeripheral *)iwDevice;

@optional
/**
 *
 *  @return Specifal services used for communication. For exeample, like bracelet, you should return  @{@"FF20",@"FFE5"}, you also should not implement this method if want to connect with zeroner's bracelet.
 */
- (NSArray<NSString *> *)serverUUID;

@end

@protocol BleConnectDelegate <NSObject>

@optional
/**
 *   @see BLEParamSign
 *   设置蓝牙参数，默认 BLEParamSignConnect
 */
- (BLEParamSign)bleParamSignSetting;
- (void)responseOfBLEParamSignSetting DEPRECATED_ATTRIBUTE;
@required
/**
 *  invoked when the device did connected by the centeral
 *
 *  @param device the device did connected
 */
- (void)IWBLEDidConnectDevice:(ZeronerBlePeripheral *)device;

@optional

/**
 *  invoked when the device did disConnect with the connectted centeral
 *
 *  @param device the device whom the centeral was connected
 */
- (void)IWBLEDidDisConnectWithDevice:(ZeronerBlePeripheral *)device andError:(NSError *)error;

/**
 *  invoked when the device did fail to connected by the centeral
 *
 *  @param device the device whom the centeral want to be connected
 */
- (void)IWBLEDidFailToConnectDevice:(ZeronerBlePeripheral *)device andError:(NSError *)error;

/**
 *  表示手环注册ANCS失败，此时消息推送不能work，需要重新配对。
 *  This method would be invoked when the Peripheral disConnected with the system; In this case ,your app should tell the user who could ingore the device on system bluetooth ,and reconnect and pair the device. or there will be risk of receiving a message reminder.
 *
 *  @param deviceName the Device Name
 */
- (void)deviceDidDisConnectedWithSystem:(NSString *)deviceName;

/**
 *  this method would be invoked when the app connected a device who is supportted by protocol2_0
 *  当前手环是2.0协议的手环是调用这个方法。
 */
- (void)didConnectProtocolNum2_0;

/**
 *  Bluetooth state changed.
 *  检测到蓝牙状态变化
 */
- (void)centralManagerStatePoweredOff;
- (void)centralManagerStatePoweredOn;

@end

@protocol BLELib3Delegate <NSObject>

#pragma mark -/****************************===device setting===*****************************************/

@required
/*
 *  Set bracelet parameter after connect with app.
 *  like ZeronerHWOption, ZeronerPersonal
 */
- (void)setBLEParameterAfterConnect;

#pragma mark -/****************************===device function===*****************************************/
@optional

/**
 * 声明：蓝牙日志的解读需要zeroner蓝牙协议的文档，如果你没有阅读文档的权限，身边也没有可以阅读此文档的人，那么写日志对你来说不是必要的。
 * 传一个地址，如果你需要蓝牙的日志的话，最好是txt格式的。
 * Return a file path for BLE log, you are expected return a file path type txt. like this
 * @code NSString *documentsPath =[NSString stringWithFormat:@"%@/Documents", NSHomeDirectory()];
    NSString *testPath = [documentsPath stringByAppendingPathComponent:@"BLE.txt"]; @/code
 */
- (NSString *)bleLogPath;
- (NSString *)arithmeticLogPath;
- (NSString *)arithmeticLogDir;
- (NSString *)currentUserUid;
/*!
 * 描述: APP主动call setKeyNotify:1，让手环进入到拍照模式，手环上出现拍照按钮，
 *      按键或点击按钮手环SDK会通过 notifyToTakePicture 通知App拍照。
 * 注意: setKeyNotify 进入App智拍模式后设置1. 退出拍照界面设置0
 *      需要做拍照保护，拍照在未保存完成前不要开启第二次拍照。
 */
- (void)notifyToTakePicture;

/*!
 * 描述: 长按手环按钮或者点击触屏选择找手机按钮，手环SDK会通过 notifyToSearchPhone告诉App，手环需要找手机。
 *       接下来App可以播放寻找手机的音乐或者其他操作
 */
- (void)notifyToSearchPhone;

#pragma mark -/****************************===device Info===*****************************************/

- (void)updateDeviceInfo:(ZeronerDeviceInfo *)deviceInfo;
- (void)updateBattery:(ZeronerDeviceInfo *)deviceInfo;


/**
 the method be called after call - (void)getSupportSportsList;

 @param ssList ssList
 */
- (void)notifySupportSportsList:(NSDictionary *)ssList;

/**
 *  responseOfGetTime
 *
 *  @param date (year month day hour minute second)
 */
- (void)responseOfGetTime:(NSDate *)date;


/**
 the response of get clock

 @param clock clock
 */
- (void)responseOfGetClock:(ZeronerClock *)clock;


/**
 the response of get sedentary

 @param sedentarys sedentarys
 */
- (void)responseOfGetSedentary:(NSArray<ZeronerSedentary *>*)sedentarys;


/**
 the response of get HWOption

 @param hwOption hwOption
 */
- (void)responseOfGetHWOption:(ZeronerHWOption *)hwOption;

- (void)responseOfGetSprotTarget:(ZeronerSportTarget *)spModel;

- (void)responseOfDNDSetting:(ZeronerDNDModel *)dndModel;

- (void)responseOfPersonalInfo:(ZeronerPersonal *)pModel;

- (void)responseOfMotoControl:(NSUInteger)countsOn;

- (void)responseOfCustomOption:(ZeronerCOption *)cOption;

#pragma mark -/****************************===device data===*****************************************/

/**
 *  Method would be invoked when syscData state changed
 *
 *  @param ksdState type means sysc finished process.
 */
- (void)syscDataFinishedStateChange:(KSyscDataState)ksdState;

/**
 *  Method would be invoked when received sport segement data（type 0x28）
 *
 @param dict dict
 */
- (void)updateSleepData:(NSDictionary *)dict;

/**
 * Method would be invoked when received sport segement data（type 0x28）

 @param dict dict
 */
- (void)updateSportData:(NSDictionary *)dict;

/**
 *  Method would be invoked when received sport summary data（type 0x29）
 *
 @param dict ：Dictionary object contains accurate timestamp provided by smartband.
 */
- (void)updateWholeDaySportData:(NSDictionary *)dict;

/**
 *  Method would be invoked when received sport summary data（type 0x29）
 *
 @param dict ：Dictionary object without accurate timestamp provided by smartband. SDK use [NSDate date] replace it.
 */
- (void)updateCurrentWholeDaySportData:(NSDictionary *)dict;

/**
 * Method would be invoked when received heart rate segement data（type 0x51）

 @param dict dict[detail_data], @{type,开始时间，结束时间，消耗能量，5个心率区间的时间分段、能量消耗、平均心率值},]
 */
- (void)updateHeartRateData:(NSDictionary *)dict;

/**
 *  Method would be invoked when received HeartRate_hours data (type 0x53).
 *  This type data shows data of heart rate in different minutes. In normal, it places one piece of data each hour, each data contains 60 values for average data of heart rate.The API/command for getting this data is @{getHeartRateDataOfHours}, call back method @{@link - (void)updateHeartRateData_hours:(NSDictionary *)dict;}
 *
 * dict[@"hour"] 小时，12表示detail的数据属于 12:00-13:00
 * dict[@"detail_data"], 一个小时内@[每分钟平均心率值]
 */
- (void)updateHeartRateData_hours:(NSDictionary *)dict;

#pragma mark -GNSS
- (void)responseOfHealth60DatasTest:(NSDictionary *)dict;
- (void)responseOfHealth61DataTest:(NSDictionary *)dict;
- (void)responseOfGNSS62DatasTest:(NSDictionary *)dict;
- (void)responseOfGNSS63DataTest:(NSDictionary *)dict;

/**
 *
 *
 */
- (void)allHealthDataDidUploadSport;
- (void)allHealthDataDidUpload28;
- (void)allHealthDataDidUploadHeartRate;
- (void)allHealthDataDidUploadHeartRateHours;

/**
 *  设置日程的应答
 *
 *  @param success YES 成功  NO 失败
 */
- (void)responseOfScheduleSetting:(BOOL)success;

/**
 *  读取某个日程的应答
 *
 *  @param exist YES 存在   NO 不存在
 */
- (void)responseOfScheduleGetting:(BOOL)exist;

/**
 *  读取日程Info的应答
 *
 *  @param dict
 dict[@"cur_num"] 当前可配置日程数量
 remaining number of schedule could be set.
 dict[@"all_num"]:日程最大数量
 max number of schedule we can configure
 dict[@"day_num"]:每天可配置日程数量
 max number of schedule could  be configured for one day.
 */
- (void)responseOfScheduleInfoGetting:(NSDictionary *)dict;

- (void)responseSplecialListsInfo:(NSDictionary *)dict;
- (void)responseSplecialRoll:(ZeronerRoll *)zRoll;

@end


#endif /* BLELib3Protocol_h */