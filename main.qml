import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2


ApplicationWindow {
    id: mainWindow

    height: 640
    width: 480
    title: qsTr("TeamBot")
    visible: true

    Rectangle {
        anchors.fill: parent

        GridLayout {
            id: grid
            anchors.centerIn: parent
            rows: 3

                Label {
                    Layout.row: 1
                    Layout.column: 1
                    Layout.margins: 16
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Введите ваше имя:")

                }

                TextField {
                    id: userNameField

                    Layout.row: 2
                    Layout.column: 1
                    Layout.margins: 16
                    Layout.alignment: Qt.AlignHCenter
                }

                Button {
                    Layout.row: 3
                    Layout.column: 1
                    Layout.margins: 16
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Начать")



                    onClicked: {
                        if (userNameField.text == "")
                        {
                            messageDialog.open()
                        }
                        else
                        {
                            messageController.setUserName(userNameField.text)
                            chatWindow.show() // Открываем окно чата
                        }
                    }
                }
        }
    }

    ChatWindow
    {
        id: chatWindow
        title: qsTr("Чат")
    }

    MessageDialog
    {
        id: messageDialog

        text: "Введите имя пользователя."
    }
}
