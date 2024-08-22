#pragma once
#include "Game.h"
#include "SelectedTile.h"
#include "cmath"
using namespace std;
using namespace sf;
class TilePanel {
	int size_x, size_y;
	int pos_x, pos_y;
	Tile*** pnl;
	RenderTarget* ObjTar;
	std::unique_ptr<SelectedTile> cur;
	std::unique_ptr<RenderTexture> TilePanel_tx;
	std::unique_ptr<Sprite> TilePanel_sp;
public:
	TilePanel(size_t tile_count,size_t rows_count,Vector2i position, Mouse* mouse);
	void draw();
	bool click(std::unique_ptr<SelectedTile>& m);
	void clickRight();
	~TilePanel();
};
string normalizeString(int num);