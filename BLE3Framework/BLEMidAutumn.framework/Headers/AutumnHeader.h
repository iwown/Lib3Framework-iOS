//
//  AutumnHeader.h
//  BLEMidAutumn
//
//  Created by A$CE on 2017/10/10.
//  Copyright © 2017年 A$CE. All rights reserved.
//

#ifndef AutumnHeader_h
#define AutumnHeader_h

#import <CoreBluetooth/CoreBluetooth.h>

#define BLE_MAIN_RESTORE_IDENTIFIER @"com.iwown.autumn"

#define PEDOMETER_NEW_SERVICE_UUID          @"FF20"
#define PEDOMETER_SPOTA_SERVICE_UUID        @"FEF5"  //Dialog升级服务
#define PEDOMETER_WATCH_SERVICE_UUID        @"18A0"
#define PEDOMETER_MTK_SERVICE_UUID          @"181A"
#define Z4_SERVICE_ID                       @"6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define PEDOMETER_PB_SERVICE_UUID           @"2E8C0001-2D91-5533-3117-59380A40AF8F"

#define HEARTRATE_SERVICE_ID                @"180D"
#define HEARTRATE_CHARACT_ID                @"2A37"
#define NEW_HEARTRATE_CHARACT_ID            @"2AFF"

#define HEARTRATE_SERVICE_UUID          @"180D"
#define HEARTRATE_CHARACT_UUID          @"2A37"
#define NEW_HEARTRATE_CHARACT_UUID      @"2AFF"

#define PEDOMETER_NEW_CHARACT_SET_UUID      @"FF21"
#define PEDOMETER_OLD_CHARACT_TEST          @"FF22"
#define PEDOMETER_NEW_CHARACT_TEST          @"FF23"
#define SCALE_S2_SERVICE_UUID               @"FF30"
#define SCALE_S2_WRITE_CHARACTERY_UUID      @"FF31"
#define SCALE_S2_READ_CHARACTERY_UUID       @"FF33"
#define PEDOMETER_MTK_CHARACT_FOTA_READ     @"2AA0"
#define PEDOMETER_MTK_CHARACT_FOTA_WRITE    @"2AA1"
#define Z4_CHARACTER_ID_NOTIFY              @"6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define Z4_CHARACTER_ID_WRITE               @"6E400002-B5A3-F393-E0A9-E50E24DCCA9E"

#define PEDOMETER_OLD_CHARACT_VALUE_PERFIX  @"22ff"
#define PEDOMETER_NEW_CHARACT_VALUE_PERFIX  @"23ff"
#define PEDOMETER_NFC_DATA_PREFIX           @"25ff"
#define SCALE_S2_CHARACT_VALUE_PERFIX       @"33ff"

/** Data types for different protocol communications*/
typedef NS_ENUM(NSInteger ,SD_TYPE) {
    SD_TYPE_Invalid = 0x00,
    SD_TYPE_FIRST = 0x01,
    SD_TYPE_SPORT = SD_TYPE_FIRST,
    SD_TYPE_SLEEP = 0x02,
    SD_TYPE_HEART_RATE = 0x03,
    SD_TYPE_ECG = 0x04,
    SD_TYPE_BLOOD_PRESSURE = 0x05,
    SD_TYPE_STEP = 0x06,//知格，当日1440分钟步数
    SD_TYPE_PPG = 0x07,
    
    SD_TYPE_DATA_INFO = 0x08,
    SD_TYPE_DATA_IT_6X = 0x09, //读取手表61|62|64的indextable
    
    SD_TYPE_RRI = 0x0A,
    
    SD_TYPE_Spo2 = 0x0B,  //血氧数据
    
    SD_TYPE_GNSS_SEGMENT = 0x10,
    SD_TYPE_GNSS_REAL_TIME = 0x11,
    
    SD_TYPE_DATA_NORMAL = 0x80, /**SD_TYPE_SPORT&&
                                 SD_TYPE_SLEEP(IF Support)&&
                                 SD_TYPE_HEART_RATE(IF Support)*/
    SD_TYPE_DATA_SUMMARY = 0xF1, //SUMMARY DATA FOR REVIEW
    SD_TYPE_LAST = 0xFF,
} ;

