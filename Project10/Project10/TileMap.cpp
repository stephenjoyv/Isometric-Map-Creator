#include "TileMap.h"
Map::Map(RenderTarget* targetToDraw, Mouse* mouse, int x, int y)
{
	ObjTar = targetToDraw;
	ms = mouse;
	size[0] = x;
	size[1] = y;
	Tile* tm = new Tile("tyles/tile_022.png", mouse);
	tile_size[0] = tm->getSize().x;
	tile_size[1] = tile_size[0];
	map_size[0] = size[0] * tile_size[0];
	map_size[1] = size[1] * tile_size[1];
	surface_tx.create(map_size[0], map_size[1]);
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
		ownmap[i][0][0]->setTarget(&surface_tx);
		//ownmap[i][0][0]->Scale(2, 2);
		if (i > 0) {
			int preposx = ownmap[i - 1][0][0]->sprite->getPosition().x, preposy = ownmap[i - 1][0][0]->sprite->getPosition().y;
			int presizex = ownmap[i - 1][0][0]->texture->getSize().x / 2;
			int presizey = ownmap[i - 1][0][0]->texture->getSize().y / 4;
			ownmap[i][0][0]->sprite->setPosition(preposx + presizex, preposy + presizey);
		}
		else {
			ownmap[i][0][0]->sprite->setPosition((surface_tx.getSize().x-ownmap[i][0][0]->getSize().x)/2.f, ownmap[i][0][0]->getSize().y*3.f/4);
		}
				
	}
	for (int i = 0; i < size[0]; i++)
	{
		for (int j = 1; j < size[1]; j++)
		{
			ownmap[i][j][0] = new Tile("tyles/tile_040.png", mouse);
			ownmap[i][j][0]->setTarget(&surface_tx);
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
	//���������� info_z
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
	//������� ownmap
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

	//������� info_z
	for (int i = 0; i < 40; i++)
	{
		delete info_z[i];
	}
	delete info_z;
}
void Map::reDraw()
{
	surface_tx.clear(sf::Color::Color(0, 0, 0, 0));
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
	surface_tx.display();
	surface_sp.setTexture(surface_tx.getTexture());
	//std::cout << "tyles drawned = " << t << '\n';
}
void Map::draw()
{
	ObjTar->draw(surface_sp);
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
	ownmap[x][y][z+1]->setTarget(&surface_tx);
	reDraw();
}

void Map::deleteTile(int x, int y,int z)
{

	//--info_z[x][y];
	if (z!=0)
	{
		ownmap[x][y][z] = nullptr;
	}
	//if (info_z[x][y] > 0) {
	//	//cout << "COMPONENTS ";
	//	nx = ownmap[x][y][z - 1]->getPosition().x;
	//	ny = ownmap[x][y][z - 1]->getPosition().y + ownmap[x][y][z - 1]->getSize().y / 2;
	//	cout << "NEW TILE POSITION | X : " << nx << " Y : " << ny << '\n';

	//}
	//else return;
	//ownmap[x][y][z]->setPosition(nx, ny);
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
	surface_tx.clear(sf::Color::Color(0, 0, 0, 0));
	surface_sp.setTexture(surface_tx.getTexture());
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
	//std::cout << "print\n";
	if (str.is_open()) {
		while (std::getline(str, line)) {
			//std::cout << "cwdaw\n";
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
					i += 3;
					while (*i != ' ') {
						tm += *i;
						i++;
					}
					x = atoi(tm.c_str());
					read_x = false;
				}
				if (read_y) {
					std::string tm;
					i += 3;
					while (*i != ' ') {
						tm += *i;
						i++;
					}
					y = atoi(tm.c_str());
					read_y = false;
				}
				if (read_z) {
					std::string tm;
					i += 3;
					while (*i != ' ') {
						tm += *i;
						i++;
					}
					z = atoi(tm.c_str());
					read_z = false;
				}
				if (read_t) {
					std::string tm;
					i += 3;
					while (i!=line.end() && *i != '\n' && *i != '\0') {
						tm += *i;
						i++;
					}
					lnk = tm;
					read_t = false;
					break;
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
			//cout << "COORDINATES | " << "x : " << x << " | " << "y : " << y << " | " << "z : " << z << '\n';
			ownmap[x][y][z] = new Tile{ lnk,ms };
			ownmap[x][y][z]->setTarget(&surface_tx);
			info_z[x][y] = z+1;
		}
	}

	if (ownmap[0][8][4])
	{
		ownmap[0][8][4]->getPosition();
		std::cout << "OWNMAP\n";
		
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
			ownmap[i][0][0]->sprite->setPosition((surface_tx.getSize().x - ownmap[i][0][0]->getSize().x) / 2.f, ownmap[i][0][0]->getSize().y * 3.f / 4);
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
	// TODO: �������� ����� �������� return
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

