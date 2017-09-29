/**文件名： dialog_login.cpp
 * 说明：  登录UI界面对应的实现文件
 * 创建者： 刘功震
 */
#include "dialog_login.h"
#include "ui_dialog_login.h"

#include "global.h"

Dialog_login::Dialog_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_login)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    setFixedSize(400,300);
}

Dialog_login::~Dialog_login()
{
    delete ui;
}

/**
 * @brief Dialog_login::on_buttonBox_accepted
 * 点击登录按钮，验证身份，并修改全局变量的登录状态标志位
 */
void Dialog_login::on_buttonBox_accepted()
{
    //打开配置文件
    QFile fuser("user.csv");
    if(!fuser.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "错误！", "无法打开文件user.csv", QMessageBox::Ok);
        exit(0);
    }
    QTextStream fu(&fuser);
    fu.setCodec("GBK");
    fu.seek(0);

    QStringList linelist;
    while(!fu.atEnd())
    {
        linelist=fu.readLine().split(",");
        if(linelist.at(0)==ui->lineEdit->text() && linelist.at(1)==ui->lineEdit_2->text())
        {
            loginstatus=0;
            username=ui->lineEdit->text();
            this->close();
            fuser.close();
            return;
        }
    }
    QMessageBox::information(this,"提示","用户名或密码错误，请重试！",QMessageBox::Ok);
    fuser.close();
}

void Dialog_login::on_buttonBox_rejected()
{
    exit(0);
}