/**! State for sysc data */
typedef NS_ENUM(NSInteger ,KSyscDataState){
    KSyscDataStateBegin = 0,
    KSyscDataStateSummaryEnd,
    KSyscDataStateStepEnd,
    KSyscDataStateSportEnd,
    KSyscDataStateSleepEnd,
    KSyscDataStateHeartRateEnd,
    KSyscDataStateGPSDateInfoEnd,
    KSyscDataStateGPSEnd,
    KSyscDataStateBPDateInfoEnd,
    KSyscDataStateBPEnd,
    
    KSyscDataStateGNSSEnd,
    KSyscDataStateECGEnd,
    KSyscDataStateIsFinished ,
    KSyscDataDateIsFinished ,

    KSyscDataState61End = 0x80,     //61结束
    KSyscDataState62End,     //62结束
    KSyscDataState64End,     //64结束
    KSyscDataStateStartSyscF1Data,
    KSyscDataState68End
};


/**
 Device operation s events

 - BKN_SET_Normal: Reset
 - BKN_SET_SmartPhoto: Easy camera switch enter
 - BKN_GET_SmartPhoto: Easy camera switch action
 - BKN_GET_SearchPhone: Search phone action
 */
typedef NS_ENUM(NSInteger ,BKeyNotify) {
    BKN_SET_Normal = 0,
    BKN_SET_SmartPhoto = 1,
    BKN_GET_SmartPhoto = BKN_SET_SmartPhoto,
    BKN_GET_SearchPhone = 2,
};

typedef NS_ENUM(NSInteger ,SleepType) {
    SleepTypeStart = 1,
    SleepTypeEnd = 2,
    SleepTypeDeep = 3,
    SleepTypeLight = 4,
    SleepTypePlaced = 5,
    SleepTypeWake = 6,
};

/** Apply protocol heartbeat to inform the device status*/
typedef NS_ENUM(NSInteger ,Heartbeats) {
    HeartbeatsOn = 0,
    HeartbeatsOff = 1,
};

/**! SDK used ,Do not pay attention<##>*/
typedef NS_ENUM(NSInteger ,bleLogType) {
    BLE_LOG_RECEIVE    = 0,
    BLE_LOG_SEND  = 1,
    BLE_LOG_NORMAL  = 2,
    BLE_LOG_DEVELOPER = 3,
} ;

/**
 * BLECmdResponse
 * pare with braceletCmd_Command_t。
 */
