# ImageToAscillArt
这是一个将图片转换成字符画的小程序。
## 前言
首先说一下什么是字符画，顾名思义即通过字符组合成图片。具体分为两种：  
1.通过将图片像素rgb经过公式转换成灰度值，然后由对应灰度值的ascii字符表示该像素，进而组成字符画。  
2.通过html语言将提取到的像素rgb对应设置到字符上，然后组成字符画。  
## 功能概述:
本程序主要有两个类组成：  
**ImgToAsciiArt：**  
该类负责将给定的图片转换成对应灰度的ascii字符串或者对应色彩的html字符串，主要提供下面两种方法，分别转换ascii字符串和html串，具体内容详见代码。  
QString imgToAscii(QImage &image,QByteArray asciiArray=QByteArray());  
QStringList imgToHtml(QImage &image, QString htmlStrSet, bool isOrder,bool isAlpha = false);  
**ImgToAsciiWidget：**  
该类则主要负责界面，包括参数的设置，图片文件的选择，字符画的生成与保存。  
## 运行截图:
![Ascii码字符画1.png](./screenshot/Ascii码字符画1.png "Ascii码字符画1.png")  
![Ascii码字符画2.png](./screenshot/Ascii码字符画2.png "Ascii码字符画2.png")  
![彩色字符画1.png](./screenshot/彩色字符画1.png "彩色字符画1.png")  
![彩色字符画2.png](./screenshot/彩色字符画2.png "彩色字符画2.png")  
![彩色字符画3.png](./screenshot/彩色字符画3.png "彩色字符画3.png")  
## 小结:
该程序没啥实际用途，纯粹是周末无聊做着玩。  
经过实际测试对于一些小分辨率层次分明的ico图片转换的效果还不错，目前程序转换ascii灰度值的字符由内部指定，因为不同字符的灰度有一定的序列，排序越准，字符画效果越好。而html字符画的字符可以由用户指定，但因为不同字体下一些字符的宽度是不同的，所以目前字体选择比较局限，内部使用字符等宽的宋体，可以实现所有的英文字符或者中文字符不论大小写宽度是一致的。但由于中文和英文的宽度是不一致的，所以暂时还不能中英文混合使用。此外由于彩色字符画是通过html文本字符串实现的，相对ascii码串较长，在实际字符画绘制时，会花费较多的时间，图片转换所得html串越长越慢，目前采用一定数量的行绘制一次，解决了长时间程序无响应的问题，但完全绘制完成还是需要一定的时间，暂时还没找到更好的办法。
## 作者联系方式
**邮箱:justdoit_mqr@163.com**  
**新浪微博:@为-何-而来**  

