#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H

#include <QObject>

class ServerManager;

class MessageController : public QObject
{
    Q_OBJECT
public:
    explicit MessageController(QObject *parent = nullptr);

public slots:
    Q_INVOKABLE void setUserName(const QString& userName);
    Q_INVOKABLE void messageSend(const QString& message);

private:
    QString userName;
    // Отвечает за отправление и получение данных от сервера
    ServerManager* serverManager;

private slots:
    // Слот принимает сигнал от serverManager'а, после получения им ответа от сервера
    void messageReceive(const QByteArray& response);

signals:
    // Сигналы высылаемые в интерфейс для добавления сообщений в чат
    void signalMessageSended(const QString& userName, const QString& message);
    void signalMessageReceived(const QString& botName, const QString& message);
};

#endif // MESSAGECONTROLLER_H
