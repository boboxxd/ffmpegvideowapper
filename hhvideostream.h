#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H
#include <QPixmap>
#include <QMutex>
#include <QTimer>
#include <QLabel>
#ifdef __cplusplus
extern "C" {
#endif

#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef __cplusplus
}
#endif



class HHVideoStream:public QObject
{
    Q_OBJECT
public:

    enum HHVideoStreamError{
        CONNECTERROR,       //打开视频流失败
        GETSTREAMINFOERROR, //获取视频流信息失败
        OPENCODECERROR,      //打开解码器失败
        NETWORKERROR        //网络错误
    };

    HHVideoStream();
    ~HHVideoStream();
    HHVideoStream(const HHVideoStream& stream)=delete;
    void operator =(const HHVideoStream& stream)=delete;
    void setUrl(QString url);
    void startStream();
    void stopStream();


private slots:
    void playSlots();

signals:
    void GetImage(QImage);
    void Error(HHVideoStreamError,const QString&);

private:
    bool Init();
    QMutex mutex;
    AVPicture  pAVPicture;
    AVDictionary* options;
    AVFormatContext *pAVFormatContext;
    AVCodecContext *pAVCodecContext;
    AVFrame *pAVFrame;
    SwsContext * pSwsContext;
    AVPacket pAVPacket;
    QString  m_str_url;
    int videoStreamIndex;
    int videoWidth,videoHeight;
    int  m_i_frameFinished;
    QTimer *m_timerPlay;
    int isconnected;
    bool hasstopped;
};

#endif // VIDEOSTREAM_H
