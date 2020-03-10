#include "../include/Bot.h"

Bot::Bot(){
	adminId = getAdminId("data/adminId.txt");
}	

TgBot::Bot Bot::create_tgbot(){
	TgBot::Bot tgbot(getBotToken("data/botToken.txt"));
	return tgbot;
}