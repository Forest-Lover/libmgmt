/******************************************************************
文件名: dialog_return.cpp
创建人: 祁瑞
日　期:2017-5-20
描　述: 还书模块
版　本: v2.0
******************************************************************/
#include "dialog_return.h"
#include "ui_dialog_return.h"

#include "book.h"
#include "reader.h"
#include "dialog_log.h"
#include "dialog_inquiry.h"

Dialog_return::Dialog_return(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_return)
{
    ui->setupUi(this);
    setWindowTitle("还书");
}

Dialog_return::~Dialog_return()
{
    delete ui;
}

void Dialog_return::on_buttonBox_rejected()
{
    this->close();
}
/**
 * @brief Dialog_return::on_buttonBox_accepted 完成还书功能
 */
void Dialog_return::on_buttonBox_accepted()
{
    QFile freader("reader.csv");
    QFile fbook("book.csv");
    if(!freader.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "错误！", "无法打开文件reader.csv", QMessageBox::Ok);
        return;
    }
    if(!fbook.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "错误！", "无法打开文件book.csv", QMessageBox::Ok);
        return;
    }

    QString readernuminput=ui->lineEdit->text();//得到用户编号
    QString booknuminput=ui->lineEdit_2->text();//得到图书编号

    if(!isexist(readernuminput, freader))
    {
        QMessageBox::warning(this, "错误！", "该读者不存在！", QMessageBox::Ok);
        return;
    }
    if(!isexist(booknuminput, fbook))
    {
        QMessageBox::warning(this, "错误！", "该书不存在！", QMessageBox::Ok);
        return;
    }
    QTextStream fb(&fbook);
    QTextStream fr(&freader);
    fb.setCodec("GBK");
    fr.setCodec("GBK");
    fr.seek(poslocate(readernuminput, freader));//在读者文件中定位还书者所在记录
    fb.seek(poslocate(booknuminput, fbook));//在图书文件中定位图书所在记录

    QString readerbuf = fr.readLine();//读取还书者的完整信息
    QString bookbuf = fb.readLine();//读取图书的完整信息

    QStringList readerline = readerbuf.split(",");//将借阅者信息以','分割成数组
    QStringList bookline = bookbuf.split(",");//将图书信息以','分割成数组

    Reader reader(readerline);
    Book book(bookline);

    freader.close();
    fbook.close();

    if(reader.returnbook(book.num(),Time())==false)
    {
        QMessageBox::information(this, "提示", "还书失败！你可能尚未借阅该书",QMessageBox::Ok);
        return;
    }
    book.plusstock();//还书成功


    reader.addtofile();//更新读者文件信息
    book.addtofile();//更新图书文件信息

    Dialog_log log; //写入日志
    log.addlog(2,book.num(),reader.num());
    QMessageBox::information(this, "提示！", "还书成功！", QMessageBox::Ok);

    if(reader.orderarrivelist().size()!=0) //温馨提醒：检查读者预约情况
    {
        if(QMessageBox::Yes==QMessageBox::question(this,
                                                   "温馨提醒！", "您有新的预约书籍到库，是否查看？",
                                                   QMessageBox::Yes|QMessageBox::No))
        {
            emit sendorderlist(reader.orderarrivelist());//显示预约到达图书列表
        }
    }
    return;

}
