/**文件名： global.h
 * 说明：  全局变量声明文件，其它文件如果引用全局变量，只需要包含改文件即可
 * 创建人： 刘功震
 */
#ifndef GLOBAL_H
#define GLOBAL_H

#include "common.h"

extern QTimer *timer;//主窗口定时器
extern long long timefromstart;//系统开始运行到现在的时间 单位ms
extern bool loginstatus;//0 登录验证通过，1 验证失败
extern QString username;//当前登录用户的用户名

#endif // GLOBAL_H

