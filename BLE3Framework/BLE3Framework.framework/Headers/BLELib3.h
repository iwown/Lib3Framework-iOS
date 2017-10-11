//
//  BLELib3.h
//  test
//
//  Created by caike on 16/9/27.
//  Copyright © 2016年 Zeroner. All rights reserved.
//

#define BLE_MAIN_RESTORE_IDENTIFIER @"main_ble_restore_identifier"

#define SCAN_TIME_INTERVAL 5
#import "ZeronerModel.h"
#import <CoreBluetooth/CoreBluetooth.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "BLELib3Protocol.h"
#import "ZeronerBlePeripheral.h"


@interface BLELib3 : NSObject

@property (nonatomic ,weak) id <BLELib3Delegate>delegate;

@property (nonatomic ,weak) id <BleConnectDelegate>connectDelegate;

@property (nonatomic ,weak) id <BleDiscoverDelegate>discoverDelegate;

/*Read Version Code of SDK*/
- (NSString *)libBleSDKVersion;

/**
 * @property state
 * Supportted add observer ,abandon @readonly ,don't change it anyway.
 */
@property (nonatomic ,assign) kBLEstate state;
@property (nonatomic ,strong) CBPeripheral *peripheral;

/**
 * 控制重连时是否需要write device setting, sdk 内部实现了一套自己的控制。
 */
@property (nonatomic ,assign) BOOL isResetFWSettingNeed;


/**
 * Control whether the SDK automatically reconnect internally, if YES, BLELib3 will reconnect binded device after 2 seconds from initinal. Default is YES.
 * If you need to implement the connection logic yourself, set it to NO.
 */
@property (class ,nonatomic ,assign) BOOL bleReConnectNeed;
/***
 * 用于查询蓝牙是否可用
 * Used for iOS_10 above
 */
@property (nonatomic ,assign) CBManagerState bluetoothState;

/***
 * 用于查询蓝牙是否可用
 * Used for iOS_10 below
 */
@property (nonatomic ,assign) CBCentralManagerState centralBluetoothState;

/*
 * 全局单例类
 * ShareInstance returns a global BLELib3's object configured to interact with low energy peripheral devices
 */
+ (instancetype)shareInstance;
/*
 * Call this method if you had change the peripheral's delegate for any other object.
 */
- (void)registerDeviceDelegate;
#pragma mark -CONNECT ACTION- 连接相关操作

/**
 * Use this method start to scan device ,Please implement method @Code{serverUUID} to custom specific services uuid
 */
- (void)scanDevice;
- (void)stopScan;
- (void)connectDevice:(ZeronerBlePeripheral *)dev;
- (void)unConnectDevice;
- (void)reConnectDevice;

/**
 * Use for custom connected.
 * If you want use a connected device ,please use @CODE{unConnectDevice} before startWithAConncectedPeripheral;
 */
- (void)startWithAConncectedPeripheral:(CBPeripheral *)peripheral;
#pragma mark -DEVICE ACTION- 设备操作
/**
 *  reset device
 */
- (void)deviceReset;
/*!
 *  发送进入 手环升级的命令。只有支持手环升级的设备需要使用
 ** This cmd could used for update firmware if the smartband is supported.
 */
- (void)deviceUpdate;
/*!
 *  提醒手环和系统解绑
 ** Remind smartband debind with system
 */
- (void)debindFromSystem;

/**
 *  调用这些方法可以得到连接的设备信息和电量信息，可以在
 *  Call these methods to get current connected device's info @see {@link updateDeviceInfo:} And {@link updateBattery:}
 */
- (void)getDeviceInfo;
- (void)readDeviceInfo;
- (void)readDeviceBattery;

#pragma mark -CONFIGURE ACTION-配置操作

/**
 *  获取支持运动类型
 *  Call this method get the supported sports list on current bracelet .@see {@link notifySupportSportsList:}
 */
- (void)getSupportSportsList;

#pragma mark -DATALOG ACTION-数据操作

