//
//  BLESolstice.h
//  BLESolstice
//
//  Created by A$CE on 2017/10/9.
//  Copyright © 2017年 A$CE. All rights reserved.
//
#import "AutumnHeader.h"
#import <Foundation/Foundation.h>

@class ZRBlePeripheral;
@class ZRDeviceInfo;
@class ZRClock;
@class ZRSedentary;
@class ZRDNDModel;
@class ZRPersonal;
@class ZRHWOption;
@class ZRSportLists;
@class ZRRoll;
@class ZRCOption;
@class ZRGPSPoint;
@class ZRWeather;
@class ZR24Weather;
@class ZRSchedule;
@class ZRContacts;
@class ZREHRWP;
@class ZRMotor;
@class ZRAction;
@class ZRGnssParam;
@class ZGUserInfoModle;
@class ZRTargetOnceDay;
@class ZRMesgPush;

typedef void(^ReadDeviceSettingComplementation)(id obj);

/**
 Communication agent, holding peripheral connection object, make a protocol conversion between the app and the device, so that the API is easier to understand than the binary.
 All api are suitable for the scene, not all devices support all api, if your device does not support your api call, you will get an NSError or in the console to see the "device does not support" log
 */
@protocol BLESolstice <NSObject,CBPeripheralDelegate>


/**
 This method can help you to get that Device object you are connected to.

 @return Returns as a CBPeripheral object
 */
- (CBPeripheral *)getConnectedPeriphral;

/*
 * Call this method if you had change the peripheral's delegate for any other object.
 */
- (void)registerDeviceDelegate;
#pragma mark- BLE
/**! Read device Info. Got the response in method readResponseFromDevice:*/
- (void)readDeviceInfo;
/**! Read device battery. Got the response in method readResponseFromDevice:*/
- (void)readDeviceBattery;
/**! Reboot device .Special device supported*/
- (void)rebootDevice;
/**! Upgrade device for DFU ,device will enter DFU state while received this cmd*/
- (void)deviceUpgrade;
/**! Device debind from iPhone system*/
- (void)debindFromSystem;
/**! Exchange ANCs information between Device and App
 * isActive: Enter YES when app is active;
 */
- (void)exchangeANCsState:(BOOL)isActive;
/**! Set don't disurb model*/
- (void)setDNDMode:(ZRDNDModel *)dndModel;
/**! Read DND model. Got the response in method readResponseFromDevice:*/
- (void)readDNDModeInfo;
/**! Sent weather info to device for show in screen ,special devices support*/
- (void)setWeather:(ZRWeather *)weather;
/**! Set Weather Unit ,0-Centigrade ,1-Fahrenheit @see TempUnit ,speacial devices support*/
- (void)setWeatherUnit:(NSInteger)unit;
/**! Set 24 hours weather data ,speacial devices support*/
- (void)set24Weathers:(ZR24Weather *)weather;
/**!Appearance time of the device, Got the response in method readResponseFromDevice:*/
- (void)readManufactureDate;
/**! Factory configuration, Got the response in method readResponseFromDevice:<##>*/
- (void)readFactoryConfiguration;
#pragma mark -SETTING ACTION-设置操作

/**
 @see syscTime:
 */
- (void)syscTimeAtOnce;
/**
 Synchronization time

 @param date The date your need sysc in device.
 */
- (void)syscTime:(NSDate *)date;
/**! Read device dateTime. Got the response in method readResponseFromDevice:*/
- (void)readTime;

/**! Set app and watch sync speed */
- (void)setBLESpeedMode:(BLECommunicateMode)mode;
/**! Read ble speed mode. Got the response in method readResponseFromDevice:*/
- (void)readBLESpeedMode;
/**! Set BLE sign*/
- (void)setBLESign:(BLEParamSign)sign;
/**! Read ble sign type. Got the response in method readResponseFromDevice:*/
- (void)readBLESign;

