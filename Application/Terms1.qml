import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12

Page {
    id:wind_terms
    Rectangle{
        id:background_color
        width: wind_terms.width
        height: wind_terms.height
        clip:true
        gradient: Gradient{
            GradientStop { position: 0.0;color:"dimgrey"}
            GradientStop { position: 0.25;color:"gray"}
            GradientStop { position: 0.5;color:"darkgrey"}
            GradientStop { position: 0.75;color:"silver"}
            GradientStop{ position: 1.0;color:"lightgrey"}
        }
        Rectangle {
            id: rect
            x: 0
            y: 45
            width: parent.width
            height: 1
            color: "#ffffff"
        }
    }
    Rectangle {
        id: toplabel
        width:wind_terms.width
        height: 44
        color: "transparent"
        Text {
            id: label_text
            text: qsTr("Terms")
            font.pointSize: 18
            color: "lightgrey"
            anchors.centerIn: parent
        }

        Button {
            id: button
            width: back.width
            height: back.height
            anchors.left: parent.left
            anchors.leftMargin: 15
            Text {
                id: back
                text: qsTr("<")
                font.pointSize: 30
                color: "white"
                anchors.centerIn: parent
            }
            background: Rectangle{
                color:"transparent"
            }
            onClicked: stack.pop()
        }

    }
    Rectangle {
        id: middlelabel
        width:wind_terms.width
        height: 72
        anchors.top: toplabel.bottom
        color: "transparent"
        Rectangle{
            height: 2
            width: 25
            anchors.verticalCenter:parent.verticalCenter
            anchors.left: our_story.right
            anchors.leftMargin: 10
        }
        Rectangle{
            height: 2
            width: 25
            anchors.verticalCenter:parent.verticalCenter
            anchors.right: our_story.left
            anchors.rightMargin: 10
        }
        Text{
            id:our_story
            text: "OUR STORY"
            color: "white"
            font.pointSize: 15
            anchors.centerIn: parent
        }
    }

    Rectangle{
        id: textRect
        width:wind_terms.width - 60
        height: wind_terms.height - toplabel.height - middlelabel.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: middlelabel.bottom
        color: "transparent"
        Flickable {
            id: flick
            anchors.fill: parent
            contentHeight: text.height
            clip: true
            Text {
                text:"Mafia, also known as Werewolf, is a party game created by Dmitry Davidoff in 1986
modelling a conflict between two groups: an informed minority (the mafia),and an
uninformed majority Mafia, also known as Werewolf, is a party game created by Dmitry Davidoff in 1986
modelling a conflict between two groups: an informed minority (the mafia),and an
uninformed majorityMafia, also known as Werewolf, is a party game created by Dmitry Davidoff in 1986
modelling a conflict between two groups: an informed minority (the mafia),and an
uninformed majorityMafia, also known as Werewolf, is a party game created by Dmitry Davidoff in 1986
modelling a conflict between two groups: an informed minority (the mafia),and an
uninformed majorityMafia, also known as Werewolf, is a party game created by Dmitry Davidoff in 1986
modelling a conflict between two groups: an informed minority (the mafia),and an
uninformed majority"
                id: text
                wrapMode: TextArea.Wrap
                width: parent.width
                font.pointSize: 18
            }
        }
    }
}
