/******************************************************************
文件名: dialog_log.cpp
创建人: 陈鸿文（2015211477）
日　期: 2017/4/19
描　述: 日志模块函数
版　本: v1.70 Copyright(c).
******************************************************************/

#include "dialog_log.h"
#include "ui_dialog_log.h"
#include "dialog_inquiry.h"
#include "global.h"

Dialog_log::Dialog_log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_log)
{
    ui->setupUi(this);
}

Dialog_log::~Dialog_log()
{
    delete ui;
}

/**
 * @brief addtofile 将日志写入log.csv文件
 * @return 正确写入返回true，否则返回false
 */
bool Dialog_log::addtofile()
{
    QFile flog("log.csv");
    QTextStream fl(&flog);
    fl.setCodec("GBK");
    if(!flog.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;

    flog.seek(flog.size());
    fl << date << "," << type << ","
       << booknum << "," << readernum << ","
       << usernum_ << endl;

    flog.flush();
    flog.close();
    return true;
}


/**
 * @brief addlog 按类型生成并添加日志（time（）获取时间，username全局变量）
 * @param type   操作类型：0 购书、1 借书、2 还书、3 查询
 * @param bnum   图书编号
 * @param rnum   读者编号
 * 备注：  可能涉及的Qt类有：QFile,QString,QTextStream
 *        涉及全局变量：username 用户名（main.cpp定义）
 *        函数调用：addtofile()
 *                time() 在dialog_inquiry.h声明
 */
void Dialog_log::addlog(int _type, QString bnum, QString rnum)
{
    date = Time();
    booknum = bnum;
    usernum_ = username;
    type = _type;
    if(type == 0)
        readernum = "";
    else
        readernum = rnum;
    addtofile();
}
/**
 * @brief logfromAtoB   返回日期A到日期B之间的所有日志信息
 * @param A     开始日期（秒）
 * @param B     结束日期（秒）
 * @return      开始行到结束行的所有日志信息
 */
QString Dialog_log::logfromAtoB(int A, int B)
{
    QString linebuf;
    QString machline = "";
    QString machlinesub = "";
    QStringList list;
    QFile flog("log.csv");

    if(!flog.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
        return "OPEN FILE FAILED!";
    flog.seek(0);
    if(A>B)
        return "";
    linebuf=flog.readLine();
    list=linebuf.split(",");

    if (list.at(0).toInt() > B)//开始日期大于结束日期返回空
        return "";
    else if(list.at(0).toInt() == B)//开始日期等于结束日期返回当前行
        return linebuf;
    else
    {
        while(!flog.atEnd())//还没到日志结尾时循环添加符合的日志记录
        {
            if(list.at(0).toInt() >= A)//日志日期比开始日期大，寻找到A的位置，开始将记录放进buffer
            {
                machline = machline + linebuf;//符合条件放进buffer，自带换行符，不用添加分隔符
                while(!flog.atEnd())//开始寻找B
                {
                    if(list.at(0).toInt() > B)//说明要找的日志记录在前一条日志与当前日志之间，应返回少一条记录的buffer
                        return machlinesub;
                    else if(list.at(0).toInt() == B)//正好相等时直接返回当前buffer
                        return machline;
                    else
                    {
                        linebuf = flog.readLine();
                        list=linebuf.split(",");
                        machlinesub = machline;//关键代码，记录下少一条日志记录的buffer，为后面判断结束日期位置做准备
                        machline = machline + linebuf;
                    }
                }
                return machline;//到这里说明结束日期大于记录最晚日期，直接返回buffer
            }
            else//日志日期比开始日期小时不放进buffer
            {
                linebuf = flog.readLine();//直接读取下一行
                list=linebuf.split(",");
            }
        }
        if(list.at(0).toInt() < A)//日志记录最晚日期大于查询的开始日期返回空
            return "";
        else
            return linebuf;//返回当前行
    }
}

void Dialog_log::on_buttonBox_accepted()
{
    QDateTime A,B;
    A=ui->dateTimeEdit->dateTime();
    B=ui->dateTimeEdit_2->dateTime();
//    qDebug()<<logfromAtoB(A.toSecsSinceEpoch(   ),B.toSecsSinceEpoch())<<endl;
    emit sendlogAtoB(logfromAtoB(A.toSecsSinceEpoch(),B.toSecsSinceEpoch()));
}

void Dialog_log::on_buttonBox_rejected()
{
    this->close();
}
