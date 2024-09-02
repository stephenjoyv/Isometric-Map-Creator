#include "Platform.h"
#include "TilePanel.h"
#include "TileMap.h"
#include "Input.h"
#include "SelectedTile.h"

Platform::Platform(sf::Mouse* mouse)
{
	panel = std::make_unique<TilePanel>(115, 20, Vector2i(700, 722), mouse);
	map = std::make_unique<Map>(Singleton::instance().getPoolWindow()[0].get(), mouse, 64, 64);
	seltile = std::make_unique<SelectedTile>();
	saving = false;
	initButtons(mouse);
	data = std::tuple<int, int, int>{ -1,-1,-1 };
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
		if (map->controlTile(x, y, z+1)) {
			cout << "----CLICKED LAST TILE-----\n";
		}
		map->addTile(seltile->getTile(), x, y,z);

		map->click(data);
		data = std::tuple<int, int, int>{ -1,-1,-1 };
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
			map->addTile(seltile->getTile(), x, y,z);
			cout << "----CLICKED LAST TILE-----\n";
		}
	
		map->click(data);

		data = std::tuple<int, int, int>{ -1,-1,-1 };
	}
}

void Platform::leftClickedPanel()
{
	panel->click(seltile);
	std::cout << "Check of map\n";
}

void Platform::initButtons(sf::Mouse * mouse)
{
	
	std::shared_ptr<Button> rb = std::make_shared<RectButton>(200, 192, 500 - 32, 750 - 32 * 3 / 4, 10, "Save Map", [this, mouse]() {
		//map->saveMap();
		//saving = true;

		setlocale(LC_ALL, "Russian");
		//RenderTarget* tm = pool_window[0].get();
		//inp = new InputTab{ 1000,200,300,500,Color::Yellow,tm,String{L"Введите путь к файлу"}};
		map->saveMap();
		}, Singleton::instance().getPoolWindow()[0].get(), mouse, * Singleton::instance().getMainColor());
	std::shared_ptr<Button> rt = std::make_shared<RectButton>(200, 192, 300 - 32, 750 - 32 * 3 / 4, 10, "Load Map", [this, mouse]() {
		map->loadMap("map.txt");
		},
		Singleton::instance().getPoolWindow()[0].get(), mouse, *Singleton::instance().getMainColor());
	rb->setId("game");
	rt->setId("game");
	Singleton::instance().getPoolButton().push_back(rb);
	Singleton::instance().getPoolButton().push_back(rt);
	//saver = new RectButton{ },Singleton::instance().getPoolWindow()[0].get(),mouse,*Singleton::instance().getMainColor() };
	//loader = new RectButton{ };
}

void Platform::rightClicked()
{
	/*seltile->loadDefaultCur();
	std::cout << normalizeString(24) << '\n';*/
	map->click(data);
	int x = get<0>(data),
		y = get<1>(data),
		z = get<2>(data);
	if ((x != -1 && y != -1 && z != -1) && seltile->isSelected()) {
		std::cout << "tile x = " << x << " tile y = " << y << '\n';
		//map->setTile(seltile->getTile(),x,y,z);
		map->deleteTile(x, y,z);

		//map->click(data);

		data = std::tuple<int, int, int>{ -1,-1,-1 };
	}
}

void Platform::wheelClicked()
{
	seltile->loadDefaultCur();
}

void Platform::draw()
{
	map->draw();
	panel->draw();
	if(saving)inp->draw();
}

Platform::~Platform()
{
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

