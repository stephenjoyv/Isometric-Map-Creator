#include "Singleton.h"

Singleton::Singleton()
{
	font_global = std::make_unique<sf::Font>();
	/*color_main = std::make_unique<sf::Color>(85, 52, 218);
	bg_color = std::make_unique<sf::Color>(129, 191, 115);*/

	auto load_colors = [](std::unique_ptr<sf::Color>& main, std::unique_ptr<sf::Color>& bg) {
		n::json obj;
		std::fstream File;
		File.open("notes/colors.json");
		std::cout << "file is open " << File.is_open() << '\n';
		File >> obj;
		std::cout << obj["colors"].size();
		main.reset(new sf::Color(
			static_cast<int>(obj["colors"]["main"]["red"]),
			static_cast<int>(obj["colors"]["main"]["green"]),
			static_cast<int>(obj["colors"]["main"]["blue"])));
		bg.reset(new sf::Color(
			static_cast<int>(obj["colors"]["background"]["red"]),
			static_cast<int>(obj["colors"]["background"]["green"]),
			static_cast<int>(obj["colors"]["background"]["blue"])));
		};
	load_colors(color_main,bg_color);
	std::shared_ptr<RenderWindow> w = std::make_shared<sf::RenderWindow>(VideoMode(1610, 1000), "application");
	font_global->loadFromFile("tt-squares-condensed-8.ttf");//EduNSWACTFoundation - Regular.ttf
	appActivity = true;
	FPS = 60;
	
	pool_window.emplace_back(w);
	pool_window[0]->setFramerateLimit(FPS);
}

std::vector<std::shared_ptr<Button>>& Singleton::getPoolButton()
{
	return pool_button;
}
std::vector<std::shared_ptr<sf::RenderWindow>>& Singleton::getPoolWindow()
{
	return pool_window;
}
std::unique_ptr<sf::Font>& Singleton::getGlobalFont()
{
	return font_global;
}
std::unique_ptr<sf::Color>& Singleton::getMainColor()
{
	return color_main;
}
std::unique_ptr<sf::Color>& Singleton::getBackgroundColor()
{
	return bg_color;
}
sf::Mouse& Singleton::getMouse()
{
	return mouse;
}
void Singleton::getCharacterSize()
{
	HDC hDC;
	TEXTMETRIC textMetric;
	HFONT   hFont, hOldFont;
	int sizeInPpoints, lineHeight;
	RECT textRect;
	LPCWSTR buffer = L"Checkable string!";

	hDC = GetDC(Singleton::instance().getPoolWindow()[0]->getSystemHandle());
	sizeInPpoints = MulDiv(36, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	hFont = CreateFont(-sizeInPpoints, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, L"tt-squares-condensed-8");
	hOldFont = (HFONT)SelectObject(hDC, hFont);

	GetTextMetrics(hDC, &textMetric);

	lineHeight = textMetric.tmHeight; // character height in current font
	std::wstring w = static_cast<std::wstring>(buffer);
	std::string m = std::string{ w.begin(),w.end() };
	textRect.left = textRect.right = textRect.top = textRect.bottom = 0;
	DrawText(hDC, buffer, strlen(m.c_str()), &textRect, DT_CALCRECT);
}
int Singleton::getFPS()
{
	return FPS;
}
bool Singleton::isAppActive()
{
	return appActivity;
}
Singleton& Singleton::instance()
{
	static Singleton INSTANCE;
	//std::cout << &INSTANCE << '\n';
	return INSTANCE;
}

void Singleton::setVl(const std::string& str)
{
	vl = str;
}

std::string Singleton::getVl()
{
	return vl;
}
