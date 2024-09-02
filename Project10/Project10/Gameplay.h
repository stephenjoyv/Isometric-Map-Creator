#pragma once
#include "Libs.h"
#include "Menu.h"
class Map;
class Playable;
class IBaseClass;
class Jammed;


class GameplayScene : public Scene
{
	std::shared_ptr<Map> map;
	std::tuple<int, int, int> clickArea;
	std::unique_ptr<Playable> player;
	std::vector<std::shared_ptr<IBaseClass>> objectsDrawable;
	std::unique_ptr<Jammed> jammable;
protected:
	virtual void drawing() override;
	virtual bool verifyEvents(const sf::Event& event) override;
	virtual void runEvents() override;
public:
	GameplayScene();
	~GameplayScene();
	void eventLoop();
};

