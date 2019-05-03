#ifndef  __LIBMEDIA_X__

#define __LIBMEDIA_X__

#include "public.h"

/**************************************************
@brief   : ��ʼ������
@author  : caojiaju/609853524@qq.com
@time    : 2019/4/12
@input   : ��ʼ���ɹ���ͨ�����÷��ز����ٱ�  
@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
**************************************************/
int InitHandle(int& operatorHandle);



/**************************************************
@brief   : �ر�����
@author  : caojiaju/609853524@qq.com
@time    : 2019/4/12
@input   : ֮ǰ��ʼ���õ��ľ��
@return  :>= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
**************************************************/
int CloseHandle(int& operatorHandle);



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
int OpenSource(const int& insHandle, const char* source, const int* wndPtr, SourceType sourcetype);


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
int ReMuxerLive(const int& insHandle,const char* source, const char* dest, int seconds);


/**************************************************
@brief   : ���ûص�����
@author  : caojiaju/609853524@qq.com
@time    : 2019/4/12
@input1   : ֮ǰ��ʼ���õ��ľ��
@input2   : �ص�������NULL��ʾ��ջص�����
@return   : void
**************************************************/
void SetCallbackFunction(const int& insHandle, callback callback);

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
int PersientLive(const int& insHandle, const char* source, const char* filename, CodecType codecType, int seconds);


/**************************************************
@brief   : ��ֹ��һ��ý�����
@author  : caojiaju
@time    : 2019/4
@input   : �������
@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
**************************************************/
int AbortLastOperator(const int& operatorHandle);

/**************************************************
@brief   : ��ͣ��һ��ý�����
@author  : caojiaju
@time    : 2019/4
@input   : �������
@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
**************************************************/
int PauseLastOperator(const int& operatorHandle);



/**************************************************
@brief   : ������һ��ý�����
@author  : caojiaju
@time    : 2019/4
@input   : �������
@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
**************************************************/
int ResumeLastOperator(const int& operatorHandle);



/**************************************************
@brief   : ��һ�ζ��������ص�����---������InitHandle���óɹ�����������
@author  : caojiaju
@time    : 2019/4
@input1   : �������
@input2   : �ص�����
@return  : >= 0 ��ʾ�ɹ� �� < 0 ��ʾʧ��
**************************************************/
int SetTaskFinishCallBack(const int& operatorHandle, void* funcPt);

/**************************************************
@brief   : ��ȡ���һ�δ�����Ϣ
@author  : caojiaju
@time    : 2019/4
@input1   :�������
@input2   :�������
@input3   :������Ϣ����ָ��
@return  :
**************************************************/
void getLastError(const int& operatorHandle,int errorcode, char* errorInfo);


bool IsBusy(const int& operatorHandle);

#endif // ! __LIBMEDIA_X__
