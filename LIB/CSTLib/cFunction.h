/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): cFunction.h
**
** 描述(Description): 本文件定义函数(function)在C语言编译环境下的封装接口
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
#ifndef _C_FUNCTION_H
#define _C_FUNCTION_H

/*-----------------------------------------------------------------------------------------
**                                         Include
**-----------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <string.h>
#include "cPair.h"

/*-----------------------------------------------------------------------------------------
**                                     Type Declaration
**-----------------------------------------------------------------------------------------
*/
/* 一元函数声明 */
typedef struct CUnaryFunction CUnaryFunction;
/* 二元函数声明 */
typedef struct CBinaryFunction CBinaryFunction;

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)一元函数接口 */
/* 2) */
struct CUnaryFunction
{
	/* 函数 */
	const void* (*O)(CUnaryFunction* thiz, const void* val);
	/* 函数指针 */
	void* _function;
};

/* <类描述> */
/* 1)二元函数接口 */
/* 2) */
struct CBinaryFunction
{
	/* 函数 */
	const void* (*O)(CBinaryFunction* thiz, const void* val1, const void* val2);
	/* 函数指针 */
	void* _function;
};

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 返回键值 */
extern CUnaryFunction cFuncSelect1st(void);
/* int型变量比较 */
extern int intComparer(const void* x, const void* y);
/* string型变量比较 */
extern int strComparer(const void* x, const void* y);

#endif /* _C_FUNCTION_H */
