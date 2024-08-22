#include "Menu.h"
#include "Game.h"
#include "Singleton.h"
#include "Animation.h"

bool WelcomeScene::verifyEvents(const sf::Event& event)
{
	switch (event.type)
	{
	case Event::Closed: {
		for (auto item : Singleton::instance().getPoolWindow())
		{
			item->close();
		}
		return false;
		break;
	}
	case Event::KeyPressed: {
		switch (event.key.scancode) {
		case Keyboard::W:
		{
			break;
		}
		}
		break;
	}
	case Event::MouseButtonPressed: {

		if (Singleton::instance().getMouse().isButtonPressed(Singleton::instance().getMouse().Left))
		{

			/*for (int i = 0; i < pool_button.size(); i++)
			{
				pool_button[i].get()->setActive();
			}*/
			for (auto c : Singleton::instance().getPoolButton())
			{
				c->setActive();
			}
		}
		break;
	}
	}
	return true;
}

void WelcomeScene::runEvents()
{
	buttonWork();
	for (auto i = anims.begin(); i != anims.end(); i++)
	{
		i->get()->changing();
	}
}

void WelcomeScene::drawing()
{
	Singleton::instance().getPoolWindow()[0]->clear(*Singleton::instance().getBackgroundColor());
	globalDraw();
	for (auto i = anims.begin(); i != anims.end(); i++)
	{
		i->get()->draw();
	}
	Singleton::instance().getPoolWindow()[0]->display();
}

void WelcomeScene::eventLoop()
{
	while (Singleton::instance().getPoolWindow()[0]->isOpen()) {
		Event event;
		while (Singleton::instance().getPoolWindow()[0]->pollEvent(event)) {
			if (!verifyEvents(event)) return;
		}
		
		runEvents();
		drawing();
		
	}
}

WelcomeScene::WelcomeScene()
{
	anims.emplace_back(std::make_unique<Animation>("images/flowers/sprite_flower", 9, 1, Singleton::instance().getPoolWindow()[0].get()));
	anims.emplace_back(std::make_unique<Animation>("images/flowers/sprite_flower", 9, 1, Singleton::instance().getPoolWindow()[0].get()));
	anims.emplace_back(std::make_unique<Animation>("images/tree/sprite_tree", 8, 1.5, Singleton::instance().getPoolWindow()[0].get()));
	anims.emplace_back(std::make_unique<Animation>("images/tree/sprite_tree", 8, 1.5, Singleton::instance().getPoolWindow()[0].get()));
	anims.emplace_back(std::make_unique<Animation>("images/star/sprite_star", 16, 2, Singleton::instance().getPoolWindow()[0].get()));
	anims[0]->moveTo(150, 400);
	anims[1]->moveTo(300, 400);
	anims[2]->moveTo(1100, 200);
	anims[3]->moveTo(1250, 500);
	anims[4]->moveTo(725, 175);
	anims[3]->scaleImage(5, 5);
	ButtonLoader(Singleton::instance().getPoolWindow()[0].get(), &Singleton::instance().getMouse(), *Singleton::instance().getMainColor(), "notes/buttons.json");
}
