/**文件名： mainwindow.h
 * 说明：  程序主窗口对应的UI界面的头文件，包含了各种按键的信号与槽的声明
 * 创建人： 刘功震
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "common.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void irqbydialoginput(QString label, QStandardItemModel *model, int column);
    ~MainWindow();

private slots:

    void on_request_info(QModelIndex index);

    void onTimerOut();

    void onReceivelogAtoB(QString str);

    void onReceiveOrderList(QStringList list);

    void on_logoff_clicked();

    void on_purchase_triggered();

    void on_borrow_triggered();

    void on_return_3_triggered();

    void on_logirq_triggered();

    void on_borrow_2_clicked();

    void on_return_2_clicked();

    void on_action_triggered();

    void on_action_3_triggered();

    void on_action_5_triggered();

    void on_action_2_triggered();

    void on_action_6_triggered();

    void on_action_4_triggered();

    void on_action_9_triggered();

    void on_action_7_triggered();

    void on_readme_triggered();

    void on_about_triggered();

    void on_action_10_triggered();

    void on_dialog_fine_accept();

    void on_action_11_triggered();

private:
    Ui::MainWindow *ui;
    QDialog *dialog_fine=new QDialog();//结算欠款界面的UI设置，此处用代码设计UI界面，以下各项均为UI中的控件声明
    QLabel *label_num;//结算欠款时使用
    QLabel *label_sum;
    QLineEdit *lineedit_num;
    QLineEdit *lineedit_sum;
    QDialogButtonBox *buttonBox;
};

#endif // MAINWINDOW_H
