import QtQuick 2.9
import QtQuick.Window 2.2
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
Page{
    StackView{
        anchors.fill: parent
        id:stack00
        //focus: true
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
            //anchors.fill: parent
            gradient: Gradient{
                GradientStop { position: 0.0;color:"dimgrey"}
                GradientStop { position: 0.25;color:"gray"}
                GradientStop { position: 0.5;color:"darkgrey"}
                GradientStop { position: 0.75;color:"silver"}
                GradientStop{ position: 1.0;color:"lightgrey"}
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
                               stack00.push(Qt.resolvedUrl("MyProfile.qml"))
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
                }
                    Component{
                        id:  dragDelegate
                        Rectangle{
                            width: 100
                            height: 30
                            color: "yellow"
                            Text{
                                text: "room1"
                                verticalAlignment: Text.AlignVCenter
                                anchors.centerIn: parent
                            }
                        }

                    }


                    StackLayout {
                        anchors.fill: parent
                        currentIndex: bar.currentIndex
                        Item {
                            id: joinTab
                            ListView {
                                id: view1
                                anchors { fill: parent; margins: 2 }
                                model: ListModel {}
                                delegate: dragDelegate
                                spacing: 2
                                //cacheBuffer: 50
                            }
                        }
                        Item {
                            id: watchTab
                            ListView {
                                id: view2
                                anchors { fill: parent; margins: 2 }
                                model: ListModel {}
                                delegate: dragDelegate
                                spacing: 2
                                //cacheBuffer: 50
                            }
                        }
                        Item {
                            id: leaderTab
                            ListView {
                                id: view3
                                anchors { fill: parent; margins: 2 }
                                model: ListModel {}
                                delegate: dragDelegate
                                spacing: 2
                                //cacheBuffer: 50
                            }
                        }
                    }
                }
            }


        }
    }
