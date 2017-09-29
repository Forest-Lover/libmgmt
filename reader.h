/**文件名：reader.h
 * 功能说明：reader类的声明文件，提供reader类与文件的IO接口，
 *      提供reader类相关查询功能
*/
#ifndef READER_H
#define READER_H


#include "common.h"

class Reader
{
public:
    Reader(){}
    Reader(QStringList list);

    QString num(void){return strReaderNum;}
    QString name(void){return strReaderName;}
    QString institute(void){return strInstitute;}
    int type(void){return nReaderType;}
    int quantity(void){return nBorrowQuantity;}
    double fine(void){return fFine;}


    void setnum(QString str){strReaderNum=str;}
    void setname(QString str){strReaderName=str;}
    void setinstitute(QString str){strInstitute=str;}
    void settype(int a){nReaderType=a;}
    void plusquantity(void){nBorrowQuantity++;}
    void minusquantity(void){nBorrowQuantity--;}
    void addfine(double a){fFine+=a;}
    bool subfine(double a);
    void clearfine(void){fFine=0.0;}

    /**
     * @brief addtofile
     * 将reader正确写入reader.csv文件，如果存在则覆盖写入
     * @return
     */
    bool addtofile(void);

    /**
     * @brief orderarrivelist 预约到达表
     * @return 返回该读者的之前有过预约，并且已经到库可借给他的书籍编号表
     *          QStringList每一项表示一个编号
     *          如果没有可借出的预约，QStringList长度为0
     */
    QStringList orderarrivelist(void);

    /**
     * @brief Reader::borrowbook执行借书操作，对类的基本信息进行修改
     * @param booknum图书编号
     * @param timesec借书时间
     * @return 成功返回true
     */
    bool borrowbook(QString booknum, int timesec);

    /**
     * @brief Reader::returnbook 还书操作，有产生欠款的机制
     * @param booknum 还书的图书编号
     * @param nowtimesec还书时间
     * @return
     */
    bool returnbook(QString booknum, int nowtimesec);

private:
    QString strReaderNum;//读者编号
    QString strReaderName;//读者姓名
    QString strInstitute;//学院
    int nReaderType=0;//读者类型 0：学生，1：教师
    int nBorrowQuantity=0;//借书数量
    double fFine=0.0;//罚款金额
    QString borrowedbook[MAX_BORROW_QUANTITY];//已经借阅书籍信息：书籍编号|借阅时间
};

#endif // READER_H
