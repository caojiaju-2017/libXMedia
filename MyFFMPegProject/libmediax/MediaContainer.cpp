#include "stdafx.h"
#include "MediaContainer.h"
#include <iostream>
//#include <pthread.h>
#include <thread>
//using namespace std;
MediaContainer * MediaContainer::getInstance()
{
	if (m_sgltonMediaContainer == nullptr)
	{
		m_sgltonMediaContainer = new MediaContainer;
	}
	return m_sgltonMediaContainer;
}

MediaContainer::MediaContainer()
{
}


MediaContainer::~MediaContainer()
{
}

int MediaContainer::MC_InitHandle(int& operatorHandle)
{
	MediaHelper* mHelper = new MediaHelper;
	if (mHelper == nullptr)
	{
		return  -ALLOC_FAILED;
	}

	__mediaHelper.push_back(mHelper);

	int* pTemp;
	pTemp = &operatorHandle;
	pTemp = (int*)(&mHelper);
	operatorHandle = *pTemp;
	return 0;
}

int MediaContainer::MC_CloseHandle(int & operatorHandle)
{
	MediaHelper* mHelper = NULL;
	//int count = __mediaHelper.size();
	//for (int i = 0; i < count; i++)
	for (auto iter = __mediaHelper.begin(); iter != __mediaHelper.end(); ++iter)
	{
		MediaHelper* mediaTemp = *iter;

		int* pTemp;
		pTemp = (int*)(&mediaTemp);

		if ((*pTemp) == operatorHandle)
		{
			std::cout << "Find Source Handle" << std::endl;

			mHelper = mediaTemp;


			// 待增加---删除verctor元素
			__mediaHelper.erase(iter);
			
			break;
		}
	}

	if (mHelper == NULL)
	{
		std::cout << "Not Find Source Handle" << std::endl;

		return -INVALID_HANDLE;
	}

	// 释放ffmpeg对象
	mHelper->Release();

	// 销毁对象
	//delete mHelper;

	return 0;
}

int MediaContainer::MC_OpenSource(const int & insHandle, const char * source, const int * wndPtr, SourceType sourcetype)
{
	return 0;
}

int MediaContainer::MC_ReMuxerLive(const int & insHandle, const char * source, const char * dest, int seconds)
{
	MediaHelper* mediaHelper = FinderHelper(insHandle);

	if (mediaHelper == NULL)
	{
		return -INVALID_HANDLE;
	}

	mediaHelper->MD_ReMuxerLive(source, dest, seconds);



	return 0;
}

int MediaContainer::MC_PersientLive(const int & insHandle, const char * source, const char * filename, CodecType codecType, int seconds)
{
	MediaHelper* mediaHelper = FinderHelper(insHandle);

	if (mediaHelper == NULL)
	{
		return -INVALID_HANDLE;
	}
	//threadRunWork = std::thread(&MediaHelper::MD_PersientLive, source, filename, codecType, seconds);

	//threadRunWork = std::thread ([=]
	//	{
			mediaHelper->MD_PersientLive(source, filename, codecType, seconds);
		//});

	//threadRunWork.join();
	
	return 0;
}

int MediaContainer::MC_AbortLastOperator(const int & operatorHandle)
{
	return 0;
}

int MediaContainer::MC_PauseLastOperator(const int & operatorHandle)
{
	return 0;
}

int MediaContainer::MC_ResumeLastOperator(const int & operatorHandle)
{
	return 0;
}

int MediaContainer::MC_SetTaskFinishCallBack(const int & operatorHandle, void * funcPt)
{
	return 0;
}

void MediaContainer::MC_GetLastError(int errorcode, char * errorInfo)
{
}

MediaHelper * MediaContainer::FinderHelper(const int & operatorHandle)
{
	for (auto iter = __mediaHelper.begin(); iter != __mediaHelper.end(); ++iter)
	{
		MediaHelper* mediaTemp = *iter;

		int* pTemp;
		pTemp = (int*)(&mediaTemp);

		if ((*pTemp) == operatorHandle)
		{
			return  mediaTemp;
		}
	}
	return NULL;
}

bool MediaContainer::MC_IsBusy(const int& operatorHandle)
{
	MediaHelper* mediaHelper = FinderHelper(operatorHandle);


	if (mediaHelper == NULL)
	{
		return true;
	}
	return mediaHelper->MD_IsBusy();
}

