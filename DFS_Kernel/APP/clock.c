/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): clock.c
**
** 描述(Description): 本文件定义Clock类成员函数实现
**
** 包含的函数(Included Function):
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
/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include "clock.h"
#ifdef WINDOWS
#include <time.h>
#else
#include <signal.h>
#include <time.h>
#endif

/*-----------------------------------------------------------------------------------------
**                                   Variable Definition
**-----------------------------------------------------------------------------------------
*/
/* 单例对象指针 */
Clock* _clock = nullptr;
/* 每月天数 */
unsigned char _days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/* 时钟周期 */
struct itimerval _period;
#ifdef WINDOWS
/* 定时器句柄 */
MMRESULT _timerId;
#endif

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 设置时钟周期 */
static void setPeriod(void* thiz, unsigned int second, unsigned long long microsecond);
/* 设置时钟处理函数 */
static void setClockHandler(void* thiz, ClockHandler handler);
/* 启动时钟 */
static bool start(void* thiz);
/* 停止时钟 */
static void stop(void* thiz);
#ifdef WINDOWS
/* 时钟中断处理函数 */
static void CALLBACK timerHandler(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
#else
/* 时钟中断处理函数 */
static void timerHandler(int param);
#endif

