#include "stdafx.h"
#include "MediaHelper.h"
#include <string>

#include <iostream>

// 全局上一次读包时间---超时处理。
int64_t lastReadPackTime;
int TIMEOUT_SECONDS = 30;

void MediaHelper::Init()
{
	av_register_all();
	avfilter_register_all();
	avformat_network_init();
	avdevice_register_all();
	av_log_set_level(AV_LOG_ERROR);
}

void MediaHelper::Release()
{
	// 收尾工作
	avformat_close_input(&inputContext);

	if (!(outputContext->flags & AVFMT_NOFILE))
	{
		avio_closep(&outputContext->pb);
	}

	try
	{
		if (outputContext->internal != NULL || outputContext->metadata != NULL)
		{
			avformat_free_context(outputContext);
		}
		
	}
	catch (exception ex)
	{

	}
}

MediaHelper::MediaHelper() 
{
	Init();
}


MediaHelper::~MediaHelper()
{
}

int MediaHelper::MD_Clear()
{
	return 0;
}

int MediaHelper::MD_OpenSource(const char * source, const int * wndPtr, SourceType sourcetype)
{
	return 0;
}

int MediaHelper::MD_ReMuxerLive(const char * source, const char * dest, int seconds)
{
	return 0;
}

int MediaHelper::MD_PersientLive(const char * source, const char * filename, CodecType codecType, int seconds)
{
	isFinishTask = false;
	__mediaThread = std::thread ([=]
	{
			isFinishTask = false;
			Init();

			int ret = openSource(source);

			if (ret >= 0)
			{
				ret = OpenOutput(filename,codecType);
			}

			int64_t startWritePack = av_gettime();
			clock_t start = clock();
			if (ret < 0)
			{
				char buf[1024] = { 0 };
				av_strerror(ret, buf, sizeof(buf) - 1);
				goto Error;
			}

			cout << "start:" << startWritePack << endl;

			
			// 读包
			while (true && !abortFlag)
			{
				auto packet = this->ReadPacketFromSource();

				if (packet)
				{
					ret = WritePacketToContext(packet);
					if (ret >= 0)
					{
						std::cout << "WritePacket Success" << endl;
					}
					else {
						cout << "WritePacket Error" << endl;
					}

				}

				int64_t endWritePack = av_gettime();

				/*cout << "end:" << endWritePack << endl;
				cout << "sep:" << endWritePack - startWritePack << endl;*/
				//if (seconds > 0 && (endWritePack - startWritePack) >= (int64_t)seconds * 1000)
				//{
				//	break;
				//}

				clock_t end = (clock() - start) / CLOCKS_PER_SEC;

				// 
				if (this->abortFlag || (seconds > 0 && end > seconds))
				{
					isFinishTask = true;
					break;
				}


			}
			// 写入文件尾数句
			av_write_trailer(outputContext);
			cout << "Finish~" << endl;

		Error:
			//Release();
			int a = 0;
			
	});

	return 0;
}

int MediaHelper::MD_AbortLastOperator()
{
	return 0;
}

int MediaHelper::MD_PauseLastOperator()
{
	return 0;
}

int MediaHelper::MD_ResumeLastOperator()
{
	return 0;
}

int MediaHelper::MD_SetTaskFinishCallBack(void * funcPt)
{
	return 0;
}

bool MediaHelper::MD_IsBusy()
{
	return !isFinishTask;
}

/// 判断打开流是否失败、超时
int interrupt_cb(void* ctx)
{
	if (av_gettime() - lastReadPackTime > (int64_t)TIMEOUT_SECONDS * 1000 * 1000)
	{
		return -1;
	}

	return 0;
}

int MediaHelper::openSource(string inputUrl)
{
	inputContext = avformat_alloc_context();

	// 上一次读包时间
	lastReadPackTime = av_gettime();
	inputContext->interrupt_callback.callback = interrupt_cb;

	// FFMPEG AIP 获取URL中的上下文
	int ret = avformat_open_input(&inputContext, inputUrl.c_str(), NULL, NULL);

	if (ret < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "Input file open failed");
		return ret;
	}

	ret = avformat_find_stream_info(inputContext, NULL);

	if (ret < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "Find input file stream failed");

	}
	else
	{
		av_log(NULL, AV_LOG_FATAL, "Open input file %s success\n", inputUrl.c_str());
	}

	return ret;
}

