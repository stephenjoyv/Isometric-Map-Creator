#include "Platform.h"

Platform::Platform(Mouse* mouse)
{
	panel = new TilePanel(Vector2f(19,6), mouse);
	map = new Map(mouse,40,40);
	seltile = new SelectedTile();
	saving = false;
	saver = new RectButton{ 200,192,500 - 32,750 - 32 * 3 / 4,10,"Save Map",[this,mouse]() {

		//map->saveMap();
		//saving = true;

		setlocale(LC_ALL, "Russian");
		//RenderTarget* tm = pool_window[0].get();
		//inp = new InputTab{ 1000,200,300,500,Color::Yellow,tm,String{L"Введите путь к файлу"}};
		map->saveMap();



		},pool_window[0].get(),mouse,*color_main};
	loader = new RectButton{ 200,192,300 - 32,750 - 32 * 3 / 4,10,"Load Map",[this,mouse]() {
		map->loadMap("map.txt");
		},
	pool_window[0].get(),mouse,*color_main};
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
	if(saving)inp->draw();
}

Platform::~Platform()
{
	delete panel;
	delete map;
	delete seltile;
}

void Platform::textClear()
{
	if (saving) inp->clear();
}

void Platform::deleteLast()
{
	if (saving) inp->deleteLast();
}

void Platform::input(const sf::Uint32& tx)
{
	if (saving) {
		inp->input(tx);
		//String m;
		//m += static_cast<char>(tx);
		//*inp += tx;
		//
		//input_tx->setString(L"Привет");
		//cout << tx << '\n';
		////String::fromUtf32(inp->begin(), inp->end())
	}
}

