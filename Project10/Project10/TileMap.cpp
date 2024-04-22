#include "TileMap.h"
Map::Map(Mouse* mouse, int x, int y)
{

	ms = mouse;
	size[0] = x;
	size[1] = y;
	Tile* tm = new Tile("tyles/tile_022.png", mouse);
	tile_size[0] = tm->getSize().x;
	tile_size[1] = tile_size[0];
	delete tm;

	ownmap = new Tile * **[size[0]];
	for (int i = 0; i < 40; i++)
	{
		ownmap[i] = new Tile * *[size[1]];
		for (int k = 0; k < 40; k++)
		{
			ownmap[i][k] = new Tile * [64];
		}
	}

	for (int i = 0; i < size[0]; i++)
	{
		//Tile* tmp = new Tile("tyles/tile_022.png", mouse);
		ownmap[i][0][0] = new Tile("tyles/tile_022.png", mouse);
		ownmap[i][0][0]->setSize(1, 1);
		if (i > 0) {
			int preposx = ownmap[i - 1][0][0]->sprite->getPosition().x, preposy = ownmap[i - 1][0][0]->sprite->getPosition().y;
			int presizex = ownmap[i - 1][0][0]->texture->getSize().x / 2;
			int presizey = ownmap[i - 1][0][0]->texture->getSize().y / 4;
			ownmap[i][0][0]->sprite->setPosition(preposx + presizex, preposy + presizey);
		}
		else {
			ownmap[i][0][0]->sprite->setPosition(700, 50);
		}
	}
	for (int i = 0; i < size[0]; i++)
	{
		for (int j = 1; j < size[1]; j++)
		{
			ownmap[i][j][0] = new Tile("tyles/tile_040.png", mouse);
			int preposx = ownmap[i][j - 1][0]->sprite->getPosition().x, preposy = ownmap[i][j - 1][0]->sprite->getPosition().y;
			int presizex = ownmap[i][j - 1][0]->texture->getSize().x / 2;
			int presizey = ownmap[i][j - 1][0]->texture->getSize().y * 1 / 4;
			ownmap[i][j][0]->sprite->setPosition(preposx - presizex, preposy + presizey);
		}
	}
	/*for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++) {

			for (int k = 1; k < 2; k++)
			{
				ownmap[i][j][k] = new Tile("tyles/tile_01"+ to_string(k) + ".png", mouse);
				int preposx = ownmap[i][j][k - 1]->sprite->getPosition().x, preposy = ownmap[i][j][k - 1]->sprite->getPosition().y + ownmap[i][j][k - 1]->texture->getSize().y * 1 / 2;
				int presizex = ownmap[i][j][k-1]->texture->getSize().x;
				int presizey = ownmap[i][j][k - 1]->texture->getSize().y;
				ownmap[i][j][k]->sprite->setPosition(preposx, preposy - ownmap[i][j][k]->getSize().y*3/4);

			}
		}
	}*/
	//Заполнение info_z
	info_z = new int* [size[0]];
	for (int i = 0; i < 40; i++)
	{
		info_z[i] = new int[size[1]];
		for (int j = 0; j < 40; j++)
		{
			info_z[i][j] = 1;
		}
	}
}
Map::Map(string symbol_map, Mouse* mouse) {

}
Map::~Map()
{
	//Очистка ownmap
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			for (int k = 0; k < info_z[i][j]; k++)
			{
				delete ownmap[i][j][k];
			}
			delete ownmap[i][j];
		}
		delete ownmap[i];
	}
	delete ownmap;

	//Очистка info_z
	for (int i = 0; i < 40; i++)
	{
		delete info_z[i];
	}
	delete info_z;
}
void Map::draw()
{
	int t = 0;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			for (int k = 0; k < info_z[i][j]; k++)
			{
				ownmap[i][j][k]->draw();
				t++;
			}
			
		}

	}
	//std::cout << "tyles drawned = " << t << '\n';
}

void Map::click(std::tuple<int,int,int>&data)
{
	bool clicked = false;
	for (int i = 40-1; i >= 0; i--)
	{
		for (int j = 40-1; j >=0; j--)
		{
			int k = info_z[i][j]; 
			for (int z = k-1; z >= 0; z--)
			{
				ownmap[i][j][z]->setActive();
				//std::cout << ownmap[i][j]->getSize().x << '\n';
				if (ownmap[i][j][z]->clicked)
				{
					cout << "COORDINATES | " << "x : " << i << " | " << "y : " << j << " | " << "z : " << z << '\n';
					cout << "POSITION " << "X : " << ownmap[i][j][z]->getPosition().x << " Y : " << ownmap[i][j][z]->getPosition().y << '\n';
					data = std::tuple<int, int, int>{ i,j,z };


					ownmap[i][j][z]->clicked = false;
					
					clicked = true;
					break;
				}
			}
			if (clicked) break;		
		}
		if (clicked) break;
	}
	if (!clicked) {
		data = std::tuple<int, int, int>{ -1,-1,-1 };
		std::cout << "wasn't drawn click\n";
	}
}

