#include "Platform.h"

Platform::Platform(Mouse* mouse)
{
	panel = new TilePanel(Vector2f(5, 2), mouse);
	map = new Map(string("daw"), mouse);
	seltile = new SelectedTile();
	data.first = -1; data.second = -1;
}

void Platform::leftClicked()
{
	panel->click(seltile);
	std::cout << "Check of map\n";
	map->click(data);
	if ((data.first != -1 && data.second != -1) && seltile->isSelected()) {
		std::cout << "tile x = " << data.first << " tile y = " << data.second << '\n';
		map->setTile(seltile->getTile(),data.first,data.second);
		data.first = -1; data.second = -1;
	}
	
}

void Platform::rightClicked()
{
	seltile->loadDefaultCur();
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

