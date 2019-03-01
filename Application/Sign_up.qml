import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
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

        PropertyAnimation{
            id:bbbb
            property: "y"
            target: go_top
            //from: 0
            to:0
            duration: 200
        }
        PropertyAnimation{
            id:dddd
            property: "y"
            target: go_top
            //from: 0
            to: -90
            duration: 200
        }
        PropertyAnimation{
            id:kkkk
            property: "y"
            target: go_top
            //from: 0
            to: -150
            duration: 200
        }
        PropertyAnimation{
            id:ssss
            property: "y"
            target: go_top
            //from: 0
            to: -180
            duration: 200
        }
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
                        bbbb.start()

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

                        width: 300
                        height: Screen.height -2*column.y
                        parent: go_top
                        spacing: 20

                        anchors.horizontalCenter: parent.horizontalCenter

                        TextField{
                            id:username
                            enabled: true

                            width: 300
                            height: (column.height-9*column.spacing)/9
                            color: "white"
                            placeholderText: "Name"
                            background: Rectangle{
                                color: "transparent"
                            }
                            Rectangle {
                                id:us
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onEditingFinished:  { us.height = 1; us.color = "white"}
                            onPressed:   {
                                us.height = 2
                                us.color = "darkgrey"
                                bbbb.start()

                            }

                        }

                        TextField{
                            id:surname

                            width: 300
                            height: username.height
                            color: "white"
                            placeholderText: "Surname"
                            background: Rectangle{
                                color: "transparent"
                            }
                            Rectangle {
                                id:sur
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onEditingFinished:  { sur.height = 1; sur.color = "white"}
                            onPressed:   { sur.height = 2 ;
                                sur.color = "darkgrey"
                                bbbb.start()
                            }

                        }
                        TextField{
                            id:email
                            height: username.height
                            width: 300
                            color: "white"
                            placeholderText: "Email"
                            background: Rectangle{
                                color: "transparent"
                            }
                            Rectangle {
                                id:mail
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onEditingFinished:  { mail.height = 1; mail.color = "white"}
                            onPressed:   { mail.height = 2 ; mail.color = "darkgrey";dddd.start()}

                        }


                        ComboBox {
                            id: comboBox


                            width: parent.width
                            height: username.height
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
                                height: 6*username.height
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
                                        slaq.text   /*comboBox.displayText*/ =days[day_t.currentIndex]+"  "+ month[month_t.currentIndex]+"  "+years[year_t.currentIndex]
                                            popup.close()

                                        }

                                    }
                                     }



                            onPressedChanged: {
                                bbbb.start()

                                popup.open()

                            }
                        }

                        Row {
                            id: row1

                            width: 300
                            height: username.height
                            spacing: 50
                            RadioButton {
                                id: radioButton

                                indicator.height: 25
                                    indicator.width: 25
                                onClicked:      {
                                    bbbb.start()
                                }
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


                                onClicked:  {
                                    bbbb.start()
                                }
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
                        TextField{
                            id:login
                            enabled: true

                            width: 300
                            height: username.height
                            color: "white"
                            placeholderText: "Login"
                            background: Rectangle{
                                color: "transparent"
                            }
                            Rectangle {
                                id:log
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onEditingFinished:  { us.height = 1; us.color = "white"}
                            onPressed:   {
                                us.height = 2
                                us.color = "darkgrey"
                               kkkk.start()

                            }

                        }
                        TextField{
                            id:user_password
                            height: username.height
                            width: 300
                            color: "white"
                            placeholderText: "Password"
                            background: Rectangle{
                                color: "transparent"
                            }
                            Rectangle {
                                id:u_pass

                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onEditingFinished:  { u_pass.height = 1; u_pass.color = "white"}
                            onPressed:   { u_pass.height = 2 ; u_pass.color = "green";kkkk.start()}
                            echoMode: TextInput.Password
                        }
                        TextField{
                            id:repeat_pass
                            height: username.height
                            width: 300
                            color: "white"
                            placeholderText: "Repeat password"
                            background: Rectangle{
                                color: "transparent"
                            }
                            Rectangle {
                                id:repass

                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onEditingFinished:  { repass.height = 1; repass.color = "white"}
                            onPressed:   { repass.height = 2 ; repass.color = "green";ssss.start()}
                            echoMode: TextInput.Password
                        }
                        Button{

                            id: sign_in
                            anchors.bottomMargin: 30
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 180

                            text: "Submit"
                            anchors.horizontalCenterOffset: 0
                            enabled: username.text === "" || surname.text === "" || mail.text === "" || u_pass.text === "" || repass.text === ""  ?false:true

                            background: Rectangle{
                                radius: 30
                                color: "lightgreen"
                                opacity: 0.75

                            }
                            onPressed: {bbbb.start()}

                        }

                    }
                }
            }
        }

    }
}
