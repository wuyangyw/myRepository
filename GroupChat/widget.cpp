#include "widget.h"
#include "ui_widget.h"
#include<QUdpSocket>
#include<QMessageBox>
#include<QDateTime>
#include<QColorDialog>
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QPainter>
#include <QKeyEvent>


Widget::Widget(QWidget *parent,QString usrname)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);               //创建udp套接字
    uName = usrname;
    port = 9999;                                   //端口默认为9999

    //将udp套接字绑定到端口和地址上（采用shareaddress模式(允许他的服务连接到相同的地址和端口),reuseaddresshint模式（断线重新连接服务器）
    udpSocket->bind(port, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    sndMsg(UsrEnter); // 新用户进入

    // 监听别人发送的消息
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::ReceiveMsg);

    init();  // 初始化背景

//////////////////////////////  功能设置  /////////////////////////////////////
    // 利用lambda表达式设置
    // 设置字体
    connect(ui->fontCbx,&QFontComboBox::currentFontChanged,[=](const QFont &font){
          ui->msgTextEdit->setCurrentFont(font);
          ui->msgTextEdit->setFocus();
    });
    // 设置字体类型
    connect(ui->fontCbx,&QFontComboBox::currentFontChanged,[=](const QFont &font){
        ui->msgTextEdit->setFontFamily(font.toString());
        ui->msgTextEdit->setFocus();
    });
    // 设置字体大小
    void (QComboBox:: * sizecbx)(const QString &text)= &QComboBox::currentTextChanged;
    connect(ui->sizeCbx,sizecbx,[=](const QString &text){
        ui->msgTextEdit->setFontPointSize(text.toDouble());
        ui->msgTextEdit->setFocus();
    });
    // 设置字体加粗
    // 按钮要勾选checkable才能切换toggle button，按下/弹起状态，默认为trigger button，按下立马弹起，下面的倾斜，下划线也是
    // 或者设置 ui->boldTBtn->setCheckable(true);
    connect(ui->boldTBtn,&QToolButton::clicked,[=](bool checked){
        if(checked)
        {
            ui->msgTextEdit->setFontWeight(QFont::Bold);
        }
        else
        {
            ui->msgTextEdit->setFontWeight(QFont::Normal);
        }
    });
    // 设置字体倾斜
    connect(ui->italicTBtn,&QToolButton::clicked,[=](bool checked){
        ui->msgTextEdit->setFontItalic(checked);
        ui->msgTextEdit->setFocus();
    });
    //设置字体下划线
    connect(ui->underlineTBtn,&QToolButton::clicked,[=](bool checked){
        ui->msgTextEdit->setFontUnderline(checked);
        ui->msgTextEdit->setFocus();
    });

}

Widget::~Widget()
{
    delete ui;
}


// 初始化背景
void Widget::init()
{
    //设置透明 使控件显示在背景上层
    ui->msgBrowser->setStyleSheet("background-color:transparent;");
    ui->msgTextEdit->setStyleSheet("background-color:transparent;");
    ui->usrTblWidget->setStyleSheet("background-color:transparent;");
    ui->textEdit->setStyleSheet("background-color:transparent;");
    ui->usrTblWidget->horizontalHeader()->setStyleSheet("QHeaderView::section"
           "{background-color:transparent;font:10pt '黑体';font:bold;color: black;}");
    ui->usrTblWidget->verticalHeader()->setVisible(false);

    ui->usrTblWidget->setShowGrid(false);   // 不显示网格线
    ui->usrTblWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   // 禁止编辑


    // setStyleSheet会被所有子类引用，需要限定模块使用
    ui->fontCbx->setObjectName("fc");                    // 限定仅为fontCbx使用，而不会在选择字体的下拉框里使用
    ui->fontCbx->setStyleSheet("#fc{background-color:transparent;}");
    ui->sizeCbx->setObjectName("sc");                    // 限定仅为sizeCbx使用，而不会在选择字号的下拉框里使用
    ui->sizeCbx->setStyleSheet("#sc{background-color:transparent;}");

    ui->boldTBtn->setStyleSheet("background-color:transparent;");
    ui->italicTBtn->setStyleSheet("background-color:transparent;");
    ui->underlineTBtn->setStyleSheet("background-color:transparent;");
    ui->colorTBtn->setStyleSheet("background-color:transparent;");
    ui->saveTBtn->setStyleSheet("background-color:transparent;");
    ui->clearTBtn->setStyleSheet("background-color:transparent;");
//  ui->sendBtn->setStyleSheet("background-color:transparent;");
//  ui->exitBtn->setStyleSheet("background-color:transparent;");

    //设置键盘快捷键
    ui->sendBtn->setFocus();
    ui->sendBtn->setDefault(true);
    ui->msgTextEdit->installEventFilter(this);//设置完后自动调用其eventFilter函数


}

//重绘事件
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/images/background.png"),QRect());
}


void Widget::sndMsg(MsgType type)
{
    // 分段处理发送内容，第一为类型，第二为昵称，第三为具体内容
    QByteArray data;                               //创建一个data数组
    QDataStream out(&data, QIODevice::WriteOnly);
    out<<type<<getUsr();
    switch (type)
    {
    case Msg :    //如果是普通信息
        if (ui->msgTextEdit->toPlainText() == "")//如果输入栏为空
        {
            QMessageBox::warning(0, "警告", "发送内容不能为空", QMessageBox::Ok);
            return;
        }
        // 发送内容
        out<<getMsg();
        break;
    case UsrEnter:      // 用户进入

        break;
    case UsrLeft:       // 用户离开
        break;
    default:
        break;
    }
    // 使用writeDatagram函数进行udp广播 发送给port的端口
    udpSocket->writeDatagram(data,QHostAddress::Broadcast, port);
}

