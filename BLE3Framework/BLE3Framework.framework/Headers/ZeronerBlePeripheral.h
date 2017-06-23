//
//  ZeronerBlePeripheral.h
//  BLELib3
//
//  Created by 曹凯 on 16/1/4.
//  Copyright © 2016年 Zeroner. All rights reserved.
//
@class CBPeripheral;
#import <Foundation/Foundation.h>

@interface ZeronerBlePeripheral : NSObject


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

- (instancetype)initWith:(CBPeripheral *)cbPeripheral andAdvertisementData:(NSDictionary *)advertisementData;

@end
