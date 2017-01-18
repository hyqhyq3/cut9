#include "widget.h"
#include "ui_widget.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileDialog>
#include <filesystem>
#include <qdebug.h>
#include <iostream>

namespace fs = std::experimental::filesystem;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void Widget::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        openFileName_ = event->mimeData()->urls()[0].toLocalFile();
        if(!openFileName_.isEmpty())
        {
            ui->widget->setImage(openFileName_);
        }
    }
}


void Widget::on_btnOpen_clicked()
{
    openFileName_ = QFileDialog::getOpenFileName(this);
    if(!openFileName_.isEmpty())
    {
        ui->widget->setImage(openFileName_);
    }
}

void Widget::on_btnSplit_clicked()
{
    ui->widget->split();
}

void Widget::on_btnSave_clicked()
{
    if(!openFileName_.isEmpty())
    {
        fs::path p = openFileName_.toStdWString();
        std::wstring filename = p.stem().wstring();
        std::wstring extension = p.extension().wstring();
        fs::path pp = p.parent_path();

        QVector<QImage> images = ui->widget->getSplitImages();
        if(images.size() != 9)
        {
            return;
        }
        for(int i = 0; i < 9; ++i)
        {
            std::wstring saveFileName = (pp / (filename + L"-" + std::to_wstring(i+1) + extension)).wstring();
            images[i].save(QString::fromStdWString(saveFileName));
        }
    }
}
