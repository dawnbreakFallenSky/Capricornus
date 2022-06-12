/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): statusManager.cpp
**
** 描述(Description): 本文件定义statusManager类成员函数实现
**
** 包含的函数(Included Function):
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
/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include "statusManager.h"

/*-----------------------------------------------------------------------------------------
**                                   Variable Definition
**-----------------------------------------------------------------------------------------
*/
/* 日志指针 */
static Logger* _logger;
/* 无效状态 */
static DfsStatus _invalidStatus;
/* 状态表互斥锁 */
static CMutex _mtx;
/* 状态表 */
static CMap _statusMap;

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 获取状态 */
static Status* getStatus(void* thiz, const char* statusName, int initValue);

/*-----------------------------------------------------------------------------------------
**                                   Function Definition
**-----------------------------------------------------------------------------------------
*/
/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): StatusManager
**
** 描述(Description): 本函数为StatusManager类构造函数
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
**      Inory, 2022年6月8日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
StatusManager* CreateStatusManager(Logger* logger)
{
    StatusManager* statusManager = (StatusManager*)malloc(sizeof(StatusManager));
    if (NULL == statusManager) {
        printf("StatusManager::StatusManager()--create StatusManager error.\n");
    }
    else
    {
        _logger = logger;

        /* 成员初始化 */
        _mtx = *CreateCMutex();
        _statusMap = *CreateCMap(STATUS_NAME_SIZE, sizeof(DfsStatus*), strComparer);
        _invalidStatus = *CreateDfsStatus(STATUS_INVALID);
        /* 成员函数初始化 */
        statusManager->getStatus = getStatus;
    }

    return statusManager;
}
/* END of CreateStatusManager */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): ~StatusManager
**
** 描述(Description): 本函数为StatusManager类析构函数
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
**      Inory, 2022年6月8日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
void DestroyStatusManager(StatusManager* statusManager)
{
    CIterator iter, last;

#ifdef DEBUG
    printf("StatusManager::StatusManager()\n");
#endif
    /* 释放共享内存 */
    iter = _statusMap.begin(&_statusMap);
    last = _statusMap.end(&_statusMap);
    while (!ITER_EQUAL(iter, last)) {
        FREE_ARRAY(((CPair*)ITER_REF(iter))->_second);
    }
    _statusMap.clear(&_statusMap);
}
/* END of DestroyStatusManager */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): getStatus
**
** 描述(Description): 本函数实现获取状态的功能
**
** 输入参数(Input Parameter):
**      statusName , const char* 状态名称
**      initValue , int 初始值
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月8日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
Status* getStatus(void* thiz, const char* statusName, int initValue)
{
    Status* sta = nullptr;
    /* 锁定状态表互斥锁 */
    _mtx.lock(&_mtx);

    /* 判断状态是否有效,并返回状态值 */
    if (0 == _statusMap.count(&_statusMap, statusName))
    {
        DfsStatus* newStatus = CreateDfsStatus(initValue);

        if (NULL != newStatus)
        {
            _statusMap.insert(&_statusMap, statusName, newStatus);
            sta = newStatus->_status;
        }
        else
        {
            printf("StatusManager::getStatus()--create Status(%s) error.\n", statusName);
            KERNELLOGF("StatusManager::getStatus()--create Status(%s) error.\n", statusName);
            sta = &_invalidStatus;
        }
    }

    /* 解除状态表互斥锁 */
    _mtx.unlock(&_mtx);

    return sta;
}
/* END of getStatus */
