/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): dfsStatus.h
**
** 描述(Description): 本文件定义dfsStatus类,该类实现状态接口
**
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2022年6月5日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2022年6月5日 创建本文件
**      $Revision$
**      $Date$
**      $Author$
**      $Log$
**
**-----------------------------------------------------------------------------------------
*/
#ifndef DFSSTATUS_H
#define DFSSTATUS_H

/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include "kernelInterface.h"
#include "../LIB/CSTLib/cMutex.h"

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)Status接口实例 */
/* 2) */
typedef struct SDfsStatus
{
    /* 设置状态值 */
    Status* (*setStatusValue)(void* thiz, int value);
    /* 获取状态值 */
    int (*getStatusValue)(void* thiz);

    /* 基类指针 */
    Status* _status;
    /* 状态互斥锁 */
    CMutex _mtx;
    /* 状态值 */
    int _value;
} DfsStatus;

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 构造函数 */
extern DfsStatus* CreateDfsStatus(int initValue);
/* 析构函数 */
extern void DestroyDfsStatus(DfsStatus* dfsStatus);

#endif /* DFSSTATUS_H */
