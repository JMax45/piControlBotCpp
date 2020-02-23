std::string hourReport(int runningTime){
    std::vector<std::string> piInfo;
    std::vector<std::string> piInfoNames;

    piInfo.push_back(getPiTemperature());
    piInfoNames.push_back("CPU temperature: ");
    
    piInfo.push_back(getPiIp());
    piInfoNames.push_back("Server IP: ");
    
    piInfo.push_back(std::to_string(runningTime) + "hr");
    piInfoNames.push_back("Running time: ");

    std::ofstream file("hourReport.txt");
    for(int i=0; i<piInfo.size(); i++){
	file << piInfoNames[i] << piInfo[i] << "\n";
    }
    file.close();
    std::ifstream file2("hourReport.txt");
    std::string str((std::istreambuf_iterator<char>(file2)),
    std::istreambuf_iterator<char>());
    file2.close();
    
    std::string command = "rm hourReport.txt";
    system(command.c_str());
    return str;
}