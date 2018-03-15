#include "hhvideostream.h"
#include <QDebug>
#include <QDateTime>
#include <unistd.h>
HHVideoStream::HHVideoStream()
    :QObject()
{
    m_i_frameFinished=1;
    isconnected=0;
    m_timerPlay = new QTimer;
    m_timerPlay->setInterval(10);
}

void HHVideoStream::setUrl(QString url)
{
    m_str_url=url;
}

void HHVideoStream::startStream()
{
    videoStreamIndex=-1;
    av_register_all();//注册库中所有可用的文件格式和解码器
    avformat_network_init();//初始化网络流格式,使用RTSP网络流时必须先执行
    pAVFormatContext = avformat_alloc_context();//申请一个AVFormatContext结构的内存,并进行简单初始化
    pAVFrame=av_frame_alloc();
    if (this->Init())
    {
        connect(m_timerPlay,SIGNAL(timeout()),this,SLOT(playSlots()));
        m_timerPlay->start();
    }
}

bool HHVideoStream::Init()
{
    if(m_str_url.isEmpty())
        return false;
    //打开视频流
    int result=avformat_open_input(&pAVFormatContext, m_str_url.toStdString().c_str(),NULL,NULL);
    if (result<0){
        qDebug()<<"打开视频流失败";
        emit Error(CONNECTERROR,"打开视频流失败!");
        return false;
    }

    //获取视频流信息
    result=avformat_find_stream_info(pAVFormatContext,NULL);
    if (result<0){
        qDebug()<<"获取视频流信息失败";
        emit Error(GETSTREAMINFOERROR,"获取视频流信息失败!");
        return false;
    }

    //获取视频流索引
    videoStreamIndex = -1;
    for (uint i = 0; i < pAVFormatContext->nb_streams; i++) {
        if (pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex==-1){
        emit Error(GETSTREAMINFOERROR,"获取视频流信息失败!");
        return false;
    }

    //获取视频流的分辨率大小
    pAVCodecContext = pAVFormatContext->streams[videoStreamIndex]->codec;
    videoWidth=pAVCodecContext->width;
    videoHeight=pAVCodecContext->height;

    avpicture_alloc(&pAVPicture,AV_PIX_FMT_RGB24,videoWidth,videoHeight);

    AVCodec *pAVCodec;

    //获取视频流解码器
    pAVCodec = avcodec_find_decoder(pAVCodecContext->codec_id);
    pSwsContext = sws_getContext(videoWidth,videoHeight,AV_PIX_FMT_YUV420P,videoWidth,videoHeight,AV_PIX_FMT_RGB24,SWS_BICUBIC,0,0,0);

    //打开对应解码器
    result=avcodec_open2(pAVCodecContext,pAVCodec,NULL);
    if (result<0){
        qDebug()<<"打开解码器失败";
        emit Error(OPENCODECERROR,"打开解码器失败!");
        return false;
    }

    qDebug()<<"初始化视频流成功";
    return true;
}


void HHVideoStream::playSlots()
{
    //一帧一帧读取视频
    isconnected = av_read_frame(pAVFormatContext, &pAVPacket);
    if (isconnected == 0){
        if(pAVPacket.stream_index==videoStreamIndex){
            avcodec_decode_video2(pAVCodecContext, pAVFrame, &m_i_frameFinished, &pAVPacket);
            if (m_i_frameFinished){
                mutex.lock();
                sws_scale(pSwsContext,(const uint8_t* const *)pAVFrame->data,pAVFrame->linesize,0,videoHeight,pAVPicture.data,pAVPicture.linesize);
                //发送获取一帧图像信号
                qDebug()<<"pts= "<<pAVFrame->pkt_pts;
                QImage image(pAVPicture.data[0],videoWidth,videoHeight,QImage::Format_RGB888);
                emit GetImage(image);
                mutex.unlock();
            }
        }
    }else{
        //网络连接已断开，正在尝试重连...
        av_free_packet(&pAVPacket);
        stopStream();
        //emit Error(NETWORKERROR,"网络连接已断开!");
        while(isconnected != 0)
        {
            qDebug()<<"connect status: "<<isconnected;
            usleep(500);
            startStream();
            break;
        }
    }

 av_free_packet(&pAVPacket);//释放资源,否则内存会一直上升

}


void HHVideoStream::stopStream()
{
    m_timerPlay->stop();
    avformat_free_context(pAVFormatContext);
    av_frame_free(&pAVFrame);
    sws_freeContext(pSwsContext);
}

HHVideoStream::~HHVideoStream()
{
    stopStream();
    av_free_packet(&pAVPacket);

}

