#include "TileMap.h"

Map::Map(string symbol_map, Mouse* mouse) {
	ownmap = new Tile * *[40];
	for (int i = 0; i < 40; i++)
	{
		ownmap[i] = new Tile * [40];
	}

	for (int i = 0; i < 40; i++)
	{
		//Tile* tmp = new Tile("tyles/tile_022.png", mouse);
		ownmap[i][0] = new Tile("tyles/tile_022.png", mouse);
		if (i > 0) {
			int preposx = ownmap[i - 1][0]->sprite->getPosition().x, preposy = ownmap[i - 1][0]->sprite->getPosition().y;
			int presizex = ownmap[i - 1][0]->texture->getSize().x / 2;
			int presizey = ownmap[i - 1][0]->texture->getSize().y / 4;
			ownmap[i][0]->sprite->setPosition(preposx + presizex, preposy + presizey);
		}
		else {
			ownmap[i][0]->sprite->setPosition(500, 0);
		}
	}
	for (int i = 0; i < 40; i++)
	{
		for (int j = 1; j < 40; j++)
		{
			ownmap[i][j] = new Tile("tyles/tile_0" + to_string(j % 10) + "5.png", mouse);
			if (i > 0) {
				int preposx = ownmap[i][j - 1]->sprite->getPosition().x, preposy = ownmap[i][j - 1]->sprite->getPosition().y;
				int presizex = ownmap[i][j - 1]->texture->getSize().x / 2;
				int presizey = ownmap[i][j - 1]->texture->getSize().y * 1 / 4;
				ownmap[i][j]->sprite->setPosition(preposx - presizex, preposy + presizey);
			}
		}
	}

}

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
