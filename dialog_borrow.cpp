/******************************************************************
文件名: dialog_borrow.cpp
创建人: 祁瑞
日　期:2017-5-20
描　述: 借书模块
版　本: v2.0
******************************************************************/
#include "dialog_borrow.h"
#include "ui_dialog_borrow.h"

#include "book.h"
#include "reader.h"
#include "dialog_log.h"
#include "dialog_inquiry.h"

Dialog_borrow::Dialog_borrow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_borrow)
{
    ui->setupUi(this);
    setWindowTitle("借书");
}

Dialog_borrow::~Dialog_borrow()
{
    delete ui;
}

void Dialog_borrow::on_buttonBox_rejected()
{
    this->close();
}
/**
 * @brief Dialog_borrow::on_buttonBox_accepted 完成借书功能
 */
void Dialog_borrow::on_buttonBox_accepted()
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

    QString readernuminput=ui->lineEdit->text();//读取借书者编号
    QString booknuminput=ui->lineEdit_2->text();//读取需借阅的图书编号

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
    fr.seek(poslocate(readernuminput, freader));//定位到借阅者所在的记录
    fb.seek(poslocate(booknuminput, fbook));//定位到借阅的图书所在的记录

    QString readerbuf = fr.readLine();//读取借阅者所在的整行信息
    QString bookbuf = fb.readLine();//读取图书所在的整行信息

    QStringList readerline = readerbuf.split(",");//将借阅者所在的整行信息以','为分割符划分成数组
    QStringList bookline = bookbuf.split(",");//将图书所在的整行信息以','为分割符划分成数组

    Reader reader(readerline);//构造读者对象

    Book book(bookline);//构造图书对象


    if(reader.fine()>MAX_FINE)
    {
        QMessageBox::information(this, "提示！", "欠款过多，请先交纳欠款方可继续借书！", QMessageBox::Ok);
        return;
    }

    if(book.stock()<book.orderrank(reader.num()))
    {
        if(QMessageBox::Yes==QMessageBox::question(this,
                                                   "提示！", "该书已经全部借出，是否预约！",
                                                   QMessageBox::Yes|QMessageBox::No))
        {
            if(book.orderstatus()==-1)
                QMessageBox::information(this, "提示！", "预约失败，预约人数已达上限！", QMessageBox::Ok);
            else if(book.addorder(reader.num()))
                QMessageBox::information(this, "提示！", "预约成功！", QMessageBox::Ok);
            else
                QMessageBox::information(this, "提示！", "预约失败！", QMessageBox::Ok);
        }
    }
    else
    {
        if(book.isinorderlist(reader.num())==true)//是否在已经预约该书的用户列表中
            book.suborder(reader.num());
        if(reader.borrowbook(book.num(),Time())==false)//修改读者信息
        {
            QMessageBox::information(this, "提示！", "同一套书只允许借阅一本！", QMessageBox::Ok);
            return;
        }
        book.borrowbook();//修改图书信息


        Dialog_log log;//写入日志
        log.addlog(1,book.num(),reader.num());
        QMessageBox::information(this, "提示！", "借书成功！", QMessageBox::Ok);
    }

    freader.close();
    fbook.close();

    reader.addtofile();
    book.addtofile();

    //温馨提醒：检查读者预约情况
    if(reader.orderarrivelist().size()!=0)
    {
        if(QMessageBox::Yes==QMessageBox::question(this,
                                                   "温馨提醒！", "您有新的预约书籍到库，是否查看？",
                                                   QMessageBox::Yes|QMessageBox::No))
        {
            emit sendorderlist(reader.orderarrivelist());
        }
    }
    return;
}

