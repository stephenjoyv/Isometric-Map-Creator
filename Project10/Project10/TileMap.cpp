#include "TileMap.h"
#include "boost/algorithm/string.hpp"
#include "boost/lexical_cast.hpp"
Map::Map(RenderTarget* targetToDraw, Mouse* mouse, int x, int y)
{
	ObjTar = targetToDraw;
	ms = mouse;
	surface_tx = std::make_unique<sf::RenderTexture>();
	surface_sp = std::make_unique<sf::Sprite>();
	size[0] = x;
	size[1] = y;
	Tile* tm = new Tile("tyles/tile_022.png", mouse);
	tile_size[0] = tm->getSize().x;
	tile_size[1] = tile_size[0];
	map_size[0] = size[0] * tile_size[0];
	map_size[1] = size[1] * tile_size[1];
	surface_tx->create(map_size[0], map_size[1]);
	delete tm;

	ownmap = new Tile * **[size[0]];
	for (int i = 0; i < 40; i++)
	{
		ownmap[i] = new Tile * *[size[1]];
		for (int k = 0; k < 40; k++)
		{
			ownmap[i][k] = new Tile * [64];
			for (int j = 0; j<64;j++)
			{
				ownmap[i][k][j] = nullptr;
			}
		}
	}

	for (int i = 0; i < size[0]; i++)
	{
		//Tile* tmp = new Tile("tyles/tile_022.png", mouse);
		ownmap[i][0][0] = new Tile("tyles/tile_022.png", mouse);
		ownmap[i][0][0]->setSize(1, 1);
		ownmap[i][0][0]->setTarget(surface_tx.get());
		//ownmap[i][0][0]->Scale(2, 2);
		if (i > 0) {
			int preposx = ownmap[i - 1][0][0]->sprite->getPosition().x, preposy = ownmap[i - 1][0][0]->sprite->getPosition().y;
			int presizex = ownmap[i - 1][0][0]->texture->getSize().x / 2;
			int presizey = ownmap[i - 1][0][0]->texture->getSize().y / 4;
			ownmap[i][0][0]->sprite->setPosition(preposx + presizex, preposy + presizey);
		}
		else {
			ownmap[i][0][0]->sprite->setPosition((surface_tx->getSize().x-ownmap[i][0][0]->getSize().x)/2.f, ownmap[i][0][0]->getSize().y*3.f/4);
		}
				
	}
	for (int i = 0; i < size[0]; i++)
	{
		for (int j = 1; j < size[1]; j++)
		{
			ownmap[i][j][0] = new Tile("tyles/tile_040.png", mouse);
			ownmap[i][j][0]->setTarget(surface_tx.get());
			//ownmap[i][j][0]->Scale(2, 2);
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
	reDraw();
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
void Map::reDraw()
{
	surface_tx->clear(sf::Color::Color(0, 0, 0, 0));
	int t = 0;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			for (int k = 0; k < info_z[i][j]; k++)
			{
				if (ownmap[i][j][k])
				{
					ownmap[i][j][k]->draw();
					t++;
				}
			}

		}

	}
	surface_tx->display();
	surface_sp->setTexture(surface_tx->getTexture());
	//std::cout << "tyles drawned = " << t << '\n';
}
void Map::draw()
{
	ObjTar->draw(*surface_sp);
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
				if (ownmap[i][j][z])
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

void Map::addTile(Tile* tile, int x, int y, int z)
{
	if (z == info_z[x][y]-1)
	{
		++info_z[x][y];
	}
	
	cout << "z is " << z << '\n';
	cout << "info z " << info_z[x][y] << '\n';
	ownmap[x][y][z+1] = new Tile{};
	*ownmap[x][y][z+1] = *tile;
	int nx,ny;
	if (info_z[x][y] > 0) {
		//cout << "COMPONENTS ";
		nx = ownmap[x][y][z]->getPosition().x;
		ny = ownmap[x][y][z]->getPosition().y + ownmap[x][y][z]->getSize().y / 2;
		cout << "NEW TILE POSITION | X : " << nx << " Y : " << ny << '\n';
		
	}
	else return;
	ownmap[x][y][z+1]->setPosition(nx,ny);
	ownmap[x][y][z+1]->setTarget(surface_tx.get());
	reDraw();
}

void Map::deleteTile(int x, int y,int z)
{
	if (z!=0)
	{
		ownmap[x][y][z] = nullptr;
	}
	reDraw();
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
				ownmap[i][j][k] = nullptr;
			}
		}
	}
	surface_tx->clear(sf::Color::Color(0, 0, 0, 0));
	surface_sp->setTexture(surface_tx->getTexture());
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
				if (ownmap[i][j][k])
				{
					file << "X : " << i << " Y : " << j << " Z : " << k << " LINK : " << ownmap[i][j][k]->getLink() << '\n';
				}
			}
		}
	}
	file.close();
}

