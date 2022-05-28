/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): processor.c
**
** 描述(Description): 本文件定义Processor类成员函数实现
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
#include "kernelInterface.h"

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 获取订阅事件ID列表 */
static CList* subscribeEventIdList(void* thiz);

/*-----------------------------------------------------------------------------------------
**                                   Function Definition
**-----------------------------------------------------------------------------------------
*/
/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): CreateProcessor
**
** 描述(Description): 本函数定义Processor类的构造函数
**
** 输入参数(Input Parameter):
**		context , Context* 程序上下文
**		param , const char* 参数
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年5月28日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
Processor* CreateProcessor(Context* context, const char* param)
{
	Processor* processor = (Processor*)malloc(sizeof(Processor));
	if (NULL == processor) {
		printf("Processor::Processor()--create processor error.\n");
	}
	else
	{
		/* 判断参数有效性并初始化成员变量 */
		if (NULL == context)
		{
			printf("Processor::Processor()--invalid 'context'.\n");
			return NULL;
		}
		else {
			processor->_context = context;
		}
		processor->_param = param;
		/* 成员初始化 */
		processor->_subscribeEventIdList = *CreateCList(sizeof(unsigned int), intComparer);
		/* 成员函数初始化 */
		processor->subscribeEventIdList = subscribeEventIdList;
	}

	return processor;
}
/* END of CreateProcessor */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): DestroyProcessor
**
** 描述(Description): 本函数定义Processor类的析构函数
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
**      Inory, 2022年5月28日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
void DestroyProcessor(Processor* processor)
{
#ifdef DEBUG
	printf("Processor::~Processor()\n");
#endif
}
/* END of DestroyProcessor */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): subscribeEventIdList
**
** 描述(Description): 本函数实现获取订阅事件ID列表的功能
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**		_subscribeEventIdList , CList* 订阅事件ID列表
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年5月28日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static CList* subscribeEventIdList(void* thiz)
{
	return &((Processor*)thiz)->_subscribeEventIdList;
}
/* END of subscribeEventIdList */
