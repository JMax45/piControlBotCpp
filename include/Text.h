#ifndef TEXT_H
#define TEXT_H

class Text{
public:
	void split(std::string s, std::string delimiter, std::string filename);

	bool checkSame(std::vector<std::string> list, std::string str);
};

#endif