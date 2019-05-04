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
	// ÿ��ý������������һ�������߳�
	std::thread __mediaThread;

public:
	void Release();

private:
	void Init();
	
public:
	/**************************************************
	@brief   : �򿪽�����
	@author  : caojiaju
	@time    : 2019/4
	@input   : �����ַ���ļ�/live/usb video/desktop
	@return  :
	**************************************************/
	int open_codec_context(enum  AVMediaType type);

	/**************************************************
	@brief   : ������������
	@author  : caojiaju
	@time    : 2019/4
	@input   : �����ַ���ļ�/live/usb video/desktop
	@return  :
	**************************************************/
	int openSource(string inputUrl);

	/**************************************************
	@brief   : �����������  FormatContext
	@author  : caojiaju
	@time    : 2019/4
	@input   : ����Ŀ�꣺�ļ�/������ַ
	@return  :
	**************************************************/
	int OpenOutput(string outUrl, CodecType type);

	/**************************************************
	@brief   : �����������  FormatContext
	@author  : caojiaju
	@time    : 2019/4
	@input   : ����Ŀ�꣺�ļ�/������ַ
	@return  :
	**************************************************/
	int OpenOutputLive(string outUrl);

	/**************************************************
	@brief   : ������Դ��ȡһ����
	@author  : caojiaju
	@time    : 2019/4
	@input   : 
	@return  : ����һ�����װ��İ�
	**************************************************/
	shared_ptr<AVPacket> ReadPacketFromSource(float& currentSecs);
	int ReadPacketFromSource2(AVPacket* packet,float& currentSecs);

	/**************************************************
	@brief   : ��ʱ��ͬ��
	@author  : caojiaju
	@time    : 2019/4
	@input   : ���� ͬ��ԭ�� ͬ��Ŀ��
	@return  :
	**************************************************/
	void av_packet_rescale_ts(AVPacket* pkt, AVRational src_tb, AVRational dst_tb);



	/**************************************************
	@brief   : �������·�װ�������context
	@author  : caojiaju
	@time    : 2019/4
	@input   : ����õİ�
	@return  : 
	**************************************************/
	int WritePacketToContext(shared_ptr<AVPacket> packet);
	int WritePacketToContext2(AVPacket packet);
	//int interrupt_cb(void* ctx);

public:
	/**************************************************
	@brief   : ����
	@author  : caojiaju/609853524@qq.com
	@time    : 2019/4/12
	@input   : ֮ǰ��ʼ���õ��ľ��
	@return  :>= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MD_Clear();



	/**************************************************
	@brief   : ����Դ��������
	@author  : caojiaju
	@time    : 2019/4
	@input1   : ��Դ��ַ
	@input2   : ������Ƶ�Ĵ��ھ��
	@input3   :  ��ǰӦ��ʵ�����
	@input4   :  �������Դ����
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MD_OpenSource(const char* source, const int* wndPtr, SourceType sourcetype);


	/**************************************************
	@brief   : �����������������͵�ָ����ý������� --- ȱ�ٸ�ʽָ��
	@author  : caojiaju
	@time    : 2019/4
	@input1   :insHandle ���
	@input2   :ý���ַ
	@input3   :ת��/���ַ
	@input4   :seconds  ת��ʱ��
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MD_ReMuxerLive(const char* source, const char* dest, int seconds);

	/**************************************************
	@brief   : ���ûص�����
	@author  : caojiaju/609853524@qq.com
	@time    : 2019/4/12
	@input1   : �ص�������NULL��ʾ��ջص�����
	@return   : void
	**************************************************/
	void MD_SetCallbackFunction(callback callBackFunc);

	/**************************************************
	@brief   : �����־û� --- ��һ·live��ת����ļ�
	@author  : caojiaju
	@time    : 2019/4
	@input1   :�������
	@input2   :ý���ַ---��
	@input3   :����ļ���
	@input4   :���뷽ʽ
	@input5   :ת��ʱ������λ��
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int  MD_PersientLive(const char* source, const char* filename, CodecType codecType, int seconds);


	/**************************************************
	@brief   : ��ֹ��һ��ý�����
	@author  : caojiaju
	@time    : 2019/4
	@input   : �������
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MD_AbortLastOperator();

	/**************************************************
	@brief   : ��ͣ��һ��ý�����
	@author  : caojiaju
	@time    : 2019/4
	@input   : �������
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MD_PauseLastOperator();



	/**************************************************
	@brief   : ������һ��ý�����
	@author  : caojiaju
	@time    : 2019/4
	@input   : �������
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MD_ResumeLastOperator();



	/**************************************************
	@brief   : ��һ�ζ��������ص�����---������InitHandle���óɹ�����������
	@author  : caojiaju
	@time    : 2019/4
	@input1   : �������
	@input2   : �ص�����
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MD_SetTaskFinishCallBack(void* funcPt);

	bool MD_IsBusy();

};

