#include <stdio.h>
#include <tgbot/tgbot.h>
#include <iostream>
#include <vector>
#include "lib/file/src/txtToVector.cpp"
#include "lib/date/include/date/date.h"
#include "lib/transfer/src/Transfer.cpp"
#include "include/piInternal.h"
#include "include/checkBot.h"
#include "include/saveBot.h"
#include "include/getBot.h"
#include "include/reportBot.h"
#include "src/Responses.cpp"
#include "src/Bot.cpp"

int main() {
    //This class contains all the things related to the bot
    Bot bot;

    bot.tgbot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Start(bot.tgbot, message);
    });
    bot.tgbot.getEvents().onCommand("temperature", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Temperature(bot.tgbot, message);
    });
    bot.tgbot.getEvents().onCommand("ip", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Ip(bot.tgbot, message);
    });
    bot.tgbot.getEvents().onCommand("restart", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Restart(bot.tgbot, message, bot.adminId);
    });
    bot.tgbot.getEvents().onCommand("shutdown", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Shutdown(bot.tgbot, message, bot.adminId);
    });
    bot.tgbot.getEvents().onCommand("speedtest", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Speedtest(bot.tgbot, message);
    });
    bot.tgbot.getEvents().onCommand("upgrade", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Upgrade(bot.tgbot, message);
    });
    bot.tgbot.getEvents().onCommand("logs", [&bot](TgBot::Message::Ptr message) {
        bot.responses.Logs(bot.tgbot, message);
    });

    bot.tgbot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        std::string log = (message->text.c_str());
        bot.log("User wrote: " + log + ".");
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
    });
    try {
        printf("Bot username: %s\n", bot.tgbot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot.tgbot);
        while (true) {
            if(getHour()!=bot.time){
		bot.time = getHour();
				bot.upTime++;
                bot.tgbot.getApi().sendMessage(std::stoi(bot.adminId), hourReport(bot.upTime));
	    }
	    checkReboot();
	    checkShutdown();
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
        std::string error = ("error: %s\n", e.what());
        bot.log(error);
        if(error=="Not Found"){
            saveBotToken("false");
        }
    }
    return 0;
}