/**! The device reserves a fixed number of alarm settings (usually eight), this method allows you to set the alarm one by one, the id of the alarm is a continuous natural number, do not exceed the allowable range, if the device has an alarm id 0x07, This is you add an alarm id is still 0x07, which is the total number of alarm clock in the device is still 1, that 0x07 alarm content will be your last set.
 Special device support, device in <BLEProtocol_Colorful> did not support this method ,use method setAlarmClocks:andSchedules: instead.
 @param clockModel alarm clock object.
 */
- (void)setAlarmClock:(ZRClock *)clockModel;

/**
 Because of the protocol, all alarms and schedules are written in one time in the same command. With this method, you need to remember the alarms and schedules you have set. Each time this method is called, the new alarm is written And schedule settings, all previous settings will be cleared. Communication reasons, this method takes a long time, when used, please note that the operation of the time interval.
 This method is designed for <BLEProtocol_Colorful> devices, but is compatible with other devices and is not recommended for use if your device is not BLEProtocol_Colorful
 @param clockModels All clocks method, you should been set less than 4 in BLEProtocol_Colorful, less than 8 in other protocol type device.
 @param schedules You are advised to write no more than 4 calendars
 */
- (void)setAlarmClocks:(NSArray<ZRClock *> *)clockModels andSchedules:(NSArray<ZRSchedule *> *)schedules;
/**
 Read alarm clocks from device. If you had sent nil to param racResponse,you will got the response in method readResponseFromDevice:

 @param racResponse Block for read response .
 */
- (void)readAlarmClocks:(ReadAlarmClockResponse)racResponse;
/**! Clear all clocks in smartband*/
- (void)clearAllClocks;

/**! Set single ZRSchedule ,special device support. */
- (void)setSchedule:(ZRSchedule *)sModel;
/**! Close single ZRSchedule ,special device support. */
- (void)closeSchedule:(ZRSchedule *)sModel;

/**
 Read schedule info ,If you had sent nil to param rsResponse, you will got the response in method readResponseFromDevice:
 dict[@"cur_num"] 当前可配置日程数量
 remaining number of schedule could be set.
 dict[@"all_num"]:日程最大数量
 max number of schedule we can configure
 dict[@"day_num"]:每天可配置日程数量
 max number of schedule could  be configured for one day.
 @param rsResponse Block for read schedule info.
 */
- (void)readScheduleInfo:(ReadSheduleResponse)rsResponse;
/**! Read special schedule model. Got the response in method readResponseFromDevice:*/
- (void)readSchedule:(ZRSchedule *)sModel;
/**! Clear all ,there is no way to delete one schedule model ,your should call this method if you need remove some invalid calendars for set more*/
- (void)clearAllSchedules;

/**! Set sedentary warning*/
- (void)setSedentary:(ZRSedentary *)sedentaryModel;
/**! Read sendentary. Got the response in method readResponseFromDevice:*/
- (void)readSedentary;

/**! Setting device option ,Some bracelets only support some settings*/
- (void)setDeviceOption:(ZRHWOption *)deOption;
/**! Read device option. Got the response in method readResponseFromDevice:*/
- (void)readDeviceOption;
- (void)readDeviceOptionWithBlock:(ReadDeviceSettingComplementation)rdsComplemention;

/** read/set r1 option */
- (void)readEarPhoneDeviceOptionWithBlock:(ReadDeviceSettingComplementation)rdsComplemention;
- (void)setEarPhoneDeviceOption:(ZRHWOption *)deOption;

/**! Get sport type list that device support. Got the response in method readResponseFromDevice:*/
- (void)readSupportSports;

/**! Add a moving target to the device, and then you can see the type of motion you added on the device's exercise screen*/
- (void)setSportLists:(ZRSportLists *)st;
/**! Read Sport target in device. Got the response in method readResponseFromDevice:*/
- (void)readSportLists;


/** Add contacts to the device ,special device support.*/
- (void)addContacts:(ZRContacts *)cModels;
/**! Read. Got the response in method readResponseFromDevice:*/
- (void)readContacts;
/**! Remove*/
- (void)removeContacts:(NSArray<ZRContacts *> *)cModels;
/**! Clear*/
- (void)clearAllContacts;

