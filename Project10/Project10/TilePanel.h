#pragma once
#include "Game.h"
#include "SelectedTile.h"
using namespace std;
using namespace sf;
class TilePanel {
	int size_x, size_y;
	Tile*** pnl;
	RenderTarget* ObjTar;
	SelectedTile* cur;
public:
	TilePanel(Vector2f amount, Mouse* mouse);
	void draw();
	bool click(SelectedTile* m);
	void clickRight();
	~TilePanel();
};
string normalizeString(int num);