bool checkExists(std::string filename){
    std::ifstream file(filename);
    return (bool)file;
}

void checkReboot(){
    if(checkExists("systemReboot.txt")==true){
        std::string command = "rm -f systemReboot.txt";
        system(command.c_str());
        piRestart();
    }	
}

bool checkAdmin(std::string adminId, std::string messageId){
    bool adminStatus;
    if(adminId == messageId){
	adminStatus = true;
    }
    else{
	adminStatus = false;
    }
    return adminStatus;
}

void checkShutdown(){
    if(checkExists("systemShutdown.txt")==true){
        std::string command = "rm -f systemShutdown.txt";
        system(command.c_str());
        piShutdown();
    }  
}