/**! Set personal info .The device requires you to pass in actual wearer information to help correct the gait algorithm */
- (void)setPersonalInfo:(ZRPersonal *)personalModel;
/**! Read personal info. Got the response in method readResponseFromDevice:*/
- (void)readPersonalInfo;

/** Heart rate alarm parameters ，Special device support*/
- (void)setEHRWParam:(ZREHRWP *)ehrwp;
/**! Read. Got the response in method readResponseFromDevice:*/
- (void)readEHRWParam;

/** Set GNSS location information, this function is aided <BLEProtocol_Watch> positioning, other devices do not need to deal with it.*/
- (void)setGNSSParameter:(ZRGnssParam *)gp;
/**! Read. Got the response in method readResponseFromDevice:*/
- (void)readGNSSParameter;

/** Set the target number of days and target calories on the day, a ring indicating the progress will be displayed on the home page of the device. If the device supports this method */
- (void)setTargetOnceDay:(ZRTargetOnceDay *)target;
/**! Read. Got the response in method readResponseFromDevice:*/
- (void)readTargetOnceDay;

/** Set incoming call reminder and message reminder */
- (void)setMessagePush:(ZRMesgPush *)messagePush;
/**! Read. Got the response in method readResponseFromDevice:*/
- (void)readMessagePush;

#pragma mark -MESSAGE ACTION-消息操作
/*!
 * Push string, Example: [ZRBLE pushStr:@"This is a test string"];
 */
- (void)pushStr:(NSString *)str; 

/**
 Add a message blacklists .
 The contents of the blacklist agreement are as follows:
 The app writes the corresponding application package name (such as WeChat) to the hand ring through a specific protocol. The wristband performs blacklist filtering by using the package name from the data information received by the ANCS, and the application message that adds the blacklist is no longer displayed on the handband interface on.
 Notes:
 1. Due to limited bracelet space, only four blacklist applications are currently supported
 2. The factory does not set a blacklist
 3. Some custom firmware should be set to white list client requirements, iwown common version is set to blacklist
 Set the blacklist protocol as follows:
 Add
             "com.tencent.xin "- WeChat
             "com.tencent.mqq" - QQ
             "com.apple.mobilephone" - Incoming call
             "com.apple.MobileSMS" - message
 For more build identify for third part apps. use 【ios-deploy --id [udid] --list_bundle_id 】in Ternimal got them. Links:https://segmentfault.com/a/1190000010205616
    @code
             NSArray * arr = @ [@ "com.apple.mobilephone",
                                @ "com.apple.MobileSMS"
                                @ "com.tencent.mqq",
                                @ "com.tencent.xin"];
             NSMutableArray * mArr = [NSMutableArray arrayWithCapacity: 0];
             for (int i = 0; i <arr.count; i ++) {
                 ZeronerRoll * zRoll = [[ZeronerRoll alloc] init];
                 zRoll.rId = 100 + i;
                 zRoll.rollName = arr [i];
                 [mArr addObject: zRoll];
             }
             [[BLELib3 shareInstance] addSpecialList: mArr];
    @endcode
 2. Read the blacklist application information
    @code    [[BLELib3 shareInstance] readAllList];@endcode
 3. Clear blacklist
    @code    [[BLELib3 shareInstance] clearAllLists];@endcode
 4 read the contents of the blacklist
    @code    NSMutableArray * mArr = [NSMutableArray arrayWithCapacity: 0];
             for (int i = 0; i <3; i + = 2) {
                 ZeronerRoll * zRoll = [[ZeronerRoll alloc] init];
                 zRoll.rId = 101 + i;
                 [mArr addObject: zRoll];
             }
             [[BLELib3 shareInstance] removeSpecialList: mArr]; @endcode

 @param sLists The blaklists
 */
- (void)addSpecialList:(NSArray <ZRRoll *>*)sLists;
- (void)removeSpecialList:(NSArray <ZRRoll *>*)sLists;
- (void)clearAllLists;
- (void)readSpecialList:(NSInteger)rId;
- (void)readAllList;

