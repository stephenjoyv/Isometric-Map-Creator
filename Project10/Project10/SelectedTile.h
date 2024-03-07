#pragma once
#include "Game.h"
using namespace std;
using namespace sf;
class SelectedTile
{
	int x, y;
	string link;
	Cursor cur;
	Image* image;
public:
	SelectedTile(Image*);
	void loadCur();
	void enableCur();
};

