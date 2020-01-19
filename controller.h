#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    void start();
    void stop();

signals:
    void startWS2();
    void stopWS2();
    void sendValue(qint8 value);

private:
    QTimer cmdTimer;
    qint8 counter = 0;

    void onTimeout();

};

#endif // CONTROLLER_H
