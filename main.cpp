/**文件名： main.cpp
 * 说明：  主函数在这里，你懂得
 * 创建人：刘功震
 */
#include <QApplication>

#include "mainwindow.h"
#include "global.h"
#include "dialog_login.h"

int main(int argc, char *argv[])
{
    int exitnum=1;//注销退出标志，如果点击注销可以返回登录窗口
    while(exitnum)
    {
        QApplication a(argc, argv);

        MainWindow mainwindow;
        while(loginstatus==1)//登录结果的标志位，如果登录成功则置为0
        {
            Dialog_login login;
            if(login.exec()==0)//点击关闭按钮，直接退出程序
                exit(0);
        }
        mainwindow.show();
        exitnum=a.exec();
    }

    return exitnum;
}
