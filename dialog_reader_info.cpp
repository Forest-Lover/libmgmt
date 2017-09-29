/**文件名： dialog_reader_info.cpp
 * 说明：  双击读者条目后弹出的读者详情UI界面对应的源文件
 * 创建人： 刘功震
 */
#include "dialog_reader_info.h"
#include "ui_dialog_reader_info.h"

#include "dialog_inquiry.h"

/**
 * @brief Dialog_reader_info::Dialog_reader_info双击后显示读者详情
 * @param str 读者编号
 * @param parent
 */
Dialog_reader_info::Dialog_reader_info(QString str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_reader_info)
{
    ui->setupUi(this);
    num=str;

    QStringListModel *model = new QStringListModel();//设置显示模板
    ui->listView->setModel(model);
    QStringList list;

    QFile freader("reader.csv");//打开文件
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
    QTextStream fb(&fbook);
    QTextStream fr(&freader);
    fb.setCodec("GBK");
    fr.setCodec("GBK");
    fr.seek(poslocate(num, freader));

    QStringList readerline = fr.readLine().split(",");//每一行之间项目用逗号分隔
    QStringList booklist=readerline.at(6).split("/");//借阅的图书的项用斜线分隔

    ui->label_num->setText(readerline.at(0));
    ui->label_name->setText(readerline.at(1));
    ui->label_institute->setText(readerline.at(2));
    ui->label_type->setText(readerline.at(3)==0?"学生":"教师");

    for(int i=0; i<booklist.size(); i++)//按行显示信息
    {
        if(booklist.at(i).isEmpty())
            break;
        QStringList item=booklist.at(i).split("|");
        fb.seek(poslocate(item.at(0), fbook));
        QStringList bookline = fb.readLine().split(",");
//        qDebug()<<"bookline"<<bookline;
        list << QString::number(i+1)+" "+bookline.at(1)+"   "+QDateTime::fromSecsSinceEpoch(item.at(1).toInt()).toString("yyyy/MM/dd hh:mm:ss");
    }
    model->setStringList(list);
}

Dialog_reader_info::~Dialog_reader_info()
{
    delete ui;
}

void Dialog_reader_info::on_pushButton_clicked()
{
    this->close();
}
