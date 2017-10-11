//
//  ZeronerBleHeader.h
//  BLELib3
//
//  Created by 曹凯 on 16/1/4.
//  Copyright © 2016年 Zeroner. All rights reserved.
//


#ifndef ZeronerBleHeader_h
#define ZeronerBleHeader_h

/**
 *  #ifndef
 */
#pragma mark- iOS_PLATFORM_INFO
#define iOS9_0 ([UIDevice currentDevice].systemVersion.floatValue >= 9.0f)

#pragma mark- BLE_DEVICE_INFO
#define PEDOMETER_NEW_SERVICE_UUID          @"FF20"
#define PEDOMETER_SPOTA_SERVICE_UUID        @"FEF5"  //Dialog升级服务
#define PEDOMETER_WATCH_SERVICE_UUID        @"18A0"
#define PEDOMETER_MTK_SERVICE_UUID          @"181A"

#define PEDOMETER_NEW_CHARACT_SET_UUID      @"FF21"
#define PEDOMETER_OLD_CHARACT_TEST          @"FF22"
#define PEDOMETER_NEW_CHARACT_TEST          @"FF23"
#define PEDOMETER_NFC_CHARACT_TEST          @"FF25"
#define SCALE_S2_SERVICE_UUID               @"FF30"
#define SCALE_S2_WRITE_CHARACTERY_UUID      @"FF31"
#define SCALE_S2_READ_CHARACTERY_UUID       @"FF33"
#define PEDOMETER_MTK_CHARACT_FOTA_READ     @"2AA0"
#define PEDOMETER_MTK_CHARACT_FOTA_WRITE    @"2AA1"


#define PEDOMETER_OLD_CHARACT_VALUE_PERFIX  @"22ff"
#define PEDOMETER_NEW_CHARACT_VALUE_PERFIX  @"23ff"
#define PEDOMETER_NFC_DATA_PREFIX           @"25ff"
#define SCALE_S2_CHARACT_VALUE_PERFIX       @"33ff"

typedef enum{
    kBLEstateDisConnected = 0,
    kBLEstateDidConnected ,
    kBLEstateBindUnConnected ,
}kBLEstate;

typedef enum {
    BLE_LOG_RECEIVE    = 0,
    BLE_LOG_SEND  = 1,
    BLE_LOG_NORMAL  = 2,
} bleLogType;

typedef enum {
    ScaleUnitKG = 0,
    ScaleUnitPound ,
    ScaleUnitJin ,
} ScaleUnit;

/*********************************************************************
 * MACROS
 */
#define MAKE_HEADER(grp, cmd)      ((((Byte)grp & 0x0f) << 4) | ((Byte)cmd & 0x0f))
#define GET_GROUP(header)          (((Byte)header & 0xf0) >> 4)
#define GET_COMMAND(header)        ((Byte)header & 0x0f)
/*********************************************************************
 * TYPEDEFS
 */
typedef enum {
    CMD_GRP_DEVICE = 0,               // RESET, UPDATE, INFORMATION, see @CMD_ID_DEVICE_
    CMD_GRP_NFC = CMD_GRP_DEVICE,
    CMD_GRP_CONFIG,               // TIME_SETTINGS, BLE_SETTING, AC_SETTING, NMA_SETTING, GNSS_SETTING
    CMD_GRP_DATALOG,              // CLEAR, GET, PEDO_SETTING
    CMD_GRP_SCALE = CMD_GRP_DATALOG,
    CMD_GRP_MSG,                  // UPLOAD, DOWNLOAD
    CMD_GRP_CTRL,
    CMD_GRP_HEARTRATE,            //心率
    CMD_GRP_GNSS,                 //GNSS, 健康数据
} braceletCmd_Group_t;

