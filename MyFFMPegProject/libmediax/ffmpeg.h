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

//typedef struct _OutputStream
//{
//	AVStream* st;
//
//	AVFrame* videoFrame;
//	AVFrame* audioFrame;
//
//	int64_t next_pts;
//
//	float t, tincr, tincr2;
//	struct SwsContext* sws_ctx;
//	struct SwsContext* swr_ctx;
//
//} OutputStream;
//
//
//#define HAVE_VIDEO 1
//#define HAVE_AUDIO 2
//
//
//#define STREAM_FRAME_RATE 25
//static int add_video_stream(OutputStream* video_st, AVFormatContext* fmt_ctx, AVCodec** codec, enum AVCodecID codec_id,int frameWidth,int frameHeight)
//{
//	*codec = avcodec_find_encoder(codec_id);
//
//	if (!(*codec))
//	{
//		return -1;
//
//	}
//
//	video_st->st = avformat_new_stream(fmt_ctx, *codec);
//	if (!(video_st->st))
//	{
//		return -1;
//	}
//	video_st->st->id = fmt_ctx->nb_streams - 1;
//
//	AVCodecContext* codecCtx = video_st->st->codec;
//		 
//	codecCtx->codec_id = codec_id;
//	codecCtx->bit_rate = 400000;
//	codecCtx->width = frameWidth;
//	codecCtx->height = frameHeight;
//
//	AVRational r = { 1,STREAM_FRAME_RATE };
//	codecCtx->time_base = r;
//
//	// 关键帧之间的间隔
//	codecCtx->gop_size;
//	codecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
//
//	if (codecCtx->codec_id == AV_CODEC_ID_MPEG1VIDEO)
//	{
//		codecCtx->mb_decision = 2;
//	}
//	
//	if (codecCtx->codec_id == AV_CODEC_ID_MPEG2VIDEO)
//	{
//		codecCtx->max_b_frames = 2;
//	}
//
//	if (fmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
//	{
//		codecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
//	}
//
//	return 1;
//}
//
//static int add_audio_stream(OutputStream* audio_st, AVFormatContext* fmt_ctx, AVCodec** codec, enum AVCodecID codec_id)
//{
//	
//	int i;
//	*codec = avcodec_find_encoder(codec_id);
//
//	if (!(*codec))
//	{
//		return -1;
//
//	}
//
//	audio_st->st = avformat_new_stream(fmt_ctx, *codec);
//	if (!(audio_st->st))
//	{
//		return -1;
//	}
//	audio_st->st->id = fmt_ctx->nb_streams - 1;
//
//	AVCodecContext* codecCtx = audio_st->st->codec;
//
//	//codecCtx->codec_id = codec_id;
//	codecCtx->sample_fmt = (*codec)->sample_fmts ? (*codec)->sample_fmts[0] : AV_SAMPLE_FMT_FLTP;
//	codecCtx->bit_rate = 64000;
//	codecCtx->sample_rate = 44100;
//
//	if ((*codec)->supported_samplerates)
//	{
//		codecCtx->sample_rate = (*codec)->supported_samplerates[0];
//		for (int i = 0; (*codec)->supported_samplerates[i]; i++)
//		{
//			if ((*codec)->supported_samplerates[i] == 44100)
//			{
//				codecCtx->sample_rate = 44100;
//			}
//		}
//	}
//
//	codecCtx->channels = av_get_channel_layout_nb_channels(codecCtx->channel_layout);
//	codecCtx->channel_layout = AV_CH_LAYOUT_STEREO;
//	if ((*codec)->channel_layouts)
//	{
//		codecCtx->channel_layout = (*codec)->channel_layouts[0];
//		for (i = 0; (*codec)->channel_layouts[i]; i++)
//		{
//			if ((*codec)->channel_layouts[i] == AV_CH_LAYOUT_STEREO)
//			{
//				codecCtx->channel_layout = AV_CH_LAYOUT_STEREO;
//			}
//		}
//	}
//
//	codecCtx->channels = av_get_channel_layout_nb_channels(codecCtx->channel_layout);
//
//	AVRational r = { 1,STREAM_FRAME_RATE };
//	audio_st->st->time_base = r;
//
//	
//
//	if (fmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
//	{
//		codecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
//	}
//
//	return 1;
//}
//
//int Add_audio_video_stream(OutputStream* video_st, OutputStream* audio_st, AVFormatContext* fmt_ctx, AVCodec* video_codec, AVCodec* audio_codec)
//{
//	int ret = 0;
//	AVOutputFormat* fmt = fmt_ctx->oformat;
//
//	// meiyou 视频
//	if (fmt->video_codec != AV_CODEC_ID_NONE)
//	{
//		// 添加视频流
//		add_video_stream(video_st, fmt_ctx, &video_codec, fmt->video_codec, 800, 640);
//	}
//
//	// meiyou 音频
//	if (fmt->audio_codec != AV_CODEC_ID_NONE)
//	{
//		// 添加视音频
//	}
//
//	return 1;
//}

#endif // !_FFMPEG_H_
