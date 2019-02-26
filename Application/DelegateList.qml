import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls 2.3
Page{

SwipeDelegate{
    id:swDel
    width: Screen.width
    height: Screen.height/8

    background: Rectangle{
        color:"white"
    }

  swipe.right:Rectangle{
        anchors.right: parent.right
        width: rm.width + mute.width + 20
        height: parent.height - 40
        anchors.verticalCenter: parent.verticalCenter
       // color: "navy"
        //height: parent.height
        Button{
            id: rm
            width: 32
            height: 32
          //  text: "Remove"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 5
            //anchors.bottomMargin:30
            background: Rectangle{
                BorderImage{
                    source: "qrc:/delete1.png"
                    anchors.fill: parent
                }

                anchors.fill: parent
                color: "red"
                radius: 20
            }
        }
        Button{
            id: mute
            width: 32
            height: 32
           // text: "Mute"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 5
            background: Rectangle{
                BorderImage{
                    source: "qrc:/notification.png"
                    anchors.fill: parent

                }

                anchors.fill: parent
                color: "red"
                radius: 20
            }
        }
}


    Image {
        id: userImage
        //source: "qrc:/user.png"
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 10
        anchors.topMargin: 10
        width: parent.height - 10
        height: parent.height - 10
    }
    Text {
        id: lastMessage
        anchors.top: textI.bottom
        anchors.topMargin: 3
        x:textI.x
        text: message
        color: "black"
        font.pixelSize: 12
    }
    Text{
        id: textI
        //anchors.centerIn: parent
        anchors.left: parent.left
        anchors.top:parent.top
        anchors.leftMargin: userImage.width + 30
        anchors.topMargin: 5
        text: textField
        font.pixelSize: 18
        color: "black"
    }

    MouseArea{
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        width: parent.width/2
        onReleased: {
            stack.push(Qt.resolvedUrl("Conversation.qml"))
            //stack.clear()
        }
       // onPressAndHold:pane.visible = true
}

    }
}
