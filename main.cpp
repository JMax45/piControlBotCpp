#include <stdio.h>
#include <tgbot/tgbot.h>
#include <iostream>
#include <vector>
#include "include/piInternal.h"
#include "include/checkBot.h"
#include "include/saveBot.h"
#include "include/getBot.h"
#include "include/reportBot.h"
#include "include/onLaunch.h"
#include "src/Responses.cpp"

int main() {
    int piHour = getHour();
    int runningTime = 0;
    std::string adminId = getAdminId("data/adminId.txt");
    TgBot::Bot bot(getBotToken("data/botToken.txt"));
    Responses botResponses;

    onLaunchServerOnline(adminId, bot);

    bot.getEvents().onCommand("start", [&bot, &botResponses](TgBot::Message::Ptr message) {
        botResponses.Start(bot, message);
    });
    bot.getEvents().onCommand("temperature", [&bot, &botResponses](TgBot::Message::Ptr message) {
        botResponses.Temperature(bot, message);
    });
    bot.getEvents().onCommand("ip", [&bot, &botResponses](TgBot::Message::Ptr message) {
        botResponses.Ip(bot, message);
    });
    bot.getEvents().onCommand("restart", [&bot,&adminId, &botResponses](TgBot::Message::Ptr message) {
        botResponses.Restart(bot, message, adminId);
    });
    bot.getEvents().onCommand("shutdown", [&bot,&adminId, &botResponses](TgBot::Message::Ptr message) {
        botResponses.Shutdown(bot, message, adminId);
    });
    bot.getEvents().onCommand("speedtest", [&bot, &botResponses](TgBot::Message::Ptr message) {
        botResponses.Speedtest(bot, message);
    });
    bot.getEvents().onCommand("upgrade", [&bot, &botResponses](TgBot::Message::Ptr message) {
        botResponses.Upgrade(bot, message);
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