void Map::loadMap(std::string link)
{
	std::string line;
	ifstream str{ link };
	clearMap();
	if (str.is_open()) {
		while (std::getline(str, line)) {
			std::vector<std::string> data;
			boost::split(data, line, boost::is_any_of(" "));
			int x = boost::lexical_cast<int>(data[2]),
				y = boost::lexical_cast<int>(data[5]),
				z = boost::lexical_cast<int>(data[8]);
			std::string link = data[11];
			ownmap[x][y][z] = new Tile{link,ms};
			ownmap[x][y][z]->setTarget(surface_tx.get());
			info_z[x][y] = z+1;
		}
	}
	str.close();
	for (int i = 0; i < size[0]; i++)
	{
		//Tile* tmp = new Tile("tyles/tile_022.png", mouse);
		ownmap[i][0][0]->setSize(ownmap[i][0][0]->getSize().x, ownmap[i][0][0]->getSize().y);
		if (i > 0) {
			int preposx = ownmap[i - 1][0][0]->sprite->getPosition().x, preposy = ownmap[i - 1][0][0]->sprite->getPosition().y;
			int presizex = ownmap[i - 1][0][0]->texture->getSize().x / 2;
			int presizey = ownmap[i - 1][0][0]->texture->getSize().y / 4;
			ownmap[i][0][0]->sprite->setPosition(preposx + presizex, preposy + presizey);
		}
		else {
			ownmap[i][0][0]->sprite->setPosition((surface_tx->getSize().x - ownmap[i][0][0]->getSize().x) / 2.f, ownmap[i][0][0]->getSize().y * 3.f / 4);
		}
	}
	for (int i = 0; i < size[0]; i++)
	{
		for (int j = 1; j < size[1]; j++)
		{
			for (int k = 0; k < info_z[i][j];k++) {
				if (ownmap[i][j][k]!=nullptr)
				{
					if (k == 0) {
						int preposx = ownmap[i][j - 1][k]->sprite->getPosition().x, preposy = ownmap[i][j - 1][k]->sprite->getPosition().y;
						int presizex = ownmap[i][j - 1][k]->texture->getSize().x / 2;
						int presizey = ownmap[i][j - 1][k]->texture->getSize().y * 1 / 4;
						ownmap[i][j][k]->sprite->setPosition(preposx - presizex, preposy + presizey);
					}
					else {
						int preposx = ownmap[i][j][0]->sprite->getPosition().x; //preposy = ownmap[i][j][0]->sprite->getPosition().y - (ownmap[i][j][0]->texture->getSize().y * 1 / 2)*(k-1);
						int presizex = ownmap[i][j][0]->texture->getSize().x;
						int presizey = ownmap[i][j][0]->texture->getSize().y;
						ownmap[i][j][k]->sprite->setPosition(preposx, ownmap[i][j][0]->sprite->getPosition().y - ownmap[i][j][0]->texture->getSize().y*(1.f/4)*k);
					}
				}
			}
			
		}
	}
	reDraw();



	
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
		texture.reset();
		sprite.reset();
		image.reset();


		this->mouse = copy.mouse;
		texture = std::unique_ptr<sf::Texture>(new sf::Texture{ *copy.texture });
		sprite = std::unique_ptr<sf::Sprite>(new sf::Sprite{ *copy.sprite });
		image = std::unique_ptr<sf::Image>(new sf::Image{ *copy.image });
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

Tile::Tile(const Tile& m) {
	/*sprite.reset();
	sprite = std::make_unique<sf::Sprite>(m.sprite);
	texture.reset();
	texture = std::make_unique<sf::Texture>(m.texture);
	image.reset();
	image = std::make_unique<sf::Image>(m.image);*/
	this->mouse = m.mouse;
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

