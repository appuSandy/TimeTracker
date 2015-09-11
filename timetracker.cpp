#include "timetracker.h"
#include "ui_timetracker.h"
#include <math.h>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QInputDialog>


TimeTracker::TimeTracker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimeTracker)
{
    _pauseTime = 0;
    _startTime = 0;
    _waitTime = 0;
    onScreen = 0;
    _pauseFlag = false;
    _startFlag  = false;
    ui->setupUi(this);

    QTimer *RunTimer = new QTimer(this);
    connect(RunTimer, SIGNAL(timeout()), this, SLOT(View_timeTracker()));
    RunTimer->start(1000);
    statusBar()->showMessage("Status: Running.");
}

TimeTracker::~TimeTracker()
{
    delete ui;
}


void TimeTracker::on_start_clicked()
{
    if(_startFlag != true)
    {
        _startTime = time(NULL);
        _startFlag = true;
    }

}

void TimeTracker::on_Pause_clicked()
{
    if(_startFlag)
    {
        if(_pauseFlag == false)
        {
            onScreen = 	time(NULL) - _startTime - _waitTime;
            _pauseTime = time(NULL);
            _pauseFlag = true;
        }
        View_timeTracker();

    }
}

void TimeTracker::on_Reset_clicked()
{
    int ret =  0;
    QMessageBox msgBox;

    if(_startFlag)
    {
        msgBox.setInformativeText("Do you want to reset timeTracker?");
        msgBox.setStandardButtons(QMessageBox::Yes |
                                  QMessageBox::No);
        ret = msgBox.exec();
        if(QMessageBox::Yes == ret)
        {
            bool ok;
            //reset
            QTextStream cout(stdout);
            QString password = "Radixweb8";
lable:  QString response = QInputDialog::getText(0,"Athuntication","Password:", QLineEdit::Normal,"DEFAULT TEXT",&ok);
            if(QString::compare(response, password, Qt::CaseInsensitive) == 0)
            {
                on_Pause_clicked();
                _startTime = time(NULL);
                _startFlag = false;
                _pauseTime = 0;
                onScreen  = 0;
                _waitTime = 0;
                _pauseFlag = false;
                ui->label_3->setText(QApplication::translate("TimeTracker", "            00:00:00", 0));
            }
            else
            {
                msgBox.setInformativeText("wrong pass word \n Do you wanna try again");
                msgBox.setStandardButtons(QMessageBox::Yes |
                                          QMessageBox::No);
                ret = msgBox.exec();
                if(QMessageBox::Yes == ret)
                {
                    goto lable;
                }
            }
        }
    }
    else
    {
        msgBox.setInformativeText("Time Tracker is not Started");
        ret = msgBox.exec();
    }

}

void TimeTracker::on_Resume_clicked()
{    if(_startFlag)
    {
        //resume
        if(_pauseFlag)
        {
            _pauseTime = time(NULL) - _pauseTime;
            _waitTime = _pauseTime + _waitTime;
            _pauseFlag = false;
        }
    }
}

void TimeTracker::on_stop_clicked()
{
    int ret =  0;
    QMessageBox msgBox;
    on_Pause_clicked();
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to Abort your changes?");
    msgBox.setStandardButtons(QMessageBox::Yes |
                              QMessageBox::No);
    ret = msgBox.exec();
    if(QMessageBox::Yes == ret)
    {
        exit(0);
    }
    else
    {
        on_Resume_clicked();
    }
}

void TimeTracker::View_timeTracker()
{
    if(_startFlag)
    {
        if(!_pauseFlag)
        {
            onScreen = time(NULL) - _startTime - _waitTime;
        }

        int hours = floor(onScreen / 3600);
        int mins = floor((onScreen - (hours*3600)) / 60);
        int secs = floor(onScreen % 60);
        QString data;
        if(hours < 10 && mins < 10 && secs < 10)
        {
            data = " 0" +  QString::number(hours) + ":0" + QString::number(mins) + ":0" + QString::number(secs);
        }
        else if(hours < 10 && mins < 10)
        {
            data = " 0" +  QString::number(hours) + ":0" + QString::number(mins) + ":" + QString::number(secs);
        }
        else if(hours < 10)
        {
            data = " 0" +  QString::number(hours) + ":" + QString::number(mins) + ":" + QString::number(secs);
        }
        else
        {
            data = " " +  QString::number(hours) + ":" + QString::number(mins) + ":" + QString::number(secs);
        }
        ui->label->setText(QApplication::translate("TimeTracker", data.toStdString().c_str(), 0));
    }
}
