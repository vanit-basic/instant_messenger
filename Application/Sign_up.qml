import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.5
Page {
    focus: true
    id:wind
    property variant days: [1, 2, 3, 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]
    property variant zuyg: [1, 2, 3, 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30]
    property variant nahanj: [1, 2, 3, 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29]
    property variant february: [1, 2, 3, 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28]
    property variant month: ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    property var years: [2005,2004,2003,2002,2001,2000,1999,1998,1997,1996,1995,1994,1993,1992,1991,1990,1989,1988,1987,1986,1985,1984,1983,1982,1981,1980,1979,1978,1977,1976,1975,1974,1973,1972,1971,1970,1969,1968,1967,1966,1965,1964,1963,1962,1961,1960,1959,1958,1957,1956,1955,1954,1953,1952,1951,1950,1949]
    Rectangle{
        width: Screen.width
        height: Screen.height
        color: "transparent"
        BorderImage {
            id: name
            source: "qrc:/51062817_2189626127969158_7173693744896540672_n.png"
            anchors.fill: parent
            Rectangle{
                id:go_top
                width: parent.width
                height: parent.height
                color: "transparent"
                MouseArea{
                    id:mouse
                    anchors.fill:parent
                    onPressed: {
                        Qt.inputMethod.hide()
                    }
                    Text {
                        id: register
                        height: back.height
                        text: qsTr("Register")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 30
                        color: "white"
                        anchors.topMargin: 5
                        anchors.horizontalCenter: mouse.horizontalCenter
                    }
                    Button{
                        id:back
                        x: 0
                        y:register.y
                        width: 52
                        height: 41
                        background: Rectangle{
                            color: "transparent"
                        }
                        onPressed: stack.pop()
                        Text {
                            id: back_text
                            x:parent.x
                            y:parent.y
                            width: parent.width
                            height: parent.height
                            text: qsTr("<")
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.topMargin: 5
                            font.pointSize: 30
                            color: "white"
                            anchors.top: parent.top
                        }
                    }
                    Column {
                        id: column
                        y:register.height+20
                        width: Screen.width-50
                        height: Screen.height -2*column.y
                        parent: go_top
                        spacing: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                        Row{
                            id:row_name
                            width: parent.width
                            height: (column.height-9*column.spacing)/9
                            Rectangle{
                                id:rec_name
                                width: repass_text.width+10
                                height: parent.height
                            color: "transparent"
                            Text {
                                id: name_text
                                text: qsTr("Name")
                                anchors.bottom: parent.bottom
                                color: "white"
                            }
                            }
                        TextInput{
                            id:enter_name
                            width: parent.width-rec_repass.width
                            height: 20
                            color: "white"
                            anchors.bottom: parent.bottom



                            Rectangle {
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onAccepted:  { enter_surname.focus = true}
                            EnterKey.type:  Qt.EnterKeyNext
                        }
                        }
                        Row{
                            width: parent.width
                            height: (column.height-9*column.spacing)/9
                            Rectangle{
                                id:rec_surname
                                width: repass_text.width+10
                                height: parent.height
                            color: "transparent"
                            Text {
                                id: surname_text
                                text: qsTr("Surname")
                                anchors.bottom: parent.bottom
                                color: "white"
                            }
                            }
                        TextInput{
                            id:enter_surname
                            width: parent.width-rec_repass.width
                            height: 20
                            color: "white"
                            anchors.bottom: parent.bottom
                            Rectangle {
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onAccepted:  { enter_email.focus = true}
                            EnterKey.type:  Qt.EnterKeyNext
                        }
                        }
                        Row{
                            width: parent.width
                           height: (column.height-9*column.spacing)/9
                            Rectangle{
                                id:rec_email
                                width: repass_text.width+10
                                height: parent.height
                            color: "transparent"
                            Text {
                                id: email_text
                                text: qsTr("Email")
                                anchors.bottom: parent.bottom
                                color: "white"
                            }
                            }
                        TextInput{
                            id:enter_email
                            width: parent.width-rec_repass.width
                            height: 20
                            color: "white"
                            anchors.bottom: parent.bottom
                            Rectangle {
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onAccepted:  {enter_login.focus = true}
                            EnterKey.type:  Qt.EnterKeyNext
                        }
                        }
                        ComboBox {
                            id: comboBox
                            width: parent.width
                            height: row_name.height
                            editable: false
                            Rectangle {
                                id:combo
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            background: Rectangle{
                                color: "transparent"
                            }
                            Rectangle{
                                height: parent.height
                                width: parent.width
                                anchors.left: parent.left
                                color: "transparent"
                                Text {
                                    id: slaq
                                    anchors.verticalCenter:  parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    text: qsTr("Birth date")
                                    color: "white"

                                }
                            }
                            Popup{
                                id: popup
                                x:parent.x
                                width:parent.width
                                height: 6*row_name.height
                                modal: true
                                background: Rectangle{
                                    color: "gray"
                                }
                                contentItem: Column{
                                    Row{
                                        height: parent.height-50
                                        width: parent.width
                                        Tumbler {
                                            id: month_t
                                            width: parent.width/2
                                            height: parent.height
                                            font.pointSize: 14
                                            model:  month
                                            visibleItemCount: 3
                                            onCurrentIndexChanged:    {
                                                if(currentIndex == 1){
                                                    if (years[year_t.currentIndex]%4 == 0)
                                                        day_t.model = nahanj
                                                    else
                                                        day_t.model = february

                                                } else if(currentIndex ==3 || currentIndex ==5 || currentIndex ==8 ||currentIndex ==10){
                                                    day_t.model = zuyg
                                                } else{
                                                    day_t.model = days
                                                }
                                            }
                                        }
                                        Tumbler {
                                            id: day_t
                                            width: parent.width/4
                                            height: parent.height
                                            font.pointSize: 14
                                            visibleItemCount: 3
                                            model: days
                                            currentIndex: 0
                                            font.bold: true
                                        }
                                        Tumbler {
                                            id: year_t
                                            width: parent.width/4
                                            height: parent.height
                                            font.pointSize: 14
                                            visibleItemCount: 3
                                            model: years
                                            currentIndex: 0
                                            onCurrentIndexChanged: {
                                                if(month_t.currentIndex == 1){
                                                    if (years[year_t.currentIndex]%4 == 0){
                                                        day_t.model = nahanj
                                                    }
                                                    else{day_t.model = february}
                                                }
                                            }
                                        }
                                    }
                                }
                                Button{
                                    height: sign_in.height
                                    width: sign_in.width-30
                                    text: "Save"
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    background: Rectangle{
                                        radius: 30
                                        color: "teal"
                                    }
                                    onClicked: {
                                        slaq.text =days[day_t.currentIndex]+"  "+ month[month_t.currentIndex]+"  "+years[year_t.currentIndex]
                                        popup.close()
//enter_login.focus = true
                                    }
                                }
                            }
                            onPressedChanged: {

                                popup.open()

                               // Qt.inputMethod.hide()
                            }
                        }
                        Row {
                            id: row1
                            width: parent.width
                            height: row_name.height
                            spacing: 50
                            RadioButton {
                                id: radioButton
                                indicator.height: 25
                                indicator.width: 25
                                Text {
                                    id: male
                                    x: 37
                                    y: 12
                                    text: qsTr("  Male")
                                    color: "white"
                                }
                            }

                            RadioButton {
                                id: radioButton1
                                indicator.height: 25
                                indicator.width: 25
                                Text {
                                    id: female
                                    x: 35
                                    y: 12
                                    text: qsTr(" Female")
                                    color: "white"
                                }
                            }
                        }
                        Row{
                            width: parent.width
                            height: (column.height-9*column.spacing)/9
                            Rectangle{
                                id:rec_login
                                width: repass_text.width+10
                                height: parent.height
                            color: "transparent"
                            Text {
                                id: login_text
                                text: qsTr("Login")
                                anchors.bottom: parent.bottom
                                color: "white"
                            }
                            }
                        TextInput{
                            id:enter_login
                            width: parent.width-rec_repass.width
                            height: 20
                            color: "white"
                            anchors.bottom: parent.bottom
                            Rectangle {
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onAccepted:   { enter_password.focus = true}
                            EnterKey.type:  Qt.EnterKeyNext
                        }
                        }
                        Row{
                            width: parent.width
                           height: (column.height-9*column.spacing)/9
                            Rectangle{
                                id:rec_pass
                                width: repass_text.width+10
                                height: parent.height
                            color: "transparent"
                            Text {
                                id: pass_text
                                text: qsTr("Password")
                                anchors.bottom: parent.bottom
                                color: "white"
                            }
                            }
                        TextInput{
                            id:enter_password
                            width: parent.width-rec_repass.width
                            height: 20
                            color: "white"
                            echoMode: TextInput.Password
                            anchors.bottom: parent.bottom
                            Rectangle {
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onAccepted:  { repeat_password.focus = true}
                            EnterKey.type:  Qt.EnterKeyNext
                        }
                        }
                        Row{
                            width: parent.width
                            height: (column.height-9*column.spacing)/9
                            Rectangle{
                                id:rec_repass
                                width: repass_text.width+10
                                height: parent.height
                            color: "transparent"
                            Text {
                                id: repass_text
                                text: qsTr("Repeat password")
                                anchors.bottom: parent.bottom
                                color: "white"
                            }
                            }
                        TextInput{
                            id:repeat_password
                            width: parent.width-rec_repass.width
                            height: 20
                            color: "white"
                            echoMode: TextInput.Password
                            anchors.bottom: parent.bottom
                            Rectangle {
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                        }
                        }
                        Button{
                            id: sign_in
                            anchors.bottomMargin: 30
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 180
                            text: "Submit"
                            anchors.horizontalCenterOffset: 0
                            //enabled: username.text === "" || surname.text === "" || mail.text === "" || u_pass.text === "" || repass.text === ""  ?false:true
                            background: Rectangle{
                                radius: 30
                                color: "lightgreen"
                                opacity: 0.75
                            }
                        }
                    }
                }
            }
        }
    }
}
