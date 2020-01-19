#include "ws2client.h"

QT_USE_NAMESPACE

Ws2Client::Ws2Client(QObject *parent) : QObject(parent){

}

void Ws2Client::startConnection()
{
    qDebug() << "Starting connection";

    webSocket = new QWebSocket();
    connect(webSocket, &QWebSocket::connected, this, &Ws2Client::onConnected, Qt::DirectConnection);
    connect(webSocket, &QWebSocket::disconnected, this, &Ws2Client::onDisconnected);
    connect(webSocket, &QWebSocket::textMessageReceived, this, &Ws2Client::onTextMessageReceived);
    webSocket->open(QUrl(QStringLiteral("ws://127.0.0.1")));

    wakeupTimer1 = new QTimer();
    connect(wakeupTimer1, &QTimer::timeout, this, &Ws2Client::onWakeupTimer1Timeout);
    wakeupTimer2 = new QTimer();
    connect(wakeupTimer2, &QTimer::timeout, this, &Ws2Client::onWakeupTimer2Timeout);
    stopTimer = new QTimer();
    connect(stopTimer, &QTimer::timeout, this, &Ws2Client::onStopTimerTimeout);

    qDebug() << "WebSocket server started on:" << QStringLiteral("127.0.0.1");
    qDebug() << "wbsocket thread: " << webSocket->thread()->objectName();
}

void Ws2Client::updateValue(qint8 val)
{
    if(initialized){
        QString cmdMsg = "{\"command\":\"Channel 1 at ";
        cmdMsg += QString::number(val);
        cmdMsg += "\",\"session\":";
        cmdMsg += session;
        cmdMsg += ",\"requestType\":\"command\",\"maxRequests\":0}";

        webSocket->sendTextMessage(cmdMsg);
        //{"command":"Channel 1 at 100","session":24,"requestType":"command","maxRequests":0}
    }
}

void Ws2Client::onConnected()
{
    qDebug() << "grandMA2 connected";
}

void Ws2Client::onDisconnected()
{
    qDebug() << "grandMA2 disconnected";
}

void Ws2Client::onTextMessageReceived(QString message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    qDebug() << "Rx: " << message;

    if(doc.isObject() && !doc.object().isEmpty()){
        if(!initialized){
            auto entry = doc.object().value("session");
            session = QString::number(entry.toDouble());


            QString myMsg = "{\"requestType\":\"login\",\"username\":\"guest\",\"password\":\"d41d8cd98f00b204e9800998ecf8427e\",\"session\":";
            myMsg += session;
            myMsg += ",\"maxRequests\":10}";
            webSocket->sendTextMessage(myMsg);

            initialized = true;
        }
    }
    else if(message == "server ready"){
        qDebug() << "Server is ready. Starting awake loop";
        webSocket->sendTextMessage("{\"session\":0}");

        wakeupTimer1->setInterval(300);
        wakeupTimer2->setInterval(10000);
        stopTimer->setInterval(30000);

        wakeupTimer1->start();
        wakeupTimer2->start();
        stopTimer->start();
    }
}

void Ws2Client::onWakeupTimer1Timeout()
{
    QString awakeMsg = "{\"requestType\":\"getdata\",\"data\":\"set,clear,solo,high\",\"session\":";
    awakeMsg += session;
    awakeMsg += ",\"maxRequests\":1}";

    webSocket->sendTextMessage(awakeMsg);
}

void Ws2Client::onWakeupTimer2Timeout()
{
    QString awakeMsg = "{\"session\":";
    awakeMsg += session;
    awakeMsg += "}";

    webSocket->sendTextMessage(awakeMsg);
}

void Ws2Client::onStopTimerTimeout()
{
    qDebug() << "60sec passed. Goodbye";

    QString disconnectMsg = "{\"requestType\":\"close\",\"session\":";
    disconnectMsg += session;
    disconnectMsg += "}";
    webSocket->sendTextMessage(disconnectMsg);
    webSocket->close();
    this->thread()->deleteLater();
    this->thread()->quit();
}
