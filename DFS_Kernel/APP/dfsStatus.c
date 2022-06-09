/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): dfsStatus.c
**
** 描述(Description): 本文件定义dfsStatus类成员函数实现
**
** 包含的函数(Included Function):
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
/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include "dfsStatus.h"

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 设置状态值 */
static Status* setStatusValue(void* thiz, int value);
/* 获取状态值 */
static int getStatusValue(void* thiz);

/*-----------------------------------------------------------------------------------------
**                                   Function Definition
**-----------------------------------------------------------------------------------------
*/
/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): CreateDfsStatus
**
** 描述(Description): 本函数为DfsStatus类构造函数
**
** 输入参数(Input Parameter):
**      initValue , int 状态初始值
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月6日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
DfsStatus* CreateDfsStatus(int initValue)
{
    DfsStatus* dfsStatus = (DfsStatus*)malloc(sizeof(DfsStatus));

    if (NULL == dfsStatus) {
        printf("DfsStatus::DfsStatus()--create dfsStatus error.\n");
    }
    else
    {
        dfsStatus->_status = (Status*)malloc(sizeof(Status));
        if (NULL == dfsStatus->_status) {
            return NULL;
        }

        dfsStatus->_value = initValue;
        /* 成员初始化 */
        dfsStatus->_mtx = *CreateCMutex();
        /* 成员函数初始化 */
        dfsStatus->getStatusValue = getStatusValue;
        dfsStatus->setStatusValue = setStatusValue;
        dfsStatus->_status->getStatusValue = getStatusValue;
        dfsStatus->_status->setStatusValue = setStatusValue;
    }

    return dfsStatus;
}
/* END of CreateDfsStatus */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): DestroyDfsStatus
**
** 描述(Description): 本函数为DfsStatus类析构函数
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
**      Inory, 2022年6月6日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
void DestroyDfsStatus(DfsStatus* dfsStatus)
{
#ifdef DEBUG
    printf("DfsStatus::~DfsStatus()\n");
#endif
}
/* END of ~DfsStatus */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): setStatusValue
**
** 描述(Description): 本函数实现设置状态值的功能
**
** 输入参数(Input Parameter):
**      value , int 状态值
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**      Status* 对象引用
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月6日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static Status* setStatusValue(void* thiz, int value)
{
    ((DfsStatus*)thiz)->_mtx.lock(&((DfsStatus*)thiz)->_mtx);

    ((DfsStatus*)thiz)->_value = value;

    ((DfsStatus*)thiz)->_mtx.unlock(&((DfsStatus*)thiz)->_mtx);

    return thiz;
}
/* END of setStatusValue */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): operator int
**
** 描述(Description): 本函数实现赋值运算符重载
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**      _value , int 状态值
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月6日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static int getStatusValue(void* thiz)
{
    return ((DfsStatus*)thiz)->_value;
}
/* END of getStatusValue */
