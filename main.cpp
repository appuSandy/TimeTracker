#include "timetracker.h"
#include <QApplication>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimeTracker w;
    w.show();
    return a.exec();
}
