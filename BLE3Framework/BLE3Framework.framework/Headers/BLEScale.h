//
//  BLEScale.h
//  BLELib3
//
//  Created by 曹凯 on 2016/12/15.
//  Copyright © 2016年 Iwown. All rights reserved.
//
@class ZeronerScaleData;
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@protocol BLEScaleDelegate <NSObject>

@optional

- (void)bleCtlDidDisconnectPeripheral:(CBPeripheral *)aPeripheral ;

- (void)bleCtlDidConnectPeripheral:(CBPeripheral *)aPeripheral ;

- (void)bleCtlDidFailToConnectPeripheral:(CBPeripheral *)aPeripheral;

- (void)bleCtlDidDiscoverPeripheral:(CBPeripheral *)aPeripheral;

- (void)bleCtlDidReceivedDeviceInfoS2:(ZeronerDeviceInfo *)deviceInfo;

/**
 * 24数据
 * detail about @\param
 */
- (void)bleCtlDidReceivedDataS2:(ZeronerScaleData *)scale;
- (void)bleCtlDidFinishedSyscDataS2:(ZeronerScaleData *)scale;
/**
 * 25数据
 * 数据格式同24
 */
- (void)bleCtlDidReceivedDataS2Recently:(ZeronerScaleData *)scale;



@end

@interface BLEScale : NSObject<CBCentralManagerDelegate,CBPeripheralDelegate>

@property (nonatomic, assign) id<BLEScaleDelegate> delegate;

@property (nonatomic, copy) NSString *infoData;

- (kBLEstate)deviceState;

- (void)scanDevice;
- (void)stopScanDevice;
- (void)turnOffScaleDevice;
- (void)connectDevice:(CBPeripheral *)device;
- (void)cancelConnect;

- (void)readScaleDeviceInfo;
- (void)readScaleDeviceBattery;

- (void)deviceReboot;
- (void)deviceUpdate;
- (void)debindFromSystem;

- (void)syscTime;
- (void)readTimeOnDevice;
/**
 * optional future setting. call this method with a option parameter improved usage experience of device.
 * @Parameter: the only one option you could setted is unitType , default is /kg/ value 0 , set 1 is means use unit /pound/ ,or set 2 declare you want to use /jin/(a unit of weight (=1/2 kilogram) ,@see ScaleUnit).
 you can set a NSDictionary value like @code\setOption:@{@"unitType":@2}\@code for this parameter; In addition , an NSNumber value like setOption:@1 is vaild in this version.
 */
- (void)setOption:(id)option;
- (void)readOption;

- (void)cleanData;
- (void)readSyscDataInfo;
- (void)syscDataStart;
- (void)syscDataStop;
- (void)syscDataBackup:(NSString *)seq;
@end