#pragma mark -CONTROL ACTION-控制操作
/*!
 * setKeyNotify 进入智拍模式设置1. 退出智拍模式设置0   // 通知拍照从 - (void)notifyToTakePicture; 获得
 * call this method to become smart photo or exits. set value 1 to active and set 0 to exit; get photoes @see - (void)notifyToTakePicture;
 */
- (void)setKeyNotify:(BKeyNotify)keyNotify;

/** Set the vibration mode*/
- (void)setMotors:(NSArray<ZRMotor *> *)motors;
/**! Read count of motor type. Got the response in method readResponseFromDevice:*/
- (void)readSupportMotorCount;
/**! Experience the vibration<##>*/
- (void)feelMotor:(ZRMotor *)motor;

/**! Set motion recognition parameters, transparent protocols, special equipment support*/
- (void)setRecognitionParams:(ZRAction *)action;

/**! Custom device function protocol, special device support*/
- (void)setCustomOptions:(ZRCOption *)cOption;
/**! Read. Got the response in method readResponseFromDevice:*/
- (void)readCustomOptions;

/**
 <BLEProtocol_Watch> The device's EPO (Assisted Positioning Protocol) upgrade is used to assist the device in positioning. When the device receives this command, it will trigger BTNotify communication and implement the BTNotify protocol protocol to upgrade the EPO file
 */
- (void)startEpoUpgrade;

/**! Devices that implement <BLEProtocol_Colorful> need to set the state of the communication over the lBLE connection in three states, direct, iOS, Android; only the fact that the state is iOS is communicable in our case, and the rest are invalid . Calling the setBleConnectStatus method attempts to set the connection state parameter, and the getConnectionStatus party can read the connection parameter. The return value is available in the responseOfConnectStatus: method.*/
- (void)setBleConnectStatus;
/**! responseOfConnectStatus:<##>*/
- (void)getConnectionStatus;

/**
 This method will read the device's data, you can get the returned data info in the updateNormalHealthDataInfo: method, you can sync the data you want to get based on the data
 */
- (void)getDataStoreDate;
/**! Mehtod to sysc data .
 @see startSpecialData:withDate:startSeq:endSeq:*/
- (void)startSpecialData:(SD_TYPE)sdType;
/**! Mehtod to sysc data .
 @see startSpecialData:withDate:startSeq:endSeq:*/
- (void)startSpecialData:(SD_TYPE)sdType withDate:(NSDate *)date;

/**
 Synchronize the data method, incoming data from the updateNormalHealthDataInfo: method to get your specified time or type of data, the data is packaged in a fixed manner, based on the amount of data, some of the data we are packaged together, But there are some data as a separate data package

 @param sdType Type
 @param date Special date .This version of the SDK which we put the time of the data as an important dimension, many data are packaged based on the date. However, some bracelets do not support this. If you do not get a valid date, you can pass in nil when syncing data or we consider this case, which is also valid on certain devices. Or you can use method without this parameter like startSpecialData:
 @param startSeq Some devices rely on Seq for their data continuity and require that they be passed in when they are synchronized. If you get startSeq & endSeq in your device info is 0, this means your device does not need this seq, Please also 0 value as a parameter to synchronize data, which is ok, or you can use the method does not need to pass in this parameter
 @see startSpecialData:withDate:
 @param endSeq Similar to startSeq.
 */
- (void)startSpecialData:(SD_TYPE)sdType withDate:(NSDate *)date startSeq:(NSInteger)startSeq endSeq:(NSInteger)endSeq;
/**! SDK internal use, do not need to use it*/
- (void)stopSpecialData:(SD_TYPE)sdType;

/*
 * Developer test api
 */
- (void)write09WithBOOL:(BOOL)isOpen DEPRECATED_ATTRIBUTE;
/*
 * Clear user's data on device.
 */
- (void)clearData DEPRECATED_ATTRIBUTE;


-(void)testECGModel;


//微教练
- (void)startExercise;
- (void)endExercise;
- (void)pauseExercise;


@end



