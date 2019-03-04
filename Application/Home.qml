import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Window 2.2

Page {
    id:home


    footer:TabBar{
        height: 44
        id:tab

        currentIndex: 1

        onCurrentIndexChanged: swipe.currentIndex = currentIndex
        background: Rectangle{
            anchors.fill: parent
            color: tab.currentIndex ===1?"transparent":"transparent"
        }

        TabButton{
            id:tb1
            height: parent.height
            background: Rectangle{

                color: tab.currentIndex === 0 ? "transparent" : "transparent"
            }
            Button{
                id:sear
                width: /*tab.currentIndex ===0?parent.height:parent.height-10*/parent.height
                height:/*tab.currentIndex ===0?parent.height: parent.height-10*/parent.height
                background: Rectangle{
                    //radius: 50
                    color: "transparent"
                    // border.color: "black"
                }
                anchors.centerIn: parent
                icon.source: "qrc:/searchb.png"
                icon.color :tab.currentIndex ===0 ?"#476b6b":"gray"
//                icon.height: tab.currentIndex ===0?sear.height:sear.height-10
//                icon.width: tab.currentIndex ===0?sear.width:sear.width-10



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
                width: /*tab.currentIndex ===1?parent.height:parent.height-10*/parent.height
                height:/*tab.currentIndex ===1?parent.height: parent.height-10*/parent.height
                background: Rectangle{
                    //radius: 50
                    color: "transparent"
                    // border.color: "black"
                }
                anchors.centerIn: parent
                icon.source: "qrc:/home.png"
                icon.color :tab.currentIndex ===1 ?"#476b6b":"gray"
//                icon.height: tab.currentIndex ===1?home1.height:home1.height-10
//                icon.width: tab.currentIndex ===1?home1.width:home1.width-10


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
                width: /*tab.currentIndex ===2?parent.height+10:parent.height*/parent.height
                height:/*tab.currentIndex ===2?parent.height: parent.height-10*/parent.height
                background: Rectangle{
                    //radius: 50
                    color: "transparent"
                    //border.color: "black"
                }
                anchors.centerIn: parent
                icon.source: "qrc:/chat.png"
                icon.color :tab.currentIndex ===2 ?"#476b6b":"gray"

//                icon.height: tab.currentIndex ===2?chat.height:chat.height-10
//                icon.width: tab.currentIndex ===2?chat.width:chat.width-10


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
