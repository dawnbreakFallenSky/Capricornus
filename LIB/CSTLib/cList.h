/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): cList.h
**
** 描述(Description): 本文件定义列表(list)在C语言编译环境下的封装接口
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
#ifndef _C_LIST_H
#define _C_LIST_H

/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include "cIterator.h"

/*-----------------------------------------------------------------------------------------
**                                     Type Declaration
**-----------------------------------------------------------------------------------------
*/
/* 列表结构体声明 */
typedef struct CList CList;

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)列表接口 */
/* 2) */
struct CList
{
	/* 列表 */
	void* _list;
	/* 比较函数 */
	comparer _keyCompare;
	/* 节点中数据占用内存大小 */
	int _nodeSize;

	/* 返回列表首节点迭代器 */
	CIterator (*begin)(CList* thiz);
	/* 返回列表尾节点迭代器 */
	CIterator (*end)(CList* thiz);
	/* 在列表尾部插入节点 */
	void (*push_back)(CList* thiz, const void* val);
	/* 删除相邻的重复元素 */
	void (*unique)(CList* thiz);
};

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 构造函数 */
extern CList* CreateCList(int nodeSize, comparer keyCmp);
/* 返回列表首节点迭代器 */
extern CIterator cListBegin(CList* thiz);
/* 返回列表末节点迭代器 */
extern CIterator cListEnd(CList* thiz);
/* 返回列表首节点的值 */
extern void* cListFront(CList* thiz);
/* 判断列表是否为空 */
extern int cListEmpty(CList* thiz);
/* 在列表末尾插入节点 */
extern void cListPushBack(CList* thiz, const void* val);
/* 在列表头部弹出节点 */
extern void cListPopFront(CList* thiz);
/* 删除重复相邻元素 */
extern void cListUnique(CList* thiz);

#endif /* _C_LIST_H */
