import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.2
import QtQml 2.12
//import QtQml.Models 2.12

Page {
    id:wind
    StackView{
        id:stackSearch
        anchors.fill: parent
        Keys.onPressed:  {
            if (event.key === Qt.Key_Back) {
                event.accepted = true
                if (stackMess.depth > 1) {
                    stackMess.pop()

                } else { swipe.currentIndex = 1}
            }
        }
        initialItem:  Rectangle{
            gradient: Gradient{
                GradientStop { position: 0.0;color:"dimgrey"}
                GradientStop { position: 0.25;color:"gray"}
                GradientStop { position: 0.5;color:"darkgrey"}
                GradientStop { position: 0.75;color:"silver"}
                GradientStop{ position: 1.0;color:"lightgrey"}
            }
            x: 0
            y: 0
            width: wind.width
            height: wind.height
            Rectangle{
                id: rec
                width: (2 * parent.width) / 2.5
                height: (parent.height)/12
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.horizontalCenter:parent.horizontalCenter
                color: "white"
                //radius: 30
                Button{
                    background: Rectangle {
                        color: "transparent"
                    }
                    id: search
                    icon.source: "qrc:/searchb.png"
                    icon.color: "teal"
                    y: rec.height / 2 - search.height / 2
                    width: 55
                    height: 55
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }

                TextField{
                    id:txt
                    height: rec.height
                    color: "black"
                    font.pointSize: 15
                    clip: true
                    anchors.left: parent.left
                    anchors.leftMargin: 45
                    anchors.right: parent.right
                    anchors.rightMargin: 45
                    placeholderText: "Name, Surname or Nickname"
                    selectByMouse: true
                    maximumLength : 100
                    background: Rectangle{
                        color: "transparent"
                    }

                    onPressed: {
                        popup.open()
                        //txt.text = "" popup.close()
                    }
                }

                Button{
                    background:
                        Rectangle{color: "transparent"}
                    id: cancel
                    icon.source: "qrc:/cancel.png"
                    icon.color: "teal"
                    y: rec.height / 2 - search.height / 2
                    width: 54
                    height: 54
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    onClicked: {
                        txt.text = " "
                    }
                }
            }

            Rectangle {
                id: jazz
                height: parent.height / 3
                width: rec.width //- 50
                anchors.top: rec.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                color: "transparent"
                Popup {
                    id: popup
                    height: parent.height
                    width: parent.width
                    anchors.centerIn: parent
                    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                    ListModel {
                        id: popmodel
                        ListElement{
                            name: "Jemma"
                        }
                        ListElement{
                            name: "Jemmasita"
                        }
                        ListElement{
                            name: "Jemmasita Gamer"
                        }
                        ListElement{
                            name: "Jemmasita the Great"
                        }
                    }

                    Component {
                        id: popcomp
                        Rectangle{
                            width: popup.width
                            height: 50
                            color: "transparent"

                            Text {
                                text: name
                                font.pixelSize: 18
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 45
                            }

                            MouseArea{
                                anchors.fill: parent
                                onClicked: txt.text = popmodel.get(index).name
                            }
                        }
                    }

                    contentData:  ListView {
                        id: popview
                        spacing: 7
                        anchors.fill: parent
                        clip: true
                        model: popmodel
                        delegate: popcomp
                    }
                }
            }


            ToolBar{
                id: toolbar
                anchors.top: rec.bottom
                anchors.topMargin: 60
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 15
                background: Rectangle{
                    color: "transparent"
                }

                RowLayout{
                    ToolButton{
                        id:tool0
                        icon.source: "avatar.png"
                        text: qsTr("User")
                        icon.color: "teal"
                        font.pointSize: 18
                        onClicked: {
                            txt.placeholderText = qsTr("Name, Surname or Nickname")
                            icon.color = "teal"
                            font.pointSize = 18
                            tool1.icon.color = "black"
                            tool1.font.pointSize = 15
                            groupview.visible = false
                            userview.visible = true
                            //font.bold = "true"
                            //font.underline = "true"
                        }
                        background: Rectangle{
                            color: "transparent"
                        }
                    }

                    ToolSeparator{}

                    ToolButton{
                        id: tool1
                        icon.source: "group.png"
                        text: qsTr("Group")
                        icon.color: "black"
                        font.pointSize: 15
                        onClicked: {
                            txt.placeholderText = qsTr("Group name")
                            icon.color = "teal"
                            font.pointSize = 18
                            tool0.icon.color = "black"
                            tool0.font.pointSize = 15
                            userview.visible = false
                            groupview.visible = true
                            //font.bold = "true"
                            //font.underline = "true"
                        }
                        background: Rectangle{
                            color: "transparent"
                        }
                    }
                    Item { Layout.fillWidth: true }
                }
            }

            Rectangle {
                id: foruser
                anchors.top: toolbar.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 10
                width: (2 * parent.width) / 2.5
                height: wind.height / 2
                color: "transparent"
                ListModel{
                    id: mod0
                    ListElement{
                        name: "Nare"
                        picture: "qrc:/avatar.png"
                    }
                    ListElement{
                        name: "Jemasita"
                        picture: "qrc:/avatar.png"
                    }
                    ListElement{
                        name: "Señorita"
                        picture: "qrc:/avatar.png"
                    }
                    ListElement{
                        name: "LoserForLife"
                        picture: "qrc:/avatar.png"
                    }
                    ListElement{
                        name: "Kolibri"
                        picture: "qrc:/avatar.png"
                    }
                    ListElement{
                        name: "Sensei"
                        picture: "qrc:/avatar.png"
                    }
                    ListElement{
                        name: "I don't have a name"
                        picture: "qrc:/avatar.png"
                    }
                    ListElement{
                        name: "Sunny"
                        picture: "qrc:/avatar.png"
                    }
                }

                Component {
                    id: mod0del
                    Rectangle{
                        width: wind.width - 50
                        height: 50
                        color: "transparent"
                        Image {
                            id: img
                            width: 30
                            height: 30
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            anchors.verticalCenter: parent.verticalCenter
                            source: picture
                        }

                        Text {
                            id: nametext
                            text: name
                            font.pixelSize: 18
                            anchors.left: img.right
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: stackSearch.push(Qt.resolvedUrl("qrc:/Users_profile.qml"))
                        }
                    }
                }
            }

            ListView {
                id: userview
                visible: true
                spacing: 7
                anchors.fill: foruser
                clip: true
                model: mod0
                delegate: mod0del
            }

            Rectangle {
                id: forgroup
                anchors.top: toolbar.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 10
                width: (2 * parent.width) / 2.5
                height: wind.height / 2
                color: "transparent"
                visible: false
                ListModel{
                    id: mod1
                    ListElement{
                        name: "Mafiosi"
                        picture: "qrc:/group.png"
                    }
                    ListElement{
                        name: "Join the fun"
                        picture: "qrc:/group.png"
                    }
                    ListElement{
                        name: "Señoritas"
                        picture: "qrc:/group.png"
                    }
                    ListElement{
                        name: "LoserForLife"
                        picture: "qrc:/group.png"
                    }
                    ListElement{
                        name: "Group for all"
                        picture: "qrc:/group.png"
                    }
                    ListElement{
                        name: "Señores"
                        picture: "qrc:/group.png"
                    }
                    ListElement{
                        name: "I don't have a name"
                        picture: "qrc:/group.png"
                    }
                    ListElement{
                        name: "Complicated group"
                        picture: "qrc:/group.png"
                    }
                }

                Component {
                    id: mod1del
                    Rectangle{
                        width: wind.width - 50
                        height: 50
                        color: "transparent"
                        Image {
                            id: img
                            width: 30
                            height: 30
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            anchors.verticalCenter: parent.verticalCenter
                            source: picture
                        }

                        Text {
                            text: name
                            font.pixelSize: 18
                            anchors.left: img.right
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        MouseArea{
                            anchors.fill: parent
                            //onClicked: stackSearch.push(Qt.resolvedUrl("qrc:/Group_profile.qml"))
                        }
                    }
                }
            }

            ListView {
                id: groupview
                visible: false
                spacing: 7
                anchors.fill: forgroup
                clip: true
                model: mod1
                delegate: mod1del
            }
        }
    }
}
