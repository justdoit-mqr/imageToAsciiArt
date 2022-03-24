/*
 *@file:   imgtoasciiart.cpp
 *@author: 缪庆瑞
 *@date:   2017.7.27
 *@brief:  实现将给定的图片(QImage)转换成对应的字符串(Ascii码:黑白和html:彩色)
 */
#include "imgtoasciiart.h"
#include <QDebug>

ImgToAsciiArt::ImgToAsciiArt(QObject *parent) : QObject(parent)
{

}

ImgToAsciiArt::~ImgToAsciiArt()
{

}
/*
 *@brief:   将图片按照像素灰度值转换成对应的Ascii字符
 *@author:  缪庆瑞
 *@date:    2017.7.27
 *@param:   image:待转换图片
 *@param:   asciiArray:按照灰度级增序排列的ascii字符，空的话采取一组默认值
 *@return:  QString:返回值是对应灰度的ascii码串
 */
QString ImgToAsciiArt::imgToAscii(QImage &image, QByteArray asciiArray)
{
    //测试转换所需的时间
//    qDebug()<<"start time:"<<QTime::currentTime().toString("hh:mm:ss:zzz");
    if(asciiArray.isEmpty())
    {
        /*初始化默认的ascii码序列,由黑到白,可以根据实际情况进行调整达到最佳效果*/
        asciiArray.append("$B@%8&WM#wmkboazcvuxr(1]?*<+~_-;,'. ");
    }
    int width = image.width();
    int height = image.height();
    float charGrayWidth = 256.0/asciiArray.size();//ascii码序列一个字符表示的灰度值宽度(范围)
    int gray;//灰度值
    int arrayIndex;//灰度对应ascii码序列的索引
    QString asciiStr;
    for(int i =0;i<height;i++)
    {
        for(int j =0;j<width;j++)
        {
            //此处使用qt封装的方法求灰度值，公式为gray = (R * 11 + G * 16 + B * 5)/32;
            gray = qGray(image.pixel(j,i));//0-255
            arrayIndex = (int)(gray/charGrayWidth);//强制转换不进行四舍五入,不会越界
            asciiStr.append(asciiArray.at(arrayIndex));
        }
        asciiStr.append("\n");
    }
    asciiStr.remove(asciiStr.size()-1,1);//移除最后一个换行符
//    qDebug()<<"stop time:"<<QTime::currentTime().toString("hh:mm:ss:zzz");
    return asciiStr;
}
/*
 *@brief:   将图片对应点的像素颜色设置到字符上
 *@author:  缪庆瑞
 *@date:    2017.7.28
 *@param:   image:待转换图片
 *@param:   htmlStrSet:彩色字符集
 *@param:   isOrder:是否对字符集按顺序显示
 *@param:   isAlpha:图片是否具有透明度
 *@return:  QStringList:表示返回的值为对应色彩的html串(按行存放)
 */
QStringList ImgToAsciiArt::imgToHtml(QImage &image, QString htmlStrSet, bool isOrder, bool isAlpha)
{
    //测试转换所需的时间
//    qDebug()<<"start time:"<<QTime::currentTime().toString("hh:mm:ss:zzz");
    int width = image.width();
    int height = image.height();
    int htmlStrSize = htmlStrSet.size();//彩色字符集的长度
    int htmlStrIndex;//彩色字符集的默认索引
    QRgb rgb;
    QString rgbHexStr;
    QStringList htmlStrList;//按行存放像素对应图片的html串
    QString htmlStr;//图片的一行对应的html串
    if(isOrder)//顺序
    {
        for(int i =0;i<height;i++)
        {
            htmlStr.clear();
            htmlStrIndex = 0;
            for(int j =0;j<width;j++)
            {
                rgb = image.pixel(j,i);//获取像素点的rgb值
                //将像素点对应的argb对应的int值转换成8位16进制字符串(AARRGGBB),不足前补0
                rgbHexStr.clear();
                rgbHexStr.append("#");
                rgbHexStr.append(QString("%1").arg(rgb,8,16,QChar('0')));
                if(!isAlpha)
                {
                    rgbHexStr.replace(1,2,"");//去除透明度AA
                }
                htmlStr.append(QString("<span style='color:%1'>%2</span>")
                               .arg(rgbHexStr).arg(htmlStrSet.at(htmlStrIndex)));

                htmlStrIndex++;
                if(htmlStrIndex>=htmlStrSize)
                {
                    htmlStrIndex = 0;
                }
            }
            htmlStr.append("<br/>");//换行
            htmlStrList.append(htmlStr);
        }
    }
    else //随机
    {
        for(int i =0;i<height;i++)
        {
            htmlStr.clear();
            for(int j =0;j<width;j++)
            {
                htmlStrIndex = qrand()%htmlStrSize;
                rgb = image.pixel(j,i);//获取像素点的rgb值
                //将像素点对应的argb对应的int值转换成8位16进制字符串(AARRGGBB),不足前补0
                rgbHexStr.clear();
                rgbHexStr.append("#");
                rgbHexStr.append(QString("%0").arg(rgb,8,16,QChar('0')));
                if(!isAlpha)
                {
                    rgbHexStr.replace(1,2,"");//去除透明度AA
                }

                htmlStr.append(QString("<span style='color:%1'>%2</span>")
                               .arg(rgbHexStr).arg(htmlStrSet.at(htmlStrIndex)));

            }
            htmlStr.append("<br/>");
            htmlStrList.append(htmlStr);
        }
    }
//    qDebug()<<"stop time:"<<QTime::currentTime().toString("hh:mm:ss:zzz");
    return htmlStrList;
}

