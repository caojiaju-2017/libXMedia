#pragma once
#ifndef  __PUBLIC_HEAD__
#define  __PUBLIC_HEAD__


//资源类别
enum SourceType
{
	Live,     // 流媒体
	File,     // 文件
	Device,   // 设备
	Desktop   // 客户桌面
};

enum CodecType
{
	FLVCodec,     // flv 流
	H264Codec,    // mp4
	MPEGTS        // ts 流
};

enum MutexType
{
	FLV,
	MP4
};


#endif