#include "../include/Responses.h"

void Responses::Start(TgBot::Bot tgbot, TgBot::Message::Ptr message){
	saveAdminId(std::to_string(message->chat->id), tgbot, message);
}

void Responses::Temperature(TgBot::Bot tgbot, TgBot::Message::Ptr message){
	tgbot.getApi().sendMessage(message->chat->id, getPiTemperature());
}

void Responses::Ip(TgBot::Bot tgbot, TgBot::Message::Ptr message){
	tgbot.getApi().sendMessage(message->chat->id, getPiIp());
}

void Responses::Restart(TgBot::Bot tgbot, TgBot::Message::Ptr message, std::string adminId){
	if(checkAdmin(adminId, std::to_string(message->chat->id))){
		tgbot.getApi().sendMessage(message->chat->id, "The server will restart");
	    std::string command = "sudo touch systemReboot.txt";
        system(command.c_str());
	}
	else{
	    tgbot.getApi().sendMessage(message->chat->id, "Only the administrator can execute this command");
	}
}

void Responses::Shutdown(TgBot::Bot tgbot, TgBot::Message::Ptr message, std::string adminId){
	if(checkAdmin(adminId, std::to_string(message->chat->id))){
		tgbot.getApi().sendMessage(message->chat->id, "The server will shutdown");
        std::string command = "sudo touch systemShutdown.txt";
        system(command.c_str());
    }
    else{
    	tgbot.getApi().sendMessage(message->chat->id, "Only the administrator can execute this command");
    }
}

void Responses::Speedtest(TgBot::Bot tgbot, TgBot::Message::Ptr message){
	tgbot.getApi().sendMessage(message->chat->id, "Testing network speed...");
    tgbot.getApi().sendMessage(message->chat->id, piSpeedTest());
}

void Responses::Upgrade(TgBot::Bot tgbot, TgBot::Message::Ptr message){
	tgbot.getApi().sendMessage(message->chat->id, "System upgrade...");
	std::string systemUpgrade = piUpgrade();
	tgbot.getApi().sendMessage(message->chat->id, systemUpgrade);
}	

void Responses::Logs(TgBot::Bot tgbot, TgBot::Message::Ptr message){
	Transfer transfer;
	
	tgbot.getApi().sendMessage(message->chat->id, "Converting logs file...");
	transfer.convert("logs.txt");
	tgbot.getApi().sendMessage(message->chat->id, "File converted");

	tgbot.getApi().sendMessage(message->chat->id, "Uploading logs file...");
	std::string fileUrl = transfer.upload();
	tgbot.getApi().sendMessage(message->chat->id, "File uploaded");

	const boost::variant< TgBot::InputFile::Ptr, std::string > filename = fileUrl;
	tgbot.getApi().sendDocument(message->chat->id, filename);
}

void Responses::Sms(TgBot::Bot tgbot, TgBot::Message::Ptr message){
	Text text;
	std::cout << "Starting smsBomber...\n";

	std::string str = (message->text.c_str());
	text.split(str, " ", "data/split.txt");

	std::vector<std::string> parameters;
	parameters = txtToVector("data/split.txt");
	remove("data/split.txt");

	// If parameters are more or less than necessary than don't execute the script but output a warning
	if(parameters.size()>4||parameters.size()<4){
		tgbot.getApi().sendMessage(message->chat->id, "Wrong number of parameters");
		tgbot.getApi().sendMessage(message->chat->id, "You have to use the following ones: phone number, time, threads");
	}
	else{
    	std::string command = ("quack --tool SMS --target " + parameters[1] + " --time " + parameters[2] + " --threads " + parameters[3]);
    	tgbot.getApi().sendMessage(message->chat->id, "Started SMS bombing...");
		system(command.c_str());    
		tgbot.getApi().sendMessage(message->chat->id, "Bombing completed");
	}	
}