#pragma once
#include "TilePanel.h"
#include "TileMap.h"
#include "Input.h"
#include <memory>

class Platform
{
	std::unique_ptr<TilePanel> panel;
	std::unique_ptr<Map> map;
	std::unique_ptr<SelectedTile> seltile;
	RectButton* saver,*loader;
	std::tuple<int, int, int> data;
	bool saving;
	InputTab* inp;
	//std::pair<int, int> data;
public:
	Platform(Mouse* mouse);
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

