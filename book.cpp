/**文件名： book.cpp
 * 说明：  book类对应成员函数的实现、以及book类与文件的IO接口
 * 创建人： 刘功震
 */
#include "book.h"

#include "dialog_inquiry.h"


struct publisher{
    QString name;
    QString ID;
};


Book::Book(QStringList list)
{
    strBookNum=list.at(0);
    strBookName=list.at(1);
    strAuthor=list.at(2);
    strPublisher=list.at(3);
    strIntro=list.at(4);
    nDate=list.at(5).toInt();
    nStock=list.at(6).toInt();

    QStringList orderlist=list.at(7).split("/");
    for(int i=0; i<MAX_ORDER_NUM; i++)
        strOrderReaderNum[i]=orderlist.at(i);

    borrowcount=list.at(8).toInt();
}

/**
 * @brief generatenum   根据Book类中的其它几项信息如：书名、作者、出版社
 *                      生成一个序列号，每一类书（所选项目相同）的序列号是
 *                      唯一的。生成的序列号直接放在Book类的strBookNum
 *                      里面，不需要返回值。
 * 备注：  可能涉及的Qt类有：QString,Qfile
 *        涉及常量：strAuthor,strBookName,strPublish,strBookNum
 *        函数调用：无
 */
void Book::generatenum()
{
  //qDebug()<<"start:"<<strBookNum<<","<<strBookName<<","<<strAuthor<<","<<strPublisher<<endl;
    struct publisher publish[100];

    QString BookID="0000000000";
    QFile in1("publish.txt");
    QFile in2("Num.txt");
    if(!(in1.open(QIODevice::ReadOnly | QIODevice::Text) && in2.open(QIODevice::ReadOnly | QIODevice::Text)))
        return;

    QTextStream in1s(&in1);
    QTextStream in2s(&in2);
    in1s.setCodec("GBK");
    in2s.setCodec("GBK");

    int i=0;
    in1s.seek(0);
    in2s.seek(0);
    while(!in1s.atEnd()&&!in2s.atEnd())
    {
        publish[i].name=in1s.readLine();
        //qDebug()<<"publish[i].name:"<<publish[i].name<<endl;
        publish[i].ID=in2s.readLine();
        //qDebug()<<"publish[i].ID:"<<publish[i].ID<<endl;
        i++;}
    int j=strAuthor.length();
    int k=strBookName.length();
    BookID[0]=j+'0';
    BookID[1]=k+'0';
    int m;
    if(strPublisher.length()<=9)
    {
        BookID[2]='0';
        m=strPublisher.length();
        BookID[3]=m+'0';
    }
    else
    {
        m=strPublisher.length();
        char c[2];
        itoa(m,c,10);
        BookID[2]=c[0];
        BookID[3]=c[1];
    }

    for(int i=0;i<46;i++){
        if(strPublisher==publish[i].name)
        {
            QByteArray b=publish[i].ID.toLatin1();
            char *n=b.data();
            //qDebug()<<"n:"<<n<<endl;
            for(int j=0;j<3;j++)
              BookID[j+4]=n[j];
            break;
        }
        else
        {
            BookID[5]='1';
            BookID[6]='1';
            BookID[4]='1';
        }
        }
    BookID[7]=abs(m-k)+'0';
    BookID[8]=abs(m-j)+'0';
    BookID[9]=abs(j-k)+'0';
    strBookNum=BookID;

    //qDebug()<<"after:"<<strBookNum<<","<<strBookName<<","<<strAuthor<<","<<strPublisher<<endl;
}

/**
 * @brief addtofile
 * 将book正确写入book.csv文件，如果存在则覆盖写入
 * @return
 */
