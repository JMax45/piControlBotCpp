void onCommandStart(TgBot::Bot bot, TgBot::Message::Ptr message){
	saveAdminId(std::to_string(message->chat->id));
	bot.getApi().sendMessage(message->chat->id, std::to_string(message->chat->id));
}

void onCommandTemperature(TgBot::Bot bot, TgBot::Message::Ptr message){
	bot.getApi().sendMessage(message->chat->id, getPiTemperature());
}

void onCommandIp(TgBot::Bot bot, TgBot::Message::Ptr message){
	bot.getApi().sendMessage(message->chat->id, getPiIp());
}

void onCommandRestart(TgBot::Bot bot, TgBot::Message::Ptr message, std::string adminId){
	if(checkAdmin(adminId, std::to_string(message->chat->id))){
		bot.getApi().sendMessage(message->chat->id, "The server will restart");
	    std::string command = "sudo touch systemReboot.txt";
        system(command.c_str());
	}
	else{
	    bot.getApi().sendMessage(message->chat->id, "Only the administrator can execute this command");
	}
}

void onCommandShutdown(TgBot::Bot bot, TgBot::Message::Ptr message, std::string adminId){
	if(checkAdmin(adminId, std::to_string(message->chat->id))){
		bot.getApi().sendMessage(message->chat->id, "The server will shutdown");
        std::string command = "sudo touch systemShutdown.txt";
        system(command.c_str());
    }
    else{
    	bot.getApi().sendMessage(message->chat->id, "Only the administrator can execute this command");
    }
}

void onCommandSpeedtest(TgBot::Bot bot, TgBot::Message::Ptr message){
	bot.getApi().sendMessage(message->chat->id, "Testing network speed...");
    bot.getApi().sendMessage(message->chat->id, piSpeedTest());
}

void onCommandUpgrade(TgBot::Bot bot, TgBot::Message::Ptr message){
	bot.getApi().sendMessage(message->chat->id, "System upgrade...");
	std::string systemUpgrade = piUpgrade();
	bot.getApi().sendMessage(message->chat->id, systemUpgrade);
}	