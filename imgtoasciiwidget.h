/*
 *@file:   imgtoasciiwidget.h
 *@author: 缪庆瑞
 *@date:   2017.7.27
 *@brief:  图片转字画的界面
 */
#ifndef IMGTOASCIIWIDGET_H
#define IMGTOASCIIWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QFont>
#include "imgtoasciiart.h"

class ImgToAsciiWidget : public QWidget
{
    Q_OBJECT

public:
    ImgToAsciiWidget(QWidget *parent = 0);
    ~ImgToAsciiWidget();

private slots:
    void openImgFileSlot();//打开图片文件
    void generateAsciiArtSlot();//生成字符画
    void paintHtmlSlot();//绘制html的串
    void saveImageSlot();//保存字符画

    void setHtmlStrEnabled(bool enabled);//设置彩色字符集是否使能

private:
    void initParamWidget();//初始化参数配置部件
    void initImgWidget();//初始化字符画显示部件


    ImgToAsciiArt *imgToAsciiArt;//图片转换的对象

    QWidget *setParamWidget;//各项参数的部件的容器
    //第一行
    QPushButton *openBtn;//打开图片文件按钮
    QString imgAddrStr;//存放打开文件的路径
    QLineEdit *imgAddrEdit;//展示文件路径
    QPushButton *generateBtn;//生成按钮
    QPushButton *saveBtn;//保存按钮
    //第二行
    QCheckBox *colorBox;//彩色字符画，由html串表示
    QCheckBox *alphaBox;//透明度
    QLineEdit *htmlStrEdit;//用来构建彩色字符画的字符
    QButtonGroup *buttonGroup;//按钮组 方便确定选中的单选按钮
    QRadioButton *randomBtn;//随机
    QRadioButton *sequenceBtn;//顺序
    QSpinBox *fontSizeBox;//字符大小
    QComboBox *imgSizeBox;//图片大小等级
    QList<int> imgSizeList;//图片真实的大小（高度）

    QWidget *setImgWidget;//展示图片部件的容器
    QTextEdit *imgEdit;//展示图片
    QStringList htmlStrList;//存放彩色字符画对应色彩的html串(按行存放)
};

#endif // IMGTOASCIIWIDGET_H
