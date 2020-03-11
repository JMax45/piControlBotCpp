std::string getTokenFromUser(){
    std::cout << "\nBot token is required: ";
    std::string botToken;
    std::cin >> botToken;
    saveBotToken(botToken);
    return botToken;
}

std::string getBotToken(std::string fileLocation){
    std::ifstream file(fileLocation);
    std::string botToken;
    file >> botToken;
    file.close();
    if(botToken == "false"){
        botToken = getTokenFromUser();
        return botToken;
    }
    else{
        return botToken;
    }    
}

int getHour(){
    const std::time_t now = std::time(nullptr) ; 
    const std::tm calendar_time = *std::localtime( std::addressof(now) ) ;
    return calendar_time.tm_hour;
}

std::string getAdminId(std::string fileLocation){
    std::ifstream file(fileLocation);
    std::string adminId;
    file >> adminId;
    file.close();
    return adminId;
}

std::string getTime(){
    using namespace date;
    using namespace std::chrono;

    std::time_t t = std::chrono::system_clock::to_time_t(system_clock::now());
    std::string ts = std::ctime(&t);
    ts.resize(ts.size()-1);

    return ts;
}