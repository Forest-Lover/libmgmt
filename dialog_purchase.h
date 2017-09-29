/******************************************************************
文件名: dialog_purchase.h
创建人:张嘉轩
日　期:2017.5.20
描　述:图书购入模块，生成对应的图书编号
版　本: v1.00 Copyright(c).
******************************************************************/
#ifndef DIALOG_PURCHASE_H
#define DIALOG_PURCHASE_H

#include "common.h"

namespace Ui {
class Dialog_purchase;
}

class Dialog_purchase : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_purchase(QWidget *parent = 0);
    ~Dialog_purchase();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog_purchase *ui;
};

#endif // DIALOG_PURCHASE_H
