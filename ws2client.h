#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QTimer>
#include <QObject>
#include <QThread>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>

class Ws2Client : public QObject
{
    Q_OBJECT
public:
    explicit Ws2Client(QObject *parent = nullptr);

public Q_SLOTS:
    void startConnection();
    void updateValue(qint8 value);

private Q_SLOTS:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void onWakeupTimer1Timeout();
    void onWakeupTimer2Timeout();
    void onStopTimerTimeout();

private:
    QWebSocket *webSocket;
    QTimer *wakeupTimer1;
    QTimer *wakeupTimer2;
    QTimer *stopTimer;
    bool initialized = false;
    QString session = "0";

};

#endif // WSCLIENT_H
