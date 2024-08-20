#include "Settings.h"

void settings() {
	Singleton::instance().getPoolButton().clear();
	cout << "setting runs\n";
	Event event;
	Mouse* mouse = new Mouse;
	ButtonLoader(Singleton::instance().getPoolWindow()[0].get(), mouse, *Singleton::instance().getMainColor(), "notes/settings.json");
	bool leftJammed = false;
	SliderBar* sb = new SliderBar{ 300,200,400,300,Singleton::instance().getPoolWindow()[0].get(),0,Color::Color(80,10,10),mouse };
	SliderBar* sb1 = new SliderBar{ 300,200,400,500,Singleton::instance().getPoolWindow()[0].get(),0,Color::Color(10,80,10),mouse };
	SliderBar* sb2 = new SliderBar{ 300,200,400,700,Singleton::instance().getPoolWindow()[0].get(),0,Color::Color(10,10,80),mouse };
	while (Singleton::instance().getPoolWindow()[0].get()->isOpen()) {
		while (Singleton::instance().getPoolWindow()[0].get()->pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed: {
				Singleton::instance().getPoolButton().clear();
				return;
				//pool_window[0].get()->close();
			}
			case Event::MouseButtonPressed: {
				if (mouse->isButtonPressed(Mouse::Left)) {
					leftJammed = true;
					for (auto c: Singleton::instance().getPoolButton()) {
						c->setActive();
					}
					
				}
				break;

			}
			case Event::MouseButtonReleased: {
				if (event.mouseButton.button = Mouse::Left) {
					leftJammed = false;
				}
			}
			}
		}

		if (leftJammed) {
			sb->setActive();
			sb1->setActive();
			sb2->setActive();
		}


		buttonWork();
		Singleton::instance().getPoolWindow()[0]->clear(*Singleton::instance().getBackgroundColor());
		//pool_window[0].get()->clear(*bg_color);
		globalDraw();
		sb->draw();
		sb1->draw();
		sb2->draw();
		//pool_window[0].get()->display();
		Singleton::instance().getPoolWindow()[0]->display();


	}
}
