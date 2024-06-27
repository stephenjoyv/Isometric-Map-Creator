#include "Header.h"
#include "Game.h"
std::vector<std::shared_ptr<Button>> pool_button;
std::vector<std::shared_ptr<RenderWindow>> pool_window;
Font* font_global;
int FPS;
bool close_app;
Color* color_main;
Color* bg_color;

int main() {
	//Задаём параметры основным переменным
	RenderWindow* window = new RenderWindow(VideoMode(1610, 1000), "application");
	close_app = false;
	font_global = new Font;
	font_global->loadFromFile("tt-squares-condensed-8.ttf");//EduNSWACTFoundation - Regular.ttf
	color_main = new Color{ 85,52,218 };
	bg_color = new Color{ 129, 191, 115 };
	std::shared_ptr<RenderWindow> w(window);
	pool_window.emplace_back(w);
	FPS = 60;
	pool_window[0]->setFramerateLimit(FPS);
	Animation** anim_pool = new Animation *[3] ;
	anim_pool[0] = new Animation{"images/flowers/sprite_flower",9,1,window};
	anim_pool[1] = new Animation{ "images/flowers/sprite_flower",9,1,window };
	anim_pool[2] = new Animation{ "images/tree/sprite_tree",8,1.5,window };
	anim_pool[0]->moveTo(200, 200);
	anim_pool[1]->moveTo(200, 400);
	anim_pool[2]->moveTo(1100, 200);
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

					for (int i = 0; i < pool_button.size(); i++)
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
		for (size_t i = 0; i < 3; i++)
		{
			anim_pool[i]->changing();
		}
		//std::cout << '\n';
		//std::cout << "frame " << pool_pair[0].get()->getFrame() << '\n';
		pool_window[0]->clear(*bg_color);
		globalDraw();
		for (size_t i = 0; i < 3; i++)
		{
			anim_pool[i]->draw();
		}
		pool_window[0]->display();
	}
	pool_button.clear();
	pool_window.clear();
	delete font_global;
	delete color_main;
	delete bg_color;
	return 0;
}
