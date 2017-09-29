/******************************************************************
文件名: dialog_log.h
创建人: 陈鸿文（2015211477）
日　期: 2017/4/19
描　述: 日志模块函数
版　本: v1.70 Copyright(c).
******************************************************************/
#ifndef DIALOG_LOG_H
#define DIALOG_LOG_H

#include "common.h"

namespace Ui {
class Dialog_log;
}

class Dialog_log : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_log(QWidget *parent = 0);
    ~Dialog_log();

    int Date(void){return date;}
    int Type(void){return type;}
    QString Booknum(void){return booknum;}
    QString Readernum(void){return readernum;}
    QString Usernum(void){return usernum_;}

    void setdate(int n){date=n;}
    void settype(int n){type=n;}
    void setbooknum(QString str){booknum=str;}
    void setreadernum(QString str){readernum=str;}
    void setusernum(QString str){usernum_=str;}

    /**
     * @brief addtofile 将日志写入log.csv文件
     * @return 正确写入返回true，否则返回false
     */
    bool addtofile(void);

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
    void addlog(int type, QString bnum, QString rnum);//生成并写入日志hongwen
    /**
     * @brief logfromAtoB   返回日期A到日期B之间的所有日志信息
     * @param A     开始日期（秒）
     * @param B     结束日期（秒）
     * @return      开始行到结束行的所有日志信息
     */
    QString logfromAtoB(int A, int B);//查找一段区间里面的日志hongwen


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog_log *ui;
    int date=0;//操作日期
    int type=0;//操作类型：0 购书、1 借书、2 还书、3 查询
    QString booknum;//图书编号
    QString readernum;//读者编号
    QString usernum_;//管理员账号
signals:
    void sendlogAtoB(QString str);
};

#endif // DIALOG_LOG_H
