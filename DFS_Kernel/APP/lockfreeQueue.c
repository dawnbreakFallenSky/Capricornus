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

/*-----------------------------------------------------------------------------------------
**                                   Function Definition
**-----------------------------------------------------------------------------------------
*/
/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): CreateLockfreeQueue
**
** 描述(Description): 本函数为LockfreeQueue类构造函数,初始化成员变量,创建存储数组
**
** 输入参数(Input Parameter):
**		len , unsigned int 队列数据项个数
**		itemSize , unsigned int 单一数据长度
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月1日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
LockfreeQueue* CreateLockfreeQueue(unsigned int len, unsigned int itemSize)
{
	LockfreeQueue* lockfreeQueue = (LockfreeQueue*)malloc(sizeof(LockfreeQueue));

    if (NULL == lockfreeQueue) {
        printf("Clock::Clock()--create clock error.\n");
    }
    else
    {
        /* 初始化成员变量 */
        lockfreeQueue->_head = 0;
        lockfreeQueue->_rear = 0;

        if (len < 2) {
            return NULL;
        }
        else
        {
            lockfreeQueue->_items = (unsigned char*)malloc(itemSize * len);
            if (NULL == lockfreeQueue->_items)
            {
                printf("LockfreeQueue::LockfreeQueue()--allocate memory for '_items' error.\n");
                return NULL;
            }
            memset((void*)lockfreeQueue->_items, 0, itemSize * len);
        }
        /* 初始化成员变量 */
        lockfreeQueue->_len = len;
        lockfreeQueue->_itemSize = itemSize;
        /* 初始化成员函数 */
        lockfreeQueue->empty = empty;
        lockfreeQueue->full = full;
        lockfreeQueue->front = front;
        lockfreeQueue->pop = pop;
        lockfreeQueue->push = push;
        lockfreeQueue->count = count;
        lockfreeQueue->capacity = capacity;
    }
}
/* END of CreateLockfreeQueue */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): ~LockfreeQueue
**
** 描述(Description): 本函数为LockfreeQueue类析构函数
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月1日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
void DestroyLockfreeQueue(LockfreeQueue* lockfreeQueue)
{
    FREE_ARRAY(lockfreeQueue->_items);
}
/* END of ~LockfreeQueue */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): empty
**
** 描述(Description): 本函数实现判断队列是否为空的功能
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**      bool true-为空 false-不为空
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月1日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static bool empty(void* thiz)
{
    /* 根据头尾游标判断队列是否为空 */
    if (((LockfreeQueue*)thiz)->_head == ((LockfreeQueue*)thiz)->_rear) {
        return true;
    }
    else {
        return false;
    }

}
/* END of empty */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): full
**
** 描述(Description): 本函数实现判断队列是否为满的功能
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**      bool true-为满 false-不为满
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月1日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static bool full(void* thiz)
{
    /* 根据头尾游标判断队列是否为满 */
    if (((LockfreeQueue*)thiz)->_head == LOOP(((LockfreeQueue*)thiz)->_rear + 1, ((LockfreeQueue*)thiz)->_len)) {
        return true;
    }
    else {
        return false;
    }
}
/* END of full */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): front
**
** 描述(Description): 本函数实现获取队列头数据项的功能
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**      const T& , 队列头数据项
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月1日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static const void* front(void* thiz)
{
    /* 返回队列头数据项 */
    return ((unsigned char*)((LockfreeQueue*)thiz)->_items + ((LockfreeQueue*)thiz)->_head * ((LockfreeQueue*)thiz)->_itemSize);
}
/* END of front */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): pop
**
** 描述(Description): 本函数实现弹出队列头数据项的功能
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月1日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static void pop(void* thiz)
{
    /* 队列不为空时,将头游标后移一项 */
    if (((LockfreeQueue*)thiz)->_head != ((LockfreeQueue*)thiz)->_rear) {
        ((LockfreeQueue*)thiz)->_head = LOOP(((LockfreeQueue*)thiz)->_head + 1, ((LockfreeQueue*)thiz)->_len);
    }
}
/* END of pop */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): push
**
** 描述(Description): 本函数实现压入队列数据项的功能
**
** 输入参数(Input Parameter):
**      item , const T&
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月1日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static bool push(void* thiz, const void* item)
{
    int offset;
    /* 根据头、尾游标判断队列是否为满 */
    if (((LockfreeQueue*)thiz)->_head == LOOP(((LockfreeQueue*)thiz)->_head + 1, ((LockfreeQueue*)thiz)->_len)) {
        return false;
    }

    offset = ((LockfreeQueue*)thiz)->_rear * ((LockfreeQueue*)thiz)->_itemSize;
    /* 将数据项存入队列 */
    memcpy((unsigned char*)((LockfreeQueue*)thiz)->_items + offset, item, ((LockfreeQueue*)thiz)->_itemSize);
    ((LockfreeQueue*)thiz)->_rear = LOOP(((LockfreeQueue*)thiz)->_rear + 1, ((LockfreeQueue*)thiz)->_len);

    return true;
}
/* END of push */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): count
**
** 描述(Description): 本函数实现获取队列中数据项个数的功能
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**      unsigned int 队列中数据项个数
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月1日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static unsigned int count(void* thiz)
{
    return LOOP(((LockfreeQueue*)thiz)->_len + ((LockfreeQueue*)thiz)->_rear - ((LockfreeQueue*)thiz)->_head, ((LockfreeQueue*)thiz)->_len);
}
/* END of count */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): capacity
**
** 描述(Description): 本函数实现获取队列容量的功能
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**      unsigned int 队列容量
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月1日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static unsigned int capacity(void* thiz)
{
    return (((LockfreeQueue*)thiz)->_len - 1);
}
/* END of capacity */
