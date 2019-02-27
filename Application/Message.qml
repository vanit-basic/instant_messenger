import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page{
    id: wind

    StackView{
        id:stackMess
        anchors.fill: parent
        initialItem:
        Rectangle{
            //anchors.fill: parent
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

                        model: /*MyListModel{}*/ ListModel{
                            ListElement{
                                textField: "VanIt"
                                message: "barev"
                            }
                        }
                        delegate: /*MyListDelegate{}*/ DelegateList{}
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

                        model: /*MyListPersonalModel{}*/ListModel{
                            ListElement{
                                textField: "Miqo"
                                message: "kyanqs))"
                            }
                        }
                        delegate: /*MyListDelegate{}*/ DelegateList{}
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
                        model: /*MyListGroupsModel{}*/ListModel{
                            ListElement{
                                textField: "FrontEnd team"
                                message: "barev"
                            }
                        }
                        delegate: /*MyListDelegate{}*/ DelegateList{}

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
                //onClicked: stackMess.push(kk)
            }

        }

    }
}
