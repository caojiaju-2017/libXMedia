#pragma once
#ifndef  __PUBLIC_HEAD__
#define  __PUBLIC_HEAD__


//��Դ���
enum SourceType
{
	Live,     // ��ý��
	File,     // �ļ�
	Device,   // �豸
	Desktop   // �ͻ�����
};

enum CodecType
{
	FLVCodec,     // 
	H264Codec
};

enum MutexType
{
	FLV,
	MP4
};


#endif