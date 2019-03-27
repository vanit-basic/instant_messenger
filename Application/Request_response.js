.pragma library
function Account (){

    this.signUp = function (firstName, lastName, gender, email, birthDate, login, password) {
        var request = new XMLHttpRequest()
        request.open('POST', 'http://127.0.1.1:6504/v1/mafclub/api/account/signUp')
        request.setRequestHeader('Content-Type', 'application/json')
        var params = {
            "firstName" : firstName,
            "lastName" : lastName,
            "gender" : gender,
            "email" : email,
            "birthDate" : birthDate,
            "login" : login,
            "password" : password
        }
        var data = JSON.stringify(params)
        request.setRequestHeader('Content-Length', data.length)
        request.send(data)
        request.onreadystatechange = function() {

            if (request.readyState === XMLHttpRequest.DONE) {
                console.log(request.status)
                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)

                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }

    this.signIn = function (login, password) {
        var request = new XMLHttpRequest()
        request.open('POST', 'http://127.0.1.1:6504/v1/mafclub/api/account/signIn')
        request.setRequestHeader('Content-Type', 'application/json')
        var params = {

            "login" : login,
            "password" : password

        }
        var data = JSON.stringify(params)
        request.setRequestHeader('Content-Length', data.length)
        request.send(data)

        request.onreadystatechange = function() {

            if (request.readyState === XMLHttpRequest.DONE) {

                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)
                    console.log(result.userId)

                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }

    this.signOut=function (userId, token) {
        var request = new XMLHttpRequest()
        var params = 'http://127.0.1.1:6504/v1/mafclub/api/account/signOut?userId='+userId
        request.open('GET',params )
        request.setRequestHeader('token', token)
        request.send()
        request.onreadystatechange = function() {

            if (request.readyState === XMLHttpRequest.DONE) {

                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)

                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }

    this.getUserInfo = function (userId, token) {
        var request = new XMLHttpRequest()
        var params = 'http://127.0.1.1:6504/v1/mafclub/api/account/getUserInfo?userId='+userId
        request.open('GET',params )
        request.setRequestHeader('token', token)
        request.send()
        request.onreadystatechange = function() {

            if (request.readyState === XMLHttpRequest.DONE) {

                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)

                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }


    this.getUserShortInfo = function (userId,clientId, token) {
        var request = new XMLHttpRequest()
        var params = 'http://127.0.1.1:6504/v1/mafclub/api/account/getUserShortInfo?userId='+userId+'&clientId='+clientId
        request.open('GET',params )
        request.setRequestHeader('token', token)
        request.send()
        request.onreadystatechange = function() {

            if (request.readyState === XMLHttpRequest.DONE) {

                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)

                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }

    this.userUpdateInfo = function (token,userId,firstName, lastName, avatar, nickname) {
        var request = new XMLHttpRequest()
        var url = 'http://127.0.1.1:6504/v1/mafclub/api/account/updateUserInfo'
        request.open('POST', url)
        request.setRequestHeader('token', token)
        var params = {
            "userId" : userId,
            "firstName" : firstName,
            "lastname" : lastName,
            "avatar" : avatar,
            "nickname" : nickname
        }
        var data = JSON.stringify(params)
        request.setRequestHeader('Content-Length', data.length)
        request.send(data)
        request.onreadystatechange = function() {

            if (request.readyState === XMLHttpRequest.DONE) {
                console.log(request.status)
                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)

                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }

    this.changePassword = function (token, userId, password, newPassword) {
        var request = new XMLHttpRequest()
        request.open('POST', 'http://127.0.1.1:6504/v1/mafclub/api/account/changePassword')
        request.setRequestHeader('token', token)
        var params = {
            "userId" : userId,
            "password" : password,
            "newPassword" : newPassword
        }
        var data = JSON.stringify(params)
        request.setRequestHeader('Content-Length', data.length)
        request.send(data)
        request.onreadystatechange = function() {

            if (request.readyState === XMLHttpRequest.DONE) {
                console.log(request.status)
                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)

                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }

    this.groupCreate = function (token,groupName,userId,access) {
        var request = new XMLHttpRequest()


        request.open('POST','http://127.0.1.1:6504/v1/mafclub/api/account/createGroup')

        request.setRequestHeader('token', token)
        var params = {
            "groupName" : groupName,
            "userId" : userId,
            "access" : access

        }
        var data = JSON.stringify(params)
        request.setRequestHeader('Content-Length', data.length)
        request.send(data)
        request.onreadystatechange = function() {
            if (request.readyState === XMLHttpRequest.DONE) {
                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)
                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }
    this.groupDelete = function (userId,token) {
        var request = new XMLHttpRequest()
        var params = 'http://127.0.1.1:6504/v1/mafclub/api/account/deleteGroup?userId=u542&groupId='+userId

        request.open('GET',params )
        request.setRequestHeader('token', token)
        request.send()
        request.onreadystatechange = function() {
            if (request.readyState === XMLHttpRequest.DONE) {
                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)
                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }
    this.getGroupInfo = function (userId,groupId,token) {
        var request = new XMLHttpRequest()
        var params = 'http://127.0.1.1:6504/v1/mafclub/api/account/getGroupInfo?userId='+userId+'&groupId='+groupId

        request.open('GET',params )
        request.setRequestHeader('token', token)
        request.send()
        request.onreadystatechange = function() {
            if (request.readyState === XMLHttpRequest.DONE) {
                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)
                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }
    this.getGroupShortInfo = function (userId,groupId,token) {
        var request = new XMLHttpRequest()
        var params = 'http://127.0.1.1:6504/v1/mafclub/api/account/getGroupInfo?userId='+userId+'&groupId='+groupId

        request.open('GET',params )
        request.setRequestHeader('token', token)
        request.send()
        request.onreadystatechange = function() {
            if (request.readyState === XMLHttpRequest.DONE) {
                if (request.status && request.status === 200) {
                    console.log("response", request.responseText)
                    var result = JSON.parse(request.responseText)
                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        return request.responseText
    }
    this.groupUpdateInfo = function (groupId,userId,name,avatar) {
        var request = new XMLHttpRequest()
        request.open('GET', 'http://127.0.1.1:6504/v1/mafclub/api/account/updateGroupInfo')
        request.setRequestHeader('Content-Type', 'application/json')
        var params = {
            "groupId" : groupId,
            "userId" : userId,
            "name" : name,
            "avatar" : avatar
        }
        var data = JSON.stringify(params)
        request.setRequestHeader('Content-Length', data.length)
        request.send(data)
        request.onreadystatechange = function() {

            if (request.readyState === XMLHttpRequest.DONE) {
                console.log(request.status,"ccccccccc")
                if (request.status && request.status === 200) {
                    console.log("response", request.responseText,"  aaaaaaaaa")
                    var result = JSON.parse(request.responseText)

                } else {
                    console.log("HTTP:", request.status, request.statusText,"bbbbbbbbbbb")
                }
            }
        }
        return request.responseText
    }
    this.groupRemoveUser = function (groupId,userId,clientId) {
        var request = new XMLHttpRequest()
        request.open('GET', 'http://127.0.1.1:6504/v1/mafclub/api/account/removeFromGroup')
        request.setRequestHeader('Content-Type', 'application/json')
        var params = {
            "groupId" : groupId,
            "userId" : userId,
            "clientId" : clientId
        }
        var data = JSON.stringify(params)
        request.setRequestHeader('Content-Length', data.length)
        request.send(data)
        request.onreadystatechange = function() {

            if (request.readyState === XMLHttpRequest.DONE) {
                console.log(request.status,"ccccccccc")
                if (request.status && request.status === 200) {
                    console.log("response", request.responseText,"  aaaaaaaaa")
                    var result = JSON.parse(request.responseText)

                } else {
                    console.log("HTTP:", request.status, request.statusText,"bbbbbbbbbbb")
                }
            }
        }
        return request.responseText
    }
}
