void saveBotToken(std::string botToken){
	std::ofstream file("data/botToken.txt");
	file << botToken;
	file.close();
}

void saveAdminId(std::string adminId, TgBot::Bot tgbot, TgBot::Message::Ptr message){
	std::vector<std::string> checkVector = txtToVector("data/adminId.txt");
	if(checkVector[0]=="false"){
		std::ofstream file("data/adminId.txt");
		file << adminId;
		file.close();
		tgbot.getApi().sendMessage(message->chat->id, std::to_string(message->chat->id));
		tgbot.getApi().sendMessage(message->chat->id, "Admin ID registered");
	}
	else{
		tgbot.getApi().sendMessage(message->chat->id, "An administrator is already registered");
	}	
}