//
//  BLEquinox.h
//  BLESolstice
//
//  Created by A$CE on 2017/10/10.
//  Copyright © 2017年 A$CE. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "BLESolstice.h"
#import "ZRBlePeripheral.h"

@class ZRHealthData;
@class ZRDataInfo;

/**
 DicoverDeleagte，Response delegate methods in discover device.
 */
@protocol BleDiscoverDelegate <NSObject>

@required

/**
 * This method is invoked while scanning
 
 @param iwDevice Instance contain a CBPeripheral object and the device's MAC address
 */
- (void)solsticeDidDiscoverDeviceWithMAC:(ZRBlePeripheral *)iwDevice;

/**
 * Search stopped
 */
- (void)solsticeStopScan;

@end

/**
 ConnectDeleagte，Response delegate methods in device connect method.
 */
@protocol BleConnectDelegate <NSObject>

@required
/**
 *  invoked when the device did connected by the centeral
 *
 *  @param device the device did connected
 */
- (void)solsticeDidConnectDevice:(ZRBlePeripheral *)device;

@optional

/**
 Invoked when the device did disConnect with the connectted centeral

 @param device The device whom the centeral was connected
 @param error In most cases it is nil
 */
- (void)solsticeDidDisConnectWithDevice:(ZRBlePeripheral *)device andError:(NSError *)error;
/**
 Invoked when the device did fail to connected by the centeral

 @param device The device whom the centeral want to be connected
 @param error In most cases it is nil
 */
- (void)solsticeDidFailToConnectDevice:(ZRBlePeripheral *)device andError:(NSError *)error;

/**
 *  invoked when connect more than 10 second.
 */
- (void)solsticeConnectTimeOut;

/**! Bluetooth state changed off.<##>*/
- (void)centralManagerStatePoweredOff;
/**! Bluetooth state changed on.<##>*/
- (void)centralManagerStatePoweredOn;

@end


/**
 Common protocol methods handle hub and perimeter communications
 */
@protocol BLEquinox <NSObject>

/**
 * After the connection is established, the SDK needs some basic setup, which takes a few seconds. After this, will call back this method, you might need read some infomation in device ,You are advised to call some methods here, like @CODE{readDeviceInfo} @CODE{readDeviceBattery}. Or do device setting in method @CODE{setBLEParameterAfterConnect}
   In <BLEProtocol_colorful> device ,these methods would not be invoked when you had implement method responseOfConnectStatus:
 */
- (void)readRequiredInfoAfterConnect;
/**
 *  I suggest you here to complete the need for other operations.
 */
- (void)setBLEParameterAfterConnect;

@optional

/**
 *  This method would be invoked when the app connected a device who is supportted by protocol2_0
 *  当前手环是2.0协议的手环是调用这个方法。
 */
- (void)didConnectProtocolNum2_0;

/**
 * The connection status is abnormal, it usually does not happen. If it appears, restart the Bluetooth and device.
 * Used for <BLEProtocol_colorful> device.
 * 连接状态异常，通常不会发生，如有出现，请重启蓝牙和设备。
 */
- (void)responseOfConnectStateError;
/**
 * 声明：蓝牙日志的解读需要ZR蓝牙协议的文档，如果你没有阅读文档的权限，身边也没有可以阅读此文档的人，那么写日志对你来说不是必要的。
 * 传一个地址，如果你需要蓝牙的日志的话，最好是txt格式的。
 * Return a file path for BLE log, you are expected return a file path type txt. like this
 * @code
 NSString *documentsPath =[NSString stringWithFormat:@"%@/Documents", NSHomeDirectory()];
 NSString *testPath = [documentsPath stringByAppendingPathComponent:@"BLE.txt"];
 return testPath;
    @endcode
 */
- (NSString *)bleLogPath;
/**
 * Description: APP initiative call setKeyNotify: 1, let the bracelet into the camera mode, camera button appears on the ring,
 Press the button or click the button The bracelet SDK will notify the App through notifyToTakePicture photo.
 Note: setKeyNotify into App mode after setting 1. Exit the camera interface to set 0
 Need to do photo protection, take pictures before saving is complete Do not open the second photo.
 Description: Long press the ring button or click the touch screen to select the phone button, the ring SDK will notify App via notifyToSearchPhone, the ring needs to find the phone.
  * Next App can play music or other operation to find the phone

 @param bkn Operation events type
 */
- (void)responseKeyNotify:(BKeyNotify)bkn;

/**
 Most read status operations will be returned in this method, including device information, device power and so on.
 Distinguished by the type of BLECmdResponse.

 @param response  @{"type" : BLECmdResponse,"data" : id}
 */
- (void)readResponseFromDevice:(ZRReadResponse *)response;

/**
 *  Method would be invoked when syscData state changed
 *  @param ksdState type means sysc finished process.
 */
- (void)syscDataFinishedStateChange:(KSyscDataState)ksdState;


/**
 Return data information

 @param zrDInfo Contain dataType,date,seqStart,seqEnd and more.
 */
- (void)updateNormalHealthDataInfo:(ZRDataInfo *)zrDInfo;

/**
 Return data.

 @param zrhData See more in ZRHealthData.h
 */
- (void)updateNormalHealthData:(ZRHealthData *)zrhData;

/**! Simple progress in Percent<##>*/
- (void)updateDataProgress:(NSInteger)progress;


/**
 * Heart Rate Protocol  心率标准协议
 * @param hr  Real-time heart rate 实时心率
 */
- (void)responseHeartRateData:(NSInteger)hr;

/**! Successfully disconnected, you can call the unbinding method here.<##>*/
- (void)debindFromBraceletSuccessful;

/**
 This method can get the connection status, when isReady == YES indicates that the communication is established, otherwise most of the business communication is not available. The SDK has its own RCC(Rotation Check Communication) method to set the connection status. You can also control it yourself by implementing this method and the two command methods setBleConnectStatus && getConnectionStatus.
 RCC(轮询检查通信) refers to the SDK after looping through reading and writing to get the correct connection status and handle some basic operations. In case of opening RCC, the interface method of SDK is readRequiredInfoAfterConnect && setBLEParameterAfterConnect. Or SDK would not invoke these two method ,interface instead by this method.
 After you have implemented this method, the SDK's RCC will not work.

 @param isReady YES means communication is OK, or you need call setBleConnectStatus to let device in ready.
 */
- (void)responseOfConnectStatus:(BOOL)isReady;

/**
 当获取8900、8901、8902、8903、8904类型的数据的时候，写指令发出后，没有收到手环传回的数据，就会调取这个回调；
 app可以根据这个回调方法，在方法内部给同步进度的progress做虚拟值赋值处理；

 @param type 8900、8901、8902、8903、8904
 */
- (void)responseOfGetDataTimeOutWithDataType:(NSInteger)type;


#pragma mark -FOTA

/**
 Transparent method, used with BtNotify. <BLEProtocol_watch> support

 @param cbc CBCharacteristic object
 */
- (void)responseOfMTKBtNotifyData:(CBCharacteristic *)cbc;
/**! Simlar to responseOfMTKBtNotifyData:*/
- (void)responseOfMTKBtWriteData:(CBCharacteristic *)cbc;
/**! Secretly Upgreade epo events*/
- (void)itIsBestTimeForEpoSecretly;


#pragma mark -
- (void)responseOfExercise:(NSString *)string;

@end

