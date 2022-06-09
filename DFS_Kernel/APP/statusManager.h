/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): statusManager.h
**
** 描述(Description): 本文件定义statusManager类,该类用于管理应用程序所需的所有状态
**
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2022年6月7日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2022年6月7日 创建本文件
**      $Revision$
**      $Date$
**      $Author$
**      $Log$
**
**-----------------------------------------------------------------------------------------
*/
#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include "dfsStatus.h"
#include "logger.h"
#include "../LIB/CSTLib/cMap.h"

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)管理应用程序所需的状态 */
/* 2) */
typedef struct SStatusManager
{
    /* 获取状态 */
    Status* (*getStatus)(void* thiz, const char* statusName, int initValue);
} StatusManager;

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 构造函数 */
extern StatusManager* CreateStatusManager(Logger* logger);
/* 析构函数 */
extern void DestroyStatusManager(StatusManager* statusManager);

#endif /* STATUSMANAGER_H */
