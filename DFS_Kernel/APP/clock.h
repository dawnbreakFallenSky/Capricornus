/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): clock.h
**
** 描述(Description): 本文件定义Clock类,该类实现定时功能
**
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2022年5月28日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2022年5月28日 创建本文件
**      $Revision$
**      $Date$
**      $Author$
**      $Log$
**
**-----------------------------------------------------------------------------------------
*/
#ifndef CLOCK_H
#define CLOCK_H

/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include <malloc.h>
#include <stdio.h>
#include "global.h"
#ifdef WINDOWS
#define NOMINMAX                    /* 禁用VC++中的min/max宏定义 */
#define WIN32_LEAN_AND_MEAN         /* 不定义此宏,Windows.h有可能包含winsock.h */
#include <windows.h>
#include <mmsystem.h>               /* Windows多媒体定时器头文件和库文件 */
#pragma comment(lib, "WinMM.lib")

/*-----------------------------------------------------------------------------------------
**                                     Type Definition
**-----------------------------------------------------------------------------------------
*/
/* 定时参数结构体 */
struct timeval
{
    unsigned int tv_sec;            /* Seconds */
    unsigned long long tv_usec;     /* Microseconds */
};
struct itimerval
{
    struct timeval it_interval;
    struct timeval it_value;
};
#else
/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include <sys/time.h>
#endif

/*-----------------------------------------------------------------------------------------
**                                     Type Definition
**-----------------------------------------------------------------------------------------
*/
/* 用户时钟处理函数指针类型 */
typedef void (*ClockHandler)(void);

/*-----------------------------------------------------------------------------------------
**                                     Macro Definition
**-----------------------------------------------------------------------------------------
*/
/* 定时周期默认值(秒+微秒) */
#define PERIOD_SECOND   0
#define PERIOD_USECOND  10000
/* 定时计数 */
#define INTERVAL_10MS   1
#define INTERVAL_20MS   2
#define INTERVAL_30MS   3
#define INTERVAL_40MS   4
#define INTERVAL_50MS   5
#define INTERVAL_100MS  10
#define INTERVAL_200MS  20
#define INTERVAL_500MS  50
#define INTERVAL_1S     100

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)产生周期定时信号,作为应用程序的时钟源 */
/* 2)单实例 */
typedef struct SClock
{
    /* 设置时钟周期 */
    void (*setPeriod)(void* thiz, unsigned int second, unsigned long long microsecond);
    /* 设置时钟处理函数 */
    void (*setClockHandler)(void* thiz, ClockHandler handler);
    /* 启动时钟 */
    bool (*start)(void* thiz);
    /* 停止时钟 */
    void (*stop)(void* thiz);

    /* 退出标志 */
    bool _exitFlag;
    /* 用户时钟处理函数指针 */
    ClockHandler _clockHandler;
    /* 应用程序运行时间(周期累加) */
    unsigned long long _appTime;
    /* 应用程序运行时utc时间 */
    long long _utcTimeBegin;
    /* 时间戳 */
    unsigned char _timestampBcd[8];
    unsigned char _timestampHex[8];
} Clock;

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 构造函数 */
extern Clock* CreateClockInstance(void);
/* 析构函数 */
extern void DestroyClock(Clock* clock);
/* 获取程序运行时间(单位为定时周期) */
extern unsigned long long ClockappTime(void);
/* 获取UTC时间(单位为S) */
extern long long ClockutcTime(void);
/* 获取时间戳 */
extern unsigned char* Clocktimestamp(void);
/* HEX-BCD码转换 */
extern unsigned char hexToBcd(unsigned char value);
extern unsigned char bcdToHex(unsigned char value);

#endif /* CLOCK_H */
