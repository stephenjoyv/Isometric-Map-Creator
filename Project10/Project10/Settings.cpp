#include "Settings.h"
void settings() {
	pool_button.clear();
	cout << "setting runs\n";
	Event event;
	Mouse* mouse = new Mouse;
	ButtonLoader(pool_window[0].get(), mouse, Color::Color(50, 50, 80), "notes/settings.json");
	while (pool_window[0].get()->isOpen()) {
		while (pool_window[0].get()->pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed: {
				pool_window[0].get()->close();
			}
			case Event::MouseButtonPressed: {
				if (mouse->isButtonPressed(Mouse::Left)) {
					for (size_t i = 0; i < pool_button.size(); i++)
					{
						pool_button[i].get()->setActive();
					}
				}
				break;

			}
			}
		}

		buttonWork();
		pool_window[0].get()->clear();
		globalDraw();

		pool_window[0].get()->display();


	}
}