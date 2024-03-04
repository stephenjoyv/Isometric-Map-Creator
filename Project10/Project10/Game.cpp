#include "Game.h"
#include "interfaceobj.h"
using namespace std;
using namespace sf;

DetectedImage::DetectedImage(string str,Mouse* mouse) {
	ObjTar = pool_window[0].get();
	image = new Image;
	texture = new Texture;
	sprite = new Sprite;
	this->mouse = mouse;
	std::cout << "load is "<< image->loadFromFile(str.c_str());
	texture->loadFromImage(*image);
	sprite->setTexture(*texture);
	sprite->setOrigin(0, texture->getSize().y*3/4);
}
void DetectedImage::Scale(int xmod, int ymod) {
	Image* tempimage = new Image;
	tempimage->create(160, 160);
	std::cout << tempimage->getSize().x;
	for (int i = 0; i < image->getSize().x; i++)
	{
		int loadedpix = 0;
		for (int j = 0; j < image->getSize().y; j++)
		{
			for (int m = 0; m < ymod; m++)
			{
				tempimage->setPixel(i + (xmod - 1) * i, j + m + (ymod - 1) * j, image->getPixel(i, j));

			}
		}
		for (int j = 0; j < image->getSize().y * ymod; j++)
		{
			for (int t = 0; t < xmod; t++)
			{
				tempimage->setPixel(i + i * (xmod - 1) + t, j, tempimage->getPixel(i + i * (xmod - 1), j));
			}
		}

	}
	delete texture, sprite,image;
	image = tempimage;
	texture = new Texture;
	texture->loadFromImage(*tempimage);
	sprite = new Sprite;
	sprite->setTexture(*texture);
	sprite->setOrigin(0, texture->getSize().y * 3 / 4);
	sprite->setPosition(texture->getSize().x / 2, texture->getSize().y);

}
void DetectedImage::draw() {
	ObjTar->draw(*sprite);
}
void DetectedImage::setActive() {
	if (Click())
	{
		std::cout << "click\n";
	}
}
bool DetectedImage::Click() {
	RenderWindow* temp = pool_window[0].get();
	update();

	bool in_area = Mouse::isButtonPressed(Mouse::Left) &&
		(mouse->getPosition(*temp).y >= pos_y) &&
		(mouse->getPosition(*temp).y < pos_y + size_y) &&
		(mouse->getPosition(*temp).x >= pos_x) &&
		(mouse->getPosition(*temp).x < pos_x + size_x);

	if (in_area)
	{
		bool alpha_pixel = (bool)(image->getPixel(mouse->getPosition(*temp).x - pos_x,
			mouse->getPosition(*temp).y - pos_y).a);
		return alpha_pixel;
	}
	return in_area;
}
void DetectedImage::update()
{
	Vector2f temp = sprite->getOrigin();
	pos_x = sprite->getPosition().x - temp.x;
	pos_y = sprite->getPosition().y - temp.y;
	size_x = texture->getSize().x;
	size_y = texture->getSize().y;
}



Map::Map(string symbol_map, int tyle_size[], Mouse* mouse) {
	this->tyle_size[0] = tyle_size[0];
	this->tyle_size[1] = tyle_size[1];
	std::vector<string> tiles = splitter(symbol_map);
	std::vector<Tile*> img;
	for (int i = 0; i < tiles.size(); i++)
	{
		Tile* tmp = new Tile("tile" + tiles[i] + ".png", mouse);
		img.emplace_back(tmp);
	}

}

std::vector<string> Map::splitter(string symbols) {
	std::vector<string> m;
	string tmp = "";
	for (int i = 0; i < symbols.size(); i++)
	{
		if (symbols[i] != ' ')
		{
			tmp += symbols[i];
		}
		else
		{
			m.emplace_back(tmp);
			tmp = "";
		}
	}
	return m;
}

Tile::Tile(string str,Mouse* mouse) : DetectedImage(str,mouse) {};


void game(RenderTarget* window) {
	Mouse mouse;
	DetectedImage a("tyles/tile_022.png",&mouse);
	DetectedImage b("tyles/tile_022.png", &mouse);
	DetectedImage c("tyles/tile_022.png", &mouse);
	DetectedImage d("tyles/tile_022.png", &mouse);
	a.Scale(5, 5);
	b.Scale(5, 5);
	c.Scale(5, 5);
	d.Scale(5, 5);
	
	a.sprite->setPosition(0, a.texture->getSize().y * 3 / 4);
	b.sprite->setPosition(a.sprite->getPosition().x + a.texture->getSize().x / 2, a.sprite->getPosition().y + a.texture->getSize().y / 4);
	c.sprite->setPosition(b.sprite->getPosition().x + b.texture->getSize().x / 2, b.sprite->getPosition().y + b.texture->getSize().y / 4);
	d.sprite->setPosition(c.sprite->getPosition().x + c.texture->getSize().x / 2, c.sprite->getPosition().y + c.texture->getSize().y / 4);
	//b.sprite->setPosition(a.sprite->getPosition().x, a.sprite->getPosition().y);
	
	std::cout << "a info " << a.sprite->getPosition().x << " " << a.sprite->getPosition().y << '\n' <<
		a.texture->getSize().x << " " << a.texture->getSize().y;
	
	
	
	
	while (pool_window[0].get()->isOpen())
	{
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
						a.setActive();
						b.setActive();
						c.setActive();
						d.setActive();
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
		pool_window[0].get()->draw(*a.sprite);
		b.draw();
		c.draw();
		d.draw();
		pool_window[0].get()->display();
	}

}