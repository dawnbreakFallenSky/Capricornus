/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): commandManager.h
**
** 描述(Description): 本文件定义commandManager类,该类对应用程序的命令行交互进行管理
**
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2022年6月9日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2022年6月9日 创建本文件
**      $Revision$
**      $Date$
**      $Author$
**      $Log$
**
**-----------------------------------------------------------------------------------------
*/
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include "global.h"
#include "../LIB/CSTLib/cMap.h"
#include "../LIB/CSTLib/cMutex.h"

/*-----------------------------------------------------------------------------------------
**                                     Type Definition
**-----------------------------------------------------------------------------------------
*/
/* 命令行函数类型 */
typedef void (*CmdHandler)(void* thiz, int argc, char* argv[]);

/*-----------------------------------------------------------------------------------------
**                                     Macro Definition
**-----------------------------------------------------------------------------------------
*/
/* 命令行最大字符数,参数最大个数 */
#define CMD_SIZE_MAX    256
#define CMD_ARGC_MAX    128

/*-----------------------------------------------------------------------------------------
**                                     Type Definition
**-----------------------------------------------------------------------------------------
*/
/* 命令行指令保存信息 */
typedef struct _CmdInfo
{
    CmdHandler func;    /* 函数指针 */
    const char* comment;     /* 函数注释 */
} SCmdInfo;

/* 命令行运行方式枚举 */
typedef enum _CmdStyle
{
    NONE,               /* 无命令行 */
    TERMINAL,           /* 控制台终端模式 */
    REMOTE_TERMINAL,    /* 远程终端模式 */
    BROWSER             /* 浏览器模式 */
} ECmdStyle;

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)命令行管理 */
/* 2) */
typedef struct SCommandManager
{
    /* 停止命令行 */
    void (*stop)(void* thiz);
    /* 注册命令行指令 */
    void (*registerCommand)(void* thiz, const char* cmd, CmdHandler cmdHandler, const char* comment);

    /* 命令行指令列表 */
    CMap _cmdMap;
    /* 命令行指令列表读写互斥锁 */
    CMutex _mtx;
} CommandManager;

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 构造函数 */
extern CommandManager* CreateCommandManager(ECmdStyle runMode);
/* 析构函数 */
extern void DestroyCommandManager(CommandManager* commandManager);

#endif /* COMMANDMANAGER_H */
