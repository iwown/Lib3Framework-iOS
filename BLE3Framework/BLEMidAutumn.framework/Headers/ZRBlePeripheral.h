//
//  ZRBlePeripheral.h
//  BLELib3
//
//  Created by 曹凯 on 16/1/4.
//  Copyright © 2016年 ZR. All rights reserved.
//
@class CBPeripheral;
@class ZRBlePeripheral;
#import "AutumnHeader.h"
#import <Foundation/Foundation.h>

@protocol ZRBlePeripheralDelegate <NSObject>
/*private method*/
- (void)zrBlePeripheralDidDiscoverServices:(ZRBlePeripheral *)zrBP;

@end

@interface ZRBlePeripheral : NSObject
/**
 The CBPeripheral object provided by CoreBluetooth Framework.
 */
@property (nonatomic ,strong) CBPeripheral *cbDevice;
/**
 The device's MAC address
 */
@property (nonatomic ,strong) NSString *mediaAC;
/**
 * Received Signal Strength Indicator
 * 接收信号强度指示器
 */
@property (nonatomic ,strong) NSNumber *RSSI;

@property (nonatomic ,strong) NSString *uuidString;
@property (nonatomic ,strong) NSString *deviceName;

/*服务UUID String*/
@property (nonatomic ,strong) NSArray <CBUUID *>*sUuidS;

@property (nonatomic ,weak) id<ZRBlePeripheralDelegate>zrpDelegate;

- (instancetype)initWith:(CBPeripheral *)cbPeripheral andAdvertisementData:(NSDictionary *)advertisementData andRSSINumber:(NSNumber *)rssi;
- (void)readSUuidS;

@end


typedef enum {
    DFUPlatformTi = 1,
    DFUPlatformNortic = 2,
    DFUPlatformDialog = 3,
    DFUPlatformMtk = 4,
} DFUPlatform;
@interface ZRDeviceInfo : NSObject
/**! System info od the Device*/
@property (nonatomic ,strong) NSString *protocolVer;   // 协议版本
@property (nonatomic ,strong) NSString *model;        // model string
@property (nonatomic ,strong) NSString *version;      // version string
@property (nonatomic ,readonly) NSUInteger versionValue;// integer value of version
@property (nonatomic ,readonly) NSUInteger oadMode;     // over air update mode
@property (nonatomic ,assign) NSUInteger batLevel;    // battery level
@property (nonatomic ,strong) NSString *seriesNo;      // series No. ble Addr for display
@property (nonatomic ,strong) NSString *bleAddr;      // series No. ble Addr for upload
@property (nonatomic ,readonly) NSUInteger hwVersion;  // integer value of hardware version

@property (nonatomic ,strong) NSString *hrVersion;    //心率版本号
@property (nonatomic ,assign) NSInteger hrVersionValue; //心率升级的版本号
@property (nonatomic ,strong) NSString *fontSupport;  //0 null ,1 e&&c ,2 128国
@property (nonatomic ,assign) NSUInteger protocalMap; //protocol map

@property (nonatomic ,strong) NSString *manuDate; //出厂日期
@property (nonatomic ,strong) NSString *factoryConf; //出厂配置

@property (nonatomic ,strong) NSData *snCode;      // probuff支持的SN码

+ (instancetype)defaultDeviceInfo;
- (void)updateDeviceInfo:(NSString *)deviceInfo;
- (void)updateBattery:(NSString *)batteryLevel;
- (void)updateHeartRateParam:(NSString *)body;

- (DFUPlatform)platformForDfu;
- (NSInteger)lowestPowerForDfu;
@end


@interface ZRReadResponse : NSObject

@property (nonatomic ,assign) BLECmdResponse cmdResponse;
@property (nonatomic ,assign) id data;

+ (instancetype)readResponse:(id)data andType:(BLECmdResponse)bleCR;

@end
