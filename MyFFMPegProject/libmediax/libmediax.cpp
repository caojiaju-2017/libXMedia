#include "stdafx.h"
#include <iostream>
#include "libmediax.h"

#include "MediaContainer.h"

MediaContainer* MediaContainer::m_sgltonMediaContainer = nullptr;//初始化在主线程之前
int InitHandle(int& handle)
{
	MediaContainer* mContainer = MediaContainer::getInstance();

	if (mContainer == nullptr)
	{
		return -SINGLE_TON_ISNULL;
	}

	return mContainer->MC_InitHandle(handle);
}

int CloseHandle(int& handle)
{
	MediaContainer* mContainer = MediaContainer::getInstance();

	if (mContainer == nullptr)
	{
		return -SINGLE_TON_ISNULL;
	}

	return mContainer->MC_CloseHandle(handle);
}

int OpenSource(const int & insHandle, const char * source, const int * wndPtr, SourceType sourcetype)
{
	MediaContainer* mContainer = MediaContainer::getInstance();

	if (mContainer == nullptr)
	{
		return -SINGLE_TON_ISNULL;
	}

	return mContainer->MC_OpenSource(insHandle, source, wndPtr, sourcetype);
}

int ReMuxerLive(const int & insHandle, const char * source, const char * dest, int seconds)
{
	MediaContainer* mContainer = MediaContainer::getInstance();

	if (mContainer == nullptr)
	{
		return -SINGLE_TON_ISNULL;
	}

	return mContainer->MC_ReMuxerLive(insHandle, source, dest, seconds);
}

void SetCallbackFunction(const int& insHandle, callback callBackFunc)
{
	MediaContainer* mContainer = MediaContainer::getInstance();

	if (mContainer == nullptr)
	{
		return ;
	}

	return mContainer->MC_SetCallbackFunction(insHandle, callBackFunc);
}

int PersientLive(const int& insHandle, const char * source, const char * filename, CodecType codecType, int seconds)
{
	MediaContainer* mContainer = MediaContainer::getInstance();

	if (mContainer == nullptr)
	{
		return -SINGLE_TON_ISNULL;
	}

	return mContainer->MC_PersientLive(insHandle, source, filename,codecType,seconds);
}

int AbortLastOperator(const int & handle)
{
	MediaContainer* mContainer = MediaContainer::getInstance();
	if (mContainer == nullptr)
	{
		return -SINGLE_TON_ISNULL;
	}

	return mContainer->MC_AbortLastOperator(handle);
}

int PauseLastOperator(const int & handle)
{
	MediaContainer* mContainer = MediaContainer::getInstance();
	if (mContainer == nullptr)
	{
		return -SINGLE_TON_ISNULL;
	}

	return mContainer->MC_PauseLastOperator(handle);
}

int ResumeLastOperator(const int & handle)
{
	MediaContainer* mContainer = MediaContainer::getInstance();
	if (mContainer == nullptr)
	{
		return -SINGLE_TON_ISNULL;
	}

	return mContainer->MC_ResumeLastOperator(handle);
}

int SetTaskFinishCallBack(const int & handle, void * funcPt)
{
	MediaContainer* mContainer = MediaContainer::getInstance();
	if (mContainer == nullptr)
	{
		return -SINGLE_TON_ISNULL;
	}

	return mContainer->MC_SetTaskFinishCallBack(handle,funcPt);
}

bool IsBusy(const int& operatorHandle)
{
	MediaContainer* mContainer = MediaContainer::getInstance();
	if (mContainer == nullptr)
	{
		return -SINGLE_TON_ISNULL;
	}

	return mContainer->MC_IsBusy(operatorHandle);
}

void getLastError(int errorcode, char * errorInfo)
{
	MediaContainer* mContainer = MediaContainer::getInstance();
	if (mContainer == nullptr)
	{
		return ;
	}

	mContainer->MC_GetLastError(errorcode, errorInfo);
}
