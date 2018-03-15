#include "hhvideowidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
HHVideoWidget::HHVideoWidget(HHVideoStream *stream,QWidget *parent)
    :QOpenGLWidget(parent),m_stream(stream),image(QImage())
{

}

void HHVideoWidget::GetImage(QImage img)
{
    image=img.copy(0,0,img.width(),img.height());
    update();
}

void HHVideoWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    if(image.isNull())
        return;
    QPainter painter(this);
    QImage tmp=image.scaled(this->width(),this->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    int posx=(this->width()-tmp.width())/2;
    int posy=(this->height()-tmp.height())/2;
    painter.drawImage(posx,posy,tmp);
    painter.end();
}

void HHVideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(isFullScreen() == false)
        {
            setWindowFlags(Qt::Window);
            showFullScreen();
        }else
        {
            setWindowFlags(Qt::SubWindow);
            showNormal();
        }
    }
}

void HHVideoWidget::handleError(HHVideoStream::HHVideoStreamError,const QString& msg )
{
    QMessageBox::information(NULL, "error", msg, QMessageBox::Yes );
}
