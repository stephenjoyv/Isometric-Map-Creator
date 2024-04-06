#include "Header.h"
std::vector<std::shared_ptr<Button>> pool_button;
std::vector<std::shared_ptr<RenderWindow>> pool_window;
Font* font_global;
int FPS;
Color* color_main;
Color* bg_color;

int main() {

	//Задаём параметры основным переменным
	RenderWindow* window = new RenderWindow(VideoMode(1610, 1000), "application");
	font_global = new Font;
	font_global->loadFromFile("EduNSWACTFoundation-Regular.ttf");
	color_main = new Color{50,50,80};
	bg_color = new Color{ 80,90,20 };
	std::shared_ptr<RenderWindow> w(window);
	pool_window.emplace_back(w);
	FPS = 60;
	pool_window[0]->setFramerateLimit(FPS);
	
	Mouse mouse;
	ButtonLoader(window, &mouse, *color_main,"notes/buttons.json");
	pool_window[0]->display();
	while (pool_window[0]->isOpen()) {
		Event event;
		while (pool_window[0]->pollEvent(event)) {
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
		buttonWork();
		//std::cout << '\n';
		//std::cout << "frame " << pool_pair[0].get()->getFrame() << '\n';

		pool_window[0]->clear(*bg_color);
		globalDraw();
		pool_window[0]->display();
	}
	pool_button.clear();
	pool_window.clear();
	delete font_global;
	delete color_main;
	delete bg_color;
	return 0;
}
