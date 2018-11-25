#include <QXmlStreamReader>
#include <QDebug>

#include "messagecontroller.h"
#include "servermanager.h"


MessageController::MessageController(QObject* parent) :
    QObject(parent),
    serverManager(nullptr)
{

}

void MessageController::setUserName(const QString& _userName)
{
    userName = _userName;

    if (serverManager == nullptr)
    {
        serverManager = new ServerManager(userName, this);
        connect(serverManager, SIGNAL( signalMessageReceived(const QByteArray& ) ),
                this, SLOT( messageReceive(const QByteArray& ) ));
    }
    else
        serverManager->setUserName(userName);
}

void MessageController::messageSend(const QString& message)
{
    serverManager->messageSend(message);
    emit signalMessageReceived(userName, message);
}

void MessageController::messageReceive(const QByteArray& response)
{
    QXmlStreamReader responseXml(response);

    QString status("");
    QString botName("");
    QString responseMessage("");

    while ( !responseXml.atEnd() )
    {
        responseXml.readNext();

        if (responseXml.name() == "success")
           status = responseXml.readElementText();
        if (responseXml.name() == "bot_name")
            botName = responseXml.readElementText();
        if (responseXml.name() == "response")
            responseMessage = responseXml.readElementText();

    }

    if (responseXml.hasError())
    {
        //Ошибка
        qDebug() << "Ошибка при обработке XML-ответа от сервера: " << responseXml.errorString();
    }

//    qDebug() << "Статус: " << status;
//    qDebug() << "Имя бота: " << botName;
//    qDebug() << "Ответное сообщение: " << responseMessage;

    if (status == "1")
        emit signalMessageReceived(botName, responseMessage);
    else
        emit signalMessageReceived("Ошибка", "Ответ не распознан");
}
