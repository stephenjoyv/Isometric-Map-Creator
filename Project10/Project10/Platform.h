#pragma once
#include "TilePanel.h"
#include "TileMap.h"
#include "Input.h"
extern Font* font_global;
class Platform
{
	TilePanel* panel;
	Map* map;
	SelectedTile* seltile;
	RectButton* saver;
	std::tuple<int, int, int> data;
	bool saving;
	InputTab* inp;
	//std::pair<int, int> data;
public:
	Platform(Mouse* mouse);
	void leftClicked();
	void leftClickedMap();
	void leftClickedPanel();
	void rightClicked();
	void input(const sf::Uint32& tx);
	void textClear();
	void draw();
	~Platform();
};

