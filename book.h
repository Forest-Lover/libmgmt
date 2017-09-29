/**文件名：book.h
 * 功能说明：book类的声明文件，提供book类与文件的IO接口，
 *      提供book类相关查询功能
 * 创建人： 刘功震
*/
#ifndef BOOK_H
#define BOOK_H

#define MAX_ORDER_NUM 10

#include "common.h"

class Book
{
public:
    Book(){}
    Book(QStringList list);

    QString num(void){return strBookNum;}
    QString name(void){return strBookName;}
    QString author(void){return strAuthor;}
    QString publisher(void){return strPublisher;}
    QString intro(void){return strIntro;}
    int date(void){return nDate;}
    int stock(void){return nStock;}
    QString *ordernum(void){return strOrderReaderNum;}
    int getBorrowcount() const{return borrowcount;}

    void setname(QString str){strBookName=str;}
    void setauthor(QString str){strAuthor=str;}
    void setpublisher(QString str){strPublisher=str;}
    void setintro(QString str){strIntro=str;}
    void setdate(int a){nDate=a;}
    void addstock(int a){nStock+=a;}//库存+a
    void plusstock(void){nStock++;}//库存++
    void minusstock(void){nStock--;}//库存--
    void setstock(int a){nStock=a;}

    /**
     * @brief generatenum   根据Book类中的其它几项信息如：书名、作者、出版社
     *                      生成一个序列号，每一类书（所选项目相同）的序列号是
     *                      唯一的。生成的序列号直接放在Book类的strBookNum
     *                      里面，不需要返回值。
     * 备注：  可能涉及的Qt类有：QString
     *        涉及常量：
     *        函数调用：
     */
    void generatenum(void);//生成序列号jiaxuan

    /**
     * @brief addtofile
     * 将book正确写入book.csv文件，如果存在则覆盖写入
     * @return
     */
    bool addtofile(void);

    /**
     * @brief refreshfromfile   依据文件中该编号的信息更新当前对象
     */
    void refreshfromfile(void);

    /**
     * @brief orderstatus 当前该书被预约状态
     * @return  -1 预约空间已满
     *          0-MAX_ORDER_NUM 该数组下标处当前为空，下一次预约可以放在这里
     */
    int orderstatus(void);

    /**
     * @brief isinorderlist 判断输入的读者是否在该图书的预约列表里面
     * @param str   当前准备判断的读者编号
     * @return  在返回true
     */
    bool isinorderlist(QString str);

    /**
     * @brief orderrank 该读者在当前图书预约列表中的排名，即他是第几个预约的
     * @param str 读者编号
     * @return 排名
     */
    int orderrank(QString str);

    /**
     * @brief addorder  在book.csv 文件里面添加预约读者编号
     *                  需要判断预约空间状态，空间满则添加失败
     * @param num       待添加的预约读者编号
     * @return          添加成功返回true，否则返回false
     * 备注：  可能涉及的Qt类有：QFile,QString,QTextStream
     *        涉及常量：MAX_ORDER_NUM最大可预约数量
     *        函数调用：orderstatus()
     */
    bool addorder(QString num);//添加预约qirui


    /**
     * @brief addorder  在book.csv 文件里面删除预约读者编号
     *                  注意FIFO原则
     * @param num       待删除的预约读者编号
     * @return          删除成功返回true，否则返回false
     * 备注：  可能涉及的Qt类有：QFile,QString,QTextStream
     *        涉及常量：MAX_ORDER_NUM最大可预约数量
     *        函数调用：orderstatus()
     */
    bool suborder(QString str);//取消预约qirui

    /**
     * @brief borrowbook借书操作对当前对象信息的修改
     */
    void borrowbook(){nStock--;borrowcount++;}


private:
    QString strBookNum;            //图书编号
    QString strBookName;           //书名
    QString strAuthor;             //作者
    QString strPublisher;          //出版社
    QString strIntro;             //简介
    int nDate=0;                  //购入日期
    int nStock=0;                      //库存量
    QString strOrderReaderNum[MAX_ORDER_NUM]; //预约读者编号
    int borrowcount=0;//历史借阅次数
};

#endif // BOOK_H
