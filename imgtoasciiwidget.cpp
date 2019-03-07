/*
 *@file:   imgtoasciiwidget.cpp
 *@author: 缪庆瑞
 *@date:   2017.7.27
 *@brief:  图片转字画的界面
 */
#include "imgtoasciiwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QTimer>
#define FONT_FAMILY "宋体"

ImgToAsciiWidget::ImgToAsciiWidget(QWidget *parent)
    : QWidget(parent)
{
    initParamWidget();
    initImgWidget();
    imgToAsciiArt = new ImgToAsciiArt(this);

    //根据屏幕最大高度设置对应等级下图片的真实高度
    int screenHeight = qApp->desktop()->screen()->height();//获取设备整个屏幕的高度
    imgSizeList.append(screenHeight-150);
    imgSizeList.prepend(screenHeight-210);
    imgSizeList.prepend(screenHeight-270);
    imgSizeList.prepend(screenHeight-330);
    imgSizeList.prepend(screenHeight-390);

    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->addWidget(setParamWidget);
    vBoxLayout->addWidget(setImgWidget);

    imgAddrStr = ":/image/happy.ico";
    generateAsciiArtSlot();
    this->showMaximized();//最大化

}

ImgToAsciiWidget::~ImgToAsciiWidget()
{

}
/*
 *@brief:   初始化参数容器部件
 *@author:  缪庆瑞
 *@date:    2017.7.30
 */
void ImgToAsciiWidget::initParamWidget()
{
    setParamWidget = new QWidget();
    setParamWidget->setFont(QFont("宋体",15));
    setParamWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    //初始化第一行部件
    openBtn = new QPushButton("浏览");
    imgAddrEdit = new QLineEdit();
    generateBtn = new QPushButton("生成");
    saveBtn = new QPushButton("保存");
    connect(openBtn,SIGNAL(clicked()),this,SLOT(openImgFileSlot()));
    connect(generateBtn,SIGNAL(clicked()),this,SLOT(generateAsciiArtSlot()));
    connect(saveBtn,SIGNAL(clicked()),this,SLOT(saveImageSlot()));
    //初始化第二行部件
    colorBox = new QCheckBox("彩色");
    colorBox->setChecked(true);
    connect(colorBox,SIGNAL(clicked(bool)),this,SLOT(setHtmlStrEnabled(bool)));
    alphaBox = new QCheckBox("透明度");
    QLabel *charsLabel = new QLabel("字符集：");
    charsLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    //charsLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    htmlStrEdit = new QLineEdit();
    //通过按钮组方便获取选中的单选按钮
    buttonGroup = new QButtonGroup();
    randomBtn = new QRadioButton("随机");
    randomBtn->setChecked(true);//默认选中随机
    sequenceBtn = new QRadioButton("顺序");
    buttonGroup->addButton(randomBtn,0);
    buttonGroup->addButton(sequenceBtn,1);
    QHBoxLayout *hBoxLayout = new QHBoxLayout();//通过一个布局使其两个单选按钮紧挨着
    hBoxLayout->addWidget(randomBtn);
    hBoxLayout->addWidget(sequenceBtn);
    //hBoxLayout->addStretch(2);

    QLabel *fontSizeLabel = new QLabel("字符大小：");
    fontSizeLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    fontSizeBox = new QSpinBox();
    fontSizeBox->setMinimum(2);
    fontSizeBox->setMaximum(12);
    fontSizeBox->setValue(6);
    QLabel *imgSizeLabel = new QLabel("图片大小：");
    imgSizeLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    imgSizeBox = new QComboBox();
    QStringList sizeList;
    sizeList<<"1"<<"2"<<"3"<<"4"<<"5";//从小到大 等级
    imgSizeBox->addItems(sizeList);
    imgSizeBox->setCurrentText("3");

    //参数部件布局
    QGridLayout *gridLayout = new QGridLayout(setParamWidget);
    gridLayout->setMargin(2);
    gridLayout->addWidget(openBtn,0,0,1,2);
    gridLayout->addWidget(imgAddrEdit,0,2,1,4);
    gridLayout->addWidget(generateBtn,0,6,1,2);
    gridLayout->addWidget(saveBtn,0,8,1,2);

    gridLayout->addWidget(colorBox,1,0,1,1);
    gridLayout->addWidget(alphaBox,1,1,1,1);
    gridLayout->addWidget(charsLabel,1,2,1,1);
    gridLayout->addWidget(htmlStrEdit,1,3,1,2);
    gridLayout->addLayout(hBoxLayout,1,5,1,1);
    gridLayout->addWidget(fontSizeLabel,1,6,1,1);
    gridLayout->addWidget(fontSizeBox,1,7,1,1);
    gridLayout->addWidget(imgSizeLabel,1,8,1,1);
    gridLayout->addWidget(imgSizeBox,1,9,1,1);
}
/*
 *@brief:   初始化图片容器部件
 *@author:  缪庆瑞
 *@date:    2017.7.30
 */
