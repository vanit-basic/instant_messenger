.pragma library

function DbManager(dbObject){
    this.db = dbObject;

    this.addUserIntoRecent = function(){

    }

    this.setUserInfo = function(info){
        var data = JSON.parse(info)
        this.db.transaction(
                 function(tx) {
                     tx.executeSql('CREATE TABLE IF NOT EXISTS user(userId TEXT UNIQUE ON CONFLICT REPLACE,firstName TEXT,lastName TEXT,birthDate TEXT, gender TEXT,email TEXT,nickName TEXT,avatar TEXT,level TEXT,playedGames INT,redCard INT,blackCard INT,sheriff INT,don INT,wins INT,fails INT,killed INT)'  );
                     tx.executeSql('INSERT INTO user (userId,firstName,lastName,birthDate,gender,email,nickName,avatar,level,playedGames,redCard,blackCard,sheriff,don,wins,fails,killed) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)',
                                   [ data.userId, data.firstName, data.lastName, data.birthDate, data.gender, data.email, data.nickName, data.avatar, data.level, data.playedGames, data.redCard, data.blackCard, data.sheriff, data.don, data.wins, data.fails, data.killed, ]);
                 }
                 )
    }

    this.updateUserInfo = function(info){

    }

    this.getUserInfoForHome = function(userId){
        var result
        this.db.transaction(
                 function(tx) {
                     var data = tx.executeSql('Select firstName,lastName,level,avatar from user where userId = ?',userId);
                     result = {firstName:data.firstName, lastName:data.lastName, level:data.level, avatar:data.avatar}
                     result = JSON.stringify(result)
                 }
                 )
        return result
    }

    this.getUserInfoForEditProfile = function(userId){
        var result
        this.db.transaction(
                 function(tx) {
                     var data = tx.executeSql('Select firstName,lastName,nickName,avatar from user where userId = ?',userId);
                     console.log(data.firstName,data.avatar)
                     result = {firstName:data.firstName, lastName:data.lastName, nickName:data.nickName, avatar:data.avatar}
                     result = JSON.stringify(result)
                 }
                 )
        return result
    }

    this.addUserIntoRecent = function(id){

    }

    this.setGroupInfo = function(info){
        var data = JSON.parse(info)
        this.db.transaction(
                 function(tx) {
                     tx.executeSql('CREATE TABLE IF NOT EXISTS groupa(groupId TEXT UNIQUE ON CONFLICT REPLACE,groupName TEXT,adminId TEXT,createDate INT,access TEXT,avatar TEXT)');
                     tx.executeSql('INSERT INTO groupa (groupId,groupName,adminId,createDate,access,avatar) VALUES(?,?,?,?,?,?)',
                                   [ data.groupId, data.groupName, data.adminId, data.createDate, data.access, data.avatar]);
                 }
                 )
    }

    this.getGroupInfo = function(groupId){
        var result
        this.db.transaction(
                 function(tx) {
                     var data = tx.executeSql('Select * from groupa where groupId = ?',groupId);
                     result = {groupId:data.groupId, groupName:data.groupName, adminId:data.adminId, createDate:data.createDate, access:data.access, avatar:data.avatar}
                     result = JSON.stringify(result)
                 }
                 )
        return result
    }












}
