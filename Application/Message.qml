import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Dialogs 1.3

Page{
    id: wind
    property int listIndex: 0
    property string delId: ""
    MessageDialog{
        id:msgDialog
        visible: false
        title: "Message"
        text: "Are you sure?"
        standardButtons: StandardButton.Save | StandardButton.Cancel
        onAccepted: { delId.model.remove(listIndex); delPop.close()}
        onRejected: delPop.close()
    }
    Popup{
        id:delPop
        width: 150
        height: 100
        anchors.centerIn: parent
        contentItem:Column {
            spacing: 3
            Rectangle{
                id: popRect
                color: "transparent"
                width: parent.width
                height: 40
                MouseArea{
                    anchors.fill: parent
                    onClicked:msgDialog.open()
                }
                Image{
                    id:imgDel
                    width: 30
                    height: 30
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    source: "qrc:/trash.png"
                }
                Text{
                    text:"Delete"
                    font.pointSize: 15
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: imgDel.right
                    anchors.leftMargin: 10
                }
            }
            Rectangle{
                color: "transparent"
                width: parent.width
                height: 40
                MouseArea{
                    anchors.fill: parent
                    onClicked: txtMute.text == "Mute" ? txtMute.text = "Unmute" : txtMute.text = "Mute"
                }
                Image{
                    id:imgMute
                    width: 30
                    height: 30
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    source: "qrc:/volume.png"
                }
                Text{
                    id:txtMute
                    text:"Mute"
                    font.pointSize: 15
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: imgMute.right
                    anchors.leftMargin: 10
                }
            }
        }
    }
    Component{
        id:delegate
        Rectangle{
            width: wind.width
            height: 60
            color: "yellow"
            MouseArea{
                anchors.fill: parent
                onPressAndHold: { delPop.open(); listIndex = index}
            }

            Image{
                id: img
                source: "qrc:/us.png"
                width: 50
                height: 50
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                fillMode: Image.PreserveAspectCrop
                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: mask
                }
                Rectangle{
                    id: mask
                    width: 50
                    height: 50
                    radius: 50
                    visible: false
                }
            }
            Text{
                id: name
                text: textName
                font.pointSize: 20
                anchors.left: img.right
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 10
            }
            Text{
                id:msg
                text: message
                font.pointSize: 13
                x:name.x + 5
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
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
                    id: list0
                    ListView{
                        id: listV1
                        objectName: "listM0"
                        anchors.fill: parent
                        spacing: 2
                        clip: true
                        ScrollIndicator.vertical: ScrollIndicator { }
                        model:  ListModel{
                            ListElement{
                                textName: "VanIt"
                                message: "barev"
                            }
                        }
                        delegate: delegate
                    }
                }
                Item {
                    id: list1
                    ListView{
                        id: listV2
                        objectName: "listM1"
                        anchors.fill: parent
                        spacing: 2
                        clip: true
                        ScrollIndicator.vertical: ScrollIndicator { }
                        model: ListModel{
                            ListElement{
                                textName: "Miqo"
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
                        objectName: "listM2"
                        anchors.fill: parent
                        spacing: 2
                        clip:true
                        ScrollIndicator.vertical: ScrollIndicator { }
                        model: ListModel{
                            ListElement{
                                textName: "FrontEnd team"
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
