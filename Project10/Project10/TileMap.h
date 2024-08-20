#pragma once
#include "Game.h"
struct Tile : public DetectedImage {
private:
	int _size[2];
	int _index;
	bool _is_priority;
public:
	void setSize(int x, int y);
	Vector2i getInTileSize();
	void setPriority(bool priority);
	bool getPriority();
	Tile(string str, Mouse* mouse);
	Tile();
	Tile(const Tile& m);
	Tile& operator=(const Tile& copy);
};
class Map :IBaseClass {
	int size[2];
	int tile_size[2];
	int map_size[2];
	int default_tile_size;
	Tile**** ownmap;
	int** info_z;
	Mouse* ms;
	RenderTexture surface_tx;
	Sprite surface_sp;
public:
	Map(RenderTarget* targetToDraw, Mouse* mouse, int x, int y);
	Map(string symbol_map, Mouse* mouse);
	~Map();
	void reDraw();
	void draw() override;
	void click(std::tuple<int, int, int>& data);
	Tile* getTile(int x, int y);
	void setTile(Tile* tile, int x, int y, int z);
	void addTile(Tile* tile, int x, int y,int z);
	void deleteTile(int x, int y, int z);
	bool controlTile(int x, int y, int z);
	void clearMap();
	void saveMap();
	void loadMap(std::string link);
private:
	std::vector<string> splitter(string symbols);
};