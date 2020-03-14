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
	transfer.convert("data/logs.txt", "data/logs.pdf");
	tgbot.getApi().sendMessage(message->chat->id, "File converted");

	tgbot.getApi().sendMessage(message->chat->id, "Uploading logs file...");
	std::string fileUrl = transfer.upload();
	tgbot.getApi().sendMessage(message->chat->id, "File uploaded");

	const boost::variant< TgBot::InputFile::Ptr, std::string > filename = fileUrl;
	tgbot.getApi().sendDocument(message->chat->id, filename);
}