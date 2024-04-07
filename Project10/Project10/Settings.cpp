#include "Settings.h"

void settings() {
	pool_button.clear();
	cout << "setting runs\n";
	Event event;
	Mouse* mouse = new Mouse;
	ButtonLoader(pool_window[0].get(), mouse, *color_main, "notes/settings.json");
	bool leftJammed = false;
	SliderBar* sb = new SliderBar{ 300,200,400,300,pool_window[0].get(),0,Color::Color(80,10,10),mouse };
	SliderBar* sb1 = new SliderBar{ 300,200,400,500,pool_window[0].get(),0,Color::Color(10,80,10),mouse };
	SliderBar* sb2 = new SliderBar{ 300,200,400,700,pool_window[0].get(),0,Color::Color(10,10,80),mouse };
	while (pool_window[0].get()->isOpen()) {
		while (pool_window[0].get()->pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed: {
				pool_window[0].get()->close();
			}
			case Event::MouseButtonPressed: {
				if (mouse->isButtonPressed(Mouse::Left)) {
					leftJammed = true;
					for (size_t i = 0; i < pool_button.size(); i++)
					{
						pool_button[i].get()->setActive();
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
		pool_window[0].get()->clear(*bg_color);
		globalDraw();
		sb->draw();
		sb1->draw();
		sb2->draw();
		pool_window[0].get()->display();


	}
}
