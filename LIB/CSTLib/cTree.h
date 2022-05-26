/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): cTree.h
**
** 描述(Description): 本文件定义红黑树(redblacktree)在C语言编译环境下的封装接口
**
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2022年5月24日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2022年5月24日 创建本文件
**      $Revision$
**      $Date$
**      $Author$
**      $Log$
**
**-----------------------------------------------------------------------------------------
*/
#ifndef _C_TREE_H
#define _C_TREE_H

/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include "cFunction.h"

/*-----------------------------------------------------------------------------------------
**                                     Macro Definition
**-----------------------------------------------------------------------------------------
*/
/* 节点颜色 */
#define RED		0
#define BLACK	1
/* 交换宏 */
#define	C_SWAP(X, Y, TMP)	do {(TMP) = (X); (X) = (Y); (Y) = (TMP);} while(0)

/*-----------------------------------------------------------------------------------------
**                                     Type Declaration
**-----------------------------------------------------------------------------------------
*/
/* 红黑树节点结构体声明 */
typedef struct CRBTreeNode CRBTreeNode;

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)红黑树节点接口 */
/* 2) */
struct CRBTreeNode
{
	/* 颜色 */
	int _color;
	/* 父节点 */
	CRBTreeNode* _parent;
	/* 左节点 */
	CRBTreeNode* _left;
	/* 右节点 */
	CRBTreeNode* _right;
	/* 键值对 */
	void* _pair;
};

/*-----------------------------------------------------------------------------------------
**                                     Type Declaration
**-----------------------------------------------------------------------------------------
*/
/* 红黑树结构体声明 */
typedef struct CRBTree CRBTree;

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)红黑树接口 */
/* 2) */
struct CRBTree
{
	/* 头节点 */
	CRBTreeNode* _header;
	/* 比较函数 */
	comparer _keyCompare;
	/* 寻找键值函数 */
	CUnaryFunction _keyofValue;
	/* 计数 */
	int _nodeCount;
	/* 键值占用内存大小 */
	int _firstSize;
	/* 数值占用内存大小 */
	int _secondSize;
};

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 构造函数 */
extern void CreateCRBTree(CRBTree* tree, int keySize, int valueSize, comparer keyCmp);
/* 红黑树插入节点 */
extern CIterBoolPair cTreeInsert(CRBTree* thiz, const void* val);
/* 红黑树删除入节点 */
extern void cTreeErase(CRBTree* thiz, CIterator position);
/* 红黑树寻找节点 */
extern CIterator cTreeFind(CRBTree* thiz, const void* key);
/* 返回红黑树的头节点 */
extern CIterator cTreeBegin(CRBTree* thiz);
/* 返回红黑树的头节点 */
extern CIterator cTreeEnd(CRBTree* thiz);
/* 清空红黑树 */
extern void cTreeClear(CRBTree* thiz);

#endif /* _C_TREE_H */
