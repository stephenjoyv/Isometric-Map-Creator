#include "Platform.h"

Platform::Platform(Mouse* mouse)
{
	panel = new TilePanel(Vector2f(19,6), mouse);
	map = new Map(mouse);
	seltile = new SelectedTile();
	saver = new RectButton{ 200,192,500-32,750-32*3/4,20,"SaveMap",[this]() {map->saveMap(); },pool_window[0].get(),mouse,*color_main};
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
		//map->setTile(seltile->getTile(),x,y,z);
		if (map->controlTile(x, y, z+1)) {
			map->addTile(seltile->getTile(), x, y);
			cout << "----CLICKED LAST TILE-----\n";
		}
		map->click(data);
		data = tuple<int, int, int>{ -1,-1,-1 };
	}
	
}

void Platform::leftClickedMap()
{
	map->click(data);
	int x = get<0>(data),
		y = get<1>(data),
		z = get<2>(data);
	if ((x != -1 && y != -1 && z != -1) && seltile->isSelected()) {
		std::cout << "tile x = " << x << " tile y = " << y << '\n';
		//map->setTile(seltile->getTile(),x,y,z);
		
		if (map->controlTile(x, y, z+1)) {
			map->addTile(seltile->getTile(), x, y);
			cout << "----CLICKED LAST TILE-----\n";
		}
	
		map->click(data);

		data = tuple<int, int, int>{ -1,-1,-1 };
	}
}

void Platform::leftClickedPanel()
{
	panel->click(seltile);
	std::cout << "Check of map\n";
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