int MediaHelper::OpenOutput(string outUrl, CodecType type= FLVCodec)
{
	string typeExtern = "flv";
	if (type == H264Codec)
	{
		typeExtern = "mp4";
	}
	int ret = avformat_alloc_output_context2(&outputContext, NULL, typeExtern.c_str(), outUrl.c_str());

	if (ret < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "open output context failed \n");
		goto Error;
	}

	av_dump_format(outputContext, 0, outUrl.c_str(), 1);

	//AVCodec* codec =  avcodec_find_encoder(AV_CODEC_ID_H264);
	//avformat_new_stream(outputContext, codec);

	//防止编码延迟修改参数
	av_opt_set(outputContext->priv_data, "preset", "superfast", 0);
	av_opt_set(outputContext->priv_data, "tune", "zerolatency", 0);

	ret = avio_open2(&outputContext->pb, outUrl.c_str(), AVIO_FLAG_READ_WRITE, NULL, NULL);
	if (ret < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "open avio failed");
		goto Error;
	}


	for (unsigned int i = 0; i < inputContext->nb_streams; i++)
	{
		AVStream* stream = avformat_new_stream(outputContext, inputContext->streams[i]->codec->codec);
		ret = avcodec_copy_context(stream->codec, inputContext->streams[i]->codec);


		/*AVCodecContext* codec_ctx = avcodec_alloc_context3(stream->codec);
		ret = avcodec_parameters_to_context(codec_ctx, in_stream->codecpar);*/


		if (ret < 0)
		{
			av_log(NULL, AV_LOG_ERROR, "copy coddec context failed\n");
			goto Error;
		}
	}

	
	ret = avformat_write_header(outputContext, NULL);

	if (ret < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "format write header failed");
		goto Error;
	}

	av_log(NULL, AV_LOG_FATAL, "Open output file success\n");

	return ret;

Error:

	if (outputContext)
	{
		for (unsigned int index = 0; index < outputContext->nb_streams; index++)
		{
			avcodec_close(outputContext->streams[index]->codec);
		}

		avformat_close_input(&outputContext);
	}
	return ret;
}


shared_ptr<AVPacket> MediaHelper::ReadPacketFromSource()
{
	//shared_ptr<AVPacket> packet = nullptr;
	shared_ptr<AVPacket> packet((AVPacket*)av_malloc(sizeof(AVPacket)), [&](AVPacket *p) {av_packet_unref(p); av_freep(&p); });

	av_init_packet(packet.get());

	// 更新包的时间
	lastReadPackTime = av_gettime();

	int ret = av_read_frame(inputContext, packet.get());

	if (ret >= 0)
	{
		// packet 裸流 
		return packet;
	}
	else
	{
		return NULL;
	}
}

void MediaHelper::av_packet_rescale_ts(AVPacket* pkt, AVRational src_tb, AVRational dst_tb)
{
	if (pkt->pts != AV_NOPTS_VALUE)
	{
		pkt->pts = av_rescale_q(pkt->pts, src_tb, dst_tb);
	}
	if (pkt->dts != AV_NOPTS_VALUE)
	{
		pkt->dts = av_rescale_q(pkt->dts, src_tb, dst_tb);
	}
	if (pkt->duration > 0)
	{
		pkt->duration = av_rescale_q(pkt->duration, src_tb, dst_tb);
	}
}

int MediaHelper::WritePacketToContext(shared_ptr<AVPacket> packet)
{
	auto inputStream = inputContext->streams[packet->stream_index];
	auto outputStream = outputContext->streams[packet->stream_index];

	// 时间戳转换---输入和输出可能存在时间基准不一致
	av_packet_rescale_ts(packet.get(), inputStream->time_base, outputStream->time_base);
	return  av_interleaved_write_frame(outputContext, packet.get());
}