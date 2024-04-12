#pragma once
#include "Libs.h"
#include "interfaceobj.h"
#include "Settings.h"
#include "Jammed.h"
using namespace std;
using namespace sf;
void game();
struct DetectedImage :public Clicable {
protected:
	void update();
	bool is_bordered;
	string link;
	Vector2i scale;
public:
	Texture* texture;
	Sprite* sprite;
	Image* image;
	RenderTexture rtexture;
	RectangleShape* borders;
	bool clicked;
	DetectedImage(string str, Mouse* mouse);
	DetectedImage();
	void setPosition(int x, int y);
	void init_border();
	Vector2i getScale();
	Vector2f getPosition();
	Vector2f getSize();
	string getLink();
	bool Click() override;
	void draw() override;
	void setActive() override;
	void isActive() override {};
	void Scale(int xmod, int ymod);
};
