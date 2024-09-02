#pragma once
#include "Libs.h"
using namespace std;
using namespace sf;
class Tile;
class SelectedTile
{
	int x, y;
	Cursor cur;
	bool selected;
	Tile* tile;

public:
	SelectedTile();
	void loadTile(Tile* tile);
	bool isSelected();
	void loadCur(Tile* m);
	void enableCur();
	void loadDefaultCur();
	Tile* getTile();
	~SelectedTile();
};