void Widget::ReceiveMsg()
{
    qint64 size=udpSocket->pendingDatagramSize();      //获取当前可供读取的UDP报文大小
    QByteArray datagram=QByteArray(size,0);
    udpSocket->readDatagram(datagram.data(),size);  //读取相应数据
    // 解析数据
    QDataStream in(&datagram, QIODevice::ReadOnly);   //只读
    int msgType;
    QString usrName, msg; // 昵称，聊天内容
    //获取现在的时间
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    in>>msgType;

    switch(msgType)
    {
    case Msg:
        in >> usrName >> msg;  //流出昵称,聊天内容
        // 聊天记录
        ui->msgBrowser->setTextColor(Qt::blue); //设置字的颜色
        ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 12));
        ui->msgBrowser->append("【"+usrName+"】  "+ time);
        ui->msgBrowser->append(msg);
        break;
    case UsrEnter:     //用户进入,显示昵称
        in>>usrName;
        usrEnter(usrName);            //调用进入函数
        break;
    case UsrLeft:      //用户离开,显示昵称
        in>>usrName;
        usrLeft(usrName,time);       //调用离开函数
        break;
    default:
        break;
    }
}

QString Widget::getMsg()
{
    QString msg = ui->msgTextEdit->toHtml(); //获取消息
    ui->msgTextEdit->clear();   //清空输入框
    ui->msgTextEdit->setFocus(); //设置光标焦点
    return msg;
}

QString Widget::getUsr()
{
    return uName;
}

 // 用户进入处理函数
void Widget::usrEnter(QString usrname)
{
    bool isEmpty = ui->usrTblWidget->findItems(usrname, Qt::MatchExactly).isEmpty();  //从列表中判断该用户是否存在
    if(isEmpty)
    {
        QTableWidgetItem *usr = new QTableWidgetItem(usrname);
        // 插入行
        ui->usrTblWidget->insertRow(0);
        ui->usrTblWidget->setItem(0, 0, usr);
        // 追加上线消息
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
        ui->msgBrowser->append(QString("%1  已上线！").arg("【"+usrname+"】"));
        // 更新在线人数
        ui->usrNumLbl->setText(QString("在线人数：%1 人").arg(ui->usrTblWidget->rowCount()));
        //再发送一次消息，更新对话框,显示已经上线的记录
        sndMsg(UsrEnter);
    }
}

// 用户离开处理函数
void Widget::usrLeft(QString  usrname, QString time)
{
    bool isEmpty = ui->usrTblWidget->findItems(usrname, Qt::MatchExactly).isEmpty();  //从列表中判断该用户是否存在
    if(!isEmpty)
    {
    // 获得上线用户昵称行
    int rowNum = ui->usrTblWidget->findItems(usrname, Qt::MatchExactly).first()->row();
    ui->usrTblWidget->removeRow(rowNum); //删除该行
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
    // 追加下线消息
    ui->msgBrowser->append(tr("%1 于 %2 离开！").arg("【"+usrname+"】 ").arg(time));
    // 更新在线人数
    ui->usrNumLbl->setText(tr("在线人数: %1 人").arg(ui->usrTblWidget->rowCount()));
    }
}


void Widget::closeEvent(QCloseEvent *e)
{
    emit this->closeWidget();
    sndMsg(UsrLeft);
    // 断开套接字
    udpSocket->close();
    udpSocket->destroyed();
    QWidget::closeEvent(e);
}

////////////////////////////  功能设置  ///////////////////////////////////

// 字体颜色设置
void Widget::on_colorTBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
    if (color.isValid())
    {
        ui->msgTextEdit->setTextColor(color);
        ui->msgTextEdit->setFocus();
    }
}

// 保存聊天记录事件
void Widget::on_saveTBtn_clicked()
{
    if (ui->msgBrowser->document()->isEmpty())   // 如果聊天记录为空
    {
        QMessageBox::warning(0, "警告", "聊天记录为空, 无法保存！", QMessageBox::Ok);
        return;
    }
    else{
        QString path = QFileDialog::getSaveFileName(this, "保存聊天记录", "聊天记录", "文本(*.txt);;所有文件(*.*)");
        if (!path.isEmpty())                   //如果保存路径不为空
        {
            saveFile(path);
        }
    }
}

// 保存聊天记录处理函数
bool Widget::saveFile(const QString &path)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))  //如果打开失败
    {
        QMessageBox::warning(this, "保存文件", QString("无法保存文件 %1:\n %2").arg(path).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->msgBrowser->toPlainText();
    file.close();
    return true;
}

// 发送消息快捷键设置
bool Widget::eventFilter(QObject *target, QEvent *event)
{

    if(target == ui->msgTextEdit)        // 可替换控件
            {
                if(event->type() == QEvent::KeyPress)  //回车键
                {
                     QKeyEvent *k = static_cast<QKeyEvent *>(event);

                     if(k->key() == Qt::Key_Return)
                     {
                         on_sendBtn_clicked();		//可替换为需要响应的函数事件
                         return true;
                     }
                }
            }
            return QWidget::eventFilter(target,event);

}

// 清屏
void Widget::on_clearTBtn_clicked()
{
    ui->msgBrowser->clear();
}

// 发送消息
void Widget::on_sendBtn_clicked()
{
    sndMsg(Msg);
}

// 退出
void Widget::on_exitBtn_clicked()
{
    close();
}


