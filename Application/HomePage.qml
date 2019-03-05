import QtQuick 2.9
import QtQuick.Window 2.2
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
Page{
    id:homePage
    StackView{
        anchors.fill: parent
        id:stack00
        Keys.onPressed:  {
            if (event.key === Qt.Key_Back) {
                event.accepted = true;
                if (stack00.depth > 1) {
                    stack00.pop()
                }
            }
        }
        initialItem:  Rectangle {
            id: root
            gradient: Gradient{
                GradientStop { position: 0.0;color:"dimgrey"}
                GradientStop { position: 0.25;color:"gray"}
                GradientStop { position: 0.5;color:"darkgrey"}
                GradientStop { position: 0.75;color:"silver"}
                GradientStop{ position: 1.0;color:"lightgrey"}
            }
            Rectangle{
                id:toolRect
                color: "transparent"
                width: parent.width
                height: 44
                Text {
                    text: "MafClub"
                    color: "white"
                    font.pointSize: 25
                    anchors.centerIn: parent
                }
            }

            Rectangle{
                id: inforect
                width: parent.width
                height: 60
                anchors.top: toolRect.bottom
                color: "transparent"
                RoundButton {
                    id: avatar
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    width: 50
                    height: 50
                    text: "+"
                    onClicked: stack00.push(Qt.resolvedUrl("MyProfile.qml"))
                }
                Image {
                    id: notifications
                    source: "not.png"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    width: 30
                    height: 30
                }
                Label {
                    id: userName
                    text: qsTr("Nare Stepanyan")
                    anchors.top: parent.top
                    anchors.left: avatar.right
                    anchors.leftMargin: 20
                }
                ProgressBar {
                    id: progressBar
                    x: userName.x
                    width: userName.width/2
                    to: 100
                    anchors.verticalCenter: parent.verticalCenter
                    value: 50
                }
                Label {
                    id: level
                    x: userName.x
                    text: qsTr("level 5")
                    font.pixelSize: 11
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                }
            }
            Button{
                id: start
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: inforect.bottom
                width: 80
                height: 40
                text: "START"
                background: Rectangle{
                    color: "#476b6b"
                    radius: 15
                }
            }

            TabBar {
                id: bar
                anchors.top: start.bottom
                anchors.topMargin: 15
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: root.bottom
                anchors.bottomMargin: 15
                width: parent.width - 30
                currentIndex: 0
                TabButton {
                    id: tabbutton
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
            }

            Component{
                id:  dragDelegate
                Rectangle{
                    width: bar.width
                    height: 35
                    color: "LightCyan"

                    Text{
                        id: rooms
                        text: "Room1"
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                    }
                    Button{
                        id: joinbutton
                        width: 60
                        height: 20
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Join"
                        contentItem: Text{
                            text: joinbutton.text
                            color: "lightgreen"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background:Rectangle {
                            color: "#476b6b"
                            radius: 8
                        }
                    }
                    Rectangle{
                        width:100
                        height: parent.height
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "transparent"
                        Label{
                            id: minor
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 3
                            text: "3"
                        }
                        Label{
                            id: major
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left:minor.right
                            anchors.leftMargin: 3
                            text: "/12"
                        }
                    }
                }

            }

            Rectangle{
                width: bar.width
                height: bar.height - tabbutton.height
                y:bar.y + tabbutton.height
                x:bar.x
                color: "transparent"
                StackLayout {
                    anchors.fill: parent
                    currentIndex: bar.currentIndex
                    Item {
                        id: joinTab
                        ListView {
                            id: view1
                            anchors { fill: parent; margins: 2 }
                            model: /*ListModel {}*/ 10
                            delegate: dragDelegate
                            spacing: 4
                            clip:true
                        }
                    }
                    Item {
                        id: watchTab
                        ListView {
                            id: view2
                            anchors { fill: parent; margins: 2 }
                            model: /*ListModel {}*/ 10
                            delegate: dragDelegate
                            spacing: 4
                            clip:true
                        }
                    }
                    Item {
                        id: leaderTab
                        ListView {
                            id: view3
                            anchors { fill: parent; margins: 2 }
                            model: /*ListModel {}*/10
                            delegate: dragDelegate
                            spacing: 4
                            clip:true
                        }
                    }
                }
            }
        }
    }
}
