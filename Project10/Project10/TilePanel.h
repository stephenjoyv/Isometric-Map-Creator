#pragma once
#include "Game.h"
#include "SelectedTile.h"
using namespace std;
using namespace sf;
class TilePanel {
	int size_x,size_y;
	DetectedImage*** pnl;
	RenderTarget* ObjTar;
	SelectedTile* cur;
public:
	TilePanel(Vector2f amount,Mouse* mouse);
	void draw();
	void click();
	~TilePanel();
};