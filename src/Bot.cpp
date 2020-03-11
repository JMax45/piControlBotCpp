#include "../include/Bot.h"

Bot::Bot(){
	adminId = getAdminId("data/adminId.txt");
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