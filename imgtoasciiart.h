/*
 *@file:   imgtoasciiart.h
 *@author: 缪庆瑞
 *@date:   2017.7.27
 *@brief:  实现将给定的图片(QImage)转换成对应的字符串(Ascii码:黑白和html:彩色)
 */
#ifndef IMGTOASCIIART_H
#define IMGTOASCIIART_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <QByteArray>
#include <QTime>
#include <QtGlobal>

class ImgToAsciiArt : public QObject
{
    Q_OBJECT
public:
    explicit ImgToAsciiArt(QObject *parent = 0);
    ~ImgToAsciiArt();

    QString imgToAscii(QImage &image,QByteArray asciiArray=QByteArray());
    QStringList imgToHtml(QImage &image, QString htmlStrSet, bool isOrder,bool isAlpha = false);

signals:

public slots:

private:

};

#endif // IMGTOASCIIART_H
