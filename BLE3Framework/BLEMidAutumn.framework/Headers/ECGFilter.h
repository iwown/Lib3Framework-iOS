//
//  ECGFilter.h
//  BLEMidAutumn
//
//  Created by west on 2020/3/10.
//  Copyright © 2020 A$CE. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ECGFilter : NSObject



/**
  重置ecg滤波器， 每一次测量都要重置滤波器
*/
- (void)resetECGFilter;

//参数传单个的值
/**
ecg滤波
@param ecg : ecg value data (int)
@return result value for filter ecg value
*/
- (int)filterECGValue:(int)ecg;


/**
 ecg滤波
 @param ecgArray ecg raw data array
 @return result for filter ECG raw data
 */
+ (NSArray *)filterEcgData:(NSArray *)ecgArray;




@end

NS_ASSUME_NONNULL_END
