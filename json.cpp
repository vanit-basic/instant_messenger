API
ip=192.168.1.12

Account Service

signUp{
        request{
                uri - uri/account/registration
                body - {
                                firstName : "Valod",
                                lastName : "Valodyan",
                                login : "v.valodyan",
                                password : "Valodik90",
                                gender : "male",
                                email : "v.valodyan@mail.com",
                                birthDate : "12.12.1990"
		}
        }

        response{
                if OK {
                        token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                        userId : "u1",
                        firstName : "Valod",
                        lastName : "Valodyan",
                        gender : "male",
                        email : "v.valodyan@msil.com",
                        birthDate : "12.12.1990"
                } else {
                        mailStatus : "inValid",
                        loginStatus : "inValid"
                }
        }
}

signIn{
        request{
                uri - uri/account/signIn
                body -  {
                                login : "v.valodyan",
                                password : "Valodik90"
                        }
        }

        response{
                if OK
                {
                        token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                        userId : "u1",
                        firstName : "Valod",
                        lastName : "Valodyan",
                        gender : "male",
                        email : "v.valodyan@msil.com",
                        birthDate : "12.12.1990"
                }
                else
                {
                        if (login - in valid)
                        {
                                "Login or Password is Wrong!!!"
                        }
                        if (login - isvalid && count < max_attempt-1)
                        {
                                "Login or Password is Wrong!!!"
                        }
                        if (login - isvalid && count = max_attempt-1)
                        {
                                "Attention!!! You have one attempt left!!!"
  }
                        if (login - isvalid && count >= max_attempt)
                        {
                                "Attempt failed!!!"
                        }
                }
        }
}

forgotPassword{
        request{
                uri - uri/account/forgotPassword
                body -  {
                                email : "v.valodyan@mail.com"
                        }
                }

        response{
                if OK
                {
                        "you have a code message in mail. Please, input code"
                }
                else
                {
                        "invalid mail"
                }
        }
}

checkingCode{
        request{
                uri - uri/account/checkingCode
                body - {
                        code : 123456,
                        mail : "v.valodyan@mail.com"
                }
        }
        response{
                if OK
                {
                        token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                        userId : "u1",
                        firstName : "Valod",
                        lastName : "Valodyan",
                        gender : "male",
                        email : "v.valodyan@msil.com",
                        birthDate : "12.12.1990"
                }
                else
                {
                        "invalid code"
                }
        }
}

newPassword {
	request {
		uri - uri/account/newPassword
		body - {
			password : "valod1990",
			email : "v.valodyan@msil.com"
		}
	}
	resonpse {
		if OK 
		{
			token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                        userId : "u1",
                        firstName : "Valod",
                        lastName : "Valodyan",
                        gender : "male",
                        email : "v.valodyan@msil.com",
                        birthDate : "12.12.1990"
		}
		else 
		{
			status : "invalid email or password"
		}
	}
}

signOut{
        request{
                uri - uri/account/signOut?clientId=u123
                header - token
        }

        response{
                if OK
                {
                        status = "OK"
                }
                else
                {
                        status = "?????"
                }
        }
}

getUserInfo{
        request{
                uri - uri/account/getUserInfo?clientId=u123
                header - token
        }
        response{
                if OK
                {
                        firstName : "Valod",
                        lastName : "Valodyan",
			avatar : "base64_string",
                        login : "v.valodyan",
                        gender : "male",
                        email : "v.valodyan@mail.com",
                        birthDate : "12.12.1990"
                }
        }
}