typedef NS_ENUM(NSInteger ,BLECmdResponse) {
    CMD_RESPONSE_DEVICE_GET_INFORMATION = 0x00,
    CMD_RESPONSE_DEVICE_GET_BATTERY = 0x01,
    CMD_RESPONSE_DEVICE_RESET = 0x02,
    CMD_RESPONSE_DEVICE_UPDATE = 0x03,
    CMD_RESPONSE_DEVICE_REQ_REBOND = 0x04,
    CMD_RESPONSE_DEVICE_DO_REBOND = 0x05,
    CMD_RESPONSE_DEVICE_DND_MODE = 0x06,
    CMD_RESPONSE_DEVICE_WEATHER = 0x07,
    CMD_RESPONSE_DEVICE_SYNCDATA = 0x08,
    CMD_RESPONSE_DEVICE_HEARTBEAT_SIGNAL = 0x09,
    CMD_RESPONSE_DEVICE_HW_OPTION_SUPPERT = 0x0a, // Hardware Option type Support
    CMD_RESPONSE_DEVICE_MANUFACTURE_DATE = 0x0b,
    CMD_RESPONSE_DEVICE_FACTORY_CONF = 0x0c,
    CMD_RESPONSE_HEADSET_PARAM = 0x0e,
    
    CMD_RESPONSE_CONFIG_SET_TIME = 0x10,                 // Time
    CMD_RESPONSE_CONFIG_GET_TIME = 0x11,
    CMD_RESPONSE_CONFIG_SET_BLE = 0x12,                  // BLE
    CMD_RESPONSE_CONFIG_GET_BLE = 0x13,
    CMD_RESPONSE_CONFIG_SET_AC = 0x14,                   // AlarmClock
    CMD_RESPONSE_CONFIG_GET_AC = 0x15,
    CMD_RESPONSE_CONFIG_SET_NMA = 0x16,                  // No-Move-Alert
    CMD_RESPONSE_CONFIG_GET_NMA = 0x17,
    CMD_RESPONSE_CONFIG_SET_HW_OPTION = 0x18,            // Hardware Option
    CMD_RESPONSE_CONFIG_GET_HW_OPTION = 0x19,
    CMD_RESPONSE_CONFIG_GET_SPORT_LIST = 0x1a,          // Sport List
    CMD_RESPONSE_CONFIG_SET_SPORT_TARGET = 0x1b,
    CMD_RESPONSE_CONFIG_GET_SPORT_TARGET = 0x1c,
    CMD_RESPONSE_CONFIG_SET_SCHEDULE = 0x1d,        //schedule
    CMD_RESPONSE_CONFIG_GET_SCHEDULE = 0x1e,
    CMD_RESPONSE_CONFIG_GET_SCHEDULE_INFO = 0x1e0,
    CMD_RESPONSE_CONFIG_SGET_CONTACTS = 0x1f,       //contacts
    
    CMD_RESPONSE_DATALOG_SET_BODY_PARAM = 0x20,    // Body Parmameters
    CMD_RESPONSE_DATALOG_GET_BODY_PARAM = 0x21,    // Read body Parmameters
    CMD_RESPONSE_DATALOG_CLEAR_ALL = 0x22,
    CMD_RESPONSE_DATALOG_START_GET_DAY_DATA = 0x23,
    CMD_RESPONSE_DATALOG_GET_WARNING_PARAM = 0x24,
    CMD_RESPONSE_DATALOG_SET_GNSS = 0x25,
    CMD_RESPONSE_DATALOG_GET_GNSS = 0x26,
    CMD_RESPONSE_DATALOG_GET_CUR_DAY_DATA = 0x27,
    CMD_RESPONSE_DATALOG_GET_SPORTDATA = 0x28,
    CMD_RESPONSE_DATALOG_GET_CUR_SPORTDATA = 0x29,
    CMD_RESPONSE_DATALOG_GET_SLEEP_TEST = 0x2a,
    CMD_RESPONSE_DATALOG_GET_SMF_TEST = 0x2b,   //SMF -> sport minute freeze
    
    CMD_RESPONSE_MSG_UPLOAD = 0x30,
    CMD_RESPONSE_MSG_SINGLE_DOWNLOAD = 0x31,
    CMD_RESPONSE_MSG_MULTI_DOWNLOAD_START = 0x32,
    CMD_RESPONSE_MSG_MULTI_DOWNLOAD_CONTINUE = 0x33,
    CMD_RESPONSE_MSG_MULTI_DOWNLOAD_END = 0x34,
    /***DEPRECATED_ATTRIBUTE
     CMD_RESPONSE_MSG_MSG_SWITCH_SET = 0x35 ,
     CMD_RESPONSE_MSG_MSG_SWITCH_GET = 0x36 ,
     */
    CMD_RESPONSE_MSG_SPECIAL_LIST_SET = 0x37 ,
    CMD_RESPONSE_MSG_SPECIAL_LIST_GET = 0x38 ,
    CMD_RESPONSE_MSG_SPECIAL_LIST_GET_INFO = 0x380,
    
    CMD_RESPONSE_CTRL_KEYNOTIFY = 0x40,
    CMD_RESPONSE_CTRL_MOTOR = 0x41,
    CMD_RESPONSE_CTRL_SENSOR = 0x42,
    CMD_RESPONSE_CTRL_RECOGNITION = 0x43,
    CMD_RESPONSE_CTRL_SET_CUSTOM_OPTION = 0x4e,
    CMD_RESPONSE_CTRL_GET_CUSTOM_OPTION = 0x4f,
    
    CMD_RESPONSE_HEARTRATE_PARAM = 0x50,         //读取和设置心率参数
    CMD_RESPONSE_HEARTRATE_DATA = 0x51,          //分段心率数据同步
    CMD_RESPONSE_HEARTRATE_UPDATE = 0x52,        //心率模块升级控制
    CMD_RESPONSE_HEARTRATE_HOURS_DATA = 0x53,    //分时心率数据
    
    CMD_RESPONSE_HEALTH_DAY_DATA = 0x60,
    CMD_RESPONSE_HEALTH_MINUTE_DATA = 0x61,
    CMD_RESPONSE_GNSS_MINUTE_DATA = 0x62,
    CMD_RESPONSE_GNSS_MINUTE_DATA_TEST = 0x63,
    CMD_RESPONSE_GNSS_READ_TARGET = 0x67,
    
    CMD_RESPONSE_CLOCK_AND_SCHEDULE = 0x84,   //NSDictionary 闹钟&日程数组
    CMD_RESPONSE_USERINFO_GET = 0x85,//ZGUserInfoModle
    CMD_RESPONSE_STARTSETTING_GET = 0x8D,//ZRStartSetting
};

