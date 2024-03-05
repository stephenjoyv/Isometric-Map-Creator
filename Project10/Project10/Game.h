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
	DetectedImage();
	bool Click() override;
	void draw() override;
	void setActive() override;
	void isActive() override {};
	void Scale(int xmod, int ymod);
};
struct Tile: public DetectedImage {
	Tile(string str,Mouse* mouse);
	Tile();
	Tile(const Tile& m);
	Tile& operator=(const Tile& copy);
	~Tile() = default;
};
class Map:IBaseClass {
	int size[2];
	int tyle_size[2];
	Tile*** ownmap;
public:
	Map(string symbol_map, Mouse* mouse);
	void draw() override;
private:
	std::vector<string> splitter(string symbols);
};