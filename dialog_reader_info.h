/**文件名： dialog_reader_info.h
 * 说明：  双击读者条目后弹出的读者详情UI界面对应的头文件
 * 创建人： 刘功震
 */
#ifndef DIALOG_READER_INFO_H
#define DIALOG_READER_INFO_H

#include <QDialog>
#include "common.h"

namespace Ui {
class Dialog_reader_info;
}

class Dialog_reader_info : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_reader_info(QString str, QWidget *parent = 0);
    ~Dialog_reader_info();
    QString num;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_reader_info *ui;
};

#endif // DIALOG_READER_INFO_H
