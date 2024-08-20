#pragma once
#include <iostream>
#include "Libs.h"
#include "interfaceobj.h"
class Button;
class Singleton
{
private:
	Singleton();
	bool appActivity;
	std::string vl;
	std::vector<std::shared_ptr<Button>> pool_button;
	std::vector<std::shared_ptr<sf::RenderWindow>> pool_window;
	std::unique_ptr<sf::Font> font_global;
	int FPS;
	std::unique_ptr<sf::Color> color_main;
	std::unique_ptr<sf::Color> bg_color;
public:
	std::vector<std::shared_ptr<Button>>& getPoolButton();
	std::vector<std::shared_ptr<sf::RenderWindow>>& getPoolWindow();
	std::unique_ptr<sf::Font>& getGlobalFont();
	std::unique_ptr<sf::Color>& getMainColor();
	std::unique_ptr<sf::Color>& getBackgroundColor();
	int getFPS();
	bool isAppActive();



	static Singleton& instance();
	void setVl(const std::string&);
	std::string getVl();
};
