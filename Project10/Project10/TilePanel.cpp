#include "TilePanel.h"
TilePanel::TilePanel(Vector2f size, Mouse* mouse) {
	size_x = size.x;
	size_y = size.y;
	ObjTar = pool_window[0].get();
	pnl = new Tile * *[size_y];
	for (int i = 0; i < size_y; i++)
	{
		pnl[i] = new Tile * [size_x];
		for (int j = 0; j < size_x; j++)
		{
			pnl[i][j] = new Tile("tyles/tile_0" + to_string(i%10) + to_string(j % 10) + ".png", mouse);
			//pnl[i][j]->Scale(2,2);
			std::cout << pnl[i][j]->getSize().x << '\n';
			pnl[i][j]->init_border();
			if (j != 0) {
				pnl[i][j]->setPosition(pnl[i][j - 1]->getPosition().x + pnl[i][j - 1]->getSize().x+7, pnl[i][j - 1]->getPosition().y+pnl[i][j]->getSize().y*3/4);
				std::cout << "borders " << pnl[i][j]->borders->getSize().y << " " << pnl[i][j]->texture->getSize().y << '\n';
			}
			else
			{
				pnl[i][j]->setPosition(700, 800+i*pnl[i][j]->getSize().y);
				std::cout << "borders " << pnl[i][j]->borders->getSize().y << " " << pnl[i][j]->getSize().y << '\n';
			}
		}
	}
}

void TilePanel::draw()
{
	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			pnl[i][j]->draw();
		}
	}
}

bool TilePanel::click(SelectedTile* seltile)
{
	bool clicked = false;
	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			
			if (pnl[i][j]->Click())
			{
				seltile->loadTile(pnl[i][j]);
				std::cout << "Tile loaded\n";
				pnl[i][j]->clicked = false;
				clicked = true;
				return clicked;
			}
		}
	}
	return clicked;
}

void TilePanel::clickRight()
{
	cur->loadDefaultCur();
}


TilePanel::~TilePanel()
{
}
