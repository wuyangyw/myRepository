#include "widget.h"

#include <QApplication>
#include"dialoglist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;
    //w.show();
    DialogList d;
    d.show();
    return a.exec();
}
