/**文件名： dialog_addreader.cpp
 * 说明：  添加读者UI界面对应的槽函数的实现
 * 创建人：刘功震
 */
#include "dialog_addreader.h"
#include "ui_dialog_addreader.h"

#include "reader.h"

Dialog_addreader::Dialog_addreader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_addreader)
{
    ui->setupUi(this);
}

Dialog_addreader::~Dialog_addreader()
{
    delete ui;
}

/**
 * @brief Dialog_addreader::on_pushButton_clicked
 * 点击确认依据输入添加该读者到文件
 */
void Dialog_addreader::on_pushButton_clicked()
{
    Reader newreader;
    QString num,name,institute;
    num=ui->lineEdit_num->text();
    name=ui->lineEdit_name->text();
    institute=ui->lineEdit_institute->text();
    if(num.isEmpty()||name.isEmpty()||institute.isEmpty())//验证输入是否合法
    {
        QMessageBox::information(this,"提示","请输入完整信息",QMessageBox::Ok);
        return;
    }
    newreader.setnum(num);
    newreader.setname(name);
    newreader.setinstitute(institute);
    newreader.settype(ui->comboBox->currentIndex());

    if(newreader.addtofile()==true)//写入文件
    {
        QMessageBox::information(this,"提示","添加成功",QMessageBox::Ok);
        this->close();
    }
}
