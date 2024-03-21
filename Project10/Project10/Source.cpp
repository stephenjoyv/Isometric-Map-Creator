#include "Header.h"
std::vector<std::shared_ptr<Button>> pool_button;
std::vector<std::shared_ptr<RenderWindow>> pool_window;
Font font_global;

int main() {
	
	RenderWindow* window = new RenderWindow(VideoMode(1610, 1000), "application");
	font_global.loadFromFile("EduNSWACTFoundation-Regular.ttf");
	std::shared_ptr<RenderWindow> w(window);
	pool_window.emplace_back(w);
	pool_window[0].get()->setFramerateLimit(60);
	Mouse mouse;
	ButtonLoader(window, &mouse, Color::Color(50, 50, 80));
	pool_window[0].get()->display();
	while (pool_window[0].get()->isOpen()) {
		Event event;
		while (pool_window[0].get()->pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed: {
				for (int i = 0; i < pool_window.size(); i++)
				{
					pool_window[i].get()->close();
				}
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

				if (mouse.isButtonPressed(mouse.Left))
				{

					for (size_t i = 0; i < pool_button.size(); i++)
					{
						pool_button[i].get()->setActive();
					}

				}
				break;
			}
			}
			
			//Sleep(5);
			
		}
		for (size_t i = 0; i < pool_button.size(); i++)
		{
			pool_button[i].get()->isActive();
		}
		//std::cout << '\n';
		//std::cout << "frame " << pool_pair[0].get()->getFrame() << '\n';
		pool_window[0].get()->clear();
		globalDraw();
		pool_window[0].get()->display();
	}
	


	return 0;
}
