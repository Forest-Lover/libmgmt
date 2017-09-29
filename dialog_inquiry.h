/**文件名： dialog_inquiry.h
 * 说明：  本文件不对应UI文件，提供查询函数供调用
 *        可以查询：模拟系统当前时间、某一字符串的编号在对应文件中是否存在、以及如果存在文件指针POS的位置
 * 创建人： 刘功震
 */
#ifndef DIALOG_INQUIRY_H
#define DIALOG_INQUIRY_H

#include "common.h"

namespace Ui {
class Dialog_inquiry;
}

class Dialog_inquiry : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_inquiry(QWidget *parent = 0);
    ~Dialog_inquiry();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_inquiry *ui;
};

/**
 * @brief   time 获取模拟系统的时间，单位：秒
 * @return  从系统登录成功开始到函数调用的模拟秒数
 */
int Time(void);//获取模拟系统时间，单位：秒

/**
 * @brief isexist   在file中是否存在编号为str的项目
 * @param str   编号
 * @param file  文件流
 * @return      存在：true； 不存在：false
 */
bool isexist(QString str, QFile & file);

/**
 * @brief poslocate 返回str编号对应的pos位置，以便写入已经存在的项目是进行覆盖写入
 * @param str   编号
 * @param file  文件流
 * @return      str编号对应的pos位置
 */
qint64 poslocate(QString str, QFile & file);
#endif // DIALOG_INQUIRY_H
