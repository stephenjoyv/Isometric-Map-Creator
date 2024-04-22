#pragma once
#include "TilePanel.h"
#include "TileMap.h"
extern Font* font_global;
class Platform
{
	TilePanel* panel;
	Map* map;
	SelectedTile* seltile;
	RectButton* saver;
	std::tuple<int, int, int> data;
	bool saving;
	String* inp;
	Text* input_tx;
	Sprite* bg_sp;
	//std::pair<int, int> data;
public:
	Platform(Mouse* mouse);
	void leftClicked();
	void leftClickedMap();
	void leftClickedPanel();
	void rightClicked();
	void input(const sf::Uint32& tx);
	void draw();
	~Platform();
};

