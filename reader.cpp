/**文件名：reader.cpp
 * 功能说明：reader类的实现文件，提供reader类与文件的IO接口，
 *      提供reader类相关查询功能
*/
#include "reader.h"

#include "book.h"
#include "dialog_inquiry.h"

/**
 * @brief Reader::Reader构造函数
 * @param list  reader.csv文件中一行信息用逗号分割后的数据
 */
Reader::Reader(QStringList list)
{
    strReaderNum=list.at(0);
    strReaderName=list.at(1);
    strInstitute=list.at(2);
    nReaderType=list.at(3).toInt();
    nBorrowQuantity=list.at(4).toInt();
    fFine=list.at(5).toDouble();
    QStringList borrowed=list.at(6).split("/");
    for(int i=0; i<MAX_BORROW_QUANTITY; i++)
    {
        borrowedbook[i]=borrowed.at(i);
    }
}

/**
 * @brief Reader::subfine结算欠款
 * @param a结算金额
 * @return 成功返回true
 */
bool Reader::subfine(double a)
{
    if(a>0 && a<=fFine)
    {
        fFine-=a;
        return true;
    }
    return false;
}

/**
 * @brief addtofile
 * 将reader正确写入reader.csv文件，如果存在则覆盖写入
 * @return
 */
bool Reader::addtofile()
{
    QFile freader("reader.csv");
    QTextStream fr(&freader);
//    fr.setCodec("GBK");
    if(!freader.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;

    fr.seek(poslocate(strReaderNum, freader));

    QStringList line;
    line << strReaderNum << strReaderName << strInstitute
         << QString::number(nReaderType) << QString::number(nBorrowQuantity)
         << QString::number(fFine);
    QString strborrow;
    for(int i=0; i<MAX_BORROW_QUANTITY; i++)
    {
        strborrow=strborrow+borrowedbook[i]+"/";
    }
    line << strborrow;
    QString str=line.join(",");
    QString linebuf(300,' ');
    fr << linebuf.replace(0,str.length(),str) << endl;

    freader.flush();
    freader.close();

    return true;
}

/**
   * @brief orderarrivelist 预约到达表
   * @return 返回该读者的之前有过预约，并且已经到库可借给他的书籍编号表
   *          QStringList每一项表示一个编号
   *          如果没有可借出的预约，QStringList长度为0
   */
QStringList Reader::orderarrivelist()
{
    QFile fbook("book.csv");
    QString linebuf;
    QStringList list;
    QStringList List;
    if(!fbook.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::Append))
        QMessageBox::warning((QWidget *)this,QObject::tr("Error"),QObject::tr("File open failed!"),QMessageBox::Yes);
    QTextStream fb(&fbook);
    fb.setCodec("GBK");
    fb.seek(0);
//    qDebug()<<"orderarrivelist():open file ok";
    while(!fb.atEnd())
    {
        linebuf=fb.readLine();
        list=linebuf.split(",");

        QStringList appointList=list.at(7).split("/");//得到该书预约读者队列
//        qDebug()<<"appointlist:"<<appointList;
//        qDebug()<<"strReaderNum"<<strReaderNum;
        for(int i=0; i<MAX_ORDER_NUM; i++)
        {
            if(appointList.at(i)==strReaderNum)
            {
                if(i<list.at(6).toInt())
                {
                    List<<list.at(0);
                }
            }
        }
    }
//    qDebug()<<"List:"<<List;
    return List;
}

/**
 * @brief Reader::borrowbook执行借书操作，对类的基本信息进行修改
 * @param booknum图书编号
 * @param timesec借书时间
 * @return 成功返回true
 */
bool Reader::borrowbook(QString booknum, int timesec)
{
    for(int i=0; i<nBorrowQuantity; i++)
    {
        QStringList item=borrowedbook[i].split("|");
        if(item.at(0)==booknum)
        {
            return false;//已经借过同一本书
        }
    }
    borrowedbook[nBorrowQuantity]=booknum+"|"+QString::number(timesec);
    nBorrowQuantity++;
    return true;
}

/**
 * @brief Reader::returnbook  完成还书，更新读者信息
 * @param booknum 图书数量
 * @param nowtimesec 还书时间
 * @return 还书成功则返回true,否则返回false
 */
bool Reader::returnbook(QString booknum, int nowtimesec)
{
    for(int i=0; i<nBorrowQuantity; i++)//遍历该读者借阅过的所有书
    {
        QStringList item=borrowedbook[i].split("|");
        if(item.at(0)==booknum)//找到所要还的书
        {
            int borrowday=(nowtimesec-item.at(1).toInt())/(24*60*60);//计算罚款
            if(borrowday>MAX_BORROW_DAY)
                fFine+=(borrowday-MAX_BORROW_DAY)*FINE_PER_DAY;
            for(int k=i;k<nBorrowQuantity-1;k++)//删除该书记录
            {
                borrowedbook[k]=borrowedbook[k+1];
            }
            borrowedbook[nBorrowQuantity-1]="";
            nBorrowQuantity--;//借书数量减1
            return true;
        }
    }
    return false;
}

