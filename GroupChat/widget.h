#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

// 枚举 分别代表普通消息，用户进入，用户离开
enum MsgType{Msg,UsrEnter, UsrLeft};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent,QString usrname);
    ~Widget();

    void closeEvent(QCloseEvent *e);                            // 关闭事件
    void paintEvent(QPaintEvent *);                             // 重绘背景
    void init();                                                // 初始化背景
    void usrEnter(QString usrname);                             // 处理新用户加入
    void usrLeft(QString  usrname, QString time);               // 处理用户离开
    void sndMsg(MsgType type);                                  // 广播UDP消息
    QString getUsr();                                           // 获取用户名
    QString getMsg();                                           // 获取聊天信息
    void ReceiveMsg();                                          // 接收消息
    bool saveFile(const QString &path);                         // 保存记录
    bool eventFilter(QObject *target, QEvent *event);           // 快捷键发送消息

private:
    Ui::Widget *ui;

    QUdpSocket *udpSocket;     // udp套接字
    qint16 port;               // 端口号
    QString uName;             // 用户名
    QColor color;              // 颜色

private slots:
    void on_colorTBtn_clicked();                                   // 设置颜色
    void on_saveTBtn_clicked();                                    // 保存聊天记录
    void on_clearTBtn_clicked();                                   // 清屏
    void on_exitBtn_clicked();                                     // 退出
    void on_sendBtn_clicked();                                     // 发送消息


signals:
    // 关闭窗口发送关闭信号
    void closeWidget();
};
#endif // WIDGET_H
