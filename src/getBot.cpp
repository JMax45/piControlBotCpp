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

std::string getAdminId(){
    std::ifstream file("doc/adminId.txt");
    std::string adminId;
    file >> adminId;
    file.close();
    return adminId;
}