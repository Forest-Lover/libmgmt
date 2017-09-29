/**文件名： mainwindow.cpp
 * 说明：  程序主窗口对应的UI界面的源文件，包含了各种按键的信号与槽的实现和链接
 * 创建人： 刘功震
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "global.h"
#include "book.h"
#include "reader.h"
#include "dialog_log.h"
#include "dialog_login.h"
#include "dialog_purchase.h"
#include "dialog_borrow.h"
#include "dialog_return.h"
#include "dialog_inquiry.h"
#include "dialog_reader_info.h"
#include "dialog_book_info.h"
#include "dialog_addreader.h"
#include "dialog_help.h"


QStandardItemModel *bookmodel()
{
    QStandardItemModel *model=new QStandardItemModel();
    model->setObjectName("book");
    model->setColumnCount(6);
    model->setHeaderData(0, Qt::Horizontal, "编号");
    model->setHeaderData(1, Qt::Horizontal, "书名");
    model->setHeaderData(2, Qt::Horizontal, "作者");
    model->setHeaderData(3, Qt::Horizontal, "出版社");
    model->setHeaderData(4, Qt::Horizontal, "购入日期");
    model->setHeaderData(5, Qt::Horizontal, "库存量");

    return model;
}
QStandardItemModel *readermodel()
{
    QStandardItemModel *model=new QStandardItemModel();
    model->setObjectName("reader");
    model->setColumnCount(6);
    model->setHeaderData(0, Qt::Horizontal, "编号");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "学院");
    model->setHeaderData(3, Qt::Horizontal, "类型");
    model->setHeaderData(4, Qt::Horizontal, "借书数量");
    model->setHeaderData(5, Qt::Horizontal, "罚款金额");

    return model;
}
QStandardItemModel *logmodel()
{
    QStandardItemModel *model=new QStandardItemModel();
    model->setObjectName("log");
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "操作日期");
    model->setHeaderData(1, Qt::Horizontal, "操作类型");
    model->setHeaderData(2, Qt::Horizontal, "图书编号");
    model->setHeaderData(3, Qt::Horizontal, "读者编号");
    model->setHeaderData(4, Qt::Horizontal, "管理员");

    return model;
}
/**
 * @brief MainWindow::irqbydialoginput
 * @param label 查询窗口的输入提示信息
 * @param model mainwindow的tableview调用的显示模板
 * @param column    按照文件的column列对应的项进行查找
 */
