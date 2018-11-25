import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Window {
    id: chatWindow

    height: 640
    width: 480

    Connections
    {
        target: messageController

        onSignalMessageSended:
        {
            chatLines.append(userName+": "+message+"\n")
        }

        onSignalMessageReceived:
        {
            chatLines.append(botName+": "+message+"\n")
        }

    }


    ColumnLayout
    {
        id: columnLayout

        anchors.fill: parent
        spacing: 8
        anchors.margins: 8

        ScrollView
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            //anchors.bottom: rowLayout.top

            TextEdit
            {
                id: chatLines

                readOnly: true
                cursorVisible: false
            }
        }

        RowLayout
        {
            id: rowLayout
            spacing: 8

            TextField
            {
                id: chatEnter

                Layout.fillWidth: true
            }

            Button {
                id: buttonSend

                text: qsTr("Отправить")
                onClicked:
                {
                    if (chatEnter.text != "")
                    {
                        messageController.messageSend(chatEnter.text)
                        chatEnter.clear()
                    }
                }
            }

        }//RowLayout

    }//ColumnLayout

}
