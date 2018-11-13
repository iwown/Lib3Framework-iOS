//
//  ZRDataTypes.h
//  BLEMidAutumn
//
//  Created by ogogo on 2017/10/23.
//  Copyright © 2017年 A$CE. All rights reserved.
//

#ifndef ZRDataTypes_h
#define ZRDataTypes_h

typedef enum  {
    Direct = 0,
    Andrdoid = 1,
    iOS = 2,
    NotSupported = 3
} ZRConnectionType;

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
}RecorDate;

typedef struct {
    RecorDate rcDate;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}RecortDate;

typedef struct {
    uint8_t totaldays;
    uint8_t storeLocation[7];
    RecorDate storeDates[7];
}bh_date_t;

typedef struct {
    uint8_t totaldays;
    RecortDate storeDates[7];
}DateStoreInfo;

typedef struct {
    uint8_t days[36];
}date_array_t;

typedef struct {
    uint16_t curYear;
    uint8_t curMonth;
    uint8_t curDay;
    uint16_t curDayStepLow;
    uint16_t curDayCalorie;
    uint16_t curDayDistance;
    uint16_t curExerciseMinute;
    uint16_t curSleepMinute;
    uint8_t curDayStepHigh;
    uint8_t curLatestHeart;
}bh_totalinfo_t;

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint16_t step;
    uint16_t calorie;
    uint16_t distance;
    uint16_t exerciseMinutes;
    uint16_t sleepMinutes;
    uint8_t heartrate;
}Total_Detail_Data;

typedef enum {
    Normal_Mode = 0,
    Run_Mode = 1,
    Bike_Mode = 2,
    Badminton_Mode = 3,
    Basketball_Mode = 4,
    Football_Mode = 5,
    Pingpong_Mode = 6,
    Tennis_Mode = 7,
    End_Mode
}practice_type;

typedef struct {
    uint16_t sportMode;
    uint16_t minutesCount;
    uint8_t startHour;
    uint8_t startMinutes;
    uint8_t endHour;
    uint8_t endMinutes;
    uint32_t step;
    uint16_t distance;
    uint16_t calorie;
    uint8_t maxSpm;
    uint8_t avgSpm;
    uint8_t maxHeart;
    uint8_t avgHeart;
}bh_exercise_t;

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint32_t exercise_length;
    bh_exercise_t exerciseInfo[10];
}bh_exercise_total_t;

typedef struct {
    uint8_t data[1608];
}practice_array_t;

#endif /* ZRDataTypes_h */
