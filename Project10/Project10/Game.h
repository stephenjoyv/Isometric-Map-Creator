#pragma once
#include "Libs.h"
#include "interfaceobj.h"
using namespace std;
using namespace sf;
void game(sf::RenderTarget* window);
struct DetectedImage :public Clicable {
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