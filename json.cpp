API

"http://host_auto_ip4:6505/v1/mafclub/api"

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
			"nickname" : "Valod",
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
			"nickname" : "Valod", 
			"avatar" : "base64_string",
                        "gender" : "male",
                        "email" : "v.valodyan@msil.com",
                        "birthDate" : "12.12.1990"
//              else 
//                      if (login - invalid || login - isvalid && attemptsCount < max_attempt-1)
                        	"status" : "Login or Password is Wrong!!!"
//                      if (login - isvalid && attemptsCount = max_attempt-1)
                                "status" : "Attention!!! You have one attempt left!!!"
//                      if (login - isvalid && attemptsCount >= max_attempt)
                                "status" : "Last attempt failed!!!"
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
			"status" : "you have a code message in mail. Please, input code here"
//              else
                        "status" : "invalid mail"
        }
}

checkingCode {
        request {
                uri - uri/account/checkingCode
                body - {
                        "code" : 123456,
                        "email" : "v.valodyan@mail.com"
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
			"userId" : "u1",
			"password" : "valod1990"
		}
	}
	resonpse {
//		if OK 
			"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                        "userId" : "u1",
                        "firstName" : "Valod",
                        "lastName" : "Valodyan",
			"nickname" : "Valod",
			"avatar" : "base64_string",
                        "gender" : "male",
                        "email" : "v.valodyan@msil.com",
                        "birthDate" : "12.12.1990"
//		else 
			"status" : "invalid password"
	}
}

signOut {
        request {
                uri - uri/account/signOut?userId=u123
                header - token
        }

        response{
		"status" : "OK"
        }
}

