//
//  ZeronerHealthData.h
//  BLE3Framework
//
//  Created by 曹凯 on 16/10/12.
//  Copyright © 2016年 Zeroner. All rights reserved.
//
#import "ZeronerBleHeader.h"
#import <Foundation/Foundation.h>

@interface ZeronerHealthData : NSObject

@property (strong ,nonatomic)NSDate *recordDate;
@property (copy ,nonatomic)NSString *dataFrom;

@end

@interface ZeronerSleepData : ZeronerHealthData

@end

@interface ZeronerSportData : ZeronerHealthData

@end


@interface ZeronerHeartRateData : ZeronerHealthData

@end


@interface ZeronerHRateHoursData : ZeronerHealthData

@property (strong ,nonatomic)NSArray *detailData;

@end

@interface ZeronerScaleData : ZeronerHealthData

@property (assign ,nonatomic)NSInteger seqNum;
@property (assign ,nonatomic)NSInteger impedance;
@property (assign ,nonatomic)NSInteger heartrate;
@property (assign ,nonatomic)float weight;
@property (assign ,nonatomic)ScaleUnit unit;

@end

