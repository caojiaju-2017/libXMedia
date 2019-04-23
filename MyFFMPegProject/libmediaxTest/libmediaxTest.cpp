
// libmediaxTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include "libmediax.h"
#include <thread>
#include "../libmediax/libmediax.h"

int main()
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


	PersientLive(*instance1, "rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov", "d:\\Work\\Temp\\output1.mp4", H264Codec, 80);

	/*std::chrono::milliseconds dura(6000);
	std::this_thread::sleep_for(dura);

	PersientLive(*instance2, "rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov", "d:\\Work\\Temp\\output2.flv", H264Codec, 30);*/


	/// upload github
	//答复是否撒旦
	//std::chrono::milliseconds dura(6000);
	//std::this_thread::sleep_for(dura);
	while (true)
	{
		if (!IsBusy(*instance1))
		{
			CloseHandle(*instance1);
			delete instance1;
			break;
		}

		std::chrono::milliseconds dura(1000);
		std::this_thread::sleep_for(dura);
		
	}

	/*CloseHandle(*instance1);

	CloseHandle(*instance2);*/

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
