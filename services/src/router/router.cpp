#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <network_utils.hpp>

#include <router/router.hpp>

Action Router::actionFromString(std::string actionName) {
    if(actionName == "signUp") {
        return Registration;
    } else if(actionName == "signIn") {
        return SignIn;
    } else if(actionName == "forgotPassword") {
        return ForgotPassword;
    } else {
        return UnknownAction;
    }
}

ServiceType Router::serviceTypeFromString(std::string serviceName) {

    if(serviceName == "account") {
        return AccountService;
    } else if(serviceName == "messaging") {
        return MessagingService;
    } else if(serviceName == "search") {
        return SearchService;
    } else if(serviceName == "game") {
        return GameService;
    } else if(serviceName == "notification") {
        return NotificationsService;
    } else {
        return UnknownService;
    }
}

http_client* Router::serviceClient(ServiceType type) {
    http_client *serviceClient = NULL;
    switch (type)
    {
        case AccountService : 
            {
                serviceClient = AccountClient;
                break;
            }
        case MessagingService : 
            {
                serviceClient = ConversationClient;
                break;
            }
        case GameService : 
            {
                serviceClient = GameClient;
                break;
            }
        case SearchService : 
            {
                serviceClient = SearchClient;
                break;
            }
        case NotificationsService : 
            {
                serviceClient = NotificationClient;
                break;
            }
        case UnknownService : 
            {
                serviceClient = NULL;
                break;
            }
        default:
            { 
                serviceClient = NULL;
                break;
            }
    }
    return serviceClient;
}

bool Router::createClients(std::string path)
{
    std::ifstream ConfigFile(path);
    json::value config;
    if (ConfigFile.is_open()) {
        ConfigFile>> config;
        ConfigFile.close();
        AccountClient = new http_client(NetworkUtils::hostURI(config.at("account").as_string()));
        ConversationClient = new http_client(NetworkUtils::hostURI(config.at("messaging").as_string()));
        GameClient = new http_client(NetworkUtils::hostURI(config.at("game").as_string()));
        NotificationClient = new http_client(NetworkUtils::hostURI(config.at("notification").as_string()));
        SearchClient = new http_client(NetworkUtils::hostURI(config.at("search").as_string()));
        TokenDbClient = new http_client(NetworkUtils::hostURI(config.at("tokendbservice").as_string()));
        this->routerUri = config.at("router").as_string();
        return true;
    }
    else {
        std::cerr << "ConfigFile is not exist!!!" << std::endl;
        return false;
    }
}

bool ServiceStart (http_client* client, std::string serviceName) {
    uri_builder builder(U("/ServiceTest/"));
    std::error_code error;

    int count = 0;
    int exequtionCount = 0;
    const int maxExequtionCount = 10;
    const int maxCount = 60;
    do{
        if(count == maxCount)
        {
            //avelacnel exequtor funkciayi kanch(vor@ petq e start ani servicner@)
            if(exequtionCount >= maxExequtionCount)
            {
                std::cout<<serviceName<<" service is dead!!!"<<std::endl;
                return false;
            }
            ++exequtionCount;
            count = 0;
        }
        usleep(100000);
        error.clear();
        try {
            count++;
            pplx::task<http_response> requestTask = client->request(methods::GET, builder.to_string());
            requestTask.then([=](http_response resp){
                    std::cout<<resp.to_string()<<std::endl;
                    });
            requestTask.wait();
        } catch (http_exception e) {
            error = e.error_code();
            std::cerr<<e.what()<<std::endl;
        }
    }
    while (error.value());
    return true;
}

bool Router::checkServices()
{
    bool status = false;
    bool accServStatus = false;
    bool convServStatus = false;
    bool gameServStatus = false;
    bool notifServStatus = false;
    bool searchServStatus = false;
    bool tokDbServStatus = false;
    accServStatus = ServiceStart(AccountClient, "Account");
    /*	qani der patrast chen bolor MikroServicener@ toxnel vorpes comment

        if(accServStatus){
        convServStatus = ServiceStart(ConversationClient, "Messaging");}
        if(convServStatus){
        gameServStatus = ServiceStart(GameClient, "Game");}
        if(gameServStatus){
        notifServStatus = ServiceStart(NotificationClient, "Notification");}
        if(notifServStatus){
        searchServStatus = ServiceStart(SearchClient, "Search");}
        if(searchServStatus){
        tokDbServStatus = ServiceStart(TokenDbClient, "TokenDB");}
        if (tokDbServStatus)
        {
        this->setEndpoint(routerUri);
        status = true;
        }
        return status;
     */
    if (accServStatus){
        		tokDbServStatus = ServiceStart(TokenDbClient, "TokenDB");}
        	if (tokDbServStatus){
        this->setEndpoint(routerUri);}
return tokDbServStatus;
}

Router::Router(std::string path)
{
    this->createClients(path);
}

Router::~Router()
{
	delete[] TokenDbClient;
	delete[] AccountClient;
	delete[] GameClient;
	delete[] ConversationClient;
	delete[] NotificationClient;
	delete[] SearchClient;
}

