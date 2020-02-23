#include <stdio.h>
#include <tgbot/tgbot.h>
#include <iostream>
#include <vector>
#include "include/piInternal.h"
#include "include/checkBot.h"
#include "include/getBot.h"
#include "include/reportBot.h"

int main() {
    int piHour = getHour();
    int runningTime = 0;
    std::string adminId = getAdminId();
    TgBot::Bot bot(getBotToken("doc/botToken.txt"));
    bot.getApi().sendMessage(std::stoi(adminId), "The server is online");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, std::to_string(message->chat->id));
    });
    bot.getEvents().onCommand("temperature", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, getPiTemperature());
    });
    bot.getEvents().onCommand("ip", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, getPiIp());
    });
    bot.getEvents().onCommand("restart", [&bot,&adminId](TgBot::Message::Ptr message) {
	if(checkAdmin(adminId, std::to_string(message->chat->id))){
	    bot.getApi().sendMessage(message->chat->id, "The server will restart");
	    std::string command = "sudo touch systemReboot.txt";
            system(command.c_str());
	}
	else{
	    bot.getApi().sendMessage(message->chat->id, "Only the administrator can execute this command");
	}
    });
    bot.getEvents().onCommand("shutdown", [&bot,&adminId](TgBot::Message::Ptr message) {
        if(checkAdmin(adminId, std::to_string(message->chat->id))){
            bot.getApi().sendMessage(message->chat->id, "The server will shutdown");
            std::string command = "sudo touch systemShutdown.txt";
            system(command.c_str());
        }
        else{
            bot.getApi().sendMessage(message->chat->id, "Only the administrator can execute this command");
        }
    });
    bot.getEvents().onCommand("speedtest", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Testing network speed...");
        bot.getApi().sendMessage(message->chat->id, piSpeedTest());
    });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            if(getHour()!=piHour){
		piHour = getHour();
				runningTime++;
                bot.getApi().sendMessage(std::stoi(adminId), hourReport(runningTime));
	    }
	    checkReboot();
	    checkShutdown();
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}
