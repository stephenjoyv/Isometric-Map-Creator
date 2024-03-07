#include "TileMap.h"
void Map::draw()
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			ownmap[j][i]->draw();
		}

	}
}

void Map::click()
{
	bool clicked = false;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			ownmap[i][j]->setActive();
			if (ownmap[i][j]->clicked)
			{
				ownmap[i][j]->clicked = false;
				clicked = true;
				break;
			}
		}
		if (clicked) break;
	}
}

std::vector<string> Map::splitter(string symbols) {
	std::vector<string> m;
	string tmp = "";
	for (int i = 0; i < symbols.size(); i++)
	{
		if (symbols[i] != ' ')
		{
			tmp += symbols[i];
		}
		else
		{
			m.emplace_back(tmp);
			tmp = "";
		}
	}
	return m;
}
Tile& Tile::operator=(const Tile& copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
	return *this;
	// TODO: вставьте здесь оператор return
}
Tile::Tile(const Tile& m) {
	this->sprite = m.sprite;
	this->texture = m.texture;
	this->mouse = m.mouse;
	this->image = m.image;
	this->ObjTar = m.ObjTar;
}
Tile::Tile(string str, Mouse* mouse) : DetectedImage(str, mouse) {}
Tile::Tile()
{

}