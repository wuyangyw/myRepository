#include "dialoglist.h"
#include "ui_dialoglist.h"
#include<QToolButton>
#include<QString>
#include<QVector>
#include"widget.h"
#include<QMessageBox>


DialogList::DialogList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogList)
{
    ui->setupUi(this);

    // 设置标题
    setWindowTitle("东华理工大学钉子户");
    // 设置图标
    setWindowIcon(QIcon(":/images/qq.png"));

    // 组合头像和昵称以及悬停信息（个性签名）
    QList<QString>nameList;
    nameList<<"一双袜子穿五天的胖虎"<<"不爱请别伤害"<<"欧青辣少"<<"东理肖某人"
    <<"鸽嘉爵"<<"底层群员"<<" 狗子嘉"<<"狗汪欣"<<"Eva-创造恋人";

    QStringList iconNameList;
    iconNameList<<"xcy"<<"yw"<<"clj"<<"xzb"<<"fjx"<<"zxc"<<"wzj"<<"wx"<<"czlr";

    QList<QString>mottoList;
    mottoList<<"  吃饭中  "<<"  道阻且长，行则将至  "<<"  好友易得，知音难觅  "
            <<"  悟已往之不谏，知来者之可追  "<<"  鸽嘉爵  "<<"  这个人没有个性也就没有个性签名  "
           <<"  TIM电脑在线  "<<"  hope is a good thing  "<<"  加好友  ";

    QVector<QToolButton *> vToolBtn;

    for(int i=0;i<9;++i)
    {
        // 设置头像加昵称列
        QToolButton *btn=new QToolButton;
        // 设置自动提升
        btn->setAutoRaise(true);
        // 文字在图片右侧
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        // 加入设置好的vLayout布局
        ui->vLayout->addWidget(btn);
        // 通过容器保存按钮,方便以后操作
        vToolBtn.push_back(btn);
        // 窗口打开标识，默认未打开
        isShow.push_back(false);

        // 昵称
        btn->setText(nameList[i]);
        // 悬停个签
        btn->setToolTip(mottoList[i]);
        // 头像
        QString str=QString(":/images/%1.jpg").arg(iconNameList.at(i));   // 格式化字符串
        btn->setIcon(QPixmap(str));
        // 设置头像大小
        btn->setIconSize(QSize(50,50));
        // btn->setIconSize(QPixmap(":/images/xcy.jpg").size());  // 原始大小

    }
    // 对ToolButton添加信号槽
    for(int i=0;i<vToolBtn.size();++i)
    {
        connect(vToolBtn[i],&QToolButton::clicked,[=](){
            // 判断窗口是否被打开了
            if(isShow[i])
            {
                QString str=QString("%1聊天窗口已经被打开了").arg(vToolBtn[i]->text());
                QMessageBox::warning(this,"警告",str);
                return;
            }
            isShow[i]=true;

            // 以顶层方式弹出聊天对话框,并显示聊天人物昵称
            Widget *widget=new Widget(0,vToolBtn[i]->text());
            widget->setWindowTitle(vToolBtn[i]->text());
            widget->setWindowIcon(vToolBtn[i]->icon());
            widget->show();

            // 关闭重新将标识改为false
            connect(widget,&Widget::closeWidget,[=](){
                isShow[i]=false;
            });

        });
    }







}

DialogList::~DialogList()
{
    delete ui;
}
