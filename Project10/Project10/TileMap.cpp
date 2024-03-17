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

void Map::click(std::pair<int, int>&data)
{
	bool clicked = false;
	for (int i = 40-1; i >= 0; i--)
	{
		for (int j = 40-1; j >=0; j--)
		{
			ownmap[i][j]->setActive();
			//std::cout << ownmap[i][j]->getSize().x << '\n';
			if (ownmap[i][j]->clicked)
			{
				std::cout << "clicked tile x y " << i << " " << j << '\n';
				data.first = i; data.second = j;
				
				ownmap[i][j]->clicked = false;
				clicked = true;
				break; 
			}
		}
		if (clicked) break;
	}
	if (!clicked) {
		data = make_pair(-1, -1); 
		std::cout << "wasn't drawn click\n";
	}
}

Tile* Map::getTile(int x, int y)
{
	return ownmap[x][y];
}

void Map::setTile(Tile* tile,int x,int y)
{
	*ownmap[x][y] = *tile;
	std::cout << "hdhawdakdk\n";
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
	//std::cout << "part 1\n";
	if (this != &copy)
	{
		int x = 0, y = 0;
		

		if (this->texture!=nullptr)
		{
			
			delete this->texture;
		}
		if (this->sprite != nullptr) {
			x = this->sprite->getPosition().x, y = this->sprite->getPosition().y;
			delete this->sprite;
		}
		if (this->image != nullptr) {
			delete this->image;
		}

		

		this->texture = new Texture;
		this->sprite = new Sprite;
		this->image = new Image;


		*(this->texture) = *copy.texture;
		//std::cout << "part 2\n";
		*this->sprite = *copy.sprite;
		if(x!=0 && y!=0)this->sprite->setPosition(x, y);
		pool_window[0].get()->draw(*this->sprite);
		*this->image = *copy.image;
		//*this->borders = *copy.borders;
		this->clicked = 0;
		//this->is_bordered = copy.
		this->link = copy.link;
		std::cout << "copy pixel "<<  copy.image->getSize().x << '\n';
		std::cout << "orig pixel " << this->image->getSize().x<< '\n';
		std::cout << "LINK = " << this->link<<'\n';

		//*this = copy;
		//std::cout << "dwada\n";
	}
	//std::cout << "part 3\n";
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
	this->texture = nullptr;
	this->sprite = nullptr;
	this->image = nullptr;
	std::cout <<"sprite n = "<< (this->sprite != nullptr);
}