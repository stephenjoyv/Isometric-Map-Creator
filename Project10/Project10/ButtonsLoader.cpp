#include "ButtonsFunctions.h"
#include "Libs.h"
#include "interfaceobj.h"

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
		std::string buttonNumber = std::to_string(i);
		std::unordered_map<int, std::function<void(void)>> menuFunction = {
			{1,StartNewGame},
			{2,LoadNewGame},
			{3,Exit},
			{4,loadDefaultColor},
			{5,Settings},
			{6,testing}
		};
		std::string name = static_cast<std::string>(obj["Buttons"][buttonNumber.c_str()]["char*"]);
		std::cout <<"size = "<< name.size() << '\n';
		Button* tmp = new CustomButton{
			(int)obj["Buttons"][buttonNumber.c_str()]["size_x"],
			(int)obj["Buttons"][buttonNumber.c_str()]["size_y"],
			(int)obj["Buttons"][buttonNumber.c_str()]["pos_x"],
			(int)obj["Buttons"][buttonNumber.c_str()]["pos_y"],
			(int)obj["Buttons"][buttonNumber.c_str()]["frames"],
			anylize(name.c_str(),name.size()),
			menuFunction[(int)obj["Buttons"][buttonNumber.c_str()]["function"]],
			space,
			mouse,
			color
		};
		tmp->pushToDrawingVector();
		
		std::cout << anylize(name.c_str(), name.size()) ;
	}
	std::cout << " pool button size " << Singleton::instance().getPoolButton().size() << '\n';
}