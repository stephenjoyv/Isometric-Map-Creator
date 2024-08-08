#include "Singleton.h"

Singleton::Singleton()
{
	font_global = std::make_unique<sf::Font>();
	color_main = std::make_unique<sf::Color>(85, 52, 218);;
	bg_color = std::make_unique<sf::Color>(129, 191, 115);
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