Tile* Map::getTile(int x, int y)
{
	return ownmap[x][y][0];
}

void Map::setTile(Tile* tile,int x,int y,int z)
{
	*ownmap[x][y][z] = *tile;
	std::cout << "hdhawdakdk\n";
}

void Map::addTile(Tile* tile, int x, int y)
{
	++info_z[x][y];
	int z = info_z[x][y]-1;
	cout << "z is " << z << '\n';
	ownmap[x][y][z] = new Tile{};
	*ownmap[x][y][z] = *tile;
	int nx,ny;
	if (info_z[x][y] > 0) {
		//cout << "COMPONENTS ";
		nx = ownmap[x][y][z - 1]->getPosition().x;
		ny = ownmap[x][y][z - 1]->getPosition().y + ownmap[x][y][z - 1]->getSize().y / 2;
		cout << "NEW TILE POSITION | X : " << nx << " Y : " << ny << '\n';
		
	}
	else return;
	ownmap[x][y][z]->setPosition(nx,ny);
}

bool Map::controlTile(int x, int y, int z)
{
	if (z == info_z[x][y]) {
		return true;
	}
	return false;
}

void Map::clearMap()
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			for (int k = 0; k < info_z[i][j]; k++)
			{
				delete ownmap[i][j][k];
			}
		}
	}
}

void Map::saveMap()
{
	ofstream file;
	file.open("map.txt");
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			for ( int k = 0; k < info_z[i][j]; k++)
			{
				file << "X : " << i << " Y : " << j << " Z : " << k << " LINK : "<< ownmap[i][j][k]->getLink()<<'\n';
			}
		}
	}
	file.close();
}

void Map::loadMap(std::string link)
{
	std::string line;
	ifstream str{ link };
	/*ownmap = new Tile * **[size[0]];
	for (int i = 0; i < size[0]; i++)
	{
		ownmap[i] = new Tile * *[size[1]];
		for (int j = 0; j < size[1]; j++)
		{
			ownmap[i][j] = new Tile * [64];
		}
	}*/
	clearMap();

	if (str.is_open()) {
		while (std::getline(str, line)) {
			bool read_x = false,
				read_y = false,
				read_z = false,
				read_t = false;
			int x, y, z;
			std::string lnk;
			for (auto i = line.begin(); i < line.end(); i++)
			{
				if (read_x) {
					std::string tm;
					i += 4;
					while (*i != ' ') {
						tm += *i;
						i++;
					}
					x = atoi(tm.c_str());
					read_x = false;
				}
				if (read_y) {
					std::string tm;
					i += 4;
					while (*i != ' ') {
						tm += *i;
						i++;
					}
					y = atoi(tm.c_str());
					read_y = false;
				}
				if (read_z) {
					std::string tm;
					i += 4;
					while (*i != ' ') {
						tm += *i;
						i++;
					}
					z = atoi(tm.c_str());
					read_z = false;
				}
				if (read_t) {
					std::string tm;
					i += 4;
					while (*i != '\n' && *i != -1) {
						tm += *i;
						i++;
					}
					lnk = tm;
					read_t = false;
				}



				if (*i == 'X') read_x = true;
				else if (*i == 'Y') {
					read_y = true;
				}
				else if (*i == 'Z') {
					read_z = true;
				}
				else if (*i == 'K') {
					read_t = true;
				}

			}
			ownmap[x][y][z] = new Tile{ lnk,ms };
			info_z[x][y] = z+1;
		}
	}
	str.close();
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

		this->mouse = copy.mouse;
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
		cout << "was copied\n";
	}
	//std::cout << "part 3\n";
	return *this;
	// TODO: вставьте здесь оператор return
}
Tile::~Tile()
{
	if (this->texture != nullptr)delete this->texture;
	if (this->sprite != nullptr)delete this->sprite;
	if (this->image != nullptr)delete this->image;
}
Tile::Tile(const Tile& m) {
	this->sprite = m.sprite;
	this->texture = m.texture;
	this->mouse = m.mouse;
	this->image = m.image;
	this->ObjTar = m.ObjTar;
}
void Tile::setSize(int x, int y)
{
	_size[0] = x; _size[1] = y;
}
Vector2i Tile::getInTileSize()
{
	return Vector2i(_size[0],_size[1]);
}
void Tile::setPriority(bool priority)
{
	_is_priority = priority;
}
bool Tile::getPriority()
{
	return _is_priority;
}
Tile::Tile(string str, Mouse* mouse) : DetectedImage(str, mouse) {
	_is_priority = false;
}
Tile::Tile()
{

}