void MainWindow::irqbydialoginput(QString label, QStandardItemModel *model, int column)
{
    bool ok;
    int count=0;
    QString text = QInputDialog::getText(this, tr("查询"),
                                       label, QLineEdit::Normal,
                                       NULL, &ok);
    if(ok && !text.isEmpty())
    {
        ui->tableView->setModel(model);

        QString linebuf;
        QStringList list;

        if(0==QString::compare(model->objectName(), "book"))
        {
            count=0;
            QFile fbook("book.csv");
            QTextStream fb(&fbook);
            fb.setCodec("GBK");
            if(!fbook.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QMessageBox::warning(this, "警告", "打开文件失败！", QMessageBox::Ok);
                return;
            }

            fb.seek(0);
            while(!fb.atEnd())
            {
                linebuf=fb.readLine();
                list=linebuf.split(",");

                if(!QString::compare(text, list.at(column)))
                {
                    //在listview中显示linebuf的内容
                    for(int i=0; i<4; i++)
                    {
                        model->setItem(count,i,new QStandardItem(list.at(i)));
                        model->item(count,i)->setTextAlignment(Qt::AlignCenter);
                    }
                    for(int i=4; i<6; i++)
                    {
                        if(i==4)
                            model->setItem(count,i,new QStandardItem(QDateTime::fromSecsSinceEpoch(list.at(i+1).toInt()).toString("yyyy/MM/dd hh:mm:ss")));
                        else if(i==5)//int 排序
                        {
                            QStandardItem *item = new QStandardItem;
                            int n = list.at(i+1).toInt();
                            item->setData(QVariant(n),Qt::EditRole);
                            model->setItem(count,i,item);
                        }
                        else
                            model->setItem(count,i,new QStandardItem(list.at(i+1)));
                        model->item(count,i)->setTextAlignment(Qt::AlignCenter);
                    }
                    count++;
                }
            }
            fbook.close();
        }
        else
        {
            count=0;
            QFile freader("reader.csv");
            QTextStream fr(&freader);
            fr.setCodec("GBK");
            if(!freader.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QMessageBox::warning(this, "警告", "打开文件失败！", QMessageBox::Ok);
                return;
            }

            fr.seek(0);
            while(!fr.atEnd())
            {
                linebuf=fr.readLine();
                list=linebuf.split(",");

                if(!QString::compare(text, list.at(0)))
                {
                    //在listview中显示linebuf的内容
                    for(int i=0; i<6; i++)
                    {
                        if(i==4)
                        {
                            QStandardItem *item = new QStandardItem;
                            int n = list.at(i).toInt();
                            item->setData(QVariant(n),Qt::EditRole);
                            model->setItem(count,i,item);
                        }
                        if(i==5)
                        {
                            QStandardItem *item = new QStandardItem;
                            double n = list.at(i).toDouble();
                            item->setData(QVariant(n),Qt::EditRole);
                            model->setItem(count,i,item);
                        }
                        else
                            model->setItem(count,i,new QStandardItem(list.at(i)));
                        model->item(count,i)->setTextAlignment(Qt::AlignCenter);
//                        qDebug()<<count<<","<<i<<endl;
                    }
                    count++;
                }
            }
            freader.close();
        }
    }
    if(count==0)
        QMessageBox::warning(this, "注意", "未查询到相关信息！", QMessageBox::Ok);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    this->setWindowTitle("图书管理系统");

    dialog_fine->setWindowTitle("结算欠款");//手动创建结算欠款的窗口
    QGridLayout *mainlayout=new QGridLayout(dialog_fine);
    label_num=new QLabel("读者编号：");
    label_sum=new QLabel("结算金额：");
    lineedit_num=new QLineEdit;
    lineedit_sum=new QLineEdit;
    lineedit_num->setPlaceholderText("请输入读者编号");
    lineedit_sum->setPlaceholderText("请输入结算金额");

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(new QPushButton("Ok"), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(new QPushButton("Cancel"), QDialogButtonBox::RejectRole);

    mainlayout->addWidget(label_num,0,0);
    mainlayout->addWidget(label_sum,1,0);
    mainlayout->addWidget(lineedit_num,0,1);
    mainlayout->addWidget(lineedit_sum,1,1);
    mainlayout->addWidget(buttonBox,2,1);

    connect(buttonBox,SIGNAL(rejected()),dialog_fine,SLOT(close()));
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(on_dialog_fine_accept()));

    ui->tableView->horizontalHeader()->setStretchLastSection(true);//最后一项填充剩余部分
    ui->tableView->verticalHeader()->hide();//隐藏行头
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选择
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);//右键菜单
    ui->tableView->setSortingEnabled(true);//排序可用
    ui->tableView->sortByColumn(5,Qt::AscendingOrder);


    timer->setInterval(TIMER_INTERVAL);//主窗口启动时打开定时器，用于刷新系统时间
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_request_info(QModelIndex)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_request_info双击表格中某一行时查看详情
 * @param index 双击位置
 */
void MainWindow::on_request_info(QModelIndex index)//双击查看图书或读者详情
{
    QString objectname=ui->tableView->model()->objectName();
    QString str=index.sibling(index.row(),0).data().toString();//该行对应条目的图书或读者编号
    if(objectname=="reader")
    {
        Dialog_log log;
        log.addlog(3,"",str);//生成查询日志
        Dialog_reader_info d(str);
        d.exec();
    }
    else if(objectname=="book")
    {
        Dialog_log log;
        log.addlog(3,str,"");//生成查询日志
        Dialog_book_info d(str);
        d.exec();
    }
}

/**
 * @brief MainWindow::onTimerOut
 * 利用定时器实现系统时间推进，以及状态栏显示当前时间
 */
