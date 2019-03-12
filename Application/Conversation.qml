import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page{
    id: wind1
    Component.onCompleted: console.log(stack00.status)
    header: ToolBar{
        id:top
        Label{
            text: "Miqo"
            anchors.centerIn: parent
        }
        ToolButton{
            text: "<"
            onClicked: {
                onClicked: { stackMess.pop(); swipe.interactive = true ; tab.visible = true}
            }
        }
    }
    footer: ToolBar{
        id: root
        width: parent.width
        height: 44
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        ScrollView {
            width: root.width - ((root.width/10) * 2) - (root.width/15)*2
            x:  (root.width/10) + root.width/15
            height: root.height - (root.height/5)
            clip: true
            TextArea {
                id: textArea
                clip: true
                width: root.width - ((root.width/10) * 2) - (root.width/15)*2
                height: root.height - (root.height/5)
                wrapMode: "WrapAtWordBoundaryOrAnywhere"
                placeholderText: "Send a message..."
            }
        }
        ToolButton{
            background: Rectangle{
                border.color: "green"
                radius: 30
            }
            height: parent.height
            width: height
            id: add
            text: "+"
            font.pixelSize: 25
            anchors.left: parent.left
            anchors.leftMargin: 5
        }
        ToolButton{
            background: Rectangle{
                border.color: "green"
                radius: 30
            }
            height: parent.height
            width: 55
            id: send
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            text: "Send"
        }
    }
}