/**
 * If your smartband supportted this option ,that is meant this device might show message sign replaced a bluetooth icon noticed connectted state .If you don't want to ,Please implement
 \@method \bleParamSignSetting of \@protocol \BleConnectDelegate .use \@code \BLEParamSignConnect you will get bluetooth icon on screen of your smartband;
 * 如果你的手环支持这个协议，你将在手环上看到一个消息标示而不是一个表示连接状态的蓝牙图标。如果你不想要这样，请实现bleParamSignSetting方法，使用BLEParamSignConnect选项，你就可以在你手环屏幕上看到那个可爱的蓝牙图标了。
 */
typedef NS_ENUM(NSInteger, BLEParamSign) {
    /**! Compatible mode，recommended<##>*/
    BLEParamSignConnect  = 0,
    /**! Used for special version*/
    BLEParamSignMSGOption,
    /**! Android used */
    BLEParamSignMSGOptionDelay DEPRECATED_ATTRIBUTE,
};
/*!
 *  @enum BLECommunicateMode
 *
 *  @discussion <##>You can control the Bluetooth transmission speed, the default BLECommunicateModeLow, it is recommended that only use BLECommunicateModehigh when dealing with large files. Only the <BLEProtocol_colorful> support.
 *
 */
typedef NS_ENUM(NSInteger, BLECommunicateMode) {
    /**! Low speed*/
    BLECommunicateModeLow,
    /**! High speed*/
    BLECommunicateModeHigh,
};
/***
 *  Sport Type
 *  数据所属运动模式
 */
