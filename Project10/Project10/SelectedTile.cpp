#include "SelectedTile.h"
SelectedTile::SelectedTile() {
	x = 0;
	y = 0;
	selected = false;
	tile = new Tile;
}

void SelectedTile::loadTile(Tile* newtile)
{
	std::cout << "load started\n";
	*tile = *newtile;
	std::cout << "successfull copy\n";
	loadCur(tile);
	/*selected = true;
	cur.loadFromSystem(Cursor::Type::Arrow);
	enableCur();*/
}

bool SelectedTile::isSelected()
{
	return selected;
}

void SelectedTile::loadCur(Tile* tile)
{
	selected = true;
	std::cout << "load successfull\n";
	Image curimg = *(tile->image);
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			curimg.setPixel(i, k, Color::Red);
		}
	}

	std::cout << "cursor loaded" << cur.loadFromPixels(curimg.getPixelsPtr(), Vector2u(curimg.getSize().x, curimg.getSize().y), Vector2u(0, 0)) << '\n';
	enableCur();
	std::cout << "dawkdakdabtr31313165464\n";
}

void SelectedTile::enableCur()
{
	pool_window[0].get()->setMouseCursor(cur);
}

void SelectedTile::loadDefaultCur()
{
	selected = false;
	cur.loadFromSystem(Cursor::Type::Arrow);
	enableCur();
}

Tile* SelectedTile::getTile()
{
	return tile;
}


SelectedTile::~SelectedTile()
{
}
