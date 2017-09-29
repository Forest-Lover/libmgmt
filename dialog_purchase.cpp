/******************************************************************
文件名: dialog_purchase.cpp
创建人:张嘉轩
日　期:2017.5.20
描　述:图书购入模块，生成对应的图书编号
版　本: v1.00 Copyright(c).
******************************************************************/
#include "dialog_purchase.h"
#include "ui_dialog_purchase.h"

#include "book.h"
#include "dialog_log.h"
#include "dialog_inquiry.h"

Dialog_purchase::Dialog_purchase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_purchase)
{
    ui->setupUi(this);
    setWindowTitle("购书");
}

Dialog_purchase::~Dialog_purchase()
{
    delete ui;
}

void Dialog_purchase::on_buttonBox_accepted()
{
    Book book;
    QFile fbook("book.csv");
    if(!fbook.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::warning(this, "warning", "error opening file!", QMessageBox::Ok);
        return;
    }
    if(ui->lineEdit_name->text().isEmpty()||ui->lineEdit_author->text().isEmpty()||ui->lineEdit_publisher->text().isEmpty())
       fbook.close();
    else if(!ui->lineEdit_name->text().isEmpty()&&!ui->lineEdit_author->text().isEmpty()&&!ui->lineEdit_publisher->text().isEmpty())
    {
        book.setname(ui->lineEdit_name->text());
        book.setauthor(ui->lineEdit_author->text());
        book.setpublisher(ui->lineEdit_publisher->text());

        book.generatenum();//0.0
    if(isexist(book.num(), fbook))//0.0
    {
        book.refreshfromfile();//改变：姓名，作者，出版社，简介，日期，库存，预约信息，借阅次数
    }
    if(!ui->textEdit_intro->toPlainText().isEmpty())//简介以当前输入为准
        book.setintro(ui->textEdit_intro->toPlainText());

        book.setdate(Time());
        book.addstock(ui->spinBox_quantity->value());
        fbook.close();


        if(book.addtofile())//0.0
    {
        //写入日志
        Dialog_log log;
        log.addlog(0,book.num(),NULL);
        QMessageBox::information(this, "提示！", "购书成功!", QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, "提示", "购书失败!", QMessageBox::Ok);
    }}
    this->close();
}


void Dialog_purchase::on_buttonBox_rejected()
{
    this->close();
}