getUserInfo {
        request {
                uri - uri/account/getUserInfo?userId=u123
                header - token
        }
        response {
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"userID" : "u123"
		"firstName" : "Valod",
                "lastName" : "Valodyan",
		"nickname" : "Valod",
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
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
	             	"userID" : "u438" 
                        "firstName" : "Heriqnaz",
                        "lastName" : "Heriqyan",
			"nickname" : "Heriq",
			"avatar" : "base64_string",
			"gender" : "female",
			"birthdate" : "12.12.1993" 
//              else
                        "status" : "invalid id"
}

updateUserInfo {
	requset {
		uri - uri/account/updateUserInfo?userId=u123
		body - {
                        "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"firstName" : "Valod",
			"lastname" : "Valodyan",
			"avatar" : "base64_string",
			"nickname" : "Valod"  // can be changed only once
		}

	response {
//              if OK
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                        "firstName" : "Valod",
                        "lastName" : "Valodyan",
			"avatar" : "base64_string",
			"nickname" : "Valod"
//              else 
                        "status" : "this field cannot be changed"
	}
}

deleteUser {
        request {
                uri - uri/user/deleteUser?userId=u123
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
        "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
        "groupID" : "g212",
        "groupName" : "Best",
        "adminID" : "u123",
        "access" : "private"
    }
}

deleteGroup {
    request {
        uri - uri/path/deleteGroup
        body - {
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"adminId" : "u542",
                "groupID" : "g123"
        }
    }

    response {
//	if OK	   
        	"status" : "deleted"
//	else 
		"status" : "only admin can delete group"
    }
}

getGroupInfo {
        request {
                uri - uri/path/getGroupInfo?userId=u325&groupId=u12
                header - token
        }

        response {
//              if OK 
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"groupName" : "ChkaMerNmany",
                        "adminID" : "u10",
                        "usersQuantity" : "13",
                        "avatar" : "base64_string",
                        "createDate" : "13.12.2018"
//              else (if the client is not a member of the group && this is a private group) 
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
                "avatar" : "base64_string"
            }
    }

    response {
//	if OK	    
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"groupID" : "g123",
        	"name" : "MafiaForever",
        	"adminID" : "u10",
        	"avatar" : "base64_string"
//	else
		"status" : "only admin can update group info"
    }
}

getGroupUsers {
    request {
        uri - uri/path/getGroupUsers?groupId=g51&userId=u25
        header - token
    }

    response {
//	if OK 
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
        	"id" : ["u1", "u12", "u18"]
//      else (if the client is not a member of the group & this is a private group) 
		"status" : "this is a private group"
    }
}

removeFromGroup {
    request {
        uri - uri/path/removeFromGroup
        body - {
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"groupId" : "g156",
                "adminID" : "u12",
                "userId" : "u23" // who will be removed
        }
    }

    response {
//          if OK 
                "status" : "removed"
//          else 
                "status" : "only admin can delete member of the group"
    }
}


getUserConversations {
        request {
        	uri - uri/user/getUserConversations?userId=u123
                header - token
	}

        response {
//		if OK
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f"
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
  		uri - uri/user/getUserConversation
        	body - {
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"userId" : "u123",
			"uId" : "u21"
		}
        }

        response {
//		if OK		
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
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

getGroupConversation {
	request {
		uri - uri/path/getGroupConversation
		body - {
			"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"userId" : "u123",
			"groupID" : "g15"
		}
	}

	response {
//	if OK
		"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		{
			"messageID" : "m12",
	 		"id" : "u1",
	  		"date" : "19.12.2018",
	  		"message" : "Hazar barev"
		}
		{
	  		"messageID" : "m11",
	  		"id" : "u3",
	  		"date" : "19.12.2018",
	 	 	"message" : "vonc eq?"
		}
		{
	  		"messageID" : "m12",
	  		"id" : "u4",
	  		"date" : "19.12.2018",
	  		"message" : "lav enq!"
		}
//	else 
		"status" : "You are not a member of this group"		
	}
}

*****************************************************************************

Messaging Service

userSendMessage {
        request {
        	uri - uri/user/addUserMessage
                body - {
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"userid" : "u21",
			"uid" : "u321",
                	"message" : "Hi!!!"
		}

        response {
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"status" : "added"
        }
}

updateUserMessage{
        request {
       		uri - uri/user/updateUserMessage
                body - {
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"userId" : "u751",
			"uid" : "u321",
                	"messageId" : "m12",
               	 	"newMessage" : "Hello!"
		}
	}

        response {
//		if OK 
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"status" : "updated"
//		else 
			"status" : "this is not the last message"
        }
}

removeUserConversation {
        request {
        	uri - uri/user/removeUserConversation?userId=u52&uId=u23
               	header - token
        }

        response {
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"status" : "removed"
        }
}

removeUserMessage {
        request {
        	uri - uri/path/removeMessage
                body - {
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"userId" : "u21",
			"uid" : "u12",
                	"messageID" : "m123",
                	"mode" : 0   // if ("mod" : 0) {delete the message} else if ("mod" : 1) {delete the message everywhere}
        }

        response {
//		if OK 
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"status" : "removed"
//		else 
			"status" : "???"
        }
}

updateGroupMessage {
    request {
    	uri - uri/path/updateGroupMessage
        body - {
		"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"groupId" : "g52",
        	"messageID" : "m10",
       		"id" : "u1",
		"newMessage" : "lav lav"
	}
    }

    response {
//	if OK
		"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"status" : "updated"
//	else
		"status" : "this is not the last message"
    }
}

sendGroupMessage {
    request {
	uri - uri/path/addGroupMessage
	body - {
                "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
		"groupId" : "g54",
		"id" : "u12",
        	"message" : "vobshm"
	}
    }

    response {
    	"status" : "added"
    }
}

removeGroupConversation {
    request {
    	uri - uri/path/removeGroupConversation?adminId=u256&groupId=g32
        header - token
    }

    response {
	    "token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
	    "status" : "removed"
    }
}

removeGroupMessage {
        request {
        	uri - uri/path/removeMessage
                body - {
                	"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"userId" : "u15",
			"groupID" : "u12",
                	"messageID" : "m23",
                	"mode" : "1"
		}
        }

        response {
		"status" : "removed"
        }
}

*************************************************************************

Search Service

searchUser {
	request {
		uri - uri/path/searchUser?userId=u21&firstname=Valod&lastname=Valodyan
		header - token
	}

	response {
//		if OK
			"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
			"id" : "u195",
			"firstname" : "Valod",
			"lastname" : "Valodyan",
			"nickname" : "Valod",
			"avatar" : "base64_string",
			"gender" : "male",
                	"birthdate" : "12.12.1990"
//		else
			"status" : "User with such name not found"
	}
}

searchGroup {
	request {
		uri - uri/path/sarchGroup/userId=u249&groupName=Best
		header - token
	}

	response {
//		if OK
			"token" : "adhd4fv4sdg5343vbxf4h5nbx15bdx6f",
                	"groupName" : "Best",
                	"adminID" : "u10",
                	"usersQuantity" : "13",
                	"avatar" : "base64_string",
                	"createDate" : "13.12.2018"
//		else 
			"status" : "Group with such name not found"
	}
}

***************************************************************************

Notification Service

userJoinGroup {
	request {
		uri - uri/path/userJoinGroup?userId=u32&groupId=g31
		header - token
	}

	response {
//	if Ok 
		"status" : "Your request is sent"
//	else
		"status" : "Group not found" || "Group is full"		
	}
}

groupAcceptUser {
	request {
		uri - uri/path/groupAcceptUser?groupId=g31&userId=u32
		header - token
	}

	response {
//	if OK
		"status" : "Your request is accepted"
//	else 
		"status" : "Internal error"
	}
} 

groupInviteUser {
	request {
		uri - uri/path/groupInviteUser?groupId=g365&userId=u751
		header - token
	}

	response {
		"status" : "Your request is sent"
	}
}

userAcceptInvitation {
	request {
		uri - uri/path/userAcceptInvitation?userId=u751&groupId=g365
		header - token
	}

	response {
//	if OK 
		"status" : "user accepts your request"
//	else
		"status" : "user does not accept your request"
	}
}

*******************************************************************************

Gaming Service

