#ifndef DIALOG_HELP_H
#define DIALOG_HELP_H

#include <QDialog>
#include "common.h"

namespace Ui {
class Dialog_help;
}

class Dialog_help : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_help(QWidget *parent = 0);
    ~Dialog_help();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_help *ui;
};

#endif // DIALOG_HELP_H
