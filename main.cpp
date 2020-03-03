#include <stdio.h>
#include <tgbot/tgbot.h>
#include <iostream>
#include <vector>
#include "include/piInternal.h"
#include "include/checkBot.h"
#include "include/saveBot.h"
#include "include/getBot.h"
#include "include/reportBot.h"
#include "include/onCommand.h"
#include "include/onLaunch.h"

int main() {
    int piHour = getHour();
    int runningTime = 0;
    std::string adminId = getAdminId("data/adminId.txt");
    TgBot::Bot bot(getBotToken("data/botToken.txt"));

    onLaunchServerOnline(adminId, bot);

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        onCommandStart(bot, message);
    });
    bot.getEvents().onCommand("temperature", [&bot](TgBot::Message::Ptr message) {
        onCommandTemperature(bot, message);
    });
    bot.getEvents().onCommand("ip", [&bot](TgBot::Message::Ptr message) {
        onCommandIp(bot, message);
    });
    bot.getEvents().onCommand("restart", [&bot,&adminId](TgBot::Message::Ptr message) {
        onCommandRestart(bot, message, adminId);
    });
    bot.getEvents().onCommand("shutdown", [&bot,&adminId](TgBot::Message::Ptr message) {
        onCommandShutdown(bot, message, adminId);
    });
    bot.getEvents().onCommand("speedtest", [&bot](TgBot::Message::Ptr message) {
        onCommandSpeedtest(bot, message);
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
