/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~
**
** 文件名(FileName): logger.c
**
** 描述(Description): 本文件定义Logger类成员函数实现
**
** 包含的函数(Included Function):
**
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2022年6月2日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2022年6月2日 创建本文件
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
#include "logger.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include "../LIB/CSTLib/cThread.h"
#ifdef WINDOWS
#include <io.h>
#include <Windows.h>
#endif

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 记录日志 */
static void log(void* thiz, const char* path);
/* 刷新日志缓冲并停止记录 */
static void stop(void* thiz);
/* 写入日志文件线程函数 */
static void writeLogFile(Logger* logger);

/*-----------------------------------------------------------------------------------------
**                                   Function Definition
**-----------------------------------------------------------------------------------------
*/
/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): CreateLogger
**
** 描述(Description): 本函数为Logger类构造函数
**
** 输入参数(Input Parameter):
**      logPath , const string& 日志文件路径
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月2日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
Logger* CreateLogger(const char* logPath)
{
	Logger* logger = (Logger*)malloc(sizeof(Logger));
	if (NULL == logger) {
		printf("Logger::Logger()--create logger error.\n");
	}
	else
	{
		time_t curTime;
		const char* fileName;
		char name[LOG_NAME_SIZE];
		int len;
		int index = 0;
		char path[LOG_PATH_SIZE];
		CThread _logThread;

		/* 初始化成员变量 */
		logger->_fd = FD_INVALID;
		logger->_hasError = false;
		logger->_exitFlag = false;

		/* 获取当时时间并以此命名日志文件 */
		time(&curTime);
		fileName = ctime(&curTime);
		/* 获取字符串长度 */
		len = strlen(fileName);
		/* 替换字符串 */
		strcpy(name, fileName);

		name[len - 1] = '\0';

		for (index = 0; index < len; index++) 
		{
			if ((name[index] == ' ') || (name[index] == ':')) {
				name[index] = '_';
			}
		}

		strcpy(path, logPath);
		strcpy(path, name);
		strcat(path, ".log");
		/* 新建并打开日志文件 */
#ifdef WINDOWS
		logger->_fd = _open(path, O_WRONLY | O_CREAT, S_IREAD);
#else
		logger->_fd = open(path, O_WRONLY | O_CREAT, S_IREAD);
#endif
		if (FD_INVALID == logger->_fd)
		{
			printf("Logger::Logger()--open log file error.\n");
			return NULL;
		}

		/* 创建并启动日志写入线程 */
		_logThread = *CreateCThread(writeLogFile, logger);
		_logThread.run(&_logThread);
	}

	return logger;
}
/* END of CreateLogger */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): DestroyLogger
**
** 描述(Description): 本函数为Logger类析构函数
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
**      Inory, 2022年6月2日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
void DestroyLogger(Logger* logger)
{
#ifdef DEBUG
	printf("Logger::~Logger()\n");
#endif
	/* 关闭日志文件 */
#ifdef WINDOWS
	_close(logger->_fd);
#else
	close(logger->_fd);
#endif
}
/* END of DestroyLogger */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): log
**
** 描述(Description): 本函数实现记录日志的功能
**
** 输入参数(Input Parameter):
**      info , const char* 待记录信息
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**      Inory, 2022年6月2日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static void log(void* thiz, const char* info)
{
	SLogInfo logInfo;

	/* 判断日志记录是否出错或退出 */
	if (((Logger*)thiz)->_hasError || ((Logger*)thiz)->_exitFlag) {
		return;
	}
	/* 判断数据有效性 */
	if ((NULL == info) || (strlen(info) > LOG_INFO_SIZE)) {
		return;
	}
	/* 将日志信息加入队列 */
	((Logger*)thiz)->_mtx.lock(&((Logger*)thiz)->_mtx);

	memset((char*)&logInfo, 0, sizeof(SLogInfo));
	memcpy(logInfo.info, info, strlen(info));

	((Logger*)thiz)->_logQueue.push(&((Logger*)thiz)->_logQueue, &logInfo);
	((Logger*)thiz)->_cv.notify_one(&((Logger*)thiz)->_cv);

	((Logger*)thiz)->_mtx.unlock(&((Logger*)thiz)->_mtx);
}
/* END of log */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): stop
**
** 描述(Description): 本函数实现刷新日志缓冲并停止记录的功能
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
**      Inory, 2022年6月2日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static void stop(void* thiz)
{
	((Logger*)thiz)->_exitFlag = true;

	/* 等待日志缓冲清空 */
	while (true)
	{
		((Logger*)thiz)->_mtx.lock(&((Logger*)thiz)->_mtx);

		if (((Logger*)thiz)->_logQueue.empty(&((Logger*)thiz)->_logQueue))
		{
			((Logger*)thiz)->_cv.notify_one(&((Logger*)thiz)->_cv);
			((Logger*)thiz)->_mtx.unlock(&((Logger*)thiz)->_mtx);
			break;
		}
		else
		{
			((Logger*)thiz)->_mtx.unlock(&((Logger*)thiz)->_mtx);
#ifdef WINDOWS
			Sleep(10);
#else
			usleep(10);
#endif
		}
	}
}
/* END of stop */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): writeLogFile
**
** 描述(Description): 本函数实现写入日志文件线程函数的功能
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
**      Inory, 2022年6月2日 创建本函数
**      $Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static void writeLogFile(Logger* logger)
{
	time_t logTime; /* 日志时间信息 */
	char strInfo[LOG_INFO_SIZE];
	char strTime[LOG_TIME_SIZE];
	char strLog[LOG_SIZE];
	const char* sTime;
	int len;

	/* 判断参数有效性 */
	if (NULL == logger) {
		return;
	}

	/* 循环等待日志写入事件,并写入日志文件 */
	while (true)
	{
		/* 等待同步信号 */
		logger->_mtx.lock(&logger->_mtx);

		while ((logger->_logQueue.empty(&logger->_logQueue)) && (!logger->_exitFlag)) {
			logger->_cv.wait(&logger->_cv, &logger->_mtx);
		}
		/* 判断循环等待退出原因(记录或程序退出) */
		if (!logger->_logQueue.empty(&logger->_logQueue))
		{
			SLogInfo info = *(SLogInfo*)logger->_logQueue.front(&logger->_logQueue);
			strcpy(strInfo, info.info);
			
			logger->_logQueue.pop(&logger->_logQueue);
			logger->_mtx.unlock(&logger->_mtx);
		}
		else
		{
			logger->_mtx.unlock(&logger->_mtx);
			break;
		}
		/* 获取当前时间,组合待写入信息 */
		time(&logTime);
		sTime = ctime(&logTime);

		strcpy(strTime, sTime);
		/* 获取字符串长度 */
		len = strlen(sTime);
		strTime[len - 1] = '\0';

		strcpy(strLog, strTime);
		strcat(strLog, "<-->");
		strcat(strLog, strInfo);
		strcat(strLog, "\n");
	}

	/* 写入日志文件 */
#ifdef WINDOWS
	if (-1 == _write(logger->_fd, strLog, (unsigned int)strlen(strLog)))
#else
	if (-1 == write(logger->_fd, strLog, (unsigned int)strlen(strLog)))
#endif
	{
		printf("Logger::writeLogFile()--write error.\n");
		logger->_hasError = true;
		return;
	}
}
/* END of writeLogFile */