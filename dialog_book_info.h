/**文件名： dialog_book_info.h
 * 说明：  双击图书条目后弹出的图书详情UI界面对应的头文件
 * 创建人： 刘功震
 */
#ifndef DIALOG_BOOK_INFO_H
#define DIALOG_BOOK_INFO_H

#include <QDialog>
#include "common.h"

namespace Ui {
class Dialog_book_info;
}

class Dialog_book_info : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Dialog_book_info
     * @param str
     * @param parent
     */
    explicit Dialog_book_info(QString str,QWidget *parent = 0);
    ~Dialog_book_info();
    QString num;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_book_info *ui;
};

#endif // DIALOG_BOOK_INFO_H
