#include "Settings.h"

void settings() {
	
	std::cout << "settings size " << Singleton::instance().getPoolButton().size() <<'\n';
	for (auto c = Singleton::instance().getPoolButton().begin(); c < Singleton::instance().getPoolButton().end();)
	{
		if (!((*c)->getId().compare("game")))
		{
			c = Singleton::instance().getPoolButton().erase(c);
		}
		else c++;
	}
	cout << "setting runs\n";
	Event event;
	std::unique_ptr<sf::Mouse> mouse = std::make_unique<sf::Mouse>();
	auto sne = Singleton::instance().getPoolButton().end()- Singleton::instance().getPoolButton().begin();
	
	ButtonLoader(Singleton::instance().getPoolWindow()[0].get(), mouse.get(), *Singleton::instance().getMainColor(), "notes/settings.json");
	
	
	//Singleton::instance().getPoolButton()[4]->;
	bool leftJammed = false;
	std::unique_ptr<ColorSel> RectColor = std::make_unique<ColorSel>(500,100,400,400);
	std::unique_ptr<SliderBar> sb = std::make_unique<SliderBar>(500, 55, 605, 700, Singleton::instance().getPoolWindow()[0].get(), 0, Color::Color(80, 10, 10), mouse.get());
	std::unique_ptr<SliderBar> sb1 = std::make_unique<SliderBar>(500, 55, 605, 755, Singleton::instance().getPoolWindow()[0].get(), 0, Color::Color(10, 80, 10), mouse.get());
	std::unique_ptr<SliderBar> sb2 = std::make_unique<SliderBar>(500, 55, 605, 810, Singleton::instance().getPoolWindow()[0].get(), 0, Color::Color(10, 10, 80), mouse.get());
	Singleton::instance().getPoolButton()[sne]->setRunFunction([&sb]() {
		auto load_colors = [](std::unique_ptr<sf::Color>& main, std::unique_ptr<sf::Color>& bg) {
			n::json obj;
			std::fstream File;
			File.open("notes/colors.json");
			std::cout << "file is open " << File.is_open() << '\n';
			File >> obj;
			std::cout << obj["colors"].size();
			main.reset(new sf::Color(
				static_cast<int>(obj["colors"]["main"]["red"]),
				static_cast<int>(obj["colors"]["main"]["green"]),
				static_cast<int>(obj["colors"]["main"]["blue"])));
			bg.reset(new sf::Color(
				static_cast<int>(obj["colors"]["background"]["red"]),
				static_cast<int>(obj["colors"]["background"]["green"]),
				static_cast<int>(obj["colors"]["background"]["blue"])));
			};
		load_colors(Singleton::instance().getMainColor(), Singleton::instance().getBackgroundColor());

		});
	
	
	
	Singleton::instance().getPoolButton()[sne + 1]->setRunFunction([&RectColor]() {Singleton::instance().getBackgroundColor().reset(new sf::Color(RectColor->getColor())); });
	Singleton::instance().getPoolButton()[sne]->setId("settings");
	Singleton::instance().getPoolButton()[sne + 1]->setId("settings");

	while (Singleton::instance().getPoolWindow()[0].get()->isOpen()) {
		while (Singleton::instance().getPoolWindow()[0].get()->pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed: {
				for (auto c = Singleton::instance().getPoolButton().begin(); c < Singleton::instance().getPoolButton().end();)
				{
					if (!((*c)->getId().compare("settings"))) {
						//std::cout << "||| er ||| " << c->get()->getId()<<'\n';
						c = Singleton::instance().getPoolButton().erase(c);
						
						
					} 
					else c++;
				}
				std::cout << "pool button size " << Singleton::instance().getPoolButton().size() << '\n';
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
			RectColor->changeColor(sf::Color(sb->getPercent() * 255, sb1->getPercent() * 255, sb2->getPercent() * 255));
			
		}


		buttonWork();
		Singleton::instance().getPoolWindow()[0]->clear(*Singleton::instance().getBackgroundColor());
		//pool_window[0].get()->clear(*bg_color);
		globalDraw();
		sb->draw();
		sb1->draw();
		sb2->draw();
		RectColor->draw();
		//pool_window[0].get()->display();
		Singleton::instance().getPoolWindow()[0]->display();


	}
}