getUserShortInfo {
        request {
                uri - uri/account/getUserShortInfo?clientId=u85&userId=u438
                header - token
        }
        response {
                if OK
                {
                        firstName : "Valod",
                        lastName : "Valodyan",
			avatar : "base64_string",
                        gender : "male",
                        email : "v.valodyan@mail.com",
                        birthDate : "12.12.1990"
                }
                else
                {
                        status : "invalidId"
                }
}

updateUserInfo {
	requset {
		uri - uri/account/updateUserInfo/id
		body - {
                        token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			firstName : "Valod",
			lastname : "Valodyan"'
			gender : "male",
			birthdate : "12.12.1990",
			avatar : "base64_string"
		}

	response {
                if OK
                {
			id : "u12"
                        firstName : "Valod",
                        lastName : "Valodyan",
                        avatar : "base64_string",
                        gender : "male",
                        birthDate : "12.12.1990"
			avatar : "base64_string"
                } else {
                        status : "0/1/2"
                }
	}
}

getUserConversations {
        request {
        	uri - uri/user/getUserConversations/id
                header - token
	}

        response {
		if OK {
       		 	id : "u12",
        		firstName : "Valod",
        		lastName : "Valodyan",
        		lastMessage : "barev",
			avatar : "base64_string",
       
			id : "u23",
        		firstName : "Heriq",
        		lastName : "Heriqyan",
        		lastMessage : "hajox",
			avatar : "base64_string"
	} else {
        	status : "0/1/2"
	}
}

getUserConversation {
        request {
  		uri - uri/user/getUserConversations/id
        	body - {
                	token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			id : "u12"
		}
        }

        response {
		id : "u21",
		messageID : "m12"
		date : "19.12.2018",
		message : "hazar barev"

		id : "u2",
       		messageID : "m110",
		date : "18.01.2019",
		message : "erkuhazar barev"'
       		//quantity -> 20
        }
        	status : "0/1"
}

deleteUser {
        request {
        	uri - uri/user/deleteUser/id
		header - token
        }
        
	response {
                status : "0"
        }
}

addUserMessage {
        request {
        	uri - uri/user/addUserMessage/id
                body - {
                	token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			id : "u321",
                	message : "Hi!!!"
		}
        }

        response {
		status : "0"
        }
}

updateUserMessage{
        request {
       		uri - uri/user/updateUserMessage/id
                body - {
                	token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			id : "u321",
                	messageId : "m12",
               	 	newMessage : "Hello!"
		}
	}

        response {
		status : "0/1"
        }
}

removeUserConversation {
        request {
        	uri - uri/user/removeUserConversation/id
                body - {
			id : "u123"
                	token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		}
        }

        response {
		status : "0/1"
        }
}

removeMessageFromUserConversation {
        request {
        	uri - uri/path/removeMessage/id
                body - {
                	token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			id : "u12",
                	messageID : "m123",
                	mode : "0/1"
        }

        response {
		status : "0/1/2"
        }
}

removeMessageFromUserConversation {
        request {
        	uri - uri/path/removeMessage/id
                body - {
                	token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			id : "u12",
                	messageID : "m22",
              		mode : "0/1"
		}
        }
        response {
		status : "0/1/2"
        }
}

###########################################################################################################################################

createGroup {
    request {
    	uri - uri/group/createGroup
    	body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		groupName : "Best",
    		adminID : "u123",
    		access : "private"
	}
    }

    response {
        status : "0",
        groupID : "g212"
    }
}

deleteGroup {
    request {
	uri - uri/path/deleteGroup/uId
	body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		groupID : "g123",
	}
    }

    response {
    	status : "0"
    }
}

getGroupInfo {
    request {
    	uri - uri/path/getGroupInfo/uId
	body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		groupID : "g123"
	}
    }

    response {
    	status : "0/1",
   	name : "ChkaMerNmany",
   	adminID : "u10",
   	usersquantity : "13",
	avatar : "base64_string",
   	createDate : "13.12.2018"
    }
}

getGroupConversation {
    request {
    	uri - uri/path/getGroupConversation/uId
   	body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		groupID : "g15"
	}
   }
   
    response {
	messageID : "m12",
        status : "0/1",
        id : "u1",
	date : "19.12.2018",
	message : "Hazar barev",

      	messageID : "m11",
       	id : "u3",
	date : "19.12.2018",
	message : "vonc eq?",

      	messageID : "m12",
       	id : "u1",
	date : "19.12.2018",
	message : "lav enq!",
    }
}

updateGroupInfo {
    request {
	    uri - uri/path/updateGroupInfo/uId
	    body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		groupID : "g123",
     		name : "MafiaForever",
   		adminID : "u10",
   		usersquantity : "13",
		avatar : "base64_string",
		createDate : "13.12.2018"
	    }
    }

    response {
	status : "0",
    	name : "MafiaForever",
    	adminID : "u10",
    	usersquantity : "13",
	avatar : "base64_string",
    	createDate : "13.12.2018"
    }
}

updateGroupMessage {
    request {
    	uri - uri/path/updateGroupMessage/gId
        body - {
		token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
        	messageID : "m10",
       		id : "u1",
		message : "lav lav"
	}
    }

    response {
        status : "0/1"
    }
}

addGroupMessage {
    request {
	uri - uri/path/addGroupMessage/gId
	body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		id : "u12",
        	message : "vobshm"
	}
    }

    response {
    	status : "0"
    }
}

addUserToGroup {
    request {
	    uri - uri/path/addUserGroup/gId
	    body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		id : "u1",
		id : "u2"
	    }
    }

    response {
   	status : "0/1"
   }
}

removeGroupConversation {
    request {
    	uri - uri/path/removeGroupConversation/gId
        body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		adminID : "u22"
	}
    }

    response {
    	status : "0/1"
    }
}

getGroupUsers {
    request {
    	uri - uri/path/getGroupUsers/gId
        body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		groupID : "12"
	}
    }

    response {
    	status : "0",
     	id : "u1",
	id : "u2",
	.........
	id : "u(n)"
    }
}

removeFromGroup {
    request {
    	uri - uri/path/removeFromGroup/gId
    	body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		adminID : "u12",
    		id : "u23" // who will be removed
	}
    }

    response {
    	status : "0/1"
    }
}

removeMessageFromGroupConversation {
        request {
        	uri - uri/path/removeMessage/id
                body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			groupID : "u12",
                	messageID : "m23",
                	mode : "0/1"
		}
        }

        response {
		status : "0/1"
        }
}
