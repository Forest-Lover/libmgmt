/**文件名:common.h
 * 说明: 提供全局公共类的引用声明，其它文件只需要包含该文件即可
 *      提供全局宏定义说明，宏定义修改在此文件中执行
 * 创建人： 刘功震
 */
#ifndef COMMON_H
#define COMMON_H

#pragma execution_character_set("utf-8")

#include <QDebug>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QTextStream>
#include <QDateTime>
#include <QTimer>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

#include <cstdlib>
#include <ctime>

#define TIMER_INTERVAL 100//主窗口定时器刷新间隔，单位ms
#define VSEC_PER_RSEC ((24*60*60)/10) //虚拟秒——per——实际秒
#define MAX_FINE 10.0//罚款最大限度，超过则不能借书danwei :yuan
#define FINE_PER_DAY 0.5//超期后每天罚款金额
#define MAX_BORROW_DAY 30//最大借书时长
#define MAX_BORROW_QUANTITY 20//最大借书数量

#endif // COMMON_H
