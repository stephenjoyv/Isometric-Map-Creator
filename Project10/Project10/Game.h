#pragma once
#include "Libs.h"
#include "interfaceobj.h"
#include "Settings.h"
#include "Jammed.h"
#include "Playable.h"
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
	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<sf::Sprite> sprite;
	std::unique_ptr<sf::Image> image;
	std::unique_ptr<sf::RectangleShape> borders;
	RenderTexture rtexture;
	bool clicked;
	DetectedImage(string str, Mouse* mouse);
	DetectedImage();
	void setPosition(int x, int y);
	void setOrigin(int x, int y);
	void setTarget(RenderTarget* target);
	void init_border();
	Vector2i getScale();
	Vector2f getPosition();
	Vector2f getSize();
	string getLink();
	bool Click() override;
	bool Click(int difference_x, int difference_y) override;
	void draw() override;
	void setActive() override;
	bool isActive() override;
	void Scale(int xmod, int ymod);
};
