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

	std::vector<std::string> prohibitedNumbers;
	prohibitedNumbers = txtToVector("data/prohibitedNumbers.txt");

	if(parameters.size() == 1){
		tgbot.getApi().sendMessage(message->chat->id, "This function can perform an SMS bombing");
		tgbot.getApi().sendMessage(message->chat->id, "You can use it by typing /sms + phone number + bombing time + threads");
		tgbot.getApi().sendMessage(message->chat->id, "Example: /sms 15554443333 15 10");
	}	
	// If parameters are more or less than necessary than don't execute the script but output a warning
	else if(parameters.size()>4||parameters.size()<4){
		tgbot.getApi().sendMessage(message->chat->id, "Wrong number of parameters");
		tgbot.getApi().sendMessage(message->chat->id, "You have to use the following ones: phone number, time, threads");
	}
	else if(text.checkSame(prohibitedNumbers, parameters[1])==true){
		tgbot.getApi().sendMessage(message->chat->id, "Prohibited number");
	}
	else{
    	std::string command = ("quack --tool SMS --target " + parameters[1] + " --time " + parameters[2] + " --threads " + parameters[3] + " >> data/smsBomb.txt");
    	tgbot.getApi().sendMessage(message->chat->id, "Started SMS bombing...");
		system(command.c_str());    

		std::vector<std::string> smsOutput;
		smsOutput = txtToVector("data/smsBomb.txt");
		// Finds how many messages were sent
		int smsSent = 0;
		for(int i=0; i<smsOutput.size(); i++){
			std::string str = smsOutput[i];
			str = str[8];
			if(str=="+"){
				smsSent++;
			}
		}
		remove("data/smsBomb.txt");

		tgbot.getApi().sendMessage(message->chat->id, std::to_string(smsSent) + " messages sent");
		tgbot.getApi().sendMessage(message->chat->id, "Bombing completed");
	}	
}