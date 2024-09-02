#include "Game.h"
#include "TileMap.h"
#include "TilePanel.h"
#include "interfaceobj.h"
#include "Platform.h"
#include "Singleton.h"

using namespace std;
using namespace sf;

DetectedImage::DetectedImage(string str, Mouse* mouse):DetectedImage() {
	link = str;
	ObjTar = Singleton::instance().getPoolWindow()[0].get();
		//pool_window[0].get();
	image = std::make_unique<sf::Image>();
	texture = std::make_unique<sf::Texture>();
	sprite = std::make_unique<sf::Sprite>();
	this->mouse = mouse;
	image->loadFromFile(link.c_str());
	texture->loadFromImage(*image);
	sprite->setTexture(*texture);
	setOrigin(0, texture->getSize().y * 3 / 4);
	clicked = false;
	update();
}
DetectedImage::DetectedImage() {
	this->texture = nullptr;
	this->sprite = nullptr;
	this->image = nullptr;
	//std::cout << "sprite n = " << (this->sprite != nullptr);
	ObjTar = Singleton::instance().getPoolWindow()[0].get();
	is_bordered = false;
	scale = Vector2i(1, 1);
}
void DetectedImage::setPosition(float x, float y)
{
	sprite->setPosition(x, y);
	update();
	if (is_bordered) borders->setPosition(pos_x, pos_y);
}
void DetectedImage::setOrigin(float x, float y)
{
	sprite->setOrigin(x, y);
	sprite->setPosition(pos_x+sprite->getOrigin().x, pos_y + sprite->getOrigin().y);
}
void DetectedImage::setTarget(RenderTarget* target)
{
	ObjTar = target;
}
void DetectedImage::init_border()
{
	if (!is_bordered)
	{
		is_bordered = true;
		borders = std::make_unique<RectangleShape>();
		update();
		borders->setSize(Vector2f(size_x, size_y));
		borders->setPosition((float)pos_x, (float)pos_y);
		borders->setOutlineColor(Color::White);
		borders->setOutlineThickness((float)4);
		borders->setFillColor(*Singleton::instance().getMainColor());
	}
	
}
Vector2i DetectedImage::getScale()
{
	return scale;
}
Vector2f DetectedImage::getPosition()
{
	update();
	return Vector2f(pos_x, pos_y);
}
Vector2f DetectedImage::getSize()
{
	update();
	return Vector2f(size_x,size_y);
}
string DetectedImage::getLink()
{
	return link;
}
void DetectedImage::Scale(int xmod, int ymod) {
	scale = Vector2i(scale.x * xmod, scale.y * ymod);
	Image* tempimage = new Image;
	tempimage->create(size_x*xmod, size_y*xmod);
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
	texture.reset();
	sprite.reset();
	image.reset(tempimage);
	texture = std::make_unique<sf::Texture>();
	sprite = std::make_unique<sf::Sprite>();
	texture->loadFromImage(*tempimage);
	sprite->setTexture(*texture);
	sprite->setOrigin(0, texture->getSize().y * 3 / 4);
	sprite->setPosition(texture->getSize().x / 2, texture->getSize().y);
	update();

}
void DetectedImage::draw() {
	if (is_bordered) ObjTar->draw(*borders);
	if(sprite!=nullptr) ObjTar->draw(*sprite);
}
void DetectedImage::setActive() {
	if (Click())
	{
		std::cout << "click\n";
	}
}
void DetectedImage::setActive(const sf::View&view)
{
	if (Click(view))
	{
		std::cout << "relative click\n";
	}
}
bool DetectedImage::isActive()
{
	return false;
}
bool DetectedImage::Click() {
	const RenderWindow* temp = Singleton::instance().getPoolWindow()[0].get();
	update();
	//std::cout <<"mouse position "<< mouse->getPosition().x << " " << mouse->getPosition().y << '\n';
	bool in_area = (Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right)) &&
		(mouse->getPosition(*temp).y >= pos_y) &&
		(mouse->getPosition(*temp).y < pos_y + size_y) &&
		(mouse->getPosition(*temp).x >= pos_x) &&
		(mouse->getPosition(*temp).x < pos_x + size_x);
	if (is_bordered) {
		clicked = true;
		return in_area;
	}
	if (in_area)
	{
		bool alpha_pixel = (bool)(image->getPixel(mouse->getPosition(*temp).x - pos_x,
			mouse->getPosition(*temp).y - pos_y).a);
		if (alpha_pixel) clicked = true;
		return alpha_pixel;
	}
	return in_area;
}
bool DetectedImage::Click(const sf::View&view)
{
	
	RenderWindow* temp = Singleton::instance().getPoolWindow()[0].get();
	update();
	sf::Vector2f mouse_pos_relative = temp->mapPixelToCoords(
		sf::Vector2i( mouse->getPosition(*temp).x,mouse->getPosition(*temp).y),view );
	//std::cout <<"mouse position "<< mouse->getPosition().x << " " << mouse->getPosition().y << '\n';
	bool in_area = (Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right)) &&
		(mouse_pos_relative.y >= pos_y) &&
		(mouse_pos_relative.y < pos_y + size_y) &&
		(mouse_pos_relative.x >= pos_x) &&
		(mouse_pos_relative.x < pos_x + size_x);
	if (is_bordered) {
		clicked = true;
		return in_area;
	}
	if (in_area)
	{
		bool alpha_pixel = (bool)(image->getPixel(mouse_pos_relative.x - pos_x,
			mouse_pos_relative.y - pos_y).a);
		if (alpha_pixel) clicked = true;
		return alpha_pixel;
	}
	return in_area;
}
bool DetectedImage::Click(int difference_x, int difference_y)
{
	RenderWindow* temp = Singleton::instance().getPoolWindow()[0].get();
	update();
	//std::cout <<"mouse position "<< mouse->getPosition().x << " " << mouse->getPosition().y << '\n';
	bool in_area = Mouse::isButtonPressed(Mouse::Left) &&
		(mouse->getPosition(*temp).y >= pos_y + difference_y) &&
		(mouse->getPosition(*temp).y < pos_y + size_y + difference_y) &&
		(mouse->getPosition(*temp).x >= pos_x + difference_x) &&
		(mouse->getPosition(*temp).x < pos_x + size_x + difference_x);
	if (is_bordered) {
		clicked = true;
		return in_area;
	}
	if (in_area)
	{
		bool alpha_pixel = (bool)(image->getPixel(mouse->getPosition(*temp).x - pos_x - difference_x,
			mouse->getPosition(*temp).y - pos_y - difference_y).a);
		if (alpha_pixel) clicked = true;
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


bool EditorScene::verifyEvents(const sf::Event& event)
{
	switch (event.type)
	{
	case Event::Closed: {
		Singleton::instance().getPoolButton().clear();
		ButtonLoader(Singleton::instance().getPoolWindow()[0].get(), &Singleton::instance().getMouse(), *Singleton::instance().getMainColor(), "notes/buttons.json");
		return false;
	}
	case Event::KeyPressed: {
		switch (event.key.scancode) {
		case Keyboard::Scan::LAlt:
		{
			std::cout << "LALT\n";
			platform->textClear();
			break;
		}
		case Keyboard::Scan::Backspace:
			platform->deleteLast();
			cout << "dellast\n";
			break;
		}

		break;

	}
	case Event::MouseButtonReleased: {
		if (event.mouseButton.button == Singleton::instance().getMouse().Left) {
			jammable->disable();
		}
		break;
	}
	case Event::MouseButtonPressed: {
		if (Singleton::instance().getMouse().isButtonPressed(Singleton::instance().getMouse().Left))
		{
			jammable->enable();
			//m->setActive();
			platform->leftClicked();

			for (auto i : Singleton::instance().getPoolButton())
			{
				i.get()->setActive();
			}
			//std::cout << "frames = " << img->getFrames();
		}
		else if (Singleton::instance().getMouse().isButtonPressed(Singleton::instance().getMouse().Right)) {
			platform->rightClicked();
		}
		else if (Singleton::instance().getMouse().isButtonPressed(Singleton::instance().getMouse().Middle))
		{
			platform->wheelClicked();
		}

		break;
	}
	case Event::TextEntered:
		if (event.text.unicode != 8) {
			text->setString(event.text.unicode);
			platform->input(event.text.unicode);
		}

		break;
	}
	return true;
}

void EditorScene::runEvents()
{
	buttonWork();
	jammable->exec();
}

void EditorScene::drawing()
{
	Singleton::instance().getPoolWindow()[0].get()->clear(*Singleton::instance().getBackgroundColor());
	std::cout << "";

	platform->draw();
	globalDraw();
	Singleton::instance().getPoolWindow()[0].get()->draw(*text);
	Singleton::instance().getPoolWindow()[0].get()->display();
}

void EditorScene::eventLoop()
{
	while (Singleton::instance().getPoolWindow()[0].get()->isOpen())
	{
		sf::Event event;
		while (Singleton::instance().getPoolWindow()[0].get()->pollEvent(event)) {
			if (!verifyEvents(event)) return;
		}
		runEvents();
		drawing();
	}
}

EditorScene::EditorScene()
{
	platform = std::make_unique<Platform>(&Singleton::instance().getMouse());
	
	Button * settingsImage = new RectButtonImageRolled(1300, 50, 1, "images/settings.png", [this]() {SettingsScene scene{}; scene.eventLoop(); platform->initButtons(&Singleton::instance().getMouse()); }, Singleton::instance().getPoolWindow()[0].get(), &Singleton::instance().getMouse());
	settingsImage->scale(0.5, 0.5);
	settingsImage->setId("game");
	settingsImage->pushToDrawingVector();
	jammed = false;

	jammable = std::make_unique<Jammed>(Singleton::instance().getFPS(), 0.1, [this]() {platform->leftClickedMap(); });

	text = std::make_unique<sf::Text>();
	text->setFont(*Singleton::instance().getGlobalFont());
	text->setPosition(500, 500);
	text->setCharacterSize(50);
	text->setFillColor(Color::White);
}

EditorScene::~EditorScene() = default;