void ImgToAsciiWidget::initImgWidget()
{
    setImgWidget = new QWidget();
    setImgWidget->setStyleSheet("background-color:white;");
    imgEdit = new QTextEdit();//使用文本编辑器展示字符画
    imgEdit->setReadOnly(true);
    //关闭滚动条 因滚动条会占据一定的空间，设置的固定大小不够存放对应的字符串
    imgEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    imgEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    imgEdit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QGridLayout *gridLayout = new QGridLayout(setImgWidget);
    gridLayout->addWidget(imgEdit,0,0,Qt::AlignCenter);
}
/*
 *@brief:   打开图片文件
 *@author:  缪庆瑞
 *@date:    2017.7.30
 */
void ImgToAsciiWidget::openImgFileSlot()
{
    imgAddrStr = QFileDialog::getOpenFileName(this,"选择图片","./image","(*.png *.jpg *.jpeg *.bmp *.ico)");
    if(imgAddrStr.isEmpty())//如果取消打开对话框返回空的字符串
    {
        return;
    }
    imgAddrEdit->setText(imgAddrStr);
}
/*
 *@brief:   生成字符画
 *@author:  缪庆瑞
 *@date:    2017.7.30
 */
void ImgToAsciiWidget::generateAsciiArtSlot()
{
    if(imgAddrStr.isEmpty())
    {
        QMessageBox::information(this,"imgToAsciiArt","请先选择一张图片文件");
        return;
    }
    QImage image(imgAddrStr);
    if(image.isNull())//图片加载失败函数返回
    {
        QMessageBox::information(this,"imgToAsciiArt","加载图片失败，请确认图片格式！");
        return;
    }

    float aspectRatio = image.width()/(float)image.height();//原始图片宽高比
    //qDebug()<<"width:height = "<<aspectRatio;
    imgEdit->clear();//先清空之前的内容
    htmlStrList.clear();
    int fontSize = fontSizeBox->value();//字符的字体大小
    imgEdit->setFont(QFont(FONT_FAMILY,fontSize));
    //根据图片大小等级获取显示时的真实高度 并通过宽高比得到真实宽度
    int realHeight = imgSizeList.at(imgSizeBox->currentIndex());
    int realWidth = realHeight*aspectRatio;
    //字符画显示部件略大于实际显示图片，因为显示字符与部件边框间有一定的距离
    imgEdit->setFixedSize(realWidth+10,realHeight+8);
    if(colorBox->isChecked())//生成彩色字符画
    {
        QString htmlStrSet = htmlStrEdit->text();//获取彩色字符集
        if(htmlStrSet.isEmpty())
        {
            htmlStrSet.append("#");
        }
        //使用真实高度除以当前字体下的行间距，得到行数也就是图片实际的缩放高度
        int imgHeight = realHeight/imgEdit->fontMetrics().lineSpacing();
        //使用真实宽度除以当前字体下的字符宽度，得到字符个数即图片实际的缩放宽度
        int imgWidth = realWidth/imgEdit->fontMetrics().width(htmlStrSet.at(0));
        image = image.scaled(imgWidth,imgHeight);
        //qDebug()<<"width:"<<image.width()<<"height:"<<image.height();
        htmlStrList = imgToAsciiArt->imgToHtml(image,htmlStrSet,(bool)buttonGroup->checkedId(),alphaBox->isChecked());
        //qDebug()<<htmlStrList;
        /*因为彩色字符画对应的html串比较长，在实际绘制时需要花费较多的时间(取决于图片大小和
         机器速度)，所以采用按(多)行依次显示，避免完整绘制期间长时间卡顿，但是按(多)行绘制
        出现了一个问题，即只有完全绘制完成，才会将imgEdit部件按其大小居中显示。所以这里使用
        一个单次定时器，实现先将该函数退出，由程序处理绘图事件将imgEdit部件居中，然后定时时
        间超出后执行真正的字符画绘制过程*/
        QTimer::singleShot(100,this,SLOT(paintHtmlSlot()));
    }
    else // 黑白字符画
    {
        //使用真实高度除以当前字体下的行间距，得到行数也就是图片实际的缩放高度
        int imgHeight = realHeight/imgEdit->fontMetrics().lineSpacing();
        //使用真实宽度除以当前字体下的字符宽度，得到字符个数即图片实际的缩放宽度
        int imgWidth = realWidth/imgEdit->fontMetrics().width("a");
        image = image.scaled(imgWidth,imgHeight);
        //qDebug()<<"width:"<<image.width()<<"height:"<<image.height();
        QString asciiStr = imgToAsciiArt->imgToAscii(image);
        imgEdit->setPlainText(asciiStr);
    }
}
/*
 *@brief:   绘制html对应的彩色字符画
 *@author:  缪庆瑞
 *@date:    2017.8.5
 */
