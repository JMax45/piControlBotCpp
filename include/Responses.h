#ifndef RESPONSES_H
#define RESPONSES_H

class Responses{
public:
	void Start(TgBot::Bot bot, TgBot::Message::Ptr message);

	void Temperature(TgBot::Bot bot, TgBot::Message::Ptr message);

	void Ip(TgBot::Bot bot, TgBot::Message::Ptr message);

	void Restart(TgBot::Bot bot, TgBot::Message::Ptr message, std::string adminId);

	void Shutdown(TgBot::Bot bot, TgBot::Message::Ptr message, std::string adminId);

	void Speedtest(TgBot::Bot bot, TgBot::Message::Ptr message);

	void Upgrade(TgBot::Bot bot, TgBot::Message::Ptr message);
};

#endif