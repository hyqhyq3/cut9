#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);

    void setImage(QString sFileName);

    void split();

    QVector<QImage> getSplitImages();

signals:

public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *paint);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private:
    QImage img_;
    int x1 = 0,x2 = 0, y1 = 0,y2 = 0;
    int startx_, starty_;
    bool mousePressed_ = false;
};

#endif // IMAGEWIDGET_H