void MainWindow::onTimerOut()
{
    timefromstart+=TIMER_INTERVAL;//修改全局变量timefromstart
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss"));
}

/**
 * @brief MainWindow::onReceivelogAtoB 根据日志UI界面返回的信息在主窗口列表中展示日志信息
 * @param str   日志UI界面返回的查询后的日志信息
 */
void MainWindow::onReceivelogAtoB(QString str)
{
    QStandardItemModel *model=logmodel();//设置模板为日志显示的model
    ui->tableView->setModel(model);

    ui->tableView->setColumnWidth(0,150);

    QStringList line,column;//按照先行后列分割日志信息存储于此
    QString stritem;

    line=str.split("\n");
    for(int i=0; i<line.size()-1; i++)
    {
        column=line.at(i).split(",");
        for(int j=0; j<column.size(); j++)
        {
            switch (j) {
            case 0:
                //设置日期显示格式
                stritem=QDateTime::fromSecsSinceEpoch(column.at(0).toInt()).toString("yyyy/MM/dd hh:mm:ss");
                break;
            case 1:
                //按照日志类型显示第二列的信息
                switch (column.at(1).toInt()) {
                case 0:
                    stritem="购书";
                    break;
                case 1:
                    stritem="借书";
                    break;
                case 2:
                    stritem="还书";
                    break;
                case 3:
                    stritem="查询";
                    break;
                default:
                    break;
                }
                break;
            default:
                stritem=column.at(j);
                break;
            }
            model->setItem(i,j,new QStandardItem(stritem));//添加当前项到日志模板中
            model->item(i,j)->setTextAlignment(Qt::AlignCenter);//设置居中显示
        }
    }
}

/**
 * @brief MainWindow::onReceiveOrderList 收到读者的到库可借的预约书籍信息时的槽
 * @param list 到库预约书籍列表
 */
