/**文件名： dialog_login.h
 * 说明：  登录UI界面对应的头文件
 * 创建者： 刘功震
 */
#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include "common.h"

namespace Ui {
class Dialog_login;
}

class Dialog_login : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_login(QWidget *parent = 0);
    ~Dialog_login();

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


private:
    Ui::Dialog_login *ui;
};

#endif // DIALOG_LOGIN_H