/**
 * 数据同步，协议0x08会通过一次通信获取手环未上传的数据内容，SDK根据内容逐条同步数据
 *
 */
- (void)syncData;
- (void)stopSyncData;
- (BOOL)syncIsFinished;

/**
 * 获取0x28数据
 */
- (void)getSportData;
- (void)stopSportData;

/**
 * 获取0x29数据
 * Call this method get current sports data; you could run a timer to do this. then you get data what you want  @see {@link updateCurrentWholeSportData:} and @see {@link updateCurrentWholeDaySportData:}
 */
- (void)getCurrentSportData;
- (void)stopCurrentSprotData;

/**
 * Equal 0x28 && 0x29
 *
 @param open @YES 表示打开，@NO表示关闭
 */
- (void)sportDataOpen:(BOOL)open;

/**
 * 0x51
 */
- (void)getHeartRateData;
- (void)stopHeartRateData;

/**
 * 0x53
 */
- (void)getHeartRateDataOfHours;
- (void)stopHeartRateDataOfHours;
/*
 * 请求心率分时数据
 * Read hrdata_hours by this cmd .
 * For the callback would be incoked when the data update. @see
 @link updateHeartRateData_hours :@/link and
 */
- (void)getHRDataOfHours DEPRECATED_ATTRIBUTE /* use getHeartRateDataOfHours instead*/ ;

/**
 * Equal 0x51 && 0x53
 *
 @param open  @YES 表示打开，@NO表示关闭
 */
- (void)heartRateDataOpen:(BOOL)open;

/**
 * Equal 0x28 && 0x29 && 0x51 && 0x53
 *
 * @param on @YES 表示打开，@NO表示关闭
 */
- (void)sportDataSwichOn:(BOOL)on DEPRECATED_ATTRIBUTE /*use {@link healthDataSwichOn:} instead.*/;
- (void)healthDataSwichOn:(BOOL)on;

/*
 * Clear all data on smartband.
 */
- (void)clearSportsData DEPRECATED_ATTRIBUTE;

#pragma mark -SETTING ACTION-设置操作
/**
 * 设置勿扰模式
 * setting DND(Do Not Disturb) mode. write this cmd with a <code>ZeronerDNDModel</code> object .
 */
- (void)setDNDMode:(ZeronerDNDModel *)dndModel;
/**
 * 读取勿扰模式设置
 * read for DND(Do Not Disturb) mode setting. Implement callback method @see\{- (void)responseOfDNDSetting:(ZeronerDNDModel *)dndModel} to get the setting after this cmd.
 */
- (void)readDNDModeSetting;

/**
 * 设置蓝牙参数，控制图标 @see bleParamSignSetting
 * Control bluetooth icon on the left top of smartband's screen
 */
- (void)syscBLEParamSign;
/**
 * 获取蓝牙参数设置 @see responseOfBLEParamSignSetting
 * read for setting param on smartband.
 */
- (void)readBLEParamSignSetting DEPRECATED_ATTRIBUTE;

/**
 * 同步时间
 * Synchronization time
 */
- (void)syscTimeAtOnce;

/**
 * 设置久坐提醒
 * Sedentary setting
 * @Param Max count is 3 .You could insert only one ZeronerSedentary object in this array ,but sedentaryId of the object must be within 0-2 limits.
 */
- (void)setAlertMotionReminders:(NSArray <ZeronerSedentary *> *)sedentaryModels;
- (void)setPersonalInfo:(ZeronerPersonal *)personalModel;
- (void)setScheduleClock:(ZeronerClock *)clockModel; //alarm clock
- (void)clearAllScheduleClock;//clear all clock in smartband
- (void)setFirmwareOption:(ZeronerHWOption *)hwOptionModel;

- (void)readPeriphralTime;
- (void)readSedentaryMotion;
- (void)readPersonalInfo;
- (void)readAlarmClock:(NSInteger)clockId;
- (void)readFirmwareOption;

- (void)setWeather:(ZeronerWeather *)weather;

