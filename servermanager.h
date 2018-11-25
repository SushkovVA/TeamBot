#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>

class QNetworkReply;
class QNetworkAccessManager;

class ServerManager: public QObject
{
    Q_OBJECT

public:
    explicit ServerManager(const QString& userName, QObject *parent = nullptr);

public slots:
    // Отправление сообщения через QNetworkAccessManager
    void messageSend(const QString& message);
    void setUserName(const QString& userName);

private:
    const QString serverUrl;
    QString userName;
    QNetworkAccessManager* requestManager;

private slots:
    // Слот подключается к сигналу requestManager'а для получения ответа на сообщение
    void messageReceive(QNetworkReply* reply);

signals:
    // Сигнал высылает полученные от сервера данные (без обработки)
    void signalMessageReceived(const QByteArray& response);

};

#endif // SERVERMANAGER_H
