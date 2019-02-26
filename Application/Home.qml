import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Window 2.2

Page {
    id:home


    footer:TabBar{

        id:tab
        currentIndex: swipe.currentIndex
        TabButton{
            id:tb1
            text: "Search"
        }
        TabButton{
            text: "Home"
        }
        TabButton{
            text: "Message"
        }
    }
    SwipeView{
        anchors.fill: parent
        id:swipe
        currentIndex:tab.currentIndex

        Page{
            Label{
                width: 200
                height: 90
                text: "Page1"
            }

        }
       HomePage{
           //       StackView{
           //           id: homeStack
           //           initialItem: Qt.resolvedUrl("HomePage.qml")
           //       }
       }
        Message{}

    }

}
