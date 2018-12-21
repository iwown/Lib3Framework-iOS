//
//  SolsticeImpl.h
//  BLEMidAutumn
//
//  Created by A$CE on 2017/10/11.
//  Copyright © 2017年 A$CE. All rights reserved.
//

#import "BLEquinox.h"
#import "BLESolstice.h"
#import <Foundation/Foundation.h>

typedef enum{
    SCQASCTypeNull = 0x00,
    SCQASCTypeFirst = 0x01,
    SCQASCTypeNormal = SCQASCTypeFirst,
    SCQASCTypeSyncDataStart = 0x02,
    SCQASCTypeSyncDataStop = 0x03,
    SCQASCTypeSyncDataDateData = 0x04,
    SCQASCTypeReadCState = 0x81,
    SCQASCTypeSyncBPDetailData = 0x8B01,
    SCQASCTypeSyncGPSDateInfo = 0x8C00,
    SCQASCTypeSyncGPSDetailData = 0x8C01,
    SCQASCTypeWriteAGPSData = 0x0e,
    SCQASCTypeCheckAGPSData = 0x8e,
    SCQASCTypeLast,
} SCQASCType;

@protocol SolsticeImplConnectDeleagte <NSObject>

@optional
- (void)connectDidLosedAndReConnectSoon;
@end

@protocol SolsticeImplDelegate <NSObject>

@optional
- (void)thereIsSomeCmdGotTimeOut:(SCQASCType)sType;
@end


@class BLEDataHandle;
@interface SolsticeImpl : NSObject<BLESolstice>

@property (nonatomic ,weak) CBPeripheral *peripheral;
@property (nonatomic ,weak) id<BLEquinox> bleQuinox;
@property (nonatomic ,weak) id<SolsticeImplConnectDeleagte>implConnectDelegate;
@property (nonatomic ,weak) id<SolsticeImplDelegate>implDelegate;
@property (class, nonatomic, readonly, copy) NSString *bleLogPath;

/**! cmd queue flag, return YES, cancel block action*/
@property (nonatomic, assign) BOOL cmdQueueCancelFlag;
@property (nonatomic, assign) BOOL longCmdsDuring; //长命令，需要拆包的
/**
 * Invoked after connected.
 * See also at @CODE{solsticeWithConnectedPeripheral:};
 @param peripheral the device 
 */
- (BOOL)startWithConnecttedPeriphral:(CBPeripheral *)peripheral;
- (void)reSetNotifyStatusBeforeUnbind;
- (void)releasePeriphral;

- (NSArray <NSString *>*)serviceUUIDs;
- (NSArray <CBUUID *>*)discoverUuids;

- (NSString *)writeServiceUuid;
- (NSString *)writeCharacteristicUuid;
- (BOOL)isWriteResp;
- (void)setNotification:(CBPeripheral *)peripheral enable:(BOOL)enable andCharcater:(NSString *)character;
- (void)setNotification:(CBPeripheral *)peripheral enable:(BOOL)enable andService:(NSString *)service andCharcater:(NSString *)character;


- (dispatch_queue_t)bleQueue;
- (void)suspendCmdQueueAfterSendCmd:(SCQASCType)type;
/* Call this methods when get finished with one commands*/
- (void)resumeCmdQueueAfterResponse;
- (void)releaseCmdQueueInUnbind;
- (NSInteger)timerDelaySeconds;
- (SCQASCType)scqascType:(NSString *)cmdStr;
- (NSDictionary *)scqascCmdsDict;

- (void)beginAfterNofityReady;
- (void)autoSettingAfterConnect;
- (BOOL)checkoutConnectState;
- (BOOL)checkoutCWorkState:(NSString *)cmdHeader;

/**! Reveive Data*/
- (void)braceletCmdReceive:(NSData *)rceData;
- (void)braceletReceiveHRData:(NSInteger)hr;
- (dispatch_queue_t)bleResponseQueue;

- (void)startSpecialData:(SD_TYPE)sdType day:(NSInteger)day;
- (void)writeToBracelet:(NSData *)writeData;
- (void)writeCharacteristicBysUUID:(NSString *)sUUID cUUID:(NSString *)cUUID data:(NSData *)data withResponse:(BOOL)with;

#pragma mark- LOG
- (void)writeBLELog:(NSData *)cmd andType:(bleLogType)type;

#pragma mark- Response
- (void)responseForReadFromDevice:(ZRReadResponse *)zrrResponse;
- (void)responseNormalHealthDataInfo:(ZRDataInfo *)zrDInfo;
- (void)responseNormalHealthData:(ZRHealthData *)zrhData;
- (void)responseDataProgress:(NSInteger)progress;
- (void)responseHeartRateData:(NSInteger)hr;

@end
