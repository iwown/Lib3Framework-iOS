//
//  BLEAutumn.h
//  BLESolstice
//
//  Created by A$CE on 2017/10/9.
//  Copyright © 2017年 A$CE. All rights reserved.
//

#import "BLEquinox.h"
#import "BLESolstice.h"
#import <Foundation/Foundation.h>

/*!
 *  @enum BLEProtocol
 *
 *  @discussion  Distinguish between data communication protocols
 *
 */
typedef NS_ENUM(NSInteger, BLEProtocol) {
    /** not Speciall*/
    BLEProtocol_Null = 0,
    /** Iwown bracelet early agreement, used in many devices*/
    BLEProtocol_EggRoll = 1,
    /** 2017 Designed for new platform devices such as wristwatches and headsets, with a wealth of data and higher hardware requirements*/
    BLEProtocol_Watch = 2,
    /** 2017 designed for the color screen bracelet agreement, content level and BLEProtocol_EggRoll similar*/
    BLEProtocol_Colorful = 3,
    /** If you are not sure what your equipment agreement, choose this*/
    BLEProtocol_Any = 8,
} ;

/**
 Core class, management search and connection, is also the entrance to the SDK.
 Sample @code{self.bleautumn = [BLEAutumn midAutumn:BLEProtocol_All];
 self.bleautumn.discoverDelegate = self;
 self.bleautumn.connectDelegate = self;}@endcode
 */
@interface BLEAutumn : NSObject

@property (nonatomic ,weak) id<BleDiscoverDelegate>discoverDelegate;
@property (nonatomic ,weak) id<BleConnectDelegate>connectDelegate;

/**
 Represents the current state of a CBManager. <CBManagerState> <CBCentralManagerState> used for below iOS10.
 @return Return to the state of the central manager, you can determine the status of Bluetooth.
 */
- (NSInteger)readManagerPowerState;

/**
 * Get the peripheral state
 */
- (CBPeripheralState)getPeripheralState;
/**
 * Get current protocol type;
 */
- (BLEProtocol)getBleProtocolType;

/**
 Scan device. You will get the discovered devices in the callback method of discoverDelegate @see solsticeDidDiscoverDeviceWithMAC:
 @param seconds Enter a number of seconds that you want to stop searching after later
 @param uuids The uuids you want to specify when searching
 @param options Same with options in @method scanForPeripheralsWithServices:options:
 */
- (void)startScanForTimeInternal:(NSTimeInterval)seconds
                 andServiceUuids:(NSArray <NSString *>*)uuids
                      andOptions:(NSDictionary<NSString *, id> *)options;
/**
 @see startScanForTimeInternal:andServiceUuids:andOptions:
 Default options is nil.
 @param seconds The uuids you want to specify when searching
 @param uuids Same with options in @method scanForPeripheralsWithServices:options:
 */
- (void)startScanForTimeInternal:(NSTimeInterval)seconds
                 andServiceUuids:(NSArray <NSString *>*)uuids;
/**
 @see startScanForTimeInternal:andServiceUuids:
 Default seconds is 10, uuids is nil, The SDK will choose the correct uuids for the  <BLEProtocol>.
 */
- (void)startScan;
/**
 Stop scan.
 The SDK calls the @see solsticeStopScan method if you have already implemented it.
 */
- (void)stopScan;

/**
 Bind and connect the device. What's the 'Band' is SDK will help you remember the uuid of this device, and reconnect it when you call the reConnectDevice method.
 @method solsticeDidConnectDevice: in <BleConnectDelegate>
 @param device The device you want to connected that had discovered
 */
- (void)bindDevice:(ZRBlePeripheral *)device;
/** Give up that bond*/
- (void)unbind;
/** Whether it is bound*/
- (BOOL)isBound;
/** That NSUuid.identifer that was remembered*/
- (NSString *)bindUuidStr;

/**
 Reconnect the bound device

 @return In most cases it is nil, unless you have not bound the device, you will get a "No binding device" prompt
 */
- (NSError *)reConnectDevice;
/** Cancel Connect*/
- (void)cancelConnect;

/*Class Method ,use @CODE{[[BLEAutumn alloc] init];} and @CODE{setBleProtocol:} is samed */
+ (instancetype)midAutumn:(BLEProtocol)blep;
- (void)setBleProtocol:(BLEProtocol)blep;

/**
 * If you need a <BLESolstice> object to communicate with device, after searching and connecting to the device with BLEAutumn, please using the this method initinal the object, or you have a peripheral device that has been connected without BLEAutumn, you can use the @see solsticeWithConnectedPeripheral: method.

 @return Follow the BLESolstice protocol for communication between the Operations Center and its surroundings
 */
- (id<BLESolstice>)solstice;

/**
 @see solstice

 @param zrPeripheral the Device had connected
 @return Follow the BLESolstice agreement object
 */
- (id<BLESolstice>)solsticeWithConnectedPeripheral:(ZRBlePeripheral *)zrPeripheral;

/**
 Call this method after initinal <BLESolstice> object; or ,you can not got any data callback from SDK.

 @param equinox The object that implements the <BLEquinox> protocol method, accepts data from sdk
 @return Returning NO means there is something wrong with BLESolstice's object
 */
- (BOOL)registerSolsticeEquinox:(id<BLEquinox>)equinox;
@end
