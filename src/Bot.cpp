#include "../include/Bot.h"

Bot::Bot(){

}	

TgBot::Bot Bot::create_tgbot(){
	TgBot::Bot tgbot(getBotToken("data/botToken.txt"));
	return tgbot;
}