#include "TilePanel.h"
TilePanel::TilePanel(Vector2f size, Mouse* mouse) {
	size_x = size.x;
	size_y = size.y;
	ObjTar = pool_window[0].get();
	pnl = new DetectedImage * *[size_y];
	for (int i = 0; i < size_y; i++)
	{
		pnl[i] = new DetectedImage * [size_x];
		for (int j = 0; j < size_x; j++)
		{
			pnl[i][j] = new DetectedImage("tyles/tile_0" + to_string(i%10) + to_string(j % 10) + ".png", mouse);
			pnl[i][j]->Scale(2,2);
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

void TilePanel::click()
{
	bool clicked = false;
	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			pnl[i][j]->Click();
			if (pnl[i][j]->clicked)
			{
				if (cur != nullptr) delete cur;
				cur = new SelectedTile(pnl[i][j]->image);
				std::cout << "clicked (" << i << ", " << j << ")\n";
				cout << "image link is " << pnl[i][j]->getLink();
				pnl[i][j]->clicked = false;
				clicked = true;
				break;
			}
		}
		if (clicked) break;
	}
}

TilePanel::~TilePanel()
{
}