void MainWindow::onReceiveOrderList(QStringList list)
{
    QStandardItemModel *model = bookmodel();
    ui->tableView->setModel(model);
    QFile fbook("book.csv");
    if(!fbook.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "警告", "打开book.scv文件失败！", QMessageBox::Ok);
        return;
    }
    QTextStream fb(&fbook);
    fb.setCodec("GBK");

    for(int i=0; i<list.size(); i++)//依编号查找每一本图书，并把信息展示在表格中
    {
        fb.seek(poslocate(list.at(i),fbook));
        QStringList column;
        column=fb.readLine().split(",");
        for(int j=0; j<4; j++)
        {
            model->setItem(i,j,new QStandardItem(column.at(j)));
            model->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
        for(int j=4; j<6; j++)
        {
            model->setItem(i,j,new QStandardItem(column.at(j+1)));
            model->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }

}

/**
 * @brief MainWindow::on_logoff_clicked
 * 按钮-注销
 */
void MainWindow::on_logoff_clicked()
{
    loginstatus=1;
    qApp->exit(1);
}

/**
 * @brief MainWindow::on_purchase_triggered
 * 购书
 */
void MainWindow::on_purchase_triggered()
{
    timer->stop();
    Dialog_purchase purchase;
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  购书");
    purchase.exec();
    timer->start();
}

/**
 * @brief MainWindow::on_borrow_triggered
 * 借书
 */
void MainWindow::on_borrow_triggered()
{
    timer->stop();
    Dialog_borrow borrow;
    connect(&borrow,SIGNAL(sendorderlist(QStringList)),this,SLOT(onReceiveOrderList(QStringList)));
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  借书");
    borrow.exec();
    timer->start();
}

/**
 * @brief MainWindow::on_return_3_triggered
 * 还书
 */
void MainWindow::on_return_3_triggered()
{
    timer->stop();
    Dialog_return return_;
    connect(&return_,SIGNAL(sendorderlist(QStringList)),this,SLOT(onReceiveOrderList(QStringList)));
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  还书");
    return_.exec();
    timer->start();
}

/**
 * @brief MainWindow::on_borrow_2_clicked
 * 按钮-借书
 */
void MainWindow::on_borrow_2_clicked()
{
    on_borrow_triggered();
}

/**
 * @brief MainWindow::on_return_2_clicked
 * 按钮-还书
 */
void MainWindow::on_return_2_clicked()
{
    on_return_3_triggered();
}

/**
 * @brief MainWindow::on_logirq_triggered
 * 查询-操作记录
 */
void MainWindow::on_logirq_triggered()
{
    timer->stop();
    Dialog_log log;
    connect(&log,SIGNAL(sendlogAtoB(QString)),this,SLOT(onReceivelogAtoB(QString)));
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  查询-操作记录");
    log.exec();
    timer->start();
}
/**
 * @brief MainWindow::on_action_triggered
 * 查询-图书信息-按编号查询
 */
void MainWindow::on_action_triggered()
{
    timer->stop();
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  查询-图书信息-按编号查询");
    irqbydialoginput("编号：", bookmodel(), 0);
    timer->start();
}

/**
 * @brief MainWindow::on_action_3_triggered
 * 查询-图书信息-按书名查询
 */
void MainWindow::on_action_3_triggered()
{
    timer->stop();
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  查询-图书信息-按书名查询");
    irqbydialoginput("书名：", bookmodel(), 1);
    timer->start();
}

/**
 * @brief MainWindow::on_action_5_triggered
 * 查询-图书信息-按作者查询
 */
void MainWindow::on_action_5_triggered()
{
    timer->stop();
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  查询-图书信息-按作者查询");
    irqbydialoginput("作者：", bookmodel(), 2);
    timer->start();
}

/**
 * @brief MainWindow::on_action_5_triggered
 * 查询-图书信息-按出版社查询
 */
void MainWindow::on_action_4_triggered()
{
    timer->stop();
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  查询-图书信息-按出版社查询");
    irqbydialoginput("出版社：", bookmodel(), 3);
    timer->start();
}
/**
 * @brief MainWindow::on_action_7_triggered
 * 查询-图书信息-所有图书
 */
void MainWindow::on_action_7_triggered()
{
    timer->stop();
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  查询-图书信息-所有图书");
    int count=0;

    QStandardItemModel *model=bookmodel();
    ui->tableView->setModel(model);

    QString linebuf;
    QStringList list;

    QFile fbook("book.csv");
    QTextStream fb(&fbook);
    fb.setCodec("GBK");
    if(!fbook.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "警告", "打开文件失败！", QMessageBox::Ok);
        return;
    }

    fb.seek(0);
    while(!fb.atEnd())
    {
        linebuf=fb.readLine();
        list=linebuf.split(",");
        //在listview中显示linebuf的内容
        for(int i=0; i<4; i++)
        {
            model->setItem(count,i,new QStandardItem(list.at(i)));
            model->item(count,i)->setTextAlignment(Qt::AlignCenter);
        }
        for(int i=4; i<6; i++)
        {
            if(i==4)
                model->setItem(count,i,new QStandardItem(QDateTime::fromSecsSinceEpoch(list.at(i+1).toInt()).toString("yyyy/MM/dd hh:mm:ss")));
            else if(i==5)//int 排序
            {
                QStandardItem *item = new QStandardItem;
                int n = list.at(i+1).toInt();
                item->setData(QVariant(n),Qt::EditRole);
                model->setItem(count,i,item);
            }
            else
                model->setItem(count,i,new QStandardItem(list.at(i+1)));
            model->item(count,i)->setTextAlignment(Qt::AlignCenter);
        }
        count++;
    }
    fbook.close();
    if(count==0)
    {
        QMessageBox::warning(this, "注意", "未查询到相关信息！", QMessageBox::Ok);
    }
    timer->start();
}

/**
 * @brief MainWindow::on_action_2_triggered
 * 查询-读者信息-按编号查询
 */
void MainWindow::on_action_2_triggered()
{
    timer->stop();
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  查询-读者信息-按编号查询");
    irqbydialoginput("编号：", readermodel(), 0);
    timer->start();
}

