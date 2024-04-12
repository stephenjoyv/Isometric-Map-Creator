#pragma once
#include "TilePanel.h"
#include "TileMap.h"
class Platform
{
	TilePanel* panel;
	Map* map;
	SelectedTile* seltile;
	std::tuple<int, int, int> data;
	//std::pair<int, int> data;
public:
	Platform(Mouse* mouse);
	void leftClicked();
	void leftClickedMap();
	void leftClickedPanel();
	void rightClicked();
	void draw();
	~Platform();
};

