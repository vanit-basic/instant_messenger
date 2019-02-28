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
                        email : "v.valodyan@mail.com",
                        birthDate : "12.12.1990",
			login : "v.valodyan"
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
			email : "v.valodyan@mail.com"
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
               /* else
                {
                        status = "?????"
                }*/
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
                        firstName : "Heriqnaz",
                        lastName : "Heriqyan",
			avatar : "base64_string",
                        gender : "female",
                        email : "heriqnaz@mail.com",
                        birthDate : "12.12.1995"
                }
                else
                {
                        status : "invalidId"
                }
}

updateUserInfo {
	requset {
		uri - uri/account/updateUserInfo?clientId=u123
		body - {
                        token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			firstName : "Valod",
			lastname : "Valodyan"'
			avatar : "base64_string"
		}

	response {
                if OK
                {
                        firstName : "Valod",
                        lastName : "Valodyan",
                        avatar : "base64_string",
			avatar : "base64_string"
                } else {
                        status : "0/1/2"
                }
	}
}

getUserConversations {
        request {
        	uri - uri/user/getUserConversations?clientId=u123
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
        		status : "Conversations not found"
		}
}

getUserConversation {
        request {
  		uri - uri/user/getUserConversations?clientId=u123&userId=u21
        	body - {
                	token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		}
        }

        response {
		id : "u21",
		messageID : "m12"
		date : "19.12.2018",
		message : "hazar barev"

		id : "u123",
       		messageID : "m110",
		date : "18.01.2019",
		message : "erkuhazar barev"'
        }
        	status : "conversation not found"
}

deleteUser {
        request {
        	uri - uri/user/deleteUser?clientId=u123
		header - token
        }
        
	response {
                status : "deleted"
        }
}

addUserMessage {
        request {
        	uri - uri/user/addUserMessage?clientId=u566
                body - {
                	token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			id : "u321",
                	message : "Hi!!!"
		}
        }

        response {
		status : "added"
        }
}

updateUserMessage{
        request {
       		uri - uri/user/updateUserMessage?clinetId=u751
                body - {
                	token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			id : "u321",
                	messageId : "m12",
               	 	newMessage : "Hello!"
		}
	}

        response {
		if OK {
			status : "updated"
		}
		else {
			status : "this is not the last message"
		}
        }
}
///////
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
        status : "created",
        groupID : "g212"
    }
}

deleteGroup {
    request {
	uri - uri/path/deleteGroup?adminId=u542
	body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		groupID : "g123",
	}
    }

    response {
    	status : "deleted"
    }
}

getGroupInfo {
	request {
		uri - uri/path/getGroupInfo?clientId=u325&groupId=u12
		header - token
	}

	response {
		if OK {
			name : "ChkaMerNmany",
			adminID : "u10",
     			usersquantity : "13",
			avatar : "base64_string",
			createDate : "13.12.2018"
		}
		else {
			status : "this is a private group"
		}
	}
}
///////
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
///////
updateGroupInfo {
    request {
	    uri - uri/path/updateGroupInfo?adimId=u231
	    body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		groupID : "g123",
     		name : "MafiaForever",
   		adminID : "u10",
   	//	usersquantity : "13",
		avatar : "base64_string",
	    }
    }

    response {
	status : "0",
    	name : "MafiaForever",
    	adminID : "u10",
    //	usersquantity : "13",
	avatar : "base64_string",
    }
}
///////
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
	    uri - uri/path/addUserGroup/groupId=g54
	    body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		uid : "u1",
		id : "u2"
	    }
    }

    response {
	    if OK {
   		status : "added"
	    }
	    else {

	    }
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
    	uri - uri/path/getGroupUsers?groupId=g51&clientId=u25
        header - token 
    }

    response {
     	id : ["u1", "u12", "u18"]
    }
}

removeFromGroup {
    request {
    	uri - uri/path/removeFromGroup?groupId=g60
    	body - {
                token : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		adminID : "u12",
    		id : "u23" // who will be removed
	}
    }

    response {
	    if OK {
    		status : "removed"
	    }
	    else {
		status : ""
	    }
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
