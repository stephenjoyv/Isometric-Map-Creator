#pragma once
#include "Libs.h"
#include "TileMap.h"
#include "Platform.h"
class Gameplay
{
	sf::Mouse mouse;
	std::shared_ptr<Map> map;
	std::tuple<int, int, int> clickArea;
	std::shared_ptr<Playable> player;
	std::vector<std::shared_ptr<IBaseClass>> objectsDrawable;
	Jammed* jm;
protected:
	virtual void drawing();
	virtual bool verifyEvents(const sf::Event& event);
	virtual void runEvents();
public:
	Gameplay();
	void eventLoop();
};