/**
 * arr [周一的arr，周二的arr，周三的arr，...]
 * 周一的arr [dict，dict，dict,...]， 周二的arr [dict，dict,...],...
 * dict {@"TARGET":@"100", @"TYPE":@"01",...}
 * 注意type和target是十进制的值
 
 * superArr contains 7 subArr like superArr[subArr1[],subArr2[],..subArr7[]]
 * subArr(1-7) match monday to sunday,
 * subArr contains some NSDictionary object contains specific target.
 * the NSDictionary object have keys @"TARGET" and @"TYPE" , @"TARGET" is a NSNumber value of specific target like waking target 8000 steps ,this value should be @8000 , @"TYPE" key is also an NSNumber value , the value matched the enum sd_sportType in ZeronerBleHeader.h file
 * Note : both @"TARGET" and @"TYPE" value is decimalization.
*/
- (void)setSportTarget:(NSMutableArray *)targetArray;
- (void)setSportTargetBy:(ZeronerSportTarget *)st;
- (void)readV3Target;

/*****
 * 写入日程
 */
- (void)writeSchedule:(ZeronerSchedule *)sModel;
/**
 * 清空日程
 */
- (void)clearAllSchedule;
/**
 * 关闭指定日程
 */
- (void)closeSchedule:(ZeronerSchedule *)sModel;
/**
 * 读取日程信息
 */
- (void)readScheduleInfo;
/**
 * 读取指定日程
 */
- (void)readSchedule:(ZeronerSchedule *)sModel;

/*****
 * 添加电话本联系人
 * Add contacts
 */
- (void)addContacts:(ZeronerContacts *)cModels;
/**
 * 读取联系人信息
 */
- (void)readContacts;
/**
 * 删除联系人信息
 */
- (void)removeContacts:(NSArray<ZeronerContacts *> *)cModels;
/**
 * 清除所有联系人信息
 */
- (void)clearAllContacts;

#pragma mark GNSS配置
/**
 * 设置位置信息
 */
- (void)setGNSSParameterWithTimeZone:(NSInteger)timeZone Latitude:(float)latitude Longitude:(float)longitude Altitude:(NSInteger)altitude;
/**
 * 清除位置信息
 */
- (void)readGNSSParameter;


#pragma mark -MESSAGE ACTION-消息操作
/*!
 * 推送字串，比如： [zeronerBLE pushStr:@"这是个测试例子"];
 */
- (void)pushStr:(NSString *)str; //推送字串

- (void)addSpecialList:(NSArray <ZeronerRoll *>*)sLists;
- (void)removeSpecialList:(NSArray <ZeronerRoll *>*)sLists;
- (void)clearAllLists;
- (void)readSpecialList:(NSInteger)rId;
- (void)readAllList;

/**
 * See also: - (void)setDNDMode:(ZeronerDNDModel *)dndModel;
 */
- (void)switchMssageWarning:(BOOL)open;
#pragma mark -CONTROL ACTION-控制操作
- (void)feelMotor:(ZeronerMotor *)motor; //体验震动;
- (void)setMotors:(NSArray<ZeronerMotor *> *)motors;  //设置震动
- (void)setRecognitionParams:(ZeronerAction *)action; //设置动作识别参数
/*!
 * setKeyNotify 进入智拍模式设置1. 退出智拍模式设置0   // 通知拍照从 - (void)notifyToTakePicture; 获得
 * call this method to become smart photo or exits. set value 1 to active and set 0 to exit; get photoes @see - (void)notifyToTakePicture;
 */
- (void)setKeyNotify:(NSUInteger)keyNotify;

- (void)setCustomOptions:(ZeronerCOption *)cOption;
- (void)readCustomOptions;
#pragma mark -HEARTRATE ACTION-心率模块

/**
 设置运动心率报警参数
 */
- (void)setEHRWParam:(ZeronerEHRWP *)ehrwp;
/**
 读取运动心率报警参数
 */
