#pragma once
#include "ffmpeg.h"
#include "public.h"
#include <string>
#include <memory>
#include<thread>

using namespace std;

class MediaHelper
{
//public:
//	static MediaHelper * getInstance();

public:
	MediaHelper();
	~MediaHelper();


public:
	callback pCallBackFunction = NULL;

public:
	AVFormatContext* inputContext = NULL;
	AVFormatContext* outputContext = NULL;
	
	AVCodecContext* videoDecCtx = NULL;
	AVCodecContext* audioDecCtx = NULL;

	bool abortFlag = false;
	bool isFinishTask = true;
	
private:
	// 每个媒体适配器，绑定一个工作线程
	std::thread __mediaThread;

public:
	void Release();

private:
	void Init();
	
public:
	/**************************************************
	@brief   : 打开解码器
	@author  : caojiaju
	@time    : 2019/4
	@input   : 输入地址：文件/live/usb video/desktop
	@return  :
	**************************************************/
	int open_codec_context(enum  AVMediaType type);

	/**************************************************
	@brief   : 打开输入上下文
	@author  : caojiaju
	@time    : 2019/4
	@input   : 输入地址：文件/live/usb video/desktop
	@return  :
	**************************************************/
	int openSource(string inputUrl);

	/**************************************************
	@brief   : 打开输出上下文  FormatContext
	@author  : caojiaju
	@time    : 2019/4
	@input   : 输入目标：文件/推流地址
	@return  :
	**************************************************/
	int OpenOutput(string outUrl, CodecType type);

	/**************************************************
	@brief   : 打开输出上下文  FormatContext
	@author  : caojiaju
	@time    : 2019/4
	@input   : 输入目标：文件/推流地址
	@return  :
	**************************************************/
	int OpenOutputLive(string outUrl);

	/**************************************************
	@brief   : 从输入源读取一个包
	@author  : caojiaju
	@time    : 2019/4
	@input   : 
	@return  : 读出一个解封装后的包
	**************************************************/
	shared_ptr<AVPacket> ReadPacketFromSource(float& currentSecs);
	int ReadPacketFromSource2(AVPacket* packet,float& currentSecs);

	/**************************************************
	@brief   : 包时间同步
	@author  : caojiaju
	@time    : 2019/4
	@input   : 包， 同步原， 同步目标
	@return  :
	**************************************************/
	void av_packet_rescale_ts(AVPacket* pkt, AVRational src_tb, AVRational dst_tb);



	/**************************************************
	@brief   : 将包重新封装到输出的context
	@author  : caojiaju
	@time    : 2019/4
	@input   : 编码好的包
	@return  : 
	**************************************************/
	int WritePacketToContext(shared_ptr<AVPacket> packet);
	int WritePacketToContext2(AVPacket packet);
	//int interrupt_cb(void* ctx);

public:
	/**************************************************
	@brief   : 清理
	@author  : caojiaju/609853524@qq.com
	@time    : 2019/4/12
	@input   : 之前初始化得到的句柄
	@return  :>= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MD_Clear();



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
	int MD_OpenSource(const char* source, const int* wndPtr, SourceType sourcetype);


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
	int MD_ReMuxerLive(const char* source, const char* dest, int seconds);

	/**************************************************
	@brief   : 设置回调函数
	@author  : caojiaju/609853524@qq.com
	@time    : 2019/4/12
	@input1   : 回调函数，NULL表示清空回调函数
	@return   : void
	**************************************************/
	void MD_SetCallbackFunction(callback callBackFunc);

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
	int  MD_PersientLive(const char* source, const char* filename, CodecType codecType, int seconds);


	/**************************************************
	@brief   : 终止上一次媒体操作
	@author  : caojiaju
	@time    : 2019/4
	@input   : 操作句柄
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MD_AbortLastOperator();

	/**************************************************
	@brief   : 暂停上一次媒体操作
	@author  : caojiaju
	@time    : 2019/4
	@input   : 操作句柄
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MD_PauseLastOperator();



	/**************************************************
	@brief   : 继续上一次媒体操作
	@author  : caojiaju
	@time    : 2019/4
	@input   : 操作句柄
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MD_ResumeLastOperator();



	/**************************************************
	@brief   : 上一次动作结束回调函数---必须在InitHandle调用成功后立即调用
	@author  : caojiaju
	@time    : 2019/4
	@input1   : 操作句柄
	@input2   : 回调函数
	@return  : >= 0 表示成功 ； < 0 表示失败
	**************************************************/
	int MD_SetTaskFinishCallBack(void* funcPt);

	bool MD_IsBusy();

};