/**
 * @brief MainWindow::on_action_6_triggered
 * 查询-读者信息-按姓名查询
 */
void MainWindow::on_action_6_triggered()
{
    timer->stop();
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  查询-读者信息-按姓名查询");
    irqbydialoginput("姓名：", readermodel(), 1);
    timer->start();
}

/**
 * @brief MainWindow::on_action_9_triggered
 *查询-读者信息-所有读者
 */
void MainWindow::on_action_9_triggered()
{
    timer->stop();
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  查询-读者信息-所有读者");
    int count=0;

    QStandardItemModel *model=readermodel();
    ui->tableView->setModel(model);

    QString linebuf;
    QStringList list;

    QFile freader("reader.csv");
    QTextStream fr(&freader);
    fr.setCodec("GBK");
    if(!freader.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "警告", "打开文件失败！", QMessageBox::Ok);
        return;
    }

    fr.seek(0);
    while(!fr.atEnd())
    {
        linebuf=fr.readLine();
        list=linebuf.split(",");

//        qDebug()<<linebuf;

        //在listview中显示reader对象或linebuf的内容
        for(int i=0; i<6; i++)
        {
            if(i==4)
            {
                QStandardItem *item = new QStandardItem;
                int n = list.at(i).toInt();
                item->setData(QVariant(n),Qt::EditRole);
                model->setItem(count,i,item);
            }
            else if(i==5)
            {
                QStandardItem *item = new QStandardItem;
                double n = list.at(i).toDouble();
                item->setData(QVariant(n),Qt::EditRole);
                model->setItem(count,i,item);
            }
            else
                model->setItem(count, i, new QStandardItem(list.at(i)));
            model->item(count, i)->setTextAlignment(Qt::AlignCenter);
        }
        count++;
    }
    freader.close();

    if(count==0)
    {
        QMessageBox::warning(this, "注意", "未查询到相关信息！", QMessageBox::Ok);
    }
    timer->start();
}

//点击使用说明
void MainWindow::on_readme_triggered()
{
    timer->stop();
    Dialog_help help;
    ui->statusBar->showMessage(QDateTime::fromMSecsSinceEpoch(timefromstart*VSEC_PER_RSEC).toString("yyyy-MM-dd hh:mm:ss")+"  帮助-使用说明");
    help.exec();
    timer->start();
}
//关于系统
void MainWindow::on_about_triggered()
{
    timer->stop();
    QMessageBox::about(this,"图书管理系统","软件名:\t\t图书管理系统\n版本号:\t\tv1.0.2\
                    \n开发团队:\t2015211312-06\n\nCopyright © 2017 2015211312-06\nAll rights reserved");
    timer->start();
}

//按钮——结算欠款
void MainWindow::on_action_10_triggered()//结算欠款
{
    timer->stop();
    lineedit_num->clear();
    lineedit_sum->clear();
    dialog_fine->exec();
    timer->start();
}

//结算欠款界面点击确认
void MainWindow::on_dialog_fine_accept()
{
    QFile freader("reader.csv");
    if(!freader.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"on_dialog_fine_accept(),reader.csv open failed";
        return;
    }
    QTextStream fr(&freader);
    fr.setCodec("GBK");
    QString num=lineedit_num->text();
    if(!isexist(num,freader))
    {
        QMessageBox::information(this,"提示","该读者不存在",QMessageBox::Ok);
        return;
    }
    fr.seek(poslocate(num,freader));
    Reader thisreader(fr.readLine().split(","));
    freader.close();

    if(thisreader.subfine(lineedit_sum->text().toDouble())==true)
    {
        QMessageBox::information(this,"提示","结算成功",QMessageBox::Ok);
        thisreader.addtofile();
        dialog_fine->close();
        on_action_9_triggered();
    }
    else
    {
        QMessageBox::information(this,"提示","结算失败,请核对欠款金额",QMessageBox::Ok);
    }
}

//添加读者
void MainWindow::on_action_11_triggered()
{
    timer->stop();
    Dialog_addreader d;
    d.exec();
    timer->start();
}
