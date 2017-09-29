/**文件名：Dialog_addreader.h
 * 说明：  添加读者UI界面对应的头文件
 * 创建者： 刘功震
 */
#ifndef DIALOG_ADDREADER_H
#define DIALOG_ADDREADER_H

#include <QDialog>
#include "common.h"

namespace Ui {
class Dialog_addreader;
}

class Dialog_addreader : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_addreader(QWidget *parent = 0);
    ~Dialog_addreader();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_addreader *ui;
};

#endif // DIALOG_ADDREADER_H
