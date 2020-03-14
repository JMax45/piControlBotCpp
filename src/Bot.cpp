#include "../include/Bot.h"

Bot::Bot(){
	adminId = getAdminId("data/adminId.txt");
	upTime = 0;
	time = getHour();
	serverOnline();
}	

TgBot::Bot Bot::create_tgbot(){
	TgBot::Bot tgbot(getBotToken("data/botToken.txt"));
	return tgbot;
}

void Bot::log(std::string message){
	std::ofstream file("data/logs.txt", std::ios::app);
	file << "\n" << "[" << getTime() << "] " << message;
	file.close();
}

void Bot::serverOnline(){
	/*
    Check if the admin id is registered, if not, send a message to the terminal.
    Otherwise send a telegram message to the admin.
    */
	if(adminId == "false"){
    	std::cout << "\nType /start to save the admin id\n";
    }
    else{
    	tgbot.getApi().sendMessage(std::stoi(adminId), "The server is online");
    }
}