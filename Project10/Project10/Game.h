#pragma once
#include "Libs.h"
#include "interfaceobj.h"
#include "Settings.h"
#include "Jammed.h"
#include "Playable.h"
#include "Menu.h"
using namespace std;
using namespace sf;

class Platform;
class Button;
class Jammed;
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
	void setPosition(float x, float y);
	void setOrigin(float x, float y);
	void setTarget(RenderTarget* target);
	void init_border();
	Vector2i getScale();
	Vector2f getPosition();
	Vector2f getSize();
	string getLink();
	bool Click() override;
	bool Click(const sf::View&) override;
	bool Click(int difference_x, int difference_y) override;
	void draw() override;
	void setActive() override;
	void setActive(const sf::View&) override;
	bool isActive() override;
	void Scale(int xmod, int ymod);
};
class EditorScene : public Scene {
	bool jammed;
	std::unique_ptr<sf::Text> text;
	std::unique_ptr<Jammed> jammable;
	std::unique_ptr<Platform> platform;
	//std::shared_ptr<Button> settingsImage;
protected:
	virtual bool verifyEvents(const sf::Event&) override;
	virtual void runEvents() override;
	virtual void drawing() override;
public:
	virtual void eventLoop() override;
	EditorScene();
	~EditorScene();
};