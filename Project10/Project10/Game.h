#pragma once
#include "Libs.h"
#include "interfaceobj.h"
using namespace std;
using namespace sf;
void game(sf::RenderTarget* window);
struct DetectedImage:public Clicable {
protected:
	void update();
public:
	Texture* texture;
	Sprite* sprite;
	Image* image;
	RenderTexture rtexture;
	DetectedImage(string str, Mouse* mouse);
	bool Click() override;
	void draw() override;
	void setActive() override;
	void isActive() override {};
	void Scale(int xmod, int ymod);
};
struct Tile: public DetectedImage {
	Tile(string str,Mouse* mouse);
};
class Map {
	int size[2];
	int tyle_size[2];
public:
	Map(string symbol_map, int tyle_size[], Mouse* mouse);
private:
	std::vector<string> splitter(string symbols);
};