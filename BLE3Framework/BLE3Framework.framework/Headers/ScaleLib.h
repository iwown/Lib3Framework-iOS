//
//  ScaleLib.h
//  ScaleLib
//
//  Created by Jackie on 15/4/27.
//  Copyright (c) 2015年 Jackie. All rights reserved.
//
#define SCALEE_SERVICE_UUID                 @"FFF0"
#define SCALE_STATUS_CHARACTERY_UUID        @"FFF0"
#define SCALE_SETTING_CHARACTERY_UUID       @"FFF1"
#define SCALE_DATA_CHARACTERY_UUID          @"FFF4"
#define DEPRECATED(BLE_PROTOCOL_VERSION,BLE_SDK_VERSION)

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreBluetooth/CBService.h>



@protocol ScaleLibDelegate <NSObject>

@optional

- (void)bleCtlDidDisconnectPeripheral:(CBPeripheral *)aPeripheral ;

- (void)bleCtlDidConnectPeripheral:(CBPeripheral *)aPeripheral ;

- (void)bleCtlDidFailToConnectPeripheral:(CBPeripheral *)aPeripheral;
@required

- (void)bleCtlDidReceivedData:(NSDictionary *)dictionary;

@end


@interface ScaleLib : NSObject<CBCentralManagerDelegate,CBPeripheralDelegate>


@property (nonatomic, weak) id<ScaleLibDelegate> delegate;

@property (nonatomic, copy) NSString *infoData;
/*!
 * 单例对象
 */
+(ScaleLib *)shareInstance;


/*!
 * scanDevice,扫描设备
 * stopScanDevice,停止扫描设备
 */
- (void)scanDevice;
- (void)stopScanDevice;
- (void)unConnectDevice;

- (void)turnOffScaleDevice;



@end
