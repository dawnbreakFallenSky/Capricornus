/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): cThread.h
**
** 描述(Description): 本文件定义线程(thread)在C语言编译环境下的封装接口
**
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2022年5月22日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2022年5月22日 创建本文件
**      $Revision$
**      $Date$
**      $Author$
**      $Log$
**
**-----------------------------------------------------------------------------------------
*/
#ifndef _C_THREAD_H
#define _C_THREAD_H

/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include <windows.h>
#include <malloc.h>
#include <stdio.h>

/*-----------------------------------------------------------------------------------------
**                                     Type Definition
**-----------------------------------------------------------------------------------------
*/
/* 线程入口函数封装 */
typedef void (*CThreadFunc)(LPVOID para);

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)线程接口 */
/* 2) */
typedef struct SCThread
{
	/* 线程启动 */
	void (*run)(void* thiz);
	/* 线程挂起 */
	void (*join)(void* thiz);

#ifdef _WIN32
	/* 线程句柄 */
	HANDLE _thread;
	/* 线程入口函数 */
	CThreadFunc _address;
	/* 入口函数参数 */
	LPVOID _para;
#endif
} CThread;

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 构造函数 */
extern CThread* CreateCThread(CThreadFunc startAddress, LPVOID threadPara);

#endif /* _C_THREAD_H */
