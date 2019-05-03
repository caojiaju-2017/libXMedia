#pragma once
#include <vector>
#include "public.h"
#include "MediaHelper.h"
#include "error.h"
#include <thread>
#include <map>

using namespace std;

class MediaContainer
{
public:
	static MediaContainer * getInstance();
	std::thread threadRunWork;

private:
	vector<MediaHelper*> __mediaHelper = {};
private:
	MediaContainer();
	~MediaContainer();
	static MediaContainer * m_sgltonMediaContainer;//（此处也可直接写为静态变量）

public:
	/**************************************************
	@brief   : 初始化操作
	@author  : caojiaju/609853524@qq.com
	@time    : 2019/4/12
	@input   : 初始化成功，通过引用返回操作举兵
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MC_InitHandle(int& operatorHandle);

	/**************************************************
	@brief   : 关闭清理
	@author  : caojiaju/609853524@qq.com
	@time    : 2019/4/12
	@input   : 之前初始化得到的句柄
	@return  :>= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MC_CloseHandle(int& operatorHandle);

	/**************************************************
	@brief   : 设置回调函数
	@author  : caojiaju/609853524@qq.com
	@time    : 2019/4/12
	@input1   : 之前初始化得到的句柄
	@input2   : 回调函数，NULL表示清空回调函数
	@return   : void
	**************************************************/
	void MC_SetCallbackFunction(const int& insHandle, callback callback);

	/**************************************************
	@brief   : 打开资源，并播放
	@author  : caojiaju
	@time    : 2019/4
	@input1   : 资源地址
	@input2   : 播放视频的窗口句柄
	@input3   :  当前应用实例句柄
	@input4   :  输入的资源类型
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MC_OpenSource(const int& insHandle, const char* source, const int* wndPtr, SourceType sourcetype);


	/**************************************************
	@brief   : 接收流，并将流推送到指定流媒体服务器 --- 缺少格式指定
	@author  : caojiaju
	@time    : 2019/4
	@input1   :insHandle 句柄
	@input2   :媒体地址
	@input3   :转发/存地址
	@input4   :seconds  转发时长
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MC_ReMuxerLive(const int& insHandle, const char* source, const char* dest, int seconds);


	/**************************************************
	@brief   : 将流持久化 --- 将一路live，转存成文件
	@author  : caojiaju
	@time    : 2019/4
	@input1   :操作句柄
	@input2   :媒体地址---流
	@input3   :输出文件名
	@input4   :编码方式
	@input5   :转存时长，单位秒
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MC_PersientLive(const int& insHandle, const char* source, const char* filename, CodecType codecType, int seconds);


	/**************************************************
	@brief   : 终止上一次媒体操作
	@author  : caojiaju
	@time    : 2019/4
	@input   : 操作句柄
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MC_AbortLastOperator(const int& operatorHandle);

	/**************************************************
	@brief   : 暂停上一次媒体操作
	@author  : caojiaju
	@time    : 2019/4
	@input   : 操作句柄
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MC_PauseLastOperator(const int& operatorHandle);



	/**************************************************
	@brief   : 继续上一次媒体操作
	@author  : caojiaju
	@time    : 2019/4
	@input   : 操作句柄
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MC_ResumeLastOperator(const int& operatorHandle);



	/**************************************************
	@brief   : 上一次动作结束回调函数---必须在InitHandle调用成功后立即调用
	@author  : caojiaju
	@time    : 2019/4
	@input1   : 操作句柄
	@input2   : 回调函数
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MC_SetTaskFinishCallBack(const int& operatorHandle, void* funcPt);

	/**************************************************
	@brief   : 获取最近一次错误信息
	@author  : caojiaju
	@time    : 2019/4
	@input1   :操作句柄
	@input2   :错误代码
	@input3   :错误信息接受指针
	@return  :
	**************************************************/
	void MC_GetLastError(int errorcode, char* errorInfo);

	/**************************************************
	@brief   : 判断当前对象是否繁忙
	@author  : none
	@time    : none
	@input   :
	@return  :
	**************************************************/
	bool MC_IsBusy(const int& operatorHandle);

private:
	/**************************************************
	@brief   : 查找
	@author  : none
	@time    : none
	@input   :
	@return  :
	**************************************************/
	MediaHelper* FinderHelper(const int& operatorHandle);



};

