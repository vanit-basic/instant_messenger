import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.3

Page {
    id:window
    Rectangle{
        id:background_color
        anchors.fill: parent
        clip:true
        gradient: Gradient{
            GradientStop { position: 0.0;color:"dimgrey"}
            GradientStop { position: 0.25;color:"gray"}
            GradientStop { position: 0.5;color:"darkgrey"}
            GradientStop { position: 0.75;color:"silver"}
            GradientStop{ position: 1.0;color:"lightgrey"}
        }
        MouseArea{
            anchors.fill: parent
            onPressed: {Qt.inputMethod.hide()}
            Rectangle {
                id: rect
                x: 0
                y: 45
                width: window.width
                height: 1
                color: "#ffffff"
            }
            Rectangle{
                id:for_search
                width:window.width
                height: (window.height)/4
                color: "grey"
                anchors.top: parent.top
                anchors.topMargin: 46
                TextField {
                    id: textField
                    width: parent.width/2
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: (parent.height)/2
                    background: Rectangle{
                        radius: 10
                    }
                    placeholderText: " Write your question"
                }
                Text{
                    id:hello_lab
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: (hello_lab.width > for_search.width)?(parent.height)/7 :(parent.height)/4
                    text: "Hello! How can we help you?"
                    wrapMode: Text.WordWrap
                    color: "white"
                    font.pointSize: (hello_lab.width > for_search.width)?13:20
                }
            }
            Rectangle{
                id:for_questions
                width:window.width-30
                anchors.horizontalCenter:  parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.top:for_search.bottom
                anchors.bottomMargin: 10
                color: "transparent"
                ListModel{
                    id:quest_model
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                    ListElement{
                        name:"➣ How does game work.How does game work?"
                    }
                }
                ListView{
                    anchors.fill: parent
                    anchors.bottom: parent.bottom
                    spacing: 10
                    model: quest_model
                    clip: true
                    delegate:
                        Rectangle{
                        width: parent.width
                        height: txt.implicitHeight
                        color: "transparent"
                        Text{
                            id:txt
                            anchors.left: parent.left
                            text: name
                            color:"#08088A"
                            wrapMode: Text.WordWrap
                            width: parent.width
                            Rectangle{
                                color: "transparent"
                            }
                            MouseArea {
                                anchors.fill: parent
                               onClicked: { parent.color = 'red' }
                            }
                        }
                    }
                }
            }
            Label {
                id: toplabel
                x: 0
                y: 0
                width:window.width
                height: 44
                Text {
                    id: label_text
                    text: qsTr("Help Center")
                    font.pointSize: 18
                    color: "lightgrey"
                    anchors.centerIn: parent
                }
                Button {
                    id: button
                    x: 8
                    y: 6
                    width: 61
                    height: 40
                    Text {
                        id: back
                        text: qsTr("<")
                        anchors.verticalCenterOffset: -3
                        anchors.horizontalCenterOffset: 0
                        font.pointSize: 30
                        color: "white"
                        anchors.centerIn: parent
                    }
                    background: Rectangle{
                        color:"transparent"
                    }
                    onClicked: stack00.pop()
                }
            }
            RoundButton {
                id: message_from
                height:50
                width:50
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.bottom: parent.bottom
                anchors.bottomMargin: toplabel.height
                Text {
                    text: qsTr("Call")
                    anchors.centerIn: parent
                }
                background:Rectangle{
                    radius: 30
                }
            }
        }
    }
}
