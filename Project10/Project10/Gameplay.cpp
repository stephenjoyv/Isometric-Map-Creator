#include "Gameplay.h"

void Gameplay::drawing()
{
	Singleton::instance().getPoolWindow()[0].get()->clear(*Singleton::instance().getBackgroundColor());
	player->draw();
	map->draw();
	globalDraw();

	Singleton::instance().getPoolWindow()[0].get()->display();
}

bool Gameplay::verifyEvents(const sf::Event& event)
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
		if (event.mouseButton.button == mouse.Left) {
			jm->disable();
		}
		break;
	}
	case Event::MouseButtonPressed: {
		if (mouse.isButtonPressed(mouse.Left))
		{
			jm->enable();
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

void Gameplay::runEvents()
{
	buttonWork();
	jm->exec();
}

Gameplay::Gameplay()
{
	map = std::make_shared<Map>(Singleton::instance().getPoolWindow()[0].get(), &mouse, 40, 40);
	player = std::make_unique<Playable>(Singleton::instance().getPoolWindow()[0].get());
	player->load("images/lords_avatars/blu_1.png");
	jm = new Jammed{ Singleton::instance().getFPS(),0.1,[this]() {
		map->click(clickArea);
		int x = std::get<0>(clickArea),
			y = std::get<1>(clickArea),
			z = std::get<2>(clickArea);
		if (x != -1 && y != -1 && z != -1)
		{
			//something to do	
		}
		} };
	objectsDrawable.push_back(map);

}

void Gameplay::eventLoop()
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