bool Book::addtofile()
{
    QFile fbook("book.csv");
    QTextStream fb(&fbook);
//    fb.setCodec("GBK");
    if(!fbook.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;

    fb.seek(poslocate(strBookNum, fbook));

    QString order;
    for(int i=0; i<MAX_ORDER_NUM; i++)
    {
        order+=strOrderReaderNum[i];
        order+="/";
    }
    QStringList line;
    line << strBookNum << strBookName << strAuthor << strPublisher << strIntro
         << QString::number(nDate) << QString::number(nStock) << order << QString::number(borrowcount);
    QString str=line.join(",");
    QString linebuf(120,' ');
    fb << linebuf.replace(0,str.length(),str) << endl;

    fbook.flush();
    fbook.close();

    return true;
}

/**
 * @brief Book::refreshfromfile
 * 依据文件中存储的内容修改该对象的值
 */
void Book::refreshfromfile()
{
    QFile fbook("book.csv");
    QTextStream fb(&fbook);
    fb.setCodec("GBK");
    if(!fbook.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() <<"error refreshfromfile when opening file book.csv" << endl;
        return;
    }
    fb.seek(poslocate(strBookNum, fbook));
    QString str=fb.readLine();
    Book bookfromfile(str.split(","));

    //逐项修改
    strBookName=bookfromfile.name();
    strAuthor=bookfromfile.author();
    strPublisher=bookfromfile.publisher();
    strIntro=bookfromfile.intro();
    nDate=bookfromfile.date();
    nStock=bookfromfile.stock();
    for(int i=0; i<MAX_ORDER_NUM; i++)
        strOrderReaderNum[i]=bookfromfile.ordernum()[i];
    borrowcount=bookfromfile.borrowcount;
}

/**
 * @brief orderstatus 当前该书被预约状态
 * @return  -1 预约空间已满
 *          0-MAX_ORDER_NUM 该数组下标处当前为空，下一次预约可以放在这里
 */
int Book::orderstatus()
{
    for(int i=0; i<MAX_ORDER_NUM; i++)
        if(!QString::compare("", strOrderReaderNum[i]))
            return i;
    return -1;
}

bool Book::isinorderlist(QString str)
{
    for(int i=0; i<orderstatus(); i++)
    {
        if(str==strOrderReaderNum[i])
            return true;
    }
    return false;
}

/**
 * @brief orderrank 该读者在当前图书预约列表中的排名，即他是第几个预约的
 * @param str 读者编号
 * @return 排名
 */
int Book::orderrank(QString str)
{
    int i=0;
    while(strOrderReaderNum[i]!=str && i<orderstatus())
        i++;
    return i+1;
}

/**
 * @brief addorder  在book.csv 文件里面添加预约读者编号
 *                  需要判断预约空间状态，空间满则添加失败
 * @param num       待添加的预约读者编号
 * @return          添加成功返回true，否则返回false
 * 备注：  可能涉及的Qt类有：QFile,QString,QTextStream
 *        涉及常量：MAX_ORDER_NUM最大可预约数量
 *        函数调用：orderstatus()
 */
bool Book::addorder(QString num)//添加预约
{
    int i=0;
    for(;i<MAX_ORDER_NUM;i++){
        if(!QString::compare(strOrderReaderNum[i],""))//到达队尾
            break;
        if(!QString::compare(strOrderReaderNum[i],num))//借阅者在预约名单中
            return true;
    }
    if(i>=MAX_ORDER_NUM)//预约已满
        return false;
    else
        strOrderReaderNum[i]=num;//成功添加到预约队列
    return true;
}

/**
 * @brief addorder  在book.csv 文件里面删除预约读者编号
 *                  注意FIFO原则
 * @param num       待删除的预约读者编号
 * @return          删除成功返回true，否则返回false
 * 备注：  可能涉及的Qt类有：QFile,QString,QTextStream
 *        涉及常量：MAX_ORDER_NUM最大可预约数量
 *        函数调用：orderstatus()
 */
bool Book::suborder(QString str)//取消预约
{
    if(!isinorderlist(str))
        return false;
    int i;
    for(i=orderrank(str)-1; i<orderstatus()-1; i++)//先进先出
       strOrderReaderNum[i]=strOrderReaderNum[i+1];
    strOrderReaderNum[i]="";
    return true;
}

