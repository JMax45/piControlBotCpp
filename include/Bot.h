#ifndef BOT_H
#define BOT_H

class Bot{
public:
	Responses responses;

	TgBot::Bot create_tgbot();
	TgBot::Bot tgbot = create_tgbot();

	Bot();
};

#endif