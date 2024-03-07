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
	Tile*** ownmap;
public:
	Map(string symbol_map, Mouse* mouse);
	void draw() override;
	void click();
private:
	std::vector<string> splitter(string symbols);
};