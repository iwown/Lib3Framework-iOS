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
 * BLECmdResponse
 * pare with braceletCmd_Command_t。
 */
typedef enum {
    CMD_RESPONSE_DEVICE_GET_INFORMATION = 0x00,
    CMD_RESPONSE_DEVICE_NFC_SET_AND_GET = CMD_RESPONSE_DEVICE_GET_INFORMATION,
    CMD_RESPONSE_DEVICE_GET_BATTERY = 0x01,
    CMD_RESPONSE_DEVICE_RESET = 0x02,
    CMD_RESPONSE_DEVICE_UPDATE = 0x03,
    CMD_RESPONSE_DEVICE_REQ_REBOND = 0x04,
    CMD_RESPONSE_DEVICE_DO_REBOND = 0x05,
    CMD_RESPONSE_DEVICE_DND_MODE = 0x06,
    CMD_RESPONSE_DEVICE_WEATHER = 0x07,
    CMD_RESPONSE_DEVICE_SYNCDATA = 0x08,
    CMD_RESPONSE_DEVICE_HEARTBEAT_SIGNAL = 0x09,
    CMD_RESPONSE_DEVICE_HW_OPTION_SUPPERT = 0x0a, // Hardware Option type Support
    
    CMD_RESPONSE_CONFIG_SET_TIME = 0x10,                 // Time
    CMD_RESPONSE_CONFIG_GET_TIME = 0x11,
    CMD_RESPONSE_CONFIG_SET_BLE = 0x12,                  // BLE
    CMD_RESPONSE_CONFIG_GET_BLE = 0x13,
    CMD_RESPONSE_CONFIG_SET_AC = 0x14,                   // AlarmClock
    CMD_RESPONSE_CONFIG_GET_AC = 0x15,
    CMD_RESPONSE_CONFIG_SET_NMA = 0x16,                  // No-Move-Alert
    CMD_RESPONSE_CONFIG_GET_NMA = 0x17,
    CMD_RESPONSE_CONFIG_SET_HW_OPTION = 0x18,            // Hardware Option
    CMD_RESPONSE_CONFIG_GET_HW_OPTION = 0x19,
    CMD_RESPONSE_CONFIG_GET_SPORT_LIST = 0x1a,          // Sport List
    CMD_RESPONSE_CONFIG_SET_SPORT_TARGET = 0x1b,
    CMD_RESPONSE_CONFIG_GET_SPORT_TARGET = 0x1c,
    CMD_RESPONSE_CONFIG_SET_SCHEDULE = 0x1d,        //schedule
    CMD_RESPONSE_CONFIG_GET_SCHEDULE = 0x1e,
    CMD_RESPONSE_CONFIG_SGET_CONTACTS = 0x1f,       //contacts
    
    CMD_RESPONSE_DATALOG_SET_BODY_PARAM = 0x20,    // Body Parmameters
    CMD_RESPONSE_DATALOG_GET_BODY_PARAM = 0x21,    // Read body Parmameters
    CMD_RESPONSE_DATALOG_CLEAR_ALL = 0x22,
    CMD_RESPONSE_DATALOG_START_GET_DAY_DATA = 0x23,
    CMD_RESPONSE_DATALOG_SCALE_SYSC_INFO = CMD_RESPONSE_DATALOG_START_GET_DAY_DATA,
    CMD_RESPONSE_DATALOG_STOP_GET_DAY_DATA = 0x24,
    CMD_RESPONSE_DATALOG_SCALE_SYSC_DATA = CMD_RESPONSE_DATALOG_STOP_GET_DAY_DATA,
    CMD_RESPONSE_DATALOG_START_GET_MINUTE_DATA = 0x25,
    CMD_RESPONSE_DATALOG_SCALE_SYSC_DATA_RECENT = CMD_RESPONSE_DATALOG_START_GET_MINUTE_DATA,
    CMD_RESPONSE_DATALOG_STOP_GET_MINUTE_DATA = 0x26,
    CMD_RESPONSE_DATALOG_GET_CUR_DAY_DATA = 0x27,
    CMD_RESPONSE_DATALOG_GET_SPORTDATA = 0x28,
    CMD_RESPONSE_DATALOG_GET_CUR_SPORTDATA = 0x29,
    CMD_RESPONSE_DATALOG_GET_SLEEP_TEST = 0x2a,
    CMD_RESPONSE_DATALOG_GET_SMF_TEST = 0x2b,   //SMF -> sport minute freeze
    
    CMD_RESPONSE_MSG_UPLOAD = 0x30,
    CMD_RESPONSE_MSG_SINGLE_DOWNLOAD = 0x31,
    CMD_RESPONSE_MSG_MULTI_DOWNLOAD_START = 0x32,
    CMD_RESPONSE_MSG_MULTI_DOWNLOAD_CONTINUE = 0x33,
    CMD_RESPONSE_MSG_MULTI_DOWNLOAD_END = 0x34,
    /***DEPRECATED_ATTRIBUTE
     CMD_RESPONSE_MSG_MSG_SWITCH_SET = 0x35 ,
     CMD_RESPONSE_MSG_MSG_SWITCH_GET = 0x36 ,
     */
    CMD_RESPONSE_MSG_SPECIAL_LIST_SET = 0x37 ,
    CMD_RESPONSE_MSG_SPECIAL_LIST_GET = 0x38 ,
    
    CMD_RESPONSE_CTRL_KEYNOTIFY = 0x40,
    CMD_RESPONSE_CTRL_MOTOR = 0x41,
    CMD_RESPONSE_CTRL_SENSOR = 0x42,
    CMD_RESPONSE_CTRL_RECOGNITION = 0x43,
    CMD_RESPONSE_CTRL_SET_CUSTOM_OPTION = 0x4e,
    CMD_RESPONSE_CTRL_GET_CUSTOM_OPTION = 0x4f,
    
    CMD_RESPONSE_HEARTRATE_PARAM = 0x50,         //读取和设置心率参数
    CMD_RESPONSE_HEARTRATE_DATA = 0x51,          //分段心率数据同步
    CMD_RESPONSE_HEARTRATE_UPDATE = 0x52,        //心率模块升级控制
    CMD_RESPONSE_HEARTRATE_HOURS_DATA = 0x53,    //分时心率数据
    
    CMD_RESPONSE_HEALTH_DAY_DATA = 0x60,
    CMD_RESPONSE_HEALTH_MINUTE_DATA = 0x61,
    CMD_RESPONSE_GNSS_MINUTE_DATA = 0x62,
    CMD_RESPONSE_GNSS_MINUTE_DATA_TEST = 0x63,
}BLECmdResponse;

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
 *  invoked when connect more than 10 second.
 */
