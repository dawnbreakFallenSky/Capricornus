﻿/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): logger.h
**
** 描述(Description): 本文件定义Logger类,该类对应用程序的日志进行管理
**
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2022年6月2日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2022年6月2日 创建本文件
**      $Revision$
**      $Date$
**      $Author$
**      $Log$
**
**-----------------------------------------------------------------------------------------
*/
#ifndef LOGGER_H
#define LOGGER_H

/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include "kernelInterface.h"
#include "lockfreeQueue.h"
#include "../LIB/CSTLib/cMutex.h"
#include "../LIB/CSTLib/cCVariable.h"

/*-----------------------------------------------------------------------------------------
**                                     Macro Definition
**-----------------------------------------------------------------------------------------
*/
/* log信息队列大小 */
#define LOG_QUEUE_SIZE      512

/*-----------------------------------------------------------------------------------------
**                                     Type Definition
**-----------------------------------------------------------------------------------------
*/
/* log信息结构体 */
#pragma pack(1)
typedef struct _SLogInfo
{
    char info[LOG_INFO_SIZE + 1];   /* log信息 */
} SLogInfo;
#pragma pack()

/*-----------------------------------------------------------------------------------------
**                                     Macro Definition
**-----------------------------------------------------------------------------------------
*/
#define KERNELLOGF(...)     {char errStr[LOG_INFO_SIZE] = {0}; sprintf(errStr, __VA_ARGS__); _logger->log(_logger, errStr);}

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)日志管理 */
/* 2) */
typedef struct SLogger
{
    /* 记录日志 */
    void (*log)(void* thiz, const char* path);
    /* 刷新日志缓冲并停止记录 */
    void (*stop)(void* thiz);

    /* 日志文件描述符 */
    int _fd;
    /* 出错标志 */
    bool _hasError;
    /* 退出标志 */
    bool _exitFlag;
    /* 日志队列 */
    LockfreeQueue _logQueue;
    /* 日志队列读写同步锁 */
    CMutex _mtx;
    /* 条件变量 */
    CCVariable _cv;
} Logger;

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 构造函数 */
extern Logger* CreateLogger(const char* logPath);
/* 析构函数 */
extern void DestroyLogger(Logger* logger);

#endif /* LOGGER_H */