#include "TilePanel.h"
#include "Game.h"
#include "SelectedTile.h"
#include "cmath"
#include "TileMap.h"
TilePanel::TilePanel(size_t tile_count,size_t rows, Vector2i pos, Mouse* mouse) {
	size_x = tile_count;
	size_y = rows;
	pos_x = pos.x;
	pos_y = pos.y;
	ObjTar = Singleton::instance().getPoolWindow()[0].get();
	pnl = new Tile * *[round(tile_count*1.0/rows)];
	cout << "ceil " << round(tile_count*1.0 / rows) << '\n';
	cur = std::make_unique<SelectedTile>();
	TilePanel_tx = std::make_unique<RenderTexture>();
	TilePanel_sp = std::make_unique<Sprite>();
	TilePanel_tx->create(724, 220);

	for (size_t i = 0; i < round(tile_count * 1.0 / rows); i++)
	{
		if (i!= round(tile_count * 1.0 / rows)-1)
		{
			pnl[i] = new Tile * [rows];
		}
		else
		{
			pnl[i] = new Tile * [tile_count%rows];
			cout << "Dwadwad";
		}
		
	}
	cout << rows << '\n';
	cout << tile_count % rows << '\n';


	for (int i = 0,j = 0, c = 0; c < tile_count; c++,j++) {
		if (j==20)
		{
			j = -1;
			i++;
			continue;
		}
		pnl[i][j] = new Tile("tyles/tile_" + normalizeString(c) + ".png", mouse);
		pnl[i][j]->setTarget(TilePanel_tx.get());
		pnl[i][j]->init_border();
		pnl[i][j]->setOrigin(0, 0);
		if (j%rows!=0) {
			pnl[i][j]->setPosition(pnl[i][j - 1]->getPosition().x + pnl[i][j - 1]->getSize().x + 4, pnl[i][j - 1]->getPosition().y);
			pnl[i][j]->draw();
			//std::cout << "borders " << pnl[i][j]->borders->getSize().y << " " << pnl[i][j]->texture->getSize().y << '\n';
		}
		else if (j!=0){
			j = -1;
			i++;
		}
		else {
			pnl[i][j]->setPosition(4, 4 + i * (pnl[i][j]->getSize().y+4));
			pnl[i][j]->draw();
		}
		std::cout << "i - " << i << "  j - " << j << " c - "<< c << '\n';
		cout << "POS x:" << 4 << " y: " << 4 + i * pnl[i][j]->getSize().y << '\n';
		
	}
	TilePanel_tx->display();
	TilePanel_sp->setTexture(TilePanel_tx->getTexture());
	TilePanel_sp->setPosition(pos.x, pos.y);
}

void TilePanel::draw()
{
	Singleton::instance().getPoolWindow()[0].get()->draw(*TilePanel_sp);
}

bool TilePanel::click(std::unique_ptr<SelectedTile>& seltile)
{
	//Доделать

	bool clicked = false;
	for (int i = 0, j = 0, c = 0; c < size_x; c++, j++) {
		if (j == 20)
		{
			j = -1;
			i++;
			continue;
		}
		if (pnl[i][j]->Click(pos_x, pos_y))
		{
			std::cout << "|||||||||||Tile pos x " << pnl[i][j]->sprite->getPosition().x <<
				" pos y " << pnl[i][j]->sprite->getPosition().y << "||||" << '\n';
			pnl[i][j]->setOrigin(0, pnl[i][j]->texture->getSize().y * 3 / 4);
			std::cout << "|||||||||||Tile pos x " << pnl[i][j]->sprite->getPosition().x <<
				" pos y "<< pnl[i][j]->sprite->getPosition().y <<"||||" << '\n';
			seltile->loadTile(pnl[i][j]);
			std::cout << "Tile loaded\n";
			pnl[i][j]->clicked = false;
			clicked = true;
			return clicked;
		}
	}
	return clicked;
}

void TilePanel::clickRight()
{
	cur->loadDefaultCur();
}


TilePanel::~TilePanel() = default;

//For 3 symbols nums
std::string normalizeString(int num)
{
	if (num<=999 && num>=(-999))
	{
		string tmp = to_string(num);
		string res = "000";
		int tms = tmp.size() - 1;
		int rs = 2;
		while (tms >=0)
		{
			res[rs] = tmp[tms];
			tms--;
			rs--;
		}
		return res;
		
	}
	else {
		throw "symbols in number more 3";
	}
	
	return string();
}
