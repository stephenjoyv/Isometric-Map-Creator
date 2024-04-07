#include "Platform.h"

Platform::Platform(Mouse* mouse)
{
	panel = new TilePanel(Vector2f(19,6), mouse);
	map = new Map(string("daw"), mouse);
	seltile = new SelectedTile();
	data = tuple<int, int, int>{ -1,-1,-1 };
}

void Platform::leftClicked()
{
	panel->click(seltile);
	std::cout << "Check of map\n";
	map->click(data);
	int x = get<0>(data),
		y = get<1>(data),
		z = get<2>(data);
	if ((x != -1 && y!= -1 && z!=-1) && seltile->isSelected()) {
		std::cout << "tile x = " << x << " tile y = " << y << '\n';
		map->setTile(seltile->getTile(),x,y,z);
		map->click(data);
		data = tuple<int, int, int>{ -1,-1,-1 };
	}
	
}

void Platform::rightClicked()
{
	seltile->loadDefaultCur();
	std::cout << normalizeString(24) << '\n';
}

void Platform::draw()
{
	panel->draw();
	map->draw();
}

Platform::~Platform()
{
	delete panel;
	delete map;
	delete seltile;
}

