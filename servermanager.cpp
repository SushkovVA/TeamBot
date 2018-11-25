#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "servermanager.h"

ServerManager::ServerManager(const QString& userName, QObject* parent) :
    QObject(parent),
    serverUrl("http://host1.demoproject2f.techcd.ru/chatbot/conversation_start.php?bot_id=2&say=userText&format=xml&Name=userName"),
    userName(userName),
    requestManager( new QNetworkAccessManager( this ) )

{
    connect( requestManager, SIGNAL( finished( QNetworkReply* ) ), SLOT( messageReceive(QNetworkReply* ) ) );
}

void ServerManager::messageSend(const QString& message)
{
    QString request = serverUrl;
    request = request.replace("userName", userName);
    request = request.replace("userText", message);
    //qDebug() << "REQUEST: " << request;
    requestManager->get(QNetworkRequest(QUrl(request)));
}

void ServerManager::setUserName(const QString& _userName)
{
    userName = _userName;
}

void ServerManager::messageReceive(QNetworkReply* reply)
{
    const QByteArray responseByte = reply->readAll();
    emit signalMessageReceived(responseByte);
}

