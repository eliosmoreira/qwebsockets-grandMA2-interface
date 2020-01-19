#include "controller.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent){}

void Controller::start()
{
    emit startWS2();
    connect(&cmdTimer, &QTimer::timeout, this, &Controller::onTimeout);
    cmdTimer.setInterval(1000);
    cmdTimer.start();
}

void Controller::stop()
{
    emit stopWS2();
}

void Controller::onTimeout()
{
    emit sendValue(counter);
    counter += 2;
}
