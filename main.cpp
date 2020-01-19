#include <QtCore/QCoreApplication>
#include "ws2client.h"
#include "controller.h"
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Ws2Client wsClient;
    Controller controller;
    QThread thread;

    QObject::connect(&controller, &Controller::startWS2, &wsClient, &Ws2Client::startConnection, Qt::QueuedConnection);
    QObject::connect(&controller, &Controller::sendValue, &wsClient, &Ws2Client::updateValue, Qt::QueuedConnection);

    wsClient.moveToThread(&thread);

    thread.start();
    controller.start();

    return a.exec();
}
