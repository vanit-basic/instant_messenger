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
                Popup{
                    id:notpopup
                    x: bar.x
                    y:notifications.y + notifications.height + 3
                    width: bar.width
                    height: homePage.height/2
                    visible: tab.currentIndex !== 1 ? false : false
                    clip:true
                    background:Rectangle {
                        radius: 20
                    }

                    exit: Transition {
                        NumberAnimation {properties: "height"; from: notpopup.height; to: 0; easing.type: Easing.Linear }
                    }
                    enter: Transition {
                        NumberAnimation { properties: "height"; from: 0; to: homePage.height/2; easing.type: Easing.Linear }
                    }
                    closePolicy: Popup.CloseOnReleaseOutsideParent
                    contentData: ListView{
                        id:notList
                        anchors.fill: parent
                        spacing: 2
                        clip: true
                        model: ListModel{
                            ListElement{
                                number:"You have new present."
                                anun: "qrc:/not.png"
                            }
                            ListElement{
                                number:"You have new present."
                                anun: "qrc:/not.png"
                            }
                            ListElement{
                                number:"You have new present."
                                anun: "qrc:/not.png"
                            }
                            ListElement{
                                number:"You have new present."
                                anun: "qrc:/not.png"
                            }
                        }
                        delegate: ItemDelegate{
                            width:notList.width
                            height: 35
                            Rectangle{
                                //color: "#007399"
                                anchors.fill: parent
                                Image{
                                    id: notImage
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: 3
                                    source: anun
                                    height: 20
                                    width: 20
                                }
                                Text{
                                    anchors.left: notImage.right
                                    anchors.leftMargin:3
                                    text:number
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                                Image{
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.right: parent.right
                                    anchors.rightMargin: 3
                                    width: 20
                                    height: 30
                                    source: "qrc:/trash.png"
                                }
                            }
                        }
                    }

                }

                Image {
                    id: notifications
                    source: "not.png"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    width: 30
                    height: 30
                    MouseArea{
                        anchors.fill: parent
                        onClicked: notpopup.opened ? notpopup.close() : notpopup.open()
                    }
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
                    height: 40
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
                        width:tabbutton.width/2
                        height: parent.height
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "transparent"
                        Label{
                            id: minor
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            text: "3"
                        }
                        Label{
                            id: slash
                            anchors.centerIn: parent
                            text: "/"
                        }
                        Label{
                            id: major
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right:parent.right
                            anchors.rightMargin: 3
                            text: "12"
                        }
                    }
                }

            }
            Component{
                id:leadersDelegate
                Rectangle {
                    height: 40
                    width: bar.width
                    color: "#007399"
                    Image {
                        id: leadersAvatar
                        source: sources
                        height: parent.height - 10
                        width: height
                        anchors.left: winners.left
                        anchors.leftMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        fillMode: Image.PreserveAspectCrop
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: mask
                        }
                    }
                    Rectangle{
                        id: mask
                        width: leadersAvatar.width
                        height: leadersAvatar.height
                        radius: 250
                        visible: false
                    }

                    Text{
                        id:names
                        height: parent.height
                        horizontalAlignment:Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: leadersAvatar.left
                        anchors.leftMargin: (leadersAvatar.width)*1.5
                        text: txt
                        color: "white"
                    }
                    Text{
                        text: wins
                        height: parent.height
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                    }
                    Text {
                        id: winners
                        text: indexes
                        height: parent.height
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        horizontalAlignment:Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
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
                            model: ListModel{
                                ListElement {
                                    txt: "Astgh"
                                    wins: "33 wins"
                                    indexes: "1"
                                    sources: "qrc:/vector-gray-wooden-planks-background.jpg"
                                }

                                ListElement {
                                    txt: "Miqayel"
                                    wins: "31 wins"
                                    indexes: "2"
                                    sources: "qrc:/vector-gray-wooden-planks-background.jpg"
                                }
                                ListElement {
                                    txt: "Narek"
                                    wins: "31 wins"
                                    indexes: "3"
                                    sources: "qrc:/vector-gray-wooden-planks-background.jpg"
                                }
                            }
                            delegate: leadersDelegate
                            spacing: 4
                            clip:true
                        }
                    }
                }
            }
        }
    }
}
