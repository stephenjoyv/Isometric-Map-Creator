#pragma once
#include <memory>
#include "Libs.h"
class TilePanel;
class Map;
class SelectedTile;
class RectButton;
class InputTab;
class Platform
{
	std::unique_ptr<TilePanel> panel;
	std::unique_ptr<Map> map;
	std::unique_ptr<SelectedTile> seltile;
	RectButton* saver,*loader;
	std::tuple<int, int, int> data;
	bool saving;
	InputTab* inp;
public:
	Platform(sf::Mouse* mouse);
	void leftClicked();
	void leftClickedMap();
	void leftClickedPanel();
	void initButtons(sf::Mouse * mouse);
	void rightClicked();
	void wheelClicked();
	void input(const sf::Uint32& tx);
	void textClear();
	void deleteLast();
	void draw();
	~Platform();
};

