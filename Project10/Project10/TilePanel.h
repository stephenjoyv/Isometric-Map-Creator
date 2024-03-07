#pragma once
#include "Game.h"
using namespace std;
using namespace sf;
class TilePanel {
	int size_x,size_y;
	DetectedImage*** pnl;
	RenderTarget* ObjTar;
public:
	TilePanel(Vector2f amount,Mouse* mouse);
	void draw();
	~TilePanel();
};