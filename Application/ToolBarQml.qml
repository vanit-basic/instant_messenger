import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

Item {
  //  x: 0
    width: 355
    height: 44

    ToolBar {
        id: toolBar
        anchors.fill: parent
        Button {
            id: homebut
            width: 30
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            background: Rectangle {
                color: "transparent"
            }
            Image {
                id: image
                //            x: 0
                //            y: 0
                width: 30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                source: "home.png"
            }
        }
        Image {
            id: image1
            y: 0
            width: 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30
            fillMode: Image.PreserveAspectFit
            source: "searchb.png"
        }

        Image {
            id: image2
            x: 0
            y: 0
            width: 30
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
            source: "chat.png"
        }
    }
}
