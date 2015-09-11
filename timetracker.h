#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
namespace Ui {
class TimeTracker;
}

class TimeTracker : public QMainWindow
{
    Q_OBJECT

public:\
    explicit TimeTracker(QWidget *parent = 0);
    ~TimeTracker();

private slots:
    void on_start_clicked();

    void on_Pause_clicked();

    void on_Reset_clicked();

    void on_Resume_clicked();

    void on_stop_clicked();

    void  View_timeTracker();

private:
    Ui::TimeTracker *ui;
    time_t _startTime;
    time_t _pauseTime;
    time_t _waitTime;
    time_t onScreen;
    bool _pauseFlag;
    bool _startFlag;
};

#endif // TIMETRACKER_H