void Router::initRestOpHandlers(){
    _listener.support(methods::GET, std::bind(&Router::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Router::handlePost, this, std::placeholders::_1));
}

std::string extractToken(http_request message){
    if(message.headers().has("token")){
        return message.headers()["token"];
    }
    return "";
}

std::string extractID (http_request message){
    if(message.method() == web::http::methods::POST) {
        json::value info = message.extract_json().get();
        json::value id = info.at("userId");
	message.set_body(info);
	if(! id.is_null()) {
            return id.as_string();
        }
    } else {
        std::map<utility::string_t, utility::string_t>  query = uri::split_query(message.request_uri().query());
        std::map<utility::string_t, utility::string_t>::iterator it = query.find( "userId" );
        if( it != query.end()){
            return it->second;
        }
    }
    return "";
}

bool isAuthorizedAction (Action action) {
    return (action != SignIn) && (action != Registration) && (action != ForgotPassword);
}

bool checkToken (std::string id, std::string token, http_client* tokenService) {
    json::value tokenInfo;
    tokenInfo["userId"] = json::value::string(id);
    tokenInfo["token"] = json::value::string(token);
    uri_builder checkToken_path(U("/checkToken"));
    http_response tokenStatus = tokenService->request(methods::POST, checkToken_path.to_string(), tokenInfo).get();
    json::value tokenJson  = tokenStatus.extract_json().get();
    if(tokenJson.at("status").as_string() != "OK")
    { 
        return false;
    }
    return true;
}

RequestStatus validateRequest  (http_request request, std::vector<std::string> urlPath, http_client* tokenService, bool authorized = true)
{
    std::string id = extractID(request);
    std::string token = extractToken(request);
    if("" == token) {
        return RequestStatusTokenMissing;
    } 
    if ("" == id) {
        return RequestStatusUserIDMissing;
    }
    if (authorized && !checkToken(id, token, tokenService)) {
        return RequestStatusUnauthorized;
    }
    if (urlPath.empty() || urlPath.size() < 2) {
        return RequestStatusInvalidPath;
    }
    return RequestStatusValid;
}

void replyToInvalidRequest(RequestStatus status, http_request request) {
    std::string status_string = "";
    int status_code = status_codes::NotImplemented;
    switch (status) {
        case RequestStatusInvalidPath: 
        {
            status_string = "NOT_FOUND";
            status_code = status_codes::NotFound;
            break;
        }
        case RequestStatusUserIDMissing: 
        {
            status_string = "USER_ID_IS_MISSING";
            status_code = status_codes::Unauthorized;
            break;
        }
        case RequestStatusTokenMissing: 
        {
            status_string = "TOKEN_IS_MISSING";
            status_code = status_codes::Unauthorized;
            break;
        }
        case RequestStatusUnauthorized: 
        {
            status_string = "WRONG_TOKEN_ID_PAIR";
            status_code = status_codes::Unauthorized;
            break;
        }
        case RequestStatusInvalidData: 
        {
            status_string = "INVALID_DATA";
            status_code = status_codes::BadRequest;
            break;
        case RequestStatusUnknown: 
        {
            status_string = "INTERNAL_ERROR";
            status_code = status_codes::InternalError;
            break;
        }
        }
        default: 
        {
            status_string = "NOT_IMPLEMENTED";
            status_code = status_codes::NotImplemented;
            break;
        }
    }
    http_response resp;
    resp.set_status_code(status_code);
    json::value info;
    info["status"] = json::value::string(status_string);
    resp.set_body(info);
    request.reply(resp);
}
static int requestCount = 0;
void Router::handleGet(http_request message) {
	++requestCount;
	std::cout<<"Request N  "<<requestCount<<std::endl;
	//std::cout<<message.to_string()<<std::endl;
    auto urlPath  = requestPath(message);
    RequestStatus status = validateRequest(message, urlPath, TokenDbClient, true);
    if(status != RequestStatusValid) return replyToInvalidRequest(status, message);

    std::string action = urlPath[1];
    std::string serviceName = urlPath[0];

    ServiceType servType = serviceTypeFromString(serviceName);
    http_client *service = serviceClient(servType);//??????????????????

    service->request(message).then([message](http_response response){
            message.reply(response);
            });
}

void Router::handlePost(http_request message) {
//	std::cout<<message.to_string()<<std::endl;
    auto urlPath  = requestPath(message);
    //TODO add path validation before using it
    std::string actionName = urlPath[1];
    Action action = actionFromString(actionName);
    bool authorized = isAuthorizedAction(action);
    RequestStatus status;
	if(authorized)
	{
    		status = validateRequest(message, urlPath, TokenDbClient, authorized);
	}
	else
	{
		status = RequestStatusValid;
	}
    if(status != RequestStatusValid)
    { 
	    return replyToInvalidRequest(status, message);
    }

    std::string serviceName = urlPath[0];
    ServiceType servType = serviceTypeFromString(serviceName);
    http_client *service = serviceClient(servType);
    service->request(message).then([message](http_response response){
            message.reply(response);
            });
}
