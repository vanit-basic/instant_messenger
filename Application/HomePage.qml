import QtQuick 2.9
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
Page{
    StackView{
    anchors.fill: parent
    id:homeStack
    //focus: true
    Keys.onPressed:  {
        if (event.key === Qt.Key_Back) {
            event.accepted = true;
            if (stack.depth > 1) {
                stack.pop()
            }
        }
    }
    initialItem:  Rectangle {
        id: root
        anchors.fill: parent
        gradient:Gradient {
            GradientStop {
                position: 0;
                color: "#476b6b" }
            GradientStop {
                position: 0.994;
                color: "#e0ebeb" }
        }
        Rectangle {
            id: upperPart
            width: parent.width
            height: (parent.height)/3
            color: "transparent"

            Label {
                id: mafClub
                anchors.horizontalCenter: parent.horizontalCenter
                y: upperPart.height / 7
                Text {
                    text: "MafClub"
                    color: "white"
                    font.pointSize: 30
                    anchors.centerIn: parent
                }
            }

            RoundButton {
                id: avatar
                x: avatar.width/2
                y: upperPart.height / 3
                width: 50
                height: 50
                text: "+"
                onClicked: /*homeStack.push(Qt.resolvedUrl("MyProfile.qml"))*/
                            stack.push(Qt.resolvedUrl("MyProfile.qml"))
            }

            ProgressBar {
                id: progressBar
                y: avatar.y + (avatar.height / 2)
                width: upperPart.width - (5 * avatar.width)
                anchors.horizontalCenter: parent.horizontalCenter
                value: 0.5
            }

            Rectangle {
                id: imageNot
                x: upperPart.width - avatar.width
                y:  upperPart.height / 3
                width: 30
                height: 30
                color: "transparent"
                Image {
                    id: notifications
                    source: "not.png"
                    width: 30
                    height: 30
                }
            }

            Label {

                id: userName
                x: progressBar.x
                y: progressBar.y - height -5
                text: qsTr("Nare Stepanyan")
            }

            Label {

                id: level
                x: progressBar.x
                y: progressBar.y + height
                text: qsTr("level 5")
                font.pixelSize: 9

            }

            Image {
                id: startGame
                //y: upperPart.y + 2 * height

                width: 110
                //height: 82
                source: "start.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.top: progressBar.bottom
                anchors.topMargin: /*(startGame.height)/3*/ 20

            }
        }

        Rectangle {
            id: middlePart
            width: parent.width - (avatar.width)
            // height: (parent.height - upperPart.height)/2
            //y: upperPart.height + (startGame.height)/2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.top:upperPart.bottom
            anchors.topMargin: startGame.height/2
            TabBar {
                id: bar
                width: parent.width
                //z: 2
                currentIndex: 0
                TabButton {
                    text: qsTr("Join")
                    rightPadding: -20
                    bottomPadding: -12
                    Image {
                        id: join
                        x: 3
                        y: 4
                        width: 39
                        height: 32
                        source: "joinGroup.png"
                    }
                }
                TabButton {
                    text: qsTr("Watch")
                    rightPadding: -20
                    bottomPadding: -12
                    Image {
                        id: watchGame
                        x: 0
                        y: 2
                        source: "watchGame.png"
                        width: 39
                        height: 32
                    }
                }
                TabButton {
                    text: qsTr("Leaders")
                    focusPolicy: Qt.StrongFocus
                    rightPadding: -20
                    bottomPadding: -12
                    Image {
                        id: leaders
                        x: 0
                        y: 4
                        source: "leaderTrophy.png"
                        width: 39
                        height: 32
                    }
                }

                StackLayout {
                    //width: parent.width
                    currentIndex: bar.currentIndex
                    Item {
                        id: joinTab
                    }
                    Item {
                        id: watchTab
                    }
                    Item {
                        id: leaderTab
                    }
                }
            }
        }


    }
}
}
