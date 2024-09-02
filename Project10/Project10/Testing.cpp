#include "Testing.h"
#include "Singleton.h"
bool Testing::verifyEvents(const sf::Event& event)
{
	switch (event.type)
	{
	case Event::Closed: {
		return false;
	}
	}
	return true;
}
void Testing::runEvents()
{
	
}
void Testing::drawing()
{
	object->draw();
}
void Testing::eventLoop()
{
	while (Singleton::instance().getPoolWindow()[0]->isOpen()) {
		Event event;
		while (Singleton::instance().getPoolWindow()[0]->pollEvent(event)) {
			if (!verifyEvents(event)) return;
		}

		runEvents();
		drawing();

	}
}

Testing::Testing()
{
	object = std::make_unique<TileClickingZone>();
}

Testing::~Testing() = default;

int TileClickingZone::leftFunction(int x)
{
	if(x<objectTx->getSize().x/2) return 0.5 * x + objectTx->getSize().y/2;
	return -1;
}

int TileClickingZone::rightFunction(int x)
{
	if (x >= objectTx->getSize().x / 2) return -0.5 * x
		+ objectTx->getSize().y;
	return -1;
}

bool TileClickingZone::Click()
{
	return false;
}

void TileClickingZone::setActive()
{
	return;
}

bool TileClickingZone::isActive()
{
	return false;
}

void TileClickingZone::draw()
{
	Singleton::instance().getPoolWindow()[0]->clear(*Singleton::instance().getBackgroundColor());
	Singleton::instance().getPoolWindow()[0]->draw(*objectSp);
	Singleton::instance().getPoolWindow()[0]->display();
}

void TileClickingZone::drawLines()
{
	std::unique_ptr<sf::Image> tempImage;
	tempImage = std::make_unique<sf::Image>();
	*tempImage = objectTx->copyToImage();
	for (size_t i = 0; i < tempImage->getSize().x; i++)
	{
		int y;
		if (i<16)
		{
			y = leftFunction((int)i);
		}
		else
		{
			y = rightFunction((int)i);
		}
		if(y>0) tempImage->setPixel(i, y, sf::Color::Red);
	}
	objectTx->loadFromImage(*tempImage);
}

TileClickingZone::TileClickingZone()
{
	objectTx = std::make_unique<sf::Texture>();
	objectSp = std::make_unique<sf::Sprite>();
	objectTx->loadFromFile("tyles/tile_040.png");
	objectSp->setTexture(*objectTx);
	objectSp->scale(10, 10);
	drawLines();
}

TileClickingZone::~TileClickingZone() = default;
