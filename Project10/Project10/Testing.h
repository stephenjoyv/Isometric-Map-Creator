#pragma once
#include "Menu.h"
#include "interfaceobj.h"
class TileClickingZone;
class Testing : Scene
{
private:
	std::unique_ptr<TileClickingZone> object;
protected:
	virtual bool verifyEvents(const sf::Event&) override;
	virtual void runEvents() override;
	virtual void drawing() override;
public:
	virtual void eventLoop() override;
	Testing();
	~Testing();
};
class TileClickingZone : public Clicable {
private:
	std::unique_ptr<sf::Texture> objectTx;
	std::unique_ptr<sf::Sprite> objectSp;
	int leftFunction(int x);
	int rightFunction(int x);
public:
	bool Click() override;
	virtual void setActive() override;
	virtual bool isActive() override;
	void draw() override;
	void drawLines();


	TileClickingZone();
	~TileClickingZone();
};