typedef NS_ENUM(NSInteger, sd_sportType) {
    SD_SPORT_TYPE_SLEEP                          = 0x00 ,//睡眠
    
    SD_SPORT_TYPE_WALKING                        = 0x01 ,//走路
    SD_SPORT_TYPE_NORMAL_MODE                    = 0x01 ,//彩屏非运动模式  
    SD_SPORT_TYPE_SITE_UPS                       = 0x02 ,//仰卧起坐
    SD_SPORT_TYPE_PUSH_UP                        = 0x03 ,//俯卧撑
    SD_SPORT_TYPE_ROPE_SKIPPING                  = 0x04 ,//跳绳
    SD_SPORT_TYPE_MOUNTAINEERING                 = 0x05 ,//登山
    SD_SPORT_TYPE_PULL_UP                        = 0x06 ,//引体向上
    SD_SPORT_TYPE_RUNNING                        = 0x07 ,//跑步
    SD_SPORT_TYPE_APP_JIANMEICAO                 = 0x08 ,//健美操
    
    SD_SPORT_TYPE_CRUNCHES                       = 0x09 ,//卷腹
    SD_SPORT_TYPE_DEEP_SQUAT                     = 0x0a ,//深蹲
    SD_SPORT_TYPE_AIR_PEDAL                      = 0x0b ,//空中蹬车
    SD_SPORT_TYPE_HIP_BRIDGE                     = 0x0c ,//臀桥
    SD_SPORT_TYPE_DUMB_BELL                      = 0x0d ,//哑铃锻炼
    SD_SPORT_TYPE_APP_KAIHETIAO                  = 0x0e ,//开合跳
    SD_SPORT_TYPE_APP_JIANBUDUN                  = 0x0f ,//箭步蹲
    SD_SPORT_TYPE_SLIMMING_EXERCISE              = 0x10 ,//蹦床
    SD_SPORT_TYPE_CLIMB_STAIRS                   = 0x11 ,//爬楼梯
    
    SD_SPORT_TYPE_APP_BUYU                       = 0x12 ,//捕鱼
    SD_SPORT_TYPE_APP_SHOULIE                    = 0x13 ,//狩猎
    SD_SPORT_TYPE_APP_JIAWU                      = 0x14 ,//家务活动
    SD_SPORT_TYPE_APP_JIATINGXIULI               = 0x15 ,//家庭修理
    SD_SPORT_TYPE_APP_ANJINGBUDONG               = 0x16 ,//安静不动
    SD_SPORT_TYPE_APP_XUEXI                      = 0x17 ,//学习
    SD_SPORT_TYPE_APP_CAOPINGTINGXUE             = 0x18 ,//草坪庭院
    SD_SPORT_TYPE_APP_JIAOTAN                    = 0x19 ,//交谈
    SD_SPORT_TYPE_APP_YUEQIYANZOU                = 0x1a ,//乐器演奏
    SD_SPORT_TYPE_APP_ZHIYEHUODONG               = 0x1b ,//职业活动
    SD_SPORT_TYPE_APP_ZILIHUODONG                = 0x1c ,//自理活动
    SD_SPORT_TYPE_APP_XINGSHENGHUO               = 0x1d ,//性生活
    SD_SPORT_TYPE_APP_XIUXIAN                    = 0x1e ,//休闲
    
    SD_SPORT_TYPE_APP_GONGLVZIXINGCHE            = 0x91 ,//功率自行车
    SD_SPORT_TYPE_APP_TABUJI                     = 0x92 ,//踏步机
    SD_SPORT_TYPE_APP_HUABAN                     = 0x93 ,//滑板
    SD_SPORT_TYPE_APP_PULATI                     = 0x94 ,//普拉提
    SD_SPORT_TYPE_APP_SHIPINYUNDONG              = 0x95 ,//视频运动
    SD_SPORT_TYPE_APP_TAIQIU                     = 0x96 ,//台球
    SD_SPORT_TYPE_APP_QUANJI                     = 0x97 ,//拳击
    SD_SPORT_TYPE_APP_JIANLIAN                   = 0x98 ,//教练
    SD_SPORT_TYPE_APP_ZHIBIAO                    = 0x9a ,//掷镖
    SD_SPORT_TYPE_APP_TUOLABISAI                 = 0x9b ,//拖拉比赛
    SD_SPORT_TYPE_APP_JIANSHU                    = 0x9c ,//剑术
    SD_SPORT_TYPE_APP_GANLANQIU                  = 0x9d ,//橄榄球
    SD_SPORT_TYPE_APP_FEIPAN                     = 0x9e ,//飞盘
    SD_SPORT_TYPE_APP_GAOERFU                    = 0x9f ,//高尔夫
    SD_SPORT_TYPE_APP_TICAO                      = 0xa0 ,//体操
    SD_SPORT_TYPE_APP_SHOUQIU                    = 0xa1 ,//手球
    SD_SPORT_TYPE_APP_HUAXIANG                   = 0xa2 ,//滑翔
    SD_SPORT_TYPE_APP_QUGUNQIU                   = 0xa3 ,//曲棍球
    SD_SPORT_TYPE_APP_BINGQIU                    = 0xa4 ,//冰球
    SD_SPORT_TYPE_APP_QIMA                       = 0xa5 ,//骑马
    SD_SPORT_TYPE_APP_HUILIQIU                   = 0xa6 ,//回力球
    SD_SPORT_TYPE_APP_WUSHU                      = 0xa7 ,//武术
    SD_SPORT_TYPE_APP_YUEYE                      = 0xa8 ,//越野
    SD_SPORT_TYPE_APP_BANQIU                     = 0xa9 ,//板球
    SD_SPORT_TYPE_APP_MANQIU                     = 0xaa ,//马球
    SD_SPORT_TYPE_APP_TIAOSAN                    = 0xab ,//跳伞
    SD_SPORT_TYPE_APP_LEIQIU                     = 0xac ,//垒球
    SD_SPORT_TYPE_APP_BIQIU                      = 0xad ,//壁球
    SD_SPORT_TYPE_TAIJI                          = 0xae ,//太极
    SD_SPORT_TYPE_APP_SHUAIJIAO                  = 0xaf ,//摔跤
    SD_SPORT_TYPE_APP_JIAOSHI                    = 0xb0 ,//驾驶
    SD_SPORT_TYPE_APP_SHEJIAN                    = 0xb1 ,//射箭
    SD_SPORT_TYPE_BRISK_WALKING                  = 0xb5 ,//快走
    SD_SPORT_TYPE_APP_JIACHUAN                   = 0xb6 ,//驾船
    SD_SPORT_TYPE_APP_PIHUATING                  = 0xb7 ,//皮划艇
    SD_SPORT_TYPE_APP_FANCHUAN                   = 0xb8 ,//帆船
    SD_SPORT_TYPE_APP_HUASHUI                    = 0xb9 ,//滑水
    SD_SPORT_TYPE_APP_QIANSHUI                   = 0xba ,//潜水
    SD_SPORT_TYPE_APP_CHONGLANG                  = 0xbb ,//冲浪
    SD_SPORT_TYPE_APP_SHUIQIU                    = 0xbc ,//水球
    SD_SPORT_TYPE_APP_TIAOXUE                    = 0xbd ,//跳雪
    SD_SPORT_TYPE_APP_XUEQIAO                    = 0xbe ,//雪橇
    SD_SPORT_TYPE_APP_XUESHANGQICHE              = 0xbf ,//雪上骑车
    SD_SPORT_TYPE_APP_TIAOSHUI                   = 0xc0 ,//跳水
    
    SD_SPORT_TYPE_MASK                           = 0x80 ,//掩码
    
    SD_SPORT_TYPE_GROUPCLASS                     = 0x30 ,//团课
    SD_SPORT_TYPE_PERSONALEDUCATION              = 0x31 ,//私教
    SD_SPORT_TYPE_TREADMILL                      = 0x32 ,//跑步机
    SD_SPORT_TYPE_FREETRAINING                   = 0x33 ,//自由训练
    SD_SPORT_TYPE_BADMINTON                      = 0x80 ,//羽毛球
    SD_SPORT_TYPE_BASKETBALL                     = 0x81 ,//篮球
    SD_SPORT_TYPE_FOOTBALL                       = 0x82 ,//足球
    SD_SPORT_TYPE_SWIM                           = 0x83 ,//游泳
    SD_SPORT_TYPE_VOLLEYBALL                     = 0x84 ,//排球
    SD_SPORT_TYPE_TABLE_TENNIS                   = 0x85 ,//乒乓球
    SD_SPORT_TYPE_BOWLING                        = 0x86 ,//保龄球
    SD_SPORT_TYPE_TENNIS                         = 0x87 ,//网球
    SD_SPORT_TYPE_CYCLING                        = 0x88 ,//骑行
    SD_SPORT_TYPE_SKI                            = 0x89 ,//滑雪
    SD_SPORT_TYPE_SKATE                          = 0x8a ,//滑冰
    SD_SPORT_TYPE_ROCK_CLIMBING                  = 0x8b ,//攀岩
    SD_SPORT_TYPE_GYM                            = 0x8c ,//健身房健身
    SD_SPORT_TYPE_DANCE                          = 0x8d ,//跳舞
    SD_SPORT_TYPE_TABLET_SUPPORT                 = 0x8e ,//平板撑
    SD_SPORT_TYPE_GYM_EXERCISE                   = 0x8f ,//健身操
    SD_SPORT_TYPE_YOGA                           = 0x90 ,//瑜伽
    SD_SPORT_TYPE_SHUTTLECOCK                    = 0x91 ,//毽球
    SD_SPORT_TYPE_ALLBALL                        = 0x92 ,//所有球类
    SD_SPORT_TYPE_POWALKING                      = 0x93 ,//健步走
    SD_SPORT_TYPE_GOLF                           = 0x94 ,//高尔夫
    SD_SPORT_TYPE_CANOEING                       = 0x95 ,//皮划艇
    
    SD_SPORT_TYPE_HEART_RATE                     = 0xf0 ,//心率
    
    SD_SPORT_TYPE_OTHER                          = 0xFF ,//其他'
    SD_SPORT_TYPE_WALKING_SAVE                   = 0x100 ,//步行

} ;


typedef void (^ReadAlarmClockResponse)(NSArray *);
typedef void (^ReadSheduleResponse)(NSDictionary *);

#define TEST_PARSE_LOG_A(val) \
if ([IVDataParseTool isTest]){ \
NSLog(@"%s ==>>body:%@",__FUNCTION__,val); \
}

#endif /* AutumnHeader_h */
