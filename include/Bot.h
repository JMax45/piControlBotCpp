#ifndef BOT_H
#define BOT_H

class Bot{
public:
	Responses responses;

	std::string adminId;

	TgBot::Bot create_tgbot();
	TgBot::Bot tgbot = create_tgbot();

	void log(std::string message);
	
	Bot();
};

#endif