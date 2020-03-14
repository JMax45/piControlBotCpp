#ifndef RESPONSES_H
#define RESPONSES_H

class Responses{
public:
	void Start(TgBot::Bot tgbot, TgBot::Message::Ptr message);

	void Temperature(TgBot::Bot tgbot, TgBot::Message::Ptr message);

	void Ip(TgBot::Bot tgbot, TgBot::Message::Ptr message);

	void Restart(TgBot::Bot tgbot, TgBot::Message::Ptr message, std::string adminId);

	void Shutdown(TgBot::Bot tgbot, TgBot::Message::Ptr message, std::string adminId);

	void Speedtest(TgBot::Bot tgbot, TgBot::Message::Ptr message);

	void Upgrade(TgBot::Bot tgbot, TgBot::Message::Ptr message);

	void Logs(TgBot::Bot tgbot, TgBot::Message::Ptr message);
};

#endif