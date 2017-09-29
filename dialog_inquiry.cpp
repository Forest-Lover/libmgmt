/**文件名： dialog_inquiry.cpp
 * 说明：  本文件不对应UI文件，提供查询函数供调用
 *        可以查询：模拟系统当前时间、某一字符串的编号在对应文件中是否存在、以及如果存在文件指针POS的位置
 * 创建人： 刘功震
 */
#include "dialog_inquiry.h"
#include "ui_dialog_inquiry.h"

#include "global.h"


Dialog_inquiry::Dialog_inquiry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_inquiry)
{
    ui->setupUi(this);
}

Dialog_inquiry::~Dialog_inquiry()
{
    delete ui;
}

/**
 * @brief isexist   在file中是否存在编号为str的项目
 * @param str   编号
 * @param file  文件流
 * @return      存在：true； 不存在：false
 */
bool isexist(QString str, QFile & file)//0.0
{
    qDebug()<<"str:"<<str;
    QString linebuf;
    QStringList list;

    file.seek(0);
    while(!file.atEnd())
    {
        linebuf=file.readLine();
        list=linebuf.split(",");
        qDebug()<<"list.at(0):"<<list.at(0);

        if(!QString::compare(list.at(0),str))
            return true;
    }

    return false;
}

/**
 * @brief poslocate 返回str编号对应的pos位置，以便写入已经存在的项目是进行覆盖写入
 * @param str   编号
 * @param file  文件流
 * @return      str编号对应的pos位置
 */
qint64 poslocate(QString str, QFile & file)
{
    QString linebuf;
    QStringList list;
    qint64 pos;

    file.seek(0);
    while(!file.atEnd())
    {
        pos=file.pos();
        linebuf=file.readLine();
        list=linebuf.split(",");

        if(QString::compare(list.at(0),str)==0)
            return pos;
    }
    return file.size();
}

/**
 * @brief   Time 获取模拟系统的时间，单位：秒
 * @return  从系统登录成功开始到函数调用的模拟秒数
 */
int Time()
{
    return timefromstart*VSEC_PER_RSEC/1000;
}

void Dialog_inquiry::on_buttonBox_accepted()
{

}
