void saveBotToken(std::string botToken){
	std::ofstream file("data/botToken.txt");
	file << botToken;
	file.close();
}

void saveAdminId(std::string adminId){
	std::ofstream file("data/adminId.txt");
	file << adminId;
	file.close();
}