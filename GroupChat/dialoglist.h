#ifndef DIALOGLIST_H
#define DIALOGLIST_H

#include <QWidget>

namespace Ui {
class DialogList;
}

class DialogList : public QWidget
{
    Q_OBJECT

public:
    explicit DialogList(QWidget *parent = nullptr);
    ~DialogList();

private:
    Ui::DialogList *ui;

    // 判断聊天窗口是否打开
    QVector<bool>isShow;
};

#endif // DIALOGLIST_H
