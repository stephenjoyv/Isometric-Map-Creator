#include "Platform.h"

Platform::Platform(Mouse* mouse)
{
	panel = new TilePanel(Vector2f(19,6), mouse);
	map = new Map(mouse,40,40);
	seltile = new SelectedTile();
	saving = false;
	saver = new RectButton{ 200,192,500 - 32,750 - 32 * 3 / 4,20,"SaveMap",[this,mouse]() {

		//map->saveMap();
		saving = true;

		setlocale(LC_ALL, "Russian");
		Texture* tx = new Texture;
		bg_sp = new Sprite;
		tx->loadFromFile("images/inter_menu.png");
		bg_sp->setTexture(*tx);
		bg_sp->setPosition(500, 0);
		//sp->setColor(Color::Color(255,0,0,255));
		bg_sp->setScale(1, 0.85);

		input_tx = new Text;
		inp = new String;
		*inp = "Hey";
		input_tx->setFont(*font_global);
		input_tx->setString(*inp);
		//String::fromUtf8(inp->begin(), inp->end())
		input_tx->setFillColor(Color::White);
		input_tx->setPosition(500, 500);
		input_tx->setCharacterSize(50);



		},pool_window[0].get(),mouse,*color_main};
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
	if (saving) {
		pool_window[0].get()->draw(*bg_sp);
		pool_window[0].get()->draw(*input_tx);
	}
}

Platform::~Platform()
{
	delete panel;
	delete map;
	delete seltile;
}

void Platform::input(const sf::Uint32& tx)
{
	if (saving) {
		String m;
		m += static_cast<char>(tx);
		*inp += tx;
		input_tx->setString(m);
		cout << tx << '\n';
		//String::fromUtf32(inp->begin(), inp->end())
	}
}

