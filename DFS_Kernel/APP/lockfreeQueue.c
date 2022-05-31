/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): lockfreeQueue.c
**
** 描述(Description): 本文件定义lockfreeQueue类成员函数实现
**
** 包含的函数(Included Function):
**
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2022年5月31日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2022年5月31日 创建本文件
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
#include "lockfreeQueue.h"

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 判断队列是否为空 */
static bool empty(void* thiz);
/* 判断队列是否已满 */
static bool full(void* thiz);
/* 获取队列头数据项 */
static const void* front(void* thiz);
/* 队列头数据项出列 */
static void pop(void* thiz);
/* 入列 */
static bool push(void* thiz, const void* item);
/* 获取队列中数据项个数 */
static unsigned int count(void* thiz);
/* 获取队列容量 */
static unsigned int capacity(void* thiz);

