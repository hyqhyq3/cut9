#include "imagewidget.h"
#include "qdebug.h"

#include <QDragEnterEvent>
#include <QPainter>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
}

void ImageWidget::setImage(QString sFileName)
{
    x1 = x2 = y1 = y2 = 0;
    img_ = QImage(sFileName);
//    resize(img_.size());
    qDebug() << img_.size();
    repaint();
}


QVector<QImage> ImageWidget::getSplitImages()
{
    QVector<QImage> ret;
    if(x1 && x2 && y1 && y2)
    {
        int x[] = {0, x1, x2, img_.width()};
        int y[] = {0, y1, y2, img_.height()};
        for(int j = 0; j < 3; ++j)
        {
            for(int i = 0; i < 3; ++i)
            {
                ret.push_back(img_.copy(x[i], y[j], x[i+1] - x[i], y[j+1] - y[j]));
            }
        }
    }
    return ret;
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    QImage tmp(img_.width(), img_.height(), QImage::Format_RGBA8888);
    tmp.fill(0);
    QPainter painter(&tmp);
    painter.drawImage(0, 0, img_);
    painter.setBrush(QColor(0, 255, 255, 100));
    painter.setPen(QPen(QColor(0,0,0,0), 0));
    if(x1 && x2 && y1 && y2)
    {
        QVector<QRect> rects;
        rects.push_back(QRect(QPoint(), QPoint(x1, y1)));
        rects.push_back(QRect(QPoint(x2,0), QPoint(img_.width(),y1)));
        rects.push_back(QRect(QPoint(x1,y1), QPoint(x2,y2)));
        rects.push_back(QRect(QPoint(0,y2), QPoint(x1,img_.height())));
        rects.push_back(QRect(QPoint(x2,y2), QPoint(img_.width(),img_.height())));
        painter.drawRects(rects);
    }

    QRect srcRect(QPoint(), img_.size());
    QRect dstRect(QPoint(0,0), size());
    QPainter painter2(this);
    painter2.drawImage(dstRect, tmp, srcRect);;
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    mousePressed_ = true;
    startx_ = event->localPos().x() / width() * img_.width();
    starty_ = event->localPos().y() / height() * img_.height();
    x1 = startx_;
    y1 = starty_;
    x2 = x1;
    y2 = y1;
    repaint();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    float x = event->localPos().x() / width() * img_.width();
    float y = event->localPos().y() / height() * img_.height();
    x1 = std::min<int>(x, startx_);
    x2 = std::max<int>(x, startx_);
    y1 = std::min<int>(y, starty_);
    y2 = std::max<int>(y, starty_);
    repaint();
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    float x = event->localPos().x() / width() * img_.width();
    float y = event->localPos().y() / height() * img_.height();
    x1 = std::min<int>(x, startx_);
    x2 = std::max<int>(x, startx_);
    y1 = std::min<int>(y, starty_);
    y2 = std::max<int>(y, starty_);
    repaint();
    mousePressed_ = false;
}

void ImageWidget::split()
{
    x1 = img_.width() / 3;
    x2 = x1 * 2;
    y1 = img_.height() / 3;
    y2 = y1 * 2;
    repaint();
}
