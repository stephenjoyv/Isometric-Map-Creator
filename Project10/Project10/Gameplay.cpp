#include "Gameplay.h"
#include "TileMap.h"
#include "Playable.h"
void GameplayScene::drawing()
{
	Singleton::instance().getPoolWindow()[0].get()->clear(*Singleton::instance().getBackgroundColor());
	player->draw();
	map->draw();
	globalDraw();
	Singleton::instance().getPoolWindow()[0].get()->display();
}

bool GameplayScene::verifyEvents(const sf::Event& event)
{
	switch (event.type)
	{
	case Event::Closed: {
		return false;
	}
	case Event::KeyPressed: {
		switch (event.key.scancode) {
		case Keyboard::Scancode::A:
		{
			player->move(Playable::Direction::left, 15);
			break;
		}
		case Keyboard::Scancode::W:
		{
			player->move(Playable::Direction::up, 15);
			break;
		}
		case Keyboard::Scancode::S:
		{
			player->move(Playable::Direction::down, 15);
			break;
		}
		case Keyboard::Scancode::D:
		{
			player->move(Playable::Direction::right, 15);
			break;
		}
		}


		break;

	}
	case Event::MouseButtonReleased: {
		if (event.mouseButton.button == Singleton::instance().getMouse().Left) {
			jammable->disable();
		}
		break;
	}
	case Event::MouseButtonPressed: {
		if (Singleton::instance().getMouse().isButtonPressed(Singleton::instance().getMouse().Left))
		{
			jammable->enable();
			for (auto i : Singleton::instance().getPoolButton())
			{
				i.get()->setActive();
			}
		}
		break;
	}
	}
	return true;
}

void GameplayScene::runEvents()
{
	buttonWork();
	jammable->exec();
}

GameplayScene::GameplayScene()
{
	map = std::make_shared<Map>(Singleton::instance().getPoolWindow()[0].get(), &Singleton::instance().getMouse(), 64, 64);
	player = std::make_unique<Playable>(Singleton::instance().getPoolWindow()[0].get());
	player->load("images/lords_avatars/blu_1.png");
	jammable = std::make_unique<Jammed>( Singleton::instance().getFPS(),0.1,[this]() {
		map->click(clickArea);
		int x = std::get<0>(clickArea),
			y = std::get<1>(clickArea),
			z = std::get<2>(clickArea);
		if (x != -1 && y != -1 && z != -1)
		{
			//something to do	
		}
		} );
	objectsDrawable.push_back(map);
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::eventLoop()
{
	while (Singleton::instance().getPoolWindow()[0].get()->isOpen())
	{
		Event event;
		while (Singleton::instance().getPoolWindow()[0].get()->pollEvent(event)) {
			if (!verifyEvents(event)) return;
		}
		runEvents();
		drawing();
	}
}

