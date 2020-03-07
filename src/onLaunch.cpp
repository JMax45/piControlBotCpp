void onLaunchServerOnline(std::string adminId, TgBot::Bot tgbot){
	/*
    Check if the admin id is registered, if not, send a message to the terminal.
    Otherwise send a telegram message to the admin.
    */
	if(adminId == "false"){
    	std::cout << "\nType /start to save the admin id\n";
    }
    else{
    	tgbot.getApi().sendMessage(std::stoi(adminId), "The server is online");
    }
}