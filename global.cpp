/**文件名： global.cpp
 * 说明：  全局变量定义文件，其它文件如果引用全局变量，只需要包含改文件即可
 * 创建人： 刘功震
 */
#include "common.h"

QTimer *timer=new QTimer();//主窗口定时器
long long timefromstart=0;//系统开始运行到现在的时间 单位ms
bool loginstatus=1;//0 登录验证通过，1 验证失败
QString username;//当前登录用户的用户名
