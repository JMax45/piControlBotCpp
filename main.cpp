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
#include "src/Bot.cpp"

int main() {
    //This class contains all the things related to the bot
    Bot bot;

    int piHour = getHour();
    int runningTime = 0;
    std::string adminId = getAdminId("data/adminId.txt");

    onLaunchServerOnline(adminId, bot.tgbot);

    bot.tgbot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Start(bot.tgbot, message);
    });
    bot.tgbot.getEvents().onCommand("temperature", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Temperature(bot.tgbot, message);
    });
    bot.tgbot.getEvents().onCommand("ip", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Ip(bot.tgbot, message);
    });
    bot.tgbot.getEvents().onCommand("restart", [&adminId, &bot](TgBot::Message::Ptr message) {
        bot.responses.Restart(bot.tgbot, message, adminId);
    });
    bot.tgbot.getEvents().onCommand("shutdown", [&adminId, &bot](TgBot::Message::Ptr message) {
        bot.responses.Shutdown(bot.tgbot, message, adminId);
    });
    bot.tgbot.getEvents().onCommand("speedtest", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Speedtest(bot.tgbot, message);
    });
    bot.tgbot.getEvents().onCommand("upgrade", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Upgrade(bot.tgbot, message);
    });

    bot.tgbot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
    });
    try {
        printf("Bot username: %s\n", bot.tgbot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot.tgbot);
        while (true) {
            if(getHour()!=piHour){
		piHour = getHour();
				runningTime++;
                bot.tgbot.getApi().sendMessage(std::stoi(adminId), hourReport(runningTime));
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
