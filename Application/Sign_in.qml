import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.3
//import io.qt.examples.Engine 1.0
Page{
    id: wind
    focus: true

    Rectangle{
        width: wind.width
        height: wind.height
        color: "transparent"
        PropertyAnimation{
            id:fbo1
            property: "opacity"
            target: button
            from: 1
            to: 0
            duration: 500
        }
        PropertyAnimation{
            id:fbh1
            property: "height"
            target: button
            //from: 0
            to: 0
            duration: 500
        }
        PropertyAnimation{
            id:fbw1
            property: "width"
            target: button
            //from: 0
            to: 0
            duration: 500
        }
        PropertyAnimation{
            id:fby1
            property: "y"
            target: button
            from: column.y+column.height
            to: button.y
            duration: 500
        }
        PropertyAnimation{
            id:fbx1
            property: "x"
            target: button
            from:column.x+60
            to: button.x
            duration: 500
        }
        PropertyAnimation{
            id:go1
            property: "opacity"
            target: button1
            from: 1
            to: 0
            duration: 500
        }
        PropertyAnimation{
            id:gh1
            property: "height"
            target: button1
           // from:  0
            to: 0
            duration: 500
        }
        PropertyAnimation{
            id:gw1
            property: "width"
            target: button1
            //from: 0
            to: 0
            duration: 500
        }
        PropertyAnimation{
            id:gy1
            property: "y"
            target: button1
            from: column.y+column.height
            to: button1.y
            duration: 500
        }
        PropertyAnimation{
            id:gx1
            property: "x"
            target: button1
            from:column.x+column.width/2-25
            to: button1.x
            duration: 500
        }
        PropertyAnimation{
            id:instao1
            property: "opacity"
            target: button2
            from: 1
            to: 0
            duration: 500
        }
        PropertyAnimation{
            id:instah1
            property: "height"
            target: button2
           // from: 0
            to: 0
            duration: 500
        }
        PropertyAnimation{
            id:instaw1
            property: "width"
            target: button2
          //  from: 0
            to: 0
            duration: 500
        }
        PropertyAnimation{
            id:instay1
            property: "y"
            target: button2
            from: column.y+column.height
            to: button2.y
            duration: 500
        }
        PropertyAnimation{
            id:instax1
            property: "x"
            target: button2
            from:column.x+column.width-110
            to: button2.x
            duration: 500
        }

        PropertyAnimation{
            id:fbo
            property: "opacity"
            target: button
            from: 0
            to: 1
            duration: 500
        }
        PropertyAnimation{
            id:fbh
            property: "height"
            target: button
            from: 0
            to: 50
            duration: 500
        }
        PropertyAnimation{
            id:fbw
            property: "width"
            target: button
            from: 0
            to: 50
            duration: 500
        }
        PropertyAnimation{
            id:fby
            property: "y"
            target: button
            from: button.y
            to: column.y+column.height
            duration: 500
        }
        PropertyAnimation{
            id:fbx
            property: "x"
            target: button
            from:button.x
            to: column.x+60
            duration: 500
        }
        PropertyAnimation{
            id:go
            property: "opacity"
            target: button1
            from: 0
            to: 1
            duration: 500
        }
        PropertyAnimation{
            id:gh
            property: "height"
            target: button1
            from:  0
            to: 50
            duration: 500
        }
        PropertyAnimation{
            id:gw
            property: "width"
            target: button1
            from: 0
            to: 50
            duration: 500
        }
        PropertyAnimation{
            id:gy
            property: "y"
            target: button1
            from: button1.y
            to: column.y+column.height
            duration: 500
        }
        PropertyAnimation{
            id:gx
            property: "x"
            target: button1
            from:button1.x
            to: column.x+column.width/2-25
            duration: 500
        }
        PropertyAnimation{
            id:instao
            property: "opacity"
            target: button2
            from: 0
            to: 1
            duration: 500
        }
        PropertyAnimation{
            id:instah
            property: "height"
            target: button2
            from: 0
            to: 50
            duration: 500
        }
        PropertyAnimation{
            id:instaw
            property: "width"
            target: button2
            from: 0
            to: 50
            duration: 500
        }
        PropertyAnimation{
            id:instay
            property: "y"
            target: button2
            //from: button2.y
            to: column.y+column.height
            duration: 500
        }
        PropertyAnimation{
            id:instax
            property: "x"
            target: button2
            from:button2.x
            to: column.x+column.width-110
            duration: 500
        }
        BorderImage {
            id: name
            source: "qrc:/51062817_2189626127969158_7173693744896540672_n.png"
         anchors.fill: parent
        }
        MouseArea{
            id:mouse
            width: parent.width
            height: parent.height
            onPressed: {
                Qt.inputMethod.hide()
            }
            Column{               
                id: column
                width: 300
                height: 362
                anchors.verticalCenterOffset: 0
                anchors.horizontalCenterOffset: 0
                anchors.centerIn: parent
                spacing: 30
                TextField{
                    id:login
                    width: 300
                    color: "white"
                    placeholderText: "Login"
                    background: Rectangle{
                        color: "transparent"
                    }
                    Rectangle {
                        id:log_rect
                        color: "white"
                        height: 1
                        width: parent.width
                        anchors.bottom: parent.bottom
                    }
                    onEditingFinished:  { log_rect.height = 1; log_rect.color = "white"}
                    onPressed:   { log_rect.height = 2 ; log_rect.color = "green"}
                }
                Rectangle{
                    width: 300
                    height: password.height
                    color: "transparent"
                    Rectangle {
                        id:passw_rect
                        color: "white"
                        height: 1
                        width: parent.width
                        anchors.bottom: parent.bottom
                    }
                    Button{
                    id:see_pass
                    width: parent.heighth
                    height: parent.height
                    background: Rectangle{
                    color: "transparent"
                    }
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    icon.source: "qrc:/glaz1.png"
                    icon.color: "white"
                    onClicked: {
                    password.echoMode === TextInput.Password?(password.echoMode =TextInput.Normal ) :(password.echoMode = TextInput.Password)
                    icon.source == "qrc:/glaz1.png"? icon.source= "qrc:/glaz.png": icon.source= "qrc:/glaz1.png"

                    }
                    }
                TextField{
                    id:password
                    width: 300-see_pass.width
                    color: "white"
                    placeholderText: "Password"
                    passwordCharacter: "*"
                    background: Rectangle{
                        color: "transparent"
                    }


                    onEditingFinished:  { passw_rect.height = 1; passw_rect.color = "white"}
                    onPressed:   { passw_rect.height = 2 ; passw_rect.color = "green"}
                    echoMode: TextInput.Password
                }

                }
                Button{
                    anchors.horizontalCenter: parent.horizontalCenter
                    id: sign_in
                    width: 180
                    text: "Sign in"
                    background: Rectangle{
                        radius: 30
                        color: "#e6e6e6"
                        opacity: 0.75
                    }
                    enabled: login.text == "" || password.text == "" ?false:true
                    onClicked: Class.sign_inn("sdrysdydfy")
                }
                Button{
                    background: Rectangle{
                        radius: 30
                        color: "lightgrey"
                        opacity: 0.75
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                    id:sign_up
                    width: 180
                    text: "Sign up"                    
                    onPressed: stack.push(Qt.resolvedUrl("Sign_up.qml"))
                }
                Button{
                    anchors.horizontalCenter: parent.horizontalCenter
                    id:forgot_password
                    font.family: "Arial"
                    width: forg_pass.width
                    height: forg_pass.height
                    Text {
                        id:forg_pass
                        text: "Forgot password?"
                        anchors.centerIn:  parent
                        color: "white"
                    }
                    background:Rectangle {
                        color: "transparent"
                    }
                    onPressed: stack.push(Qt.resolvedUrl("Forgot_Password.qml"))
                }
                Button{
                    anchors.horizontalCenter: parent.horizontalCenter
                    id: sign_up_with
                    width: s_with.width
                    height: s_with.height
                    checkable: true
                    Text {
                        id:s_with
                        text: qsTr("Sign up with")
                        color: "white"
                        anchors.centerIn: parent
                    }
                    background:Rectangle {
                        color: "transparent"
                    }
                    onPressed:  {
                        if( button.height == 0){
                            fbx.start()
                            fby.start()
                            fbo.start()
                            fbw.start()
                            fbh.start()
                            gx.start()
                            gy.start()
                            go.start()
                            gw.start()
                            gh.start()
                            instax.start()
                            instay.start()
                            instao.start()
                            instaw.start()
                            instah.start()
                        }
                        else{
                            fbx1.start()
                            fby1.start()
                            fbo1.start()
                            fbw1.start()
                            fbh1.start()
                            gx1.start()
                            gy1.start()
                            go1.start()
                            gw1.start()
                            gh1.start()
                            instax1.start()
                            instay1.start()
                            instao1.start()
                            instaw1.start()
                            instah1.start()
                        }
                    }
                }
            }
            Button {
                id: button                
                x: column.x+50
                y: column.y+column.height
                width: 0
                height:0
                background: Rectangle{                   
                    color:"transparent"
                }
                BorderImage {
                    id: fb1
                    source: "qrc:/5ab8bcb464f2c(1).png"
                    width: parent.width
                    height: parent.height
                }
            }
            Button {
                id: button1               
                x: column.x+column.width/2-25
                y: column.y+column.height
                width: 0
                height: 0
                background: Rectangle{                  
                    color:"transparent"
                }
                BorderImage {
                    id: fb3
                    width: parent.width
                    height: parent.height
                    source: "qrc:/5ab8bcb464f2c(3).png"
                }
            }
            Button {
                id: button2               
                x: column.x+column.width-100
                y: column.y+column.height
                width: 0
                height: 0
                background: Rectangle{                   
                    color:"transparent"
                }
                BorderImage {
                    id: fb2
                    width: parent.width
                    height: parent.height
                    source: "qrc:/5ab8bcb464f2c(2).png"
                }
            }
        }
    }
}
