#include "../include/Transfer.h"

Transfer::Transfer(){

}

void Transfer::convert(std::string filename){
	std::string command = ("cd data && libreoffice --convert-to 'pdf' " + filename);
	system(command.c_str());
}

std::string Transfer::upload(){
	std::string filename = "./logs.pdf";
	std::string command = ("cd data && curl --upload-file " + filename + " https://transfer.sh/" + filename +
		" >> upload.txt");

	system(command.c_str());
	//system("cd ..");

	std::ifstream file("data/upload.txt");
	std::string fileUrl;
	file >> fileUrl;

	system("rm -f data/upload.txt");
	system("rm -f data/logs.pdf");

	return fileUrl;
}