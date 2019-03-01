API
ip=192.168.1.12

Account Service

signUp {
        request {
                uri - uri/account/registration
                body - {
                                "firstName" : "Valod",
                                "lastName" : "Valodyan",
                                "gender" : "male",
                                "email" : "v.valodyan@mail.com",
                                "birthDate" : "12.12.1990",
				"login" : "v.valodyan",
                                "password" : "Valodik90"
		}
        }

        response {
//              if OK 
                        "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                        "userId" : "u1",
                        "firstName" : "Valod",
                        "lastName" : "Valodyan",
                        "gender" : "male",
                        "email" : "v.valodyan@mail.com",
                        "birthDate" : "12.12.1990",
			"login" : "v.valodyan"
//		else 
                        "mailStatus" : "inValid",
                        "loginStatus" : "inValid"
        }
}

signIn {
        request {
                uri - uri/account/signIn
                body -  {
                                "login" : "v.valodyan",
                                "password" : "Valodik90"
                        }
        }

        response {
//              if OK 
                        "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                        "userId" : "u1",
                        "firstName" : "Valod",
                        "lastName" : "Valodyan",
                        "gender" : "male",
                        "email" : "v.valodyan@msil.com",
                        "birthDate" : "12.12.1990"
//              else 
//                      if (login - in valid)
                        	"status" : "Login or Password is Wrong!!!"
//                      if (login - isvalid && count < max_attempt-1)
                                "status" : "Login or Password is Wrong!!!"
//                      if (login - isvalid && count = max_attempt-1)
                                "status" : "Attention!!! You have one attempt left!!!"
//                      if (login - isvalid && count >= max_attempt)
                                "status" : "Attempt failed!!!"
                }
        }
}

forgotPassword {
        request {
                uri - uri/account/forgotPassword
                body -  {
                                "email" : "v.valodyan@mail.com"
                        }
                }

        response {
//              if OK
			"status" : "you have a code message in mail. Please, input code"
//              else
                        "status" : "invalid mail"
        }
}

checkingCode {
        request {
                uri - uri/account/checkingCode
                body - {
                        "code" : 123456,
                        "mail" : "v.valodyan@mail.com"
                }
        }
        response {
//              if OK
                        "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                        "userId" : "u1",
//              else
                        "status" : "invalid code"
        }
}

newPassword {
	request {
		uri - uri/account/newPassword
		body - {
			"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"password" : "valod1990"
		}
	}
	resonpse {
//		if OK 
			"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                        "userId" : "u1",
                        "firstName" : "Valod",
                        "lastName" : "Valodyan",
                        "gender" : "male",
                        "email" : "v.valodyan@msil.com",
                        "birthDate" : "12.12.1990"
//		else 
			"status" : "invalid password"
	}
}

signOut {
        request {
                uri - uri/account/signOut?clientId=u123
                header - token
        }

        response{
//              if OK
			"status" : "OK"
        }
}

getUserInfo {
        request {
                uri - uri/account/getUserInfo?clientId=u123
                header - token
        }
        response {
//              if OK
                        "firstName" : "Valod",
                        "lastName" : "Valodyan",
			"avatar" : "base64_string",
                        "login" : "v.valodyan",
                        "gender" : "male",
                        "email" : "v.valodyan@mail.com",
                        "birthDate" : "12.12.1990"
        }
}

