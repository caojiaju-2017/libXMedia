#pragma once
#ifndef _FFMPEG_H_

#define _FFMPEG_H_

extern "C"
{
#include "libavcodec/avcodec.h"  
#include "libavformat/avformat.h"  
#include "libavfilter/avfiltergraph.h"  
#include "libavfilter/buffersink.h"  
#include "libavfilter/buffersrc.h"  
#include "libavutil/avutil.h"  
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavutil/avassert.h"
#include "libavutil/channel_layout.h"
#include "libavutil/opt.h"
#include "libavutil/mathematics.h"
#include "libavutil/timestamp.h"
#include "libavdevice/avdevice.h"
#include "libavutil/time.h"
}
#endif // !_FFMPEG_H_
