#include "../src/onCommand.cpp"

void onCommandStart(TgBot::Bot bot, TgBot::Message::Ptr message);

void onCommandTemperature(TgBot::Bot bot, TgBot::Message::Ptr message);

void onCommandIp(TgBot::Bot bot, TgBot::Message::Ptr message);

void onCommandRestart(TgBot::Bot bot, TgBot::Message::Ptr message, std::string adminId);

void onCommandShutdown(TgBot::Bot bot, TgBot::Message::Ptr message, std::string adminId);

void onCommandSpeedtest(TgBot::Bot bot, TgBot::Message::Ptr message);