import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page{
    id: wind1
    //Component.onCompleted: console.log(stack00.status)
    header: ToolBar{
        id:top
        Label{
            text: "Miqo"
            anchors.centerIn: parent
        }
        ToolButton{
            text: "<"
            onClicked: {
                stackMess.pop(); swipe.interactive = true ; tab.visible = true
            }
        }
    }
    footer: ToolBar{
        id: root
        width: parent.width
        height: 44
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Row{
            anchors.fill: parent

            ToolButton{
                background: Rectangle{
                    border.color: "green"
                    radius: 30
                }
                height: 40
                width: height
                id: add
                text: "+"
                font.pixelSize: 25
                //            anchors.left: parent.left
                //            anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
            }
            TextField {
                id: textArea
                clip: true
                width: root.width - 95
                wrapMode: "WrapAtWordBoundaryOrAnywhere"
                placeholderText: "Send a message..."


                //topInset: 20
            }


            ToolButton{
                background: Rectangle{
                    border.color: "green"
                    radius: 30
                }
                height: 30
                width: 55
                id: send
                //            anchors.right: parent.right
                //            anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                text: "Send"
            }
        }
    }
}
