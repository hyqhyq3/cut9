#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


private slots:
    void on_btnOpen_clicked();

    void on_btnSplit_clicked();

    void on_btnSave_clicked();

private:
    Ui::Widget *ui;
    QString openFileName_;
};

#endif // WIDGET_H
