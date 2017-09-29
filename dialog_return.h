/******************************************************************
文件名: dialog_return.h
创建人: 祁瑞
日　期:2017-5-20
描　述: 还书模块头文件
版　本: v2.0
******************************************************************/
#ifndef DIALOG_RETURN_H
#define DIALOG_RETURN_H

#include "common.h"

namespace Ui {
class Dialog_return;
}

class Dialog_return : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_return(QWidget *parent = 0);
    ~Dialog_return();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::Dialog_return *ui;
signals:
    void sendorderlist(QStringList list);
};

#endif // DIALOG_RETURN_H