getUserShortInfo {
        request {
                uri - uri/account/getUserShortInfo?clientId=u85&userId=u438
                header - token
        }
        response {
//              if OK
                        "firstName" : "Heriqnaz",
                        "lastName" : "Heriqyan",
			"avatar" : "base64_string",
			"gender" : "male",
			"birthdate" : "12.12.1993" 
//              else
                        "status" : "invalidId"
}

updateUserInfo {
	requset {
		uri - uri/account/updateUserInfo?clientId=u123
		body - {
                        "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"firstName" : "Valod",
			"lastname" : "Valodyan",
			"avatar" : "base64_string",
			"" : ""
			
		}

	response {
//              if OK
                        "firstName" : "Valod",
                        "lastName" : "Valodyan",
			"avatar" : "base64_string",
//              else 
                        "status" : ""
	}
}

deleteUser {
        request {
                uri - uri/user/deleteUser?clientId=u123
                header - token
        }

        response {
                "status" : "deleted"
        }
}

createGroup {
    request {
        uri - uri/group/createGroup
        body - {
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                "groupName" : "Best",
                "adminID" : "u123",
                "access" : "private"
        }
    }

    response {
        "status" : "created",
        "groupID" : "g212"
    }
}

deleteGroup {
    request {
        uri - uri/path/deleteGroup
        body - {
		"adminId" : "u542",
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                "groupID" : "g123"
        }
    }

    response {
        "status" : "deleted"
    }
}

getGroupInfo {
        request {
                uri - uri/path/getGroupInfo?clientId=u325&groupId=u12
                header - token
        }

        response {
//              if OK 
                        "name" : "ChkaMerNmany",
                        "adminID" : "u10",
                        "usersquantity" : "13",
                        "avatar" : "base64_string",
                        "createDate" : "13.12.2018"
//              else 
                        "status" : "this is a private group"
        }

}

updateGroupInfo {
    request {
            uri - uri/path/updateGroupInfo?adimId=u231
            body - {
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                "groupID" : "g123",
                "name" : "MafiaForever",
                "adminID" : "u10",
                "avatar" : "base64_string",
            }
    }

    response {
	"groupID" : "g123",
        "name" : "MafiaForever",
        "adminID" : "u10",
        "avatar" : "base64_string"
    }
}

getGroupUsers {
    request {
        uri - uri/path/getGroupUsers?groupId=g51&clientId=u25
        header - token
    }

    response {
//	for public group
        "id" : ["u1", "u12", "u18"]
//	for privat group
	"status" : ""
    }
}

removeFromGroup {
    request {
        uri - uri/path/removeFromGroup
        body - {
		"groupId" : "g156",
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                "adminID" : "u12",
                "id" : "u23" // who will be removed
        }
    }

    response {
//          if OK 
                "status" : "removed"
//          else 
                "status" : ""
    }
}

//////////////////////////////////////////////
Messaging Service

getUserConversations {
        request {
        	uri - uri/user/getUserConversations?clientId=u123
                header - token
	}

        response {
//		if OK
		{ 
       		 	"id" : "u12",
        		"firstName" : "Valod",
        		"lastName" : "Valodyan",
        		"lastMessage" : "barev",
			"avatar" : "base64_string"
		}
       		{
			"id" : "u23",
        		"firstName" : "Heriq",
        		"lastName" : "Heriqyan",
        		"lastMessage" : "hajox",
			"avatar" : "base64_string"
		}
//		else 
        		"status" : "Conversations not found"
}

getUserConversation {
        request {
  		uri - uri/user/getUserConversations
        	body - {
			"clientId" : "u123",
			"uId" : "u21",
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		}
        }

        response {
//		if OK		
		{
			"id" : "u21",
			"messageID" : "m12",
			"date" : "19.12.2018",
			"message" : "hazar barev"
		}
		{
			"id" : "u123",
			"messageID" : "m110",
			"date" : "18.01.2019",
			"message" : "erkuhazar barev"
		}
//		else
        		"status" : "conversation not found"
}

addUserMessage {
        request {
        	uri - uri/user/addUserMessage
                body - {
			"uid" : "u21",
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"id" : "u321",
                	"message" : "Hi!!!"
		}

        response {
		"status" : "added"
        }
}

updateUserMessage{
        request {
       		uri - uri/user/updateUserMessage
                body - {
			"clientId" : "u751",
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"id" : "u321",
                	"messageId" : "m12",
               	 	"newMessage" : "Hello!"
		}
	}

        response {
//		if OK 
			"status" : "updated"
//		else 
			"status" : "this is not the last message"
        }
}

removeUserConversation {
        request {
        	uri - uri/user/removeUserConversation
                body - {
			"clientId" : "u22",
			"id" : "u123",
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f"
		}
        }

        response {
		"status" : "removed"
        }
}

removeMessageFromUserConversation {
        request {
        	uri - uri/path/removeMessage
                body - {
			"clientId" : "u21",
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"id" : "u12",
                	"messageID" : "m123",
                	"mode" : "0/1"
        }

        response {
		"status" : "0/1/2"
        }
}

getGroupConversation {
	request {
		uri - uri/path/getGroupConversation
			body - {
				"uid" : "u123",
				"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
				"groupID" : "g15"
			}
	}

	response {
		messageID : "m12",
	 // 	status : "0/1",
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

updateGroupMessage {
    request {
    	uri - uri/path/updateGroupMessage
        body - {
		"groupId" : "g52",
		"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
        	"messageID" : "m10",
       		"id" : "u1",
		"message" : "lav lav"
	}
    }

    response {
        "status" : "0/1"
    }
}

addGroupMessage {
    request {
	uri - uri/path/addGroupMessage
	body - {
		"groupId" : "g54",
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"id" : "u12",
        	"message" : "vobshm"
	}
    }

    response {
    	"status" : "0"
    }
}

addUserToGroup {
    request {
	    uri - uri/path/addUserGroup
	    body - {
		    "groupId" : "g254",
                    "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		    "adminId" : "u1",
		    "id" : "u2"
	    }
    }

    response {
//	    if OK 
   		"status" : "added"
//	    else 
   }
}

removeGroupConversation {
    request {
    	uri - uri/path/removeGroupConversation
        body - {
		"groupId" : "g23",
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"adminId" : "u22"
	}
    }

    response {
    	"status" : "0/1"
    }
}

removeMessageFromGroupConversation {
        request {
        	uri - uri/path/removeMessage
                body - {
			"uid" : "u15",
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"groupID" : "u12",
                	"messageID" : "m23",
                	"mode" : "0/1"
		}
        }

        response {
		"status" : "0/1"
        }
}
