import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1
import "Request_response.js" as Logic
Page{
    id:wind
    property var ob
    Component.onCompleted: ob = new Logic.Account()
    Drawer {
        id: drawer
        width:  wind.width-rectangle.x-tab_stat.width+50
        height: Screen.height
        dragMargin: -1
        edge: Qt.RightEdge
        background: Rectangle{
            color:"grey"
        }
        Column{
            anchors.fill: parent
            spacing: 10
            Rectangle{
                width: parent.width
                height: 46
                color: "transparent"
                Image {
                    id:settingsImg
                    source: "qrc:/settings.png"
                    width:35
                    height: 35
                    anchors.right: settingsText.left
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text{
                    id: settingsText
                    text: "Settings"
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 18
                    color:"lightgrey"
                    anchors.centerIn: parent
                }
                Rectangle{
                    border.color: "white"
                    height:1
                    width:parent.width
                    anchors.bottom: parent.bottom
                }
            }
            Rectangle{
                width: parent.width
                height: 30
                color: "transparent"
                Image {
                    id: editphoto
                    source: "qrc:/editprofile.png"
                    height: 30
                    width: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Button{
                    width: edit_profile.width
                    height: edit_profile.height
                    anchors.left: editphoto.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    background:Rectangle{
                        color: "gray"
                    }
                    Text{
                        id:edit_profile
                        text: "Edit profile"
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                        font.pointSize: 15
                    }
                    onClicked:{
                        drawer.close()
                        stack00.push(Qt.resolvedUrl("Edit_Profile.qml"))
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 30
                color: "transparent"
                Image {
                    id: passphoto
                    source: "qrc:/password.png"
                    height: 30
                    width: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Button{
                    width: password.width
                    height: password.height
                    anchors.left: passphoto.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    background:Rectangle{
                        color: "gray"
                    }
                    Text{
                        id:password
                        text: "Change Password"
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                        font.pointSize: 15
                    }
                    onClicked: {
                        drawer.close()
                        stack00.push(Qt.resolvedUrl("Change_Password.qml"))
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 30
                color: "transparent"
                Image {
                    id: langphoto
                    source: "qrc:/language.png"
                    height: 30
                    width: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Button{
                    width: language.width
                    height: language.height
                    anchors.left: langphoto.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    background:Rectangle{
                        color: "gray"
                    }
                    Text{
                        id:language
                        text: "Language"
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                        font.pointSize: 15
                    }
                }
                ComboBox{
                    id: combo
                    width: 80
                    height: language.height +6
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 5
                    displayText: "ARM"
                    font.pointSize: 15
                    background: Rectangle{
                        color: "transparent"
                        border.color: "black"
                    }
                    onActivated: {
                        combo.displayText = model.get(currentIndex).lang
                    }
                    Material.background: Material.transparent
                    contentItem: Text{
                        id: comboText
                        text: combo.displayText
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        anchors.leftMargin: 5
                        anchors.left: parent.left
                    }
                    indicator: Image{
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/indicator.png"
                        width: 15
                        height: 10
                    }
                    model:ListModel {
                        id: model

                        ListElement {
                            lang: "EN"
                            sources: "qrc:/us.png"
                        }
                        ListElement {
                            lang: "RU"
                            sources: "qrc:/ru.png"
                        }
                        ListElement {
                            lang: "ES"
                            sources: "qrc:/es.png"
                        }
                        ListElement {
                            lang: "ARM"
                            sources: "qrc:/arm.png"
                        }
                    }
                    delegate: ItemDelegate {
                        width: combo.width
                        contentItem: Rectangle{
                            color: "lightgray"
                            anchors.fill: parent
                            Text {
                                text: lang
                                font.pointSize: 15
                                color: "black"
                                verticalAlignment: Text.AlignVCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 4
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Image{
                                width: 25
                                height: 15
                                anchors.right: parent.right
                                anchors.rightMargin: 4
                                anchors.verticalCenter: parent.verticalCenter
                                source: sources
                            }
                        }
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 30
                color: "transparent"
                Image {
                    id: soundhoto
                    source: "qrc:/volume.png"
                    height: 30
                    width: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Button{
                    width: sound.width
                    height: sound.height
                    anchors.left: soundhoto.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    background:Rectangle{
                        color: "gray"
                    }
                    Text{
                        id:sound
                        text: "Sound"
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                        font.pointSize: 15
                    }
                }
                Switch{
                    id: control
                    anchors.right: parent.right
                    anchors.rightMargin: 3
                    anchors.verticalCenter: parent.verticalCenter
                    checked: true
                    onCheckedChanged:{console.log("switch")}
                    indicator: Rectangle {
                        width: 50
                        height: parent.height - 10
                        anchors.verticalCenter: parent.verticalCenter
                        radius: 13
                        color: control.checked ? "#17a81a" : "#ffffff"
                        Rectangle {
                            x: control.checked ? parent.width - width : 0
                            width: height
                            height: parent.height
                            radius: 13
                            color: control.down ? "#cccccc" : "#ffffff"
                            border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
                        }
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 30
                color: "transparent"
                Image {
                    id: helpphoto
                    source: "qrc:/support.png"
                    height: 30
                    width: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Button{
                    width: help.width
                    height: help.height
                    anchors.left: helpphoto.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    background:Rectangle{
                        color: "gray"
                    }
                    Text{
                        id:help
                        text: "Help Center"
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                        font.pointSize: 15
                    }
                    onClicked:{
                        drawer.close()
                        stack00.push(Qt.resolvedUrl("Help_Center.qml"))
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 30
                color: "transparent"
                Image {
                    id: termsphoto
                    source: "qrc:/terms.png"
                    height: 30
                    width: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Button{
                    width: terms.width
                    height: terms.height
                    anchors.left: termsphoto.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    background:Rectangle{
                        color: "gray"
                    }
                    Text{
                        id:terms
                        text: "Terms and Conditions"
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                        font.pointSize: 15
                    }
                    onClicked:{
                        drawer.close()
                        stack00.push(Qt.resolvedUrl("Terms.qml"))
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 30
                color: "transparent"
                Image {
                    id: aboutphoto
                    source: "qrc:/about.png"
                    height: 30
                    width: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Button{
                    width: about.width
                    height: about.height
                    anchors.left: aboutphoto.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    background:Rectangle{
                        color: "gray"
                    }
                    Text{
                        id:about
                        text: "About us"
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                        font.pointSize: 15
                    }
                    onClicked:{
                        drawer.close()
                        stack00.push(Qt.resolvedUrl("About_us.qml"))
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 30
                color: "transparent"
                Image {
                    id: signoutphoto
                    source: "qrc:/signout.png"
                    height: 30
                    width: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Button{
                    width: signout.width
                    height: signout.height
                    anchors.left: signoutphoto.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    background:Rectangle{
                        color: "gray"
                    }
                    Text{
                        id:signout
                        text: "Sign Out"
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                        font.pointSize: 15
                    }
                    onClicked:{                       
                         ob.signOut("u1", "6")
                        stack.push(Qt.resolvedUrl("Sign_in.qml"))
                    }
                }
            }
        }
    }
    Rectangle{
        id:back_color
        x: 0
        y: 0
        width: wind.width
        height: wind.height
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
            width: wind.width
            height: 1
            color: "#ffffff"
        }
        Rectangle {
            id: rectangle
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin:  toplabel.height + middlelabel.height+ 10//(wind.height)/8
            anchors.bottom: /*tool_bar_form.top*/ parent.bottom
            anchors.bottomMargin: bar.height
            width: wind.width - 2*nextbut.width
            height: 350
            color: "transparent"
            TabBar {
                id: bar
                width: parent.width
                TabButton {
                    id:tab_stat
                    text: qsTr("Statistics")
                }
                TabButton {
                    id: tabButton
                    text: qsTr("Information")
                }
            }
            StackLayout {
                width: parent.width
                anchors.fill: rectangle
                anchors.topMargin: tabButton.height
                currentIndex: bar.currentIndex               
                ListView{
                    id:statistic
                    spacing: 3
                    model: list_model_stat
                    clip: true
                    delegate:
                        Rectangle{
                        width: rectangle.width
                        height:  50
                        Image {
                            id: stat
                            source: /*"qrc:/vector-gray-wooden-planks-background.jpg"*/ "qrc:/taxtak.png"
                            anchors.fill: parent
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                text: name
                                color: "white"
                            }
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.rightMargin: 10
                                anchors.right: parent.right
                                text:number
                                color: "white"
                            }
                        }
                    }
                }
                ListModel{
                    id:list_model_stat
                    ListElement{
                        name:"Played games"
                        number:"15"
                    }
                    ListElement{
                        name:"Red card"
                        number:"5"
                    }
                    ListElement{
                        name:"Black card"
                        number:"5"
                    }
                    ListElement{
                        name:"Sheriff"
                        number:"2"
                    }
                    ListElement{
                        name:"Don"
                        number:"3"
                    }
                    ListElement{
                        name:"Wins"
                        number:"10"
                    }
                    ListElement{
                        name:"Fails"
                        number:"5"
                    }
                    ListElement{
                        name:"Killed"
                        number:"7"
                    }
                }
                ListView{
                    id:information
                    clip: true
                    spacing: 3
                    model: list_model_info
                    delegate:
                        Rectangle{
                        width: rectangle.width
                        height:  50
                        Image {
                            id: stat1
                            source:  "qrc:/taxtak.png"
                            anchors.fill: parent
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                text: name
                                color: "white"
                            }
                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.rightMargin: 10
                                anchors.right: parent.right
                                text:number
                                color: "white"
                            }
                        }
                    }
                    ListModel{
                        id:list_model_info
                        ListElement{
                            name:"Nickname"
                            number:"Valod001"
                        }
                        ListElement{
                            name:"Name"
                            number:"Valod"
                        }
                        ListElement{
                            name:"Surname"
                            number:"Valodyan"
                        }
                        ListElement{
                            name:"Date of birth"
                            number:"22.10.1998"
                        }
                        ListElement{
                            name:"Gender"
                            number:"Male"
                        }
                        ListElement{
                            name:"E-mail"
                            number:"valod001@mail.ru"
                        }
                    }
                }
            }
        }
        Label {
            id: toplabel
            x: 0
            y: 0
            width:wind.width
            height: 44
            Text {
                id: label_text
                text: qsTr("MY PROFILE")
                font.pointSize: 18
                color: "lightgrey"
                anchors.centerIn: parent
            }
            Button {
                id: button
                x: 8
                y: 16
                width: 61
                height: 40
                anchors.verticalCenter: parent.verticalCenter
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
            Button{
                id:nextbut
                anchors.left: parent.left
                anchors.leftMargin: parent.width-40
                anchors.top: parent.top
                anchors.topMargin: 5
                width: 30
                height: 40
                background: Rectangle{
                    color: "transparent"
                    BorderImage {
                        height: parent.height
                        width:parent.width
                        id: menuph
                        source: "qrc:/menu.png"
                    }
                }
                onClicked: drawer.open()
            }
            background: Rectangle{
                x:toplabel.x
                y:toplabel.y
                color: "transparent"
            }
        }
        Label {
            id: middlelabel
            x: 0
            y: 45
            width:wind.width
            height: 72
            RoundButton {
                id: roundButton
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 50
                width: 57
                height: 57
                text: "+"
            }
            Button {
                id: name_surname
                anchors.left: parent.left
                anchors.leftMargin: 130
                anchors.top: parent.top
                width: 164
                height: 40
                Text {
                    text: qsTr("Hrach Asatryan")
                    visible: true
                    font.pointSize: 15
                    anchors.centerIn: parent
                }
                background: Rectangle{
                    color:"transparent"
                }
            }
            ProgressBar {
                id: progressBar
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.leftMargin: 147
                anchors.bottomMargin: 20
                width: 93
                height: 6
                value: 0.5
                background: Rectangle{
                    radius: 20
                }
            }
            Label {
                id: level
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.leftMargin: 248
                anchors.bottomMargin: 15
                text: qsTr("Level 7")
                font.pointSize: 12
            }
        }
        Rectangle{
            id:freespace
            width:Screen.width
            height:(parent.height)/5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: bar.height
            color: "transparent"
        }
    }
}
