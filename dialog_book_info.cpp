/**文件名：dialog_book_info.cpp
 * 说明：  读者详情UI界面的实现，展示读者几乎所有属性
 * 创建人： 刘功震
 */
#include "dialog_book_info.h"
#include "ui_dialog_book_info.h"

#include "dialog_inquiry.h"

/**
 * @brief Dialog_book_info::Dialog_book_info 显示图书详细信息
 * @param str 图书编号，mainwindow.cpp对应槽传递过来的
 * @param parent
 */
Dialog_book_info::Dialog_book_info(QString str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_book_info)
{
    ui->setupUi(this);
    num=str;

    QFile fbook("book.csv");
    if(!fbook.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "错误！", "无法打开文件book.csv", QMessageBox::Ok);
        return;
    }
    QTextStream fb(&fbook);
    fb.setCodec("GBK");
    fb.seek(poslocate(num,fbook));
    QStringList bookline = fb.readLine().split(",");

    //设置UI界面每一项的显示信息
    ui->label_num->setText(bookline.at(0));
    ui->label_name->setText(bookline.at(1));
    ui->label_author->setText(bookline.at(2));
    ui->label_publisher->setText(bookline.at(3));
    ui->textBrowser->setText(bookline.at(4));
    ui->label_date->setText(QDateTime::fromSecsSinceEpoch(bookline.at(5).toInt()).toString("yyyy/MM/dd hh:mm:ss"));
    ui->label_stock->setText(bookline.at(6));
    ui->label_count->setText(bookline.at(8));
}

Dialog_book_info::~Dialog_book_info()
{
    delete ui;
}

void Dialog_book_info::on_pushButton_clicked()
{
    this->close();
}