void ImgToAsciiWidget::paintHtmlSlot()
{
    //根据彩色HTML字符串列表，按行追加数据
    for(int i=0;i<htmlStrList.size();i++)
    {
        imgEdit->append(htmlStrList.at(i));
        /*因为在字体较小，图片较大的情况下，实际会有很多行，如果追加每一行都绘制一次的话，
        同样比较费时，这里的处理是对每张显示的字符画，按照12次显示完整张图片*/
        if(!(i%(htmlStrList.size()/12)))
        {
            repaint();
        }
    }
}
/*
 *@brief:   保存图片
 *@author:  缪庆瑞
 *@date:    2017.8.5
 */
void ImgToAsciiWidget::saveImageSlot()
{
    QString saveImagename = QFileDialog::getSaveFileName(this,"保存图片","./image/字符画.png","(*.png *.jpg *.bmp, *.ico)");
    if(saveImagename.isEmpty())//如果取消保存对话框返回空的字符串
    {
        return;
    }
    int imgWidth = imgEdit->width();
    int imgHeight = imgEdit->height();
    QImage image;
    //必须设置大小,不然会无法会“QWidget::paintEngine: Should no longer be called”
    //QPixmap pixmap(imgWidth,imgHeight);
    if(alphaBox->isChecked())//保存的图片具有透明度
    {
        image = QImage(imgWidth,imgHeight,QImage::Format_ARGB32);
    }
    else
    {
        image = QImage(imgWidth,imgHeight,QImage::Format_RGB32);
    }
    //将部件的指定区域渲染到image上,第一个参数是渲染的目标设备，第二个参数是在目标设备的起始渲染点，
    //第三个参数指定被渲染部件的区域
    imgEdit->render(&image,QPoint(),QRegion(0,0,imgWidth,imgHeight));//将widget页渲染到pixmap上
    //pixmap=pixmap.scaled(imgWidth*2,imgHeight*2);//将图片伸缩到指定大小，默认参数忽略宽高比例
    //第一个参数指定保存的文件名，第二个图片格式，第三个是图片质量0-100
    if(image.save(saveImagename,"PNG",90))//保存图片
    {
        QMessageBox::information(this,"information","图片已成功保存");
    }
    else
    {
        QMessageBox::information(this,"information","图片保存失败");
    }
}
/*
 *@brief:   设置彩色字符集使能
 *@author:  缪庆瑞
 *@date:    2017.8.5
 *@param:   enabled:设置彩色字符集编辑框是否使能
 */
void ImgToAsciiWidget::setHtmlStrEnabled(bool enabled)
{
    htmlStrEdit->setEnabled(enabled);
    alphaBox->setEnabled(enabled);
}

