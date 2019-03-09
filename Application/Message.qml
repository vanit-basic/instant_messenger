import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page{
    id: wind
    Component{
        id: delegate
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
                Button{
                    id: rm
                    width: 32
                    height: 32
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
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
                onClicked: {
                    stack55.push(Qt.resolvedUrl("Conversation.qml"))
                }
            }
        }
    }
    StackView{
        id:stackMess
        anchors.fill: parent
        initialItem:
        Rectangle{
        Rectangle{
            id:rect
            anchors.fill: parent
            width: parent.width
            height: parent.height -  toolbar.height - tabbar.height
            anchors.topMargin: toolbar.height + searchrect.height +tabbar.height
            color: "white"
        }
            Rectangle{
                id: toolbar
                width: parent.width
                height: 44
                color: "lightblue"
                anchors.top: parent.top
                Text {
                    text: "Message"
                    anchors.centerIn: parent
                    font.pixelSize: 30
                }
            }
            Rectangle{
                id: searchrect
                anchors.top: toolbar.bottom
                width: parent.width
                height: toolbar.height/2 + 5
                color: "white"
                TextField{
                    id: search
                    placeholderText: "Search..."
                    anchors.fill: parent
                    color: "black"
                    background: Rectangle{
                        anchors.fill: search
                        color: "lightgrey"
                    }
                }
            }
            TabBar{
                anchors.top:searchrect.bottom
                id:tabbar
                width: parent.width
                TabButton{
                    id: all
                    text: "All"
                }
                TabButton{
                    id:personal
                    text: "Personal"
                }
                TabButton{
                    id:groups
                    text: "Groups"
                }
            }
            StackLayout{
                anchors.fill: rect
                currentIndex: tabbar.currentIndex
                Item {
                    id: list1
                    ListView{
                        id: listV1
                        anchors.fill: parent
                        spacing: 2
                        clip: true
                        ScrollIndicator.vertical: ScrollIndicator { }
                        model:  ListModel{
                            ListElement{
                                textField: "VanIt"
                                message: "barev"
                            }
                        }
                        delegate: delegate
                    }
                }
                Item {
                    id: list3
                    ListView{
                        id: listV2
                        anchors.fill: parent
                        spacing: 2
                        clip: true
                        ScrollIndicator.vertical: ScrollIndicator { }
                        model: ListModel{
                            ListElement{
                                textField: "Miqo"
                                message: "kyanqs))"
                            }
                        }
                        delegate: delegate
                    }
                }
                Item {
                    id: list2
                    ListView{
                        id: listV3
                        anchors.fill: parent
                        spacing: 2
                        clip:true
                        ScrollIndicator.vertical: ScrollIndicator { }
                        model: ListModel{
                            ListElement{
                                textField: "FrontEnd team"
                                message: "barev"
                            }
                        }
                        delegate: delegate
                    }
                }
            }
            RoundButton{
                id:roundBtn
                width: 50
                height: 50
                background: Rectangle{
                    color: "green"
                    radius: roundBtn.radius
                }
                anchors.right: rect.right
                anchors.bottom: rect.bottom
                anchors.rightMargin: 10
                anchors.bottomMargin: 10
                font.pixelSize: 30
                text: "+"               
            }
        }
    }
}
