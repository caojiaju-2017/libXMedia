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
	FLVCodec,     // flv ��
	H264Codec,    // mp4
	MPEGTS        // ts ��
};

enum MutexType
{
	FLV,
	MP4
};


#endif