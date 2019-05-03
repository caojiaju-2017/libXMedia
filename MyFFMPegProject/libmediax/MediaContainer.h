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
	static MediaContainer * m_sgltonMediaContainer;//���˴�Ҳ��ֱ��дΪ��̬������

public:
	/**************************************************
	@brief   : ��ʼ������
	@author  : caojiaju/609853524@qq.com
	@time    : 2019/4/12
	@input   : ��ʼ���ɹ���ͨ�����÷��ز����ٱ�
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MC_InitHandle(int& operatorHandle);

	/**************************************************
	@brief   : �ر�����
	@author  : caojiaju/609853524@qq.com
	@time    : 2019/4/12
	@input   : ֮ǰ��ʼ���õ��ľ��
	@return  :>= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MC_CloseHandle(int& operatorHandle);

	/**************************************************
	@brief   : ���ûص�����
	@author  : caojiaju/609853524@qq.com
	@time    : 2019/4/12
	@input1   : ֮ǰ��ʼ���õ��ľ��
	@input2   : �ص�������NULL��ʾ��ջص�����
	@return   : void
	**************************************************/
	void MC_SetCallbackFunction(const int& insHandle, callback callback);

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
	int MC_OpenSource(const int& insHandle, const char* source, const int* wndPtr, SourceType sourcetype);


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
	int MC_ReMuxerLive(const int& insHandle, const char* source, const char* dest, int seconds);


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
	int MC_PersientLive(const int& insHandle, const char* source, const char* filename, CodecType codecType, int seconds);


	/**************************************************
	@brief   : ��ֹ��һ��ý�����
	@author  : caojiaju
	@time    : 2019/4
	@input   : �������
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MC_AbortLastOperator(const int& operatorHandle);

	/**************************************************
	@brief   : ��ͣ��һ��ý�����
	@author  : caojiaju
	@time    : 2019/4
	@input   : �������
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MC_PauseLastOperator(const int& operatorHandle);



	/**************************************************
	@brief   : ������һ��ý�����
	@author  : caojiaju
	@time    : 2019/4
	@input   : �������
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MC_ResumeLastOperator(const int& operatorHandle);



	/**************************************************
	@brief   : ��һ�ζ��������ص�����---������InitHandle���óɹ�����������
	@author  : caojiaju
	@time    : 2019/4
	@input1   : �������
	@input2   : �ص�����
	@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
	**************************************************/
	int MC_SetTaskFinishCallBack(const int& operatorHandle, void* funcPt);

	/**************************************************
	@brief   : ��ȡ���һ�δ�����Ϣ
	@author  : caojiaju
	@time    : 2019/4
	@input1   :�������
	@input2   :�������
	@input3   :������Ϣ����ָ��
	@return  :
	**************************************************/
	void MC_GetLastError(int errorcode, char* errorInfo);

	/**************************************************
	@brief   : �жϵ�ǰ�����Ƿ�æ
	@author  : none
	@time    : none
	@input   :
	@return  :
	**************************************************/
	bool MC_IsBusy(const int& operatorHandle);

private:
	/**************************************************
	@brief   : ����
	@author  : none
	@time    : none
	@input   :
	@return  :
	**************************************************/
	MediaHelper* FinderHelper(const int& operatorHandle);



};

