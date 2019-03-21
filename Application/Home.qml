import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height
title: qsTr("MafClub")
    id:home
    footer:TabBar{
        height: 44
        id:tab
        currentIndex: 1
        onCurrentIndexChanged: swipe.currentIndex = currentIndex
        background: Rectangle{
            anchors.fill: parent
            color: tab.currentIndex ===1 || tab.currentIndex ===0?"lightgray":"white"
        }
        TabButton{
            id:tb1
            height: parent.height
            background: Rectangle{
                color: tab.currentIndex === 0 ? "transparent" : "transparent"
            }
            Button{
                id:sear
                width:parent.height
                height:parent.height
                background: Rectangle{                   
                    color: "transparent"                   
                }
                anchors.centerIn: parent
                icon.source: "qrc:/searchb.png"
                icon.color :tab.currentIndex ===0 ?"#476b6b":"gray"
                onClicked: {
                    tab.currentIndex = 0
                }
            }
        }
        TabButton{
            id:tb2
            height: parent.height
            background: Rectangle{
                color: (tab.currentIndex === 1) ? "transparent" : "transparent"
            }
            Button{
                id:home1
                width: parent.height
                height:parent.height
                background: Rectangle{                    
                    color: "transparent"                    
                }
                anchors.centerIn: parent
                icon.source: "qrc:/home.png"
                icon.color :tab.currentIndex ===1 ?"#476b6b":"gray"
                onClicked: {
                    tab.currentIndex = 1
                }
            }
        }
        TabButton{
            id:tb3
            height: parent.height
            background: Rectangle{
                color: tab.currentIndex === 2 ? "transparent" : "transparent"
            }
            Button{
                id:chat
                width:parent.height
                height:parent.height
                background: Rectangle{                   
                    color: "transparent"                 
                }
                anchors.centerIn: parent
                icon.source: "qrc:/chat.png"
                icon.color :tab.currentIndex ===2 ?"#476b6b":"gray"
                onClicked:{
                    tab.currentIndex = 2
                }
            }
        }
    }
    SwipeView{
        currentIndex: 1
        onCurrentIndexChanged: tab.currentIndex = currentIndex
        anchors.fill: parent
        id:swipe
        Search{}
        HomePage{}
        Message{}
    }
}
