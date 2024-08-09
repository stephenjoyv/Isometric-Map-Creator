
#include "ButtonsFunctions.h"
namespace n = nlohmann;
char* anylize(const char* ptr ,int size) {
	char* tmp = new char[size+1];
	for (int i = 0; i < size; i++) {
		tmp[i] = ptr[i];
	}
	tmp[size] = '\0';
	return tmp;
}
void ButtonLoader(sf::RenderTarget* space,sf::Mouse* mouse,sf::Color color,String adress) {
	n::json obj;
	std::fstream File;
	File.open(adress.toAnsiString());
	std::cout << "file is open " << File.is_open() << '\n';
	File >> obj;
	std::cout << obj["Buttons"].size();
	for (int i = 1; i <= obj["Buttons"].size(); i++) {
		std::string tmps = std::to_string(i);
		void(*tmpv)();
		switch ((int)obj["Buttons"][tmps.c_str()]["function"])
		{
		case 1:
		{
			tmpv = StartNewGame;
			break;
		}
		case 2: {
			tmpv = LoadNewGame;
			break;
		}
		case 3: {
			tmpv = Exit;
			break;
		}
		case 4: {
			tmpv = loadDefaultColor;
			break;
		}
		case 5: {
			tmpv = Settings;
			break;
		}
		}
		std::string name = (std::string)obj["Buttons"][tmps.c_str()]["char*"];
		std::cout <<"size = "<< name.size() << '\n';
		Button* tmp = new CustomButton{ (int)obj["Buttons"][tmps.c_str()]["size_x"],(int)obj["Buttons"][tmps.c_str()]["size_y"],
		(int)obj["Buttons"][tmps.c_str()]["pos_x"],(int)obj["Buttons"][tmps.c_str()]["pos_y"],(int)obj["Buttons"][tmps.c_str()]["frames"],
		anylize(name.c_str(),name.size()),tmpv,space,mouse,color};
		std::cout << anylize(name.c_str(), name.size()) ;
		//delete name;
	}
}