typedef enum {
    CMD_ID_DEVICE_GET_INFORMATION = 0,
    CMD_ID_DEVICE_NFC_SET_AND_GET = CMD_ID_DEVICE_GET_INFORMATION,
    CMD_ID_DEVICE_GET_BATTERY = 1,
    CMD_ID_DEVICE_RESET = 2,
    CMD_ID_DEVICE_UPDATE = 3,
    CMD_ID_DEVICE_REQ_REBOND = 4,
    CMD_ID_DEVICE_DO_REBOND = 5,
    CMD_ID_DEVICE_DND_MODE = 6,
    CMD_ID_DEVICE_WEATHER = 7,
    CMD_ID_DEVICE_SYNCDATA = 8,
    CMD_ID_DEVICE_HEARTBEAT_SIGNAL = 9,
    CMD_ID_DEVICE_HW_OPTION_SUPPERT = 10, // Hardware Option type Support
    
    CMD_ID_CONFIG_SET_TIME = 0,                 // Time
    CMD_ID_CONFIG_GET_TIME = 1,
    CMD_ID_CONFIG_SET_BLE = 2,                  // BLE
    CMD_ID_CONFIG_GET_BLE = 3,
    CMD_ID_CONFIG_SET_AC = 4,                   // AlarmClock
    CMD_ID_CONFIG_GET_AC = 5,
    CMD_ID_CONFIG_SET_NMA = 6,                  // No-Move-Alert
    CMD_ID_CONFIG_GET_NMA = 7,
    CMD_ID_CONFIG_SET_HW_OPTION = 8,            // Hardware Option
    CMD_ID_CONFIG_GET_HW_OPTION = 9,
    CMD_ID_CONFIG_GET_SPORT_LIST = 10,          // Sport List
    CMD_ID_CONFIG_SET_SPORT_TARGET = 11,
    CMD_ID_CONFIG_GET_SPORT_TARGET = 12,
    CMD_ID_CONFIG_SET_SCHEDULE = 13,        //schedule
    CMD_ID_CONFIG_GET_SCHEDULE = 14,
    CMD_ID_CONFIG_SGET_CONTACTS = 15,       //contacts
    
    CMD_ID_DATALOG_SET_BODY_PARAM = 0,    // Body Parmameters
    CMD_ID_DATALOG_GET_BODY_PARAM = 1,    // Read body Parmameters
    CMD_ID_DATALOG_CLEAR_ALL = 2,
    CMD_ID_HEART_RATE_SET_WARNING_PARAM = 3,
    CMD_ID_HEART_RATE_GET_WARNING_PARAM = 4,
    CMD_ID_GNSS_SETTING = 5,
    CMD_ID_GNSS_GET_SETTING = 6,
    CMD_ID_DATALOG_GET_CUR_DAY_DATA = 7,
    CMD_ID_DATALOG_GET_SPORTDATA = 8,
    CMD_ID_DATALOG_GET_CUR_SPORTDATA = 9,
    CMD_ID_DATALOG_GET_SLEEP_TEST = 10,
    CMD_ID_DATALOG_GET_SMF_TEST = 11,   //SMF -> sport minute freeze
    
    CMD_ID_MSG_UPLOAD = 0,
    CMD_ID_MSG_SINGLE_DOWNLOAD = 1,
    CMD_ID_MSG_MULTI_DOWNLOAD_START = 2,
    CMD_ID_MSG_MULTI_DOWNLOAD_CONTINUE = 3,
    CMD_ID_MSG_MULTI_DOWNLOAD_END = 4,
    /***DEPRECATED_ATTRIBUTE
     CMD_ID_MSG_MSG_SWITCH_SET = 5 ,
     CMD_ID_MSG_MSG_SWITCH_GET = 6 ,
     */
    CMD_ID_MSG_SPECIAL_LIST_SET = 7 ,
    CMD_ID_MSG_SPECIAL_LIST_GET = 8 ,
    
    CMD_ID_CTRL_KEYNOTIFY = 0,
    CMD_ID_CTRL_MOTOR = 1,
    CMD_ID_CTRL_SENSOR = 2,
    CMD_ID_CTRL_RECOGNITION = 3,
    CMD_ID_CTRL_SET_CUSTOM_OPTION = 14,
    CMD_ID_CTRL_GET_CUSTOM_OPTION = 15,
    
    CMD_ID_HEARTRATE_PARAM = 0,         //读取和设置心率参数
    CMD_ID_HEARTRATE_DATA = 1,          //分段心率数据同步
    CMD_ID_HEARTRATE_UPDATE = 2,        //心率模块升级控制
    CMD_ID_HEARTRATE_HOURS_DATA = 3,    //分时心率数据
    
    CMD_ID_HEALTH_DAY_DATA = 0,
    CMD_ID_HEALTH_MINUTE_DATA = 1,
    CMD_ID_GNSS_MINUTE_DATA = 2,
    CMD_ID_GNSS_MINUTE_DATA_TEST = 3,
    CMD_ID_ECG_MINUTE_DATA = 4,
    CMD_ID_EPO_DOWNLOAD_START = 5,
} braceletCmd_Command_t;

/***
 *  Sport Type
 *  数据所属运动模式
 */
typedef enum {
    SD_SPORT_TYPE_SLEEP                          = 0x00 ,//睡眠
    
    SD_SPORT_TYPE_WALKING                        = 0x01 ,//走路
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
    
    SD_SPORT_TYPE_WALKING_SAVE                   = 0x100 ,//走路
} sd_sportType;

/*** BraceletType
 * These declarator is work fo smartband who used naming format like {Bracel*-XXXX} ,If your smart band have not use this naming format ,please ignore this enum
 */
typedef enum {
    BraceletTypeUnknown         = 0x00,
    
    BraceletTypeI5              = 0x01,
    BraceletTypeV6              = 0x02,
    BraceletTypeI7              = 0x03,
    BraceletTypeI5PRO           = 0x04,
    BraceletTypeI6PRO           = 0x05,
    BraceletTypeR1              = 0x06,
    BraceletTypeI6HR            = 0x13,
    BraceletTypeI6NH            = 0x15,
    BraceletTypeI6H9            = 0x16,
    BraceletTypeWatchF1         = 0x17,
} BraceletType;


#define test
#define TEST_PARSE_LOG_A(val) \
if ([IVDataParseTool isTest]){ \
NSLog(@"%s ==>>body:%@",__FUNCTION__,val); \
}

#endif /* ZeronerBleHeader_h */