- (void)IWBLEConnectTimeOut;

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

/*
 *  Set bracelet parameter after connect with app.
 *  like ZeronerHWOption, ZeronerPersonal
 *  use @CODE{doNotSyscHealthAtTimes} instead .
 */
- (void)setBLEParameterAfterConnect DEPRECATED_ATTRIBUTE;

#pragma mark -/****************************===device function===*****************************************/
@optional
/*
 * Implement this method and return YES if you are not want sysc data automaticlly.
 * Or SDK will call @method{syncData} after a little.
 * NOTE: You should set bracelet parameter in this method instead @CODE{setBLEParameterAfterConnect} ,if you need lot of setting in there. You will be suggested return YES in finally.
 */
- (BOOL)doNotSyscHealthAtTimes;

/**
 * Invoked when sppcial cmd sent to device.
 */
- (BOOL)writeCmdResponse:(BLECmdResponse)type;
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
 *  Method would be invoked when received sport segement data.（data type is 0x28）
 *
 @param dict dict
 */
- (void)updateSleepData:(NSDictionary *)dict;

/**
 * Method would be invoked when received sport segement data .（data type is 0x28）

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

/**
 * Method invoke by of 0x08.
 * Contain data @{key:{jsonStr}}; type key lists : 0x29\0x28,0x51,0x53;
 * jsonStr equal = @"{\"total\":%d,\"start\":%d,\"end\":%d}"; total =cicle num of seq, start=start of seq; end =end of seq
 */
- (void)updateNormalHealthData:(NSDictionary *)dict;

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
