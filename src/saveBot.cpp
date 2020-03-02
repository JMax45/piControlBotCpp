void saveBotToken(std::string botToken){
	std::ofstream file("data/botToken.txt");
	file << botToken;
	file.close();
}