- (void)readEHRWParam;
/*!
 * 写心率参数
 * hrIntensity 运动强度;
 * time 报警时间 units is minute , default is 10 minutes. if you write an number 0, the default num will be valid.
 */
- (void)setHRParamData:(NSUInteger)hrIntensity andAlarmTime:(NSUInteger)time DEPRECATED_ATTRIBUTE;
/*!
 * 读取心率模块参数
 * Read setting params of heartRate;
 */
- (void)getHRParam DEPRECATED_ATTRIBUTE;

/*!
 *  心率升级必备。//注： 暂不支持心率升级
 */
- (void)writeHeartRateUpdateCharacteristicData:(NSString *)str DEPRECATED_ATTRIBUTE;
- (void)hrDataSwichStr:(NSString *)str DEPRECATED_ATTRIBUTE;

/*!
 *  Default is NO. set YES 放弃通用读写操作，在心率升级的时候使用。升级完成时候，需改回.
 */
- (void)setWriteDataForbidden:(BOOL)forbidden DEPRECATED_ATTRIBUTE;

#pragma mark 补录
/**
 *  Read special seq data with data type
 *
 */
- (void)add28DataBySeq:(NSInteger )seq;
- (void)add51DataBySeq:(NSInteger )seq;
- (void)add53DataBySeq:(NSInteger )seq;

- (NSInteger)dataSyncProgress;

- (void)clearUpDataSyscTimer;
#pragma mark --NFC

/**
 *  交换NFC指令和数据
 *
 *  @param data data want change to bracelet use NFC
 *  @param successData block want to do when success
 *  @param failure block callbacked when get any error
 */
- (void)exchangeWithData:(NSString *)data
            responseData:(NFCSuccessData)successData
                 failure:(void(^)(id error))failure;

#define mark -AppBackMode

- (void)applicationDidEnterBackground ;
- (void)applicationWillEnterForeground ;
- (void)applicationWillTerminate ;
- (void)applicationProtectedDataDidBecomeAvailable;
- (void)applicationProtectedDataWillBecomeUnavailable;
- (void)applicationDidFinishLaunchingWithOptions;

- (BraceletType)deviceType;
- (NSString *)getDeivceAlias;

- (BOOL)hasHeartFunction;
- (BOOL)hasScheduleFunction;
- (BOOL)hasWeatherFunction;
- (BOOL)hasMotorControlFunction;
- (BOOL)hasBackgroundLightFunction;
- (BOOL)hasLanguageSelectFunction;
- (BOOL)hasLedLightFunction;
- (BOOL)hasAutoHeartRateFunction;
- (BOOL)hasWristBlightFunction;
- (BOOL)hasExerciseHRWarningFunction;
- (BOOL)hasSimpleLanguage;
- (BOOL)hasJapaneseLanguage;
- (BOOL)hasItalianLanguage;

#pragma mark - 0x6x
- (void)getHealthDataWith60;
- (void)getHealthDataIndexTableWith61;
- (void)startGetHealthDataWith61WithDate:(NSDate *)date StartSeq:(NSInteger)startSeq EndSeq:(NSInteger)endSeq;
- (void)startGetHealthDataWith61WithData:(NSString *)sendData;
- (void)endGetHealthDataWith61;
- (void)getHealthDataIndexTableWith62;
- (void)startGetHealthDataWith62WithDate:(NSDate *)date StartSeq:(NSInteger)startSeq EndSeq:(NSInteger)endSeq;
- (void)startGetHealthDataWith62WithData:(NSString *)sendData;
- (void)endGetHealthDataWith62;
- (void)getHealthDataWith63;
- (void)endGetHealthDataWith63;
- (void)getECGDataIndexTable;
- (void)startGetECGDataWithDate:(NSDate *)date StartSeq:(NSInteger)startSeq EndSeq:(NSInteger)endSeq;
- (void)startGetECGDataWithData:(NSString *)sendData;
- (void)endGetECGData;


#pragma mark -

// 09
- (void)write09WithBOOL:(BOOL)isOpen;

@end
