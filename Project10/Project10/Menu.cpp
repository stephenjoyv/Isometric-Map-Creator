#include "Menu.h"

void menu()
{
	//bool close_app;
	//RenderWindow* window = new RenderWindow(VideoMode(1610, 1000), "application");
	//close_app = false;
	//font_global = new Font;
	//font_global->loadFromFile("tt-squares-condensed-8.ttf");//EduNSWACTFoundation - Regular.ttf
	//color_main = new Color{ 85,52,218 };
	//bg_color = new Color{ 129, 191, 115 };
	//std::shared_ptr<RenderWindow> w(window);
	//pool_window.emplace_back(w);
	//FPS = 60;
	//pool_window[0]->setFramerateLimit(FPS);
	std::vector<unique_ptr<Animation>> anims;
	anims.emplace_back(std::make_unique<Animation>("images/flowers/sprite_flower", 9, 1, Singleton::instance().getPoolWindow()[0].get()));
	anims.emplace_back(std::make_unique<Animation>("images/flowers/sprite_flower", 9, 1, Singleton::instance().getPoolWindow()[0].get()));
	anims.emplace_back(std::make_unique<Animation>("images/tree/sprite_tree", 8, 1.5, Singleton::instance().getPoolWindow()[0].get()));
	anims.emplace_back(std::make_unique<Animation>("images/tree/sprite_tree", 8, 1.5, Singleton::instance().getPoolWindow()[0].get()));
	anims.emplace_back(std::make_unique<Animation>("images/star/sprite_star", 16, 2, Singleton::instance().getPoolWindow()[0].get()));
	/*Animation** anim_pool = new Animation * [5];
	anim_pool[0] = new Animation{ "images/flowers/sprite_flower",9,1,Singleton::instance().getPoolWindow()[0].get() };
	anim_pool[1] = new Animation{ "images/flowers/sprite_flower",9,1,Singleton::instance().getPoolWindow()[0].get() };
	anim_pool[2] = new Animation{ "images/tree/sprite_tree",8,1.5,Singleton::instance().getPoolWindow()[0].get() };
	anim_pool[3] = new Animation{ "images/tree/sprite_tree",8,1.5,Singleton::instance().getPoolWindow()[0].get() };
	anim_pool[4] = new Animation{ "images/star/sprite_star",16,2,Singleton::instance().getPoolWindow()[0].get() };*/
	anims[0]->moveTo(150, 400);
	anims[1]->moveTo(300, 400);
	anims[2]->moveTo(1100, 200);
	anims[3]->moveTo(1250, 500);
	anims[4]->moveTo(725, 175);
	anims[3]->scaleImage(5, 5);



	/*anim_pool[0]->moveTo(200, 200);
	anim_pool[1]->moveTo(200, 400);
	anim_pool[2]->moveTo(1100, 200);
	anim_pool[3]->moveTo(1250, 500);
	anim_pool[4]->moveTo(200, 600);
	anim_pool[3]->scaleImage(5, 5);*/
	Mouse mouse;
	ButtonLoader(Singleton::instance().getPoolWindow()[0].get(), &mouse, *Singleton::instance().getMainColor(), "notes/buttons.json");
	Singleton::instance().getPoolWindow()[0]->display();
	while (Singleton::instance().getPoolWindow()[0]->isOpen()) {
		Event event;
		while (Singleton::instance().getPoolWindow()[0]->pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed: {
				/*for (int i = 0; i < pool_window.size(); i++)
				{
					pool_window[i].get()->close();
				}*/
				for (auto c: Singleton::instance().getPoolWindow())
				{
					c->close();
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

					/*for (int i = 0; i < pool_button.size(); i++)
					{
						pool_button[i].get()->setActive();
					}*/
					for (auto c: Singleton::instance().getPoolButton())
					{
						c->setActive();
					}
				}
				break;
			}
			}

			//Sleep(5);

		}
		buttonWork();
		for (auto i = anims.begin(); i != anims.end();i++)
		{
			i->get()->changing();
		}
		
		/*for (size_t i = 0; i < 5; i++)
		{
			anim_pool[i]->changing();
		}*/
		//std::cout << '\n';
		//std::cout << "frame " << pool_pair[0].get()->getFrame() << '\n';
		//pool_window[0]->clear(*bg_color);
		Singleton::instance().getPoolWindow()[0]->clear(*Singleton::instance().getBackgroundColor());
		globalDraw();
		/*for (size_t i = 0; i < 5; i++)
		{
			anim_pool[i]->draw();
		}*/
		for (auto i = anims.begin(); i != anims.end(); i++)
		{
			i->get()->draw();
		}
		Singleton::instance().getPoolWindow()[0]->display();
	}
}
