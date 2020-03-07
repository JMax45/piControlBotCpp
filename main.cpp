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
    int piHour = getHour();
    int runningTime = 0;
    std::string adminId = getAdminId("data/adminId.txt");
    TgBot::Bot tgbot(getBotToken("data/botToken.txt"));

    //This class contains all the things related to the bot
    Bot bot;

    onLaunchServerOnline(adminId, tgbot);

    tgbot.getEvents().onCommand("start", [&tgbot, &bot](TgBot::Message::Ptr message) {
        bot.responses.Start(tgbot, message);
    });
    tgbot.getEvents().onCommand("temperature", [&tgbot, &bot](TgBot::Message::Ptr message) {
        bot.responses.Temperature(tgbot, message);
    });
    tgbot.getEvents().onCommand("ip", [&tgbot, &bot](TgBot::Message::Ptr message) {
        bot.responses.Ip(tgbot, message);
    });
    tgbot.getEvents().onCommand("restart", [&tgbot,&adminId, &bot](TgBot::Message::Ptr message) {
        bot.responses.Restart(tgbot, message, adminId);
    });
    tgbot.getEvents().onCommand("shutdown", [&tgbot,&adminId, &bot](TgBot::Message::Ptr message) {
        bot.responses.Shutdown(tgbot, message, adminId);
    });
    tgbot.getEvents().onCommand("speedtest", [&tgbot, &bot](TgBot::Message::Ptr message) {
        bot.responses.Speedtest(tgbot, message);
    });
    tgbot.getEvents().onCommand("upgrade", [&tgbot, &bot](TgBot::Message::Ptr message) {
        bot.responses.Upgrade(tgbot, message);
    });

    tgbot.getEvents().onAnyMessage([&tgbot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
    });
    try {
        printf("Bot username: %s\n", tgbot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(tgbot);
        while (true) {
            if(getHour()!=piHour){
		piHour = getHour();
				runningTime++;
                tgbot.getApi().sendMessage(std::stoi(adminId), hourReport(runningTime));
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
