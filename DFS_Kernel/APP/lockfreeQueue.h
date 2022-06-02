/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): lockfreeQueue.h
**
** 描述(Description): 本文件定义lockfreeQueue类模板
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
#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H

/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include <memory.h>
#include <malloc.h>
#include <stdio.h>
#include "global.h"

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)无锁队列(适用于单生产-单消费者) */
/* 2) */
typedef struct SLockfreeQueue
{
    /* 判断队列是否为空 */
    bool (*empty)(void* thiz);
    /* 判断队列是否已满 */
    bool (*full)(void* thiz);
    /* 获取队列头数据项 */
    const void* (*front)(void* thiz);
    /* 队列头数据项出列 */
    void (*pop)(void* thiz);
    /* 入列 */
    bool (*push)(void* thiz, const void* item);
    /* 获取队列中数据项个数 */
    unsigned int (*count)(void* thiz);
    /* 获取队列容量 */
    unsigned int (*capacity)(void* thiz);

    /* 数据项存储数组 */
    void* _items;
    /* 头游标 */
    unsigned int _head;
    /* 尾游标 */
    unsigned int _rear;
    /* 队列数据项个数 */
    unsigned int _len;
    /* 单一数据项长度 */
    unsigned int _itemSize;
} LockfreeQueue;

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 构造函数 */
extern LockfreeQueue* CreateLockfreeQueue(unsigned int len, unsigned int itemSize);
/* 析构函数 */
extern void DestroyLockfreeQueue(LockfreeQueue* lockfreeQueue);

#endif /* LOCKFREEQUEUE_H */
