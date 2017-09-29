/******************************************************************
文件名: dialog_borrow.h
创建人: 祁瑞
日　期:2017-5-20
描　述: 借书模块
版　本: v2.0
******************************************************************/
#ifndef DIALOG_BORROW_H
#define DIALOG_BORROW_H

#include "common.h"

namespace Ui {
class Dialog_borrow;
}

class Dialog_borrow : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_borrow(QWidget *parent = 0);
    ~Dialog_borrow();

private slots:
    void on_buttonBox_rejected();
    /**
     * @brief on_buttonBox_accepted
     */
    void on_buttonBox_accepted();

private:
    Ui::Dialog_borrow *ui;
signals:
    void sendorderlist(QStringList list);
};

#endif // DIALOG_BORROW_H
