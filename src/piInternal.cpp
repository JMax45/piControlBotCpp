std::string getPiTemperature(){
    std::string command = "vcgencmd measure_temp >> temperature.txt";
    system(command.c_str());

    std::ifstream file("temperature.txt");
    std::string piTemperature;
    file >> piTemperature;
    std::string command2 = "rm temperature.txt";
    system(command2.c_str());
    return piTemperature;
}

std::string getPiIp(){
    std::string command = "curl ifconfig.me >> ifconfig.txt";
    system(command.c_str());

    std::ifstream file("ifconfig.txt");
    std::string piIp;
    file >> piIp;
    std::string command2 = "rm ifconfig.txt";
    system(command2.c_str());
    return piIp;
}

void piRestart(){
    std::string command = "sudo shutdown now -r";
    system(command.c_str());
}

void piShutdown(){
    std::string command = "sudo shutdown now";
    system(command.c_str());
}

std::string piSpeedTest(){
	std::string command = "sudo speedtest-cli --simple >> speedTest.txt";
	system(command.c_str());
	std::ifstream file("speedTest.txt");
    std::string str((std::istreambuf_iterator<char>(file)),
    std::istreambuf_iterator<char>());
    file.close();
	std::string command2 = "rm speedTest.txt";
	system(command2.c_str());
	return str;
}

std::vector<std::string> txtToVector(std::string filename){
    std::vector<std::string> allStrings;
    std::ifstream file(filename);
    std::string str;
    while(std::getline(file, str)){
    allStrings.push_back(str);
    }
    file.close();
    return allStrings;
}

std::string piUpgrade(){
    system("sudo apt-get upgrade >> upgrade.txt");
    system("tail -n 1 upgrade.txt >> upgradeStatus.txt");
    system("sudo rm upgrade.txt");
    std::vector<std::string> fileTail = txtToVector("upgradeStatus.txt");
    system("rm upgradeStatus.txt");
    // Returns first element because there is only one line in the file
    return fileTail[0]; 
}