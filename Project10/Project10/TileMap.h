#pragma once
#include "Game.h"
struct Tile : public DetectedImage {
	Tile(string str, Mouse* mouse);
	Tile();
	Tile(const Tile& m);
	Tile& operator=(const Tile& copy);
	~Tile() = default;
};
class Map :IBaseClass {
	int size[2];
	int tyle_size[2];
	Tile**** ownmap;
	int **info_z;
public:
	Map(string symbol_map, Mouse* mouse);
	~Map();
	void draw() override;
	void click(std::pair<int, int>& data);
	Tile* getTile(int x,int y);
	void setTile(Tile* tile, int x, int y);
private:
	std::vector<string> splitter(string symbols);
};