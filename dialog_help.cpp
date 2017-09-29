#include "dialog_help.h"
#include "ui_dialog_help.h"

Dialog_help::Dialog_help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_help)
{
    ui->setupUi(this);
    this->setWindowTitle("使用说明");
}

Dialog_help::~Dialog_help()
{
    delete ui;
}

void Dialog_help::on_pushButton_clicked()
{
    close();
}
