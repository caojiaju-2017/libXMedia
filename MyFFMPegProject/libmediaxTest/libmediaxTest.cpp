
// libmediaxTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include "libmediax.h"
#include <thread>

static int callBack(int a, int b) {
	std::cout << "Time go " << b << std::endl;
	return 0;
}

void rtspToFile()
{
	std::cout << "Hello World!\n";

	int* instance1 = new int(0);
	std::cout << "Instance1=" << *instance1 << std::endl;
	InitHandle(*instance1);
	std::cout << "Instance1=" << *instance1 << std::endl;

	int* instance2 = new int(0);
	std::cout << "Instance2=" << *instance2 << std::endl;
	InitHandle(*instance2);
	std::cout << "Instance2=" << *instance2 << std::endl;


	PersientLive(*instance1, "rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov", "d:\\Work\\Temp\\rtspToMp4.mp4", H264Codec, 80);

	std::chrono::milliseconds dura(6000);
	std::this_thread::sleep_for(dura);

	PersientLive(*instance2, "rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov", "d:\\Work\\Temp\\rtspToFlv.flv", FLVCodec, 80);

	//std::chrono::milliseconds dura(6000);
	//std::this_thread::sleep_for(dura);
	int exist = 0;
	while (true)
	{

		if (instance1 != nullptr && !IsBusy(*instance1))
		{
			CloseHandle(*instance1);
			delete instance1;
			instance1 = nullptr;
			exist = exist + 1;
			//break;
		}

		if (instance2 != nullptr && !IsBusy(*instance2))
		{
			CloseHandle(*instance2);
			delete instance2;
			instance2 = nullptr;
			exist = exist + 1;
			//break;
		}

		if (exist >= 2)
		{
			break;
		}

		std::chrono::milliseconds dura(1000);
		std::this_thread::sleep_for(dura);

	}
}


void RtspToRtmp()
{
	std::cout << "Hello World!\n";

	int* instance1 = new int(0);
	std::cout << "Instance1=" << *instance1 << std::endl;
	InitHandle(*instance1);
	std::cout << "Instance1=" << *instance1 << std::endl;


	ReMuxerLive(*instance1, "rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov", "rtmp://192.168.252.129/live/35", 180);

	int exist = 0;
	while (true)
	{

		if (instance1 != nullptr && !IsBusy(*instance1))
		{
			CloseHandle(*instance1);
			delete instance1;
			instance1 = nullptr;
			exist = exist + 1;
		}

		if (exist >= 1)
		{
			break;
		}

		std::chrono::milliseconds dura(1000);
		std::this_thread::sleep_for(dura);

	}
}


void RtmpToRtmp()
{
	std::cout << "Hello World!\n";

	int* instance1 = new int(0);
	std::cout << "Instance1=" << *instance1 << std::endl;
	InitHandle(*instance1);
	std::cout << "Instance1=" << *instance1 << std::endl;


	ReMuxerLive(*instance1, "rtmp://192.168.252.129/vod/35.mp4", "rtmp://192.168.252.129/live/35", 180);

	int exist = 0;
	while (true)
	{

		if (instance1 != nullptr && !IsBusy(*instance1))
		{
			CloseHandle(*instance1);
			delete instance1;
			instance1 = nullptr;
			exist = exist + 1;
		}

		if (exist >= 1)
		{
			break;
		}

		std::chrono::milliseconds dura(1000);
		std::this_thread::sleep_for(dura);

	}
}

void rtmpToFile()
{
	std::cout << "Hello World!\n";

	int* instance1 = new int(0);
	std::cout << "Instance1=" << *instance1 << std::endl;
	InitHandle(*instance1);
	std::cout << "Instance1=" << *instance1 << std::endl;

	int* instance2 = new int(0);
	std::cout << "Instance2=" << *instance2 << std::endl;
	InitHandle(*instance2);
	std::cout << "Instance2=" << *instance2 << std::endl;

	SetCallbackFunction(*instance1, callBack);

	PersientLive(*instance1, "rtmp://192.168.252.129/vod/35.mp4", "d:\\Work\\Temp\\rtmpToMp4.mp4", H264Codec, 80);

	std::chrono::milliseconds dura(6000);
	std::this_thread::sleep_for(dura);

	PersientLive(*instance2, "rtmp://192.168.252.129/vod/35.mp4", "d:\\Work\\Temp\\rtmpToFlv.flv", FLVCodec, 80);

	//std::chrono::milliseconds dura(6000);
	//std::this_thread::sleep_for(dura);
	int exist = 0;
	while (true)
	{

		if (instance1 != nullptr && !IsBusy(*instance1))
		{
			CloseHandle(*instance1);
			delete instance1;
			instance1 = nullptr;
			exist = exist + 1;
			//break;
		}

		if (instance2 != nullptr && !IsBusy(*instance2))
		{
			CloseHandle(*instance2);
			delete instance2;
			instance2 = nullptr;
			exist = exist + 1;
			//break;
		}

		if (exist >= 2)
		{
			break;
		}

		std::chrono::milliseconds dura(1000);
		std::this_thread::sleep_for(dura);

	}
}

void rtmpAndRtspToTS()
{
	std::cout << "Hello World!\n";

	int* instance1 = new int(0);
	std::cout << "Instance1=" << *instance1 << std::endl;
	InitHandle(*instance1);
	std::cout << "Instance1=" << *instance1 << std::endl;

	int* instance2 = new int(0);
	std::cout << "Instance2=" << *instance2 << std::endl;
	InitHandle(*instance2);
	std::cout << "Instance2=" << *instance2 << std::endl;


	PersientLive(*instance1, "rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov", "d:\\Work\\Temp\\rtspToTS.ts", MPEGTS, 80);

	//std::chrono::milliseconds dura(6000);
	//std::this_thread::sleep_for(dura);

	PersientLive(*instance2, "rtmp://192.168.252.129/vod/35.mp4", "d:\\Work\\Temp\\rtmpToTS.ts", MPEGTS, 80);

	//std::chrono::milliseconds dura(6000);
	//std::this_thread::sleep_for(dura);
	int exist = 0;
	while (true)
	{

		if (instance1 != nullptr && !IsBusy(*instance1))
		{
			CloseHandle(*instance1);
			delete instance1;
			instance1 = nullptr;
			exist = exist + 1;
			//break;
		}

		if (instance2 != nullptr && !IsBusy(*instance2))
		{
			CloseHandle(*instance2);
			delete instance2;
			instance2 = nullptr;
			exist = exist + 1;
			//break;
		}

		if (exist >= 2)
		{
			break;
		}

		std::chrono::milliseconds dura(1000);
		std::this_thread::sleep_for(dura);

	}
}

int main()
{
    
	//rtspToFile();

	rtmpToFile();

	// RtspToRtmp();

	//rtmpAndRtspToTS();

	/*CloseHandle(*instance1);

	CloseHandle(*instance2);*/

}

//我需要一个rtsp到其他流的包，sdk。我提供rtp流，你转换出来，我提供回调函数。
//你可以设计API，先rtsp到ts。要求音频必须是acc。我节后开始实现rtsp服务，
//这段时间在适应编程。还有我是用go调用。需要mac、win、Linux版。我的开发环境是mac
//
//
//
//基本可以理解为ffmpeg例子不用建立连接rtsp服务的网络，你需要的数据我都提供，
//所以你先要了解转换所需要的参数，后面就是rtp数据，你要看了ffmpeg代码就非常清楚了。
//ts的格式我还不了解，最好就是能直接保存的数据，并告诉该包是否是i侦，还有自启动以来该侦在第几秒等



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
